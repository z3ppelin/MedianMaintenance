/**
 * Header file for Median Maintanence problem.
 * 
 * @author      Bogdan Constantinescu <bog_con@yahoo.com>
 * @since       2013.08.15
 * @version     1.0
 * @link        GitHub    https://github.com/z3ppelin/MedianMaintenance
 * @licence     The MIT License (http://opensource.org/licenses/MIT); see LICENCE.txt
 */

#ifndef _MEDIAN_MAINTANENCE_H_
#define _MEDIAN_MAINTANENCE_H_

struct MinHeap {
	int lastFreePos; // last free position in heap
	int* values; // heap 's elements
	int heapDimension; // number of elements
};
typedef struct MinHeap MinHeap;

struct MaxHeap {
	int lastFreePos; // last free position in heap
	int* values; // heap 's elements
	int heapDimension; // number of elements
};
typedef struct MaxHeap MaxHeap;


/* function prototypes */
void err(const char*);
int readVectorFromFile(int**, int*, char*, char*);
void printVector(const int*, const int);
void insertMinHeap(MinHeap*, const int);
void insertMaxHeap(MaxHeap*, const int);
int deleteMinHeap(MinHeap*, const int);
int deleteMaxHeap(MaxHeap*, const int);
int extractMin(MinHeap*);
int extractMax(MaxHeap*);

#endif /* _MEDIAN_MAINTANENCE_H_ */
