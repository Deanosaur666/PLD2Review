#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// make all functions recursive, no loops

void printArrayRecursive(int * arr, int len, int i) {
    if(len <= 0) {
        return;
    }
    else if(i >= len) {
        printf(" ]\n");
    }
    else if(i == 0) {
        printf("[ %d", arr[i]);
        printArrayRecursive(arr, len, i + 1);
    }
    else {
        printf(", %d", arr[i]);
        printArrayRecursive(arr, len, i + 1);
    }
}

void printArray(int * arr, int len) {
    printArrayRecursive(arr, len, 0);
}

void printArrayArrayRecursive(int ** arr, int rows, int cols, int i) {
    if(i < rows) {
        printArray(arr[i], cols);
        printArrayArrayRecursive(arr, rows, cols, i + 1);
    }
}

void printArrayArray(int ** arr, int rows, int cols) {
    printArrayArrayRecursive(arr, rows, cols, 0);
}

/*

[ 1, 2, 3, 4 ] 
[ 4, 2, 3, 1 ] swap 0 with (0 - 1) % len
[ 2, 4, 3, 1 ] swap 1 with (1 - 1) % len
[ 2, 3, 5, 1 ] swap 2 with (2 - 1) % len

*/

// cycle first element to the end n times, starting swapping with element i
void cycleRecursive(int arr[], int len, int n, int i) {
    if(n > 0) {
        if(i < len - 1) {
            // j is previous item, looping back to end
            int j = (i + len - 1) % len;
            // swap i and j
            int arri = arr[i];
            arr[i] = arr[j];
            arr[j] = arri;
            // swap next 2
            cycleRecursive(arr, len, i + 1, n);
        }
        else {
            // we finished swapping, so start a new cycle
            cycleRecursive(arr, len, 0, n - 1);
        }
    }
}

void cycle(int arr[], int len, int n) {
    cycleRecursive(arr, len, n, 0);
}

bool isPrimeRecursive(int n, int i) {
    // once we reach our target
    if(i >= n) {
        return true;
    }
    // is divisible
    else if(n % i == 0) {
        return false;
    }
    else {
        return isPrimeRecursive(n, i + 1);
    }
}

bool isPrime(int n) {
    if(n <= 1)
        return false;
    else
        return isPrimeRecursive(n, 2);
}

void selectRecursive(int in[], int inLen, int out[], int * outLen, int i, bool (*f)(int)) {
    if(i < inLen) {
        bool select = f(in[i]);
        if(select) {
            out[*outLen] = in[i];
            (*outLen) = *outLen + 1;
        }
        selectRecursive(in, inLen, out, outLen, i + 1, f);
    }
}

// lowercasse select has a name conflict for some reason
// remember to free returned value
int * Select(int arr[], int len, int * outLen, bool (*f)(int)) {
    int outArr[len]; // oversized
    *outLen = 0;
    selectRecursive(arr, len, outArr, outLen, 0, f);
    
    int * out = (int *)malloc(*outLen * sizeof(int));
    memcpy(out, outArr, *outLen * sizeof(int));
    
    return out;
}

// make an array 2D
void makeArray2D(int * * array, int rows, int cols, int i) {
    if(i < rows) {
        array[i] = array[0] + i * cols;
        makeArray2D(array, rows, cols, i + 1);
    }
}

void swapRowColumns(int ** dest, int ** source, int rows, int columns, int r, int c) {
    if(c < columns) {
        dest[r][c] = source[c][r];
        swapRowColumns(dest, source, rows, columns, r, c + 1);
    }
    else if(r < rows) {
        swapRowColumns(dest, source, rows, columns, r + 1, 0);
    }
}

// Write a function that converts an array of pairs into an array of arrays, preserving the order of the
// elements. For example, convert [[1,2], [3,4], [5,6]] should generate [[1,3,5], [2,4,6]].
int ** convert(int ** pairs, int len) {
    /*
    rows 
     |
     v -> columns
    [] -> [ 1, 2, 3, 4 ]
    [] -> [ 4, 5, 6, 7 ]
    [] -> ...
    ...
    arr[row][col]
    */
    
    // set up array array
    int rows = 2; // we are always receiving pairs, so our output will be a pair of arrays
    int cols = len;
    
    int ** array = malloc(rows * sizeof(int *));
	array[0] = malloc(rows * cols * sizeof(int));
	makeArray2D(array, rows, cols, 1);
	
	// we now have an array that's like arr[2][len]
	// we want to go from arr[len][2] to arr[2][len]
	
	// convert to recursive
	swapRowColumns(array, pairs, rows, cols, 0, 0);
	for(int i = 0; i < rows && false; i ++) {
	    for(int j = 0; j < cols; j ++) {
	        array[i][j] = pairs[j][i];
	    }
	}
	
	return array;
}

// to free result of convert
void freeArrArr(int ** arr) {
    free(arr[0]);
    free(arr);
}

int main() {
    int arr[] = { 1, 2, 3, 4, 5, 6, 7 };
    int len = 7;

    printf("Starting array:\n");
    printArray(arr, len);
    printf("Cycle array 3 times:\n");
    cycle(arr, len, 3);
    printArray(arr, len);

    printf("Is 4 prime? %s\n", isPrime(4) ? "Yes." : "No");
    printf("Is 7907 prime? %s\n", isPrime(7907) ? "Yes." : "No");
    printf("Is 7906 prime? %s\n", isPrime(7906) ? "Yes." : "No");
    
    int primeCount = 0;
    int * primes = Select(arr, len, &primeCount, isPrime);
    printf("%d primes in array:\n", primeCount);
    printArray(primes, primeCount);
    free(primes);
    
    // we can't do int pairs[3][2], since that can't be passed to the functions
    int * pairs[3];
    
    int r0[] = { 1, 2 };
    int r1[] = { 3, 4 };
    int r2[] = { 5, 6 };
    
    pairs[0] = r0;
    pairs[1] = r1;
    pairs[2] = r2;
    
    
    int rows = 3;
    int cols = 2;
    
    printf("Array of pairs:\n");
    printArrayArray(pairs, rows, cols);
    
    printf("Converted pair of arrays:\n");
    int ** converted = convert(pairs, rows);
    printArrayArray(converted, cols, rows);
    freeArrArr(converted);

    return 0;
}
