#include "memoria.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


int tamanho_vetor;

Quadro *init_memoria(unsigned int sizeFis, unsigned int sizePg){

    tamanho_vetor=sizeFis / sizePg;
    Quadro *memoria=(Quadro*)calloc(tamanho_vetor,sizeof(Quadro));
    return memoria;
}



void processamento_memoria(unsigned int vpn, char operacao, Quadro memoria[],int relogio,char *polisub, unsigned long *evictadas,unsigned long *page_faults){


    int encontro=0;
    for(int i=0;i<tamanho_vetor;i++){

        //page hit
        if(vpn == memoria[i].vpn && memoria[i].ocupado ==1){
            encontro=1;
            memoria[i].tempo_uso=relogio;
            if(operacao == 'W'){
                memoria[i].suja=1;
            }
            break;
        }
    }
    if (encontro == 0){
        //page fault
        (*page_faults)++;
        int bit_enc=0;
        for(int j=0;j<tamanho_vetor;j++){
            //caso da memoria esta com espaço
            if(memoria[j].ocupado==0){
                bit_enc=1;
                memoria[j].vpn=vpn;
                memoria[j].ocupado=1;
                memoria[j].tempo_uso=relogio;
                memoria[j].tempo_carga=relogio;
                if(operacao=='W'){
                    memoria[j].suja=1;
                }else{memoria[j].suja=0;}
                break;
            }
        }
        //implementar o caso da memoria esta cheia
        if(bit_enc==0){
            //FIFO
            if(strcmp(polisub, "fifo")==0){
                    int menor=memoria[0].tempo_carga;
                    int pos=0;
                    for(int k=0;k<tamanho_vetor;k++){
                        if(memoria[k].tempo_carga<menor){
                            menor=memoria[k].tempo_carga;
                            pos=k;
                        }
                    }
                    if(memoria[pos].suja==1){ (*evictadas)++;}
                    memoria[pos].vpn=vpn;
                    memoria[pos].suja=(operacao== 'W')? 1:0;
                    memoria[pos].tempo_carga=relogio;
                    memoria[pos].tempo_uso=relogio;


            }else if(strcmp(polisub, "lru")==0){
                //LRU
                int menor=memoria[0].tempo_uso;
                int pos=0;
                for(int k=0;k<tamanho_vetor;k++){
                    if(memoria[k].tempo_uso<menor){
                        menor=memoria[k].tempo_uso;
                        pos=k;
                    }
                }
                if(memoria[pos].suja==1){ (*evictadas)++;}
                memoria[pos].vpn=vpn;
                memoria[pos].suja=(operacao=='W')? 1:0;
                memoria[pos].tempo_carga=relogio;
                memoria[pos].tempo_uso=relogio;

            }else if(strcmp(polisub,"random")==0){
                //Random
                int pos_ale=rand() % tamanho_vetor;
                if(memoria[pos_ale].suja==1){ (*evictadas)++;}
                memoria[pos_ale].vpn=vpn;
                memoria[pos_ale].suja=(operacao=='W')? 1:0;
                memoria[pos_ale].tempo_carga=relogio;
                memoria[pos_ale].tempo_uso=relogio;
            }

        }
    }
}
