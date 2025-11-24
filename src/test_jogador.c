#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Jogador.h"
#include "Baralho.h"

// Criar carta manualmente para testes
Carta* NovaCarta(int numero, char naipe)
{
    Carta* c = malloc(sizeof(Carta));
    c->Numero = numero;
    c->Naipe = naipe;
    return c;
}

void TesteCriarEDestruir()
{
    printf("\n==== TESTE: Criar e Destruir Jogador ====\n");
    Jogador* j = CriaJogador("Alice");

    if (!j) printf("FALHOU: Jogador não criado.\n");
    else printf("OK: Jogador criado com nome '%s'\n", j->nome);

    if (DestroiJogador(j) == 0)
        printf("OK: Jogador destruído corretamente.\n");
    else
        printf("FALHOU: Erro ao destruir jogador.\n");
}

void TesteReceberCartas()
{
    printf("\n==== TESTE: Receber Cartas ====\n");

    Jogador* j = CriaJogador("Bob");

    Carta* c1 = NovaCarta(10, 'H');
    Carta* c2 = NovaCarta(5, 'P');

    if (JogadorRecebeCarta(j, c1) == 0)
        printf("OK: Primeira carta recebida.\n");
    else
        printf("FALHOU: Erro ao receber 1ª carta.\n");

    if (JogadorRecebeCarta(j, c2) == 0)
        printf("OK: Segunda carta recebida.\n");
    else
        printf("FALHOU: Erro ao receber 2ª carta.\n");

    int qtd = GetJogadorQuantidadeCartas(j);
    if (qtd == 2)
        printf("OK: Quantidade correta de cartas (%d).\n", qtd);
    else
        printf("FALHOU: Quantidade incorreta (%d).\n", qtd);

    DestroiJogador(j);
}

void TesteMaoCheia()
{
    printf("\n==== TESTE: Mão Cheia ====\n");

    Jogador* j = CriaJogador("Carlos");

    for (int i = 0; i < MAX_CARTAS; i++) {
        Carta* c = NovaCarta(i+1, 'O');
        JogadorRecebeCarta(j, c);
    }

    Carta* extra = NovaCarta(7, 'E');
    int r = JogadorRecebeCarta(j, extra);

    if (r != 0)
        printf("OK: Não permitiu carta além de MAX_CARTAS.\n");
    else
        printf("FALHOU: Jogador recebeu carta extra!\n");

    free(extra);
    DestroiJogador(j);
}

void TesteStandDoubleHit()
{
    printf("\n==== TESTE: Hit / Stand / Double ====\n");

    Jogador* j = CriaJogador("Diego");

    // Dá duas cartas
    JogadorRecebeCarta(j, NovaCarta(3, 'C'));
    JogadorRecebeCarta(j, NovaCarta(9, 'P'));

    // Teste HIT
    if (JogadorExecutaHit(j) == 0)
        printf("OK: Hit permitido.\n");
    else
        printf("FALHOU: Hit rejeitado incorretamente.\n");

    // Teste DOUBLE
    j->fez_double = 0;
    j->fez_stand = 0;

    if (JogadorExecutaDouble(j) == 0)
        printf("OK: Double permitido.\n");
    else
        printf("FALHOU: Double recusado incorretamente.\n");

    // Teste STAND
    j->fez_stand = 0;

    if (JogadorExecutaStand(j) == 0)
        printf("OK: Stand permitido.\n");
    else
        printf("FALHOU: Stand recusado.\n");

    DestroiJogador(j);
}

void TesteLimparMao()
{
    printf("\n==== TESTE: Limpar Mão ====\n");

    Jogador* j = CriaJogador("Eva");

    JogadorRecebeCarta(j, NovaCarta(1, 'C'));
    JogadorRecebeCarta(j, NovaCarta(2, 'C'));

    if (JogadorLimpaMao(j) == 0)
        printf("OK: Mão limpa com sucesso.\n");
    else
        printf("FALHOU: Erro ao limpar mão.\n");

    if (GetJogadorQuantidadeCartas(j) == 0)
        printf("OK: Mão está realmente vazia.\n");
    else
        printf("FALHOU: Mão não foi zerada.\n");

    DestroiJogador(j);
}

int main()
{
    printf("\n=====================================\n");
    printf("        TESTES DO MÓDULO JOGADOR\n");
    printf("=====================================\n");

    TesteCriarEDestruir();
    TesteReceberCartas();
    TesteMaoCheia();
    TesteStandDoubleHit();
    TesteLimparMao();

    printf("\n==== FIM DOS TESTES ====\n");

    return 0;
}
