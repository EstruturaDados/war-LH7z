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

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// --- Constantes Globais ---
    typedef struct {
        char nome[30];
        char CordoExercito[10];
        int NumerodeTropas; /* data */
    }territorio;
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
territorio* inicializarTerritorios(int *numTerritorios);
void exibirMapa(const territorio *territorios, int numTerritorios);
void liberarMemoria(territorio *territorios);
void atacar(territorio* atacante, territorio* defensor);
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    srand(time(NULL));

    
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.
    int numTerritorios;
    territorio *territorios = inicializarTerritorios(&numTerritorios);

        if (territorios == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }   

    int opcao;
    do {
        printf("\n=== Menu ===\n");
        printf("1 - Exibir mapa\n");
        printf("2 - Atacar\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1:
                exibirMapa(territorios, numTerritorios);
                break;
            case 2:
                exibirMapa(territorios, numTerritorios);
                int atk, def;
                printf("Escolha o numero do territorio atacante: ");
                scanf("%d", &atk);
                getchar();
                printf("Escolha o numero do territorio defensor: ");
                scanf("%d", &def);
                getchar();

                // validação de índices
                if (atk < 1 || atk > numTerritorios || def < 1 || def > numTerritorios) {
                    printf("Escolha invalida!\n");
                } else if (atk == def) {
                    printf("Atacante e defensor nao podem ser o mesmo territorio!\n");
                } else {
                    atacar(&territorios[atk - 1], &territorios[def - 1]);
                }
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    liberarMemoria(territorios);    
    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.
territorio* inicializarTerritorios(int *numTerritorios) {
    printf("Digite o numero de Territorios: ");
    scanf("%d", numTerritorios);
    getchar(); // limpa buffer

    // aloca dinamicamente memória para os territórios
    territorio *territorios = calloc(*numTerritorios, sizeof(territorio));

    if (territorios == NULL) {
        return NULL;
    }
    for (int i = 0; i < *numTerritorios; i++) {
        printf("--------------------------\n");
        printf("Preencha os dados iniciais do Territorio %d.\n", i + 1);

        printf("Nome: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = 0; // remove \n

        printf("Cor do Exercito: ");
        fgets(territorios[i].CordoExercito, sizeof(territorios[i].CordoExercito), stdin);
        territorios[i].CordoExercito[strcspn(territorios[i].CordoExercito, "\n")] = 0;

        printf("Numero de Tropas: ");
        scanf("%d", &territorios[i].NumerodeTropas);
        getchar(); // limpa buffer
    }

    return territorios;
}
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

void liberarMemoria(territorio *territorios) {
    free(territorios);
}
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

void exibirMapa(const territorio *territorios, int numTerritorios) {
    printf("\n-----------Mapa atual----------\n");
    for (int i = 0; i < numTerritorios; i++) {
        printf("Territorio %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do territorio: %s\n", territorios[i].CordoExercito);
        printf("Numero de tropas: %d\n", territorios[i].NumerodeTropas);
        printf("---------------------------\n");
    }
}
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
void atacar(territorio* atacante, territorio* defensor) {
    if (atacante->NumerodeTropas < 2) {
        printf("\n%s nao possui tropas suficientes para atacar.\n", atacante->nome);
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
            defensor->NumerodeTropas = 1;
            atacante->NumerodeTropas--;
            snprintf(defensor->CordoExercito, sizeof(defensor->CordoExercito), "%s", atacante->CordoExercito);
        }
    } else {
        atacante->NumerodeTropas--;
        printf("%s perde 1 tropa!\n", atacante->nome);
    }

    printf("--- Resultado ---\n");
    printf("%s: %d tropas\n", atacante->nome, atacante->NumerodeTropas);
    printf("%s: %d tropas\n", defensor->nome, defensor->NumerodeTropas);
}
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
