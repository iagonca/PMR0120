#include "maquina_estados.h"

matriz matrizTransicaoEstados[numEstados][numEventos];

void iniciarMaquinaEstados() {
    int i;
    int j;

    for (i = 0; i < numEstados; i++) {
        for (j = 0; j < numEventos; j++) {
            matrizTransicaoEstados[i][j].prox_estado = i; // proximo estado e o proprio estado
            matrizTransicaoEstados[i][j].acao = nenhumaAcao; // por padrao, nao realiza nenhuma ação
        }
    }

    for (const auto &t : transicoes) {
        matrizTransicaoEstados[t.estado][t.evento] = {t.prox_estado, t.acao};
    };
}

void iniciaSistema() {
    // incializacoes do sistema
    //iniciarMaquinaEstados();

}

/*int obterEvento(int estado, int evento) {
    //
}*/

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


/*
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
*/