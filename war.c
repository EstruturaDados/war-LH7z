// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Estruturas ---
typedef struct {
    char nome[30];
    char CordoExercito[10];
    int NumerodeTropas;
} territorio;

typedef struct {
    char cor[10];
    char *missao; // ponteiro dinâmico
} Jogador;

// --- Missões ---
char missoes[1][100] = {
    "Destruir o exercito Azul",
    //"Destruir o exercito Vermelho",
    //"Conquistar 1 territorios",
    //"Conquistar 3 territorios",
    //"Conquistar 4 territorios"
};

// --- Protótipos ---
territorio* inicializarTerritorios(int *numTerritorios);
void exibirMapa(const territorio *territorios, int numTerritorios);
void liberarMemoria(territorio *territorios);
void atacar(territorio* atacante, territorio* defensor);
int sortearMissao();
int verificarMissao(char* missao, territorio* mapa, int tamanho, const char* corJogador);

// --- Funções ---
territorio* inicializarTerritorios(int *numTerritorios) {
    printf("Digite o numero de Territorios: ");
    scanf("%d", numTerritorios);
    getchar();

    territorio *territorios = calloc(*numTerritorios, sizeof(territorio));
    if (!territorios) return NULL;

    for (int i = 0; i < *numTerritorios; i++) {
        printf("\nTerritorio %d\n", i + 1);

        printf("Nome: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = 0;

        printf("Cor do Exercito: ");
        fgets(territorios[i].CordoExercito, sizeof(territorios[i].CordoExercito), stdin);
        territorios[i].CordoExercito[strcspn(territorios[i].CordoExercito, "\n")] = 0;

        printf("Numero de Tropas: ");
        scanf("%d", &territorios[i].NumerodeTropas);
        getchar();
    }
    return territorios;
}

void liberarMemoria(territorio *territorios) {
    free(territorios);
}

void exibirMapa(const territorio *territorios, int numTerritorios) {
    printf("\n-----------Mapa Atual----------\n");
    for (int i = 0; i < numTerritorios; i++) {
        printf("Territorio %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].CordoExercito);
        printf("Numero de tropas: %d\n", territorios[i].NumerodeTropas);
        printf("-------------------------------\n");
    }
}

int sortearMissao(const char* corJogador) {
    if (strcmp(corJogador, "Azul") == 0) {
        printf("caiu azul\n");
        return rand() % 1; // Missão de destruir o exército Azul
    } else if (strcmp(corJogador, "Vermelho") == 0) {
        return rand() % 1; // Missão de destruir o exército Vermelho
    }
    return rand() % 1;
}

void atacar(territorio* atacante, territorio* defensor) {
    if (atacante->NumerodeTropas < 2) {
        printf("%s nao possui tropas suficientes para atacar.\n", atacante->nome);
        return;
    }

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n--- Batalha ---\n");
    printf("%s (Atacante) rola: %d\n", atacante->nome, dadoAtacante);
    printf("%s (Defensor) rola: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        defensor->NumerodeTropas--;
        printf("%s perde 1 tropa!\n", defensor->nome);

        if (defensor->NumerodeTropas <= 0) {
            printf("%s conquistou %s!\n", atacante->nome, defensor->nome);
            strcpy(defensor->CordoExercito, atacante->CordoExercito);

            // mover tropas do atacante para o defensor
            int tropasMover = atacante->NumerodeTropas / 2; // metade das tropas
            if (tropasMover < 1) tropasMover = 1;
            defensor->NumerodeTropas = tropasMover;
            atacante->NumerodeTropas -= tropasMover;
        }
    } else {
        atacante->NumerodeTropas--;
        printf("%s perde 1 tropa!\n", atacante->nome);
    }
}

int verificarMissao(char* missao, territorio* mapa, int tamanho, const char* corJogador) {
    int count = 0;

    // MISSÕES DE CONQUISTA
    if (strcmp(missao, "Conquistar 1 territorios") == 0) {
            for (int i = 0; i < tamanho; i++) {
                if (strcmp(mapa[i+1].CordoExercito, corJogador) == 0) {
                    count++;
                }
            }
        if (count >= 1) return 1;
    } else if (strcmp(missao, "Conquistar 3 territorios") == 0) {
        printf("Verificando missao de conquistar 3 territorio...\n");
        for (int i = 0; i < tamanho; i++) {
                if (strcmp(mapa[i+1].CordoExercito, corJogador) == 0) {
                    count++;
                }
        }
        if (count >= 3) return 1;
    } else if (strcmp(missao, "Conquistar 4 territorios") == 0) {
        printf("Verificando missao de conquistar 4 territorio...\n");
        for (int i = 0; i < tamanho; i++) {
                if (strcmp(mapa[i+1].CordoExercito, corJogador) == 0) {
                    count++;
                }
        }
        if (count >= 4) return 1;
    }
    // MISSÕES DE DESTRUIÇÃO
    if (strcmp(missao, "Destruir o exercito Azul") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].CordoExercito, "Azul") == 0) {
                return 0; // ainda existe um territorio azul
            }
        }
        return 1; // nenhum territorio azul encontrado
    } else if (strcmp(missao, "Destruir o exercito Vermelho") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].CordoExercito, "Vermelho") == 0) {
                return 0; // ainda existe um territorio vermelho
            }
        }
        return 1; // nenhum territorio vermelho encontrado
    }
    return 0;
}

// --- MAIN ---
int main() {
    srand(time(NULL));

    int numTerritorios;
    territorio *territorios = inicializarTerritorios(&numTerritorios);
    if (!territorios) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    // CRIAR JOGADOR
    Jogador jogador;
    printf("\nDigite a cor do seu exercito: ");
    fgets(jogador.cor, sizeof(jogador.cor), stdin);
    jogador.cor[strcspn(jogador.cor, "\n")] = 0;

    int idMissao = sortearMissao(jogador.cor);
    jogador.missao = malloc(strlen(missoes[idMissao]) + 1);
    strcpy(jogador.missao, missoes[idMissao]);

    printf("\nSua Missao Secreta: %s\n", jogador.missao);

    int opcao;
    do {
        printf("\n=== Menu ===\n");
        printf("1 - Exibir mapa\n");
        printf("2 - Atacar\n");
        printf("3 - Exibir Missao\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1:
                exibirMapa(territorios, numTerritorios);
                break;
            case 2: {
                exibirMapa(territorios, numTerritorios);
                int atk, def;
                printf("Numero do territorio atacante: ");
                scanf("%d", &atk);
                getchar();
                printf("Numero do territorio defensor: ");
                scanf("%d", &def);
                getchar();

                if (atk < 1 || atk > numTerritorios || def < 1 || def > numTerritorios)
                    printf("Escolha invalida!\n");
                else if (atk == def)
                    printf("Atacante e defensor nao podem ser iguais!\n");
                else
                    atacar(&territorios[atk - 1], &territorios[def - 1]);
                break;
            }
            case 3:
                printf("\nSua Missao Secreta: %s\n", jogador.missao);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

        if (verificarMissao(jogador.missao, territorios, numTerritorios, jogador.cor)) {
            printf("\n🎉 Parabens! Voce cumpriu sua missao e venceu o jogo!\n");
            break;
        }

    } while (opcao != 0);

    free(jogador.missao);
    liberarMemoria(territorios);

    return 0;
}