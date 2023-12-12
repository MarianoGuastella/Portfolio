#include <stdio.h>
#include <stdlib.h>

typedef enum TypeTag {
    ADD, MUL, SUB, DIV, FIBO, VALUE
} TypeTag;

typedef struct Node {
    TypeTag type;
    int value;
    int (*operation)(int, int);
    struct Node* left;
    struct Node* right;
} Node;

int add(int a, int b) {
    return a + b;
}

int multiply(int a, int b) {
    return a * b;
}

int subtract(int a, int b) {
    return a - b;
}

int fibonacci_recursive(int* fibo_sequence, int n){
    if (fibo_sequence[n] == -1) {
        fibo_sequence[n] = fibonacci_recursive(fibo_sequence, n - 1) + fibonacci_recursive(fibo_sequence, n - 2); 
    }
    return fibo_sequence[n];
}

int fibonacci(int n) {
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

Node* makeFunc(TypeTag type, int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = type;
    node->value = value;  // Set the value field with the provided value.
    node->operation = NULL;  // Default to NULL initially.
    node->left = NULL;
    node->right = NULL;
    switch (type) {
        case ADD:
            node->operation = add;
            break;
        case MUL:
            node->operation = multiply;
            break;
        case SUB:
            node->operation = subtract;
            break;
        default:
            // For FIBO and VALUE nodes, the operation function is not used.
            break;
    }
    return node;
}

int calc(Node* node) {
    if (node == NULL) {
        return 0;
    }
    if (node->type == VALUE) {
        return node->value;
    }
    int left = calc(node->left);
    int right = calc(node->right);
    if (node->operation != NULL) {
        node->value = node->operation(left, right);
    } else if (node->type == FIBO) {
        node->value = fibonacci(left);
    }
    return node->value;
}

int main() {
    Node* add = makeFunc(ADD, 0); // The value for ADD node will be updated during evaluation.
    add->left = makeFunc(VALUE, 10);
    add->right = makeFunc(VALUE, 6);

    Node* mul = makeFunc(MUL, 0); // The value for MUL node will be updated during evaluation.
    mul->left = makeFunc(VALUE, 5);
    mul->right = makeFunc(VALUE, 4);

    Node* sub = makeFunc(SUB, 0); // The value for SUB node will be updated during evaluation.
    sub->left = mul;
    sub->right = add;

    Node* fibo = makeFunc(FIBO, 5); // The value for FIBO node will be updated during evaluation.
    fibo->left = sub;

    int result_add = calc(add);
    int result_mul = calc(mul);
    int result_sub = calc(sub);
    int result_fibo = calc(fibo);

    printf("add : %d\n", result_add);
    printf("mul : %d\n", result_mul);
    printf("sub : %d\n", result_sub);
    printf("fibo : %d\n", result_fibo);

    free(add);
    free(mul);
    free(sub);
    free(fibo);

    return 0;
}