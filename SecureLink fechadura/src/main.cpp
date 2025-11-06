#include <Arduino.h>

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

// codigo principal
int main() {

    // funcao copiada do professor
    int codigoEvento;
    int codigoAcao;
    int estado;
    int eventoInterno;

    estado = trancada;
    eventoInterno = nenhumEvento;

    iniciaSistema();
    printf ("Alarme iniciado\n");
    while (true) {
        if (eventoInterno == nenhumEvento) {
            codigoEvento = obterEvento();
        } else {
            codigoEvento = eventoInterno;
        }
        if (codigoEvento != nenhumEvento)
        {
        codigoAcao = obterAcao(estado, codigoEvento);
        estado = obterProximoEstado(estado, codigoEvento);
        eventoInterno = executarAcao(codigoAcao);
        printf("Estado: %d Evento: %d Acao:%d\n", estado, codigoEvento, codigoAcao);
        }
    } // while true


    // se prox.evento == nenhumEvento => evento nao muda (para lembrar de incluir no codigo)
    return 0;
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
