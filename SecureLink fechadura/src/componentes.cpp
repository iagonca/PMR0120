#include "componentes.h"
#include "definicoes.h"
#include "maquina_estados.h"

// Implementações dos métodos que usam acrescentaEvento

void Teclado::update() {
    tecla = keypad.getKey();
        if(tecla != NO_KEY){
        acrescentaEvento(millis(),teclaRecebida,0);
        }
}

void Teclado::incluir_na_senha(int *senha) {
    if (tecla >= '0' && tecla <= '9') {
        int n = tecla - '0';
        senha[counterSenha] = n;
        counterSenha++;
        
        if(counterSenha == 5) {
            long senha_decimal = (10000L * senha[0]) + (1000L * senha[1]) + 
                                 (100L * senha[2]) + (10L * senha[3]) + senha[4];
            counterSenha = 0;
            
            for(int i = 0; i < MAX_USUARIOS; i++) {
                if(senha_decimal == senhas[i]) {
                    n_tentativas = 0;
                    acrescentaEvento(millis(), senhaCorreta, 3);
                    return;
                }
            }
            
            n_tentativas++;
            if(n_tentativas == 5) {
                acrescentaEvento(millis(), maxTentativas, 0);
            }
        }
    } 
}

void Teclado::capturaNome(char *nome) {
    if ((tecla >= '0' && tecla <= '9') || (tecla >= 'A' && tecla <= 'C')) {
        if (counterNome < 16) {
            bufferNome[counterNome] = tecla;
            counterNome++;
            bufferNome[counterNome] = '\0';
        }
    }
    else if (tecla == 'D' && counterNome > 0) {
        counterNome--;
        bufferNome[counterNome] = '\0';
    }
    else if (tecla == '#') {
        if (counterNome > 0) {
            strcpy(nome, bufferNome);
            counterNome = 0;
            bufferNome[0] = '\0';
            acrescentaEvento(millis(), confirmaAlteracao, 0);
        }
    }
    else if (tecla == '*') {
        counterNome = 0;
        bufferNome[0] = '\0';
        acrescentaEvento(millis(), retorna, 0);
    }
}

void Teclado::capturaSenha(int *senha) {
    if (tecla >= '0' && tecla <= '9') {
        if (counterSenha < 5) {
            int n = tecla - '0';
            bufferSenha[counterSenha] = n;
            counterSenha++;
        }
    } 
    else if (tecla == 'D' && counterSenha > 0) {
        counterSenha--;
        bufferSenha[counterSenha] = 0;
    }
    else if (tecla == '#' && counterSenha == 5) {
        for (int i = 0; i < 5; i++) {
            senha[i] = bufferSenha[i];
        }
        counterSenha = 0;
        memset(bufferSenha, 0, 5 * sizeof(int));
        acrescentaEvento(millis(), confirmaAlteracao, 0);
    }
    else if (tecla == '*') {
        counterSenha = 0;
        memset(bufferSenha, 0, 5 * sizeof(int));
        acrescentaEvento(millis(), retorna, 0);
    }
}

void Teclado::confirmaExclusao() {
    if (tecla == '#') {
        acrescentaEvento(millis(), salvandoDados, 0);
    }
}

void Teclado::selecaoEmConfiguracao() {
    switch (tecla) {
        case 'A':
            acrescentaEvento(millis(), editarUsuario, 0);
            break;
        case 'B':
            acrescentaEvento(millis(), novoUsuario, 0);
            break;
    }
}

void Teclado::selecaoSelecionarUser() {
    switch (tecla) {
        case 'A':
            acrescentaEvento(millis(), excluirUsuario, 0);
            break;
        case 'B':
            acrescentaEvento(millis(), editarUsuario, 0);
            break;
    }
}

void Teclado::selecaoAguardandoInfoUser() {
    switch (tecla) {
        case 'A':
            acrescentaEvento(millis(), editandoNome, 0);
            break;
        case 'B':
            acrescentaEvento(millis(), editarSenha, 0);
            break;
        case 'C':
            acrescentaEvento(millis(), editarRFID, 0);
            break;
    }
}

void Teclado::selecaoNovoUsuario() {
    switch (tecla) {
        case 'A':
            acrescentaEvento(millis(), novoNome, 0);
            break;
        case 'B':
            acrescentaEvento(millis(), novaSenha, 0);
            break;
        case 'C':
            acrescentaEvento(millis(), novoRFID, 0);
            break;
    }
}

void PIR::update() {
    estadoAtual = digitalRead(pino);
    if (estadoAtual != ultimoEstado && estadoAtual == HIGH) {
        acrescentaEvento(millis(), pessoaPresente, 0);
    }
    ultimoEstado = estadoAtual;
}