/*
 * File: bubblesort.c
 * TODO: Complete this comment, include your name
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <sys/time.h>
#include <omp.h>


void serial_bubblesort(int *array, long length);
void parallel_bubblesort(int *array, long length);

void genRandomArray(int *array, long length);
void genIncreasingArray(int *array, long length);
void genDecreasingArray(int *array, long length);

void copyArray(int *source, int *dest, long length);
void printArray(int *array, long length);
int print_error(char *msg);

/* main function:
 * gets array length from command line args, allocates a random array of that
 * size, allocates the counts array, the executes step 1 of the CountSort
 * algorithm (countsElem) followed by step 2 (writeArray).
*/
int main(int argc, char **argv) {
    long length = 100000;
    int verbose = 0;
    int option = 0;
    if (argc > 1) {
        // Set the length of the array from the first argument
        length = strtol(argv[1], NULL, 10);
    }
    if (argc > 2) {
        // Set whether to print a lot or a little from the second argument
        verbose = atoi(argv[2]);
    }
    if (argc > 3) {
        // Set the array option from  the third argument
        option = atoi(argv[3]);
    }

    //srand(10);  //uncomment this line to make random values predictably the same each run
    srand(time(NULL));  //uncomment this line to have random arrays every run


    //generate random array of elements of specified length
    int *sarray = malloc(length * sizeof(int));
    int *parray = malloc(length * sizeof(int));
    if (!sarray || !parray) print_error("ERROR: malloc failed");

    if (option == 0) {
        genRandomArray(sarray, length);
    }
    else if (option == 1) {
        genIncreasingArray(sarray, length);
    }
    else {
        genDecreasingArray(sarray, length);
    }
    copyArray(sarray, parray, length);

    //print out array before sort
    if (verbose) {
        printf("array before sort:\n");
        printArray(sarray, length);
    }
    
    double tstart, tend, time;

    tstart = omp_get_wtime();
    serial_bubblesort(sarray, length); //calls sort
    tend = omp_get_wtime();
    time = tend - tstart;
    printf("Run Time for Serial Bubblesort is %g\n", time);

    if (verbose) {
        printf("array after serial bubblesort:\n");
        printArray(sarray, length);
    }

    tstart = omp_get_wtime();
    parallel_bubblesort(parray, length); //calls sort
    tend = omp_get_wtime();
    time = tend - tstart;
    printf("Run Time for Parallel Bubblesort is %g\n", time);

    //print out array after sort
    if (verbose) {
        printf("result after parallel bubblesort:\n");
        printArray(parray, length);
    }
    free(sarray); //free memory
    free(parray); //free memory

    return 0;
}

/*
 * This function takes in an array of integers, and the length of the array,
 * and it performs a version of the Bubble Sort algorithm on the array, 
 * moving the data into increasing (or non-decreasing) order.
 */
void serial_bubblesort(int *array, long length) {
    int j, temp;
    char changes = 1;

    while (changes) {
        changes = 0;
        for (j = 0; j < length - 1; j++) {
            if (array[j] > array[j+1]) {
                changes = 1;
                temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;

            }
        }
    }
}

/*
 * TODO: Complete this function, including this comment
 */
void parallel_bubblesort(int *array, long length) {
    char changes = 1;
    int temp;

    while (changes) {
        changes = 0;
        //#pragma omp parallel for private(temp) //reduction(+:changes)
        for (int j = 0; j < length - 1; j+=2) {
            if (array[j] > array[j+1]) {
                changes += 1;
                temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
        //#pragma omp parallel for private(temp) // reduction(+:changes)
        for (int j = 1; j < length - 1; j+=2) {
            if (array[j] > array[j+1]) {
                changes = +1;
                temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;

            }
        }
    }
}


/* helper function: genRandomArray
 * fills an input array of specified length (length) with random 
   values from 0 to MAX-1
*/
void genRandomArray(int *array, long length) {
    int i;
    for (i = 0; i < length; i++) {
        array[i] = (int)rand();
    }
}

/* helper function: genIncreasingArray
 * fills an input array of specified length (length) with values
 from 0 to length - 1, increasing order
*/
void genIncreasingArray(int *array, long length) {
    int i;
    for (i = 0; i < length; i++) {
        array[i] = i;
    }
}
/* helper function: genDecreasingArray
 * fills an input array of specified length (length) with values
 from length to 1, decreasing order
*/
void genDecreasingArray(int *array, long length) {
    int i;
    for (i = 0; i < length; i++) {
        array[i] = length - i;
    }
}


/* helper function: printArray
 * prints out all the values in the input array separated by spaces
 */
void printArray(int *array, long length) {
    int i;
    for (i = 0; i < length; i++) {
        printf("%10d\n", array[i]);
    }
    printf("\n");
}

void copyArray(int *source, int *dest, long length) {
    for (int i = 0; i < length; i++) {
        dest[i] = source[i];
    }
}


/*error handling function: prints out error message*/
int print_error(char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(2);
}
