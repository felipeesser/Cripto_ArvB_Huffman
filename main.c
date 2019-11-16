#include <stdio.h>
#include <stdlib.h>

const int t = 2;

typedef struct ArvB{
  int nchaves, folha;
  char *chave;
  struct ArvB **filho;
}TAB;
/*typedef struct Arvhuff{
  int nchaves, folha;
  char *chave;
  float *freq;
  struct Arvhuff **filho;
}TAhuff;*/
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
    if ((*filaini)==NULL)return -7;
    int retorno;
    TF *aux;
    aux=(*filaini);
    TF **pop=filaini;
    if((*filaini)->p!=NULL){
    retorno=(*filaini)->cod;
    (*filaini)=aux->p;
    free(pop);
    return retorno;}
    else{
        retorno=(*filaini)->cod;
        (*filaini)=NULL;
        free(pop);
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
    if ((*filaini)==NULL)return 'ç';
    char retorno;
    TF *aux;
    aux=(*filaini);
    TF **pop=filaini;
    if((*filaini)->p!=NULL){
    retorno=(*filaini)->letra;
    (*filaini)=aux->p;
    free(pop);
    return retorno;}
    else{
        retorno=(*filaini)->letra;
        (*filaini)=NULL;
        free(pop);
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
      TAB *y = arv->filho[i];  //Encontrar o predecessor k' de k na árvore com raiz em y
      while(!y->folha) y = y->filho[y->nchaves];
      int temp = y->chave[y->nchaves-1];
      arv->filho[i] = remover(arv->filho[i], temp, t);
      //Eliminar recursivamente K e substitua K por K' em x
      arv->chave[i] = temp;
      return arv;
    }
    if(!arv->folha && arv->filho[i+1]->nchaves >= t){ //CASO 2B
      printf("\nCASO 2B\n");
      TAB *y = arv->filho[i+1];  //Encontrar o sucessor k' de k na árvore com raiz em y
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
        for(j=i; j < arv->nchaves-1; j++){ //limpar referências de i
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
  if(i < arv->nchaves && letra == arv->chave[i]){printf("%d",andar);
  return i;}
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
for(int i=0;i<cont-1;i++){j=codificaaux(pop(Ti),arv,0);
if (j>=0)printf("%d",j);
}}
void deco(TF **Ti,TAB* arv){
if ((*Ti)==NULL)return;
TAB *aux=arv;
int j=popi(Ti);
for(int i=0;i<j;i++){
    aux=aux->filho[popi(Ti)];
}printf("%c",aux->chave[popi(Ti)]);
deco(Ti,arv);}
void retiramin(TAB* arv){
    char min[52]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    for(int i=0;i<52;i++){
      arv=retira(arv,min[i],t);
    }

}
void retiramai(TAB* arv){
    char mai[52]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    for(int i=0;i<52;i++){
      arv=retira(arv,mai[i],t);
    }

}
void retiravog(TAB* arv){
    char mai[52]={'A','E','I','O','U'};
    for(int i=0;i<52;i++){
      arv=retira(arv,mai[i],t);
    }

}
void retiracon(TAB* arv){
    char mai[52]={'B','C','D','F','G','H','J','K','L','M','N','P','Q','R','S','T','V','W','X','Y','Z','b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','y','z',};
    for(int i=0;i<52;i++){
      arv=retira(arv,mai[i],t);
    }

//
int main(int argc, char *argv[]){
  TAB * arvore = Inicializa();
  int cont=0,chave=0;
  TF *Ti=NULL;
  TF *Td=NULL;
  char letra,cod;
  criaarvore(&arvore,t);
  Imprime(arvore,0);
  while(chave !=-1){
    printf("Digite -1 para sair 0 para encriptar e 1 para desencriptar\n");
    scanf("%d",&chave);
    while ((getchar()) != '\n');//aparentemente limpa o buffer
  if (chave==0){
printf("Digite um texto\n");
  scanf("%c",&letra);
  cont++;
  while (letra!='\n'){
    push(&Ti,letra);
    cont++;
    scanf("%c",&letra);
}codifica(arvore,&Ti,cont);
}
if (chave==1){
printf("Digite o codigo\n");
scanf("%c",&cod);
  while (cod!='\n'){
    if(cod>47&&cod<58)pushi(&Td,cod-48);
    scanf("%c",&cod);
}
deco(&Td,arvore);
}}
return 0;}
