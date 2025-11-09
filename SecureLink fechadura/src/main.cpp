#include <Arduino.h>
#include "componentes.h"
#include "maquina_estados.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);
Led ledVermelho(12);
Led ledVerde(11);
Led lampada(10);
Relay rele(13);
PIR movimento(7);
Buzzer buzzer(6);
FimDeCurso portaAberta(0);

void setup(){
  iniciarMaquinaEstados();
  Serial.begin(115200);
  lcd.init();                     
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Ola usuario!");
}
unsigned long tempo_inicial = millis();

// codigo principal
void loop() {

    Serial.print("Detector de Movimento: ");
    Serial.print(movimento.update());
    Serial.print(" Teclado: ");
    Serial.print(keypad.getKey());
    Serial.print(" Porta: ");
    if(portaAberta.update() == 0){
        Serial.println("Fechada");
    }
    else Serial.println("Aberta");
    lampada.ligar();
    if(millis()-tempo_inicial >= 500){
        tempo_inicial = millis();
        if(rele.estado == 1){
        rele.desligar();
        ledVerde.ligar();
        ledVermelho.desligar();
        buzzer.desligar();
        }
        else{
        rele.ligar();
        buzzer.tocar();
        ledVerde.desligar();
        ledVermelho.ligar();
        }
    }
}

void executarAcao(int codigoAcao) {
    
    switch (codigoAcao) {
        case a01:
            lampada.ligar();
            ledVerde.piscar();
            ledVermelho.desligar();
            break;

        case a02:
            buzzer.tocar();
            ledVerde.desligar();
            ledVermelho.piscar();
            lampada.piscar();
            break;
        
        case a03:
            lampada.desligar();
            ledVermelho.desligar();
            ledVermelho.ligar();
            break;
        
        case a04:
            // 
            break;
        
        case a05:
            //
            break;
        
        case a06:
            // 
            break;
        
        case a07:
            //
            break;
        
        case a08:
            buzzer.desligar();
            ledVermelho.ligar();
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
        
        }
}

