cmake_minimum_required(VERSION 3.27)
project(lab_hash)

set(CMAKE_C_STANDARD 17)

SET(CMAKE_EXE_LINKER_FLAGS  "-fsanitize=address -lm")



add_executable(lab_hash main.c
        hash_cep.c
        hash_cep.h
        hash_lin.c
        hash_lin.h
        func.c
)

add_executable(lab_hash_find
        hash_cep.c
        hash_cep.h
        hash_lin.c
        hash_lin.h
        func.c
        func.h
        PerfectHashFind.c
        PerfectHashFind.h
        find_main.c
        find_main.h)

add_executable(lab_hash_random
        hash_cep.c
        hash_cep.h
        hash_lin.c
        hash_lin.h
        func.c
        func.h
        main_random.c)

