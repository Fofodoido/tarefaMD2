# Atividade de Matemática Discreta II - Implementações em C

Este repositório contém as implementações em C para a atividade da disciplina de Matemática Discreta II, do curso de Engenharia de Software da Universidade de Brasília (FGA). O projeto aborda a aplicação prática de conceitos de teoria dos números, aritmética modular e criptografia.

## Questões Desenvolvidas

O projeto é composto por 4 questões, cada uma em seu respectivo arquivo:

1.  **Questão 01:** Implementação completa do sistema de criptografia RSA.
2.  **Questão 02:** Solução do problema "Chaves Periódicas".
3.  **Questão 03:** Cálculo da "Razão de Eficiência de um Número".
4.  **Questão 04:** Bônus de preenchimento de código e análise.

-----

### **`questao1.c`** - Sistema de Criptografia RSA

Este programa implementa o sistema criptográfico RSA desde a geração dos fatores primos até a criptografia e descriptografia de uma mensagem.

**Funcionalidades:**

  * **Etapa 1: Fatoração Interativa (Método p de Pollard)**

      * O usuário insere dois números compostos, $N_1$ e $N_2$.
      * O programa utiliza o método **p de Pollard**, com a função de iteração $g(x) = (x^2 + 1) \pmod{N_i}$ e semente $x_0=2$, para encontrar os fatores primos `p` (de $N_1$) e `q` (de $N_2$).
      * Todos os passos da iteração são exibidos.
      * O cálculo do MDC é feito com uma implementação própria do **Algoritmo de Euclides**.

  * **Etapa 2: Geração das Chaves RSA**

      * Calcula o módulo $n = p \times q$ e o totiente de Euler $z(n) = (p-1) \times (q-1)$.
      * Encontra o menor expoente público `E` tal que `mdc(E, z(n)) = 1`.
      * Calcula o expoente privado `D` usando o **Algoritmo Estendido de Euclides** para encontrar o inverso modular de `E`.
      * Exibe a chave pública `(n, e)` e a chave privada `(n, d)`.

  * **Etapa 3: Codificação e Decodificação**

      * Uma mensagem de texto é convertida em números usando a pré-codificação `A=11`, `B=12`, ..., `Z=36`, `Espaço=00`.
      * **Criptografia:** Cada bloco numérico `M` é criptografado via $C \equiv M^E \pmod{n}$.
      * **Descriptografia:** Cada bloco cifrado `C` é descriptografado via $M \equiv C^D \pmod{n}$.
      * A exponenciação modular seleciona automaticamente o método de redução de expoente mais adequado, indicando na saída se o **Teorema de Euler** ou a **Divisão Euclidiana** (exponenciação por quadrados) foi utilizado.
      * Ao final, o programa confirma que a mensagem descriptografada é idêntica à original.

### **`questao2.c`** - Chaves Periódicas

Este programa resolve um problema inspirado no desafio "Cigarras Periódicas". O objetivo é encontrar o primeiro ano, dentro de um limite, em que várias chaves com ciclos de ativação diferentes podem ser usadas simultaneamente. A solução é baseada no cálculo do **Mínimo Múltiplo Comum (MMC)** dos ciclos.

  * **Entrada:** O número de chaves `N` e uma lista com os `N` ciclos de ativação $C_i$.
  * **Objetivo:** Encontrar o primeiro ano $X > 0$ e $X \le 50$ que seja múltiplo de todos os ciclos $C_i$.
  * **Saída:** O primeiro ano sincronizado ou uma mensagem de impossibilidade caso não exista solução no intervalo definido.

### **`questao3.c`** - A Razão de Eficiência de um Número

O programa calcula a "Razão de Eficiência" de um número inteiro `N`, definida como $\frac{\sigma(N)}{\tau(N)}$, onde:

  * $\tau(N)$ é a função que conta o número total de divisores de N.
  * $\sigma(N)$ é a função que calcula a soma de todos os divisores de N.
  * **Entrada:** Um único inteiro $N (1 \le N \le 105)$.
  * **Processo:**
    1.  O número `N` é decomposto em seus fatores primos usando o método de **Trial Division**.
    2.  A partir da fatoração prima, as fórmulas para $\tau(N)$ e $\sigma(N)$ são aplicadas.
    3.  Os passos intermediários do cálculo são exibidos.
  * **Saída:** O valor da Razão de Eficiência com duas casas decimais de precisão.

### **`questao4.txt`** - Bônus: Análise de Código

Este arquivo de texto contém as respostas para a Questão 04, que consiste em:

1.  Completar as linhas de um código em C para que ele realize corretamente o cálculo de uma divisão modular seguida de uma exponenciação.
2.  Analisar o código completo e classificar uma série de afirmativas como Verdadeiro (V) ou Falso (F).

-----

## Como Compilar e Executar

O código foi desenvolvido em C e pode ser compilado com o GCC (GNU Compiler Collection).

```bash
# Para compilar um arquivo específico (ex: questao1.c)
gcc questao1.c -o questao1 -lm

# Para executar o programa
./questao1
```

Repita o processo para as outras questões, substituindo `questao1` por `questao2` ou `questao3`.

## Autores

  * **Nome:** [Rodrigo Henrique Donato de Souza]
  * **Matrícula:** [241012374]
  * **Nome:** [Raphaela Guimarães de Araujo dos Santos]
  * **Matrícula:** [190116072]
