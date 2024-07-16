#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

void criar_diretorio(const char *nome) {
    if (mkdir(nome, 0755) == -1) {
        if (errno == EEXIST) {
            printf("Erro: O diretório '%s' já existe.\n", nome);
        } else {
            perror("Erro ao criar diretório");
        }
    } else {
        printf("Diretório '%s' criado com sucesso.\n", nome);
    }
}

void criar_diretorio_com_caminho(int count, ...) {
    char caminho[256] = "";
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        const char* parte = va_arg(args, const char*);
        if (i > 0) strcat(caminho, "/");
        strcat(caminho, parte);
    }

    va_end(args);
    criar_diretorio(caminho);
}

void criar_modulo(const char *nome) {
    if (mkdir(nome, 0755) == -1) {
        if (errno == EEXIST) {
            printf("Erro: O diretório '%s' já existe.\n", nome);
        } else {
            perror("Erro ao criar diretório");
        }
    } else {
        const char *diretorios[] = {"dtos", "infra", "repositories", "services"};
        for (int i = 0; i < 4; i++) {
            if (i == 1) {
                criar_diretorio_com_caminho(2, nome, diretorios[i]);
                const char *infraDirs[] = {"http", "prisma"};
                for (int j = 0; j < 2; j++) {
                    criar_diretorio_com_caminho(3, nome, diretorios[i], infraDirs[j]);
                    if (j == 0) {
                        criar_diretorio_com_caminho(4, nome, diretorios[i], infraDirs[j], "controller");
                        criar_diretorio_com_caminho(4, nome, diretorios[i], infraDirs[j], "routes");
                        criar_diretorio_com_caminho(4, nome, diretorios[i], infraDirs[j], "schemas");
                    } else {
                        criar_diretorio_com_caminho(4, nome, diretorios[i], infraDirs[j], "entities");
                        criar_diretorio_com_caminho(4, nome, diretorios[i], infraDirs[j], "repositories");
                    }
                }
            } else {
                criar_diretorio_com_caminho(2, nome, diretorios[i]);
            }
        }
    }
}

void criar_provider(const char *nome) {
    if (mkdir(nome, 0755) == -1) {
        if (errno == EEXIST) {
            printf("Erro: O diretório '%s' já existe.\n", nome);
        } else {
            perror("Erro ao criar diretório");
        }
    } else {
     // TODO: Implementar a criação de um provider   
    }
}


// Função para mostrar a ajuda
void mostrar_ajuda() {
    printf("Uso: cli <opção> <comando>\n");
    printf("Opções:\n");
    printf("  -h, --help        Mostrar esta ajuda\n");
    printf("  -v, --version     Mostrar a versão do programa\n");
    printf("Comandos:\n");
    printf("  hello             Mostrar mensagem de saudação\n");
    printf("  bye               Mostrar mensagem de despedida\n");
    printf("  module <nome>      Criar um modulo DDD com o nome especificado\n");
    printf("  provider <nome>      Criar um provider DDD com o nome especificado\n");
}


// Função para mostrar a versão
void mostrar_versao() {
    printf(" ______________________________________________  \n");
    printf("< CLI DDD Backend versão 1.0 [Feito por jacule] >\n");
    printf(" ----------------------------------------------  \n");
    printf("        \\   ^__^\n");
    printf("         \\  (oo)\\_______\n");
    printf("            (__)\\       )\\/\\\n");
    printf("                ||----w |\n");
    printf("                ||     ||\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <opção> <comando>\n", argv[0]);
        return 1;
    }

    // Verifica as opções
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            mostrar_ajuda();
            return 0;
        }
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
            mostrar_versao();
            return 0;
        }
    }

    // Verifica os comandos
    if (strcmp(argv[argc - 1], "hello") == 0) {
        printf("Olá, mundo!\n");
    } else if (strcmp(argv[argc - 1], "bye") == 0) {
        printf("Adeus, mundo!\n");
    } else if (strcmp(argv[argc - 2], "module") == 0) {
        if (argc < 3) {
            printf("Erro: Nome do diretório não especificado.\n");
            printf("Uso: %s module <nome>\n", argv[0]);
        } else {
            criar_modulo(argv[2]);
        }
    }else {
        printf("Comando desconhecido: %s\n", argv[argc - 1]);
        printf("Comandos disponíveis: hello, bye\n");
    }

    return 0;
}
