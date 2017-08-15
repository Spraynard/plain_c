#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

char * lowerCased(char * string) {
	char * returnString;
	strcpy(returnString, string);
	int i = 0;
	while (string[i]) {
		returnString[i] = tolower(string[i]);
		i++;
	}
	return returnString;
}

void printArray(int array[], int size) {
	printf("[");
	for (int i = 0; i < size; i++) {
		if (i == (size - 1)) {
			printf("%d", array[i]);
		} else {
			printf("%d, ", array[i]);
		}
	}
	printf("]\n");
}

int checkArray(int h_array[], int size) {
/* Summary: Performs a check on binary heap to see if there any values of zero. If there are then the code will be exited and shut down
 *
 * Input: `h_array` - The binary heap
 * 		  `size` - The binary heap size
 *
 * Returns: `0` if there is a 0 in the array. `1` if there is not a zero in the array.
 */
	for (int i = 0; i < size; i++) {
		if (h_array[i] == 0) {
			return 0;
		}
	}
	return 1;
}

int getLeftChild(int h_array[], int p_index, int size) {
/* Summary: Obtains the `left child` of Parent at given parent index (p_index)
 * 
 * Input: `h_array` - The binary heap
 * 		  `p_index` - The index of the parent that we are currently looking at
 *		  `size` - The size of the binary heap.
 *
 * Return: `0` if the index given points out of bounds of the array. Returns the child of parent at p_index if not
 */	
	int child = 0;
	if (p_index * 2 + 1 < size) {
		child = h_array[p_index * 2 + 1];
	}
	return child;
}

int getRightChild(int h_array[], int p_index, int size) {
/* Summary: Obtains the `right child` of Parent at given parent index (p_index)
 * 
 * Input: `h_array` - The binary heap
 * 		  `p_index` - The index of the parent that we are currently looking at
 *		  `size` - The size of the binary heap.
 *
 * Return: `0` if the index given points out of bounds of the array. Returns the child of parent at p_index if not
 */	
	int child = 0;
	if ((p_index * 2 + 2) < size) {
		child = h_array[p_index * 2 + 2];
	}
	return child;
}

void heapSort(int h_array[], int size, int min_max) {
/* Summary: Performs a heap sort on a binary heap array; parents with 2 children maximum.
 *			This could be used to implement a priority queue, as the node with the highest (or lowest)
 *			priority will be at the root of the list.
 * Input: `h_array` - the heap array to sort
 *		  `size` - The size of the heap array
 *        `min_max` - an input that will tell whether or not we want to return a 'maxed', or a 'min'd' binary heap.
 *						maxed will have highest priority at the root, and min'd will have the lowest priority at the root
 * 
 * Returns: Does not return. Performs all sorting operations on input array.
 **/
	int parent, leftChild, rightChild, p_holder, i = 0;
	while (i < (size / 2)) {
		parent = h_array[i];
		leftChild = getLeftChild(h_array, i, size);
		rightChild = getRightChild(h_array, i, size);

		if (min_max == 0 ) {
			while (parent < leftChild || parent < rightChild) {
				p_holder = parent;
				if (parent < leftChild) {
					h_array[i] = leftChild;
					h_array[(i * 2) + 1] = p_holder;
				} else if (parent < rightChild) {
					h_array[i] = rightChild;
					h_array[(i * 2) + 2] = p_holder;
				}
				i = 0;
				parent = h_array[i];
				leftChild = getLeftChild(h_array, i, size);
				rightChild = getRightChild(h_array, i, size);
			}
		i++;
		} else {
			while ((leftChild != 0 && parent > leftChild) || (rightChild != 0 &&parent > rightChild)) {
				p_holder = parent;
				if ((leftChild != 0) && parent > leftChild) {
					h_array[i] = leftChild;
					h_array[(i * 2) + 1] = p_holder;
				} else if ((rightChild != 0) && parent > rightChild) {
					h_array[i] = rightChild;
					h_array[(i * 2) + 2] = p_holder;
				}
				i = 0;
				parent = h_array[i];
				leftChild = getLeftChild(h_array, i, size);
				rightChild = getRightChild(h_array, i, size);
			}
		i++;
		}
	}
}

void heapAdd(int h_array[], int *a_size, int value, int *min_max_ptr) {
/* Summary: Adds a value to the binary heap
 * Input: `h_array` - The binary heap array
 * 		  `a_size` - The size of the array. A pointer to `size` located in main().
 *        `value` - The value that is to be inserted in the array
 * Returns: Void function. Performs all operations on inputted array.
 */

	*a_size += 1;
	h_array[*a_size - 1] = value;
	heapSort(h_array, *a_size, *min_max_ptr);
}

void heapSub(int h_array[], int *a_size, int *min_max_ptr) {
/* Summary: Subtracts the root value from the binary heap
 * Input: `h_array` - The binary heap array
 * 		  `a_size` - The size of the array. A pointer to `size` located in main().
 * Returns: Void function. Performs all operations on inputted array.
 */
	h_array[0] = h_array[*a_size - 1];
	h_array[*a_size - 1] = 0;
	*a_size -= 1; // Put here in order to not do any stupid calculations in the calls.
	heapSort(h_array, *a_size, *min_max_ptr);
}

int main(void) {
	char * user_input;
	int user_value;
	int debug = 0;

	// min_max = 0 to produce a max-heap, min_max = 1 to produce a min-heap
	int min_max = 0;
	int *min_max_ptr = &min_max;

	int size = 0;
	int *size_ptr = &size;

	int alloc_size = 1000;
	int * main_array = malloc(alloc_size * sizeof(int));

	do {
		if (alloc_size - size < 2) {
			printf("Reallocating the main_array size");
			alloc_size += 1000;
			main_array = realloc(main_array, alloc_size * sizeof(int));
			if (main_array == NULL) {
				printf("realloc addition failed, exiting");
				exit(1);
			}
		} else if (alloc_size - size > 1002) {
			alloc_size -= 1000;
			main_array = realloc(main_array, alloc_size * sizeof(int));
			if (main_array == NULL) {
				printf("Realloc subtraction failed, exiting");
				exit(1);
			}
		}
		printf("Current Heap:\n");
		printArray(main_array, size);
		// Debug
		if (debug) {
			printf("Current Heap Size: %i\n", size);
		}
		printf("What is your input?: ");
		scanf("%s", user_input);
		// Debug
		if (debug) {
			printf("Current user input is: %s\n", user_input);
		}
		if (strcmp(user_input, "add") == 0) {
			printf("What # will you be adding to the heap?: ");
			scanf("%i", &user_value);
			heapAdd(main_array, size_ptr, user_value, min_max_ptr);
		} else if (strcmp(user_input, "sub") == 0) {
			if (size == 0) {
				printf("Can't subtract any more from the heap.\n");
				continue;
			} else {
				printf("Subtracting %i from array\n", main_array[0]);
				heapSub(main_array, size_ptr, min_max_ptr);
			}
		} else if (strcmp(user_input, "debug") == 0) {
			printf("Do you want to toggle debug mode(y/n): ");
			scanf("%s", user_input);
			if (strcmp(user_input, "y") == 0) {
				debug = (debug == 0) ? 1 : 0;
				printf("Debug is: %i", debug);
			} else {
				continue;
			}
		} else {
			printf("Incorrect Input, please read the instructions more fully\n\n");
		}
		printf("\n");
	} while (strcmp(user_input, "q") != 0);
	free(main_array);
	return 0;
}