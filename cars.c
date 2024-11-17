#include <stdio.h>
#include <stdlib.h>

// Im sure theres a more elegant way to do this with taking the raw value of the letter but thats stupid so I brute force it
int getSpeed(char letter){
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
    printf("\n");
    for(int i=0; i<length;i++){
        for (int i=0; i<10; i++){
            printf("%d", arr[i][0]);
        }
        printf("\n");
        for (int i=0; i<10; i++){
            printf("%d", arr[i][1]);
        }
        printf("\n");
        printf("\n");
        bnchs += step(arr, length);
        
        
    }
    return bnchs;
}




int main(void) {

    
// Get inputs
    



    int ncols = 10;
    int nrows = 2;
    int speeds[] = {getSpeed('D'),getSpeed('B'),getSpeed('A'),getSpeed('A')};
    int starts[] = {0,1,4,7};
    int numberOfCars = sizeof(starts) / sizeof(starts[0]);


    // Create Main Array [isCar, speed]
    int *A = (int *) malloc(nrows*ncols*sizeof(int));
    int **arr = (int **) malloc(ncols*sizeof(int *));
    for (int i=0; i<ncols; i++){
        arr[i] = A + i*nrows;
    }

    // Start assigning values
    for (int i = 0; i<ncols; i++){
        for (int j = 0; j<nrows; j++){
            arr[i][j] = 0;
        }
    }
    for (int i = 0; i<ncols; i++){
        for (int j = 0; j<numberOfCars; j++){
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


