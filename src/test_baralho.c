// TestesBaralho.c
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "Baralho.h"

// Macros para testes
#define TEST_ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            printf("TEST FAILED: %s (Line %d)\n", message, __LINE__); \
            return 0; \
        } else { \
            printf("TEST PASSED: %s\n", message); \
        } \
    } while(0)

// Função auxiliar para verificar se baralho está completo
int verificaBaralhoCompleto(const Baralho* baralho) {
    int tamanho = BaralhoGetTamanho(baralho);
    if (tamanho != MAX_CARTAS) return 0;
    
    int count[4][13] = {0}; // Matriz para contar cartas por naipe e número
    char naipes[] = {'C', 'O', 'E', 'P'};
    
    for (int i = 0; i < tamanho; i++) {
        const Carta* c = BaralhoGetCartaConst(baralho, i);
        if (!c) return 0;

        int  numero = CartaGetNumero(c);
        char naipe  = CartaGetNaipe(c);
        int  valor  = CartaGetValor(c);
        
        // Encontra índice do naipe
        int naipe_idx = -1;
        for (int n = 0; n < 4; n++) {
            if (naipe == naipes[n]) {
                naipe_idx = n;
                break;
            }
        }
        if (naipe_idx == -1) return 0;
        
        // Verifica número válido
        if (numero < 1 || numero > 13) return 0;
        
        // Verifica valor correto
        int valor_esperado;
        if (numero == 1)       valor_esperado = 11;
        else if (numero > 10)  valor_esperado = 10;
        else                   valor_esperado = numero;
        
        if (valor != valor_esperado) return 0;
        
        count[naipe_idx][numero - 1]++;
    }
    
    // Verifica se tem exatamente uma carta de cada tipo
    for (int n = 0; n < 4; n++) {
        for (int num = 0; num < 13; num++) {
            if (count[n][num] != 1) return 0;
        }
    }
    
    return 1;
}

// TESTE 1: CriaBaralho
int test_CriaBaralho() {
    printf("\n=== TESTE CriaBaralho ===\n");
    
    Baralho* baralho = CriaBaralho();
    TEST_ASSERT(baralho != NULL, "Baralho criado nao deve ser NULL");
    TEST_ASSERT(BaralhoGetTamanho(baralho) == MAX_CARTAS, "Tamanho deve ser 52");
    TEST_ASSERT(verificaBaralhoCompleto(baralho) == 1, "Baralho deve conter todas as 52 cartas unicas");
    
    // Verifica algumas cartas específicas
    int as_encontrado = 0, rei_encontrado = 0;
    int tamanho = BaralhoGetTamanho(baralho);

    for (int i = 0; i < tamanho; i++) {
        const Carta* c = BaralhoGetCartaConst(baralho, i);
        TEST_ASSERT(c != NULL, "Carta acessivel por indice");

        int numero = CartaGetNumero(c);
        int valor  = CartaGetValor(c);

        if (numero == 1  && valor == 11) as_encontrado = 1;
        if (numero == 13 && valor == 10) rei_encontrado = 1;
    }
    TEST_ASSERT(as_encontrado, "Deve conter As com valor 11");
    TEST_ASSERT(rei_encontrado, "Deve conter Rei com valor 10");
    
    DestroiBaralho(baralho);
    return 1;
}

// TESTE 2: DestroiBaralho
int test_DestroiBaralho() {
    printf("\n=== TESTE DestroiBaralho ===\n");
    
    // Teste com baralho válido
    Baralho* baralho = CriaBaralho();
    int resultado = DestroiBaralho(baralho);
    TEST_ASSERT(resultado == 0, "Destruicao de baralho valido deve retornar 0");
    
    // Teste com NULL
    resultado = DestroiBaralho(NULL);
    TEST_ASSERT(resultado == -1, "Destruicao de NULL deve retornar -1");
    
    return 1;
}

// TESTE 3: Embaralha
int test_Embaralha() {
    printf("\n=== TESTE Embaralha ===\n");
    
    Baralho* baralho = CriaBaralho();
    
    // Teste com baralho válido
    int resultado = Embaralha(baralho);
    TEST_ASSERT(resultado == 0 || resultado == 1, "Embaralha deve retornar 0 ou 1");
    TEST_ASSERT(BaralhoGetTamanho(baralho) == MAX_CARTAS, "Tamanho deve permanecer 52 apos embaralhar");
    
    // Teste com NULL
    resultado = Embaralha(NULL);
    TEST_ASSERT(resultado == -1, "Embaralha com NULL deve retornar -1");
    
    // Teste múltiplos embaralhamentos
    Baralho* baralho2 = CriaBaralho();
    (void)Embaralha(baralho);
    (void)Embaralha(baralho2);
    
    // Verifica se pelo menos algumas cartas mudaram de posição
    int tamanho = BaralhoGetTamanho(baralho);
    int limite = tamanho < 10 ? tamanho : 10;
    int cartas_na_mesma_posicao = 0;

    for (int i = 0; i < limite; i++) {
        const Carta* c1 = BaralhoGetCartaConst(baralho, i);
        const Carta* c2 = BaralhoGetCartaConst(baralho2, i);
        TEST_ASSERT(c1 != NULL && c2 != NULL, "Cartas acessiveis apos embaralhar");

        int num1 = CartaGetNumero(c1);
        int num2 = CartaGetNumero(c2);
        char np1 = CartaGetNaipe(c1);
        char np2 = CartaGetNaipe(c2);

        if (num1 == num2 && np1 == np2) {
            cartas_na_mesma_posicao++;
        }
    }
    TEST_ASSERT(cartas_na_mesma_posicao < limite, "Embaralhamentos diferentes devem produzir ordens diferentes");
    
    DestroiBaralho(baralho);
    DestroiBaralho(baralho2);
    return 1;
}

// TESTE 4: PegaCarta
int test_PegaCarta() {
    printf("\n=== TESTE PegaCarta ===\n");
    
    Baralho* baralho = CriaBaralho();
    int tamanho_inicial = BaralhoGetTamanho(baralho);
    
    // Teste pegar várias cartas
    for (int i = 0; i < 5; i++) {
        Carta* carta = PegaCarta(baralho);
        TEST_ASSERT(carta != NULL, "PegaCarta deve retornar carta valida");

        int numero = CartaGetNumero(carta);
        TEST_ASSERT(numero >= 1 && numero <= 13, "Carta deve ter numero entre 1-13");

        TEST_ASSERT(BaralhoGetTamanho(baralho) == tamanho_inicial - i - 1,
                    "Tamanho deve diminuir apos pegar carta");
    }
    
    // Teste pegar todas as cartas
    while (BaralhoGetTamanho(baralho) > 0) {
        Carta* carta = PegaCarta(baralho);
        TEST_ASSERT(carta != NULL, "Deve conseguir pegar cartas ate o baralho acabar");
    }
    
    // Teste pegar carta de baralho vazio
    Carta* carta = PegaCarta(baralho);
    TEST_ASSERT(carta == NULL, "PegaCarta de baralho vazio deve retornar NULL");
    TEST_ASSERT(BaralhoGetTamanho(baralho) == 0, "Tamanho deve permanecer 0");
    
    // Teste com NULL
    carta = PegaCarta(NULL);
    TEST_ASSERT(carta == NULL, "PegaCarta com NULL deve retornar NULL");
    
    DestroiBaralho(baralho);
    return 1;
}

// TESTE 5: Valores das Cartas
int test_ValoresCartas() {
    printf("\n=== TESTE Valores das Cartas ===\n");
    
    Baralho* baralho = CriaBaralho();
    
    int as_count = 0, figura_count = 0, numero_count = 0;
    int tamanho = BaralhoGetTamanho(baralho);
    
    for (int i = 0; i < tamanho; i++) {
        const Carta* c = BaralhoGetCartaConst(baralho, i);
        TEST_ASSERT(c != NULL, "Carta acessivel por indice");

        int numero = CartaGetNumero(c);
        int valor  = CartaGetValor(c);
        
        if (numero == 1) {
            TEST_ASSERT(valor == 11, "As deve valer 11");
            as_count++;
        } else if (numero >= 11 && numero <= 13) {
            TEST_ASSERT(valor == 10, "Figuras (J, Q, K) devem valer 10");
            figura_count++;
        } else {
            TEST_ASSERT(valor == numero, "Cartas 2-10 devem valer seu numero");
            numero_count++;
        }
    }
    
    TEST_ASSERT(as_count == 4, "Deve haver 4 Ases");
    TEST_ASSERT(figura_count == 12, "Deve haver 12 figuras (3 por naipe)");
    TEST_ASSERT(numero_count == 36, "Deve haver 36 cartas numericas (9 por naipe)");
    
    DestroiBaralho(baralho);
    return 1;
}

// TESTE 7: Integração Completa
int test_IntegracaoCompleta() {
    printf("\n=== TESTE Integracao Completa ===\n");
    
    // Cria, embaralha, pega cartas e destrói
    Baralho* baralho = CriaBaralho();
    TEST_ASSERT(baralho != NULL, "Baralho criado com sucesso");
    
    int resultado_embaralha = Embaralha(baralho);
    TEST_ASSERT(resultado_embaralha == 0 || resultado_embaralha == 1, "Embaralhamento bem-sucedido");
    
    // Pega algumas cartas
    Carta* carta1 = PegaCarta(baralho);
    Carta* carta2 = PegaCarta(baralho);
    TEST_ASSERT(carta1 != NULL && carta2 != NULL, "Cartas pegas com sucesso");
    TEST_ASSERT(carta1 != carta2, "Cartas diferentes devem ter enderecos diferentes");
    
    int resultado_destroi = DestroiBaralho(baralho);
    TEST_ASSERT(resultado_destroi == 0, "Baralho destruido com sucesso");
    
    return 1;
}

// Função principal para rodar todos os testes
int main() {
    printf("INICIANDO TESTES UNITARIOS - BARALHO\n");
    
    int total_passados = 0;
    int total_testes = 6;
    
    total_passados += test_CriaBaralho();
    total_passados += test_DestroiBaralho();
    total_passados += test_Embaralha();
    total_passados += test_PegaCarta();
    total_passados += test_ValoresCartas();
    total_passados += test_IntegracaoCompleta();
    
    printf("\n RESULTADO FINAL DOS TESTES\n");
    printf("Testes passados: %d/%d\n", total_passados, total_testes);
    printf("Taxa de sucesso: %.1f%%\n", (total_passados * 100.0) / total_testes);
    
    if (total_passados == total_testes) {
        printf("TODOS OS TESTES PASSARAM!\n");
        return 0;
    } else {
        printf("ALGUNS TESTES FALHARAM!\n");
        return 1;
    }
}
