long int mdc(long int n, long int m);
long int mod(long int a, long int b);
long int euclidesExt(long int a, long int b, long int *x, long int *y);
long int normalizacao(long int x, long int y);
long int funcao(long int x);
long int pollard(long int n);
long int expoenteE(long int n, long int z_n);
int ehPrimo(long int N, int primos[], int num_primos);
int peneira_erastotenes(int limite, int primos[]);
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

long int powMod_com_teoremas(long int base, long int exp, long int mod, long int zn, int primos[], int total_primos) {
    long int exp_original = exp; 
    printf("\n-- Calculando %ld^%ld mod %ld --\n", base, exp_original, mod);
    if (ehPrimo(mod, primos, total_primos)) {
        exp = exp % (mod - 1);
        printf("Aplicado Pequeno Teorema de Fermat. Expoente reduzido para %ld.\n", exp);
    }
    else if (mdc(base, mod) == 1) {
        exp = exp % zn;
        printf("Aplicado Teorema de Euler. Expoente reduzido para %ld.\n", exp);
    }
    else {
        printf("Condicoes de Fermat/Euler nao atendidas. Usando Exponenciacao por Quadrados com expoente original.\n");
    }
    long long res = 1;
    long long b = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1) {
            res = (res * b) % mod;
        }
        exp = exp / 2;
        b = (b * b) % mod;
    }
    printf("Resultado: %ld\n", (long int)res);
    return (long int)res;
}

int peneira_erastotenes(int limite, int primos[]) {
    char is_prime[limite + 1];
    for (int i = 0; i <= limite; i++) {
        is_prime[i] = 1;
    }
    is_prime[0] = is_prime[1] = 0;

    for (int p = 2; p * p <= limite; p++) {
        if (is_prime[p] == 1) {
            for (int i = p * p; i <= limite; i += p) {
                is_prime[i] = 0;
            }
        }
    }

    int contador = 0;
    for (int p = 2; p <= limite; p++) {
        if (is_prime[p] == 1) {
            primos[contador++] = p;
        }
    }
    return contador;
}

int ehPrimo(long int N, int primos[], int num_primos) {
    if (N <= 1) return 0;
    if (N <= 3) return 1;
    if (N % 2 == 0 || N % 3 == 0) return 0;
    long int limite = (long int)sqrt(N);
    for (int i = 0; i < num_primos; i++) {
        int d = primos[i];
        if (d > limite) {
            break;
        }
        if (N % d == 0) {
            return 0;
        }
    }
    return 1;
}

long int mod(long int a, long int b) {
    //implementa de maneira simples o calculo de mod com valores positivos ou negativos
    if (b < 0) {
        b = -b;
    }
    long int r = a % b;
    if (r < 0) {
        return r + b;
    } else {
        return r;
    }
}


long int mdc(long int n, long int m){
    n = abs(n);
    m = abs(m);
    if (m == 0) {
        printf("MDC encontrado: %ld\n", n);
        return n;
    }
    if (n < m){
        return mdc(m, n);
    }
    printf("Iniciando mdc(%ld, %ld)\n", n, m);
    long int d, r = n % m;
    printf("Passo: %ld mod %ld = %ld\n", n, m, r);
    while (r != 0){
        d = r;
        printf("Passo: %ld mod %ld = %ld\n",m,r,m%r);
        r = m % r;
        m = d;
    }
    printf("MDC encontrado: %ld\n", m);
    return m;
}

long int expoenteE(long int n, long int z_n){
    printf("Calculando os numeros E>1 e E<n tal que mdc(z(n),E)=1");
    for(long int i =2; i<n;i++){
        if (mdc(z_n,i)==1){ 
            printf("Menor expoente E encontrado. E=%ld", i);
            return i;
        }
    }
    printf("Nenhum expoente Encontrado.");
    return -1;
}

long int euclidesExt(long int a, long int b, long int *x, long int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    long int x1, y1;
    long int d = euclidesExt(b, a % b, &x1, &y1); //usa de modo recursivo a função até encontrar o caso base, retornando assim os coeficientes
    *x = y1;
    *y = x1 - y1 * (a / b);
    return d;
}

long int normalizacao(long int x, long int y){
    //código que normaliza os coeficientes da equação inicial do teorema chinês
    printf("executando o algoritmo de euclides extendido e normalizando as equacoes.\n");
    long int cx,cy; // coeficientes que acompanham x e y ao final da execução do algoritmo extendido
    long int numero = euclidesExt(x,y,&cx,&cy);
    if (numero!=1){
        return -1;
    }
    cx = mod(cx,y);
    return cx;
}

long int funcao(long int x){
    return (x*x)+1;
}

long int pollard(long int n) {
    printf("\n--- Tentando fatorar %ld com semente x0 = 2 ---\n", n);
    long int x0 = 2;
    long int x1 = mod(funcao(x0), n);
    long int x2 = mod(funcao(x1), n);
    printf("x1=%ld, x2=%ld\n", x1, x2);
    long int d = mdc(abs(x2 - x1), n);
    long int contador_iteracoes = 0;
    long int limite_maximo = 20000;

    while (d == 1) {
        if (contador_iteracoes++ > limite_maximo) {
            printf("\nAVISO: Limite de iteracoes atingido com semente x0=2.\n");
            goto TENTATIVA_SEMENTE_3;
        }
        printf("Passo: mdc(|%ld-%ld|,%ld)=%ld\n", x2, x1, n, d);
        long int temp = x2;
        x2 = mod(funcao(x2), n);
        x1 = temp;
        d = mdc(abs(x2 - x1), n);
    }
    printf("Passo: mdc(|%ld - %ld|, %ld) = %ld\n", x1, x2, n, d);
    if (d != n) {
        return d;
    }
    printf("O calculo com a semente x0 = 2 falhou.\n");

TENTATIVA_SEMENTE_3:
    printf("\n--- Tentando fatorar %ld com semente x0 = 3 ---\n", n);
    x0 = 3; // Nova semente
    x1 = mod(funcao(x0), n);
    x2 = mod(funcao(x1), n);
    printf("x1=%ld, x2=%ld\n", x1, x2);
    d = mdc(abs(x2 - x1), n);
    contador_iteracoes = 0; 

    while (d == 1) {
        if (contador_iteracoes++ > limite_maximo) {
            printf("\nAVISO: Limite de iteracoes atingido com semente x0=3.\n");
            goto TENTATIVA_SEMENTE_5; 
        }
        printf("Passo: mdc(|%ld-%ld|,%ld)=%ld\n", x2, x1, n, d);
        long int temp = x2;
        x2 = mod(funcao(x2), n);
        x1 = temp;
        d = mdc(abs(x2 - x1), n);
    }
    printf("Passo: mdc(|%ld - %ld|, %ld) = %ld\n", x1, x2, n, d);
    if (d != n) {
        return d; 
    }
    printf("O calculo com a semente x0 = 3 falhou.\n");

TENTATIVA_SEMENTE_5:
    printf("\n--- Tentando fatorar %ld com semente x0 = 5 ---\n", n);
    x0 = 5;
    x1 = mod(funcao(x0), n);
    x2 = mod(funcao(x1), n);
    printf("x1=%ld, x2=%ld\n", x1, x2);
    d = mdc(abs(x2 - x1), n);
    contador_iteracoes = 0; 

    while (d == 1) {
        if (contador_iteracoes++ > limite_maximo) {
            printf("\nAVISO: Limite de iteracoes atingido com semente x0=5.\n");
            goto FALHA_TOTAL; 
        }
        printf("Passo: mdc(|%ld-%ld|,%ld)=%ld\n", x2, x1, n, d);
        long int temp = x2;
        x2 = mod(funcao(x2), n);
        x1 = temp;
        d = mdc(abs(x2 - x1), n);
    }
    printf("Passo: mdc(|%ld - %ld|, %ld) = %ld\n", x1, x2, n, d);
    if (d != n) {
        return d; 
    }

FALHA_TOTAL:
    printf("\nO algoritmo de Pollard falhou para N=%ld com todas as sementes testadas.\n", n);
    return -1;
}

int main(){
    printf("Rodrigo Henrique Donato de Souza - 241012374\n");
    printf("Raphaela Guimarães de Araujo dos Santos - 190116072\n");
    int limite = 100;
    int primos_encontrados[100];
    int total_primos;
    printf("Descobrindo os numeros primos ate %d (como o limite e 9999, esses sao todos que precisamos)\n", limite);
    total_primos = peneira_erastotenes(limite, primos_encontrados);
    printf("Foram encontrados %d primos.\n", total_primos);
    printf("A lista de primos e:\n");
    for (int i = 0; i < total_primos; i++) {
        printf("%d ", primos_encontrados[i]);
    }
    printf("\n");
    long int N1, N2;
    char mensagem_texto[256];
    long int mensagem_numerica[256];
    int tamanho_mensagem = 0;
    printf("Etapa 1\n");
    printf("Insira dois numeros compostos N1 e N2, N1 diferente de N2 e 100 <N<9999, dando espaco ou enter apos cada numero:\n");
    printf("O numero tem que ser um produto de primos distintos.\n");
    scanf("%ld %ld",&N1, &N2);
    printf("A funcao que sera utilizada sera f(x)=(x^2)+1, com semente x0=2\n");
    printf("Calculando o Pollard de %ld\n",N1);
    long int p=pollard(N1);
    if (p == -1) {
        printf("Nao foi possivel fatorar N2. Encerrando o programa.\n");
        return 1; 
    }
    printf("p=%ld\n",p);
    printf("Calculando o Pollard de %ld\n",N2);
    long int q=pollard(N2);
    if (q == -1) {
        printf("Nao foi possivel fatorar N2. Encerrando o programa.\n");
        return 1; 
    }
    printf("Etapa 2\n");
    printf("q=%ld\n",q);
    long int modulo=p*q;
    long int zn=(p-1)*(q-1);
    long int expPub=expoenteE(modulo,zn);
    if (expPub==-1){
        printf("Nao foi possivel encontrar um expoente valido\n");
        return  -1;
    }
    long int expPri = normalizacao(expPub,zn);
    printf("Chave Publica: (%ld,%ld)\nChave Privada: (%ld,%ld)\n",modulo,expPub,modulo,expPri);
    printf("Etapa 3\n");
    printf("Insira a mensagem que voce quer que seja criptografada:\n");
    scanf(" %[^\n]", mensagem_texto);
    printf("Convertendo a mensagem para numeros (Pre-codificacao)...\n");
    for (int i = 0; i < strlen(mensagem_texto); i++){
        char caractere_atual = mensagem_texto[i];
        long int valor_numerico;
        if (caractere_atual >= 'A' && caractere_atual <= 'Z'){
            valor_numerico = caractere_atual - 'A' + 11;
        }else if(caractere_atual == ' '){
            valor_numerico = 0;
        }else{
            continue; 
        }
        mensagem_numerica[tamanho_mensagem] = valor_numerico;
        if (valor_numerico == 0){
            printf("Caractere '%c' -> Numero %02ld\n", caractere_atual, valor_numerico);
        }else{
            printf("Caractere '%c' -> Numero %ld\n", caractere_atual, valor_numerico);
        }
        tamanho_mensagem++;
    }
    long int mensagem_criptografada[256];
    printf("\nCriptografando a mensagem com a Chave Publica (%ld, %ld)...\n", modulo, expPub);
    for (int i = 0; i < tamanho_mensagem; i++) {
        long int M = mensagem_numerica[i];
        long int C = powMod_com_teoremas(M, expPub, modulo, zn, primos_encontrados, total_primos);
        mensagem_criptografada[i] = C;
    }
    printf("\nMensagem criptografada (sequencia de numeros C):\n");
    for (int i = 0; i < tamanho_mensagem; i++) {
        printf("%ld ", mensagem_criptografada[i]);
    }
    printf("\n");
    char mensagem_descriptografada[256];
    printf("\nDescriptografando a mensagem com a Chave Privada (%ld, %ld)...\n", modulo, expPri);
    for (int i = 0; i < tamanho_mensagem; i++) {
        long int C = mensagem_criptografada[i];
        long int M_decifrado = powMod_com_teoremas(C, expPri, modulo, zn, primos_encontrados, total_primos);
        char caractere_decifrado;
        if (M_decifrado >= 11 && M_decifrado <= 36) {
            caractere_decifrado = M_decifrado - 11 + 'A';
        } else if (M_decifrado == 0) {
            caractere_decifrado = ' ';
        } else {
            caractere_decifrado = '?';
        }
        mensagem_descriptografada[i] = caractere_decifrado;
    }
    mensagem_descriptografada[tamanho_mensagem] = '\0';

    printf("\n--- Verificacao Final ---\n");
    printf("Mensagem Original:       %s\n", mensagem_texto);
    printf("Mensagem Descriptografada: %s\n", mensagem_descriptografada);

    if (strcmp(mensagem_texto, mensagem_descriptografada) == 0) {
        printf("\nConfirmado: A mensagem decifrada e identica a mensagem original.\n");
    } else {
        printf("\nErro: A mensagem decifrada e diferente da mensagem original.\n");
    }
    return 0;
}
