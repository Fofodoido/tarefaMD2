#include <stdio.h>

// Função para calcular o MDC usando o algoritmo de Euclides
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Função para calcular o MMC de dois números
int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}

int main() {
    int N;
    scanf("%d", &N);
    
    int cycles[10];
    for (int i = 0; i < N; i++) {
        scanf("%d", &cycles[i]);
    }
    
    // Calcular o MMC de todos os ciclos
    int result = cycles[0];
    for (int i = 1; i < N; i++) {
        result = lcm(result, cycles[i]);
    }
    
    // Verificar se o resultado está dentro do limite
    if (result > 0 && result <= 50) {
        printf("%d\n", result);
    } else {
        printf("Nao ha ano no limite!\n");
    }
    
    return 0;
}