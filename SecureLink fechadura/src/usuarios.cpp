#include <Arduino.h>
#include "usuarios.h"

// Array de usuários em memória
usuario usuarios[MAX_USUARIOS];
int numUsuarios = 0;

void carregaUsuarios() {
    Serial.println("--- CARREGANDO DADOS PRE-DEFINIDOS (USUARIOS.H) ---");
    
    numUsuarios = 0;

    for (int i = 0; i < MAX_USUARIOS; i++) {
        
        // if (numUsuarios >= MAX_USUARIOS) {
        //     Serial.println("Aviso: Limite maximo de usuarios atingido!");
        //     break;
        // }

        // Copia os dados da lista fixa para a memória do sistema
        strlcpy(usuarios[numUsuarios].nome, usuariosFixos[i].nome, sizeof(usuarios[numUsuarios].nome));
        strlcpy(usuarios[numUsuarios].senha, usuariosFixos[i].senha, sizeof(usuarios[numUsuarios].senha));
        strlcpy(usuarios[numUsuarios].rfid, usuariosFixos[i].rfid, sizeof(usuarios[numUsuarios].rfid));
        
        usuarios[numUsuarios].admin = usuariosFixos[i].admin;
        usuarios[numUsuarios].encontrado = true;
        
        numUsuarios++;
    }

    Serial.print("Sucesso! Usuarios carregados: ");
    Serial.println(numUsuarios);
    listaUsuarios();
}

void modificaSenha(char* nome, char* novaSenha) {
    for (int i = 0; i < numUsuarios; i++) {
        if (strcmp(usuarios[i].nome, nome) == 0) {
            strlcpy(usuarios[i].senha, novaSenha, sizeof(usuarios[i].senha));
            Serial.println("Senha modificada com sucesso");
            return;
        }
    }
    Serial.println("Usuario nao encontrado");
}

void modificaRFID(char* nome, char* novo_rfid) {
    for (int i = 0; i < numUsuarios; i++) {
        if (strcmp(usuarios[i].nome, nome) == 0) {
            strlcpy(usuarios[i].rfid, novo_rfid, sizeof(usuarios[i].rfid));
            Serial.println("RFID modificado com sucesso");
            return;
        }
    }
    Serial.println("Usuario nao encontrado");
}

usuario verificaSenha(char* senha) {
    usuario resultado = {"", "", "", false, false};

    for (int i = 0; i < numUsuarios; i++) {
        if (strcmp(usuarios[i].senha, senha) == 0) {
            resultado = usuarios[i];
            Serial.print("Usuario encontrado: ");
            Serial.println(resultado.nome);
            return resultado;
        }
    }

    Serial.println("Senha nao encontrada");
    return resultado;
}

usuario verificaRFID(char* rfid) {
    usuario resultado = {"", "", "", false, false};

    for (int i = 0; i < numUsuarios; i++) {
        if (strcmp(usuarios[i].rfid, rfid) == 0) {
            resultado = usuarios[i];
            Serial.print("Usuario encontrado: ");
            Serial.println(usuarios[i].nome);
            return resultado;
        }
    }

    Serial.println("RFID nao encontrado");
    return resultado;
}

void listaUsuarios() {
    Serial.println("\n=== Lista de Usuarios ===");
    for (int i = 0; i < numUsuarios; i++) {
        Serial.print(i + 1);
        Serial.print(". Nome: ");
        Serial.print(usuarios[i].nome);
        Serial.print(" | Senha: ");
        Serial.print(usuarios[i].senha);
        Serial.print(" | RFID: ");
        Serial.print(usuarios[i].rfid);
        Serial.print(" | Admin: ");
        Serial.println(usuarios[i].admin ? "Sim" : "Nao");
    }
    Serial.println("========================\n");
}
