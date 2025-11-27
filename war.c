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

/*
    Estrutura de dados para armazenar informações de um território.
    Agora usada com ponteiros em alocação dinâmica.
*/
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};


// ========================= DECLARAÇÃO DAS FUNÇÕES =========================

void cadastrarTerritorios(struct Territorio* mapa, int quantidade);
void exibirTerritorios(struct Territorio* mapa, int quantidade);
void atacar(struct Territorio* atacante, struct Territorio* defensor);
void liberarMemoria(struct Territorio* mapa);


// =============================== FUNÇÃO MAIN ===============================

int main() {

    srand(time(NULL)); // garante números aleatórios diferentes a cada execução

    int quantidade;
    struct Territorio* mapa = NULL;

    printf("\n===== WAR - NIVEL AVENTUREIRO =====\n\n");

    printf("Digite a quantidade de territorios que deseja cadastrar: ");
    scanf("%d", &quantidade);

    // Alocação dinâmica com calloc
    mapa = (struct Territorio*) calloc(quantidade, sizeof(struct Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    // Cadastro dos territórios
    cadastrarTerritorios(mapa, quantidade);

    // Exibição inicial
    printf("\n===== TERRITORIOS CADASTRADOS =====\n");
    exibirTerritorios(mapa, quantidade);

    // --------- SIMULAÇÃO DE ATAQUE ------------
    int atacanteID, defensorID;

    printf("\n===== SIMULACAO DE ATAQUE =====\n");

    printf("Escolha o ID do territorio ATACANTE (0 a %d): ", quantidade - 1);
    scanf("%d", &atacanteID);

    printf("Escolha o ID do territorio DEFENSOR (0 a %d): ", quantidade - 1);
    scanf("%d", &defensorID);

    // Validação
    if (atacanteID < 0 || atacanteID >= quantidade ||
        defensorID < 0 || defensorID >= quantidade) {

        printf("\nIDs invalidos! Encerrando ataque.\n");
    }
    else if (strcmp(mapa[atacanteID].cor, mapa[defensorID].cor) == 0) {

        printf("\nERRO: Voce nao pode atacar um territorio da mesma cor!\n");

    } else {

        atacar(&mapa[atacanteID], &mapa[defensorID]);
    }

    // Exibição após o ataque
    printf("\n===== TERRITORIOS APOS O ATAQUE =====\n");
    exibirTerritorios(mapa, quantidade);

    // Liberar memória
    liberarMemoria(mapa);

    return 0;
}



// ===================== FUNÇÕES DO SISTEMA ==========================


/*
    Função para cadastrar todos os territórios no vetor dinamicamente alocado.
*/
void cadastrarTerritorios(struct Territorio* mapa, int quantidade) {

    for (int i = 0; i < quantidade; i++) {

        printf("\n--- Cadastro do Territorio %d ---\n", i);

        printf("Nome: ");
        scanf("%s", mapa[i].nome);

        printf("Cor do exercito: ");
        scanf("%s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}


/*
    Função para exibir todos os territórios
*/
void exibirTerritorios(struct Territorio* mapa, int quantidade) {

    for (int i = 0; i < quantidade; i++) {

        printf("\nID %d\n", i);
        printf("Territorio: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
        printf("-----------------------------\n");
    }
}


/*
    Função de ataque entre dois territórios usando ponteiros.
    Cada lado rola um dado (1 a 6).
    Se o atacante ganhar, o defensor muda de cor e perde metade das tropas.
    Se o atacante perder, ele perde 1 tropa.
*/
void atacar(struct Territorio* atacante, struct Territorio* defensor) {

    printf("\n===== ATAQUE INICIADO =====\n");

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("Dado do atacante (%s): %d\n", atacante->nome, dadoAtacante);
    printf("Dado do defensor  (%s): %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {

        printf("\n>>> O atacante venceu a batalha!\n");
        
        // defensor muda de cor
        strcpy(defensor->cor, atacante->cor);

        // defensor perde metade das tropas
        defensor->tropas /= 2;

        printf("O defensor agora pertence ao exercito %s!\n", atacante->cor);

    } else {

        printf("\n>>> O defensor resistiu ao ataque!\n");

        // atacante perde 1 tropa
        if (atacante->tropas > 0)
            atacante->tropas--;

        printf("%s perdeu 1 tropa!\n", atacante->nome);
    }
}


/*
    Função para liberar memória alocada dinamicamente
*/
void liberarMemoria(struct Territorio* mapa) {
    free(mapa);
}
