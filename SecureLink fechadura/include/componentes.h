#ifndef COMPONENTES_H_INCLUDED
#define COMPONENTES_H_INCLUDED

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include "maquina_estados.h"

extern int senhas[20];

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

class Teclado{
  private:
    Keypad keypad;
  public:
    char tecla;
    int counter_digitos_senha = 0;
    int n_tentativas = 0;
    char senhac[6];
    Teclado(Keypad tec) : keypad(tec){

    }
    void update(){
      tecla = keypad.getKey();
      if(tecla != NO_KEY){
        acrescentaEvento(millis(),teclaRecebida,0);
      }
    }
    void incluir_na_senha(int *senha){
      int n = tecla-'0';
      if(tecla == '0') n = 0;
      *(senha+counter_digitos_senha) = n;
      senhac[counter_digitos_senha] = tecla;
      counter_digitos_senha++;
      
      if(counter_digitos_senha == 5){
        /*TRANSFORMAR EM UM INT APENAS*/
        int senha_decimal = (10000*(*senha)) + (1000*(*(senha+1))) + (100*(*(senha+2))) + (10*(*(senha+3))) + (1*(*(senha+4)));
        Serial.print("Senha digitada: ");
        Serial.println(senha_decimal);
        counter_digitos_senha = 0;
        /*CHECAR SENHA*/
        for(int i = 0; i< 20; i++){
          if(senha_decimal == senhas[i]){
            Serial.println("Senha correta! Seja bem-vindo!");
            n_tentativas = 0;
            acrescentaEvento(millis(),senhaCorreta,3);
            break;
          }
        }
        n_tentativas++;
        if(n_tentativas == 5) acrescentaEvento(millis(),maxTentativas,0);
      }
    }
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
  bool estadoAtual;
  bool ultimoEstado = 0;
    PIR(int p){
      pino = p;
      pinMode(pino, INPUT);
    }
    bool update(){
      estadoAtual = digitalRead(pino);
      if(estadoAtual != ultimoEstado){
        if(estadoAtual == 0){
        }
        else{
          Serial.println("Pessoa presente (.h)");
          acrescentaEvento(millis(),pessoaPresente,0);
        }
        ultimoEstado = estadoAtual;
      }
    }
};
/*COLOCAR DEBOUNCE TIME NO FIM DE CURSO*/
class FimDeCurso{
  private:
    int pino;
  public:
    bool estado_inicial = 0;
    bool estado = 0;
    FimDeCurso(int p){
      pino = p;
      pinMode(pino, INPUT_PULLUP);
    }
    bool update(){

    }
   
};



#endif
