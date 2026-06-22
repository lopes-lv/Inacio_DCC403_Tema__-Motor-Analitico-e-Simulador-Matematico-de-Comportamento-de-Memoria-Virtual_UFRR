# Nome do compilador1
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

test_lru: $(TARGET)
	@echo "=================================================="
	@echo "   INICIANDO DE TESTES DE MEMORIA- LRU        "
	@echo "=================================================="
	@echo "\n>>> TESTE 1: Analise de Desempenho - 4KB"
	@./$(TARGET) lru trace.log 4 1024
	@echo "\n>>> TESTE 2: Analise de Desempenho - 8KB"
	@./$(TARGET) lru trace.log 8 1024
	@echo "\n>>> TESTE 3: Analise de Desempenho - 16KB"
	@./$(TARGET) lru trace.log 16 1024
	@echo "           \nBATERIA DE TESTES CONCLUIDA!           "
	
test_fifo: $(TARGET)
	@echo "=================================================="
	@echo "   INICIANDO DE TESTES DE MEMORIA- FIFO        "
	@echo "=================================================="
	@echo "\n>>> TESTE 1: Analise de Desempenho - 4KB"
	@./$(TARGET) fifo trace.log 4 1024
	@echo "\n>>> TESTE 2: Analise de Desempenho - 8KB"
	@./$(TARGET) fifo trace.log 8 1024
	@echo "\n>>> TESTE 3: Analise de Desempenho - 16KB"
	@./$(TARGET) fifo trace.log 16 1024
	@echo "           \nBATERIA DE TESTES CONCLUIDA!           "

test_random: $(TARGET)
	@echo "=================================================="
	@echo "   INICIANDO DE TESTES DE MEMORIA- RANDOM        "
	@echo "=================================================="
	@echo "\n>>> TESTE 1: Analise de Desempenho - 4KB"
	@./$(TARGET) random trace.log 4 1024
	@echo "\n>>> TESTE 2: Analise de Desempenho - 8KB"
	@./$(TARGET) random trace.log 8 1024
	@echo "\n>>> TESTE 3: Analise de Desempenho - 16KB"
	@./$(TARGET) random trace.log 16 1024
	@echo "           \nBATERIA DE TESTES CONCLUIDA!           "


test_belady: $(TARGET)
	@echo "=================================================="
	@echo "       FORCANDO A ANOMALIA DE BELADY (FIFO)       "
	@echo "=================================================="
	@echo "\n>>> Cenario 1: Memoria FISICA PEQUENA (3 Quadros / 12 KB)"
	@./$(TARGET) fifo trace_belady.log 4 12
	@echo "\n>>> Cenario 2: Memoria FISICA MAIOR (4 Quadros / 16 KB)"
	@./$(TARGET) fifo trace_belady.log 4 16
	@echo "\n=================================================="
	@echo "   Observe o paradoxo nos resultados acima:"
	@echo "   Mais capacidade de memoria = Mais Page Faults!"
	@echo "=================================================="

test_belady_lru: $(TARGET)
	@echo "=================================================="
	@echo "     PROVANDO A IMUNIDADE DO LRU (SEM ANOMALIA)   "
	@echo "=================================================="
	@echo "\n>>> Cenario 1: Memoria FISICA PEQUENA (3 Quadros / 12 KB)"
	@./$(TARGET) lru trace_belady.log 4 12
	@echo "\n>>> Cenario 2: Memoria FISICA MAIOR (4 Quadros / 16 KB)"
	@./$(TARGET) lru trace_belady.log 4 16
	@echo "\n=================================================="
	@echo "   Observe a logica restaurada:"
	@echo "   Mais memoria = Menos Page Faults (Como deve ser!)"
	@echo "=================================================="

# Regra para limpar o diretorio (apaga o executavel)
clean:
	rm -f $(TARGET)

# Regra para auditar vazamentos de memoria no código (Requer Valgrind)
valgrind: $(TARGET)
	@echo "Iniciando auditoria profunda de memoria com Valgrind..."
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET) lru trace.log 4 1024
