#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fibonacci_recursive(int* fibo_sequence, int n){
    if (fibo_sequence[n] == -1) {
        fibo_sequence[n] = fibonacci_recursive(fibo_sequence, n - 1) + fibonacci_recursive(fibo_sequence, n - 2); 
    }
    return fibo_sequence[n];
}

int fibonacci1(int n) {
    if (n <= 2)
        return n;
    int* fibo_sequence = (int*)malloc((n + 1) * sizeof(int));
    fibo_sequence[0] = 0;
    fibo_sequence[1] = 1;
    fibo_sequence[2] = 2;
    for (int i = 3; i <= n; i++) {
        fibo_sequence[i] = -1;
    }
    int result = fibonacci_recursive(fibo_sequence, n);
    free(fibo_sequence);
    return result;
}

int fibonacci2(int n) {
    if (n == 0){
        return 0;
    }
    if (n == 1){
        return 1;
    }
    int fibo_sequence[] = {1, 2};
    for (int i = 3; i <= n; i++) {
        int next = fibo_sequence[0] + fibo_sequence[1];
        fibo_sequence[0] = fibo_sequence[1];
        fibo_sequence[1] = next;
    }
    int result = fibo_sequence[1];
    return result;
}

int fibonacci3(int n){
    if (n == 0){
        return 0;
    }
    if (n == 1){
        return 1;
    }
    if (n == 2){
        return 2;
    }
    else{
        return fibonacci3(n - 2) + fibonacci3(n - 1);
    }
}

int main(int argc, char* argv[]){
    if (argc != 3) {
        printf("Usage: %s <argument>\n", argv[0]);
        return 1;
    }
    int fibonacci_number;
    if (strcmp(argv[1], "1") == 0){
        fibonacci_number = fibonacci1(atoi(argv[2]));
    }
    if (strcmp(argv[1], "2") == 0){
        fibonacci_number = fibonacci2(atoi(argv[2]));
    }
    if (strcmp(argv[1], "3") == 0){
        fibonacci_number = fibonacci3(atoi(argv[2]));
    }
    printf("fibonacci number : %d\n", fibonacci_number);
    return 0;
}
