#ifndef COMPONENTES_H_INCLUDED
#define COMPONENTES_H_INCLUDED

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include "componentes.h"
#include "definicoes.h"
#include "maquina_estados.h"

class Lcd {
  private:
    LiquidCrystal_I2C display;
  public:
    Lcd(LiquidCrystal_I2C disp) : display(disp){}

    void clear() {
      display.clear();
    }

    void setCursor(int row, int col) {
      display.setCursor(col, row);
    }

    void print(const char* texto) {
      display.print(texto)
    }

};

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

    void update(){
      tecla = keypad.getKey();
      if(tecla != NO_KEY){
        acrescentaEvento(millis(),teclaRecebida,0);
      }
    }

    void incluir_na_senha(int *senha){
      if (tecla >= '0' && tecla <= '9') {
        int n = tecla-'0';
        senha[counterSenha] = n;
        counterSenha++;
      
        if(counterSenha == 5){
          /*TRANSFORMAR EM UM INT APENAS*/
          int senha_decimal = (10000*(*senha)) + (1000*(*(senha+1))) + (100*(*(senha+2))) + (10*(*(senha+3))) + (1*(*(senha+4)));
          Serial.print("Senha digitada: ");
          Serial.println(senha_decimal);
          counterSenha = 0;
          /*CHECAR SENHA*/
          for(int i = 0; i < 20; i++){
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
    }

    /* BUFFERS DE VERIFICAR OS INPUTS */
    void capturaNome(char *nome) {
      // Apenas dígitos e letras (A-D do teclado 4x4)
        if ((tecla >= '0' && tecla <= '9') || 
            (tecla >= 'A' && tecla <= 'C')) {
            
            if (counterNome < 16) {
              bufferNome[counterNome] = tecla;
              counterNome++;
              bufferNome[counterNome] = '\0';
              
              // Mostrar no LCD
            }
        }
        
        // Backspace (tecla D)
        else if (tecla == 'D' && counterNome > 0) {
          counterNome--;
          bufferNome[counterNome] = '\0';
          
          // Atualizar LCD
        }
        
        // Confirmar (tecla #)
        else if (tecla == '#') {
            if (counterNome == 0) {
              // print erro nome nulo
            }

            else {
              // COPIAR o conteúdo para o ponteiro de destino
              strcpy(nome, bufferNome);
              
              // Mostrar confirmação
              
              counterNome = 0;
              bufferNome[0] = '\0';
              
              acrescentaEvento(millis(), confirmaAlteracao, 0);
            }
        }
        
        // Cancelar (tecla *)
        else if (tecla == '*') {
          // Resetar buffer
          counterNome = 0;
          bufferNome[0] = '\0';
          
          acrescentaEvento(millis(), retorna, 0);
        }
    }

    void capturaSenha(int *senha) {
      if (tecla >= '0' && tecla <= '9') {
        if (counterSenha < 5) {
          int n = tecla-'0';
          bufferSenha[counterSenha] = n;
          counterSenha++;
        }

      } 

      // backspace
      else if (tecla == 'D' && counterSenha > 0) {
        counterSenha--;
        bufferSenha[counterSenha] = 0;
        
        // Atualizar LCD

      }

      // confirmar
      else if (tecla == '#') {
        if (counterSenha != 5) {
          // print a senha deve conter 5 caracteres
        }

        else {
          for (int i = 0; i < 5; i++) {
            senha[i] = bufferSenha[i];
          }

          // Mostrar confirmação
          
          bufferSenha[0] = 0;
          
          acrescentaEvento(millis(), confirmaAlteracao, 0);
        }
      }
        
        // cancelar 
        else if (tecla == '*') {
            counterSenha = 0;
            
            acrescentaEvento(millis(), retorna, 0);
        }
    }    
    
    void confirmaExclusao() {
      switch (tecla) {
        case '#':
          acrescentaEvento(millis(), salvandoDados, 0);
          break;
        case '*':
          acrescentaEvento(millis(), retorna, 0);
          break;
        default:
          break;
      }
    }
    
    /* FUNCOES DE SELECIONAR UM NOVO MENU */
    void selecaoEmConfiguracao() {
      switch (tecla) {
        case 'A':
          acrescentaEvento(millis(), editarUsuario, 0);
          break;
        case 'B':
          acrescentaEvento(millis(), novoUsuario, 0);
          break;
        default:
          break;
      }
    }

    void selecaoSelecionarUser() {
      switch (tecla) {
        case 'A':
          acrescentaEvento(millis(), excluirUsuario, 0);
          break;
        case 'B':
          acrescentaEvento(millis(), editarUsuario, 0);
          break;
        default:
          break;
      }
    }

    void selecaoAguardandoInfoUser() {
      switch (tecla) {
        case 'A':
          acrescentaEvento(millis(), editandoNome, 0);
          break;
        case 'B':
          acrescentaEvento(millis(), editarSenha, 0);
          break;
        case 'C':
          acrescentaEvento(millis(), editarRFID, 0);
          break;
        default:
          break;
      }
    }

    void selecaoNovoUsuario() {
      switch (tecla) {
        case 'A':
          acrescentaEvento(millis(), novoNome, 0);
          break;
        case 'B':
          acrescentaEvento(millis(), novaSenha, 0);
          break;
        case 'C':
          acrescentaEvento(millis(), novoRFID, 0);
          break;
        default:
          break;
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
    void update(){
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
    void update(){

    }
   
};


#endif