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
    Serial.print("Ação de código: ");
    Serial.println(codigoAcao);
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
            acrescentaEvento(millis()+TIMEOUT_AUTENTICACAO,timeOutAguardando,0);
            break;
 

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
            Serial.println("PORTA FOI FECHADA");
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
            Serial.println("Parabéns, agora você está no modo de info. do usuário!");
            // 
            break;
        
        case a15: // printa na tela "rfid recebido"
            Serial.println("RFID recebido!");
            // 
            break;
        
        case a16: // salvando dados be voltando às configurações
            Serial.println("Configurações.");
            vTaskDelay( 1000 / portTICK_PERIOD_MS );
            Serial.println("Para editar usuário existente, digite 1");
            vTaskDelay( 7000 / portTICK_PERIOD_MS );
            Serial.println("Para incluir novo usuário, digite 2");
            vTaskDelay( 7000 / portTICK_PERIOD_MS );
            //
            break;

        case a17: // printa na tela "config"
            Serial.println("Configurações.");
            vTaskDelay( 1000 / portTICK_PERIOD_MS );
            Serial.println("Para editar usuário existente, digite 1");
            vTaskDelay( 7000 / portTICK_PERIOD_MS );
            Serial.println("Para incluir novo usuário, digite 2");
            vTaskDelay( 7000 / portTICK_PERIOD_MS );
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

        case a20: // printa na tela "confirma exclusão?"
            Serial.println("Confirmar exclusão?");
            break;

        case a21: // print na tela "config salva"
            Serial.println("Configuração salva.");
            break;
    
        case a22: // printa na tela "seleção de usuario"
            Serial.println("Seleção de usuário.");
            break;

        case a23: // printa na tela "aguardando info do usuario"
            Serial.println("Aguardando informação do usuário.");
            break;
        
        case a24: // printa na tela "config"
            Serial.println("Configurações.");
            break;

        case a25: // printa na tela "digite o nome"
            Serial.println("Digite o nome: ");
            break;

        case a26: // printa na tela "digite a senha"
            Serial.println("Digite a senha: ");
            break;

        case a27: // printa na tela "apresente RFID"
            Serial.println("Apresente RFID: ");
            break;

        case a28: // computa a tecla e printa ela
            // 
            break;

        case a29: // computa a tecla e printa ela
            // 
            break;

        case a30: // computa o novo RFID
            // 
            break;

        case a31: // salva o nome e printa na tela "aguardando info do usuário"
            Serial.println("Aguardando info do usuário.");
            break;

        case a32: // salva a senha e printa na tela "aguardando info do usuário"
            Serial.println("Aguardando info do usuário.");
            break;

        case a33: // salva o RFID e printa na tela "aguardando info do usuário"
            Serial.println("Aguardando info do usuário.");
            break;

        case a34: // printa na tela "aguardando indo do usuário"
            Serial.println("Aguardando info do usuário.");
            break;

        case a35: // printa na tela "aguardando indo do usuário"
            Serial.println("Aguardando info do usuário.");
            break;

        case a36: // printa na tela "aguardando indo do usuário"
            Serial.println("Aguardando info do usuário.");
            break;

        case a37: // printa na tela "aguardando indo do usuário"
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

        case a41: // computa tecla e printa ela
            // 
            break;

        case a42: // computa tecla e printa ela
            // 
            break;

        case a43: // printa "alterações descartadas"; printa na tela "Alterações"
            Serial.println("Alterações descartadas");
            vTaskDelay( 1000 / portTICK_PERIOD_MS );
            Serial.println("Parabéns, agora você está no modo de info. do usuário!");
            // 
            break;

        case a44: // printa "alterações descartadas"; printa na tela "Alterações"
            Serial.println("Alterações descartadas.");
            vTaskDelay( 1000 / portTICK_PERIOD_MS );
            Serial.println("Parabéns, agora você está no modo de info. do usuário!");
            // 
            break;

        case a45: // printa "alterações descartadas"; printa na tela "Alterações"
            Serial.println("Alterações descartadas.");
            vTaskDelay( 1000 / portTICK_PERIOD_MS );
            Serial.println("Parabéns, agora você está no modo de info. do usuário!");
            // 
            break;

        case a46: // não existe
            // 
            break;

        case a47: // não existe
            // 
            break;

        case a48: // printa na tela "Alterações"
            Serial.println("Parabéns, agora você está no modo de info. do usuário!");
            // 
            break;

        case a49: // printa na tela "Alterações"
            Serial.println("Parabéns, agora você está no modo de info. do usuário!");
            // 
            break;

        case a50: // printa na tela "Alterações"
            Serial.println("Parabéns, agora você está no modo de info. do usuário!");
            // 
            break;

        case a51:// printa "alterações salvas"; printa na tela "Alterações"
            Serial.println("Alterações salvas.");
            vTaskDelay( 1000 / portTICK_PERIOD_MS );
            Serial.println("Parabéns, agora você está no modo de info. do usuário!");
            // 
            break;
        
        case a52:// printa "alterações salvas"; printa na tela "Alterações"
            Serial.println("Alterações salvas.");
            vTaskDelay( 1000 / portTICK_PERIOD_MS );
            Serial.println("Parabéns, agora você está no modo de info. do usuário!");
            // 
            break;

        case a53: // printa "alterações salvas"; printa na tela "Alterações"
            Serial.println("Alterações salvas.");
            vTaskDelay( 1000 / portTICK_PERIOD_MS );
            Serial.println("Parabéns, agora você está no modo de info. do usuário!");
            // 
            break;

        case a54: // printa "Cadrastre o nome"
            Serial.println("Cadastre o nome: ");
            // 
            break;

        case a55: // printa "Cadrastre a senha"
            Serial.println("Cadastre a senha: ");
            // 
            break;

        case a56: // printa "Aproxime o novo RFID"
            Serial.println("Apromixe o novo RFID");
            // 
            break;
    }
}
