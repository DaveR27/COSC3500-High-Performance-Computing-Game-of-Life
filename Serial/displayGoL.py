import matplotlib.pyplot as plt 
import matplotlib.animation as animation
import numpy as np

moves = 200
N = 256
storyIndex = 0


story  = np.empty(moves, np.object)

while (storyIndex<moves):
    story[storyIndex] = np.zeros((N,N), np.uint)
    storyIndex = storyIndex + 1

storyIndex = 0

path = "game_of_life_save.txt"

with open(path, 'r') as file:
    for line in file.readline():
        print(line)
        print("Len: %d", len(line))
        # if (line == '\n'):
        #     break
        # else:
        #     i = 0
        #     j = 0
        #     while (i < N):
        #         while (j < N):
        #             story[storyIndex][i, j] = line[j]
        #             j = j + 1
        #         j = 0
        #         i = i + 1
    #         if line == '\n':
    #             storyIndex = storyIndex + 1
    #         else:
    #             i = 0
    #             j = 0
    #             while i < N:
    #                 while j < N:
    #                     story[storyIndex][i,j] = line[j]
    #                     j = j + 1
    #                 j = 0
    #                 i = i + 1

storyIndex = 0





#Animation
#-----------------------------------------------
fig = plt.figure()
plt.pink()

cells = story[storyIndex]
print(cells)

img = plt.imshow(cells, animated=True)


def getNextPhase(storyIndex):
    storyIndex = storyIndex + 1
    return story[storyIndex]

def animate(i):
    nextGen = getNextPhase(storyIndex)
    img.set_array(nextGen)
    return img



interval = 200 #ms

# #animate 24 fames with an interval between them calling animate function at each frame
ani = animation.FuncAnimation(fig, animate, frames=24, interval=interval, blit=True)

plt.show()