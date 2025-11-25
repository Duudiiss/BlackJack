@echo off
title Testes Unitarios - BlackJack
color 0A

echo ========================================
echo    TESTES UNITARIOS - BLACKJACK
echo ========================================
echo.

:: Verificar se arquivos existem NA MESMA PASTA
if not exist "Baralho.h" (
    echo ❌ ERRO: Arquivo Baralho.h nao encontrado!
    goto error
)

if not exist "Baralho.c" (
    echo ❌ ERRO: Arquivo Baralho.c nao encontrado!
    goto error
)

if not exist "Jogador.h" (
    echo ❌ ERRO: Arquivo Jogador.h nao encontrado!
    goto error
)

if not exist "Jogador.c" (
    echo ❌ ERRO: Arquivo Jogador.c nao encontrado!
    goto error
)

if not exist "test_baralho.c" (
    echo ❌ ERRO: Arquivo test_baralho.c nao encontrado!
    goto error
)

if not exist "test_jogador.c" (
    echo ❌ ERRO: Arquivo test_jogador.c nao encontrado!
    goto error
)

echo 📁 Todos os arquivos encontrados!
echo 🔨 Compilando testes...
echo.

:: Compilar testes do BARALHO
echo 🔨 Compilando test_baralho.c ...
gcc -Wall -Wextra -o test_baralho.exe test_baralho.c Jogador.c Baralho.c
if %errorlevel% neq 0 (
    echo.
    echo ❌ ERRO: Falha na compilacao de test_baralho.c !
    goto error
)

:: Compilar testes do JOGADOR
echo.
echo 🔨 Compilando test_jogador.c ...
gcc -Wall -Wextra -o test_jogador.exe test_jogador.c Jogador.c Baralho.c
if %errorlevel% neq 0 (
    echo.
    echo ❌ ERRO: Falha na compilacao de test_jogador.c !
    goto error
)

echo.
echo ✅ Compilacao bem-sucedida!
echo 🚀 Executando testes...
echo ========================================
echo.

:: Executar testes
echo ▶ Executando test_baralho.exe
echo ----------------------------------------
test_baralho.exe
echo.

echo ▶ Executando test_jogador.exe
echo ----------------------------------------
test_jogador.exe
echo.

goto end

:error
echo.
echo 💡 VERIFIQUE:
echo - Todos arquivos estao nesta pasta: %CD%
echo - Nomes dos arquivos estao CORRETOS
echo.
dir *.c *.h
echo.

:end
echo ========================================
pause
