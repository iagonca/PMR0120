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

    else if (tecla == '*') {
        counterSenha = 0;
        acrescentaEvento(millis(), retorna, 0);

        //lcd.mostrarCancelado();
    }
}

void Teclado::capturaSenha(char* senha) {
    Serial.print("N_USUARIO = ");
    Serial.println(n_usuario);
    if (tecla >= '0' && tecla <= '9') {

        if (counterSenha == 0) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Nova Senha:");
        }
        
        if (counterSenha < 5) {
            senha[counterSenha] = tecla;
            Serial.print(tecla);

            lcd.setCursor(1, counterSenha);
            lcd.print("*");

            counterSenha++;
        }
    }

    else if (tecla == 'D' && counterSenha > 0) {
        counterSenha--;
        senha[counterSenha] = '\0';

        lcd.setCursor(1, counterSenha);
        lcd.print(" ");
    }

    else if (tecla == '#' && counterSenha == 5) {
        for (int i = 0; i < 5; i++){
            usuarios[n_usuario].senha[i] = senha[i];
        }

        acrescentaEvento(millis(), confirmaAlteracao, 0);
        lcd.mostrarSucesso("Senha salva!");
    }

    else if (tecla == '*') {
        counterSenha = 0;
        acrescentaEvento(millis(), retorna, 0);

        //lcd.mostrarCancelado();
    }
}

void Teclado::capturaRFID(char *rfid) {
    if (input.length() > 0) {
        input.toCharArray(usuarios[n_usuario].rfid, 20);

        input = "";

        acrescentaEvento(millis(), confirmaAlteracao, 0);
        lcd.mostrarSucesso("RFID salvo!");
    }

    else if (tecla == '*') {
        counterSenha = 0;
        acrescentaEvento(millis(), retorna, 0);
        //lcd.mostrarCancelado();
    }
}

void Teclado::retornar() {
    if (tecla == '*') {
        acrescentaEvento(millis(), retorna, 0);
    }
}

void Teclado::confirmaExclusao() {
    if (tecla == '#') {
        lcd.mostrarSalvando();
        acrescentaEvento(millis(), salvandoDados, 0);
    }
    else if (tecla == '*') {
        //lcd.mostrarCancelado();
        acrescentaEvento(millis(), retorna, 0);
    }
}

void Teclado::selecaoSelecionarUser() {
    if (tecla >= '1' && tecla <= '9') {
        n_usuario = tecla - '0';
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print("Usuario ");
        lcd.print(n_usuario);
        acrescentaEvento(millis(),editarInfos,0);
    }

    else if (tecla == '*') {
        counterSenha = 0;
        acrescentaEvento(millis(), retorna, 0);

        //lcd.mostrarCancelado();
    }

    else {
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print("Erro!");
    }
}

void Teclado::selecaoAguardandoInfoUser() {
    switch (tecla) {
        case 'A':
            acrescentaEvento(millis(), editarSenha, 0);
            break;
        case 'B':
            acrescentaEvento(millis(), editarRFID, 0);
            break;
        case '*':
            counterSenha = 0;
            acrescentaEvento(millis(), retorna, 0);
            //lcd.mostrarCancelado();
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

void RFID::update(String input) {
  if (input.length() > 0) {
    char rfidBuffer[20];
    input.toCharArray(rfidBuffer, 20);

    usuario resultado = verificaRFID(rfidBuffer);

	if (resultado.encontrado) {
        lcd.mostrarSenhaCorreta(resultado.nome);
		acrescentaEvento(millis(), rfidCorreto, 0);
	}

    else {
        lcd.mostrarErro("RFID Incorreto");
        acrescentaEvento(millis(), rfidIncorreto, 0);
        }
    }
}