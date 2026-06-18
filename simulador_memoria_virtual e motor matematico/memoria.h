typedef struct Quadro{
	unsigned int vpn;
	int ocupado;
	int suja;
	unsigned int tempo_uso;
	unsigned int tempo_carga;
} Quadro;


void processamento_memoria(unsigned int vpn, char operacao);

Quadro *init_memoria(unsigned int sizeFis, unsigned int sizePg);
