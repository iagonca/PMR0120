#include "maquina_estados.h"
matriz matrizTransicaoEstados[numEstados][numEventos];

void iniciarMaquinaEstados() {
    int i;
    int j;

    for (i = 0; i < numEstados; i++) {
        for (j = 0; j < numEventos; j++) {
            matrizTransicaoEstados[i][j].prox_estado = i; // proximo estado é o proprio estado
            matrizTransicaoEstados[i][j].acao = nenhumaAcao; // por padrao, nao realiza nenhuma ação
        }
    }

    for (const auto &t : transicoes) {
        matrizTransicaoEstados[t.estado][t.evento] = {t.prox_estado, t.acao};
    };
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