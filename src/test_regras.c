#include <stdio.h>
#include <assert.h>

#include "regras.h"
#include "jogador.h"
#include "fichas.h"
<<<<<<< Updated upstream
#include "baralho.h"
=======
>>>>>>> Stashed changes

/* =====================================================
   Função auxiliar para criar jogador com carteira
   ===================================================== */
Jogador* NovoJogadorComSaldo(float saldo) {
    Jogador *j = CriaJogador("Teste");
<<<<<<< Updated upstream
    InitWallet(j, saldo);
=======
    j->carteira = InitWallet(saldo);
>>>>>>> Stashed changes
    return j;
}

/* =====================================================
   Função auxiliar para adicionar carta manualmente
   ===================================================== */
void AddCarta(Jogador *j, int numero) {
    // Cria uma carta falsa para teste
    Carta *c = (Carta*)malloc(sizeof(Carta));
    c->numero = numero;
    c->naipe  = 'X';
    c->valor  = (numero == 1) ? 11 : (numero > 10 ? 10 : numero);

    JogadorRecebeCarta(j, c);
}

/* ============================
   Teste: ValorDaMao
   ============================ */
void Test_ValorDaMao() {
    printf("\n=== Teste ValorDaMao ===\n");

    Jogador *j = NovoJogadorComSaldo(100);

    AddCarta(j, 10);
    AddCarta(j, 5);
    printf("Esperado: 15 | Obtido: %d\n", ValorDaMao(j));

    AddCarta(j, 1); // ás
    printf("Esperado: 16 | Obtido: %d\n", ValorDaMao(j));

    DestroiJogador(j);
}

/* ============================
   Teste: Estourou
   ============================ */
void Test_Estourou() {
    printf("\n=== Teste Estourou ===\n");

    Jogador *j = NovoJogadorComSaldo(100);

    AddCarta(j, 10);
    AddCarta(j, 10);
    AddCarta(j, 5);

    printf("Valor da mão: %d\n", ValorDaMao(j));
    printf("Esperado: 1 | Obtido: %d\n", Estourou(j));

    DestroiJogador(j);
}

/* ============================
   Teste: Blackjack natural
   ============================ */
void Test_TemBlackjack() {
    printf("\n=== Teste TemBlackjack ===\n");

    Jogador *j = NovoJogadorComSaldo(100);

    AddCarta(j, 1);
    AddCarta(j, 13); // rei (10)

    printf("Esperado: 1 | Obtido: %d\n", TemBlackjack(j));

    DestroiJogador(j);
}

/* ============================
   Teste: Pagamentos
   ============================ */
void Test_Pagamentos() {
    printf("\n=== Teste Pagamentos ===\n");

    Jogador *j = NovoJogadorComSaldo(100);

    AplicarVitoria(j, 50);
    printf("Vitória: esperado 150 | obtido %.1f\n", GetBalance(j));

    AplicarDerrota(j, 30);
    printf("Derrota: esperado 120 | obtido %.1f\n", GetBalance(j));

    AplicarEmpate(j, 20);
    printf("Empate: esperado 140 | obtido %.1f\n", GetBalance(j));

    AplicarBlackjack(j, 20); // paga 30
    printf("Blackjack: esperado 170 | obtido %.1f\n", GetBalance(j));

    DestroiJogador(j);
}

/* ============================
   Teste: ResolverRodada
   ============================ */
void Test_ResolverRodada() {
    printf("\n=== Teste ResolverRodada ===\n");

    Jogador *player = NovoJogadorComSaldo(100);
    Jogador *dealer = NovoJogadorComSaldo(100);

    AddCarta(player, 10);
    AddCarta(player, 10);

    AddCarta(dealer, 10);
    AddCarta(dealer, 6);

    ResolverRodada(player, dealer, 20);

    printf("Jogador venceu? Esperado saldo 120 | obtido %.1f\n",
           GetBalance(player));

    DestroiJogador(player);
    DestroiJogador(dealer);
}

/* =====================================================
   MAIN
   ===================================================== */
int main() {
    printf("====== TESTES DO MÓDULO REGRAS ======\n");

    Test_ValorDaMao();
    Test_Estourou();
    Test_TemBlackjack();
    Test_Pagamentos();
    Test_ResolverRodada();

    printf("\nTodos os testes foram executados.\n");
    return 0;
}
