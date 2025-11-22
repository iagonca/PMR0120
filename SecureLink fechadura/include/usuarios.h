#ifndef USUARIOS_H_INCLUDED
#define USUARIOS_H_INCLUDED

#include <Arduino.h> // Necessário para tipos
#include "definicoes.h"

struct usuario {
    //bool encontrado;
    char nome[50];
    char senha[7];
    char rfid[20];
    bool admin;
    bool encontrado;
};

// Lista de usuários para carregar automaticamente (Edite aqui para adicionar mais)
const usuario usuariosFixos[] = {
    {"1", "12345", "BD 31 15 2B", true},
    {"2",  "11111", "BD 31 15 2C", false},
    {"3", "22222", "BD 31 15 2D", false},
    {"4", "33333", "BD 31 15 2E", false},
    {"5",   "44444", "BD 31 15 2F", false}
};

// Array de usuários em memória
extern usuario usuarios[MAX_USUARIOS];


void carregaUsuarios();
void modificaSenha(char* nome, char* novaSenha);
void modificaRFID(char* nome, char* novo_rfid);
usuario verificaSenha(char* senha);
usuario verificaRFID(char* rfid);
void listaUsuarios();

#endif