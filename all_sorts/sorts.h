#pragma once
#include <iostream>
#include <cmath>
#include <random>

class sorts
{
public:
	int* shell_sort(int* arr, int* gaps, int size, int gaps_size);
	int* quick_sort(int* arr, int size);
	int* merge_sort(int* arr, int size);
	int* insertion_sort(int* arr, int size);
	int* selection_sort(int* arr, int size);
	int* bubble_sort(int* arr, int size);
	int* heap_sort(int* arr, int size);

	int* reverse_quick_sort(int* arr, int size);

private:
	void heapify(int* arr, int size, int root_idx);
};

struct gaps {
public:
	bool is_prime(int num);

	int* my_simple_gaps(int n, int& gaps_size);
	int* shell_gaps(int n, int& gaps_size);
	int* hib_gaps(int n, int& gaps_size);
	int* prat_gaps(int n, int& gaps_size);
};
	
void swap(int& n1, int& n2);