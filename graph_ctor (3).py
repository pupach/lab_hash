import matplotlib.pyplot as plt
import csv

fileNames = ["hash_lin", "Cep_Hash", "hash_quad", "Two_Hash", "hash_lin_find", "Cep_Hash_find", "hash_quad_find", "Perfect_find"
             , "hash_lin_random", "Cep_Hash_random", "hash_quad_random", "Two_Hash_random"]

title     = "square sorts"
units     = "ms"


dataDir   = "cmake-build-debug"
graphDir  = ""

X = []
Y = []

for name in fileNames:
    with open(dataDir + name + ".txt", 'r') as dataFile:
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


