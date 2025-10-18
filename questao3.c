#include <stdio.h>
#include <math.h>
#include <stdlib.h> // Para abs()

int main() {
    int N;

    printf("--- Questao 03: Razao de Eficiencia ---\n");
    printf("Digite um numero N (entre 1 e 105): ");
    scanf("%d", &N);

    if (N < 1 || N > 105) {
         printf("Erro: N deve estar no intervalo [1, 105].\n");
         return 1;
    }
    
    printf("\n--- Passo 1: Fatoracao Prima de %d ---\n", N);
    
    int fatores[100];
    int expoentes[100];
    int idx = 0;
    int temp = N;
    
    if (N == 1) {
        fatores[idx] = 1;
        expoentes[idx] = 1;
        idx++;
    } else {
        for (int p = 2; p * p <= temp; p++) {
            if (temp % p == 0) {
                int expoente = 0;
                while (temp % p == 0) {
                    expoente++;
                    temp /= p;
                }
                fatores[idx] = p;
                expoentes[idx] = expoente;
                idx++;
            }
        }
        if (temp > 1) {
            fatores[idx] = temp;
            expoentes[idx] = 1;
            idx++;
        }
    }
    
    for (int i = 0; i < idx; i++) {
        printf("Fator: %d, Expoente: %d\n", fatores[i], expoentes[i]);
    }
    
    printf("\n--- Passo 2: Calculo de tau(N) e sigma(N) ---\n");
    
    int tau = 1;
    for (int i = 0; i < idx; i++) {
        tau *= (expoentes[i] + 1);
    }
    printf("Calculo intermediario tau(%d) = %d\n", N, tau);
    
    int sigma = 1;
    for (int i = 0; i < idx; i++) {
        int p = fatores[i];
        int exp = expoentes[i];
        int soma = 1;
        int potencia = 1;
        for (int j = 0; j < exp; j++) {
            potencia *= p;
            soma += potencia;
        }
        sigma *= soma;
    }
    printf("Calculo intermediario sigma(%d) = %d\n", N, sigma);
    
    printf("\n--- Passo 3: Calculo da Razao de Eficiencia ---\n");
    
    double razao = (double)sigma / tau;
    printf("Razao = sigma(N) / tau(N) = %d / %d\n", sigma, tau);
    printf("Resultado final (com duas casas decimais): %.2f\n", razao);
    
    return 0;
}