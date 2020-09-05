import numpy as np
import matplotlib as plt
import json

data_struct = {}

currentOpti = ""
currentGen = ""
currentGrid = ""

with open('data.txt', 'r') as file:
    for line in file:
        if line == '\n':
            continue
        if "Optimisation" in line:
            currentOpti = line.split(":")[1][1:-1]
            data_struct[currentOpti] = {}
        elif "Generations" in line:
            currentGen = line.split(":")[1][1:-1]
            data_struct[currentOpti][currentGen] = {}
        elif "Grid Size" in line:
            currentGrid = line.split(":")[1][1:-1]
            data_struct[currentOpti][currentGen][currentGrid] = {}
        else:
            dataLine = line.split(" ")
            key = dataLine[0]
            data_struct[currentOpti][currentGen][currentGrid][key] = np.zeros(4, float)
            
            data_struct[currentOpti][currentGen][currentGrid][key][0]=float(dataLine[1])
            data_struct[currentOpti][currentGen][currentGrid][key][1]=float(dataLine[2])
            data_struct[currentOpti][currentGen][currentGrid][key][2]=float(dataLine[3])
            data_struct[currentOpti][currentGen][currentGrid][key][3]=float(dataLine[4])

with open('data.json', 'w') as jfile:
    json.dump(data_struct, jfile)


