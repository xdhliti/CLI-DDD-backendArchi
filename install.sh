#!/bin/bash

# Nome do arquivo de origem e do executável
SOURCE_FILE="cli.c"
MAIN_FILE="main.c"
EXECUTABLE_NAME="jacule"

# Local de instalação do executável
INSTALL_PATH_LINUX="/usr/local/bin"
INSTALL_PATH_MAC="/usr/local/bin"


OS=$(uname -s)

if [ "$OS" = "Linux" ]; then
    sudo apt-get update
    sudo apt-get install gcc
    INSTALL_PATH=$INSTALL_PATH_LINUX
elif [ "$OS" = "Darwin" ]; then 
    brew install gcc
    INSTALL_PATH=$INSTALL_PATH_MAC
else
    echo "Sistema operacional não suportado."
    exit 1
fi

# Compilando o programa
gcc -o $EXECUTABLE_NAME $MAIN_FILE $SOURCE_FILE 

# Verifica se a compilação foi bem-sucedida
if [ $? -eq 0 ]; then
    echo "Compilação bem-sucedida. Instalando o programa..."

    # Movendo o executável para o diretório de instalação
    sudo mv $EXECUTABLE_NAME $INSTALL_PATH

    # Dando permissão de execução
    sudo chmod +x $INSTALL_PATH/$EXECUTABLE_NAME

    echo "Instalação concluída. Você pode agora executar o comando '$EXECUTABLE_NAME' de qualquer lugar no sistema."
else
    echo "Erro: A compilação falhou. Verifique o código e tente novamente."
fi
