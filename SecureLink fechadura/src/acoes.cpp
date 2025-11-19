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

void executarAcao(int codigoAcao) {
    
    switch (codigoAcao) {
        case a01: // acao a ser realizada
            // código exemplo -- modificar depois
            lcd.clear();
            lcd.backlight();
            lcd.setCursor(0,0);
            lcd.print("SecureLink");
            lcd.setCursor(0,1);
            lcd.print("Bem-Vindo");
            lampada.ligar();
            break;

        case a02:
            //
            Serial.println("ALARME DISPARADO (freertos)");
            acrescentaEvento(millis() + 10000, timeOutAlarme,0);
            teclado.n_tentativas = 0;
            break;
        
        case a03:
            //
            break;
        
        case a04:
            teclado.incluir_na_senha(&senha[0]);
            // 
            break;
        
        case a05:
            Serial.println("Senha correta. Seja bem-vindo! (freertos)");
            // 
            break;
        
        case a06:
            // 
            break;
        
        case a07:
            Serial.println("LED ON");
            //
            break;
        
        case a08:
          Serial.println("Alarme 'des'disparado");
            //
            break;
        
        case a09:
            //
            break;
        
        case a10:
            // 
            break;
        
        case a11:
            // 
            break;
        
        case a12:
            // 
            break;
        
        case a13:
            // 
            break;
        
        case a14:
            // 
            break;
        
        case a15:
            // 
            break;
        
        case a16:
            // 
            break;

        // case a16:
        //     // 
        //     break;
        
        // }

        case a17:
            // 
            break;

        case a18:
            // 
            break;
        

        case a19:
            // 
            break;
        

        case a20:
            // 
            break;
        

        case a21:
            // 
            break;
        

        case a22:
            // 
            break;
        

        case a23:
            // 
            break;
        

        case a24:
            // 
            break;

        case a25:
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
    }
}
