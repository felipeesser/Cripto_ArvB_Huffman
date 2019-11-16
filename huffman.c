// Árvore Huffman usando MinHeap
//https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/



#include <stdio.h> 
#include <stdlib.h> 

// precisamos de função para calcular a altura da arvore 
// como nao temos ainda usa essa constante
#define MAX_ARV_ALT 100 

// nó da arvore
typedef struct MinHeapNo
{ 

	char chave; 
	unsigned freq;  
	struct MinHeapNo *esq, *dir; 
}   MinHeapNo;

// MinHeap: Conjunto de nós da MinHeap 
typedef struct MinHeap
{ 

	// tamanho atual da MinHeap
	unsigned tam; 

	// capacidade da MinHeap 
	unsigned capacidade; 

	// Array de ponteiros para nós da MinHeap 
	struct MinHeapNo** array; 
}  MinHeap; 

// aloca um novo nó da MinHeap com o char e a frequencia dada  
MinHeapNo *novoNo(char chave, unsigned freq)
{ 
	MinHeapNo *novo = (MinHeapNo*)malloc(sizeof(MinHeapNo)); 

	novo->esq = novo->dir = NULL; 
	novo->chave = chave; 
	novo->freq = freq; 

	return novo; 
} 

// cria uma MinHeap da capacidade dada  
MinHeap *criaMinHeap(unsigned capacidade)
{ 

	MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap)); 

	//tamanho atual é 0 
	minHeap->tam = 0; 

	minHeap->capacidade = capacidade; 

	minHeap->array = (MinHeapNo**)malloc(minHeap->capacidade * sizeof(MinHeapNo*)); 
	return minHeap; 
} 

// troca 2 nós da MinHeap
void trocaNo(struct MinHeapNo** a, struct MinHeapNo** b)
{ 
	MinHeapNo *t = *a; 
	*a = *b; 
	*b = t; 
} 

// função original minHeapify (preciso verificar idx)
void minHeapify(MinHeap* minHeap, int idx) 

{ 

	int menor = idx; 
	int esq = 2 * idx + 1; 
	int dir = 2 * idx + 2; 

	if (esq < minHeap->tam && minHeap->array[esq]->freq < minHeap->array[menor]->freq) 
		menor = esq; 

	if (dir < minHeap->tam && minHeap->array[dir]->freq < minHeap->array[menor]->freq) 
		menor = dir; 

	if (menor != idx) { 
		trocaNo(&minHeap->array[menor],&minHeap->array[idx]); 
		minHeapify(minHeap, menor); 
	} 
} 

// checa se o tamnaha da heap é 1 ou não 
int eUm(MinHeap* minHeap) 
{ 

	return (minHeap->tam == 1); 
} 

// retira o menor valor de um nó da heap 
MinHeapNo *retiraMenor(MinHeap *minHeap) 
{ 

	MinHeapNo *novo = minHeap->array[0]; 
	minHeap->array[0] = minHeap->array[minHeap->tam - 1]; 

	--minHeap->tam; 
	minHeapify(minHeap, 0); 

	return novo; 
} 

// insere um novo nó na MinHeap 
void insereMinHeap(MinHeap* minHeap, MinHeapNo* MinHeapNo) 

{ 

	++minHeap->tam; 
	int i = minHeap->tam - 1; 

	while (i && MinHeapNo->freq < minHeap->array[(i - 1) / 2]->freq) { 

		minHeap->array[i] = minHeap->array[(i - 1) / 2]; 
		i = (i - 1) / 2; 
	} 

	minHeap->array[i] = MinHeapNo; 
} 


void constroiMinHeap(MinHeap* minHeap) 

{ 

	int n = minHeap->tam - 1; 
	int i; 

	for (i = (n - 1) / 2; i >= 0; --i) 
		minHeapify(minHeap, i); 
} 

// printa um array de tamanho n  
void printArr(int arr[], int n) 
{ 
	int i; 
	for (i = 0; i < n; ++i) 
		printf("%d", arr[i]); 

	printf("\n"); 
} 

// verifica se o nó é folha 
int eFolha(MinHeapNo* raiz) 

{ 

	return !(raiz->esq) && !(raiz->dir); 
} 

//Cria uma MinHeap de capacidade igual a tam e insere o array de char nela
//Inicialmente tamanho da MinHeap é igual a capacidade 

MinHeap* criaMontaMinHeap(char chave[], int freq[], int tam) 

{ 

	MinHeap* minHeap = criaMinHeap(tam); 

	for (int i = 0; i < tam; ++i) 
		minHeap->array[i] = novoNo(chave[i], freq[i]); 

	minHeap->tam = tam; 
	constroiMinHeap(minHeap);

	return minHeap; 
} 

// função pricipal que cria uma Árvore Huffman 
MinHeapNo *criaArvoreHuffman(char chave[], int freq[], int tam) 

{ 
	MinHeapNo *esq, *dir, *topo; 

	// Passo 1: Cria uma MinHeap de capacidade igual a tam. 
	//Inicialmente tem nós iguais a tam
	 
	struct MinHeap* minHeap = criaMontaMinHeap(chave, freq, tam); 

	// enquanto o tamanho da heap não for 1 
	while (!eUm(minHeap)) { 

		// Passo 2: extrai as 2 chaves com menor frequencia da heap 
		esq = retiraMenor(minHeap); 
		dir = retiraMenor(minHeap); 

		/* Passo 3: Create a new internal Cria um novo nó interno com frequencia igual a soma dos 2 nós. 
		Faz os 2 nós extraídos virarem filhos desse novo nó. 
		Adiciona esse nó na heap. 
		"?" é especial para nós internos*/ 
		topo = novoNo('?', esq->freq + dir->freq); 

		topo->esq = esq; 
		topo->dir = dir; 

		insereMinHeap(minHeap, topo); 
	} 

	// Passo 4: o nó que sobre é a raiz e assim a árvore está feita 
	return retiraMenor(minHeap); 
} 

//Printa o código de huffman a partir da raiz 
// Usa arr[] para guardar o código 
void printaCodigo(struct MinHeapNo* raiz, int arr[], int topo) 

{ 

	// Arestas a esquerda recebem 0 
	if (raiz->esq) { 

		arr[topo] = 0; 
		printaCodigo(raiz->esq, arr, topo + 1); 
	} 

	// Arestas a esquerda recebem 1 
	if (raiz->dir) { 

		arr[topo] = 1; 
		printaCodigo(raiz->dir, arr, topo + 1); 
	} 

	//  Se o nó for folha, então contém um dos caracteres. 
	//Printa o char e o codigo correspondente de arr[]
	 
	if (eFolha(raiz)) { 

		printf("%c: ", raiz->chave); 
		printArr(arr, topo); 
	} 
} 

// Função principal que constrói uma Árvore Huffman e printa o código fazendo os passos inversos que a criaram 
void codigoHuffman(char chave[], int freq[], int tam) 

{ 
	// Constrói Árvore Huffman  
	MinHeapNo* raiz = criaArvoreHuffman(chave, freq, tam); 

	// Print Huffman codes using Printa o código da Árvore construída acima
	int arr[MAX_ARV_ALT], topo = 0; 

	printaCodigo(raiz, arr, topo); 
} 

// programa teste 
int main() 
{ 

	char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' }; 
	int freq[] = { 5, 9, 17, 18, 21, 30 }; 

	int tam = sizeof(arr) / sizeof(arr[0]); 

	codigoHuffman(arr, freq, tam); 

	return 0; 
} 
