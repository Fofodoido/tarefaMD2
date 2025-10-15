#include <stdio.h>
#include <stdlib.h>

int normalizacao(int x,int y){
    if (x%){
        
    }
    
}

int mdc(int n, int m){
    n=abs(n);
    m=abs(m);
    int d,r=n%m;
    if (n<m){
        return mdc(m,n);
    }
    
    while (r!=0){
        d=r;
        r=m%r;
        m=d;
    }
    return m;
}

int main(){
    long int a,c,e,b,d,f,n1,n2,n3;
    printf("Insira os coeficientes a, c, e das equacoes, inserindo espacos entre eles ou colocando o valor e dando enter.\n ax=b mod n1;\n cx=d mod n2;\n ex=f mod n3\n");
    scanf("%ld %ld %ld",&a,&c,&e);
    printf("Insira os coeficientes b, d, f das equacoes inserindo espacos entre eles ou colocando o valor e dando enter.\n ax=b mod n1;\n cx=d mod n2;\n ex=f mod n3\n");
    scanf("%ld %ld %ld",&b,&d,&f);
    printf("Insira os coeficientes n1, n2, n3 das equacoes inserindo espacos entre eles ou colocando o valor e dando enter.\n ax=b mod n1;\n cx=d mod n2;\n ex=f mod n3\n");
    scanf("%ld %ld %ld",&n1,&n2,&n3);
    if (mdc(a,n1)==1 && mdc(c,n2)==1 && mdc(e,n3)==1 && mdc(n1,n2)==1 && mdc(n1,n3)==1 && mdc(n2,n3)==1){
        int N=n1*n2*n3;
        
    }else{
        printf("O teorema chines nao pode ser aplicado");
        return 0;
    }
    return 0;
}
