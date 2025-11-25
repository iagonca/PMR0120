#ifndef MAQUINA_ESTADOS_H_INCLUDED
#define MAQUINA_ESTADOS_H_INCLUDED

// definicoes
#define true 1
#define false 0

#define numEstados 15
#define numEventos 26
// #define numAcoes 0 // preencher



enum ESTADOS {
  trancada,
  aberta,
  emAutenticacao,
  alarmeDisparado,
  emConfiguracao,
  aguardandoInfoNovo,
  aguardandoInfoUser,
  selecionarUser,
  confirmarExclusao,
  editandoNome,
  editandoSenha,
  editandoRFID,
  cadastrarNome,
  cadastrarSenha,
  cadastrarRFID
};

enum EVENTOS {
  nenhumEvento = -1,
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
  senhaAdmVerificada,
  editarNome,
  editarSenha,
  editarRFID,
  novoNome,
  novaSenha,
  novoRFID,
  confirmaAlteracao,
  descartaAlteracao,
  retorna
};

enum ACOES {
  nenhumaAcao = -1,
  a01, a02, a03, a04, a05, a06, a07, a08, a09, a10,
  a11, a12, a13, a14, a15, a16, a17, a18, a19, a20,
  a21, a22, a23, a24, a25, a26, a27, a28, a29, a30,
  a31, a32, a33, a34, a35, a36, a37, a38, a39, a40,
  a41, a42, a43, a44, a45, a46, a47, a48, a49, a50,
  a51, a52, a53, a54, a55, a56, a57, a58, a59, a60
};

typedef struct matriz{
  int prox_estado;
  int acao;
} matriz;

// inicializacao das funcoes
void iniciarMaquinaEstados();
// void iniciaSistema();
// void acrescentaEvento(unsigned long instante, int tipo, int dado);
int obterAcao(int estado, int evento);
int obterProximoEstado(int estado, int evento);
// void executarAcao(int codigoAcao);

struct transicao {int estado; int evento; int prox_estado; int acao; };
static const transicao transicoes [] = {
  
  {trancada,           pessoaPresente,     emAutenticacao,     a01},
  {trancada,           teclaRecebida,      emAutenticacao,     a01},

  {emAutenticacao,     rfidIncorreto,      alarmeDisparado,    a02},
  {emAutenticacao,     maxTentativas,      alarmeDisparado,    a02},
  {emAutenticacao,     timeOutAguardando,  trancada,           a03},
  {emAutenticacao,     teclaRecebida,      emAutenticacao,     a04},
  {emAutenticacao,     rfidCorreto,        aberta,             a05},
  {emAutenticacao,     senhaCorreta,       aberta,             a05},
  {emAutenticacao,     senhaAdmVerificada, emConfiguracao,     a06},

  {aberta,             portaFechada,       trancada,           a07},

  {alarmeDisparado,    timeOutAlarme,      trancada,           a08},

  {selecionarUser,     teclaRecebida,      selecionarUser,     a11},
  {selecionarUser,     editarInfos,        aguardandoInfoUser, a23},
  {selecionarUser,     retorna,            trancada,           a40},
  {selecionarUser,     timeOutAguardando,  trancada,           a40},

  {aguardandoInfoUser, teclaRecebida,      aguardandoInfoUser, a12},
  {aguardandoInfoUser, retorna,            selecionarUser,     a24},
  {aguardandoInfoUser, timeOutAguardando,  selecionarUser,     a24},
  {aguardandoInfoUser, editarSenha,        editarSenha,        a26},
  {aguardandoInfoUser, editarRFID,         editandoRFID,       a27},

  {editandoSenha,      teclaRecebida,      editarSenha,        a29},
  {editandoSenha,      confirmaAlteracao,  aguardandoInfoUser, a32},
  {editandoSenha,      timeOutAguardando,  aguardandoInfoUser, a35},
  {editandoSenha,      descartaAlteracao,  aguardandoInfoUser, a38},

  {editandoRFID,       teclaRecebida,      editandoRFID,       a30},
  {editandoRFID,       confirmaAlteracao,  aguardandoInfoUser, a33},
  {editandoRFID,       retorna,            aguardandoInfoUser, a36},
  {editandoRFID,       timeOutAguardando,  aguardandoInfoUser, a36},
  {editandoRFID,       descartaAlteracao,  aguardandoInfoUser, a39},
  
};

extern matriz matrizTransicaoEstados[numEstados][numEventos];

#endif