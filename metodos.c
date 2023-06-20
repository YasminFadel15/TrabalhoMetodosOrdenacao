#include <stdio.h>
#include <stdlib.h>

int mergesort(int[], int);
void _mergesort(int[], int, int, int*);
void merge(int[], int, int, int, int*);
void _mergesortBU(int[], int, int, int*);

int quicksort(int[], int);
void _quicksort(int[], int, int, int*);
int partition(int[], int, int, int*);

int radixsort(int[], int);
void countingsort(int[], int, int, int*);
int max(int[], int);

int* populaVetorMelhorCaso(int n) {
    int *v = malloc(sizeof(int) * n);
    int i;
    for (i = 0; i < n; i++) {
        v[i] = i;
    }
    return v;
}

int* populaVetorPiorCaso(int n) {
    int *v = malloc(sizeof(int) * n);
    int i;
    for (i = 0; i < n; i++) {
        v[i] = n - i;
    }
    return v;
}

int* populaVetorCasoMedio(int n) {
    int *v = malloc(sizeof(int) * n);
    int i;
    for (i = 0; i < n; i++) {
        v[i] = rand() % n;
    }
    return v;
}

void troca(int* v, int i, int j) {
    int aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

int bubblesort(int* v, int n) {
    int i,j,c = 0;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            c++; //comparação
            if (v[i] > v[j]) {
              troca(v, i, j);
              c++; //troca
            }
        }
    }
    return c;
}

int bubblesort2(int v[], int n) {
  int i, c, trocou;
  do {
    trocou = 0; // false
    for (i = 0; i < n - 1; i++) {
      c++;
      if (v[i] > v[i + 1]) {
        c++;
        troca(v, i, i + 1);
        trocou = 1; // true 
      }
    }
  } while (trocou);
  return c;
}

void exibeVetor(int* v, int n) {
    int i;
    printf("[ ");
    for (i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("]\n");
}

int* copiaVetor(int* v, int n) {
    int *copia = malloc(sizeof(int) * n);
    int i;
    for (i = 0; i < n; i++) {
        copia[i] = v[i];
    }
    return copia;
}

void heapify(int v[], int n, int i, int* c) {
    int raiz = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;
    
    (*c)++;
    if (esquerda < n && v[esquerda] > v[raiz]) {
        raiz = esquerda;
    }

    (*c)++;
    if (direita < n && v[direita] > v[raiz]) {
        raiz = direita;
    }
    
    if (raiz != i) {
        (*c)++;
        troca(v, i, raiz);
        heapify(v, n, raiz, c);
    }
}

int heapsort(int v[], int n) {
    int c = 0;
    int i;
    for (i = n / 2 - 1; i >= 0; i--) {
        heapify(v, n, i, &c);
    }
    
    for (i = n - 1; i > 0; i--) {
        c++;
        troca(v, 0, i);
        heapify(v, i, 0, &c);
    }

    return c;
}

int insertionsort(int v[], int n) {
    int pivo, j, c = 0;
    for (int i = 1; i < n; i++) {
        pivo = v[i];
        j = i - 1;
        c++; //comparação
        while (j >= 0 && pivo < v[j]) {
            c++; // troca
            v[j + 1] = v[j];  // desloca para a direita
            j--;
            c++; // comparação
        }
        c++; // troca
        v[j + 1] = pivo;
    }
    return c;
}

void merge(int v[], int inicio, int meio, int fim, int* c) {
    int aux[fim - inicio + 1];
    int i = inicio, j = meio + 1, k = 0;

    (*c)++;
    while (i <= meio && j <= fim) { // Intercala
        aux[k++] = v[i] <= v[j] ? v[i++] : v[j++];
        (*c)++;
    }

    (*c)++;
    while (i <= meio) {
        aux[k++] = v[i++];
        (*c)++;
    } 

    (*c)++;
    while (j <= fim) {
        aux[k++] = v[j++];
        (*c)++;
    }

    (*c)++;
    for (i = inicio, k = 0; i <= fim; i++, k++) {
        v[i] = aux[k];
        (*c)++;
    }
}

int mergesort(int v[], int n) {
    int c = 0;
    _mergesort(v, 0, n - 1, &c);
    return c;
}   

void _mergesort(int v[], int inicio, int fim, int* c) {
    int meio = (inicio + fim) / 2;
        
    if (inicio < fim) {
        _mergesort(v, inicio, meio, c);
        _mergesort(v, meio + 1, fim, c);
            
        merge(v, inicio, meio, fim, c);
    }
}

int mergesortBU(int v[], int n) {
  int c = 0;
  _mergesortBU(v, 0, n - 1, &c);
  return c;
}

void _mergesortBU(int v[], int inicio, int fim, int* c) {
  int i, meio;
  for (meio = 1; meio < fim - inicio + 1; meio *= 2 * meio) { 
    for (i = inicio; i <= fim - meio; i += 2 * meio) {
      int j = (i + (2 * meio)) - 1;
      if (j > fim) j = fim;
      
      merge(v, i, i + meio - 1, j, c);
    }
  }
}

int quicksort(int v[], int n) {
    int c = 0;
    _quicksort(v, 0, n - 1, &c);
    return c;
}

void _quicksort(int v[], int inicio, int fim, int* c) {
    if (inicio < fim) {
        int meio = partition(v, inicio, fim, c);
                
        _quicksort(v, inicio, meio - 1, c);  // Antes do pivô
        _quicksort(v, meio + 1, fim, c); // Após pivô
    }
}

int partition(int v[], int inicio, int fim, int* c) {
    int pivo = v[fim]; // Pivô será o último elemento da partição
    int i = (inicio - 1); // Indica a posição correta do pivô até então

    for (int j = inicio; j <= fim - 1; j++) {
        (*c)++;
        if (v[j] < pivo) { // Verifica se o elemento atual é menor que o pivô
            i++; // Incrementa o índice da posição correta do pivô
            (*c)++;
            troca(v, i, j); // Realiza a troca (swap) do elemento atual 
        }
    }
    (*c)++;
    troca(v, i + 1, fim); // Posiciona o pivô na posição correta
    return i + 1; // Informa o índice a ser utilizado para o próximo particionamento
}

void countingsort(int v[], int n, int exp, int* c) {
    int saida[n], frequencia[10]={}; // Dígitos de 0 a 9
    
    (*c)++;
    for (int i = 0; i < n; i++) { // Armazena a frequência de cada valor pelo índice
        frequencia[(v[i] / exp) % 10]++;
        (*c)++;
    }
    (*c)++;
    
    for (int i = 1; i < 10; i++) { // Armazena a soma do elemento atual com o elemento anterior
        frequencia[i] += frequencia[i - 1];
        (*c)++;
    }
    (*c)++;
        
    for (int i = n - 1; i >= 0; i--) { // Cria a saída a partir do vetor de entrada e da frequência
        (*c)++;
        saida[frequencia[(v[i] / exp) % 10] - 1] = v[i];
        frequencia[(v[i] / exp) % 10]--;
    }
    (*c)++;
    
    for (int i = 0; i < n; i++) { // Copia o vetor de saída para o vetor de entrada
        v[i] = saida[i];
        (*c)++;
    }
}

int max(int v[], int n) {
    int max = v[0];
    
    for (int i = 1; i < n; i++)
        if (v[i] > max)
            max = v[i];
    return max;
}

int radixsort(int v[], int n) {
    int c = 0;
    int m = max(v, n); // Obtém o maior número para conhecer a quantidade de dígitos
    
    for (int exp = 1; m / exp > 0; exp *= 10) //Realiza o counting sort para cada dígito
        countingsort(v, n, exp, &c); // exp é atualizada com 10^i, onde i é o dígito atual 10, 100, 1000, ...
    return c;
}


int main() {
    int n = 1000;
    int repeticoes = 30;
    int i;
    
    unsigned int operacoesBubblesort = 0;
    unsigned int operacoesBubblesort2 = 0;
    unsigned int operacoesHeapsort = 0;
    unsigned int operacoesInsertionSort = 0;
    unsigned int operacoesMergeSort = 0;
    unsigned int operacoesMergeSort2 = 0;
    unsigned int operacoesQuickSort = 0;
    unsigned int operacoesRadixSort = 0;

    for (i = 0; i < repeticoes; i++) {
        int* casoMedio = populaVetorCasoMedio(n);

        operacoesBubblesort += bubblesort(copiaVetor(casoMedio, n), n);
        operacoesBubblesort2 += bubblesort2(copiaVetor(casoMedio, n), n);
        operacoesHeapsort += heapsort(copiaVetor(casoMedio, n), n);
        operacoesInsertionSort += insertionsort(copiaVetor(casoMedio, n), n);
        operacoesMergeSort += mergesort(copiaVetor(casoMedio, n), n);
        operacoesMergeSort2 += mergesortBU(copiaVetor(casoMedio, n), n);
        operacoesQuickSort += quicksort(copiaVetor(casoMedio, n), n);
        operacoesRadixSort += radixsort(copiaVetor(casoMedio, n), n);
    }

    operacoesBubblesort /= repeticoes;
    operacoesBubblesort2 /= repeticoes;
    operacoesHeapsort /= repeticoes;
    operacoesInsertionSort /= repeticoes;
    operacoesMergeSort /= repeticoes;
    operacoesMergeSort2 /= repeticoes;
    operacoesQuickSort /= repeticoes;
    operacoesRadixSort /= repeticoes;

    printf("-------------------------------\n");
    printf("Bubblesort\n");
    printf("Caso medio: %d\n", operacoesBubblesort);
    printf("-------------------------------\n");
    printf("Bubblesort 2\n");
    printf("Caso medio: %d\n", operacoesBubblesort2);
    printf("-------------------------------\n");
    printf("Heapsort\n");
    printf("Caso medio: %d\n", operacoesHeapsort);
    printf("-------------------------------\n");
    printf("Insertionsort\n");
    printf("Caso medio: %d\n", operacoesInsertionSort);
    printf("-------------------------------\n");
    printf("Mergesort\n");
    printf("Caso medio: %d\n", operacoesMergeSort);    
    printf("-------------------------------\n");
    printf("MergesortBU\n");
    printf("Caso medio: %d\n", operacoesMergeSort2);  
    printf("-------------------------------\n");
    printf("Quicksort\n");
    printf("Caso medio: %d\n", operacoesQuickSort);    
    printf("-------------------------------\n");
    printf("Radixsort\n");
    printf("Caso medio: %d\n", operacoesRadixSort);    
    printf("-------------------------------\n");
    
    return 0;
}
