#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[]){

	if(argc !=5){printf("Falta parametros");return 1;}


	//definição dos argv
	int sizePg= atoi(argv[3]);
	char *polisub=argv[1];
	char *arquivo_log=argv[2];
	int sizefis= atoi(argv[4]);
	

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

	while (fscanf(arquivo,"%x %c", &endereco,&operacao)==2){

		//aplicar deslocamento
		unsigned int vpn=endereco >> n;
		
	}

	fclose(arquivo);

	return 0;



}
