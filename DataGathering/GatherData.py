import os
import time
import json
"""
This Script is used to gather all the data from running all the combinations of inputs to ./main
It will then write the output to a file called "data.txt" which can be processed and changed 
into json format using processData.py in the reports file.
"""
data_json = {}
testAmount = 0
Generations = ["100","1000","10000"]
GridSize = ["256", "512", "1024"]
OptimiseLevel = ["all", "levelOne", "levelTwo", "levelThree"]
ImplementationTypes = ["SerialOptimized", "Parallel", "GPU"]
Patterns = [
    "PatternFiles/13enginecordership.txt",
    "PatternFiles/Frothing_puffer.txt",
    "PatternFiles/Gosper_glider_gun.txt",
    "PatternFiles/Period144Oscillator.txt"]

for a in ImplementationTypes:
    data_json[a] = {}
    if a == "SerialOptimized":
        os.system("cd ../" + a)
    if a == "Parallel":
        os.system("cd ../" + a)
        OptimiseLevel = ["para", "para1", "para2", "para3"]
    if a == "GPU":
        os.system("cd ../" + a)
        OptimiseLevel = ["gpu"]
    for i in OptimiseLevel:
        data_json[a][i] = {}
        os.system("make " + i)
        for j in Generations:
            data_json[a][i][j] = {}
            for k in GridSize:
                data_json[a][i][j][k] = {}
                for l in Patterns:
                    title = l.split("/")[1]
                    data_json[a][i][j][k][title[:-4]] = {}
                    for m in range(0,6):
                        start_time = time.time()
                        os.system("./main " + l + ' ' + k + ' ' +
                        k + ' ' + j + ' ' + 'NoVis')
                        end_time = time.time() - start_time
                        testAmount = testAmount + 1
                        data_json[a][i][j][k][title[:-4]][m] = str(end_time)
    os.system("cd ../DataGathering" + a)


with open("data.json", 'w') as dataFile:
    json.dump(data_json, dataFile)

dataFile.close()
print(testAmount)

                   
                    
