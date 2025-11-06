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