#include <Arduino.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include "componentes.h"
#include "definicoes.h"
#include "maquina_estados.h"


long senhas[MAX_USUARIOS];
QueueHandle_t filaEventos;
SemaphoreHandle_t xBinarySemaphore;
SemaphoreHandle_t semaforoVermelho;
SemaphoreHandle_t semaforoVerde;


/*### SETUP COMPONENTES ####*/
char senha[6] = {0,0,0,0,0};

char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[KEYPAD_ROWS] = {A15, A14, A13, A12};
byte colPins[KEYPAD_COLS] = {A11, A10, A9, A8};

LiquidCrystal_I2C lcdI2C(0x27, 16, 2);
Display lcd(&lcdI2C);
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


/*### FREERTOS ###*/
#define TAMANHO_FILA 5
int estado = trancada;
int codigoAcao;
