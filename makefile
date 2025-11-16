# Makefile para compilar o programa de Blackjack em C
# =============================

# 1. QUAL COMPILADOR USAR?
CC = gcc

# 2. QUAIS OPÇÕES USAR NA COMPILAÇÃO?
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
# -Wall = mostra avisos importantes
# -Wextra = mostra mais avisos
# -std=c99 = usa a versão C99 do C
# -Iinclude = procura arquivos .h na pasta "include"

# 3. QUAIS ARQUIVOS PRECISAM SER COMPILADOS?
SOURCES = src/Baralho.c src/test_baralho.c

# 4. NOME DO PROGRAMA FINAL
TARGET = blackjack

# 5. COMO CRIAR O PROGRAMA FINAL?
$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)
	@echo "✅ Programa criado: $(TARGET)"

# 6. COMANDO PARA RODAR OS TESTES
test: $(TARGET)
	@echo "🎯 RODANDO TESTES..."
	./$(TARGET)

# 7. COMANDO PARA APAGAR O PROGRAMA
clean:
	rm -f $(TARGET)
	@echo "🧹 PROGRAMA REMOVIDO"

# 8. COMANDO DE AJUDA
help:
	@echo "📋 COMANDOS DISPONÍVEIS:"
	@echo "  make        - Compila o programa"
	@echo "  make test   - Compila e roda os testes" 
	@echo "  make clean  - Apaga o programa"
	@echo "  make help   - Mostra esta ajuda"