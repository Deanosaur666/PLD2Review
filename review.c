#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// make all functions recursive, no loops

void printArray(int arr[], int len, int i) {
    if(len <= 0) {
        return;
    }
    else if(i >= len) {
        printf(" ]\n");
    }
    else if(i == 0) {
        printf("[ %d", arr[i]);
        printArray(arr, len, i + 1);
    }
    else {
        printf(", %d", arr[i]);
        printArray(arr, len, i + 1);
    }
}

/*

[ 1, 2, 3, 4 ] 
[ 4, 2, 3, 1 ] swap 0 with (0 - 1) % len
[ 2, 4, 3, 1 ] swap 1 with (1 - 1) % len
[ 2, 3, 5, 1 ] swap 2 with (2 - 1) % len

*/

// cycle first element to the end n times, starting swapping with element i
void cycle(int arr[], int len, int i, int n) {
    if(n > 0) {
        if(i < len - 1) {
            // j is previous item, looping back to end
            int j = (i + len - 1) % len;
            // swap i and j
            int arri = arr[i];
            arr[i] = arr[j];
            arr[j] = arri;
            // swap next 2
            cycle(arr, len, i + 1, n);
        }
        else {
            // we finished swapping, so start a new cycle
            cycle(arr, len, 0, n - 1);
        }
    }
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
    return isPrimeRecursive(n, 2);
}

int * select(int arr[], int len, bool (*f)(int)) {

}

int main() {
    int arr[] = { 1, 2, 3, 4, 5, 6 };

    printf("Starting array:\n");
    printArray(arr, 6, 0);
    printf("Cycle array 3 times:\n");
    cycle(arr, 6, 0, 3);
    printArray(arr, 6, 0);

    //printf("Is 7 prime? %s")

    return 0;
}