cmake_minimum_required(VERSION 3.10)
project(BlackJack)

# Especificar que é um programa console
add_executable(BlackJack 
    src/main.c
    src/Baralho.c
    src/Baralho.h
)

# Se estiver compilando como Windows App, mude para Console:
if(WIN32)
    set_target_properties(BlackJack PROPERTIES
        WIN32_EXECUTABLE FALSE
    )
endif()