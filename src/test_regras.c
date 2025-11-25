#include <stdio.h>
#include <assert.h>
#include "regras.h"
#include "jogador.h"
#include "fichas.h"

/* =====================================================
   Função auxiliar para criar jogador com carteira
   ===================================================== */
Jogador* NovoJogadorComSaldo(float saldo) {
    Jogador *j = InitJogador("Teste");
    j->carteira = InitWallet(saldo);
    return j;
}

/* =====================================================
   Função auxiliar para adicionar carta manualmente
   ===================================================== */
void AddCarta(Jogador *j, int numero) {
    // Mock simples: só guarda o número em j->maoNumeros[].
    j->mao[j->totalCartas].numero = numero;
    j->mao[j->totalCartas].valor = (numero == 1) ? 11 : (numero > 10 ? 10 : numero);
    j->totalCartas++;
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
    printf("Esperado: 16 (Ás valendo 1) | Obtido: %d\n", ValorDaMao(j));

    ExcluiJogador(j);
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
    printf("Esperado: 1 (estourou) | Obtido: %d\n", Estourou(j));

    ExcluiJogador(j);
}

/* ============================
   Teste: Blackjack natural
   ============================ */
void Test_TemBlackjack() {
    printf("\n=== Teste TemBlackjack ===\n");

    Jogador *j = NovoJogadorComSaldo(100);

    AddCarta(j, 1);
    AddCarta(j, 13); // rei (valor 10)

    printf("Esperado: 1 | Obtido: %d\n", TemBlackjack(j));

    ExcluiJogador(j);
}

/* ============================
   Teste: Pagamentos
   ============================ */
void Test_Pagamentos() {
    printf("\n=== Teste Pagamentos ===\n");

    Jogador *j = NovoJogadorComSaldo(100);

    AplicarVitoria(j, 50);
    printf("Vitória: esperado 150 | obtido %.1f\n", j->carteira->saldo);

    AplicarDerrota(j, 30);
    printf("Derrota: esperado 120 | obtido %.1f\n", j->carteira->saldo);

    AplicarEmpate(j, 20);
    printf("Empate: esperado 140 | obtido %.1f\n", j->carteira->saldo);

    AplicarBlackjack(j, 20); // paga 30
    printf("Blackjack: esperado 170 | obtido %.1f\n", j->carteira->saldo);

    ExcluiJogador(j);
}

/* ============================
   Teste: ResolverRodada
   ============================ */
void Test_ResolverRodada() {
    printf("\n=== Teste ResolverRodada ===\n");

    Jogador *player = NovoJogadorComSaldo(100);
    Jogador *dealer = NovoJogadorComSaldo(100);

    // Jogador: 10 + 10 = 20
    AddCarta(player, 10);
    AddCarta(player, 10);

    // Dealer: 10 + 6 = 16
    AddCarta(dealer, 10);
    AddCarta(dealer, 6);

    ResolverRodada(player, dealer, 20);

    printf("Jogador venceu? Esperado saldo 120 | obtido %.1f\n", player->carteira->saldo);

    ExcluiJogador(player);
    ExcluiJogador(dealer);
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
