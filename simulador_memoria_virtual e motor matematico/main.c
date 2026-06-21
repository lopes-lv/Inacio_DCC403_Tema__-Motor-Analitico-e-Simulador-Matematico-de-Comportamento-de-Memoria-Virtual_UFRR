#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "memoria.h"


int main(int argc, char *argv[]){

	if(argc !=5){printf("Falta parametros");return 1;}

    srand(time(NULL));


	//definição dos argv
	int sizePg= atoi(argv[3]);
	char *polisub=argv[1];
	char *arquivo_log=argv[2];
	int sizeFis= atoi(argv[4]);
	

	// definição das variaveis 
	unsigned int endereco;
	char operacao;
	//abrindo arquivo
	FILE *arquivo=fopen(arquivo_log,"r");

	// calculando log
	unsigned int n=0;
	unsigned int log=sizePg*1024;

	while (log>1){
		log=log/2;
		n++;
	}

	if(arquivo==NULL){ printf("Erro ao abrir o arquivo\n"); return 1;}

    int relogio=0;
    unsigned long paginas_sujas_evictadas=0;
    unsigned long page_faults=0;

    Quadro *memoria=init_memoria(sizeFis,sizePg);

	while (fscanf(arquivo,"%x %c", &endereco,&operacao)==2){

		//aplicar deslocamento
		unsigned int vpn=endereco >> n;

        processamento_memoria(vpn,operacao,memoria,relogio,polisub, &paginas_sujas_evictadas,&page_faults);
		
                       
		
	}

	fclose(arquivo);

    printf("Executando Edge-AI Memory Perfomance Profile\n");
    printf("==============================================\n");
    printf("Tecnica de Reposicao (Polisub) : %s\n", polisub);
    printf("Arquivo de Traco Processado : %s\n", arquivo_log);
    printf("Tamanho de cada Paginas/Quadro : %d KB\n", sizePg);
    printf("Capacide de Memoria Fisica : %d KB\n", sizeFis);
    printf("Resultados da simulacao\n");
    printf("Total de Acesso Computados : %d\n", relogio);
    printf("Ocorrencias de Page Faults (Lidas) : %lu\n", page_faults);
    printf("Paginas sujas evictadas (Escritas) : %lu\n", paginas_sujas_evictadas);
    printf("Simulacao Conccluidas com sucesso\n");

    free(memoria);


	return 0;



}
