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
#define nrand() (sqrt(-2 * log(frand())) * cos(2 * 3.141592653589793238 * frand()))

// Function Prototypes
// Generate a random real number uniformly distributed in [m, M]
double generate_uniform_real(double m, double M);
// Generate a random integer uniformly distributed in [m, M]
double generate_uniform_int(double m, double M);
// Generate a random real number from a normal distribution
double generate_normal(double mu, double sigma);
// Generate a random real integer number from a normal distribution
double generate_normal_int(double mu, double sigma);
// Generate a random integer from a truncated normal distribution
int generate_truncated_normal_int(double mu, double sigma, int min, int max);
// Generate a random real number from a truncated normal distribution
double generate_truncated_normal_real(double mu, double sigma, double min, double max);

// Calculate the mean of an array of numbers
double calculate_mean(double *values, int N);
// Calculate the standard deviation of an array of numbers
double calculate_stddev(double *values, int N);
// Write generated random values to the file
void write_to_file(FILE *f, double s2, double s3, int s4, double s5);
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

    // Arrays to store values for calculating mean and stddev for each distribution
    double *uniform_real_vals = (double *)malloc(N * sizeof(double));
    double *normal_real_vals = (double *)malloc(N * sizeof(double));
    double *uniform_int_vals = (double *)malloc(N * sizeof(double));
    double *normal_int_vals = (double*)malloc(N * sizeof(double));
    int *truncated_normal_int_vals = (int *)malloc(N * sizeof(int));
    double *truncated_normal_real_vals = (double *)malloc(N * sizeof(double));

    // Write column headers to the file and console for clarity
    fprintf(f, "Continuous Real\tNormal Real\tUniform Int\tNormal Int\tTrunc Int\tTrunc Real\n");
    printf("\n%-20s%-20s%-20s%-20s%-20s%-20s\n", "Continuous Real", "Normal Real", "Uniform Int", "Normal Int", "Trunc Int", "Trunc Real");
    printf("--------------------------------------------------------------------------------------------------------------------\n");

    // Generate random values and store them in arrays for mean and stddev calculation
    for (int i = 0; i < N; i++) {
        double s2 = generate_uniform_real(m, M);
        double s3 = generate_normal(mu, sigma);
        int s4 = generate_uniform_int(min_int, max_int);
        int s1 = generate_normal_int(mu, sigma);
        int s5 = generate_truncated_normal_int(mu, sigma, min_int, max_int);
        double s6 = generate_truncated_normal_real(mu, sigma, min_real, max_real);

        // Store the values for later mean and stddev calculation
        normal_int_vals[i] = s1;
        uniform_real_vals[i] = s2;
        normal_real_vals[i] = s3;
        uniform_int_vals[i] = s4;
        truncated_normal_int_vals[i] = s5;
        truncated_normal_real_vals[i] = s6;
        
        // Write the values to the file and print to the console
        fprintf(f, "%.5f\t%.5f\t%d\t%d\t%.5f\t%d\n", s2, s3, s4, s5, s6, s5);
        printf("%-20.5f%-20.5f%-20d%-20d%-20.5f%-20d\n", s2, s3, s4, s5, s6, s5);
    }

    // Calculate and print the mean and standard deviation for each distribution
    double mean_uniform_real = calculate_mean(uniform_real_vals, N);
    double stddev_uniform_real = calculate_stddev(uniform_real_vals, N);
    double mean_normal_real = calculate_mean(normal_real_vals, N);
    double stddev_normal_real = calculate_stddev(normal_real_vals, N);
    double mean_normal_int = calculate_mean((double*)normal_int_vals, N);
    double stddev_normal_int = calculate_stddev((double*)normal_int_vals, N);
    double mean_uniform_int = calculate_mean((double *)uniform_int_vals, N);  // Cast to double for consistency
    double stddev_uniform_int = calculate_stddev((double *)uniform_int_vals, N);
    double mean_truncated_normal_int = calculate_mean((double *)truncated_normal_int_vals, N);
    double stddev_truncated_normal_int = calculate_stddev((double *)truncated_normal_int_vals, N);
    double mean_truncated_normal_real = calculate_mean(truncated_normal_real_vals, N);
    double stddev_truncated_normal_real = calculate_stddev(truncated_normal_real_vals, N);

    // Print results for each distribution
    printf("\n\nMean and Standard Deviation for each distribution:\n-------------------------------------------------------------\n");
    printf("Uniform Real:\nMean = %.5f\nStddev = %.5f\n\n", mean_uniform_real, stddev_uniform_real);
    printf("Normal Real:\nMean = %.5f\nStddev = %.5f\n\n", mean_normal_real, stddev_normal_real);
    printf("Uniform Int:\nMean = %.5f\nStddev = %.5f\n\n", mean_uniform_int, stddev_uniform_int);
    printf("Normal Int:\nMean = %.5f\nStddev = %.5f\n\n", mean_normal_int, stddev_normal_int);
    printf("Truncated Normal Int:\nMean = %.5f\nStddev = %.5f\n\n", mean_truncated_normal_int, stddev_truncated_normal_int);
    printf("Truncated Normal Real:\nMean = %.5f\nStddev = %.5f\n\n", mean_truncated_normal_real, stddev_truncated_normal_real);

    // Output the mean and stddev for each distribution to the file
    fprintf(f, "\n\nMean and Standard Deviation for each distribution:\n-------------------------------------------------------------\n");
    fprintf(f, "Uniform Real:\nMean = %.5f\nStddev = %.5f\n\n", mean_uniform_real, stddev_uniform_real);
    fprintf(f, "Normal Real:\nMean = %.5f\nStddev = %.5f\n\n", mean_normal_real, stddev_normal_real);
    fprintf(f, "Uniform Int:\nMean = %.5f\nStddev = %.5f\n\n", mean_uniform_int, stddev_uniform_int);
    fprintf(f, "Normal Int:\nMean = %.5f\nStddev = %.5f\n\n", mean_normal_int, stddev_normal_int);
    fprintf(f, "Truncated Normal Int:\nMean = %.5f\nStddev = %.5f\n\n", mean_truncated_normal_int, stddev_truncated_normal_int);
    fprintf(f, "Truncated Normal Real:\nMean = %.5f\nStddev = %.5f\n\n", mean_truncated_normal_real, stddev_truncated_normal_real);

    fclose(f); // Close the file after writing
    free(uniform_real_vals);
    free(normal_real_vals);
    free(uniform_int_vals);
    free(normal_int_vals);
    free(truncated_normal_int_vals);
    free(truncated_normal_real_vals);

    return 0;
}

// Generate a random real number uniformly distributed in [m, M]
double generate_uniform_real(double m, double M) {
    return m + (M - m) * frand();
}

// Generate a random integer uniformly distributed in [m, M]
double generate_uniform_int(double m, double M) {
    int rand_val = m + (int)(frand() * (M - m + 1));  // Ensures the integer is within range
return rand_val;
//printf("Uniform rand_val: %.5d\n", rand_val);  // Debugging output
}
// Generate a random real number from a normal distribution
double generate_normal(double mu, double sigma) {
    return nrand() * sigma + mu;
}
// Generate a random real integer from a normal distribution
double generate_normal_int(double m, double sigma) {
    double norm_val = generate_normal(m, sigma);
    //printf("Normal rand_val: %.5f\n", norm_val);  // Debugging output
    return (int)round(norm_val);
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

// Function to calculate mean
double calculate_mean(double *values, int N) {
    double sum = 0;
    for (int i = 0; i < N; i++) {
        sum += values[i];
    }
    return sum / N;
}

// Function to calculate standard deviation
double calculate_stddev(double *values, int N) {
    double mean = calculate_mean(values, N);
    double sum_of_squares = 0;
    for (int i = 0; i < N; i++) {
        sum_of_squares += pow(values[i] - mean, 2);
    }
    return sqrt(sum_of_squares / (N - 1));
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