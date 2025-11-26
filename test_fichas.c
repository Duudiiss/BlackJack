#include <stdio.h>
#include <stdlib.h>
#include "Fichas.h"
#include "Jogador.h"

int main() {
    Jogador* jogador = NULL;
    int opcao;
    float valor;
    
    printf("=== TESTE SUPER SIMPLES FICHAS ===\n");
    
    while (1) {
        printf("\n1-Criar Carteira \n2-Saldo \n3-Adicionar \n4-Subtrair \n5-Excluir \n6-Sair\n ");
        scanf("%d", &opcao);
        
        if (opcao == 1) {
            if (jogador) {
                printf("Ja existe jogador!\n");
            } else {
                jogador = (Jogador*)malloc(sizeof(Jogador));
                printf("Saldo inicial: ");
                scanf("%f", &valor);
                jogador->carteira = InitWallet(valor);
                printf("Criado: R$%.2f\n", valor);
            }
        }
        else if (opcao == 2) {
            if (!jogador) printf("Crie jogador!\n");
            else printf("\nSaldo: R$%.2f\n", GetBalance(jogador));
        }
        else if (opcao == 3) {
            if (!jogador) printf("Crie jogador!\n");
            else {
                printf("Valor+: ");
                scanf("%f", &valor);
                if (somaCarteira(jogador, valor) == 0)
                    printf("OK! Saldo: R$%.2f\n", GetBalance(jogador));
                else
                    printf("Erro!\n");
            }
        }
        else if (opcao == 4) {
            if (!jogador) printf("Crie jogador!\n");
            else {
                printf("Valor-: ");
                scanf("%f", &valor);
                if (descontaCarteira(jogador, valor) == 0)
                    printf("OK! Saldo: R$%.2f\n", GetBalance(jogador));
                else
                    printf("Erro! Saldo insuficiente\n");
            }
        }
        else if (opcao == 5) {
            if (!jogador) printf("Nenhum jogador!\n");
            else {
                ExcluiCarteira(jogador);
                free(jogador);
                jogador = NULL;
                printf("Excluido!\n");
            }
        }
        else if (opcao == 6) {
            if (jogador) {
                ExcluiCarteira(jogador);
                free(jogador);
            }
            break;
        }
        else {
            printf("Opcao invalida!\n");
        }
    }
    
    return 0;
}