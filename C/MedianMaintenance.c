/**
 * Median Maintanence problem. This particular implementation prints the sum of medians.
 *
 * @author      Bogdan Constantinescu <bog_con@yahoo.com>
 * @since       2013.08.15
 * @version     1.0
 * @link        GitHub    https://github.com/z3ppelin/MedianMaintenance
 * @licence     The MIT License (http://opensource.org/licenses/MIT); see LICENCE.txt
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "MedianMaintenance.h"

/**
 * Main function. Reads vector, check if there are 2 values that   it, and prints the resultd
 * @param     argc       Command line arguments no.
 * @param     argv       Command line arguments.
 * @return               Success/error code. (0 is a success, anything else is error).
 */
int main(int argc, char** argv) {
	printf("------ Begin Median Maintanence ------\n");
	int n, i, half;
	long sumMedians = 0;
	int *v, *medians;
	clock_t start, end;
	char error[128];
	MinHeap minHeap; // in minheap we 'll keep the n / 2 most biggest values
	MaxHeap maxHeap; // in maxHeap we 'll kepp the n / 2 most smallest values

	/* read vector */
	if (argc == 1) {
		err("Err. The input file must be given as an argument.\n");
	}
	if (!readVectorFromFile(&v, &n, argv[1], error)) {
		err(error);
	}
	medians = (int*) malloc(sizeof(int) * n);

	half = n / 2;
	minHeap.heapDimension = half + 2;
	minHeap.lastFreePos = 0;
	minHeap.values = (int*) malloc(sizeof(int) * (half + 2));

	maxHeap.heapDimension = half + 2;
	maxHeap.lastFreePos = 0;
	maxHeap.values = (int*) malloc(sizeof(int) * (half + 2));

	/* print read vector */
	//printf("The read vector is: ");
	//printVector(v, n);
	//printf("\n");
	
	/* start calculating medians  */
	start = clock();
	if (n > 0) {
		insertMaxHeap(&maxHeap, v[0]);
		medians[0] = maxHeap.values[maxHeap.lastFreePos - 1];
		sumMedians += medians[0];
	}

	for (i = 1; i < n; i++) {
		if (v[i] <= maxHeap.values[0]) {
			insertMaxHeap(&maxHeap, v[i]);
		} else {
			insertMinHeap(&minHeap, v[i]);
		}

		/* rebalance heaps */
		if (minHeap.lastFreePos - maxHeap.lastFreePos > 1) {
			insertMaxHeap(&maxHeap, extractMin(&minHeap));
		} else if (maxHeap.lastFreePos - minHeap.lastFreePos > 1) {
			insertMinHeap(&minHeap, extractMax(&maxHeap));
		}

		int medianPos;
		if (i % 2) {
			medianPos = (i - 1) / 2;
		} else {
			medianPos = i / 2;
		}
		if (maxHeap.lastFreePos - 1 >= medianPos) {
			medians[i] = maxHeap.values[0];
		} else {
			medians[i] = minHeap.values[0];
		}
		sumMedians += medians[i];
	}
	end = clock();

	/* print results */
	printf("Medians sum = %d\n", sumMedians);

	//printf("Medians are: ");
	//printVector(medians, n);
	//printf("\n");

	/* free memory */
	free(v);
	free(minHeap.values);
	free(maxHeap.values);
	free(medians);

	printf("Elapsed: %f seconds.\n", (double) (end - start) / CLOCKS_PER_SEC);
	printf("------- End Median Maintanence -------\n");
	return EXIT_SUCCESS;
}

/**
 * Prints error and exits program.
 * @param    msg   The error to print.
 */
void err(const char* msg) {
	printf(msg);
	printf("------- End Median Maintanence -------\n");
	exit(EXIT_FAILURE);
}

/**
 * Reads array from file.
 * @param      v     The address of the array to store read elements.
 * @param      n     The address of the number of elements array has.
 * @param      file  The file where to read array from.
 * @param      err   An error message, if any occcurred during reading.
 * @return           1 if everything went fine, 0 otherwise. 
 */
int readVectorFromFile(int** v, int* n, char* file, char* err) {
	FILE *inputFile = fopen(file, "rt");
	int countReadedElements = 0, i = 0;

	if (inputFile == NULL) {
		strcpy(err, "Err. Could not open file.\n");
		return 0;
	}
	if (fscanf(inputFile, "%d", n) != 1) {
		fclose(inputFile);
		strcpy(err, "Err. Could not read number of elements.\n");
		return 0;
	}
	*v = (int*) malloc(sizeof(int) * (*n));
	while (!feof(inputFile)) {
		if (fscanf(inputFile, "%d", &(*v)[i++]) != 1) {
			break;
		}
		countReadedElements++;
	}
	fclose(inputFile);
	if (countReadedElements != *n) {
		strcpy(err, "Err. Number of declared elements does not match with the one found in file.\n");
		return 0;
	}
	return 1;
}

/**
 * Prints an array 's elements.
 * @param    v        The vector to print.
 * @param    n        The number of elements vector has.    
 */
void printVector(const int* v, const int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf("%d ", v[i]);
	}
}

/**
 * Inserts a new element in a heap maintaining the min-heap property.
 * @param		heap			The min heap.
 * @param		value  			The new element to insert.
 */
void insertMinHeap(MinHeap* heap, const int value) {
	if (heap->lastFreePos == heap->heapDimension) {
		err("Heap overflow");
	}
	heap->values[heap->lastFreePos] = value;
	int childPos = heap->lastFreePos, parentPos = (childPos - 1) / 2, aux;
	while (parentPos >= 0 && heap->values[parentPos] > heap->values[childPos]) {
		aux = heap->values[parentPos];
		heap->values[parentPos] = heap->values[childPos];
		heap->values[childPos] = aux;
		childPos = parentPos;
		parentPos = (childPos - 1) / 2;
	}
	heap->lastFreePos++;
}

/**
 * Inserts a new element in a heap maintaining the max-heap property.
 * @param		heap			The max heap.
 * @param		value  			The new element to insert.
 */
void insertMaxHeap(MaxHeap* heap, const int value) {
	if (heap->lastFreePos == heap->heapDimension) {
		err("Heap overflow");
	}
	heap->values[heap->lastFreePos] = value;
	int childPos = heap->lastFreePos, parentPos = (childPos - 1) / 2, aux;
	while (parentPos >= 0 && heap->values[parentPos] < heap->values[childPos]) {
		aux = heap->values[parentPos];
		heap->values[parentPos] = heap->values[childPos];
		heap->values[childPos] = aux;
		childPos = parentPos;
		parentPos = (childPos - 1) / 2;
	}
	heap->lastFreePos++;
}

/**
 * Extract the element with the smalles key in a heap and restores min-heap property.
 * @param	heap		The min heap.
 * @return	            The element with the smallest key in the heap.
 */
int extractMin(MinHeap* heap) {
	if (heap->lastFreePos == 0) {
		err("Empty heap");
	}

	int returnValue = heap->values[0], aux;
	heap->values[0] = heap->values[heap->lastFreePos - 1];
	heap->values[heap->lastFreePos - 1] = 0;
	heap->lastFreePos--;

	/* bubble down */
	int parentPos = 0, leftChildPos = (parentPos + 1) * 2 - 1, rightChildPos = leftChildPos + 1, minChildPos;
	while ((leftChildPos < heap->lastFreePos && heap->values[parentPos] > heap->values[leftChildPos])
			|| (rightChildPos < heap->lastFreePos && heap->values[parentPos] > heap->values[rightChildPos])) {
		minChildPos = leftChildPos;
		if (rightChildPos < heap->lastFreePos && heap->values[leftChildPos] > heap->values[rightChildPos]) {
			minChildPos = rightChildPos;
		}
		aux = heap->values[parentPos];
		heap->values[parentPos] = heap->values[minChildPos];
		heap->values[minChildPos] = aux;
		parentPos = minChildPos;
		leftChildPos = (parentPos + 1) * 2 - 1;
		rightChildPos = leftChildPos + 1;
	}
	return returnValue;
}

/**
 * Extract the element with the biggest key in a heap and restores max-heap property.
 * @param	heap		The max heap.
 * @return	            The element with the biggest key in the heap.
 */
int extractMax(MaxHeap* heap) {
	if (heap->lastFreePos == 0) {
		err("Empty heap");
	}

	int returnValue = heap->values[0], aux;
	heap->values[0] = heap->values[heap->lastFreePos - 1];
	heap->values[heap->lastFreePos - 1] = 0;
	heap->lastFreePos--;

	/* bubble down */
	int parentPos = 0, leftChildPos = (parentPos + 1) * 2 - 1, rightChildPos = leftChildPos + 1, minChildPos;
	while ((leftChildPos < heap->lastFreePos && heap->values[parentPos] < heap->values[leftChildPos])
			|| (rightChildPos < heap->lastFreePos && heap->values[parentPos] < heap->values[rightChildPos])) {
		minChildPos = leftChildPos;
		if (rightChildPos < heap->lastFreePos && heap->values[leftChildPos] < heap->values[rightChildPos]) {
			minChildPos = rightChildPos;
		}
		aux = heap->values[parentPos];
		heap->values[parentPos] = heap->values[minChildPos];
		heap->values[minChildPos] = aux;
		parentPos = minChildPos;
		leftChildPos = (parentPos + 1) * 2 - 1;
		rightChildPos = leftChildPos + 1;
	}
	return returnValue;
}
