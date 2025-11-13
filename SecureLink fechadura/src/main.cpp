#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "componentes.h"
#include "maquina_estados.h"
#include <queue.h>

#define MAX_USUARIOS 20
#define senha_do_adm 12121
int senhas[MAX_USUARIOS];


/*### SETUP COMPONENTES ####*/
int senha[5] = {0,0,0,0,0};
LiquidCrystal_I2C lcd(0x27, 16, 2);
Keypad keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);
Teclado teclado(keypad);
Led ledLigado(9);
Led ledVermelho(12);
Led ledVerde(11);
Led Lampada(10);
Relay rele(13);
PIR movimento(7);
Buzzer buzzer(6);
FimDeCurso portaAberta(0);


/*### MÁQUINA DE ESTADOS ###*/
#define MAX_EVENTO 50
unsigned long EventoInstante[MAX_EVENTO];
int EventoTipo[MAX_EVENTO], EventoDado[MAX_EVENTO];
int numeroEventos = 0;
void inicializaSenhas(){
  for(int i = 0; i<MAX_USUARIOS; i++){
    senhas[i] = senha_do_adm;
  }
}
void executarAcao(int codigoAcao) {
    
    switch (codigoAcao) {
        case a01: // acao a ser realizada
            
            Serial.println("PESSOA PRESENTE (freertos)");
            Lampada.ligar();
          
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
        
        }
}

void acrescentaEvento(unsigned long instante, int tipo, int dado)
{
  Serial.println("Acrescenta evento = " + String(tipo));
  if (numeroEventos == MAX_EVENTO)
    return;
  int i, j;
  for (i = 0; i < numeroEventos; i++)
    if (EventoInstante[i] < instante)
    {
      for (j = numeroEventos; j > i - 1; j--)
      {
        EventoInstante[j] = EventoInstante[j - 1];
        EventoTipo[j] = EventoTipo[j - 1];
        EventoDado[j] = EventoDado[j - 1];
      }
      break;
    }
  EventoInstante[i] = instante;
  EventoTipo[i] = tipo;
  EventoDado[i] = dado;
  numeroEventos++;
}

class Evento
{
private:
  int _dado, _tipo;

public:
  Evento() {};
  Evento(int tipo, int dado)
  {
    _tipo = tipo;
    _dado = dado;
  }
  int getDado(void) { return _dado; };
  int getTipo(void) { return _tipo; };
};

Evento obterEvento(void)
{
  Evento eventoNulo(nenhumEvento, 0);
  if (numeroEventos == 0)
    return eventoNulo;
  if (millis() < EventoInstante[0])
    return eventoNulo;
  int evento = EventoTipo[0], dado = EventoDado[0], i;
  for (i = 0; i < numeroEventos - 1; i++)
  {
    EventoInstante[i] = EventoInstante[i + 1];
    EventoTipo[i] = EventoTipo[i + 1];
    EventoDado[i] = EventoDado[i + 1];
  }
  numeroEventos--;
  Evento eventoAtual(evento, dado);
  return eventoAtual;
}

/*### FREERTOS ###*/
#define TAMANHO_FILA 5

int estado = trancada;
int codigoAcao;

QueueHandle_t filaEventos;
void taskMaqEstados(void *pvParameters){
  Evento evento;

  for (;;)
  {
    // evento = obterEvento();
    if (xQueueReceive(filaEventos, &evento, portMAX_DELAY) != pdPASS)
    {
      Serial.println("Erro ao receber item da fila");
      continue;
    }

    if (evento.getTipo() != nenhumEvento)
    {
      Serial.println("Evento!");
      codigoAcao = obterAcao(estado, evento.getTipo());
      estado = obterProximoEstado(estado, evento.getTipo());
      executarAcao(codigoAcao);
    }

    movimento.update();
    teclado.update();
  }

}
void taskObterEvento(void *pvParameters);
void taskBlink(void *pvParameters){
  for (;;) // A Task shall never return or exit.
  {
    ledLigado.ligar();   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
    ledLigado.desligar();    // turn the LED off by making the voltage LOW
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
  }
}
void taskBuzzer(void *pvParameters){

}
void setup(){
  iniciarMaquinaEstados();
  inicializaSenhas();
  filaEventos = xQueueCreate(TAMANHO_FILA, sizeof(Evento));
  Serial.begin(115200);
  xTaskCreate(taskBlink,"piscaLed",128,NULL,2,NULL);
  xTaskCreate(taskMaqEstados,"Maquina de Estados",128,NULL,2,NULL);
  xTaskCreate(taskObterEvento, "taskObterEvento", 128, NULL, 1, NULL);
  vTaskStartScheduler();

}
unsigned long tempo_inicial = millis();

// codigo principal
void loop() {
}

void taskObterEvento(void *pvParameters){
  Evento evento;

  for (;;)
  {
    evento = obterEvento();

    if (xQueueSendToBack(filaEventos, &evento, portMAX_DELAY) != pdPASS)
    {
      Serial.println("Erro ao enviar item para fila");
    }
  }
}