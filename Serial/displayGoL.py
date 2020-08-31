import matplotlib.pyplot as plt 
import matplotlib.animation as animation
import numpy as np
import sys
import os

#Start up C++ GoL
#---------------------------------
argv = sys.argv
argc = len(argv)
#Needed
#----------------------------
#argv[1]: Vis of NoVis | indicates if the GoL is needed to be Visual or not
#
#Optional
#----------------------------
#argv[2]: Path to pattern txt file
#argv[3]: Height of Grid
#argv[4]: Width of Grid
#argv[5]: Amount of moves for the simulation

#Vis or NoVis
Vis =  False
default = True

if argv[1] == "Vis":
    Vis = True
elif argv[1] == "NoVis":
    Vis = False
else:
    print("Pick option Vis or NoVis")
    exit

if argc == 6:
    path = argv[2]
    gridHeight = argv[3]
    gridWidth = argv[4]
    gridEvolves = argv[5]
    default = False


if default:
    os.system("./main")
else:
    os.system(
        "./main " + path + ' ' + gridWidth + ' ' 
        + gridHeight + ' ' + gridEvolves
    )
    
if (Vis == False):
    exit




#Visual start up
#---------------------------------------------------
if (argc == 6):
    moves = int(gridEvolves)
    N = int(gridWidth)
else:
    moves = 50
    N = 256

lifeIndex = 0



life  = np.empty(moves, np.ndarray)

while (lifeIndex<moves):
    life[lifeIndex] = np.zeros((N,N), np.uint)
    lifeIndex = lifeIndex + 1

lifeIndex = 0

path = "game_of_life_save.txt"

with open(path, 'r') as file:

    while (lifeIndex < moves):
        k = 0
        while (k <= N):
            line = file.readline()
            if line == '\n':
                lifeIndex = lifeIndex + 1
                break
            else:
                line = line[:-1]
                for index, element in enumerate(line):
                    life[lifeIndex][k][index] = int(element)
            k = k + 1


lifeIndex = 0





#Animation
#-----------------------------------------------

fig = plt.figure()
plt.pink()

cells = life[lifeIndex]


img = plt.imshow(cells, animated=True)



def animate(i):
    global life
    global lifeIndex

    lifeIndex = lifeIndex + 1

    if lifeIndex == moves:
        lifeIndex = 0

    updatedCells = life[lifeIndex]

    img.set_array(updatedCells)

    return img




interval = 200 #ms

# # #animate 24 fames with an interval between them calling animate function at each frame
ani = animation.FuncAnimation(fig, animate, frames=24, interval=interval)

plt.show()