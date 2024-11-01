# Parallelizing Bubble Sort

## Overview

In this assignment, you will apply the OpenMP library and the parallel concepts we
have been studying to the task of converting a serial algorithm, Bubble Sort, into
a parallel version. Then you will time and test two versions of the parallel implementation
against the serial implementation to see the results.

Finally, you will summarize and explain your results in a short report.


### Rubric

REDO THIS!!
* `report.txt` (3 points)
    - Text file contains a short paragraph that correctly identifies
    which function is slowest, and provides a **correct** explanation for why.
* `dynamic_array.c` (19 points)
   - Descriptive comment with your name at the top, good coding style (2 points)
   - Step 0: Allocates array correctly using malloc (3 points)
   - Step 1: `populate` function defined correctly (3 points)
   - Step 2: `square_roots` function defined correctly (3 points)
   - Step 3: `test` function defined correctly (3 points)
   - Step 4: `rand_update` function defined correctly (4 points)
   - Step 5: Frees the array at the end (1 point)

### Starter Files

* `Makefile`
    - A simple makefile that will compile your program
* `dynamic_array.c`
    - This file contains starter code for our program and the `main`
    function. You will define a set of helper functions, as well as
    making changes to the `main` function, and will time each major
    part of the process.
    - Note that this program allows command-line inputs, read more about that below!

### Execution

As always, the graders should be able to build, check, and clean your code:

```
make clean
make
./bubble 10 1 0
```

### Command-line arguments for `bubble`

The main program here takes in three optional command-line arguments. You must
give them in order: either none, or just the first, or the first and second, or all
three:
* An integer, the array length
* A boolean (0 or 1), whether to print the sorted data or not
* An integer (0, 1, or 2), to generate a random, increasing, or decreasing array
    
## Tasks to Complete

### Step 0: Understanding Bubble Sort

Bubble sort is one of the simplest algorithms for sorting an array of data. 

