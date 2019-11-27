#include <stdio.h>
#include <stdlib.h>

typedef struct no
{   int tam;
	char* chave;
	float freq;
	struct no *esq, *dir;
	struct no *prox;
}   HUFFNo;

typedef struct NO{
    int cod;
    struct NO *prox;
}lista;

void pushi(lista **L, int c){
    lista *a;
    a = (lista*)malloc(sizeof(lista));
    a->cod = c;
    a->prox = NULL;
    if((*L) == NULL){
        (*L) = a;
    }
    else{
        lista *aux = (*L);
        while(aux->prox){
            aux = aux->prox;
        }
        aux->prox = a;
    }
}

void criaarv(float *freq,char *nos,HUFFNo **h,int tam){
    for(int i=0;i<tam;i++){
    HUFFNo* novo=(HUFFNo*)malloc(sizeof(HUFFNo));
    novo->chave=(char*)malloc(sizeof(char*));
    novo->chave[0]=nos[i];
    novo->freq=freq[i];
    novo->esq=NULL;
    novo->dir=NULL;
    novo->prox=NULL;
    novo->tam=1;
    HUFFNo *aux=(*h);
    if(aux==NULL)(*h)=novo;
    else{
    while(aux->prox!=NULL){
        aux=aux->prox;
    }
    aux->prox=novo;
    }}
    while(tam!=1){
    int j=0;
    int k=0;
        HUFFNo* novo=(HUFFNo*)malloc(sizeof(HUFFNo));
        novo->prox=NULL;
        HUFFNo *aux1=(*h);
        HUFFNo *aux2=(*h)->prox;
        novo->chave=(char*)malloc(sizeof(char*)*(aux1->tam+aux2->tam));
        for( j;j<aux1->tam;j++){
            novo->chave[j]=aux1->chave[j];
        }
        for( k;k<aux2->tam;k++){
            novo->chave[j]=aux2->chave[k];
            j++;
        }
        novo->freq=aux1->freq+aux2->freq;
        novo->tam=aux1->tam+aux2->tam;
        novo->esq=aux1;
        novo->dir=aux2;
        HUFFNo *aux3=aux2->prox;
        int cont=0;
        while(cont!=-1){
                aux2=aux2->prox;
                aux1=aux1->prox;
                if(aux2==NULL){
                    (*h)=novo;
                    cont=-2;
                }
                if(cont!=-2&&aux2->prox==NULL){
                        aux2->prox=novo;
                        (*h)=aux3;
                        cont=-2;

                }
                else if(cont!=-2&&cont==0&&aux2->freq>=novo->freq){
                        novo->prox=aux2;
                        (*h)=novo;
                        cont=-2;

                }
                else if(cont!=-2&&cont!=0&&aux2->freq>=novo->freq){
                    aux1->prox=novo;
                    novo->prox=aux2;
                    (*h)=aux3;
                    cont=-2;
                }
            cont++;
        }
        tam--;
    }
}
void imprime_aux(HUFFNo* a, int andar){
  if(a){
    int j;
    imprime_aux(a->esq, andar + 1);
    for(j = 0; j <= andar; j++) printf("   ");
    for(int i = 0; i<a->tam; i++){
            if(i==a->tam-1)printf("%c\n", a->chave[i]);
            else printf("%c", a->chave[i]);
    }
    imprime_aux(a->dir, andar + 1);
  }
}

void decodifica(lista *L,HUFFNo *H){
    if(L&&(H)){
        while(L->prox){
            HUFFNo *aux = H;
            while((aux->tam != 1)){//se H->tam == 1 quer dizer que é uma folha, portanto chegou em alguma letra.
                if(!L)return;
                if((L->cod == 0))aux = aux->esq;
                else aux = aux->dir;
                lista *aux2 = L;
                L = (L)->prox;
                free(aux2);
            }
        printf("%c",(aux)->chave[0]);
        if(!L)return;
        }
    }
}


void imprime_ab(HUFFNo* a){
  imprime_aux(a, 0);
}


void quicksort(float *v1,char *v2,int tam){
if(tam<=1)return;
float x=v1[0];
char  x2=v2[0];
int a=1,b=tam-1;
do{
while((a<tam)&&(v1[a]<=x))a++;
while(v1[b]>x)b--;
if(a<=b){
    float temp=v1[a];
    char  temp2=v2[a];
    v1[a]=v1[b];
    v2[a]=v2[b];
    v1[b]=temp;
    v2[b]=temp2;
    a++;b--;
}}while(a<=b);
v1[0]=v1[b];
v2[0]=v2[b];
v1[b]=x;
v2[b]=x2;
quicksort(v1,v2,b);
quicksort(&v1[b+1],&v2[b+1],tam-b-1);
}
void arqfreq(char *v1,float *v2){
FILE *fp1=fopen("freq.txt","rt");
if((!fp1))exit(1);
int r1;
char n1;
float n2;
r1=fscanf(fp1,"%c",&n1);
int i=0;
int j=0;
int cfreq=0;
while(r1!=EOF){
if(n1==37&&r1!=EOF){
r1=fscanf(fp1,"%c",&n1);
}
if(n1=='\n'&&r1!=EOF){
r1=fscanf(fp1,"%c",&n1);
}
while(n1==32&&r1!=EOF){
    r1=fscanf(fp1,"%c",&n1);
}
if(((n1>64&&n1<91)||(n1>96&&n1<123))&&r1!=EOF){
v1[i]=n1;
cfreq=1;
i++;
r1=fscanf(fp1,"%c",&n1);
}
if (cfreq==1){
r1=fscanf(fp1,"%f",&n2);
v2[j]=n2;
j++;
cfreq=0;}
r1=fscanf(fp1,"%c",&n1);
}fclose(fp1);
quicksort(v2,v1,52);
}
void libera_huff(HUFFNo* t){
  if(t){
  libera_huff(t->esq);
  libera_huff(t->dir);
  free(t->chave);
  free(t);
  }
}
void alterafreq(float* v1,char *v2,float cont,int chave,char *R,int tam){
    int i=0;
    if(chave==0){
        while(v1[i]<101){
            v1[i]=(v1[i]*100)/cont;
            i++;
        }

    }
    else{
        for(int j=0;j<tam;j++){
            if(v2[j]!=R[0]){
                v1[j]=(v1[j]*100)/cont;
            }
        }
    }

}
int retira(float* v1,char *v2,char *R,int cont,int *tam){
    float cont2=0;
    int cont3=0;
    for(int i=0;i<cont;i++){
    for (int j=0;j<(*tam);j++){
            if(v2[j]==R[i]){
                cont2=cont2+v1[j];
                v1[j]=101;
                cont3++;
            }
   }
}(*tam)=(*tam)-cont3;
return 100-cont;
}
void retiravog(HUFFNo **h,float* v1,char *v2,int *tam){
    float cont;
    char R[10]={'a','e','i','o','u','A','E','I','O','U'};
    cont=retira(v1,v2,R,10,tam);
    quicksort(v1,v2,52);
    alterafreq(v1,v2,cont,0,R,52);
    libera_huff((*h));
    (*h)=NULL;
    criaarv(v1,v2,h,(*tam));
}
void retiracons(HUFFNo **h,float* v1,char *v2,int *tam){
    float cont;
    char R[42]={'B','C','D','F','G','H','J','K','L','M','N','P','Q','R','S','T','V','W','X','Y','Z','b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','y','z'};
    cont=retira(v1,v2,R,42,tam);
    quicksort(v1,v2,52);
    alterafreq(v1,v2,cont,0,R,52);
    libera_huff((*h));
    (*h)=NULL;
    criaarv(v1,v2,h,(*tam));
}
void retiramaius(HUFFNo **h,float* v1,char *v2,int *tam){
    float cont;
    char R[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    cont=retira(v1,v2,R,26,tam);
    quicksort(v1,v2,52);
    alterafreq(v1,v2,cont,0,R,52);
    libera_huff((*h));
    (*h)=NULL;
    criaarv(v1,v2,h,(*tam));
}
void retiraminus(HUFFNo **h,float* v1,char *v2,int *tam){
    float cont;
    char R[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    cont=retira(v1,v2,R,26,tam);
    quicksort(v1,v2,52);
    alterafreq(v1,v2,cont,0,R,52);
    libera_huff((*h));
    (*h)=NULL;
    criaarv(v1,v2,h,(*tam));
}
void alteraelem(HUFFNo **h,char *R,float *Rf,float* v1,char *v2,int *tam){
    float cont;
    for(int i=0;i<(*tam);i++){
        if(v2[i]==R[0]){
            if(Rf[0]==v1[i]){
                return;
            }
                if(Rf[0]==0){cont=retira(v1,v2,R,1,tam);
                quicksort(v1,v2,52);
                alterafreq(v1,v2,cont,0,R,52);
                libera_huff((*h));
                (*h)=NULL;
                criaarv(v1,v2,h,(*tam));
                }
                if(v1[i]>Rf[0]){
                    cont=100-(v1[i]-Rf[0]);
                    v1[i]=Rf[0];
                    alterafreq(v1,v2,cont,1,R,52);
                    quicksort(v1,v2,52);
                    libera_huff((*h));
                    (*h)=NULL;
                    criaarv(v1,v2,h,(*tam));
                }
                if(v1[i]<Rf[0]){
                    cont=100+(Rf[0]-v1[i]);
                    v1[i]=Rf[0];
                    alterafreq(v1,v2,cont,1,R,52);
                    quicksort(v1,v2,52);
                    libera_huff((*h));
                    (*h)=NULL;
                    criaarv(v1,v2,h,(*tam));
                }
        }
    }
}
int main()
{
    int tam=52;
	char v1[52];
    float v2[52];
    char R[1]={'a'};
    float Rf[1]={0};
    arqfreq(v1,v2);
    HUFFNo *h=NULL;
	criaarv(v2,v1,&h,52);
	alteraelem(&h,R,Rf,v2,v1,&tam);
	imprime_ab(h);
	char s;
    lista *l = NULL;
    printf("\nDigite o codigo para decodificar: ");
    scanf("%c",&s);
    while(s!='\n'){
        pushi(&l,s-48);
        scanf("%c",&s);
    }
    decodifica(l,h);
	return 0;
}

