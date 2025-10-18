#include <stdio.h>
#include <math.h>

int main() {
    int N;
    scanf("%d", &N);
    
    printf("Fatoracao de %d:\n", N);
    
    int fatores[100]; // Armazena os fatores primos
    int expoentes[100]; // Armazena os expoentes
    int idx = 0; // Índice para os fatores
    int temp = N;
    
    // Caso especial para N = 1
    if (N == 1) {
        fatores[idx] = 1;
        expoentes[idx] = 1;
        idx++;
    } else {
        // Fatoração por Trial Division
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
    
    // Imprime fatores primos e expoentes
    for (int i = 0; i < idx; i++) {
        printf("Primeiro: %d, Expoente: %d\n", fatores[i], expoentes[i]);
    }
    
    // Cálculo de τ(N)
    int tau = 1;
    for (int i = 0; i < idx; i++) {
        tau *= (expoentes[i] + 1);
    }
    printf("tau(%d) = %d\n", N, tau);
    
    // Cálculo de σ(N)
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
    printf("sigma(%d) = %d\n", N, sigma);
    
    // Cálculo da Razão de Eficiência
    double razao = (double)tau / sigma;
    printf("Razao de Eficiencia: %.2f\n", razao);
    
    return 0;
}