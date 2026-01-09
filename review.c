#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// No loops are used. Recursive functions are used in place of loops

// I'm not bothering with an h file or forward declarations,
// so order of some stuff may look odd
// oh well

// ==========================
// print functions for output
// ==========================

// recursive version is called by main version, so regular
// printing doesn't need to provide i of 0
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
==========================
1. Write a function cycle that takes an array and an integer n as
input and cycles the first element of the list to the end n times.
==========================
*/

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
            cycleRecursive(arr, len, n, i + 1);
        }
        else {
            // we finished swapping, so start a new cycle
            cycleRecursive(arr, len, n - 1, 0);
        }
    }
}

void cycle(int arr[], int len, int n) {
    cycleRecursive(arr, len, n, 0);
}

/*
==========================
2. Write a function isPrime that returns true if and only if its integer
parameter is a prime number.
==========================
*/

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

/*
==========================
3. Write a function select that takes an array and a function f as a parameter.
Your function should apply f to each element of the array and should return a
new array containing only those elements of the original list for which f
returned true. For example, evaluating select ([1,2,3,4,5,6,7], is Prime)
should return [2,3,5,7].
==========================
*/

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

/*
==========================
4. Write a function that converts an array of pairs into an array of arrays,
preserving the order of the elements. For example,
convert [[1,2], [3,4], [5,6]] should generate [[1,3,5], [2,4,6]].
==========================
*/

// make an array 2D
void makeArray2D(int * * array, int rows, int cols, int i) {
    if(i < rows) {
        array[i] = array[0] + i * cols;
        makeArray2D(array, rows, cols, i + 1);
    }
}

void swapRowColumns(int ** dest, int ** source, int rows, int columns, int r, int c) {
    if(r < rows) {
        if(c < columns) {
            dest[r][c] = source[c][r];
            swapRowColumns(dest, source, rows, columns, r, c + 1);
        }
        else {
            swapRowColumns(dest, source, rows, columns, r + 1, 0);
        }
    }
}

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
	
	// recursive swapping function
	swapRowColumns(array, pairs, rows, cols, 0, 0);
	
	return array;
}

// to free result of convert
void freeArrArr(int ** arr) {
    free(arr[0]);
    free(arr);
}

/*
==========================
5. A binary search tree (BST) is a binary tree with special properties.
It may be Empty. It may be a Node (represented as a structure) containing
a left subtree, a data item x, and a right subtree. In this case all
the data items in the tree are different, all the items in the left
subtree are smaller than x, all the items in the right subtree are
greater than x, and the left and right subtrees arc also binary search
trees. Write a function makeBST that converts an array of integers into
a BST. The tree need not be balanced. You may assume that no item in the
array is repeated.
==========================
*/

typedef struct BST {
    int val;
    struct BST * left;
    struct BST * right;
} BST;

void BSTInsert(BST * bst, int n) {
    if(n > bst->val) {
        if(bst->right == NULL) {
            BST * right = (BST *)malloc(sizeof(BST));
            right->val = n;
            right->left = NULL;
            right->right = NULL;
            bst->right = right;
        }
        else {
            BSTInsert(bst->right, n);
        }
    }
    else {
        if(bst->left == NULL) {
            BST * left = (BST *)malloc(sizeof(BST));
            left->val = n;
            left->left = NULL;
            left->right = NULL;
            bst->left = left;
        }
        else {
            BSTInsert(bst->left, n);
        }
    }
}

void makeBSTRecursive(BST * bst, int * arr, int len, int i) {
    if(i < len) {
        BSTInsert(bst, arr[i]);
        makeBSTRecursive(bst, arr, len, i + 1);
    }
}

BST * makeBST(int * arr, int len) {
    BST * bst = (BST *)malloc(sizeof(BST));
    bst->left = NULL;
    bst->right = NULL;
    bst->val = arr[0];

    makeBSTRecursive(bst, arr, len, 1);

    return bst;
}

void freeBST(BST * bst) {
    if(bst != NULL) {
        freeBST(bst->left);
        freeBST(bst->right);
        free(bst);
    }
}

int BSTDepth(BST * bst) {
    if(bst == NULL)
        return 0;
    else {
        int left = BSTDepth(bst->left) + 1;
        int right = BSTDepth(bst->right) + 1;
        
        return left > right ? left : right;
    }
}

int BSTCount(BST * bst) {
    if(bst == NULL) 
        return 0;
    else
        return BSTCount(bst->left) + BSTCount(bst->right) + 1;
}

void BSTBFS(int * out, int i, BST * bst) {
    // need to find a way to print a BST
    
}

// it would be nice to have prettier BST output, but that's hard
// what is printed is still interpretable
char * BSTString(BST * bst) {
    if(bst == NULL)
        return NULL;
    int count = BSTCount(bst);
    char * buffer = (char *)malloc(20 * count * sizeof(char));
    char * left = BSTString(bst->left);
    char * right = BSTString(bst->right);

    // min size is 14
    sprintf(buffer, "(V:%d L:%s R:%s)", bst->val, left == NULL ? "X" : left, right == NULL ? "X" : right);
    free(left);
    free(right);

    return buffer;
}

void printBST(BST * bst) {
    char * str = BSTString(bst);
    printf("%s\n", str);
    free(str);
}

/*
==========================
6. Write a function searchBST that searches a BST for a given data element.
You should not search every node in the tree, but only those nodes that,
according to the definition, might contain the element you are looking for.
==========================
*/

bool searchBST(BST * bst, int n) {
    if(bst == NULL)
        return false;
    else if(n == bst->val)
        return true;
    else if(n < bst->val)
        return searchBST(bst->left, n);
    else if(n > bst-> val)
        return searchBST(bst->right, n);
}

/*
==========================
main function
==========================
*/

int main() {
    
    // 1. cycle
    int arr[] = { 1, 2, 3, 4, 5, 6, 7 };
    int len = 7;

    printf("Starting array:\n");
    printArray(arr, len);
    printf("Cycle array 3 times:\n");
    cycle(arr, len, 3);
    printArray(arr, len);

    // 2. isPrime
    printf("Is 4 prime? %s\n", isPrime(4) ? "Yes." : "No");
    printf("Is 7907 prime? %s\n", isPrime(7907) ? "Yes." : "No");
    printf("Is 7906 prime? %s\n", isPrime(7906) ? "Yes." : "No");
    
    // 3. select
    int primeCount = 0;
    int * primes = Select(arr, len, &primeCount, isPrime);
    printf("%d primes in array:\n", primeCount);
    printArray(primes, primeCount);
    free(primes);
    
    // 4. convert
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

    // 5. makeBST
    printf("Array to convert to BST:\n");
    int arr2[] = { 7, 1, 9, -1, 3, 10, 8 };
    int len2 = 7;
    printArray(arr2, len2);

    printf("BST of array:\n");
    BST * bst = makeBST(arr2, len2);
    printBST(bst);

    // 6. searchBST
    printf("Is 9 in the BST? %s\n", searchBST(bst, 9) ? "Yes." : "No");
    printf("Is -1 in the BST? %s\n", searchBST(bst, -1) ? "Yes." : "No");
    printf("Is 10 in the BST? %s\n", searchBST(bst, 10) ? "Yes." : "No");
    printf("Is 4 in the BST? %s\n", searchBST(bst, 4) ? "Yes." : "No");
    printf("Is -2 in the BST? %s\n", searchBST(bst, -2) ? "Yes." : "No");

    return 0;
}