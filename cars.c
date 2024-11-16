#include <stdio.h>
#include <stdlib.h>

int main(void) {

    
// Get inputs
     



    int ncols = 10;
    int nrows = 3;
    int speeds[] = {getSpeed('A'),getSpeed('A'),getSpeed('B'),getSpeed('B')};
    int starts[] = {1,3,5,7};
    int numberOfCars = sizeof(starts) / sizeof(starts[0]);


    // Create Main Array [isCar, speed]
    int *A = (int *) malloc(nrows*ncols*sizeof(int));
    int **arr = (int **) malloc(nrows*sizeof(int *));
    for (int i=0; i<nrows; i++){
        arr[i] = A + i*ncols;
    }

    // Start assigning values
    for (int i = 0; i<ncols; i++){
        for (int j = 0; j<nrows; j++){
            arr[i][j] = 0;
        }
    }
    for (int i = 0; i<ncols; i++){
        for (int j = 0; j<numberOfCars; i++){
            if (i == starts[j]){
                arr[i][0] = 1;
                arr[i][1] = speeds[j];
            }
        }
    }

    // Run Sim
    int response = runSimulation(arr, ncols, numberOfCars);

    printf("%d", response);




    return 0;

}

// Im sure theres a more elegant way to do this with taking the raw value of the letter but thats stupid so I brute force it
int getSpeeds(char letter){
    if (letter == 'A'){
        return 1;
    } else if (letter == 'B'){
        return 2;
    } else if (letter == 'C'){
        return 3;
    } else if (letter == 'D'){
        return 4;
    } else if (letter == 'E'){
        return 5;
    } else if (letter == 'F'){
        return 6;
    } else if (letter == 'G'){
        return 7;
    } else if (letter == 'H'){
        return 8;
    }else if (letter == 'I'){
        return 9;
    } else if (letter == 'J'){
        return 10;
    }
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

int step(int **arr, int length){
    int ret = 0;
    // Stepping backwards as to not overwrite bunches that havent moved yet
    for(int i=length-1; i>-1;i--){
        if(arr[i][0]){
            //"lock in" bunch if it reaches tghe end
            if(i + arr[i][1] > length){
                ret++;
            }
            // If bunch doesnt reach end or doesnt catch up to another bunch
            if(i + arr[i][1] < length || !arr[i+arr[i][1]][0]){
                // Move Car
                arr[i+arr[i][1]][0] = 1;
                arr[i+arr[i][1]][1] = arr[i][1];
            }
            // Delete old bunch
            arr[i][0] = 0;
            arr[i][1] = 0;
            
        }
    }
    return ret;
}
