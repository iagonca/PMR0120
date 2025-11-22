#ifndef DEFINICOES_H_INCLUDED
#define DEFINICOES_H_INCLUDED

#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <semphr.h>
#include "componentes.h"
#include "maquina_estados.h"

#define MAX_USUARIOS 5
#define senhaAdm 12345
#define TIMEOUT_AUTENTICACAO 30000
#define TIMEOUT_ALARME 60000
#define TIMEOUT_CONFIG 120000

class Evento {
  private:
    int _dado, _tipo;

  public:
    Evento(){};

    Evento(int tipo, int dado)
    {
    _tipo = tipo;
    _dado = dado;
    }
    int getDado(void) { return _dado; };
    int getTipo(void) { return _tipo; };
    void setTipo(int tipo) { _tipo = tipo; }
    void setDado(int dado) { _dado = dado; }
};

// const byte KEYPAD_ROWS = 4;
// const byte KEYPAD_COLS = 4;
// extern byte rowPins[KEYPAD_ROWS] = {A15, A14, A13, A12};
// byte colPins[KEYPAD_COLS] = {A11, A10, A9, A8};

const byte KEYPAD_ROWS = 4;
const byte KEYPAD_COLS = 4;

extern char keys[KEYPAD_ROWS][KEYPAD_COLS];
extern byte rowPins[KEYPAD_ROWS];
extern byte colPins[KEYPAD_COLS];

// char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
//   {'1', '2', '3', 'A'},
//   {'4', '5', '6', 'B'},
//   {'7', '8', '9', 'C'},
//   {'*', '0', '#', 'D'}
// };

// APENAS DECLARAÇÕES com extern
extern long senhas[MAX_USUARIOS];
extern QueueHandle_t filaEventos;
extern SemaphoreHandle_t xBinarySemaphore;
extern SemaphoreHandle_t semaforoVermelho;
extern SemaphoreHandle_t semaforoVerde;


/*### SETUP COMPONENTES ####*/
class Display;
class Keypad;
class Teclado;
class Led;
class Relay;
class PIR;
class Buzzer;
class FimDeCurso;

extern char senha[6];
extern char keys[KEYPAD_ROWS][KEYPAD_COLS];
extern byte rowPins[KEYPAD_ROWS];
extern byte colPins[KEYPAD_COLS];

extern Display lcd;
extern Keypad keypad;
extern Teclado teclado;
extern Led ledLigado;
extern Led ledVermelho;
extern Led ledVerde;
extern Led lampada;
extern Relay rele;
extern PIR movimento;
extern Buzzer buzzer;
extern FimDeCurso sensorPorta;

/*### MÁQUINA DE ESTADOS ###*/
#define MAX_EVENTO 50
extern unsigned long EventoInstante[MAX_EVENTO];
extern int EventoTipo[MAX_EVENTO];
extern int EventoDado[MAX_EVENTO];
extern int numeroEventos;

void inicializaSenhas();

void acrescentaEvento(unsigned long instante, int tipo, int dado);
Evento obterEvento(void);

/*### FREERTOS ###*/
#define TAMANHO_FILA 5
extern int estado;
extern int codigoAcao;

#endif