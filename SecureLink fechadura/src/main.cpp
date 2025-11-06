#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

//Definições para o keypad
const byte KEYPAD_ROWS = 4;
const byte KEYPAD_COLS = 4;
byte rowPins[KEYPAD_ROWS] = {A15, A14, A13, A12};
byte colPins[KEYPAD_COLS] = {A11, A10, A9, A8};
char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);

class Relay{
  private:
    int pino;
  public:
    //Construtor
    bool estado;
    Relay(int p){
      pino = p;
      pinMode(pino, OUTPUT);
      digitalWrite(p, 0);
      estado = 0;
    }
    void ligar(){
      digitalWrite(pino,1);
      estado = 1;
    }
    void desligar(){
      digitalWrite(pino,0);
      estado = 0;
    }
};

class Led{
  private:
    int pino;
  public:
    //Construtor
    Led(int p){
      pino = p;
      pinMode(pino, OUTPUT);
      digitalWrite(p, 0);
    }
    void ligar(){
      digitalWrite(pino,1);
    }
    void desligar(){
      digitalWrite(pino,0);
    }
    void piscar(){
      // Fazer código com freeRTOS
    }
};

class Buzzer{
  private:
    int pino;
  public:
    bool estado;
    Buzzer(int p){
      pino = p;
      pinMode(pino, OUTPUT);
      estado = 0;
    }
    void tocar(){
      // Utilizar freeRTOS para alternar som
      tone(pino, 440);
      estado = 1;
    }
    void desligar(){
      noTone(pino);
      estado = 0;
    }
};

class PIR{
  private:
    int pino;
  public:
    PIR(int p){
      pino = p;
      pinMode(pino, INPUT);
    }
    int update(){
      return(digitalRead(pino));
    }
};

class FimDeCurso{
  private:
    int pino;
  public:
    FimDeCurso(int p){
      pino = p;
      pinMode(pino, INPUT_PULLUP);
    }
    bool update(){
      return(digitalRead(pino));
    }
};

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