#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    FILE* in;
    FILE* out;
    int index;
    int start;
    char line[1024];
    double adds_per_second[20];
    int minimal_runtime;
    double mean;
    double variance;
    double standard_deviation;

    in = fopen("../vec_sum/scripts/result.csv", "r");
    out = fopen("standard_deviation.csv", "w");
    fprintf(out, "MinimalRuntime,StandardDeviation\n");
    index = 0;
    start = 643;

    while (fgets(line, 1024, in) != NULL) {
        index++;
        if (index < start) continue;
        strtok(line, ",");
        adds_per_second[(index - start) % 20] = strtold(strtok(NULL, ","), NULL);
        if ((index - start) % 20 == 0) {
            strtok(NULL, ",");
            minimal_runtime = strtold(strtok(NULL, ","), NULL);
        } else if ((index - start) % 20 == 19) {
            mean = 0;
            for (int i = 0; i < 20; i++) mean += adds_per_second[i];
            mean /= 20;
            variance = 0;
            for (int i = 0; i < 20; i++) variance += (adds_per_second[i] - mean) * (adds_per_second[i] - mean);
            variance /= 20;
            standard_deviation = sqrt(variance);
            standard_deviation *= 100;
            standard_deviation /= mean;
            fprintf(out, "%d,%lf\n", minimal_runtime, standard_deviation);
        }
    }

    fclose(in);
    fclose(out);
    return 0;
}
