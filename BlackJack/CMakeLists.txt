cmake_minimum_required(VERSION 3.10)

# Nome do projeto
project(BlackJack C)

# Coleta todos os arquivos .c da pasta src
file(GLOB SOURCES "src/*.c")

# Inclui a pasta de cabeçalhos
include_directories(include)

# Cria o executável
add_executable(BlackJack ${SOURCES})

# Define o padrão do C (C20 equivale a C 2023)
if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET BlackJack PROPERTY C_STANDARD 23)
endif()
