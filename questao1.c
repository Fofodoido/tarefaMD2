long int mdc(long int n, long int m);
long int mod(long int a, long int b);
long int euclidesExt(long int a, long int b, long int *x, long int *y);
long int normalizacao(long int x, long int y);
long int funcao(long int x);
long int pollard(long int n);
long int expoenteE(long int n, long int z_n);
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

long int pollard(long int n){
    long int x0=2;
    long int x1=mod(funcao(x0),n);
    long int x2=mod(funcao(x1),n);
    printf("x1=%ld, x2=%ld\n",x1,x2);
    long int d = mdc(abs(x2 - x1), n);
    long int contador_iteracoes = 0;
    long int limite_maximo = 20000;
    while(d==1){
        if (contador_iteracoes++ > limite_maximo) {
            printf("\nAVISO: Limite de iteracoes atingido. O algoritmo entrou em um ciclo infinito ou e ineficaz para este numero com a semente x0=2.\n");
            return -1;
        }
        printf("Passo: mdc(|%ld-%ld|,%ld)=%ld\n",x2,x1,n,d);
        long int temp = x2;
        x2=mod(funcao(x2),n);
        x1=temp;
        d = mdc(abs(x2 - x1), n);
    }
    printf("Passo: mdc(|%ld - %ld|, %ld) = %ld\n", x1, x2, n, d);
    if (d==n){
        printf("O calculo com a semente x0 = 2 falhou. O enunciado nao pode ser executado de maneira efetiva devido à escolha da semente.");
        return -1;
    }
    return d;
}

int main(){
    long int N1, N2;
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
    return 0;
}