cmake_minimum_required(VERSION 3.10)
project(BlackJack C)

add_executable(BlackJack
    src/main.c
    src/Baralho.c
    src/Jogador.c
    src/Regras.c
    src/Fichas.c
    src/Partida.c
)

if(WIN32)
    set_target_properties(BlackJack PROPERTIES
        WIN32_EXECUTABLE FALSE
    )
endif()
