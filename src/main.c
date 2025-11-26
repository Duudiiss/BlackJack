#include <stdio.h>
#include "Partida.h"

int main(void)
{
    int saldo_inicial = 100;  // por exemplo

    printf("=== BLACKJACK ===\n");
    printf("Saldo inicial: %d\n", saldo_inicial);

    Partida* p = PartidaCria(saldo_inicial);
    if (!p) {
        printf("Erro ao criar partida.\n");
        return 1;
    }

    PartidaExecuta(p);
    PartidaDestroi(p);

    printf("\nObrigado por jogar!\n");
    return 0;
}
