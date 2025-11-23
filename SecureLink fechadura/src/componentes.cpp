#include "componentes.h"
#include "definicoes.h"
#include "maquina_estados.h"
#include "usuarios.h"

void Teclado::update() {
    tecla = keypad.getKey();
        if(tecla != NO_KEY){
        acrescentaEvento(millis(),teclaRecebida,0);
        }
}

void Teclado::incluir_na_senha(char* senha) {
    if (tecla >= '0' && tecla <= '9') {
        // int n = tecla - '0';

        if (counterSenha == 0) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Digite a Senha:");
        }
        
        if (counterSenha < 5) {
            senha[counterSenha] = tecla;
            Serial.print(tecla);

            lcd.setCursor(1, counterSenha);
            lcd.print("*");

            counterSenha++;
        }
        
        if(counterSenha == 5) {
            usuario resultado = verificaSenha(senha);
            counterSenha = 0;

            if (!resultado.encontrado) {
                n_tentativas++;
                lcd.mostrarSenhaIncorreta(n_tentativas);
    
                if(n_tentativas >= 5) {
                    acrescentaEvento(millis(), maxTentativas, 0);
                    n_tentativas = 0;
                }

                return;
            }

            n_tentativas = 0;

            if (resultado.admin) {
                lcd.mostrarSenhaCorreta("Admin");
                acrescentaEvento(millis(), senhaAdmVerificada, 0);
                return;
            }

            lcd.mostrarSenhaCorreta(resultado.nome);
            acrescentaEvento(millis(), senhaCorreta, 3);
            return;

        }
    }

    else if (tecla == 'D' && counterSenha > 0) {
        counterSenha--;
        senha[counterSenha] = '\0';

        lcd.setCursor(1, counterSenha);
        lcd.print(" ");
    }
}


bool Teclado::verificarSenhaAdmin(int* senha) {
    long senha_decimal = (10000L * senha[0]) + (1000L * senha[1]) + 
                         (100L * senha[2]) + (10L * senha[3]) + senha[4];

    if (senha_decimal == senhaAdm) {
        lcd.mostrarSucesso("Admin");
        acrescentaEvento(millis(), senhaAdmVerificada, 0);
        return true;
    }

    lcd.mostrarErro("Senha inv.");
    return false;
}

void Teclado::capturaNome(char *nome) {
    if ((tecla >= '0' && tecla <= '9') || (tecla >= 'A' && tecla <= 'C')) {
        if (counterNome < 16) {
            bufferNome[counterNome] = tecla;
            counterNome++;
            bufferNome[counterNome] = '\0';

            lcd.setCursor(1, counterNome-1);
            lcd.print(tecla);
        }
    }
    else if (tecla == 'D' && counterNome > 0) {
        counterNome--;
        bufferNome[counterNome] = '\0';

        lcd.setCursor(1, counterNome-1);
        lcd.print(" ");
    }

    else if (tecla == '#') {
        if (counterNome > 0) {
            strcpy(nome, bufferNome);
            counterNome = 0;
            bufferNome[0] = '\0';
            acrescentaEvento(millis(), confirmaAlteracao, 0);

            lcd.mostrarSucesso("Nome salvo!");
        }

        else {
            lcd.mostrarErro("Nome vazio!");
        }
    }
    else if (tecla == '*') {
        counterNome = 0;
        bufferNome[0] = '\0';
        acrescentaEvento(millis(), retorna, 0);

        lcd.mostrarCancelado();
    }
}

void Teclado::capturaSenha(int *senha) {
    if (tecla >= '0' && tecla <= '9') {
        if (counterSenha < 5) {
            int n = tecla - '0';
            bufferSenha[counterSenha] = n;
            counterSenha++;

            lcd.setCursor(1, counterSenha-1);
            lcd.print("*");
        }
    } 
    else if (tecla == 'D' && counterSenha > 0) {
        counterSenha--;
        bufferSenha[counterSenha] = 0;

        lcd.setCursor(1, counterSenha-1);
        lcd.print(" ");
    }
    else if (tecla == '#' && counterSenha == 5) {
        for (int i = 0; i < 5; i++) {
            senha[i] = bufferSenha[i];
        }
        counterSenha = 0;
        memset(bufferSenha, 0, 5 * sizeof(int));
        acrescentaEvento(millis(), confirmaAlteracao, 0);

        lcd.mostrarSucesso("Senha salva!");
    }
    else if (tecla == '*') {
        counterSenha = 0;
        memset(bufferSenha, 0, 5 * sizeof(int));
        acrescentaEvento(millis(), retorna, 0);

        lcd.mostrarCancelado();
    }
}

void Teclado::retornar() {
    if (tecla == 'B') {
        acrescentaEvento(millis(), retorna, 0);
    }
}

void Teclado::confirmaExclusao() {
    if (tecla == '#') {
        lcd.mostrarSalvando();
        acrescentaEvento(millis(), salvandoDados, 0);
    }
    else if (tecla == '*') {
        lcd.mostrarCancelado();
        acrescentaEvento(millis(), retorna, 0);
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
        lcd.mostrarPessoaPresente();
        acrescentaEvento(millis(), pessoaPresente, 0);
    }
    ultimoEstado = estadoAtual;
}

void RFID::update() {
  if (input.length() > 0) {

    usuario.resultado = verificaRFID(input);

	if (verificaRFID(input).encontrado) {
        lcd.mostrarSenhaCorreta();
        lcd.setCursor(1,0);
        lcd.print("Usuario ");
        lcd.setCursor(1, 8);
        lcd.print(resultado.nome);
		acrescentaEvento(millis(), rfidCorreto, 0);
	}

    else {
        lcd.mostrarErro("RFID Incorreto");
        acrescentaEvento(millis(), rfidIncorreto, 0);
        }
    }
}