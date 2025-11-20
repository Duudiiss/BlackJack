@echo off
title Testes Unitarios - BlackJack
color 0A

echo ========================================
echo    TESTES UNITARIOS - BLACKJACK
echo ========================================
echo.

:: Verificar se arquivos existem NA MESMA PASTA
if not exist "Baralho.h" (
    echo ❌ ERRO: Arquivo  nao encontrado!
    goto error
)

if not exist "Baralho.c" (
    echo ❌ ERRO: Arquivo Baralho.c nao encontrado!
    goto error
)

if not exist "test_baralho.c" (
    echo ❌ ERRO: Arquivo test_baralho.c nao encontrado!
    goto error
)

echo  Todos os arquivos encontrados!
echo  Compilando testes...

:: Compilar - tudo na mesma pasta
gcc -o test_baralho.exe test_baralho.c Baralho.c

if %errorlevel% neq 0 (
    echo.
    echo ❌ ERRO: Falha na compilacao!
    goto error
)

echo.
echo ✅ Compilacao bem-sucedida!
echo 🚀 Executando testes...
echo ========================================
echo.

:: Executar testes
test_baralho.exe

goto end

:error
echo.
echo 💡 VERIFIQUE:
echo - Todos arquivos estao nesta pasta: %CD%
echo - Nomes dos arquivos estao CORRETOS
dir *.c *.h
echo.

:end
echo ========================================
pause@echo off
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

if not exist "test_baralho.c" (
    echo ❌ ERRO: Arquivo test_baralho.c nao encontrado!
    goto error
)

echo 📁 Todos os arquivos encontrados!
echo 🔨 Compilando testes...

:: Compilar - tudo na mesma pasta
gcc -o test_baralho.exe test_baralho.c Baralho.c

if %errorlevel% neq 0 (
    echo.
    echo ❌ ERRO: Falha na compilacao!
    goto error
)

echo.
echo ✅ Compilacao bem-sucedida!
echo 🚀 Executando testes...
echo ========================================
echo.

:: Executar testes
test_baralho.exe

goto end

:error
echo.
echo 💡 VERIFIQUE:
echo - Todos arquivos estao nesta pasta: %CD%
echo - Nomes dos arquivos estao CORRETOS
dir *.c *.h
echo.

:end
echo ========================================
pause