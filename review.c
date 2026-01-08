#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// make all functions recursive, no loops

void printArray(int * arr, int len, int i) {
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

int main() {
    int arr[] = { 1, 2, 3, 4, 5, 6 };

    printf("Starting array:\n");
    printArray(arr, 6, 0);
    printf("Cycle array 3 times:\n");
    cycle(arr, 6, 0, 3);
    printArray(arr, 6, 0);

    printf("Is 4 prime? %s\n", isPrime(4) ? "Yes." : "No");
    printf("Is 7907 prime? %s\n", isPrime(7907) ? "Yes." : "No");
    printf("Is 7906 prime? %s\n", isPrime(7906) ? "Yes." : "No");
    
    int primeCount = 0;
    int * primes = Select(arr, 6, &primeCount, isPrime);
    printf("%d primes in array:\n", primeCount);
    printArray(primes, primeCount, 0);
    free(primes);

    return 0;
}
