# Nome do compilador
CC = gcc

# Flags do compilador (exibe todos os alertas de seguranca)
CFLAGS = -Wall

# Nome do seu arquivo executavel final
TARGET = edge-profiler

# Regra padrao executada quando se digita apenas "make"
all: $(TARGET)

# Regra para compilar o projeto unindo os arquivos .c
$(TARGET): main.c memoria.c
	$(CC) $(CFLAGS) main.c memoria.c -o $(TARGET)

# --------------------------------------------------------------------
# 1. REGRA INTERATIVA (RUN)
# --------------------------------------------------------------------
run: $(TARGET)
	@read -p "Qual politica de substituicao deseja usar (lru, fifo, random)? " pol; \
	echo "\n>>> Executando $$pol com paginas de 4KB e memoria de 512KB..."; \
	./$(TARGET) $$pol trace.log 4 512

# --------------------------------------------------------------------
# 2. BATERIA DE TESTES UNIFICADA (ARTIGO SBC)
# --------------------------------------------------------------------
bateria_test: $(TARGET)
	@echo "=================================================="
	@echo "   BATERIA UNIFICADA - ARTIGO SBC (PARETO 80/20)  "
	@echo "=================================================="
	@for pol in fifo lru random; do \
		for mem in 128 256 512 768 1024; do \
			echo "\n>>> Politica: $$pol | Pagina: 4KB | Memoria Fisica: $$mem KB"; \
			./$(TARGET) $$pol trace.log 4 $$mem; \
		done; \
	done
	@echo "\n=================================================="
	@echo "             BATERIA DE TESTES CONCLUIDA!         "
	@echo "=================================================="

# --------------------------------------------------------------------
# 3. TESTE DA ANOMALIA DE BELADY (FIFO vs LRU)
# --------------------------------------------------------------------
test_belady: $(TARGET)
	@echo "=================================================="
	@echo "       FORCANDO A ANOMALIA DE BELADY (FIFO)       "
	@echo "=================================================="
	@echo "\n[FIFO] >>> Cenario 1: 3 Quadros (12 KB)"
	@./$(TARGET) fifo trace_belady.log 4 12
	@echo "\n[FIFO] >>> Cenario 2: 4 Quadros (16 KB) -> Anomalia Ocorre!"
	@./$(TARGET) fifo trace_belady.log 4 16
	@echo "\n=================================================="
	@echo "     PROVANDO A IMUNIDADE DO LRU (SEM ANOMALIA)   "
	@echo "=================================================="
	@echo "\n[LRU] >>> Cenario 1: 3 Quadros (12 KB)"
	@./$(TARGET) lru trace_belady.log 4 12
	@echo "\n[LRU] >>> Cenario 2: 4 Quadros (16 KB) -> Logica Restaurada!"
	@./$(TARGET) lru trace_belady.log 4 16

# --------------------------------------------------------------------
# 4. TESTE DE INUNDACAO SEQUENCIAL
# --------------------------------------------------------------------
test_sequencial: $(TARGET)
	@echo "=================================================="
	@echo "   INUNDACAO SEQUENCIAL (COLAPSO DE LRU E FIFO)   "
	@echo "=================================================="
	@echo "\n>>> Testando FIFO..."
	@./$(TARGET) fifo trace_sequencial.log 16 512
	@echo "\n>>> Testando LRU..."
	@./$(TARGET) lru trace_sequencial.log 16 512


# --------------------------------------------------------------------
# LIMPEZA E AUDITORIA
# --------------------------------------------------------------------
clean:
	rm -f $(TARGET)

valgrind: $(TARGET)
	@echo "Iniciando auditoria profunda de memoria com Valgrind..."
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET) lru trace.log 4 1024
