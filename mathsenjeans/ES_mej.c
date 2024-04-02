#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define NB_GENERATIONS 500
#define NB_INDIVUDUALS 1200
#define NB_PROCESSORS 8
#define NB_PARENTS 120
#define RANDOM_PARENTS_RATE 0.5
#define MUTATION_RATE 0.1

typedef struct {
    int** matrix;
    int score;
} MatrixInfo;

// Function to count distinct elements in an array
int countDistinct(int arr[], int n, int processors[]) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        processors[arr[i]] = 1;
        int j;
        for (j = 0; j < i; j++)
            if (arr[i] == arr[j])
                break;
        if (i == j)
            count++;
    }
    return count;
}

int fitnessCoef(int** matrix, int l, int c) {
    int maxDistinct = 0;
    int processors[NB_PROCESSORS];
    for (int i = 0; i < NB_PROCESSORS; i++) {
        processors[i] = 0;
    }

    for (int i = 0; i < l; i++) {
        int distinct = countDistinct(matrix[i], c, processors);
        if (distinct > maxDistinct)
            maxDistinct = distinct;
    }
    for (int i = 0; i < c; i++) {
        int* column = (int*)malloc(l * sizeof(int));
        for (int j = 0; j < l; j++)
            column[j] = matrix[j][i];
        int distinct = countDistinct(column, l, processors);
        if (distinct > maxDistinct)
            maxDistinct = distinct;
        free(column);
    }
    int processors_not_used = NB_PROCESSORS;
    for (int i = 0; i < NB_PROCESSORS; i++) {
        if (processors[i] == 1){
            processors_not_used--;
            
        }
    }
    return (maxDistinct + (processors_not_used * processors_not_used));
}

// Compare the fitness coef of two arrays
int compare(const void* a, const void* b) {
    return ((MatrixInfo*)a)->score - ((MatrixInfo*)b)->score;
}

int mutation (int parent_gene) {
    float random_float = ((float)rand() / RAND_MAX);
    if (random_float <= MUTATION_RATE) {
        return (rand() % NB_PROCESSORS);
    }
    return parent_gene;
}

int main() {
    srand(time(NULL));
    int l = 3, c = 8;
    MatrixInfo parents[NB_PARENTS];
    MatrixInfo matrices[NB_INDIVUDUALS];

    // Create a array of NB_INDIVUDUALS, assigns them a fitness coefficient 
    // and sort them from smallest to largest 
    for (int m = 0; m < NB_INDIVUDUALS; m++) {
        matrices[m].matrix = (int**)malloc(l * sizeof(int*));
        for (int i = 0; i < l; i++) {
            matrices[m].matrix[i] = (int*)malloc(c * sizeof(int));
            for (int j = 0; j < c; j++)
                matrices[m].matrix[i][j] = rand() % NB_PROCESSORS;
        }
        matrices[m].score = fitnessCoef(matrices[m].matrix, l, c);
    }

    qsort(matrices, NB_INDIVUDUALS, sizeof(MatrixInfo), compare);

    // Chose parents by lowest fitness coef
    for (int i = 0; i < (NB_PARENTS - (RANDOM_PARENTS_RATE * NB_PARENTS)); i++) {
        parents[i].matrix = (int**)malloc(l * sizeof(int*));
        for (int j = 0; j < l; j++) {
            parents[i].matrix[j] = (int*)malloc(c * sizeof(int));
            memcpy(parents[i].matrix[j], matrices[i].matrix[j], c * sizeof(int));
        }
        parents[i].score = matrices[i].score;
    }

    // Chose parents randomly 
    for (int i = (NB_PARENTS - (RANDOM_PARENTS_RATE * NB_PARENTS)); i < NB_PARENTS; i++) {
        parents[i].matrix = (int**)malloc(l * sizeof(int*));
        for (int j = 0; j < l; j++) {
            parents[i].matrix[j] = (int*)malloc(c * sizeof(int));
            int randmatrix = (rand() % NB_INDIVUDUALS);
            memcpy(parents[i].matrix[j], matrices[randmatrix].matrix[j], c * sizeof(int));
        }
        parents[i].score = matrices[i].score;
    }

    // freed up space allocated to the previous generation
    for (int m = 0; m < NB_INDIVUDUALS; m++) {
        for (int i = 0; i < l; i++) {
            free(matrices[m].matrix[i]);
        }
        free(matrices[m].matrix);
    }

    // Evolution strategy
    for (int generation = 0; generation < NB_GENERATIONS; generation++) {

        // Creation of the new population
        int idx_child = 0;
        for (int idx_parent = 0; idx_parent < (NB_PARENTS - (RANDOM_PARENTS_RATE * NB_PARENTS)); idx_parent++) {

            for (int child = 0; child < NB_INDIVUDUALS / NB_PARENTS; child++) {

                matrices[idx_child].matrix = (int**)malloc(l * sizeof(int*));

                for (int i = 0; i < l; i++) {
                    matrices[idx_child].matrix[i] = (int*)malloc(c * sizeof(int));
                    for (int j = 0; j < c; j++) {
                        matrices[idx_child].matrix[i][j] = mutation(parents[idx_parent].matrix[i][j]);
                    }
                }
                matrices[idx_child].score = fitnessCoef(matrices[idx_child].matrix, l, c);
                idx_child++;
            }
        }
        
        for (int idx_parent = (NB_PARENTS - (RANDOM_PARENTS_RATE * NB_PARENTS)); idx_parent < NB_PARENTS; idx_parent++) {
            
            for (int child = 0; child < (NB_INDIVUDUALS / NB_PARENTS); child++) {

                matrices[idx_child].matrix = (int**)malloc(l * sizeof(int*));

                for (int i = 0; i < l; i++) {
                    matrices[idx_child].matrix[i] = (int*)malloc(c * sizeof(int));
                    for (int j = 0; j < c; j++) {
                        matrices[idx_child].matrix[i][j] = mutation(parents[idx_parent].matrix[i][j]);
                    }
                }
                matrices[idx_child].score = fitnessCoef(matrices[idx_child].matrix, l, c);
                idx_child++;
            }
        }


        // selection of the new parents
        qsort(matrices, NB_INDIVUDUALS, sizeof(MatrixInfo), compare);

        for (int m = 0; m < NB_PARENTS; m++) {
            for (int i = 0; i < l; i++) {
                free(parents[m].matrix[i]);
            }
            free(parents[m].matrix);
        }

        for (int i = 0; i < NB_PARENTS; i++) {
            parents[i].matrix = (int**)malloc(l * sizeof(int*));
            for (int j = 0; j < l; j++) {
                parents[i].matrix[j] = (int*)malloc(c * sizeof(int));
                memcpy(parents[i].matrix[j], matrices[i].matrix[j], c * sizeof(int));
            }
            parents[i].score = matrices[i].score;
        }

        for (int m = 0; m < NB_INDIVUDUALS; m++) {
            for (int i = 0; i < l; i++) {
                free(matrices[m].matrix[i]);
            }
            free(matrices[m].matrix);
        }
    }

    // Print the 10 finals best result

    printf("Top %d matrices with the lowest scores:\n", 10);
    for (int m = 0; m < 10; m++) {
        printf("Matrix %d (score: %d):\n", m + 1, parents[m].score);
        for (int i = 0; i < l; i++) {
            for (int j = 0; j < c; j++)
                printf("%d ", parents[m].matrix[i][j]);
            printf("\n");
        }
        printf("\n");
    }

    for (int m = 0; m < NB_PARENTS; m++) {
        for (int i = 0; i < l; i++) {
            free(parents[m].matrix[i]);
        }
        free(parents[m].matrix);
    }

    return 0;
}