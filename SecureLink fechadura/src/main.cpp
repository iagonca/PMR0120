#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "componentes.h"
#include "maquina_estados.h"
#include <queue.h>

#define MAX_USUARIOS 20
#define senhaAdm 123456
int senhas[MAX_USUARIOS];


/*### SETUP COMPONENTES ####*/
int senha[5] = {0,0,0,0,0};
LiquidCrystal_I2C lcd(0x27, 16, 2);
Keypad keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);
Teclado teclado(keypad);
Led ledLigado(9);
Led ledVermelho(12);
Led ledVerde(11);
Led lampada(10);
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
    senhas[i] = senhaAdm;
  }
}

void executarAcao(int codigoAcao) {
    
    switch (codigoAcao) {
        case a01: // acao a ser realizada
            
            Serial.println("PESSOA PRESENTE (freertos)");
            lampada.ligar();
          
            break;

        case a02:
            //
            Serial.println("ALARME DISPARADO (freertos)");
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

        case a16:
            // 
            break;
        
        }

        case a17:
            // 
            break;
        
        }

        case a18:
            // 
            break;
        
        }

        case a19:
            // 
            break;
        
        }

        case a20:
            // 
            break;
        
        }

        case a21:
            // 
            break;
        
        }

        case a22:
            // 
            break;
        
        }

        case a23:
            // 
            break;
        
        }

        case a24:
            // 
            break;
        
        }

        case a25:
            // 
            break;
        
        }

        case a26:
            // 
            break;
        
        }

        case a27:
            // 
            break;
        
        }

        case a28:
            // 
            break;
        
        }

        case a29:
            // 
            break;
        
        }

        case a30:
            // 
            break;
        
        }

        case a31:
            // 
            break;
        
        }

        case a32:
            // 
            break;
        
        }

        case a33:
            // 
            break;
        
        }

        case a34:
            // 
            break;
        
        }

        case a35:
            // 
            break;
        
        }

        case a36:
            // 
            break;
        
        }

        case a37:
            // 
            break;
        
        }

        case a38:
            // 
            break;
        
        }

        case a39:
            // 
            break;
        
        }

        case a40:
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
    Evento evento = obterEvento();

    if (xQueueSendToBack(filaEventos, &evento, portMAX_DELAY) != pdPASS)
    {
      Serial.println("Erro ao enviar item para fila");
    }
  }

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