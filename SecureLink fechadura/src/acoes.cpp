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
            ledVerdeLiberado = true;
            xSemaphoreGive(semaforoVerde);
            acrescentaEvento(millis()+10000,timeOutAguardando,0);
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
            teclado.counterSenha = 0;
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
            vTaskDelay( 1000 / portTICK_PERIOD_MS );
            Serial.println("Para editar usuário existente, digite 1");
            vTaskDelay( 7000 / portTICK_PERIOD_MS );
            Serial.println("Para incluir novo usuário, digite 2");
            vTaskDelay( 7000 / portTICK_PERIOD_MS );
            // 
            break;
        
        case a07: // tranca a porta; apaga led verde
            ledVerdeLiberado = false;
            Serial.println("LED ON");
            //
            break;
        
        case a08: // para o alarme e volta pro estado "trancada"
            buzzerLiberado = false;
            Serial.println("Alarme 'des'disparado");
            lampada.desligar();
            ledVerdeLiberado = false;
            //
            break;
        
        case a09: // computa tecla
            //capturaSenha(int *senha);
            //
            break;
        
        case a11: // computa tecla
            // 
            break;
        
        case a12: // computa tecla
            // 
            break;

        case a18: //apaga led verde
            lampada.desligar();
            Serial.println("PESSOA desPRESENTE (freertos)");
            ledVerdeLiberado = false;
            teclado.counterSenha = 0;
            break;

        case a19: // printa na tela "seleção de usuario"; Como como como exibir usuarios :_( e selecionar tbm??!
            Serial.println("Seleção de usuário.");          
            break;

        case a23: // printa na tela "aguardando info do usuario"
            Serial.println("Aguardando informação do usuário.");
            break;
        
        case a24: // printa na tela "config"
            Serial.println("Configurações.");
            break;

        case a26: // printa na tela "digite a senha"
            Serial.println("Digite a senha: ");
            break;

        case a27: // printa na tela "apresente RFID"
            Serial.println("Apresente RFID: ");
            break;

        case a29: // computa a tecla e printa ela
            // 
            break;

        case a30: // computa o novo RFID
            // 
            break;

        case a32: // salva a senha e printa na tela "aguardando info do usuário"
            Serial.println("Aguardando info do usuário.");
            break;

        case a33: // salva o RFID e printa na tela "aguardando info do usuário"
            Serial.println("Aguardando info do usuário.");
            break;

        case a35: // printa na tela "aguardando indo do usuário"
            Serial.println("Aguardando info do usuário.");
            break;

        case a36: // printa na tela "aguardando indo do usuário"
            Serial.println("Aguardando info do usuário.");
            break;

        case a38: // printa na tela "aguardando indo do usuário"
            Serial.println("Aguardando info do usuário.");
            break;

        case a39: // printa na tela "aguardando indo do usuário"
            Serial.println("Aguardando info do usuário.");
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