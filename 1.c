#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define ARRSIZE 100000
#define PRINT_ARRAYS (ARRSIZE < 30)

double get_time();
void swap(int[], long, long);
void qs_sort(int[], long, long);
void bubble_sort(int[], long, long);
void bubble_sort_rev(int[], long, long);
void print_array(int[]);
int is_sorted(int[], int);

void test_sort(char* type, int array[], int size, int reverse, void (*function)(int[], long, long)) {
	int* arr = (int*) calloc(size, sizeof(int));
	memcpy(arr, array, size * sizeof(int));
	printf("Testing sort \"%s\"", type);
	if(reverse) printf(" (reverse)");
	printf("\n");
	print_array(arr);
	double time = get_time();
	function(arr, 0, size - 1);
	double delta = get_time() - time;
	if(is_sorted(arr, reverse)) {
		printf(" - time took: %lf\n", delta);
		print_array(arr);
	} else {
		printf("ERROR, array wasn't sorted properly\n");
	}
}
int main() {
	int* arr = (int*) calloc(ARRSIZE, sizeof(int));
	srand(time(0));
	for(int i = 0; i < ARRSIZE; ++i) {
		arr[i] = rand();
	}
	print_array(arr);
	test_sort("quicksort", arr, ARRSIZE, 0, qs_sort);
	test_sort("bubble", arr, ARRSIZE, 1, bubble_sort_rev);
	test_sort("bubble", arr, ARRSIZE, 0, bubble_sort);
	return 0;
}

int is_sorted(int arr[], int reverse) {
	for(int i = 1; i < ARRSIZE; ++i) {
		if(reverse ? arr[i - 1] < arr[i] : arr[i - 1] > arr[i])
			return 0;
	}
	return 1;
}

void bubble_sort_rev(int arr[], long pos1, long pos2) {
	for(int i = pos1; i <= pos2; ++i) {
		for(int j = pos1; j <= pos2 - 1; ++j) {
			if(arr[j] <= arr[j + 1]) {
				swap(arr, j, j + 1);
			}
		}
	}
}
void bubble_sort(int arr[], long pos1, long pos2) {
	for(int i = pos1; i <= pos2; ++i) {
		for(int j = pos1; j <= pos2 - 1; ++j) {
			if(arr[j] > arr[j + 1]) {
				swap(arr, j, j + 1);
			}
		}
	}
}

void swap(int array[], long pos1, long pos2) {
	long tmp;
	tmp = array[pos1];
	array[pos1] = array[pos2];
	array[pos2] = tmp;
}

void qs_sort(int array[], long start, long end)
{
  long head = start, tail = end - 1, tmp;
  long diff = end - start;
  long pe_index;

  if (diff < 1) return;
  if (diff == 1 && array[start] > array[end])
  {
    swap(array, start, end);
    return;
  }

  long m = (start + end) / 2;
  if (array[start] <= array[m])
  {
    if (array[m] <= array[end]) pe_index = m;
    else if (array[end] <= array[start]) pe_index = start;
    else pe_index = end;
  }
  else
  {
    if (array[start] <= array[end]) pe_index = start;
    else if (array[end] <= array[m]) pe_index = m;
    else pe_index = end;
  }
  long pe = array[pe_index];
  swap(array, pe_index, end);

  while (1)
  {
    while (array[head] < pe) ++head;
    while (array[tail] > pe && tail > start) --tail;
    if (head >= tail) break;
    swap(array, head++, tail--);
  }
  swap(array, head, end);
  long mid = head;
  qs_sort(array, start, mid - 1);
  qs_sort(array, mid + 1, end);
}

void print_array(int array[]) {
	if(!PRINT_ARRAYS) return;
	for(int i = 0; i < ARRSIZE; ++i) {
		printf("%5d ", array[i]);
	}
	printf("\n");
}

// https://stackoverflow.com/a/2349941
#ifdef WIN32

#include <windows.h>
double get_time()
{
    LARGE_INTEGER t, f;
    QueryPerformanceCounter(&t);
    QueryPerformanceFrequency(&f);
    return (double)t.QuadPart/(double)f.QuadPart;
}

#else

#include <sys/time.h>
#include <sys/resource.h>

double get_time()
{
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec*1e-6;
}

#endif
