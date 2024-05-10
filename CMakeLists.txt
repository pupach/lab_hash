cmake_minimum_required(VERSION 3.27)
project(lab_hash)

set(CMAKE_C_STANDARD 17)

SET(CMAKE_EXE_LINKER_FLAGS  "-fsanitize=address -lm")


execute_process(COMMAND mkdir -p data)

add_executable(gen_graph mains.c)

add_custom_target(python
        gen_graph
        COMMAND mkdir -p graph && ../venv/bin/python3 ../graph.py
        COMMENT "Executing linter"
)

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
        Hash_Perfect.h
        Hash_Perfect.c
        find_main.c
        find_main.h)

add_executable(lab_hash_random
        hash_chain.c
        hash_chain.h
        hash_open_adress.c
        hash_open_adress.h
        main_random.c)

