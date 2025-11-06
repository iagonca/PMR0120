#include <Arduino.h>
#include "componentes.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);


Led ledVermelho(12);
Led ledVerde(11);
Led Lampada(10);

Relay rele(13);
PIR movimento(7);
Buzzer buzzer(6);
FimDeCurso portaAberta(0);

void setup(){
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
    Lampada.ligar();
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