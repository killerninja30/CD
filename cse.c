#include <stdio.h>
#include <string.h>

#define MAX_QUADS 20
#define MAX_EXPR_LEN 50

typedef struct {
    char op[5];
    char arg1[MAX_EXPR_LEN];
    char arg2[MAX_EXPR_LEN];
    char result[MAX_EXPR_LEN];
} Quadruple;

int is_same_expr(Quadruple *q1, Quadruple *q2) {
    // Check if two quadruples represent the same expression (commutative ops considered)
    if (strcmp(q1->op, q2->op) != 0) return 0;

    if (strcmp(q1->arg1, q2->arg1) == 0 && strcmp(q1->arg2, q2->arg2) == 0)
        return 1;
    // For commutative operators like + and *, check swapped args
    if ((strcmp(q1->op, "+") == 0 || strcmp(q1->op, "*") == 0) &&
        strcmp(q1->arg1, q2->arg2) == 0 && strcmp(q1->arg2, q2->arg1) == 0)
        return 1;

    return 0;
}

void common_subexpression_elimination(Quadruple quads[], int n) {
    char temp_map[MAX_QUADS][MAX_EXPR_LEN]; // Map from expression to result variable
    int temp_map_count = 0;

    for (int i = 0; i < n; i++) {
        int found = -1;
        for (int j = 0; j < i; j++) {
            if (is_same_expr(&quads[i], &quads[j])) {
                found = j;
                break;
            }
        }
        if (found != -1) {
            // Replace result with previous result to eliminate common subexpression
            printf("// Eliminating common subexpression: %s = %s %s %s replaced by %s\n",
                   quads[i].result, quads[i].arg1, quads[i].op, quads[i].arg2, quads[found].result);
            strcpy(quads[i].op, ":=");
            strcpy(quads[i].arg1, quads[found].result);
            strcpy(quads[i].arg2, "");
        }
    }

    // Print optimized quadruples
    printf("Optimized Quadruples:\n");
    for (int i = 0; i < n; i++) {
        if (strcmp(quads[i].op, ":=") == 0)
            printf("%s = %s\n", quads[i].result, quads[i].arg1);
        else
            printf("%s = %s %s %s\n", quads[i].result, quads[i].arg1, quads[i].op, quads[i].arg2);
    }
}

int main() {
    // Hardcoded quadruples input
    Quadruple quads[] = {
        {"*", "a", "b", "t1"},
        {"+", "t1", "c", "t2"},
        {"*", "a", "b", "t3"},
        {"+", "t3", "c", "t4"},
        {"+", "t1", "c", "t5"}
    };
    int n = sizeof(quads) / sizeof(quads[0]);

    printf("Original Quadruples:\n");
    for (int i = 0; i < n; i++) {
        printf("%s = %s %s %s\n", quads[i].result, quads[i].arg1, quads[i].op, quads[i].arg2);
    }
    printf("\n");

    common_subexpression_elimination(quads, n);

    return 0;
}
