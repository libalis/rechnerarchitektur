#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    FILE* in;
    FILE* out;
    int index;
    char line[1024];
    double additionsPerSecond[20];
    double minimalRuntime;
    double mean;
    double variance;
    double standard_deviation;
    double standard_deviation_percentage;

    in = fopen("../ex_00/scripts/result.csv", "r");
    out = fopen("standard_deviation.csv", "w");
    index = 0;

    while (fgets(line, 1024, in) != NULL) {
        index++;
        if (index < 643) continue;
        strtok(line, ",");
        additionsPerSecond[(index - 643) % 20] = strtod(strtok(NULL, ","), NULL);
        if ((index - 643) % 20 == 0) {
            strtok(NULL, ",");
            minimalRuntime = strtod(strtok(NULL, ","), NULL);
        } else if ((index - 643) % 20 == 19) {
            mean = 0;
            for (int i = 0; i < 20; i++) mean += additionsPerSecond[i];
            mean /= 20;
            variance = 0;
            for (int i = 0; i < 20; i++) variance += (additionsPerSecond[i] - mean) * (additionsPerSecond[i] - mean);
            variance /= 20;
            standard_deviation = sqrt(variance);
            standard_deviation_percentage = (standard_deviation * 100) / mean;
            fprintf(out, "minimalRuntime: %lf, standard_deviation_percentage: %lf\n", minimalRuntime, standard_deviation_percentage);
        }
    }

    fclose(in);
    fclose(out);
    return 0;
}
