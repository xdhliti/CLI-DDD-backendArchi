#ifndef CLI_H
#define CLI_H

#include <stdarg.h>

void criar_diretorio(const char *nome);
void criar_diretorio_com_caminho(int count, ...);

void criar_modulo(const char *nome);
void criar_provider(const char *nome);

void mostrar_ajuda();
void mostrar_versao();

#endif // CLI_H
