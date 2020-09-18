import os
import time
"""
This Script is used to gather all the data from running all the combinations of inputs to ./main
It will then write the output to a file called "data.txt" which can be processed and changed 
into json format using processData.py in the reports file.
"""
testAmount = 0
Generations = ["100","1000","10000"]
GridSize = ["256", "512", "1024"]
OptimiseLevel = ["all", "levelOne", "levelTwo", "levelThree"]
Patterns = [
    "PatternFiles/13enginecordership.txt",
    "PatternFiles/Frothing_puffer.txt",
    "PatternFiles/Gosper_glider_gun.txt",
    "PatternFiles/Period144Oscillator.txt"]
data_file = open("data.txt", 'w')

for i in OptimiseLevel:
    data_file.write("Optimisation Level: " + i + '\n')
    os.system("make " + i)
    for j in Generations:
        data_file.write("Generations: " + j + '\n')
        for k in GridSize:
            data_file.write("Grid Size: " + k + '\n')
            for l in Patterns:
                title = l.split("/")[1]
                data_file.write(title[:-4])
                for m in range(0,5):
                    start_time = time.time()
                    os.system("./main " + l + ' ' + k + ' ' +
                    k + ' ' + j + ' ' + 'NoVis')
                    end_time = time.time() - start_time
                    testAmount = testAmount + 1
                    data_file.write(' ' + str(end_time))
                    if m == 4:
                        data_file.write('\n')
            data_file.write('\n')    

data_file.close()
print(testAmount)

                   
                    
