#include <Arduino_FreeRTOS.h>
#include <Arduino.h>
#include "componentes.h"
#include "definicoes.h"
#include "maquina_estados.h"
#include "acoes.h"
#include <queue.h>

void acrescentaEvento(unsigned long instante, int tipo, int dado);
void taskMaqEstados(void *pvParameters);
void taskBlink(void *pvParameters);
void taskBuzzer(void *pvParameters);
void taskObterEvento(void *pvParameters);

void setup(){
  iniciarMaquinaEstados();
  inicializaSenhas();
  filaEventos = xQueueCreate(TAMANHO_FILA, sizeof(Evento));
  Serial.begin(115200);
  lcd.init();
  lcd.mostrarTelaInicial();
  xTaskCreate(taskBlink,"piscaLed",128,NULL,2,NULL);
  xTaskCreate(taskMaqEstados,"Maquina de Estados",128,NULL,2,NULL);
  xTaskCreate(taskObterEvento, "taskObterEvento", 128, NULL, 1, NULL);
  vTaskStartScheduler();
}

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

/*### FREERTOS ###*/

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

void loop() {}