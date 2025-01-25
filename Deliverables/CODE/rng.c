/******************************************************************************
 * File: random_number_generator.c
 * 
 * Purpose:
 * This program demonstrates the generation of random numbers using both uniform
 * and normal distributions, including support for:
 * 
 * 1. **Continuous Uniform Distribution**: Generates random real numbers 
 *    uniformly distributed in [m, M].
 * 2. **Normal Distribution**: Generates random real numbers from a normal
 *    distribution with specified mean and standard deviation.
 * 3. **Truncated Normal Distribution**: Generates random integers and real
 *    numbers from a truncated normal distribution within specified ranges.
 * 
 * Features:
 * - Generates random numbers using the above distributions.
 * - Outputs the generated values to the console.
 * - Writes a set of random sequences to a file in tab-separated format.
 * 
 * Output:
 * - Randomly generated values displayed on the console.
 * - A file "output.txt" containing generated sequences in tabular form.
 * 
 * Usage: (Updated Since I Changed The File Name)
 * - Compile: gcc rng.c -lm -o r
 * - Execute: ./r
 * - I used "r" because it is shorter to call in the executable but you can easily change it.
 * 
 * Experimentation Instructions:
 * 1. Change `m`, `M`, `mu`, `sigma`, and ranges during input to experiment with 
 *    different distributions and ranges.
 * 2. Modify the number of sequences written to the file for larger/smaller datasets.
 * 
 *****************************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// Macro for generating random real numbers uniformly in [0, 1)
#define frand() (rand() / (double)RAND_MAX) 

// Macro for generating random real numbers from a normal distribution
// Uses the Box-Muller transform for normal random number generation
#define nrand() (sqrt(-2 * log(frand())) * cos(2 * M_PI * frand()))

// Function Prototypes
// Generate a random real number uniformly distributed in [m, M]
double generate_uniform_real(double m, double M);
// Generate a random real number from a normal distribution
double generate_normal(double mu, double sigma);
// Generate a random integer from a truncated normal distribution
int generate_truncated_normal_int(double mu, double sigma, int min, int max);
// Generate a random real number from a truncated normal distribution
double generate_truncated_normal_real(double mu, double sigma, double min, double max);
// Write generated random values to the file
void write_to_file(FILE *f, double s2, double s3);
// Validate user inputs for correctness
void validate_input(double m, double M, double sigma, int N);

int main() {
    srand(time(NULL)); // Seed the random number generator with the current time

    // Variables for ranges, distributions, and number of samples
    double m, M, mu, sigma;
    int N, min_int, max_int;
    double min_real, max_real;

    // Input for uniform distribution range
    printf("Enter the minimum value (m) for uniform distributions: ");
    scanf("%lf", &m);
    printf("Enter the maximum value (M) for uniform distributions: ");
    scanf("%lf", &M);

    // Input for normal distribution parameters
    printf("Enter the mean (mu) for the normal distribution: ");
    scanf("%lf", &mu);
    printf("Enter the standard deviation (sigma) for the normal distribution: ");
    scanf("%lf", &sigma);

    // Input for truncated normal ranges
    printf("Enter the minimum integer value for truncated normal distribution: ");
    scanf("%d", &min_int);
    printf("Enter the maximum integer value for truncated normal distribution: ");
    scanf("%d", &max_int);
    printf("Enter the minimum real value for truncated normal distribution: ");
    scanf("%lf", &min_real);
    printf("Enter the maximum real value for truncated normal distribution: ");
    scanf("%lf", &max_real);

    // Input for the number of random numbers to generate
    printf("Enter the number of random sequences (N) to generate: ");
    scanf("%d", &N);

    // Validate inputs
    validate_input(m, M, sigma, N);

    // Output filename to save the generated sequences
    char filename[50] = "output.txt";

    // Open a file to write the random sequences
    FILE *f = fopen(filename, "w"); // Open file in write mode
    if (f == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Write column headers to the file and console for clarity
    fprintf(f, "Continuous\tNormal\tTruncInt\tTruncReal\n"); // File header
    printf("\n%-12s%-12s%-12s%-12s\n", "Continuous", "Normal", "TruncInt", "TruncReal");
    printf("-------------------------------------------------------\n");

    for (int i = 0; i < N; i++) {
        // Generate random values for each distribution
        double s2 = generate_uniform_real(m, M);
        double s3 = generate_normal(mu, sigma);
        int s4 = generate_truncated_normal_int(mu, sigma, min_int, max_int);
        double s5 = generate_truncated_normal_real(mu, sigma, min_real, max_real);

        // Write the values to the file and print to the console
        fprintf(f, "%.5f\t%.5f\t%d\t%.5f\n", s2, s3, s4, s5);
        printf("%-12.5f%-12.5f%-12d%-12.5f\n", s2, s3, s4, s5);
    }

    fclose(f); // Close the file after writing
    printf("Random sequences have been written to %s\n", filename);

    return 0;
}

// Generate a random real number uniformly distributed in [m, M]
double generate_uniform_real(double m, double M) {
    return m + (M - m) * frand();
}

// Generate a random real number from a normal distribution
double generate_normal(double mu, double sigma) {
    return nrand() * sigma + mu;
}

// Generate a random integer from a truncated normal distribution
int generate_truncated_normal_int(double mu, double sigma, int min, int max) {
    int value;
    do {
        value = (int)round(nrand() * sigma + mu);
    } while (value < min || value > max);
    return value;
}

// Generate a random real number from a truncated normal distribution
double generate_truncated_normal_real(double mu, double sigma, double min, double max) {
    double value;
    do {
        value = nrand() * sigma + mu;
    } while (value < min || value > max);
    return value;
}

// Write generated random values to the file
void write_to_file(FILE *f, double s2, double s3) {
    if (fprintf(f, "%.5f\t%.5f\n", s2, s3) < 0) {
        fprintf(stderr, "Error: Failed to write to file.\n");
        fclose(f);
        exit(EXIT_FAILURE);
    }
}

// Validate user inputs for correctness
void validate_input(double m, double M, double sigma, int N) {
    if (m >= M) {
        fprintf(stderr, "Error: Minimum value (m) must be less than maximum value (M).\n");
        exit(EXIT_FAILURE);
    }
    if (sigma <= 0) {
        fprintf(stderr, "Error: Standard deviation (sigma) must be positive.\n");
        exit(EXIT_FAILURE);
    }
    if (N <= 0) {
        fprintf(stderr, "Error: Number of sequences (N) must be greater than zero.\n");
        exit(EXIT_FAILURE);
    }
}
