#include <stdio.h>
#include <stdlib.h>

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
        r = m % r;
        m = d;
    }
    printf("MDC encontrado: %ld\n", m);
    return m;
}

int main(){
    printf("Rodrigo Henrique Donato de Souza - 241012374\n");
    long int a,c,e,b,d,f,n1,n2,n3;
    printf("Insira os coeficientes a, c, e das equacoes, inserindo espacos entre eles ou colocando o valor e dando enter.\n ax=b mod n1;\n cx=d mod n2;\n ex=f mod n3\n");
    scanf("%ld %ld %ld",&a,&c,&e);
    printf("Insira os coeficientes b, d, f das equacoes inserindo espacos entre eles ou colocando o valor e dando enter.\n ax=b mod n1;\n cx=d mod n2;\n ex=f mod n3\n");
    scanf("%ld %ld %ld",&b,&d,&f);
    printf("Insira os coeficientes n1, n2, n3 das equacoes inserindo espacos entre eles ou colocando o valor e dando enter.\n ax=b mod n1;\n cx=d mod n2;\n ex=f mod n3\n");
    scanf("%ld %ld %ld",&n1,&n2,&n3);
    if (mdc(a,n1)==1 && mdc(c,n2)==1 && mdc(e,n3)==1 && mdc(n1,n2)==1 && mdc(n1,n3)==1 && mdc(n2,n3)==1){
        long int u1 = mod(normalizacao(a,n1)*b,n1);
        long int u2 = mod(normalizacao(c,n2)*d,n2);
        long int u3 = mod(normalizacao(e,n3)*f,n3);
        printf("Equacoes normalizadas:\n \n x=%ld mod %ld;\n x=%ld mod %ld;\n x=%ld mod %ld;\n",b,n1,d,n2,f,n3);
        long int N=n1*n2*n3;
        long int N1=n2*n3, N2=n1*n3, N3=n1*n2;
        printf("Novo sistema a ser resolvido:\n %ldx1=1mod%ld\n %ldx2=1mod%ld\n %ldx3=1mod%ld\n",N1,n1,N2,n2,N3,n3);
        long int x1 =mod(normalizacao(N1,n1),n1);
        long int x2=mod(normalizacao(N2,n2),n2);
        long int x3=mod(normalizacao(N3,n3),n3);
        printf("Resultados:\n x1=%ldmod%ld\n x2=%ldmod%ld\n x3=%ldmod%ld\n",u1,n1,u2,n2,u3,n3);
        printf("Calculando o resultado por meio da equacao x=u mod N...\n u = (u1.x1.N1)+(u2.x2.N2)+(u3.x3.N3)\n");
        long int u = (u1*x1*N1)+(u2*x2*N2)+(u3*x3*N3);
        long int result_x = mod(u,N);
        printf("\nX vai ser igual a %ld com as equacoes dadas\n", result_x);
    }else{
        printf("O teorema chines nao pode ser aplicado");
        return 0;
    }
    return 0;
}
