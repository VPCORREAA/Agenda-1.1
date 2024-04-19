#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTATOS 255
#define TAM_NOME 50
#define TAM_TELEFONE 15
#define TAM_EMAIL 50

// Estrutura para o contato
typedef struct {
    char nome[TAM_NOME];
    char telefone[TAM_TELEFONE];
    char email[TAM_EMAIL];
} Contato;

// Função para adicionar contato
void adicionar_contato(Contato agenda[], int *num_contatos) {
    if (*num_contatos < MAX_CONTATOS) {
        printf("Digite o nome do contato: ");
        scanf(" %[^\n]", agenda[*num_contatos].nome);
        printf("Digite o telefone do contato: ");
        scanf(" %[^\n]", agenda[*num_contatos].telefone);
        printf("Digite o email do contato: ");
        scanf(" %[^\n]", agenda[*num_contatos].email);
        (*num_contatos)++;
        printf("Contato adicionado com sucesso!\n");
    } else {
        printf("Limite de contatos atingido.\n");
    }
}

// Função para listar contatos
void listar_contatos(Contato agenda[], int num_contatos) {
    printf("Lista de Contatos:\n");
    for (int i = 0; i < num_contatos; i++) {
        printf("Nome: %s\n", agenda[i].nome);
        printf("Telefone: %s\n", agenda[i].telefone);
        printf("Email: %s\n", agenda[i].email);
        printf("-------------\n");
    }
}

// Função para deletar contato
void deletar_contato(Contato agenda[], int *num_contatos, char *telefone) {
    int encontrado = 0;
    for (int i = 0; i < *num_contatos; i++) {
        if (strcmp(agenda[i].telefone, telefone) == 0) {
            encontrado = 1;
            for (int j = i; j < *num_contatos - 1; j++) {
                strcpy(agenda[j].nome, agenda[j + 1].nome);
                strcpy(agenda[j].telefone, agenda[j + 1].telefone);
                strcpy(agenda[j].email, agenda[j + 1].email);
            }
            (*num_contatos)--;
            printf("Contato deletado com sucesso!\n");
            break;
        }
    }
    if (!encontrado) {
        printf("Contato não encontrado.\n");
    }
}

// Função para salvar agenda em arquivo binário
void salvar_agenda(Contato agenda[], int num_contatos) {
    FILE *arquivo = fopen("agenda.bin", "wb");
    if (arquivo) {
        fwrite(agenda, sizeof(Contato), num_contatos, arquivo);
        fclose(arquivo);
        printf("Agenda salva com sucesso!\n");
    } else {
        printf("Erro ao abrir arquivo.\n");
    }
}

// Função para carregar agenda do arquivo binário
void carregar_agenda(Contato agenda[], int *num_contatos) {
    FILE *arquivo = fopen("agenda.bin", "rb");
    if (arquivo) {
        *num_contatos = fread(agenda, sizeof(Contato), MAX_CONTATOS, arquivo);
        fclose(arquivo);
        printf("Agenda carregada com sucesso!\n");
    } else {
        printf("Arquivo não encontrado.\n");
    }
}

int main() {
    Contato agenda[MAX_CONTATOS];
    int num_contatos = 0;
    char telefone[TAM_TELEFONE];
    int opcao;

    while (1) {
        printf("\nAgenda Telefônica\n");
        printf("1. Adicionar Contato\n");
        printf("2. Listar Contatos\n");
        printf("3. Deletar Contato\n");
        printf("4. Salvar Agenda\n");
        printf("5. Carregar Agenda\n");
        printf("6. Sair\n");

        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionar_contato(agenda, &num_contatos);
                break;
            case 2:
                listar_contatos(agenda, num_contatos);
                break;
            case 3:
                printf("Digite o telefone do contato a ser deletado: ");
                scanf(" %[^\n]", telefone);
                deletar_contato(agenda, &num_contatos, telefone);
                break;
            case 4:
                salvar_agenda(agenda, num_contatos);
                break;
            case 5:
                carregar_agenda(agenda, &num_contatos);
                break;
            case 6:
                printf("Saindo...\n");
                return 0;
            default:
                printf("Opção inválida!\n");
                break;
        }
    }

    return 0;
}
