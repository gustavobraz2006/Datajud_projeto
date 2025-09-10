#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "processos.h"

Processos * LerDadosProcessos(char * NomeArquivo) {

    FILE * fp = fopen(NomeArquivo, "r");
    if (fp == NULL) {
        printf("ERRO: o arquivo não pode ser aberto\n");
        exit(1);
    }

    char buffer[1024];
    fgets(buffer, sizeof(buffer), fp); // pula cabeçalho

    Processos * P = malloc(100000 * sizeof(Processos));
    int i = 0;

    while (!feof(fp)) {

        // Variáveis temporárias para campos numéricos que podem estar vazios
        char tmp_cnm1[10], tmp_primeirasentm1[10], tmp_baixm1[10], tmp_decm1[10];
        char tmp_mpum1[10], tmp_julgadom1[10], tmp_desm1[10], tmp_susm1[10];

        int n = fscanf(fp,
            "%d;%49[^;];%9[^;];%99[^;];%49[^;];%9[^;];%d;%d;%d;%10[^;];%d;%d;%d;%d;%d;%d;%d;%d;%10[^;];%9[^;];%9[^;];%9[^;];%9[^;];%9[^;];%9[^;];%9[^;]\n",
            &P[i].id_processo,
            P[i].numero_sigilo,
            P[i].sigla_grau,
            P[i].procedimento,
            P[i].ramo_justica,
            P[i].sigla_tribunal,
            &P[i].id_tribunal,
            &P[i].recurso,
            &P[i].id_ultimo_oj,
            P[i].dt_recebimento,
            &P[i].id_ultima_classe,
            &P[i].flag_violencia_domestica,
            &P[i].flag_feminicidio,
            &P[i].flag_ambiental,
            &P[i].flag_quilombolas,
            &P[i].flag_indigenas,
            &P[i].flag_infancia,
            &P[i].decisao,
            P[i].dt_resolvido,
            tmp_cnm1,
            tmp_primeirasentm1,
            tmp_baixm1,
            tmp_decm1,
            tmp_mpum1,
            tmp_julgadom1,
            tmp_desm1,
            tmp_susm1
        );

        if (n == EOF) break;
        if (n != 26) continue; // ignora linhas inválidas

        // Converter campos numéricos temporários para int, trata vazio como 0
        P[i].cnm1 = strlen(tmp_cnm1) > 0 ? atoi(tmp_cnm1) : 0;
        P[i].primeirasentm1 = strlen(tmp_primeirasentm1) > 0 ? atoi(tmp_primeirasentm1) : 0;
        P[i].baixm1 = strlen(tmp_baixm1) > 0 ? atoi(tmp_baixm1) : 0;
        P[i].decm1 = strlen(tmp_decm1) > 0 ? atoi(tmp_decm1) : 0;
        P[i].mpum1 = strlen(tmp_mpum1) > 0 ? atoi(tmp_mpum1) : 0;
        P[i].julgadom1 = strlen(tmp_julgadom1) > 0 ? atoi(tmp_julgadom1) : 0;
        P[i].desm1 = strlen(tmp_desm1) > 0 ? atoi(tmp_desm1) : 0;
        P[i].susm1 = strlen(tmp_susm1) > 0 ? atoi(tmp_susm1) : 0;

        i++;
    }

    P[i].id_processo = 0; // marca final do vetor
    fclose(fp);
    return P;
}

int getnumProcessos (Processos * P) {
    int i = 0;
    while (P[i].id_processo != 0) i++;
    return i;
}

// o ultimo orgao julgador do processo a partir do id_processo

int getUltimoOrgaoJulgador(Processos * P, int id_processo) {
    int i = 0;
    while (P[i].id_processo != 0) {
        if (P[i].id_processo == id_processo) {
            return P[i].id_ultimo_oj;
        }
        i++;
    }
    return -1; // retorna -1 se o processo não for encontrado
}
int getidprocessoMaisAntigo (Processos * P) {
    int i = 0;
    int idxMaisAntigo = 0;
    while (P[i].id_processo != 0) {
        if (strcmp(P[i].dt_recebimento, P[idxMaisAntigo].dt_recebimento) < 0) {
            idxMaisAntigo = i;
        }
        i++;
    }
    return P[idxMaisAntigo].id_processo;
}

int getviolenciadomestica (Processos * P) {
    int i = 0, y = 0;
    while (P[i].id_processo != 0) {
        if (P[i].flag_violencia_domestica == 1) y++;
        i++;
    }
    return y;
}

int getfeminicidios (Processos * P) {
    int i = 0, y = 0;
    while (P[i].id_processo != 0) {
        if (P[i].flag_feminicidio == 1) y++;
        i++;
    }
    return y;
}

int getambientais (Processos * P) {
    int i = 0, y = 0;
    while (P[i].id_processo != 0) {
        if (P[i].flag_ambiental == 1) y++;
        i++;
    }
    return y;
}

int getquilombolas (Processos * P) {
    int i = 0, y = 0;
    while (P[i].id_processo != 0) {
        if (P[i].flag_quilombolas == 1) y++;
        i++;
    }
    return y;
}

int getindigenas (Processos * P) {
    int i = 0, y = 0;
    while (P[i].id_processo != 0) {
        if (P[i].flag_indigenas == 1) y++;
        i++;
    }
    return y;
}

int getinfancia (Processos * P) {
    int i = 0, y = 0;
    while (P[i].id_processo != 0) {
        if (P[i].flag_infancia == 1) y++;
        i++;
    }
    return y;
}

// numero de dias entre data de recebimento e a data resolvida

int getDiasEntreDatas(const char * dt_recebimento, const char * dt_resolvido) {
    struct tm tm_recebimento = {0};
    struct tm tm_resolvido = {0};


    sscanf(dt_recebimento, "%d-%d-%d", &tm_recebimento.tm_year, &tm_recebimento.tm_mon, &tm_recebimento.tm_mday);
    sscanf(dt_resolvido, "%d-%d-%d", &tm_resolvido.tm_year, &tm_resolvido.tm_mon, &tm_resolvido.tm_mday);

    
    tm_recebimento.tm_year -= 1900;
    tm_recebimento.tm_mon -= 1;
    tm_resolvido.tm_year -= 1900;
    tm_resolvido.tm_mon -= 1;

    time_t time_recebimento = mktime(&tm_recebimento);
    time_t time_resolvido = mktime(&tm_resolvido);

    double segundos = difftime(time_resolvido, time_recebimento);
    return (int)(segundos / (60 * 60 * 24));
}


float getcumprimentoMeta1(Processos * P) {
    int totalProcessos = getnumProcessos(P);
    int processosResolvidos = 0;
    for (int i = 0; i < totalProcessos; i++) {
        if (strlen(P[i].dt_resolvido) > 0) processosResolvidos++;
    }
    if (totalProcessos == 0) return 0.0;
    return (float)processosResolvidos / totalProcessos * 100.0;
}

Processos * gerarCSVMeta1julgados(Processos * P, const char * NomeArquivoSaida) {
    FILE * fp = fopen(NomeArquivoSaida, "w");
    if (fp == NULL) {
        printf("ERRO: o arquivo de saída não pode ser criado\n");
        exit(1);
    }

    fprintf(fp, "id_processo;numero_sigilo;sigla_grau;procedimento;ramo_justica;sigla_tribunal;id_tribunal;recurso;id_ultimo_oj;dt_recebimento;id_ultima_classe;flag_violencia_domestica;flag_feminicidio;flag_ambiental;flag_quilombolas;flag_indigenas;flag_infancia;decisao;dt_resolvido;cnm1;primeirasentm1;baixm1;decm1;mpum1;julgadom1;desm1;susm1\n");

    int i = 0;
    while (P[i].id_processo != 0) {
        if (P[i].julgadom1 == 1) {
            fprintf(fp,
                "%d;%s;%s;%s;%s;%s;%d;%d;%d;%s;%d;%d;%d;%d;%d;%d;%d;%d;%s;%d;%d;%d;%d;%d;%d;%d;%d\n",
                P[i].id_processo,
                P[i].numero_sigilo,
                P[i].sigla_grau,
                P[i].procedimento,
                P[i].ramo_justica,
                P[i].sigla_tribunal,
                P[i].id_tribunal,
                P[i].recurso,
                P[i].id_ultimo_oj,
                P[i].dt_recebimento,
                P[i].id_ultima_classe,
                P[i].flag_violencia_domestica,
                P[i].flag_feminicidio,
                P[i].flag_ambiental,
                P[i].flag_quilombolas,
                P[i].flag_indigenas,
                P[i].flag_infancia,
                P[i].decisao,
                P[i].dt_resolvido,
                P[i].cnm1,
                P[i].primeirasentm1,
                P[i].baixm1,    
                P[i].decm1,
                P[i].mpum1,
                P[i].julgadom1,
                P[i].desm1,
                P[i].susm1
            );
        }
        i++;
    }

    fclose(fp);
    return P;
}