#include <stdlib.h>
#include "Fichas.h"

struct Fichas {
    int saldo;
    int aposta_atual;
};

Fichas* FichasCria(int saldo_inicial)
{
    if (saldo_inicial < 0) saldo_inicial = 0;

    Fichas* f = (Fichas*)malloc(sizeof(Fichas));
    if (!f) return NULL;

    f->saldo = saldo_inicial;
    f->aposta_atual = 0;
    return f;
}

int FichasDestroi(Fichas* f)
{
    if (!f) return -1;
    free(f);
    return 0;
}

int FichasGetSaldo(const Fichas* f)
{
    if (!f) return -1;
    return f->saldo;
}

int FichasGetAposta(const Fichas* f)
{
    if (!f) return -1;
    return f->aposta_atual;
}

int FichasPodeApostar(const Fichas* f, int valor)
{
    if (!f) return 0;
    if (valor <= 0) return 0;
    return (f->saldo >= valor);
}

int FichasRealizaAposta(Fichas* f, int valor)
{
    if (!f) return -1;
    if (valor <= 0) return -1;
    if (f->saldo < valor) return -1;

    f->saldo -= valor;
    f->aposta_atual += valor;
    return 0;
}

int FichasResetaAposta(Fichas* f)
{
    if (!f) return -1;
    f->aposta_atual = 0;
    return 0;
}

int FichasAplicarResultado(Fichas* f, ResultadoMao resultado, int blackjack)
{
    if (!f) return -1;

    int aposta = f->aposta_atual;
    if (aposta <= 0) return 0;  // nada a fazer

    if (resultado == RESULTADO_JOGADOR_PERDEU) {
        /* Perdeu a aposta: aposta já foi debitada do saldo,
           só zerar aposta_atual. */
        f->aposta_atual = 0;
        return 0;
    }

    if (resultado == RESULTADO_EMPATE) {
        /* Empate: jogador recebe a aposta de volta (sem lucro) */
        f->saldo += aposta;
        f->aposta_atual = 0;
        return 0;
    }

    /* Vitória */
    if (resultado == RESULTADO_JOGADOR_GANHOU) {
        if (blackjack) {
            /* Pagamento 3:2 típico — aprox com inteiros (5/2) */
            int ganho = (aposta * 5) / 2;  // devolução + lucro
            f->saldo += ganho;
        } else {
            /* Vitória normal: 1:1 (devolve aposta + mesmo valor de lucro) */
            int ganho = aposta * 2;
            f->saldo += ganho;
        }
        f->aposta_atual = 0;
        return 0;
    }

    return -1;
}
