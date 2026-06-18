#include "memoria.h"
#include <stdio.h>


Quadro *init_memoria(unsigned int sizeFis, unsigned int sizePg){
	int tamanho_vetor=sizeFis/sizePg;
	Quadro memoria[tamanho_vetor];

    for(int i=0;i<tamanho_vetor;i++){
        Quadro *quadro=(Quadro*)malloc(sizeof(Quadro));
        


    }

}
