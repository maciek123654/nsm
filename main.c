#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#ifdef __ARM_NEON
#include <arm_neon.h>
#endif

#define SIZE 100

// Funkcje do generowania macierzy
void generate_matrix_int(int matrix[SIZE][SIZE], int start, int step) {
    int value = start;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matrix[i][j] = value;
            value += step;
            if (value > 100) value = start; // Cykl od 1 do 100
        }
    }
}

void generate_matrix_double(double matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matrix[i][j] = sin((i * SIZE + j) * M_PI / 180.0);
        }
    }
}

// Funkcja mnożenia macierzy - wersja podstawowa
void multiply_matrix_int(const int A[SIZE][SIZE], const int B[SIZE][SIZE], int C[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            C[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Funkcja mnożenia macierzy - wersja z NEON
#ifdef __ARM_NEON
void multiply_matrix_int_neon(const int A[SIZE][SIZE], const int B[SIZE][SIZE], int C[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int32x4_t sum = vdupq_n_s32(0); // SIMD - inicjalizacja wektora sum
            for (int k = 0; k < SIZE; k += 4) {
                int32x4_t a = vld1q_s32(&A[i][k]);     // Wczytanie 4 elementów z A
                int32x4_t b = vld1q_s32(&B[k][j]);     // Wczytanie 4 elementów z B
                sum = vmlaq_s32(sum, a, b);           // Mnożenie i sumowanie
            }
            int temp[4];
            vst1q_s32(temp, sum);                    // Przekopiowanie wyniku SIMD
            C[i][j] = temp[0] + temp[1] + temp[2] + temp[3];
        }
    }
}
#endif

// Pomocnicza funkcja pomiaru czasu
double measure_time(void (*func)(const int[SIZE][SIZE], const int[SIZE][SIZE], int[SIZE][SIZE]), 
                    const int A[SIZE][SIZE], const int B[SIZE][SIZE], int C[SIZE][SIZE]) {
    clock_t start = clock();
    func(A, B, C);
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// Main
int main() {
    int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];

    // Generowanie macierzy
    generate_matrix_int(A, 1, 1);
    generate_matrix_int(B, 1, 1);

    // Mnożenie macierzy - wersja podstawowa
    double basic_time = measure_time(multiply_matrix_int, A, B, C);
    printf("Czas wykonania: %.5f s\n", basic_time);

#ifdef __ARM_NEON
    // Mnożenie macierzy - wersja NEON
    double neon_time = measure_time(multiply_matrix_int_neon, A, B, C);
    printf("Czas wykonania (NEON): %.5f s\n", neon_time);
#endif

    return 0;
}
