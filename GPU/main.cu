#include <fstream>
#include <string>
#include <chrono>
#include <string>
#include <iostream>
#include <iomanip>



//For GPU Access
int* grid = nullptr;
int* gridGPU = nullptr;
int* tempGPU = nullptr;
int width = 0;
int height = 0;


//Error checking for cuda calls
void checkError(cudaError_t e)
{
   if (e != cudaSuccess)
   {
      std::cerr << "CUDA error: " << int(e) << " : " << cudaGetErrorString(e) << '\n';
      abort();
   }
}

//Changes the mod operator to work like python
__host__
int modFixH(int x, int dimension) {
    if (x < 0) {
        return dimension + (x % dimension);
    } else {
        return x % dimension;
    }
}



//Changes the mod operator to work like python
__device__
int modFix(int x, int dimension) {
    if (x < 0) {
        return dimension + (x % dimension);
    } else {
        return x % dimension;
    }
}

/**
* Given the state of a cell the GoL rules apply:
* - Any live call with fewer than 2 neighbors dies = underpopulation
* - Any live cell with two or three live neighbors lives on to the next gen
* - Any live cell with more than 3 live neighbors dies = overpopulation
* - Any dead cell with exactly 3 live neighbors becomes living = reproduction
* 
* After these rules have been checked, the grid is then updated.
*
* @gridGPU: Representation of the grid that lives on the GPU memory.
* @tempGPU: Representation of the grid that lives on the GPU memory that is used for inbetween states.
* @width: The width of the grid.
* @height: The height of the grid.
*/
__global__
void evolve(int* gridGPU, int* tempGPU, int width, int height) {
    //Defineing alive and dead
    int deadValue = 0;
    int aliveValue = 1;
    
    //Gpu loop set up
    int index = blockIdx.x*blockDim.x + threadIdx.x;
    int index2 = blockIdx.y*blockDim.y + threadIdx.y;

    int stride = blockDim.x*gridDim.x;
    int stride2 = blockDim.y*gridDim.y;

    //Gpu iteration of the cells universe
    for (int a=index; a < width; a += stride){
        for(int b=index2; b < height; b += stride2) {

            //Checks for alive neighbors
            int aliveCells = 0;
            for (int k=-1; k <= 1; k++) {
                for (int l=-1; l <= 1; l++) {
                    if (!(k == 0 && l == 0)) {
                        int neigh = gridGPU[(modFix(k + a,width) * width) + modFix(l + b,height)];
                        if ((neigh == aliveValue)) {
                            aliveCells++;
                        }   
                    }
                }
            }

            //Modifies the grid depending on surrounding
            if (aliveCells < 2 || aliveCells > 3) {
                tempGPU[(modFix(a, width)*width)+modFix(b, height)] = deadValue;
                
            } else if (aliveCells == 3) {
                tempGPU[(modFix(a, width)*width)+modFix(b, height)] = aliveValue;
            } 
        }
    }
}

/**
 * Sets up the grid so that every cell of the environment starts off
 * as being dead.
 * 
 * @grid: The grid that the game of life will be played on.
 * @width: The width of the environment.
 * @height: The height of the environment.
 */
void intialGrid(int* grid, int width, int height){
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            grid[j*width + i] = 0;   
        }
    }
}

// void debugGrid(int* grid, int width, int height) {
//     for (int i = 0; i < width; ++i) {
//         for (int j = 0; j < height; ++j) {
//             std::cout<<grid[j*width + i]<<" ";   
//         }
//         std::cout<<std::endl;
//     }
//     std::cout<<std::endl;
// }

//Runs Program
int main(int argc, char const *argv[]) {
    int generations;
    std::string visOut = "NoVis";
    const std::string visStatus = "NoVis";
    

    if (argc == 6) {
        //argv[1] is the file you want to insert
        width = atoi(argv[2]); //argv[2]
        height = atoi(argv[3]); //argv[3]
        generations = atoi(argv[4]); //argv[4]
        visOut = argv[5];
    } else {
        //argv[1] is the file you want to insert
        width = 256; //argv[2]
        height = 256; //argv[3]
        generations = 50; //argv[4]
        
    }


    //Initalize the grid for the game
    grid = new int[width*height];
    intialGrid(grid, width, height);

    //Add pattern to the grid
    std::ifstream file(argv[1]);
    std::string line;
    int centering = 0;
    bool centered = false;
    int i = 0;
    while(getline(file, line)) {
        if(centered == false){
            centering += line.size();
            centered = true;
        }
        for (uint j=0; j<line.length(); j++) {
            if (line[j] == 'O') {
                grid[(((i+(width/2)) - (centering/2)) * width) + (j+(height/2) - (centering/2))] = 1;
            }
        }
        i++;
    }
    file.close();
    std::ofstream outFile;

    if (visStatus.compare(visOut)) { //For visualizing and verification
        outFile.open("game_of_life_save.txt");
    }

    
    //Allocate GPU memory for calculations
    checkError(cudaMalloc(&gridGPU, width*height*sizeof(int)));
    checkError(cudaMalloc(&tempGPU, width*height*sizeof(int)));

    //Copy intial array to GPU memory locations
    checkError(cudaMemcpy(gridGPU, grid, width*height*sizeof(int), cudaMemcpyHostToDevice));
    checkError(cudaMemcpy(tempGPU, grid, width*height*sizeof(int), cudaMemcpyHostToDevice));

    // assign a 2D distribution of CUDA "threads" within each CUDA "block"
    int Threads = 256;
    int Blocks = (width+Threads-1)/Threads;

    for (int i = 0; i < generations; i++) {
        //plays gol
        evolve<<<Blocks, Threads>>>(gridGPU, tempGPU, width, height);
        
        //Sync host and device
        cudaDeviceSynchronize();

        // copy from GPU to CPU
        checkError(cudaMemcpy(grid, tempGPU, width*height*sizeof(int), cudaMemcpyDeviceToHost));
        checkError(cudaMemcpy(gridGPU, grid, width*height*sizeof(int), cudaMemcpyHostToDevice));

        if (visStatus.compare(visOut)) { //For visualizing and verification
            for (int i=0; i < width; i++) {
                for (int j=0; j < height; j++) {
                    outFile << grid[(modFixH(i, width)*width)+modFixH(j, height)];
                }
                outFile << std::endl;
            }
            outFile << std::endl;
        }   
    }

    if (visStatus.compare(visOut)) {
       outFile.close(); 
    }

    cudaFree(gridGPU);
    cudaFree(tempGPU);
    free(grid);
    
    return 0;
}