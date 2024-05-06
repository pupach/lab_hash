import matplotlib.pyplot as plt
import csv

fileNames = ["hash_lin", "Cep_Hash", "hash_quad", "Two_Hash"]

title     = "hash_1"
units     = "ms"


dataDir   = "cmake-build-debug/"
graphDir  = ""

X = []
Y = []

for name in fileNames:
    with open(dataDir + name + ".txt", 'r') as dataFile:
        plotting = csv.reader(dataFile, delimiter=',')
        
        for ROWS in plotting:
            print(ROWS, name)
            X.append(float(ROWS[0]))
            Y.append(float(ROWS[1]))

    plt.plot(X, Y)
    X.clear()
    Y.clear()



plt.legend(fileNames)

plt.title(title)

plt.xlabel("load_factor")
plt.ylabel(units)

plt.savefig(graphDir + title + "png")
plt.show()


