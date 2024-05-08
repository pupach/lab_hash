import matplotlib.pyplot as plt
import csv

fileNames = ["hash_lin_random_025", "hash_quad_random_025", "Two_Hash_random_025"]

title     = "hash_1_random_025_withut_cep"
units     = "ms"


dataDir   = "data/"
graphDir  = "graph/"

X = []
Y = []

for name in fileNames:
    with open(dataDir + name + ".txt", 'r') as dataFile:
        plotting = csv.reader(dataFile, delimiter=',')
        
        for ROWS in plotting:
            print(ROWS, name)
            X.append(int(ROWS[0]))
            Y.append(float(ROWS[1]))

    plt.plot(X, Y)
    X.clear()
    Y.clear()



plt.legend(fileNames)

plt.title(title)

plt.xlabel("size")
plt.ylabel(units)

plt.savefig(graphDir + title + "png")
plt.show()


