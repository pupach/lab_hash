import matplotlib.pyplot as plt
import csv

fileNames = ["AVL_insert", "decart_insert", "splay_insert", "RBT_insert", "AVL_remove", "decart_remove", "splay_remove", "RBT_remove"]

title     = "square sorts"
units     = "ms"


dataDir   = "data/"
graphDir  = "graphs/"

X = []
Y = []

for name in fileNames:

    with open(dataDir + name + ".csv", 'r') as dataFile:
        plotting = csv.reader(dataFile, delimiter=',')
        
        for ROWS in plotting:
            X.append(int(ROWS[0]))
            Y.append(int(ROWS[1]))

    plt.plot(X, Y)
    X.clear()
    Y.clear()



plt.legend(fileNames)

plt.title(title)

plt.xlabel("array size")
plt.ylabel(units)

plt.savefig(graphDir + title + "png")
plt.show()


