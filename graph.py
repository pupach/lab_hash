import matplotlib.pyplot as plt
import csv

fileNames = ["hash_lin_random_025", "hash_quad_random_025", "Two_Hash_random_025"]
dataDir   = "../data/"
graphDir  = "../graph/"
units     = "ms"

def gen_graphs(fileNames, title):
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


gen_graphs(["hash_lin_random_025", "hash_quad_random_025", "Two_Hash_random_025"], "hash_rand_without_cep_025")
gen_graphs(["hash_lin_random_025", "hash_quad_random_025", "Two_Hash_random_025", "Cep_Hash_random_025"], "hash_rand_025")

gen_graphs(["hash_lin_random_075", "hash_quad_random_075", "Two_Hash_random_075"], "hash_rand_without_cep_075")
gen_graphs(["hash_lin_random_075", "hash_quad_random_075", "Two_Hash_random_075", "Cep_Hash_random_075"], "hash_rand_075")

gen_graphs(["hash_lin_random", "hash_quad_random", "Two_Hash_random"], "hash_rand_without_cep")
gen_graphs(["hash_lin_random", "hash_quad_random", "Two_Hash_random", "Cep_Hash_random"], "hash_rand")

gen_graphs(["hash_lin_find", "hash_quad_find", "Perfect_find", "Cep_Hash_find"], "hash_find")
gen_graphs(["hash_lin_find", "hash_quad_find", "Perfect_find"], "hash_findwithout_cep")

gen_graphs(["hash_lin", "hash_quad", "Two_Hash", "Cep_Hash"], "hash_1")
gen_graphs(["hash_lin", "hash_quad", "Two_Hash"], "hash_1_without_cep")

