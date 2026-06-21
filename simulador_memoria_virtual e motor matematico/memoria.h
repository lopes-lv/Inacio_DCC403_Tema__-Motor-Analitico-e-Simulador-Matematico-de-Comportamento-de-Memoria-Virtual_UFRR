#ifndef MEMORIA_H
#define MEMORIA_H



typedef struct Quadro{
	unsigned int vpn; // numero da page
	int ocupado; // para dizer se esta com page ou não 
	int suja; // para dizer se a page foi modificada 
	unsigned int tempo_uso; // tempo de uso para o LRU
	unsigned int tempo_carga; // quem entrou primero
} Quadro;


void processamento_memoria(unsigned int vpn, char operacao, Quadro memoria[], int relogio, char *polisub, unsigned long *evictadas, unsigned long *page_faults);

Quadro *init_memoria(unsigned int sizeFis, unsigned int sizePg);

#endif
