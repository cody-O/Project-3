#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Im sure theres a more elegant way to do this with taking the raw value of the letter but thats stupid so I brute force it
int getSpeed(char letter){
    return letter - 'A' + 1;
}

int jumpCheck(int **arr, int start, int speed){
    int r = 0;
    for (int i = 0; i<speed;i++){
        if (arr[i+start+1][0]){
            r = 1;
        }
    }
    return r;
}

int step(int **arr, int length){
    int ret = 0;
    int ilength = length-1;
    // Stepping backwards as to not overwrite bunches that havent moved yet
    for(int i=ilength; i>-1;i--){
        if(arr[i][0]){
            //"lock in" bunch if it reaches the end
            if(i + arr[i][1] >= ilength){
                ret++;
            } else {
                // If bunch doesnt reach end or doesnt catch up to another bunch
                if(!jumpCheck(arr, i, arr[i][1])){
                    // Move Car
                    arr[i+arr[i][1]][0] = 1;
                    arr[i+arr[i][1]][1] = arr[i][1];
                    if(i + arr[i][1] < ilength){
                        // Move Car
                        arr[i+arr[i][1]][0] = 1;
                        arr[i+arr[i][1]][1] = arr[i][1];
                    }
                } 
            }
            // Delete old bunch
            arr[i][0] = 0;
            arr[i][1] = 0;
            
        }
    }
    return ret;
}

int runSimulation(int **arr, int length, int bunches){
    int bnchs = 0;
    if (bunches == 0){
        return -1;
    }
    for(int i=0; i<length;i++){
        bnchs += step(arr, length);
    }
    return bnchs;
}




int main(void) {
    while (1) {
        int ncols;
        char buffer[1024];
        char *char_list = NULL;
        int *starts = NULL;

        // Read the destination position
        if (scanf("%d", &ncols) != 1) break;

        // Read the line of car letters
        if (scanf("%s", buffer) != 1) break;
        size_t numCars = strlen(buffer);
        char_list = (char *)malloc((numCars + 1) * sizeof(char));
        if (!char_list) {
            fprintf(stderr, "Memory allocation failed for char_list\n");
            return 1;
        }
        strcpy(char_list, buffer);

        // Read the initial positions
        starts = (int *)malloc(numCars * sizeof(int));
        if (!starts) {
            fprintf(stderr, "Memory allocation failed for starts\n");
            free(char_list);
            return 1;
        }
        for (size_t i = 0; i < numCars; i++) {
            if (scanf("%d", &starts[i]) != 1) {
                free(char_list);
                free(starts);
                return 1;
            }
        }

        // Validate input
        for (size_t i = 0; i < numCars; i++) {
            if (starts[i] >= ncols) {
                printf("-1\n");
                free(char_list);
                free(starts);
                goto cleanup;
            }
        }

        // Initialize simulation grid
        int nrows = 2;
        int *A = (int *)calloc(nrows * ncols, sizeof(int));
        int **arr = (int **)malloc(ncols * sizeof(int *));
        if (!A || !arr) {
            fprintf(stderr, "Memory allocation failed for simulation array\n");
            free(char_list);
            free(starts);
            free(A);
            free(arr);
            return 1;
        }
        for (int i = 0; i < ncols; i++) {
            arr[i] = A + i * nrows;
        }

        // Populate grid with car positions and speeds
        for (size_t i = 0; i < numCars; i++) {
            arr[starts[i]][0] = 1;
            arr[starts[i]][1] = getSpeed(char_list[i]);
        }

        // Run the simulation and print the result
        printf("%d\n", runSimulation(arr, ncols, numCars));

        // Free dynamically allocated memory
        free(char_list);
        free(starts);
        free(A);
        free(arr);

        // Continue to the next input set
        cleanup:
        if (feof(stdin)) break;
    }

    return 0;
}


