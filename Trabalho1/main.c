#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USUARIOS 100 // Defina o número máximo de usuários
#define MAX_MEDICAMENTOS 100 // Defina o número máximo de medicamentos por usuário

//  armazenar informações do medicamento
typedef struct {
    char nome[20];
    char horario[20];
    int quantidade;
    int duracao;
} Medicamento;

//  armazenar informações do usuário
typedef struct {
    char nome[20];
    char senha[20];
    int idade;
    Medicamento medicamentos[MAX_MEDICAMENTOS];
    int numMedicamentos;
} Usuario;

void limparTela() {
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // Linux e MacOS
    #endif
}

int main() {
    Usuario usuarios[MAX_USUARIOS]; // Array para armazenar os usuários
    int numUsuarios = 0; // Contador de usuários cadastrados
    char opcao;
    int logado = -1; // Índice do usuário logado (-1 indica nenhum usuário logado)
    char nome[20];
    char senha[20];

    do {
        if (logado != -1) {
            printf("Voce esta logado com %s\n", usuarios[logado].nome);
            // Mostrar medicamentos do usuário logado
            printf("Medicamentos cadastrados:\n");
            for (int i = 0; i < usuarios[logado].numMedicamentos; i++) {
                printf("Nome: %s, Horario: %s, Quantidade: %d, Duracao: %d dias\n",
                       usuarios[logado].medicamentos[i].nome,
                       usuarios[logado].medicamentos[i].horario,
                       usuarios[logado].medicamentos[i].quantidade,
                       usuarios[logado].medicamentos[i].duracao);
            }//fim do for
        }//fim do if

        printf("\nMenu:\n");
        printf("a) Login\n");
        printf("b) Cadastro usuario\n");
        printf("c) Cadastro medicamento\n");
        printf("d) Sair\n");
        printf("Opcao: ");
        scanf(" %c", &opcao);

        limparTela(); // Limpar a tela antes de mostrar o menu novamente

        switch (opcao) {
            case 'a': {
                printf("########## Login ##########\n");
                printf("Nome: ");
                scanf(" %s", nome);
                printf("Senha: ");
                scanf(" %s", senha);

                int i;
                for (int i = 0; i < numUsuarios; i++) {
                    if (strcmp(nome, usuarios[i].nome) == 0 && strcmp(senha, usuarios[i].senha) == 0) {
                        printf("Login realizado com sucesso.\n");
                        logado = i; // Definir o índice do usuário logado
                        break;
                    }//fim do for
                }//fim do if
                if (logado == -1) {
                    printf("Nome de usuario ou senha incorreto.\n");
                }
                limparTela();
                break;
            }
            case 'b': {
                if (numUsuarios < MAX_USUARIOS) {
                    printf("Cadastro de usuario:\n");
                    printf("Nome: ");
                    scanf(" %s", usuarios[numUsuarios].nome);
                    printf("Senha: ");
                    scanf(" %s", usuarios[numUsuarios].senha);
                    printf("Idade:");
                    scanf(" %d", &usuarios[numUsuarios].idade);
                    usuarios[numUsuarios].numMedicamentos = 0; // Inicializar o contador de medicamentos
                    printf("Usuario cadastrado com sucesso.\n");
                    numUsuarios++;
                } else {
                    printf("Limite de usuarios atingido.\n");
                }
                limparTela();
                break;
            }//fim do case
            case 'c':{
                if (logado != -1) {
                    if (usuarios[logado].numMedicamentos < MAX_MEDICAMENTOS) {
                        printf("Cadastro de medicamento:\n");
                        Medicamento *med = &usuarios[logado].medicamentos[usuarios[logado].numMedicamentos];
                        printf("Nome do medicamento: ");
                        scanf(" %s", med->nome);
                        printf("Horario de ingestao (formato HH:MM): ");
                        scanf(" %s", med->horario);
                        printf("Quantidade por dia: ");
                        scanf(" %d", &med->quantidade);
                        printf("Duracao do tratamento (em dias): ");
                        scanf(" %d", &med->duracao);
                        printf("Medicamento cadastrado com sucesso.\n");
                        usuarios[logado].numMedicamentos++;
                    } else {
                        printf("Limite de medicamentos atingido.\n");
                    }
                } else {
                    printf("Nenhum usuario logado. Faca o login primeiro.\n");
                }
                limparTela();
                break;
            }//fim do case
            case 'd':
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                limparTela();
        }//fim do switch

    } while (opcao != 'd');

    return 0;
}//fim do codigo