#include "cli.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <opção> <comando>\n", argv[0]);
        return 1;
    }

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
    } else if (strcmp(argv[argc - 2], "provider") == 0) {
        if (argc < 3) {
            printf("Erro: Nome do diretório não especificado.\n");
            printf("Uso: %s provider <nome>\n", argv[0]);
        } else {
            criar_provider(argv[2]);
        }
    } else {
        printf("Comando desconhecido: %s\n", argv[argc - 1]);
        printf("Comandos disponíveis: hello, bye\n");
    }

    return 0;
}