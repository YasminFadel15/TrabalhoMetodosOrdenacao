#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//função para gerar números inteiros aleatórios entre min e max, contando com eles
int gerarNumeroAleatorio(int min, int max) {
    return min + rand() % (max - min + 1);
}

//implementação dos algoritmos de ordenação

void troca(int *vetor, int i, int j) {
  int temp = vetor[i];
  vetor[i] = vetor[j];
  vetor[j] = temp;
}

void bubbleSort2(int vetor[], int n, int *trocas, int *comparacoes) {
  int i, trocou;
  *trocas = 0;
  *comparacoes = 0;

  do {
    trocou = 0; // false
    for (i = 0; i < n - 1; i++) {
      (*comparacoes)++;
      if (vetor[i] > vetor[i + 1]) {
        (*comparacoes)++;
        troca(vetor, i, i + 1);
        trocou = 1; // true
      }
    }
  } while (trocou);
}

void insertionSort(int vetor[], int n, int *trocas, int *comparacoes) {
    *trocas = 0;
    *comparacoes = 0;

    for (int i = 1; i < n; i++) {
        int pivo = vetor[i];
        int j = i - 1;
        (*comparacoes)++;
        while (j >= 0 && pivo < vetor[j]) {
            (*trocas)++;
            vetor[j + 1] = vetor[j];
            j--;
            (*comparacoes)++;
        }
        (*trocas)++;
        vetor[j + 1] = pivo;
    }
}

void heapify(int vetor[], int n, int i, int *trocas, int *comparacoes) {
    int raiz = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    (*comparacoes)++;
    if (esquerda < n && vetor[esquerda] > vetor[raiz])
        raiz = esquerda;

    (*comparacoes)++;
    if (direita < n && vetor[direita] > vetor[raiz])
        raiz = direita;

    if (raiz != i) {
        (*trocas)++;
        int temp = vetor[i];
        vetor[i] = vetor[raiz];
        vetor[raiz] = temp;
        heapify(vetor, n, raiz, trocas, comparacoes);
    }
}

void heapSort(int vetor[], int n, int *trocas, int *comparacoes) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(vetor, n, i, trocas, comparacoes);

    for (int i = n - 1; i > 0; i--) {
        (*trocas)++;
        int temp = vetor[0];
        vetor[0] = vetor[i];
        vetor[i] = temp;
        heapify(vetor, i, 0, trocas, comparacoes);
    }
}

void merge(int vetor[], int esquerda, int meio, int direita, int *trocas, int *comparacoes) {
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = vetor[esquerda + i];
    for (int j = 0; j < n2; j++)
        R[j] = vetor[meio + 1 + j];

    int i = 0;
    int j = 0;
    int k = esquerda;

    while (i < n1 && j < n2) {
        (*comparacoes)++;
        if (L[i] <= R[j]) {
            (*trocas)++;
            vetor[k] = L[i];
            i++;
        } else {
            (*trocas)++;
            vetor[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        (*trocas)++;
        vetor[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        (*trocas)++;
        vetor[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int vetor[], int esquerda, int direita, int *trocas, int *comparacoes) {
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;

        mergeSort(vetor, esquerda, meio, trocas, comparacoes);
        mergeSort(vetor, meio + 1, direita, trocas, comparacoes);

        merge(vetor, esquerda, meio, direita, trocas, comparacoes);
    }
}

int partition(int vetor[], int inicio, int fim, int *trocas, int *comparacoes) {
    int pivo = vetor[fim];
    int i = (inicio - 1);

    for (int j = inicio; j <= fim - 1; j++) {
        (*comparacoes)++;
        if (vetor[j] < pivo) {
            i++;
            (*trocas)++;
            int temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
        }
    }

    (*trocas)++;
    int temp = vetor[i + 1];
    vetor[i + 1] = vetor[fim];
    vetor[fim] = temp;

    return (i + 1);
}

void quickSort(int vetor[], int inicio, int fim, int *trocas, int *comparacoes) {
    if (inicio < fim) {
        int pi = partition(vetor, inicio, fim, trocas, comparacoes);

        quickSort(vetor, inicio, pi - 1, trocas, comparacoes);
        quickSort(vetor, pi + 1, fim, trocas, comparacoes);
    }
}

int getMax(int vetor[], int n) {
    int max = vetor[0];
    for (int i = 1; i < n; i++) {
        if (vetor[i] > max)
            max = vetor[i];
    }
    return max;
}

void countingSort(int vetor[], int n, int exp, int *trocas, int *comparacoes) {
    int saida[n];
    int frequencia[10] = {0};

    for (int i = 0; i < n; i++)
        frequencia[(vetor[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        frequencia[i] += frequencia[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        saida[frequencia[(vetor[i] / exp) % 10] - 1] = vetor[i];
        frequencia[(vetor[i] / exp) % 10]--;
        (*trocas)++;
    }

    for (int i = 0; i < n; i++) {
        vetor[i] = saida[i];
        (*comparacoes)++;
    }
}

void radixSort(int vetor[], int n, int *trocas, int *comparacoes) {
    int max = getMax(vetor, n);

    for (int exp = 1; max / exp > 0; exp *= 10)
        countingSort(vetor, n, exp, trocas, comparacoes);
}

int main() {
    srand(time(0)); //inicializa a semente do gerador de números aleatórios

    int tamanho_minimo = 1;
    int tamanho_maximo = 1000;
    int num_execucoes = 30;

    //cria um vetor para armazenar os resultados com os 6 métodos
    int resultados[tamanho_maximo][6]; 

    //loop para os diferentes tamanhos do conjunto de dados
    for (int tamanho = tamanho_minimo; tamanho <= tamanho_maximo; tamanho++) {
        int trocas[6] = {0}; //contagem de trocas para cada método de ordenação
        int comparacoes[6] = {0}; //contagem de comparações para cada método de ordenação

        //loop para execuções distintas
        for (int execucao = 0; execucao < num_execucoes; execucao++) {
            int dados[tamanho];

            //gera números aleatórios
            for (int i = 0; i < tamanho; i++)
                dados[i] = gerarNumeroAleatorio(1, 1000);

            //faz uma cópia dos dados para cada método de ordenação
            int dados_copy[6][tamanho];
            for (int i = 0; i < 6; i++)
                memcpy(dados_copy[i], dados, tamanho * sizeof(int));

            //bubble sort
            bubbleSort2(dados_copy[0], tamanho, &trocas[0], &comparacoes[0]);

            //insertion sort
            insertionSort(dados_copy[1], tamanho, &trocas[1], &comparacoes[1]);

            //heap sort
            heapSort(dados_copy[2], tamanho, &trocas[2], &comparacoes[2]);

            //merge sort
            mergeSort(dados_copy[3], 0, tamanho - 1, &trocas[3], &comparacoes[3]);

            //quick sort
            quickSort(dados_copy[4], 0, tamanho - 1, &trocas[4], &comparacoes[4]);

            //radix sort
            radixSort(dados_copy[5], tamanho, &trocas[5], &comparacoes[5]);
        }

        //calcula a média das trocas e comparações
        for (int i = 0; i < 6; i++) {
            trocas[i] /= num_execucoes;
            comparacoes[i] /= num_execucoes;
        }

        //armazena os resultados
        for (int i = 0; i < 6; i++) {
            resultados[tamanho - 1][i] = trocas[i] + comparacoes[i];
        }
    }

    //abre o arquivo para escrever os resultados em formato CSV
    FILE *csvFile = fopen("resultadosMetodos_.csv", "w");
    if (csvFile == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    //escreve o cabeçalho 
    fprintf(csvFile, "Tamanho,Bubble Sort,Insertion Sort,Heap Sort,Merge Sort,Quick Sort,Radix Sort\n");

    //escreve os resultados 
    for (int tamanho = tamanho_minimo; tamanho <= tamanho_maximo; tamanho++) {
        fprintf(csvFile, "%d,", tamanho);
        for (int i = 0; i < 6; i++) {
            fprintf(csvFile, "%d", resultados[tamanho - 1][i]);
            if (i < 5)
                fprintf(csvFile, ",");
        }
        fprintf(csvFile, "\n");
    }

    //fecha o arquivo
    fclose(csvFile);

    printf("Arquivo 'resultados.csv' gerado com sucesso!\n");

    return 0;
}
