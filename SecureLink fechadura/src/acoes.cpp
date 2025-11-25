#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "componentes.h"
#include "definicoes.h"
#include "maquina_estados.h"
#include <queue.h>
#include "acoes.h"

// extern Led lampada;
// extern Teclado teclado;
// extern
extern bool buzzerLiberado;
extern bool ledVerdeLiberado;
extern bool ledVermelhoLiberado;

void executarAcao(int codigoAcao) {
    /*DEBUGGING*/
    Serial.println("==============================================");
    Serial.print("AÇÃO: ");
    Serial.println(codigoAcao);
    Serial.println("=============================================="); 

    switch (codigoAcao) {
        case a01: // acao a ser realizada     // liga tela inicial; liga lampada; pisca led verde
            // código exemplo -- modificar depois
            lcd.clear();
            lcd.backlight();
            lcd.setCursor(0,0);
            lcd.print("Digite sua senha");
            lcd.setCursor(1,0);
            lcd.print("ou use seu RFID.");
            lampada.ligar();
            ledVerdeLiberado = true;
            xSemaphoreGive(semaforoVerde);
            acrescentaEvento(millis()+60000,timeOutAguardando,0);
            break;

        case a02: // dispara alarme; liga led vermelho; desliga led verde
            //
            Serial.println("ALARME DISPARADO (freertos)");
            ledVermelho.desligar();
            ledVerde.desligar();
            lcd.clear();
            lcd.mostrarAlarme();

            buzzerLiberado = true;
            ledVermelhoLiberado = true;
            ledVerdeLiberado = false;

            xSemaphoreGive(xBinarySemaphore);
            xSemaphoreGive(semaforoVermelho);
            removeEvento(timeOutAguardando);
            acrescentaEvento(millis() + 10000, timeOutAlarme,0);
            teclado.n_tentativas = 0;

            lampada.desligar();
            break;
        
        case a03: // desliga lampada; desliga led; reseta a tela
            //
            lampada.desligar();
            Serial.println("PESSOA desPRESENTE (freertos)");
            lcd.mostrarTelaInicial();
            ledVerdeLiberado = false;
            ledVerde.desligar();
            teclado.counterSenha = 0;
            break;
        
        case a04: // computa tecla 
            teclado.incluir_na_senha(&senha[0]);
            // 
            break;
         
        case a05: // printa na tela; liga led verde; desliga lampada; abre a fechadura
            Serial.println("Senha correta. Seja bem-vindo! (freertos)");
            ledVerdeLiberado = false;
            ledVerde.desligar();
            ledVerde.ligar();
            ledVermelho.desligar();
            lampada.desligar();
            rele.desligar();
            removeEvento(timeOutAguardando);
            // 
            break;
        
        case a06: // printa "config"
            removeEvento(timeOutAguardando);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Editar usuario.");
            lcd.setCursor(1,0);
            lcd.print("Selecione: 1 a 5");
            acrescentaEvento(millis()+60000,timeOutAguardando,0);
            // 
            break;
        
        case a07: // tranca a porta; apaga led verde
            ledVerdeLiberado = false;
            ledVerde.desligar();
            lcd.mostrarTelaInicial();
            ledVermelho.ligar();
            Serial.println("PORTA FOI FECHADA");
            rele.ligar();
            //
            break;
        
        case a08: // para o alarme e volta pro estado "trancada"
            buzzerLiberado = false;
            ledVermelhoLiberado = false;
            Serial.println("Alarme desligado");
            lampada.desligar();
            ledVerdeLiberado = false;
            ledVermelho.ligar();
            lcd.mostrarTelaInicial();
            //
            break;
        
        case a11: // computa tecla
            teclado.selecaoSelecionarUser();
            acrescentaEvento(millis(),editarInfos,0);
            break;
        
        case a12: // computa tecla A ou B para selecionar rfid ou senha
            teclado.selecaoAguardandoInfoUser();
            // teclado. asterisco
            break;

        case a23: // printa na tela "aguardando info do usuario"
            removeEvento(timeOutAguardando);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("A: editar RFID");
            lcd.setCursor(1,0);
            lcd.print("B: editar senha");
            acrescentaEvento(millis()+60000,timeOutAguardando,0);
            // 
            break;
        
        case a24: // printa na tela "config"
            removeEvento(timeOutAguardando);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Editar usuario.");
            lcd.setCursor(1,0);
            lcd.print("Selecione: 1 a 5");
            acrescentaEvento(millis()+60000,timeOutAguardando,0);
            break;

        case a26: // printa na tela "digite a senha"
            removeEvento(timeOutAguardando);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Digite a nova");
            lcd.setCursor(1,0);
            lcd.print("senha.");
            acrescentaEvento(millis()+60000,timeOutAguardando,0);
            break;

        case a27: // printa na tela "apresente RFID"
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Aproxime RFID");
            acrescentaEvento(millis()+60000,timeOutAguardando,0);
            break;

        case a29: // computa a tecla e printa ela
            teclado.capturaSenha(&senha[0]);
            break;

        case a30: // computa o novo RFID
            // 
            break;

        case a32: // salva a senha e printa na tela "aguardando info do usuário"
            removeEvento(timeOutAguardando);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("A: editar RFID");
            lcd.setCursor(1,0);
            lcd.print("B: editar senha");
            acrescentaEvento(millis()+60000,timeOutAguardando,0);
            Serial.println("Aguardando info do usuário.");
            break;

        case a33: // salva o RFID e printa na tela "aguardando info do usuário"
            Serial.println("Aguardando info do usuário.");
            break;

        case a35: //
            removeEvento(timeOutAguardando); 
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("A: editar RFID");
            lcd.setCursor(1,0);
            lcd.print("B: editar senha");
            acrescentaEvento(millis()+60000,timeOutAguardando,0);
            break;

        case a36: // printa na tela "aguardando indo do usuário"
            Serial.println("Aguardando info do usuário.");
            break;

        case a38: // printa na tela "aguardando indo do usuário"
            Serial.println("Aguardando info do usuário.");
            break;

        case a39: // descartar alterações

            break;

        case a40: // desliga lampada; desliga led; reseta a tela
            //
            lampada.desligar();
            Serial.println("PESSOA desPRESENTE (freertos)");
            ledVerdeLiberado = false;
            teclado.counterSenha = 0;
            break;
    }
}