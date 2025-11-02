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
  A01,
  A02,
  A03,
  A04,
  A05,
  A06,
  A07,
  A08,
  A09,
  A10,
  A11,
  A12,
  A13,
  A14,
  A15,
  A16,
  A17,
  A18,
  A19,
  A20
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
        {trancada,           pessoaPresente,    emAutenticacao,     A01},
        {aberta,             portaFechada,      trancada,           A07},
        {emAutenticacao,     teclaRecebida,     nenhumEvento,       A04},
        {emAutenticacao,     rfidIncorreto,     alarmeDisparado,    A02},
        {emAutenticacao,     rfidCorreto,       aberta,             A05},
        {emAutenticacao,     senhaCorreta,      aberta,             A05},
        {emAutenticacao,     maxTentativas,     alarmeDisparado,    A02},
        {emAutenticacao,     senhaAdm,          emConfiguracao,     A06},
        {alarmeDisparado,    timeOutAlarme,     trancada,           A08},
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
        case A01: // acao a ser realizada
            // coisas a executar dentro da acao 
            printf("Moeda inserida, digite S para iniciar o jogo.\n");
            printf("Ou insira outra moeda para o jogo de 2 jogadores.\n");
            break;

        case A02:
            //
            break;
        
        case A03:
            //
            break;
        
        case A04:
            // 
            break;
        
        case A05:
            // 
            break;
        
        case A06:
            // 
            break;
        
        case A07:
            //
            break;
        
        case A08:
            //
            break;
        
        case A09:
            //
            break;
        
        case A10:
            // 
            break;
        
        case A11:
            // 
            break;
        
        case A12:
            // 
            break;
        
        case A13:
            // 
            break;
        
        case A14:
            // 
            break;
        
        case A15:
            // 
            break;
        
        case A16:
            // 
            break;
        
        }
}
