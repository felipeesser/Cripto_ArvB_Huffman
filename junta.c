#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct ArvB{
  int nchaves, folha;
  char *chave;
  struct ArvB **filho;
}TAB;

typedef struct no
{   int tam;
	char* chave;
	float freq;
	struct no *esq, *dir;
	struct no *prox;
}   HUFFNo;

typedef struct lista{
    char letra;
    int cod;
    struct lista* p;
    }TF;

void pushi(TF**filaini,int letra){
    TF *novo;
    novo=(TF*)malloc(sizeof(TF));
    novo->cod=letra;
    novo->p=NULL;
    if((*filaini)==NULL){
        (*filaini)=novo;
    }
    else{
        TF *aux=(*filaini);
        while(aux->p){
            aux=aux->p;}
        aux->p=novo;
    }
}

int popi(TF**filaini){
       if ((*filaini)==NULL)return -1;
    int retorno;
    TF *aux=(*filaini);
    if((*filaini)->p!=NULL){
    retorno=(*filaini)->cod;
    (*filaini)=(*filaini)->p;
    free(aux);
    return retorno;}
    else{
        retorno=(*filaini)->cod;
        (*filaini)=NULL;
        free(aux);
        return retorno;
    }
}

void push(TF**filaini,char letra){
    TF *novo;
    novo=(TF*)malloc(sizeof(TF));
    novo->letra=letra;
    novo->p=NULL;
    if((*filaini)==NULL){
        (*filaini)=novo;
    }
    else{
        TF *aux=(*filaini);
        while(aux->p){
            aux=aux->p;}
        aux->p=novo;
    }
}

char pop(TF**filaini){
    if ((*filaini)==NULL)return '?';
    char retorno;
    TF *aux=(*filaini);
    if((*filaini)->p!=NULL){
    retorno=(*filaini)->letra;
    (*filaini)=(*filaini)->p;
    free(aux);
    return retorno;}
    else{
        retorno=(*filaini)->letra;
        (*filaini)=NULL;
        free(aux);
        return retorno;
    }
}

TAB *Cria(int t){
  TAB* novo = (TAB*)malloc(sizeof(TAB));
  novo->nchaves = 0;
  novo->chave =(char*)malloc(sizeof(char*)*((t*2)-1));
  novo->folha=1;
  novo->filho = (TAB**)malloc(sizeof(TAB*)*t*2);
  int i;
  for(i=0; i<(t*2); i++) novo->filho[i] = NULL;
  return novo;
}

void criaHuff(float *freq,char *nos,HUFFNo **h,int tam){
    int j=0;
    int k=0;
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
     j=0;
     k=0;
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

TAB *Libera(TAB *a){
  if(a){
    if(!a->folha){
      int i;
      for(i = 0; i <= a->nchaves; i++) Libera(a->filho[i]);
    }
    free(a->chave);
    free(a->filho);
    free(a);
    return NULL;
  }return NULL;
}


void Imprime(TAB *a, int andar){
  if(a){
    int i,j;
    for(i=0; i<=a->nchaves-1; i++){
      Imprime(a->filho[i],andar+1);
      for(j=0; j<=andar; j++) printf("   ");
      printf("%c\n", a->chave[i]);
    }
    Imprime(a->filho[i],andar+1);
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
void imprime_ab(HUFFNo* a){
  imprime_aux(a, 0);
}

TAB *Busca(TAB* x, char ch){
  TAB *resp = NULL;
  if(!x) return resp;
  int i = 0;
  while(i < x->nchaves && ch > x->chave[i]) i++;
  if(i < x->nchaves && ch == x->chave[i]) return x;
  if(x->folha) return resp;
  return Busca(x->filho[i], ch);
}


TAB *Inicializa(){
  return NULL;
}


TAB *Divisao(TAB *x, int i, TAB* y, int t){
  TAB *z=Cria(t);
  z->nchaves= t - 1;
  z->folha = y->folha;
  int j;
  for(j=0;j<t-1;j++) z->chave[j] = y->chave[j+t];
  if(!y->folha){
    for(j=0;j<t;j++){
      z->filho[j] = y->filho[j+t];
      y->filho[j+t] = NULL;
    }
  }
  y->nchaves = t-1;
  for(j=x->nchaves; j>=i; j--) x->filho[j+1]=x->filho[j];
  x->filho[i] = z;
  for(j=x->nchaves; j>=i; j--) x->chave[j] = x->chave[j-1];
  x->chave[i-1] = y->chave[t-1];
  x->nchaves++;
  return x;
}


TAB *Insere_Nao_Completo(TAB *x, char k, int t){
  int i = x->nchaves-1;
  if(x->folha){
    while((i>=0) && (k<x->chave[i])){
      x->chave[i+1] = x->chave[i];
      i--;
    }
    x->chave[i+1] = k;
    x->nchaves++;
    return x;
  }
  while((i>=0) && (k<x->chave[i])) i--;
  i++;
  if(x->filho[i]->nchaves == ((2*t)-1)){
    x = Divisao(x, (i+1), x->filho[i], t);
    if(k>x->chave[i]) i++;
  }
  x->filho[i] = Insere_Nao_Completo(x->filho[i], k, t);
  return x;
}


TAB *Insere(TAB *T, char k, int t){
  if(Busca(T,k)) return T;
  if(!T){
    T=Cria(t);
    T->chave[0] = k;
    T->nchaves=1;
    return T;
  }
  if(T->nchaves == (2*t)-1){
    TAB *S = Cria(t);
    S->nchaves=0;
    S->folha = 0;
    S->filho[0] = T;
    S = Divisao(S,1,T,t);
    S = Insere_Nao_Completo(S,k,t);
    return S;
  }
  T = Insere_Nao_Completo(T,k,t);
  return T;
}


TAB* remover(TAB* arv, char ch, int t){
  if(!arv) return arv;
  int i;
  printf("Removendo %c...\n", ch);
  for(i = 0; i<arv->nchaves && arv->chave[i] < ch; i++);
  if(i < arv->nchaves && ch == arv->chave[i]){ //CASOS 1, 2A, 2B e 2C
    if(arv->folha){ //CASO 1
      printf("\nCASO 1\n");
      int j;
      for(j=i; j<arv->nchaves-1;j++) arv->chave[j] = arv->chave[j+1];
      arv->nchaves--;
      return arv;
    }
    if(!arv->folha && arv->filho[i]->nchaves >= t){ //CASO 2A
      printf("\nCASO 2A\n");
      TAB *y = arv->filho[i];  //Encontrar o predecessor k' de k na  rvore com raiz em y
      while(!y->folha) y = y->filho[y->nchaves];
      int temp = y->chave[y->nchaves-1];
      arv->filho[i] = remover(arv->filho[i], temp, t);
      //Eliminar recursivamente K e substitua K por K' em x
      arv->chave[i] = temp;
      return arv;
    }
    if(!arv->folha && arv->filho[i+1]->nchaves >= t){ //CASO 2B
      printf("\nCASO 2B\n");
      TAB *y = arv->filho[i+1];  //Encontrar o sucessor k' de k na  rvore com raiz em y
      while(!y->folha) y = y->filho[0];
      int temp = y->chave[0];
      y = remover(arv->filho[i+1], temp, t); //Eliminar recursivamente K e substitua K por K' em x
      arv->chave[i] = temp;
      return arv;
    }
    if(!arv->folha && arv->filho[i+1]->nchaves == t-1 && arv->filho[i]->nchaves == t-1){ //CASO 2C
      printf("\nCASO 2C\n");
      TAB *y = arv->filho[i];
      TAB *z = arv->filho[i+1];
      y->chave[y->nchaves] = ch;          //colocar ch ao final de filho[i]
      int j;
      for(j=0; j<t-1; j++)                //juntar chave[i+1] com chave[i]
        y->chave[t+j] = z->chave[j];
      for(j=0; j<=t; j++)                 //juntar filho[i+1] com filho[i]
        y->filho[t+j] = z->filho[j];
      y->nchaves = 2*t-1;
      for(j=i; j < arv->nchaves-1; j++)   //remover ch de arv
        arv->chave[j] = arv->chave[j+1];
      for(j=i+1; j <= arv->nchaves; j++)  //remover ponteiro para filho[i+1]
        arv->filho[j] = arv->filho[j+1];
      arv->filho[j] = NULL; //Campello
      arv->nchaves--;
      arv->filho[i] = remover(arv->filho[i], ch, t);
      return arv;
    }
  }

  TAB *y = arv->filho[i], *z = NULL;
  if (y->nchaves == t-1){ //CASOS 3A e 3B
    if((i < arv->nchaves) && (arv->filho[i+1]->nchaves >=t)){ //CASO 3A
      printf("\nCASO 3A: i menor que nchaves\n");
      z = arv->filho[i+1];
      y->chave[t-1] = arv->chave[i];   //dar a y a chave i da arv
      y->nchaves++;
      arv->chave[i] = z->chave[0];     //dar a arv uma chave de z
      int j;
      for(j=0; j < z->nchaves-1; j++)  //ajustar chaves de z
        z->chave[j] = z->chave[j+1];
      //z->chave[j] = 0; Rosseti
      y->filho[y->nchaves] = z->filho[0]; //enviar ponteiro menor de z para o novo elemento em y
      for(j=0; j < z->nchaves; j++)       //ajustar filhos de z
        z->filho[j] = z->filho[j+1];
      z->nchaves--;
      arv->filho[i] = remover(arv->filho[i], ch, t);
      return arv;
    }
    if((i > 0) && (!z) && (arv->filho[i-1]->nchaves >=t)){ //CASO 3A
      printf("\nCASO 3A: i igual a nchaves\n");
      z = arv->filho[i-1];
      int j;
      for(j = y->nchaves; j>0; j--)               //encaixar lugar da nova chave
        y->chave[j] = y->chave[j-1];
      for(j = y->nchaves+1; j>0; j--)             //encaixar lugar dos filhos da nova chave
        y->filho[j] = y->filho[j-1];
      y->chave[0] = arv->chave[i-1];              //dar a y a chave i da arv
      y->nchaves++;
      arv->chave[i-1] = z->chave[z->nchaves-1];   //dar a arv uma chave de z
      y->filho[0] = z->filho[z->nchaves];         //enviar ponteiro de z para o novo elemento em y
      z->nchaves--;
      arv->filho[i] = remover(y, ch, t);
      return arv;
    }
    if(!z){ //CASO 3B
      if(i < arv->nchaves && arv->filho[i+1]->nchaves == t-1){
        printf("\nCASO 3B: i menor que nchaves\n");
        z = arv->filho[i+1];
        y->chave[t-1] = arv->chave[i];     //pegar chave [i] e coloca ao final de filho[i]
        y->nchaves++;
        int j;
        for(j=0; j < t-1; j++){
          y->chave[t+j] = z->chave[j];     //passar filho[i+1] para filho[i]
          y->nchaves++;
        }
        if(!y->folha){
          for(j=0; j<t; j++){
            y->filho[t+j] = z->filho[j];
          }
        }
        for(j=i; j < arv->nchaves-1; j++){ //limpar refer ncias de i
          arv->chave[j] = arv->chave[j+1];
          arv->filho[j+1] = arv->filho[j+2];
        }
        arv->nchaves--;
        arv = remover(arv, ch, t);
        return arv;
      }
      if((i > 0) && (arv->filho[i-1]->nchaves == t-1)){
        printf("\nCASO 3B: i igual a nchaves\n");
        z = arv->filho[i-1];
        if(i == arv->nchaves)
          z->chave[t-1] = arv->chave[i-1]; //pegar chave[i] e poe ao final de filho[i-1]
        else
          z->chave[t-1] = arv->chave[i];   //pegar chave [i] e poe ao final de filho[i-1]
        z->nchaves++;
        int j;
        for(j=0; j < t-1; j++){
          z->chave[t+j] = y->chave[j];     //passar filho[i+1] para filho[i]
          z->nchaves++;
        }
        if(!z->folha){
          for(j=0; j<t; j++){
            z->filho[t+j] = y->filho[j];
          }
        }
        arv->nchaves--;
        arv->filho[i-1] = z;
        arv = remover(arv, ch, t);
        return arv;
      }
    }
  }
  arv->filho[i] = remover(arv->filho[i], ch, t);
  return arv;
}


TAB* retira(TAB* arv, char k, int t){
  if(!arv || !Busca(arv, k)) return arv;
  return remover(arv, k, t);
}

void criaarvore(TAB **arv,int t){
	char alfabeto[52]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	for (int i=0;i<52;i++){
    (*arv)=Insere((*arv),alfabeto[i],t);
	}
}

int codificaaux(char letra,TAB* arv,int andar){
  int i = 0;
  int j=0;
  while(i < arv->nchaves && letra > arv->chave[i]) i++;
  if(i < arv->nchaves && letra == arv->chave[i]){
  	printf("%d",andar);
  return i;
	}
  if(arv->folha){
    printf("?");
    return -1;
	}
    j=codificaaux(letra,arv->filho[i],andar+1);
    if(j>=0)printf("%d",i);
    return j;
}

void codifica(TAB* arv,TF **Ti,int cont){
	int j;
	if(!arv||!(*Ti))return;
	for(int i=0;i<cont-1;i++){
	j=codificaaux(pop(Ti),arv,0);
		if (j>=0)printf("%d",j);
	}
}

void deco(TF **Ti,TAB* arv){
	if ((*Ti)==NULL)return;
	TAB *aux=arv;
	int j=popi(Ti);
	for(int i=0;i<j;i++){
  		if(i>aux->nchaves)return;
    	aux=aux->filho[popi(Ti)];
	}
	printf("%c",aux->chave[popi(Ti)]);
	deco(Ti,arv);
}

void decodifica(TF *L,HUFFNo *H){
    if(L&&(H)){
        if(L&&H){
        while(L->p){
            HUFFNo *aux = H;
            while((aux->tam != 1)){//se H->tam == 1 quer dizer que é uma folha, portanto chegou em alguma letra.
                if(!L)return;
                if(L->cod == 0)aux = aux->esq;
                else aux = aux->dir;
                TF *aux2 = L;
                L = (L)->p;
                free(aux2);
            }
        printf("%c",(aux)->chave[0]);
        if(!L)return;
        }
    }
    }
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
    return;
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

int retirahuff(float* v1,char *v2,char *R,int cont,int *tam){
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
void retiravoghuff(HUFFNo **h,float* v1,char *v2,int *tam){
    float cont;
    char R[10]={'a','e','i','o','u','A','E','I','O','U'};
    cont=retirahuff(v1,v2,R,10,tam);
    quicksort(v1,v2,52);
    alterafreq(v1,v2,cont,0,R,52);
    libera_huff((*h));
    (*h)=NULL;
    criaarv(v1,v2,h,(*tam));
}
void retiraconshuff(HUFFNo **h,float* v1,char *v2,int *tam){
    float cont;
    char R[42]={'B','C','D','F','G','H','J','K','L','M','N','P','Q','R','S','T','V','W','X','Y','Z','b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','y','z'};
    cont=retirahuff(v1,v2,R,42,tam);
    quicksort(v1,v2,52);
    alterafreq(v1,v2,cont,0,R,52);
    libera_huff((*h));
    (*h)=NULL;
    criaarv(v1,v2,h,(*tam));
}
void retiramaiushuff(HUFFNo **h,float* v1,char *v2,int *tam){
    float cont;
    char R[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    cont=retirahuff(v1,v2,R,26,tam);
    quicksort(v1,v2,52);
    alterafreq(v1,v2,cont,0,R,52);
    libera_huff((*h));
    (*h)=NULL;
    criaarv(v1,v2,h,(*tam));
}
void retiraminushuff(HUFFNo **h,float* v1,char *v2,int *tam){
    float cont;
    char R[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    cont=retirahuff(v1,v2,R,26,tam);
    quicksort(v1,v2,52);
    alterafreq(v1,v2,cont,0,R,52);
    libera_huff((*h));
    (*h)=NULL;
    criaarv(v1,v2,h,(*tam));
}

void retiramin(TAB* arv,int t){
    char min[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    for(int i=0;i<52;i++){
      arv=retira(arv,min[i],t);
    }
}

void retiramai(TAB* arv,int t){
    char mai[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    for(int i=0;i<52;i++){
      arv=retira(arv,mai[i],t);
    }
}

void retiravog(TAB* arv,int t){
    char mai[10]={'A','E','I','O','U','a','e','i','o','u'};
    for(int i=0;i<52;i++){
      arv=retira(arv,mai[i],t);
    }
}

void retiracon(TAB* arv,int t){
    char mai[42]={'B','C','D','F','G','H','J','K','L','M','N','P','Q','R','S','T','V','W','X','Y','Z','b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','y','z'};
    for(int i=0;i<52;i++){
      arv=retira(arv,mai[i],t);
    }
}

void alteraelem(HUFFNo **h,char *R,float *Rf,float* v1,char *v2,int *tam){
    float cont;
    for(int i=0;i<(*tam);i++){
        if(v2[i]==R[0]){
            if(Rf[0]==v1[i]){
                return;
            }
                if(Rf[0]==0){cont=retirahuff(v1,v2,R,1,tam);
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
bool codificah(HUFFNo *H,TF **L, TF **L2){
    if(!((H->esq)&&(H->dir))&&(H->chave[0]==(*L)->letra)){
        return true;
    }
    else{
        bool encontrado = false;
        if(H->esq){
            TF *aux = (TF*)malloc(sizeof(TF));
            aux->cod=0;
            aux->p=NULL;
            (*L2)->p= aux;
            encontrado = codificah(H->esq,L,&aux);
        }
        if(!encontrado&&H->dir){
            TF *aux2 = (TF*)malloc(sizeof(TF));
            aux2->cod=1;
            aux2->p=NULL;
            (*L2)->p= aux2;
            encontrado = codificah(H->dir,L,&aux2);
        }
        return encontrado;
    }
    }
void codificaauxh(HUFFNo *H,TF **L, TF **L2){
    while((*L)){
        codificah(H,L,L2);
    TF *aux2=(*L2)->p;
    while(aux2!=NULL){
        printf("%d",aux2->cod);
        aux2=aux2->p;
    }
        TF *aux=(*L);
        (*L)=(*L)->p;
        free(aux);
    }
}

void retiraElem(TAB* arv, char c, int t){
	arv=retira(arv,c,t);
}

int main(int argc, char *argv[]){
  TAB * arvore = Inicializa();
  int cont=0,chave=0, t;
  HUFFNo *h=NULL;
  TF *Ti=NULL;
  TF *Td=NULL;
  TF *lc=NULL;
  TF *resp=NULL;
  TF *aux = NULL;
  aux = (TF*)malloc(sizeof(TF));
    aux->cod=-1;
    aux->p=NULL;
    resp= aux;
  char letra,cod;
  int tam=52;
  char v1[52];
  float v2[52];
  arqfreq(v1,v2);
  char R[1]={'a'};
  float Rf[1]={11.602};
  criaHuff(v2,v1,&h,52);
  int a;
  while((chave !=-1) &&(a != -1)){
    printf("\nPara utilizar a Arvore B digite 0 \nPara Arvore de Huffman digite 1\nPara sair digite -1\n");
    scanf("%d",&a);
    if(a == 0){
        printf("Digite o 't' desejado: ");
        scanf("%d", &t);
        criaarvore(&arvore,t);
        Imprime(arvore,0);
        cont=0;
        printf("\n");
        printf("----------------------------------------------");
        printf("\n");
        printf("0 para encriptar\n");
        printf("1 para desencriptar\n");
        printf("2 para retirar um elemento\n");
        printf("3 para retirar todas as vogais\n");
        printf("4 para retirar todas as consoantes\n");
        printf("5 para retirar todas as letra minusculas\n");
        printf("6 para retirar todas as letra maiusculas\n");
        printf("7 para desfazer as alteracoes\n");
        printf("-1 para sair\n");
        printf("----------------------------------------------");
        printf("\n");
        printf("Digite sua opcao:");
        scanf("%d",&chave);
        printf("\n");
        while ((getchar()) != '\n');//aparentemente limpa o buffer
      if (chave==0){
        printf("Digite um texto: ");
        scanf("%c",&letra);
        cont++;
        while (letra!='\n'){
          push(&Ti,letra);
          cont++;
          scanf("%c",&letra);
        }
        codifica(arvore,&Ti,cont);
        printf("\n");
      }

      if (chave==1){
        printf("Digite o codigo\n");
        scanf("%c",&cod);
        while (cod!='\n'){
          if(cod>47&&cod<58)pushi(&Td,cod-48);
          scanf("%c",&cod);
        }
        deco(&Td,arvore);
        printf("\n");
      }

      if(chave==2){
        char c;
        printf("Qual letra deseja retirar? ");
        scanf("%c", &c);
        retiraElem(arvore,c,t);
        Imprime(arvore, 0);
        printf("\n");
      }

      if(chave==3){
        retiravog(arvore,t);
        Imprime(arvore, 0);
        printf("\n");
      }

      if(chave==4){
        retiracon(arvore,t);
        Imprime(arvore, 0);
        printf("\n");
      }

      if(chave==5){
        retiramin(arvore,t);
        Imprime(arvore, 0);
        printf("\n");
      }

      if(chave==6){
        retiramai(arvore,t);
        Imprime(arvore, 0);
        printf("\n");
      }

      if(chave==7){
        Libera(arvore);
        TAB * arv = Inicializa();
        criaarvore(&arv,t);
        Imprime(arv, 0);
        printf("\n");
      }
    }
    if(a == 1){
      imprime_aux(h,0);
        printf("\n");
        printf("----------------------------------------------");
        printf("\n");
        printf("0 para encriptar\n");
        printf("1 para desencriptar\n");
        printf("2 para retirar um elemento\n");
        printf("3 para retirar todas as vogais\n");
        printf("4 para retirar todas as consoantes\n");
        printf("5 para retirar todas as letra minusculas\n");
        printf("6 para retirar todas as letra maiusculas\n");
        printf("7 para desfazer as alteracoes\n");
        printf("8 para alaterar a frequência\n");
        printf("-1 para sair\n");
        printf("----------------------------------------------");
        printf("\n");
        printf("Digite sua opcao:");
        scanf("%d",&chave);
        printf("\n");
        int tam = 52;
        if (chave==0){
            char letra;
            printf("Digite um texto: ");
            while ((getchar()) != '\n');
            scanf("%c",&letra);
        while (letra!='\n'){
          push(&lc,letra);
          scanf("%c",&letra);
        }
        codificaauxh(h,&lc,&resp);
        printf("\n");
      }

      if (chave==1){
        char s;
        TF *l = NULL;
        printf("\nDigite o codigo para decodificar: ");
        scanf("%c",&s);
        scanf("%c",&s);
        while(s!='\n'){
            pushi(&l,s-48);
            scanf("%c",&s);
        }
        decodifica(l,h);
    }

      if(chave==2){
        char f;
        char R[1];
        float Rf[1] = {0};
        printf("Digite o elemento que deseja retirar\n");
        while ((getchar()) != '\n');
        scanf("%c",&f);
        R[0]=f;
        alteraelem(&h,R,Rf,v2,v1,&tam);
        imprime_aux(h,0);
        printf("\n");
      }

      if(chave==3){
        retiravoghuff(&h,v2,v1,&tam);
        imprime_aux(h,0);
        printf("\n");
      }

      if(chave==4){
        retiraconshuff(&h,v2,v1,&tam);
        imprime_aux(h, 0);
        printf("\n");
      }

      if(chave==5){
        retiraminushuff(&h,v2,v1,&tam);
        imprime_aux(h, 0);
        printf("\n");
      }

      if(chave==6){
        retiramaiushuff(&h,v2,v1,&tam);
        imprime_ab(h);
        printf("\n");
      }

      if(chave==7){
        libera_huff(h);
        arqfreq(v1,v2);
        h = NULL;
        tam = 52;
        criaarv(v2,v1,&h,tam);
        imprime_aux(h,0);
        printf("\n");
      }
      if(chave==8){
        char l;
        float lf;
        char R[1];
        float Rf[1];
        printf("Digite a letra que quer alterar a frequência\n");
        while ((getchar()) != '\n');
        scanf("%c",&l);
        R[0]=l;
        printf("Digite a frequência\n");
        scanf("%f",&lf);
        Rf[0]=lf;
        alteraelem(&h,R,Rf,v2,v1,&tam);
        imprime_aux(h,0);
        printf("\n");
      }
    }
    }

    return 0;
}
