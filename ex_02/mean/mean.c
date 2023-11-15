#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("usage: %s in.csv in_mean.csv 0\n", argv[0]);
        return -1;
    }

    FILE* in;
    FILE* out;
    int index;
    int start;
    char line[1024];
    double value[20];
    int size;
    double mean;

    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if (strtold(argv[3], NULL) == 0) fprintf(out, "ArraySize,Mean\n");
    else fprintf(out, "EdgeSize,Mean\n");
    index = 0;
    start = 2;

    while (fgets(line, 1024, in) != NULL) {
        index++;
        if (index < start) continue;
        if ((index - start) % 20 == 0) {
            size = strtold(strtok(line, ","), NULL);
            value[(index - start) % 20] = strtold(strtok(NULL, ","), NULL);
        } else {
            strtok(line, ",");
            value[(index - start) % 20] = strtold(strtok(NULL, ","), NULL);
        }
        if ((index - start) % 20 == 19) {
            mean = 0;
            for (int i = 0; i < 20; i++) mean += value[i];
            mean /= 20;
            fprintf(out, "%d,%lf\n", size, mean);
        }
    }

    fclose(in);
    fclose(out);
    return 0;
}
