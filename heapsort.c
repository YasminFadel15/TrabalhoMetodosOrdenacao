#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int heapify(int* v, int n, int i, int c) {
    int raiz = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;
    if (esquerda < n && v[esquerda] > v[raiz]) raiz = esquerda; // Troca esquerda com raiz
    if (direita < n && v[direita] > v[raiz]) 
        raiz = direita; // Troca direita com raiz
    if (raiz != i) { // Verifica se a raiz precisa ser alterada
        troca(v, i, raiz); // Realiza a troca
        c++;
        c = heapify(v, n, raiz, c); // Garante recursivamente o heap máximo
    }
    return c;
}

int heapsort(int* v, int n) {
    // Cria o heap máximo a partir dos nós não folha (n / 2 - 1)
    // Valores maiores que n / 2 - 1 são nós folha
    int c = 0;
    for (int i = n / 2 - 1; i >= 0; i--) {
        c = heapify(v, n, i, c);
    }
    // Recria o heap máximo reduzindo o tamanho da heap a cada iteração (heap parcial)
    for (int i = n - 1; i > 0; i--) {
        troca(v, 0, i); // Troca o primeiro valor (maior) pelo último da heap parcial
        c++;
        c = heapify(v, i, 0, c); // Atualiza o heap máximo parcial
    }
    return c;
}

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

int main() {
    int n = 1000;
    
    srand(time(0));
    
    int* melhorCaso = populaVetorMelhorCaso(n);
    int* piorCaso = populaVetorPiorCaso(n);
    int* casoMedio = populaVetorCasoMedio(n);
    
    printf("Heapsort:\n");
    
    int iteracoesMelhorCaso = heapsort(copiaVetor(melhorCaso, n), n);
    printf("Melhor caso: %d\n", iteracoesMelhorCaso);
    
    int iteracoesPiorCaso = heapsort(copiaVetor(piorCaso, n), n);
    printf("Pior caso: %d\n", iteracoesPiorCaso);
    
    int iteracoesCasoMedio = heapsort(copiaVetor(casoMedio, n), n);
    printf("Caso médio: %d\n", iteracoesCasoMedio);

    free(melhorCaso);
    free(piorCaso);
    free(casoMedio);
}
