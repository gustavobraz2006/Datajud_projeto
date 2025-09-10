## Projeto: Análise de Processos Judiciais

Este projeto em C foi desenvolvido para **ler, analisar e gerar estatísticas** a partir de um arquivo CSV de processos judiciais (exemplo: `TJDFT_filtrado.csv`).  

O objetivo é extrair informações como:  
- Número total de processos;  
- Processos por categoria (violência doméstica, feminicídio, ambiental, etc.);  
- Identificação do processo mais antigo;  
- Dias entre o recebimento e a resolução de um processo;  
- Percentual de cumprimento da **Meta 1 do CNJ**;  
- Geração de um novo CSV apenas com os processos julgados na Meta 1.  

---
##  Estrutura do Projeto

.
├── main.c # Arquivo principal: chama as funções e imprime resultados
├── processos.c # Implementação das funções que manipulam os dados
├── processos.h # Cabeçalho com definições da struct e protótipos de funções
└── TJDFT_filtrado.csv # Arquivo de entrada (não incluído no repositório)

##  Como funciona

1. **Leitura dos dados (`LerDadosProcessos`)**  
   - O programa lê o CSV linha por linha e armazena as informações em um vetor de structs `Processos`.  

2. **Funções de análise**  
   - `getnumProcessos` → Conta quantos processos foram carregados.  
   - `getviolenciadomestica`, `getfeminicidios`, `getambientais`, `getquilombolas`, `getindigenas`, `getinfancia` → Contam processos específicos de cada categoria.  
   - `getidprocessoMaisAntigo` → Encontra o ID do processo mais antigo com base na data de recebimento.  
   - `getDiasEntreDatas` → Calcula o número de dias entre o recebimento e a resolução.  
   - `getcumprimentoMeta1` → Calcula o percentual de processos julgados dentro da Meta 1.  

3. **Geração de CSV (`gerarCSVMeta1julgados`)**  
   - Cria um novo arquivo CSV contendo apenas os processos julgados da Meta 1.  

---

## OBSERVAÇÃO!!
 -   O CSV de entrada deve estar no formato correto, com os campos separados por ;.

## Exemplo de Saída

-Numero de processos: 15230
-Numero de processos com violência doméstica: 230
-Numero de processos com feminicídio: 12
-Numero de processos ambientais: 85
-Numero de processos com comunidades quilombolas: 3
-Numero de processos com comunidades indígenas: 9
-Numero de processos com crimes contra a infância: 45
-id do processo mais antigo: 123456
-Numero de dias entre a data de recebimento e a data resolvida do processo mais antigo: 320
-Percentual de cumprimento da Meta 1: 78.52%
