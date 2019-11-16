/*heap && fila de prioridades
max-heap: árvore binária em que cada pai é maior ou igual a qualquer um dos seus filhos
https://www.ime.usp.br/~pf/analise_de_algoritmos/aulas/heap.html
https://www.ime.usp.br/~pf/analise_de_algoritmos/aulas/priority.html
*/


//heap

void heapify(int *A, int n ,int i){ //rearranja o vetor de forma que a sub árvore com 
	if (!A) return 0;
	int j, f, aux;
	j = i;
	
	while(2*j<=n){
		f = 2*j;
		if((f<n) && A[f]<A[f+1]) 
			f = f+1;
		if(A[j]>=A[f])
			j = n;
		else{
			aux = A[j];
			A[j] = A[f];
			A[f] = aux;
		}
		j = f;
	}
}

corrige_subindo(int *A, int m){
	if (!A) return 0;
	int i, aux;
	i = m;
	while(i>=2 && A[i/2]<A[i])
		aux = A[i/2];
		A[i/2] = A[i];
		A[i] = aux;
		i = i/2;
}



void build_max_heap(int *A, int n){ //rearranja os elementos de forma a transformar o vetor em um max-heap
	if (!A) return 0;
	int i;
	for(i=n/2;i = 0;i--)
		 heapify(A, n, i);
}


//fila de prioridades

int remove_max(int *A, int n){
	if (!A) return 0;
	int max;
	max = A[1];
	A[1] = A[n];
	n = n-1;
	heapify(A,n,1)
	return max;
}

void insere_fila(int *A, int n, int c){
	if (!A) return 0;
	A[n+1] = c;
	corrige_subindo(A,n+1)
}

int encontra_max(int *A, int n){
	if (!A) return 0;
	return A[1];
}

void aumenta_chave(int *A, int i, int c){
	if (!A) return 0;
	A[i] = c;
	corrige_subindo(A, i);
}

void diminui_chave(int *A, int n, int i, int c){
	if (!A) return 0;
	A[i] = c;
	heapify(A, n, i);
}
