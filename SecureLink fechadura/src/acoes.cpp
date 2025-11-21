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
    
    switch (codigoAcao) {
        case a01: // acao a ser realizada     // liga tela inicial; liga lampada; pisca led verde
            // código exemplo -- modificar depois
            lcd.clear();
            lcd.backlight();
            lcd.setCursor(0,0);
            lcd.print("SecureLink");
            lcd.setCursor(0,1);
            lcd.print("Bem-Vindo");
            lampada.ligar();
<<<<<<< HEAD
            ledVerdeLiberado = true;
            xSemaphoreGive(semaforoVerde);
            acrescentaEvento(millis()+10000,timeOutAguardando,0);
=======
>>>>>>> d7e299a06a5dcc9fc8345e9aa928abbfe49d2006
            break;
 
  //    case a01: // acao a ser realizada
  //          // código exemplo -- modificar depois
  //          lcd.mostrarTelaInicial();
  //          lampada.ligar();
  //          ledVerdeLiberado = true;
  //          xSemaphoreGive(semaforoVerde);
  //          acrescentaEvento(millis()+10000,timeOutAguardando,0);
  //          break;

        case a02: // dispara alarme; liga led vermelho; desliga led verde
            //
            Serial.println("ALARME DISPARADO (freertos)");
            buzzerLiberado = true;
            ledVermelhoLiberado = true;
            ledVerdeLiberado = false;

            xSemaphoreGive(xBinarySemaphore);
            xSemaphoreGive(semaforoVermelho);
            acrescentaEvento(millis() + 10000, timeOutAlarme,0);
            teclado.n_tentativas = 0;

            lampada.desligar();
            break;
        
        case a03: // desliga lampada; desliga led; reseta a tela
            //
            lampada.desligar();
            Serial.println("PESSOA desPRESENTE (freertos)");
            ledVerdeLiberado = false;
            teclado.counter_digitos_senha = 0;
            break;
        
        case a04: // computa tecla 
            teclado.incluir_na_senha(&senha[0]);
            // 
            break;
         
        case a05: // printa na tela; liga led verde; desliga lampada; abre a fechadura
            Serial.println("Senha correta. Seja bem-vindo! (freertos)");
            ledVerdeLiberado = false;
            ledVerde.ligar();
            lampada.desligar();
            // 
            break;
        
        case a06: // printa "config"
            Serial.println("Parabéns, agora você está no modo de configuração!");
            // 
            break;
        
        case a07: // tranca a porta; apaga led verde
            Serial.println("LED ON");
            //
            break;
        
        case a08: // para o alarme
          buzzerLiberado = false;
          Serial.println("Alarme 'des'disparado");
            //
            break;
        
        case a09: // computa tecla
            //
            break;
        
        case a10: // computa tecla
            // 
            break;
        
        case a11: // computa tecla
            // 
            break;
        
        case a12: // computa tecla
            // 
            break;
        
        case a13: // computa tecla
            // 
            break;
        
        case a14: // printa na tela "Alterações"
            Serial.println("Parabéns, agora você está no modo de info. do usuário!")
            // 
            break;
        
        case a15: // printa na tela "rfid recebido"
            Serial.println("RFID recebido!")
            // 
            break;
        
        case a16: 
            // 
            break;

        case a17: // printa na tela "config"
            // 
            break;

        case a18: tranca porta; apaga led verde
            // 
            break;

        case a19: // printa na tela "seleção de usuario"
            // 
            break;
        case a20: // printa na tela "confirma exclusão?"
            // 
            break;

        case a21: // print na tela "config salva"
            // 
            break;
    
        case a22: // printa na tela "seleção de usuario"
            // 
            break;

        case a23: // printa na tela "aguardando onfo do usuario"
            // 
            break;
        
        case a24: // printa na tela "config"
            // 
            break;

        case a25: // printa na tela "digite o nome"
            // 
            break;

        case a26:
            // 
            break;

        case a27:
            // 
            break;

        case a28:
            // 
            break;

        case a29:
            // 
            break;

        case a30:
            // 
            break;

        case a31:
            // 
            break;

        case a32:
            // 
            break;

        case a33:
            // 
            break;

        case a34:
            // 
            break;

        case a35:
            // 
            break;

        case a36:
            // 
            break;

        case a37:
            // 
            break;

        case a38:
            // 
            break;

        case a39:
            // 
            break;

        case a40:
            // 
            break;

        case a41:
            // 
            break;

        case a42:
            // 
            break;

        case a43:
            // 
            break;

        case a44:
            // 
            break;

        case a45:
            // 
            break;

        case a46:
            // 
            break;

        case a47:
            // 
            break;

        case a48:
            // 
            break;

        case a49:
            // 
            break;

        case a50:
            // 
            break;

        case a51:
            // 
            break;
        
        case a52:
            // 
            break;

        case a53:
            // 
            break;

        case a54:
            // 
            break;

        case a55:
            // 
            break;

        case a56:
            // 
            break;
    }
}
