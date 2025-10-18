#include <stdio.h>
#include <stdlib.h> 

int gcd(int a, int b) {
    int a_orig = a, b_orig = b;
    a = abs(a);
    b = abs(b);
    
    printf("  Calculando MDC(%d, %d):\n", a, b);
    
    while (b != 0) {
        int temp = b;
        int r = a % b;
        printf("    Passo: %d mod %d = %d\n", a, b, r);
        b = r;
        a = temp;
    }
    printf("    MDC encontrado: %d\n", a);
    return a;
}

int lcm(int a, int b) {
    printf("\nCalculando MMC(%d, %d):\n", a, b);
    
    int mdc_val = gcd(a, b);
    
    if (mdc_val == 0) return 0; 
    
    int mmc_val = (a / mdc_val) * b;
    printf("  -> MMC = (a / MDC) * b = (%d / %d) * %d = %d\n", a, mdc_val, b, mmc_val);
    return mmc_val;
}

int main() {
    int N;
    
    printf("--- Questao 02: Chaves Periodicas ---\n");
    printf("Digite o numero de chaves (N): ");
    scanf("%d", &N);
    
    if (N < 1 || N > 10) {
        printf("Erro: O numero de chaves deve estar entre 1 e 10.\n");
        return 1;
    }

    int cycles[10];
    
    printf("Digite os %d ciclos (separados por espaco): ", N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &cycles[i]);
        if (cycles[i] < 2 || cycles[i] > 20) {
             printf("Erro: O ciclo de cada chave deve estar entre 2 e 20.\n");
             return 1;
        }
    }
    
    int result = cycles[0];
    printf("\n--- Iniciando calculo do MMC total ---\n");
    printf("MMC inicial (ciclo 1): %d\n", result);
    
    for (int i = 1; i < N; i++) {
        result = lcm(result, cycles[i]);
    }
    
    printf("\n--- Resultado Final ---\n");
    printf("O MMC final de todos os ciclos e: %d\n", result);
    
    if (result > 0 && result <= 50) {
        printf("O primeiro ano sincronizado e: %d\n", result);
    } else {
        printf("Impossivel sincronizar as chaves dentro do limite de 50 anos.\n");
    }
    
    return 0;
}