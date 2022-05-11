#include <stdio.h>
#include <stdlib.h>

#define MAX_HEIGHT 100
#define MAX_WEIDTH 100

int main()
{
    char line[MAX_WEIDTH];
    char matrix[MAX_HEIGHT][MAX_WEIDTH];
    int a = -1, b = -1;
    int stroki = 0, stolbi = 0;
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.dot", "w");
    fputs("graph G {", out);
    while (fgets(line, 100, in)) {
        stolbi = 0;
        for (int i = 0; line[i]; i++) {
            if (line[i] != ' ') {
                matrix[stroki][stolbi] = line[i];
                stolbi++;
            }
        }
        stroki++;
    }

    for (int i = 0; i < stroki; ++i) {
        int flag = 0;
        for (int j = 0; j < stolbi; ++j) {
            if (matrix[i][j] == '1') {
                flag = 1;
            }
        }
        if (flag == 0) {
            fprintf(out, "\n\t%d;", i);
        }
    }

    for (int i = 0; i < stolbi; ++i) {
        b = -1;
        a = -1;
        for (int j = 0; j < stroki; ++j) {
            if (matrix[j][i] == '1') {
                b = a;
                a = j;
            }
        }
        if (b == -1) {
            fprintf(out, "\n\t%d--%d;", a, a);
        } else {
        fprintf(out, "\n\t%d--%d;", b, a);
        }
    }
    char otvet = 'Y';
    printf("Нужно ли добавлять ребро между вершинами[Y/N]: ");
    while (otvet == 'Y') {
        scanf("%c", &otvet);
        if (otvet == '\n') {
            scanf("%c", &otvet);
        }
        if (otvet == 'Y') {
            int a, b;
            printf("Введите номера вершин через пробел: ");
            scanf("%d%d", &a, &b);
            fprintf(out, "\n\t%d--%d;", a, b);
            printf("Нужно ли добавлять ребро между вершинами[Y/N]: ");
        }
    }
    fprintf(out, "\n\n}");
    fclose(out);
    fclose(in);
    system("dot output.dot -Tpng -o graph.png");
    return 0;
}