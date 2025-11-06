#ifndef MAQUINA_ESTADOS_H_INCLUDED
#define MAQUINA_ESTADOS_H_INCLUDED

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

// inicializacao das funcoes
void iniciarMaquinaEstados();
void iniciaSistema();
int obterEvento();
int obterAcao(int estado, int evento);
int obterProximoEstado(int estado, int evento);
void executarAcao(int codigoAcao);

#endif