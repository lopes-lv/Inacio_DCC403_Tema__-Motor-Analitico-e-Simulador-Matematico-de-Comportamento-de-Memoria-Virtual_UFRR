# Edge-mem-profiler: Simulador Analítico de Memória Virtual

Bem-vindo ao repositório do **edge-mem-profiler**, um motor analítico e simulador matemático nativo de Unidade de Gerenciamento de Memória (MMU) desenvolvido em C ANSI. 

Este projeto foi desenvolvido como parte dos requisitos da disciplina de Sistemas Operacionais (DCC403) da Universidade Federal de Roraima (UFRR). O objetivo principal da ferramenta é auditar e analisar o comportamento de algoritmos de substituição de páginas sob restrições severas de hardware (focando em arquiteturas de *Edge Computing* e *Edge AI*).

---

## Funcionalidades e Algoritmos Implementados

O simulador processa arquivos de rastro (*logs* de execução) contendo endereços de memória interceptados e avalia a taxa de *Page Faults* (Faltas de Página) operando sob as seguintes políticas de substituição:

* **FIFO (First-In, First-Out):** Substituição baseada na ordem de chegada (complexidade O(1)). Permite a observação empírica da Anomalia de Belady.
* **LRU (Least Recently Used):** Substituição baseada na localidade temporal, eliminando a página não referenciada há mais tempo.
* **Random (Aleatório):** Política base para *benchmarking*, selecionando aleatoriamente o quadro a ser evictado.

A ferramenta é protegida contra vazamentos de memória (0% *memory leak* validado via Valgrind) e extrai o *Virtual Page Number* (VPN) através de operações rápidas de *bitshift* (deslocamento de bits), evitando divisões dispendiosas na CPU.

---

## Pré-requisitos

Para compilar e executar este projeto, você precisará de um ambiente Linux com as seguintes ferramentas instaladas e precisa retirar os arquivos de rastro do zip e deixa-los na pasta principal do projeto sem esta dentro de nenhuma pasta :
* Compilador **GCC**
* Ferramenta **Make**


---

## Como Compilar e Gerenciar o Projeto (Makefile)

Todo o fluxo de compilação, limpeza e automação de testes foi abstraído através do `Makefile` para garantir a reprodutibilidade. No diretório raiz do projeto, abra o terminal e utilize os seguintes comandos de acordo com a sua necessidade:

* **`make`** (ou **`make all`**)
  Invoca o compilador GCC com as *flags* de otimização e avisos estritos (`-Wall -Wextra`), construindo os objetos e gerando o arquivo executável final do simulador de forma limpa.

* **`make run`**
  Executa o simulador utilizando uma configuração e parâmetros de teste padrão pré-definidos no Makefile unica coisa que tera que fazer será escolher a politica que deseja usar (lru,fifo,random). É o comando ideal para verificar rapidamente se a compilação foi bem-sucedida e se o programa está rodando corretamente, poupando o trabalho de digitar todos os argumentos manualmente.

* **`make clean`**
  Realiza a faxina do diretório de trabalho. Ele remove os arquivos objetos (`.o`) gerados durante a compilação e exclui o executável antigo, deixando o repositório pronto para uma nova compilação do zero.

* **`make bateria_test`**
  Dispara o motor de testes automatizados para validação acadêmica. Este comando utiliza laços de repetição nativos do terminal para executar o simulador dezenas de vezes, cruzando automaticamente três tamanhos de página (4 KB, 8 KB e 16 KB) com cinco escalonamentos de memória física (128 KB a 1024 KB) sob as três políticas (FIFO, LRU e Random).
  
## Como Executar

O simulador requer quatro parâmetros obrigatórios via linha de comando:

`./<nome_do_executavel> <algoritmo> <arquivo.log> <tamanho_pagina_KB> <tamanho_memoria_fisica_KB>`

**Exemplo de execução manual:**
Para rodar a política LRU usando páginas de 4 KB em uma memória física de 128 KB contra um log chamado `trace.log`:

`./edge_mem_profiler lru trace.log 4 128`

---

## Automação de Testes (Make)

Para fins de validação científica, o `Makefile` inclui rotinas de automação que executam baterias de testes cruzando múltiplos tamanhos de página e escalonamento de memória.

### 1. Verificar os arquivos de Log
Antes de iniciar os testes automatizados, certifique-se que os rastros sintéticos estão na pasta principal:

```text
trace.log
trace_belady.log
trace_sequencial.log
````

### 2. Rodar a Bateria Completa
Para executar as simulações em lote (variando páginas de 4KB, 8KB, 16KB e memórias de 128KB a 1024KB) para todos os três algoritmos simultaneamente, execute:

`make bateria_test`


---

## Autor

**Inácio Viana**   
*Estudante de Ciência da Computação - UFRR* | [GitHub](https://github.com/lopes-lv)
