cmake_minimum_required(VERSION 3.27)
project(lab_hash)

set(CMAKE_C_STANDARD 17)

SET(CMAKE_EXE_LINKER_FLAGS  "-fsanitize=address -lm")



add_executable(lab_hash main.c
        hash_chain.c
        hash_chain.h
        hash_open_adress.c
        hash_open_adress.h
)

add_executable(lab_hash_find
        hash_chain.c
        hash_chain.h
        hash_open_adress.c
        hash_open_adress.h
        find_main.c
        find_main.h)

add_executable(lab_hash_random
        hash_chain.c
        hash_chain.h
        hash_open_adress.c
        hash_open_adress.h
        main_random.c)

