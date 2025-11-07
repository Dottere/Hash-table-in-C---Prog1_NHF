cmake_minimum_required(VERSION 4.0)
project(Programming1_NagyHF C)

set(CMAKE_C_STANDARD 99)

add_executable(Programming1_NagyHF main.c
        headers/ht.h
        headers/fnv1a.h
        fnv1a.c
        ht.c
        headers/datastructs.h
)
