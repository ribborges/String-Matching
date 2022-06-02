/*
    Pontificia universidade católica de minas gerais
    Projeto e Analise de Algoritmos

    Richard de Carvalho Borges

    String Match
*/

# include <limits.h>
# include <string.h>
# include <stdio.h>
 
# define MAX_STRING 256

int max (int a, int b) {
    return (a > b)? a: b;
}

void badCharHeuristic( char *str, int size, int badchar[MAX_STRING]) {
    int i;

    for (i = 0; i < MAX_STRING; i++) {
        badchar[i] = -1;
    }

    for (i = 0; i < size; i++) {
        badchar[(int) str[i]] = i;
    }
}

int search( char *texto,  char *string) {
    int n = strlen(texto);
    int m = strlen(string);
    int badchar[MAX_STRING];

    int ns = 0;

    badCharHeuristic(string, m, badchar);
 
    int s = 0;

    while(s <= (n - m)) {
        int j = m-1;

        while(j >= 0 && string[j] == texto[s+j]) {
            j--;
        }
 
        if (j < 0) {
            s += (s+m < n)? m-badchar[texto[s+m]] : 1;
            ns++;
        }
 
        else {
            s += max(1, j - badchar[texto[s+j]]);
        }
    }

    return ns;
}

int main() {
    char texto[MAX_STRING];
    char string[MAX_STRING];
    char ch;
    int i = 0;

    char *arquivo = "teste.txt";
    FILE *fp = fopen(arquivo, "r");

    if (fp == NULL) {
        printf("\nArquivo '%s' não foi encontrado", arquivo);
        return 1;
    }

    printf("Insira a string que sera procurada: ");
    scanf("%s", string);

    while ((ch = fgetc(fp)) != EOF) {
        texto[i] = ch;
        i++;
    }

    fclose(fp);

    printf("%d", search(texto, string));
    return 0;
}