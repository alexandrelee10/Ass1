/* Instructions:
 * ========================================================================================
 * Usage: 
 * - Compile: gcc rns.c -lm -o r
 * - Execute: ./r
 * - I used "r" because it is shorter to call in the executable but you can easily change it.
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#define frand() (rand() / (double)RAND_MAX)
#define nrand() (sqrt(-2 * log(frand())) * cos(2 * M_PI * frand()))
#define HISTOGRAM_BINS 50

void generate_random_numbers_to_file(const char *filename, int type, double m, double M, double mu, double sigma, int N);
int create_directory(const char *path);

int main()
{
    srand(time(NULL));
    double scenarios[3][5] = {
        {5, 1, 1, 8, 20},
        {pow(2, 10), pow(2, 8), 1, 2000, 200000},
        {pow(2, 12), 1.3 * pow(2, 10), 1, 8100, 2000000}};
    char *subfolders[3] = {"DATA/Scenario1", "DATA/Scenario2", "DATA/Scenario3"};
    create_directory("DATA");

    for (int i = 0; i < 3; i++)
    {
        double mu = scenarios[i][0];
        double sigma = scenarios[i][1];
        double m = scenarios[i][2];
        double M = scenarios[i][3];
        int N = (int)scenarios[i][4];

        create_directory(subfolders[i]);

        char filepath[100];
        snprintf(filepath, sizeof(filepath), "%s/uniform_integers.txt", subfolders[i]);
        generate_random_numbers_to_file(filepath, 1, m, M, mu, sigma, N);

        snprintf(filepath, sizeof(filepath), "%s/uniform_real_numbers.txt", subfolders[i]);
        generate_random_numbers_to_file(filepath, 2, m, M, mu, sigma, N);

        snprintf(filepath, sizeof(filepath), "%s/normally_distributed_integers.txt",subfolders[i]);
        generate_random_numbers_to_file(filepath, 1, m, M, mu, sigma, N);
        
        snprintf(filepath, sizeof(filepath), "%s/normal_distributed_real_numbers.txt", subfolders[i]);
        generate_random_numbers_to_file(filepath, 3, m, M, mu, sigma, N);

        snprintf(filepath, sizeof(filepath), "%s/truncated_normal_integers.txt", subfolders[i]);
        generate_random_numbers_to_file(filepath, 2, m, M, mu, sigma, N);

        snprintf(filepath, sizeof(filepath), "%s/truncated_normal_real_numbers.txt", subfolders[i]);
        generate_random_numbers_to_file(filepath, 3, m, M, mu, sigma, N);
    }
    return 0;
}

int create_directory(const char *path)
{
    if (mkdir(path, 0777) == 0 || errno == EEXIST)
    {
        return 0;
    }
    else
    {
        perror("Error creating directory");
        return -1;
    }
}
void generate_random_numbers_to_file(const char *filename, int type, double m, double M, double mu, double sigma, int N)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < N; i++)
    {
        double num = 0;
        switch (type)
        {
        case 1:
            num = (int)(m + rand() % ((int)M - (int)m + 1));
            break;
        case 2:
            num = m + frand() * (M - m);
            break;
        case 3:
            num = mu + nrand() * sigma;
            break;
        default:
            fprintf(stderr, "Invalid type\n");
            exit(EXIT_FAILURE);
        }
        fprintf(file, "%.6f\n", num);
    }
    fclose(file);
}