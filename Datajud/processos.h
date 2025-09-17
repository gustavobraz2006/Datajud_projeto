#ifndef PROCESSOS_H
#define PROCESSOS_H

typedef struct {
    int id_processo;
    char numero_sigilo[50];
    char sigla_grau[10];
    char procedimento[100];
    char ramo_justica[50];
    char sigla_tribunal[10];
    int id_tribunal;
    int recurso;
    int id_ultimo_oj;
    char dt_recebimento[11];   // formato YYYY-MM-DD
    int id_ultima_classe;

    // Flags (0 ou 1)
    int flag_violencia_domestica;
    int flag_feminicidio;
    int flag_ambiental;
    int flag_quilombolas;
    int flag_indigenas;
    int flag_infancia;

    char decisao[20];               // inteiro no CSV, mas eu manti como uma string 
    char dt_resolvido[11];     // formato YYYY-MM-DD

    // Campos extras
    int cnm1;
    int primeirasentm1;
    int baixm1;
    int decm1;
    int mpum1;
    int julgadom1;
    int desm1;
    int susm1;

} Processos;

// Funções
Processos * LerDadosProcessos(char * NomeArquivo);
int getnumProcessos (Processos * P);
int getUltimoOrgaoJulgador(Processos * P, int id_processo);
int getidprocessoMaisAntigo (Processos * P);
int getviolenciadomestica (Processos * P);
int getfeminicidios (Processos * P);
int getambientais (Processos * P);
int getquilombolas (Processos * P);
int getindigenas (Processos * P);
int getinfancia (Processos * P);
int getDiasEntreDatas(const char * dt_recebimento, const char * dt_resolvido);
float getcumprimentoMeta1(Processos * P);
Processos * gerarCSVMeta1julgados(Processos * P, const char * NomeArquivoSaida);

#endif
