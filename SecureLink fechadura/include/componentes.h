#ifndef COMPONENTES_H_INCLUDED
#define COMPONENTES_H_INCLUDED

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include "componentes.h"
#include "definicoes.h"
#include "maquina_estados.h"

void acrescentaEvento(unsigned long instante, int tipo, int dado);
extern long senhas[];

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
    int n_usuario = 0;

    Teclado(Keypad tec) : keypad(tec){}

    void update();
    void incluir_na_senha(char *senha);
    void capturaSenha(char* senha);
    void capturaRFID(char* rfid);
    void retornar();
    void confirmaExclusao();
    void selecaoSelecionarUser();
    void selecaoAguardandoInfoUser();

    void incluir_comando_de_config_aguardando_em_config(){} // a fazer
};

class RFID {
  public:
    void update(String input);
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
    unsigned long onTime = 0;
    FimDeCurso(int p){
      pino = p;
      pinMode(pino, INPUT_PULLUP);
    }
    void update(){
      estado = digitalRead(pino);
      if (estado != estado_inicial && estado == LOW) {
          acrescentaEvento(millis(), portaFechada, 0);
      }
      estado_inicial = estado;
      /*
      if(digitalRead(pino) == 0){
        if(estado == 0){
          acrescentaEvento(millis(), portaFechada, 0);
          onTime = millis();
        }
        estado = 1;
      }
      else{
        if (onTime > 0 && millis() - onTime > 1000){
          estado = false;
          onTime = 0;
        }
      }*/

    }
   
};

class Display {
  private:
    LiquidCrystal_I2C* lcd;
    
  public:
    // Construtor
    Display(LiquidCrystal_I2C* disp) : lcd(disp) {}
    
    // Inicialização
    void init() {
      lcd->init();
      lcd->backlight();
      lcd->clear();
    }
    
    // Métodos básicos (wrapper para LiquidCrystal_I2C)
    void clear() { lcd->clear(); }
    void setCursor(int row, int col) { lcd->setCursor(col, row); }
    void print(const char* texto) { lcd->print(texto); }
    void print(char c) { lcd->print(c); }
    void print(int num) { lcd->print(num); }
    void print(long num) { lcd->print(num); }
    void backlight() { lcd->backlight(); }  
    void noBacklight() { lcd->noBacklight(); }
    
    // Métodos específicos do projeto
    void mostrarTelaInicial() {
      clear();
      setCursor(0, 0);
      print("SecureLink");
      setCursor(1, 0);
      print("Trancada");
    }
    
    void mostrarAguardandoRFID() {
      clear();
      setCursor(0, 0);
      print("Aproxime o");
      setCursor(1, 0);
      print("cartao...");
    }
    
    void mostrarDigiteSenha() {
      clear();
      setCursor(0, 0);
      print("Digite a senha:");
      setCursor(1, 0);
    }
    
    void mostrarDigiteNome() {
      clear();
      setCursor(0, 0);
      print("Digite o nome:");
      setCursor(1, 0);
    }
    
    void mostrarMenuConfig() {
      clear();
      setCursor(0, 0);
      print("A-Edit B-Novo");
    }
    
    void mostrarMenuUsuario(const char* nome) {
      clear();
      setCursor(0, 0);
      print(nome);
      setCursor(1, 0);
      print("A-Exc B-Edit");
    }
    
    void mostrarMenuEditarInfo() {
      clear();
      setCursor(0, 0);
      print("A-Nome B-Senha");
      setCursor(1, 0);
      print("C-RFID");
    }
    
    void mostrarMenuNovoUsuario() {
      clear();
      setCursor(0, 0);
      print("Novo Usuario:");
      setCursor(1, 0);
      print("A-Nome B-Senha");
    }
    
    void mostrarAlarme() {
      clear();
      setCursor(0, 0);
      print("*** ALARME ***");
      setCursor(1, 0);
      print("Tentativas max!");
    }
    
    void mostrarPortaAberta() {
      clear();
      setCursor(0, 0);
      print("Porta Aberta");
    }
    
    void mostrarPortaFechada() {
      clear();
      setCursor(0, 0);
      print("Porta Fechada");
    }
    
    void mostrarSalvando() {
      clear();
      setCursor(0, 0);
      print("Salvando...");
    }
    
    void mostrarSucesso(const char* msg) {
      clear();
      setCursor(0, 0);
      print(msg);
      setCursor(1, 0);
      print("Sucesso!");
    }
    
    void mostrarErro(const char* msg) {
      clear();
      setCursor(0, 0);
      print("Erro:");
      setCursor(1, 0);
      print(msg);
    }
    
    void mostrarCancelado() {
      clear();
      setCursor(0, 0);
      print("Cancelado");
    }
    
    void mostrarConfirmaExclusao(const char* nome) {
      clear();
      setCursor(0, 0);
      print("Excluir:");
      setCursor(1, 0);
      print(nome);
      // Próxima linha pode mostrar "# Sim * Nao"
    }
    
    void mostrarSenhaCorreta(const char* usuario) {
      clear();
      setCursor(0, 0);
      print("Bem-vindo!");
      setCursor(1,0);
      print("Usuario ");
      setCursor(1, 8);
      print(usuario);
    }
    
    void mostrarSenhaIncorreta(const int tentativas) {
      clear();
      setCursor(0, 0);
      print("Senha incorreta");
      setCursor(1, 0);
      print("Tent: ");
      print(tentativas);
      print("/5");
    }
    
    void mostrarAguardandoAdmin() {
      clear();
      setCursor(0, 0);
      print("Senha Admin:");
      setCursor(1, 0);
    }
    
    void mostrarPessoaPresente() {
      clear();
      setCursor(0, 0);
      print("Pessoa presente");
    }
};

#endif