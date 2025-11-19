#ifndef COMPONENTES_H_INCLUDED
#define COMPONENTES_H_INCLUDED

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include "componentes.h"
//#include "definicoes.h"
#include "maquina_estados.h"

void acrescentaEvento(unsigned long instante, int tipo, int dado);
extern long senhas[];
extern const int MAX_USUARIOS;

class Teclado{
  private:
    Keypad keypad;
  public:
    char tecla;
    int counterNome = 0;
    char bufferNome[17];
    int counterSenha = 0;
    int bufferSenha[5];
    int n_tentativas = 0;

    Teclado(Keypad tec) : keypad(tec){}

    void update();
    void incluir_na_senha(int *senha);
    void capturaNome(char *nome);
    void capturaSenha(int *senha);
    void confirmaExclusao();
    void selecaoEmConfiguracao();
    void selecaoSelecionarUser();
    void selecaoAguardandoInfoUser();
    void selecaoNovoUsuario();
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
    void update();
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
    void update(){

    }
   
};


#endif