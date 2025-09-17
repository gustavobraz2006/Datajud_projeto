#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processos.h"

int main() {

    Processos * P = LerDadosProcessos("TJDFT_filtrado.csv");

    printf("Numero de processos: %d\n", getnumProcessos(P));
    printf("Id do ultimo orgão julgador do ultimo processo de id %d: %d\n", getidprocessoMaisAntigo(P), getUltimoOrgaoJulgador(P, getidprocessoMaisAntigo(P)));

    printf("Numero de processos com violência doméstica: %d\n", getviolenciadomestica(P));
    printf("Numero de processos com feminicídio: %d\n", getfeminicidios(P));
    printf("Numero de processos ambientais: %d\n", getambientais(P));
    printf("Numero de processos com comunidades quilombolas: %d\n", getquilombolas(P));
    printf("Numero de processos com comunidades indígenas: %d\n", getindigenas(P));
    printf("Numero de processos com crimes contra a infância: %d\n", getinfancia(P));



    printf("id do processo mais antigo: %d\n", getidprocessoMaisAntigo(P));

    int idAntigo = getidprocessoMaisAntigo(P);
    int idx = 0;
    while (P[idx].id_processo != 0 && P[idx].id_processo != idAntigo) idx++;
    if (P[idx].id_processo != 0 && strlen(P[idx].dt_resolvido) > 0) {
    printf("Numero de dias entre recebimento e resolvido do mais antigo: %d\n",
           getDiasEntreDatas(P[idx].dt_recebimento, P[idx].dt_resolvido));
    } 
    
    else {
    printf("Processo mais antigo não possui data de resolvido registrada.\n");
    }

    printf("Percentual de cumprimento da Meta 1: %.2f%%\n", getcumprimentoMeta1(P));
    gerarCSVMeta1julgados(P, "processos_julgados_meta1.csv");

    free(P); 

    return 0;
}