#include <Arduino.h>
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

#define NUM_MAX_USUARIOS 30
#define TAMANHO_SENHA 5


/*Senha ADM*/
int senha_adm = 99999;
/*Matriz de Senhas*/
int senhas[NUM_MAX_USUARIOS];

/*Definições para o keypad*/
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
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);

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

LiquidCrystal_I2C lcd(0x27, 16, 2);


Led ledVermelho(12);
Led ledVerde(11);
Led Lampada(10);

Relay rele(13);
PIR movimento(7);
Buzzer buzzer(6);
FimDeCurso portaAberta(0);

// definicoes
#define true 1
#define false 0

#define numEstados 9
#define numEventos 16
// #define numAcoes 0 // preencher
#define nenhumEvento -1
#define nenhumaAcao -1

enum ESTADOS {
  trancada,
  aberta,
  emAutenticacao,
  alarmeDisparado,
  emConfiguracao,
  aguardandoInfoNovo,
  aguardandoInfoUser,
  selecionarUser,
  confirmarExclusao
};

enum EVENTOS {
  pessoaPresente,
  teclaRecebida,
  rfidIncorreto,
  rfidCorreto,
  senhaCorreta,
  portaFechada,
  excluirUsuario,
  editarInfos,
  maxTentativas,
  timeOutAlarme,
  salvandoDados,
  timeOutAguardando,
  novoUsuario,
  editarUsuario,
  rfidRecebido,
  senhaAdm
};

enum ACOES {
  // colocar as acoes 
  a01,
  a02,
  a03,
  a04,
  a05,
  a06,
  a07,
  a08,
  a09,
  a10,
  a11,
  a12,
  a13,
  a14,
  a15,
  a16,
  a17,
  a18,
  a19,
  a20
};

typedef struct matriz{
  int prox_estado;
  int acao;
} matriz;

matriz matrizTransicaoEstados[numEstados][numEventos];


// inicializacao das funcoes
void iniciarMaquinaEstados();
void iniciaSistema();
int obterEvento();
int obterAcao(int estado, int evento);
int obterProximoEstado(int estado, int evento);
void executarAcao(int codigoAcao);


void setup(){
  Serial.begin(115200);
  lcd.init();                     
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Ola usuario!");
}
unsigned long tempo_inicial = millis();
// codigo principal
void loop() {
    // funcao copiada do professor
    /*
    int codigoEvento;
    int codigoAcao;
    int estado;
    int eventoInterno;

    estado = ESPERA;
    eventoInterno = NENHUM_EVENTO;

    iniciaSistema();
    printf ("Alarme iniciado\n");
    while (true) {
        if (eventoInterno == NENHUM_EVENTO) {
            codigoEvento = obterEvento();
        } else {
            codigoEvento = eventoInterno;
        }
        if (codigoEvento != NENHUM_EVENTO)
        {
        codigoAcao = obterAcao(estado, codigoEvento);
        estado = obterProximoEstado(estado, codigoEvento);
        eventoInterno = executarAcao(codigoAcao);
        printf("Estado: %d Evento: %d Acao:%d\n", estado, codigoEvento, codigoAcao);
        }
    } // while true


    // se prox.evento == nenhumEvento => evento nao muda (para lembrar de incluir no codigo)
    return 0;*/
    Serial.print("Detector de Movimento: ");
    Serial.print(movimento.update());
    Serial.print(" Teclado: ");
    Serial.print(keypad.getKey());
    Serial.print(" Porta: ");
    if(portaAberta.update() == 0){
        Serial.println("Fechada");
    }
    else Serial.println("Aberta");
    Lampada.ligar();
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

void iniciarMaquinaEstados() {
    int i;
    int j;

    for (i = 0; i < numEstados; i++) {
        for (j = 0; j < numEventos; j++) {
            matrizTransicaoEstados[i][j].prox_estado = i; // proximo estado e o proprio estado
            matrizTransicaoEstados[i][j].acao = nenhumaAcao; // por padrao, nao realiza nenhuma ação
        }
    }

    struct transicao {int estado; int evento; int prox_estado; int acao; };
    static const transicao transicoes [] = {
        {trancada,           pessoaPresente,    emAutenticacao,     a01},
        {aberta,             portaFechada,      trancada,           a07},
        {emAutenticacao,     teclaRecebida,     nenhumEvento,       a04},
        {emAutenticacao,     rfidIncorreto,     alarmeDisparado,    a02},
        {emAutenticacao,     rfidCorreto,       aberta,             a05},
        {emAutenticacao,     senhaCorreta,      aberta,             a05},
        {emAutenticacao,     maxTentativas,     alarmeDisparado,    a02},
        {emAutenticacao,     senhaAdm,          emConfiguracao,     a06},
        {alarmeDisparado,    timeOutAlarme,     trancada,           a08},
        {emConfiguracao,     teclaRecebida,     nenhumEvento,       /**/},
        {emConfiguracao,     timeOutAguardando, trancada,           /**/},
        {emConfiguracao,     novoUsuario,       aguardandoInfoNovo, /**/},
        {emConfiguracao,     editarUsuario,     selecionarUser,     /**/},
        {aguardandoInfoNovo, teclaRecebida,     nenhumEvento,       /**/},
        {aguardandoInfoNovo, salvandoDados,     emConfiguracao,     /**/},
        {aguardandoInfoNovo, timeOutAguardando, emConfiguracao,     /**/},
        {aguardandoInfoUser, teclaRecebida,     nenhumEvento,       /**/},
        {aguardandoInfoUser, salvandoDados,     selecionarUser,     /**/},
        {aguardandoInfoUser, timeOutAguardando, selecionarUser,     /**/},
        {selecionarUser,     teclaRecebida,     nenhumEvento,       /**/},
        {selecionarUser,     excluirUsuario,    confirmarExclusao,  /**/},
        {selecionarUser,     editarInfos,       aguardandoInfoUser, /**/},
        {selecionarUser,     timeOutAguardando, trancada,           /**/},
        {confirmarExclusao,  teclaRecebida,     nenhumEvento,       /**/},
        {confirmarExclusao,  salvandoDados,     selecionarUser,     /**/},
        {confirmarExclusao,  timeOutAguardando, selecionarUser,     /**/}
    };

    for (const auto &t : transicoes) {
        matrizTransicaoEstados[t.estado][t.evento] = {t.prox_estado, t.acao};
    };
}

void iniciaSistema() {
    // incializacoes do sistema
    iniciarMaquinaEstados();

}

int obterEvento() {
    //
}

int obterAcao(int estado, int evento) {
    if (estado < 0 || estado >= numEstados || evento < 0 || evento >= numEventos) {
        // condicional para garantir que nao seja acessaco uma entrada inexistente na matriz 
        return nenhumaAcao;
    }
    return matrizTransicaoEstados[estado][evento].acao;
}

int obterProximoEstado(int estado, int evento) {
    if (estado < 0 || estado >= numEstados || evento < 0 || evento >= numEventos) {
        return estado;
    }
    return matrizTransicaoEstados[estado][evento].prox_estado;
}

void executarAcao(int codigoAcao) {
    
    switch (codigoAcao) {
        case a01: // acao a ser realizada
            // coisas a executar dentro da acao 
            printf("Moeda inserida, digite S para iniciar o jogo.\n");
            printf("Ou insira outra moeda para o jogo de 2 jogadores.\n");
            break;

        case a02:
            //
            break;
        
        case a03:
            //
            break;
        
        case a04:
            // 
            break;
        
        case a05:
            // 
            break;
        
        case a06:
            // 
            break;
        
        case a07:
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
}
