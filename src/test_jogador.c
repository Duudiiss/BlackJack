#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> 

#include "Jogador.h"
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

/* =========================================================
 *  TESTES DE CRIAÇÃO / DESTRUIÇÃO
 * ========================================================= */

int test_CriaJogador() {
    printf("\n=== TESTE CriaJogador ===\n");

    // Nome NULL
    Jogador* j_null = CriaJogador(NULL);
    TEST_ASSERT(j_null == NULL, "CriaJogador(NULL) deve retornar NULL");

    // Nome vazio
    Jogador* j_vazio = CriaJogador("");
    TEST_ASSERT(j_vazio == NULL, "CriaJogador(\"\") deve retornar NULL");

    // Nome válido
    const char* nome = "Alice";
    Jogador* j = CriaJogador(nome);
    TEST_ASSERT(j != NULL, "CriaJogador(nome valido) nao deve retornar NULL");

    char* nome2 = GetNomeJogador(j);
    TEST_ASSERT(nome2 != NULL, "GetNomeJogador deve retornar string nao NULL");
    TEST_ASSERT(strcmp(nome2, nome) == 0, "Nome interno deve ser igual ao passado");

    // Ao criar, mao deve estar vazia
    TEST_ASSERT(GetJogadorQuantidadeCartas(j) == 0,
                "Jogador recem criado deve ter 0 cartas");

    int r = DestroiJogador(j);
    (void)r;

    return 1;
}

int test_DestroiJogador() {
    printf("\n=== TESTE DestroiJogador ===\n");

    Jogador* j = CriaJogador("Bob");
    TEST_ASSERT(j != NULL, "Jogador criado com sucesso para teste de destrucao");

    int resultado = DestroiJogador(j);
    TEST_ASSERT(resultado == 0,
                "DestroiJogador(jogador valido) deve retornar 0");

    resultado = DestroiJogador(NULL);
    TEST_ASSERT(resultado == -1,
                "DestroiJogador(NULL) deve retornar -1");

    return 1;
}

/* =========================================================
 *  TESTES DE ACESSO A DADOS BÁSICOS
 * ========================================================= */

int test_GetNomeJogador() {
    printf("\n=== TESTE GetNomeJogador ===\n");

    Jogador* j = CriaJogador("Carlos");
    TEST_ASSERT(j != NULL, "Jogador deve ser criado");

    char* nome = GetNomeJogador(j);
    TEST_ASSERT(nome != NULL, "GetNomeJogador nao deve retornar NULL");
    TEST_ASSERT(strcmp(nome, "Carlos") == 0,
                "GetNomeJogador deve retornar o nome correto");

    DestroiJogador(j);
    return 1;
}

int test_GetJogadorQuantidadeCartas_e_GetJogadorCarta() {
    printf("\n=== TESTE GetJogadorQuantidadeCartas / GetJogadorCarta ===\n");

    // Jogador NULL
    TEST_ASSERT(GetJogadorQuantidadeCartas(NULL) == -1,
                "GetJogadorQuantidadeCartas(NULL) deve retornar -1");

    Jogador* j = CriaJogador("Daniela");
    TEST_ASSERT(j != NULL, "Jogador deve ser criado");

    // Mao inicialmente vazia
    TEST_ASSERT(GetJogadorQuantidadeCartas(j) == 0,
                "Mao deve iniciar com 0 cartas");

    // GetJogadorCarta com jogador NULL
    TEST_ASSERT(GetJogadorCarta(NULL, 0) == NULL,
                "GetJogadorCarta(NULL, ...) deve retornar NULL");

    // Indice negativo
    TEST_ASSERT(GetJogadorCarta(j, -1) == NULL,
                "GetJogadorCarta(indice negativo) deve retornar NULL");

    // Indice grande demais
    TEST_ASSERT(GetJogadorCarta(j, MAX_MAO_CARTAS) == NULL,
                "GetJogadorCarta(indice >= MAX_MAO_CARTAS) deve retornar NULL");

    // Indice maior que quantidade de cartas (ainda 0)
    TEST_ASSERT(GetJogadorCarta(j, 0) == NULL,
                "GetJogadorCarta(indice > qtdCartas) deve retornar NULL quando mao vazia");

    DestroiJogador(j);
    return 1;
}

/* =========================================================
 *  TESTES DE RECEBIMENTO / LIMPEZA DE CARTAS
 * ========================================================= */

// Funcao auxiliar: cria um ponteiro fake para Carta (nao deve ser free)
static Carta* fake_carta_ptr(int id) {
    return (Carta*)(uintptr_t)(id + 1);
}

int test_JogadorRecebeCarta_e_GetQuantidade() {
    printf("\n=== TESTE JogadorRecebeCarta / GetJogadorQuantidadeCartas / GetJogadorCarta ===\n");

    // Jogador NULL
    Carta* c_fake = fake_carta_ptr(1);
    TEST_ASSERT(JogadorRecebeCarta(NULL, c_fake) == 3,
                "JogadorRecebeCarta(NULL, carta) deve retornar 3");

    // Carta NULL
    Jogador* j = CriaJogador("Eva");
    TEST_ASSERT(j != NULL, "Jogador deve ser criado");

    TEST_ASSERT(JogadorRecebeCarta(j, NULL) == 2,
                "JogadorRecebeCarta(jogador, NULL) deve retornar 2");

    // Situação normal: receber cartas até encher a mão
    int i;
    for (i = 0; i < MAX_MAO_CARTAS; i++) {
        int r = JogadorRecebeCarta(j, fake_carta_ptr(i));
        TEST_ASSERT(r == 0, "JogadorRecebeCarta deve retornar 0 enquanto houver espaco");
        TEST_ASSERT(GetJogadorQuantidadeCartas(j) == i + 1,
                    "Quantidade de cartas deve aumentar a cada recebimento");
    }

    // Tentar receber mais uma carta além do limite
    int r = JogadorRecebeCarta(j, fake_carta_ptr(999));
    TEST_ASSERT(r == 1,
                "JogadorRecebeCarta deve retornar 1 quando mao estiver cheia");
    TEST_ASSERT(GetJogadorQuantidadeCartas(j) == MAX_MAO_CARTAS,
                "Quantidade de cartas nao deve ultrapassar MAX_MAO_CARTAS");

    // Verificar que GetJogadorCarta retorna exatamente os ponteiros inseridos
    for (i = 0; i < MAX_MAO_CARTAS; i++) {
        Carta* c = GetJogadorCarta(j, i);
        TEST_ASSERT(c == fake_carta_ptr(i),
                    "GetJogadorCarta deve devolver a mesma carta inserida no indice correto");
    }

    // Não chamamos DestroiJogador aqui (leakzinho planejado)
    return 1;
}

int test_JogadorLimpaMao() {
    printf("\n=== TESTE JogadorLimpaMao ===\n");

    // Jogador NULL
    TEST_ASSERT(JogadorLimpaMao(NULL) == 1,
                "JogadorLimpaMao(NULL) deve retornar 1");

    // Jogador sem cartas
    Jogador* j = CriaJogador("Fernanda");
    TEST_ASSERT(j != NULL, "Jogador deve ser criado");

    TEST_ASSERT(JogadorLimpaMao(j) == 0,
                "JogadorLimpaMao em mao vazia deve retornar 0");
    TEST_ASSERT(GetJogadorQuantidadeCartas(j) == 0,
                "Mao deve continuar com 0 cartas");

    DestroiJogador(j);
    return 1;
}

/* =========================================================
 *  TESTES DE AÇÕES DO JOGADOR (Hit / Stand / Double)
 * ========================================================= */

int test_JogadorExecutaHit() {
    printf("\n=== TESTE JogadorExecutaHit ===\n");

    // Jogador NULL
    TEST_ASSERT(JogadorExecutaHit(NULL) == 3,
                "JogadorExecutaHit(NULL) deve retornar 3");

    Jogador* j = CriaJogador("Gustavo");
    TEST_ASSERT(j != NULL, "Jogador deve ser criado");

    TEST_ASSERT(JogadorExecutaHit(j) == 0,
                "JogadorExecutaHit deve retornar 0 quando jogador puder receber carta");

    JogadorExecutaStand(j);
    TEST_ASSERT(JogadorExecutaHit(j) == 3,
                "JogadorExecutaHit deve retornar 3 se jogador ja fez stand");

    DestroiJogador(j);
    return 1;
}

int test_JogadorExecutaStand() {
    printf("\n=== TESTE JogadorExecutaStand ===\n");

    TEST_ASSERT(JogadorExecutaStand(NULL) == 1,
                "JogadorExecutaStand(NULL) deve retornar 1");

    Jogador* j = CriaJogador("Helena");
    TEST_ASSERT(j != NULL, "Jogador deve ser criado");

    TEST_ASSERT(JogadorExecutaStand(j) == 0,
                "Primeiro stand deve retornar 0");

    TEST_ASSERT(JogadorExecutaStand(j) == 1,
                "Stand em jogador que ja fez stand deve retornar 1");

    DestroiJogador(j);
    return 1;
}

int test_JogadorExecutaDouble() {
    printf("\n=== TESTE JogadorExecutaDouble ===\n");

    TEST_ASSERT(JogadorExecutaDouble(NULL) == 3,
                "JogadorExecutaDouble(NULL) deve retornar 3");

    Jogador* j = CriaJogador("Igor");
    TEST_ASSERT(j != NULL, "Jogador deve ser criado");

    TEST_ASSERT(JogadorExecutaDouble(j) == 3,
                "Double com qtdCartas != 2 deve retornar 3");

    JogadorRecebeCarta(j, fake_carta_ptr(1));
    TEST_ASSERT(JogadorExecutaDouble(j) == 3,
                "Double com 1 carta deve retornar 3");

    JogadorRecebeCarta(j, fake_carta_ptr(2));

    TEST_ASSERT(JogadorExecutaDouble(j) == 0,
                "Double com 2 cartas, sem stand e sem double, deve retornar 0");

    TEST_ASSERT(JogadorExecutaDouble(j) == 3,
                "Double novamente deve retornar 3 (ja fez double)");

    TEST_ASSERT(JogadorExecutaDouble(j) == 3,
                "Double com fez_stand=1 deve retornar 3");

    return 1;
}

/* =========================================================
 *  TESTES DE FUNÇÕES INTERATIVAS
 * ========================================================= */

int test_JogadorPedeAposta() {
    printf("\n=== TESTE JogadorPedeAposta (parte nao interativa) ===\n");

    TEST_ASSERT(JogadorPedeAposta(NULL) == -1,
                "JogadorPedeAposta(NULL) deve retornar -1");

    return 1;
}

int test_JogadorQuerJogarNovamente() {
    printf("\n=== TESTE JogadorQuerJogarNovamente (parte nao interativa) ===\n");

    TEST_ASSERT(JogadorQuerJogarNovamente(NULL) == -1,
                "JogadorQuerJogarNovamente(NULL) deve retornar -1");

    return 1;
}

int test_JogadorExibeMao_e_JogadorExibeMensagem() {
    printf("\n=== TESTE JogadorExibeMao / JogadorExibeMensagem (nulos) ===\n");

    JogadorExibeMao(NULL);
    JogadorExibeMensagem(NULL, "x");
    JogadorExibeMensagem(NULL, NULL);

    Jogador* j = CriaJogador("Julia");
    TEST_ASSERT(j != NULL, "Jogador deve ser criado");

    JogadorExibeMensagem(j, NULL);
    JogadorExibeMensagem(j, "Teste de mensagem");
    JogadorExibeMao(j);

    DestroiJogador(j);
    return 1;
}

/* =========================================================
 *  MAIN DOS TESTES
 * ========================================================= */

int main() {
    printf("INICIANDO TESTES UNITARIOS - JOGADOR\n");

    int total_passados = 0;
    int total_testes   = 12; // <- corrigi para 12

    total_passados += test_CriaJogador();
    total_passados += test_DestroiJogador();
    total_passados += test_GetNomeJogador();
    total_passados += test_GetJogadorQuantidadeCartas_e_GetJogadorCarta();
    total_passados += test_JogadorRecebeCarta_e_GetQuantidade();
    total_passados += test_JogadorLimpaMao();
    total_passados += test_JogadorExecutaHit();
    total_passados += test_JogadorExecutaStand();
    total_passados += test_JogadorExecutaDouble();
    total_passados += test_JogadorPedeAposta();
    total_passados += test_JogadorQuerJogarNovamente();
    total_passados += test_JogadorExibeMao_e_JogadorExibeMensagem();

    printf("\nRESULTADO FINAL DOS TESTES - JOGADOR\n");
    printf("Testes passados: %d/%d\n", total_passados, total_testes);
    printf("Taxa de sucesso: %.1f%%\n", (total_passados * 100.0) / total_testes);

    if (total_passados == total_testes) {
        printf("TODOS OS TESTES DE JOGADOR PASSARAM!\n");
        return 0;
    } else {
        printf("ALGUNS TESTES DE JOGADOR FALHARAM!\n");
        return 1;
    }
}
