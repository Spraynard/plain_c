#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*void merge(int array[], size_t l_index, size_t r_index, size_t middle) {
	int l_size = middle - l_index + 1;
	int r_size = r_index - middle;

	int leftArray[l_size], rightArray[r_size];

	for (int i = 0; i < l_size; i++) {
		leftArray[i] = array[l_index + i];
	}
	for (int j = 0; j < r_size; j++) {
		rightArray[j] = array[middle + 1 + j];
	}

	printArray(leftArray, l_size, "Left Array: ");
	printArray(rightArray, r_size, "Right Array: ");

	int index_1 = 0;
	int index_2 = 0;
	int k = l_index;

	while (index_1 < l_size && index_2 < r_size) {
		if (leftArray[index_1] <= rightArray[index_2]) {
			array[k] = leftArray[index_1];
			index_1++;
		} else {
			array[k] = rightArray[index_2];
			index_2++;
		}
		k++;
	}

	while (index_1 < l_size) {
		array[k] = leftArray[index_1];
		index_1++;
		k++;
	}

	while (index_2 < r_size) {
		array[k] = rightArray[index_2];
		index_2++;
		k++;
	}
	// printArray(leftArray, l_size, "Left Array: ");
	// printArray(rightArray, r_size, "Right Array: ");

}


void mergeSort(int array[], size_t l_index, size_t r_index) {
	if (l_index < r_index) {
		int middle = (l_index + (r_index - 1)) / 2;
		printf("Middle: %i\n", middle);

		mergeSort(array, l_index, middle);
		mergeSort(array, middle + 1, r_index);

		merge(array, l_index, r_index, middle);
	}
}*/

int getALength() {
	return rand() % 50;
}

int getNumber() {
	return rand() % 1000;
}

void printArray(int array[], size_t size, char * string) {
	printf("%s\n", string);
	for (int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

void produceArray(int initArray[], size_t size) {
	for (int i = 0; i < size; i++) {
		initArray[i] = getNumber();
	}
}

int * subset(size_t start, size_t end, int array[]) {
	int subArraySize = end - start;
	int * sub_array = calloc(subArraySize, sizeof(int));
	int i = 0;
	while (start < end) {
		sub_array[i] = array[start];
		i++;
		start++;
	}
	return sub_array;
}

int * merge(int l_array[], int l_size, int r_array[], int r_size) {
	int o_size = l_size + r_size;
	int * mergedArray = calloc(o_size, sizeof(int));
	int i = 0;
	int j = 0;
	int k = 0;

	while (i < l_size && j < r_size) {
		if (l_array[i] <= r_array[j]) {
			mergedArray[k] = l_array[i];
			i++;
		} else {
			mergedArray[k] = r_array[j];
			j++;
		}
		k++;
	}

	while (i < l_size) {
		mergedArray[k] = l_array[i];
		i++;
		k++;
	}

	while (j < r_size) {
		mergedArray[k] = r_array[j];
		j++;
		k++;
	}
	return mergedArray;
}

int * sort(int array[], int size) {
	if (size > 1) {
  	int middle = size / 2;
  	int l_size = middle;
  	int r_size = ceil((double)size/2);
		int * leftArray = sort(subset(0, l_size, array), l_size);
		int * rightArray = sort(subset(l_size, size, array), r_size);
		return merge(leftArray, l_size, rightArray, r_size);
	}
	return array;
}

int main(void) {
	srand(time(NULL));

	size_t a_len = getALength();
	printf("Taking in a random length of: %zu\n", a_len);
	int array[a_len];
	produceArray(array, a_len);
	printArray(array, a_len, "Unsorted Array: ");
	// mergeSort(array, 0, a_len - 1);
	int * sortedArray = sort(array, a_len);
	printArray(sortedArray, a_len, "Sorted Array: ");
}