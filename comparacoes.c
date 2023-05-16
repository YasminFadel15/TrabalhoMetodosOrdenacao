#include <stdio.h>
#include <stdlib.h>

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
            c++;
            if (v[i] > v[j]) {
              troca(v, i, j);
              c++;
            }
        }
    }
    return c;
}

int bubblesort2(int v[], int n) {
  int i, c = 0, trocou;
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

int insertionsort(int* v, int s) {
    int pivo, j, c = 0;
    for (int i = 1; i < s; i++) {
        pivo = v[i];
        j = i - 1;
        
        c++;
        while (j >= 0 && pivo < v[j]) {
            c++;
            v[j + 1] = v[j]; // desloca para a direita
            j--;
            c++;
        }
        c++;
        v[j + 1] = pivo;
    }
    return c;
}

int main() {
    int n = 1000;
  
    int* melhorCaso = populaVetorMelhorCaso(n);
    int* piorCaso = populaVetorPiorCaso(n);
    int* casoMedio = populaVetorCasoMedio(n);
    
    printf("-------------------------------\n");
    printf("Bubblesort:\n");
    printf("Melhor caso: %d\n", bubblesort(copiaVetor(melhorCaso, n), n));
    printf("Pior caso: %d\n", bubblesort(copiaVetor(piorCaso, n), n));
    printf("Caso medio: %d\n", bubblesort(copiaVetor(casoMedio, n), n));
    printf("-------------------------------\n");
    printf("Bubblesort 2:\n");
    printf("Melhor caso: %d\n", bubblesort2(copiaVetor(melhorCaso, n), n));
    printf("Pior caso: %d\n", bubblesort2(copiaVetor(piorCaso, n), n));
    printf("Caso medio: %d\n", bubblesort2(copiaVetor(casoMedio, n), n));
    printf("-------------------------------\n");
    printf("Heapsort:\n");
    printf("Melhor caso: %d\n", heapsort(copiaVetor(melhorCaso, n), n));
    printf("Pior caso: %d\n", heapsort(copiaVetor(piorCaso, n), n));
    printf("Caso medio: %d\n", heapsort(copiaVetor(casoMedio, n), n));
    printf("-------------------------------\n");
    printf("Insertionsort:\n");
    printf("Melhor caso: %d\n", insertionsort(copiaVetor(melhorCaso, n), n));
    printf("Pior caso: %d\n", insertionsort(copiaVetor(piorCaso, n), n));
    printf("Caso medio: %d\n", insertionsort(copiaVetor(casoMedio, n), n));
}
