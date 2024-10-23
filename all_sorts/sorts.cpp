#include "sorts.h"
#include <list>

void swap(int& n1, int& n2)
{
	int tmp = n1;
	n1 = n2;
	n2 = tmp;
}

int* sorts::shell_sort(int* arr, int* gaps, int size, int gaps_size) {
	if (size <= 1) {
		return arr;
	} 
	else {
		for (int g = 0; g < gaps_size; g++) { 
			int gap = gaps[g];
			for (int i = gap; i < size; i += gap) {
				int key = arr[i]; 
				int j = i; 
				while (j >= gap && arr[j - gap] > key) { 
					arr[j] = arr[j - gap]; 
					j -= gap; 
				}
				arr[j] = key; 
			}
		}
	}

	return arr;
}

int* sorts::quick_sort(int* arr, int size)
{
	if (size <= 1) return arr;

	int pivot = arr[rand() % size];
	int l_i = 0, m_i = 0, r_i = 0;

	int* l_arr = new int[size];
	int* m_arr = new int[size];
	int* r_arr = new int[size];

	for (int i = 0; i < size; i++) {
		if (arr[i] < pivot) {
			l_arr[l_i++] = arr[i];
		}
		else if (arr[i] > pivot) {
			r_arr[r_i++] = arr[i];
		}
		else {
			m_arr[m_i++] = arr[i];
		}
	}

	int* sorted_left = quick_sort(l_arr, l_i);
	int* sorted_right = quick_sort(r_arr, r_i);

	int* result = new int[size];
	std::copy(sorted_left, sorted_left + l_i, result);
	std::copy(m_arr, m_arr + m_i, result + l_i);
	std::copy(sorted_right, sorted_right + r_i, result + l_i + m_i);

	delete[] l_arr;
	delete[] m_arr;
	delete[] r_arr;

	return result;
}

int* sorts::merge_sort(int* arr, int size)
{
	if (size <= 1) return arr;

	int mid = size / 2;
	int r_size = size - mid;

	int* l_fake = new int[mid];
	int* r_fake = new int[r_size];

	for (int i = 0; i < mid; i++) {
		l_fake[i] = arr[i];
	}
	for (int i = 0; i < r_size; i++) {
		r_fake[i] = arr[mid + i];
	}

	merge_sort(l_fake, mid);
	merge_sort(r_fake, r_size);

	int i = 0, j = 0, k = 0;
	int* new_arr = new int[size];

	while (i < mid && j < r_size) {
		if (l_fake[i] < r_fake[j]) new_arr[k++] = l_fake[i++];
		else new_arr[k++] = r_fake[j++];
	}

	while (i < mid) new_arr[k++] = l_fake[i++];
	while (j < r_size) new_arr[k++] = r_fake[j++];

	for (int i1 = 0; i1 < size; i1++) {
		arr[i1] = new_arr[i1];
	}

	if (l_fake) delete[] l_fake;
	if (r_fake) delete[] r_fake;
	if (new_arr) delete[] new_arr;

	return arr;
}

int* sorts::insertion_sort(int* arr, int size)
{
	if (size <= 1) return arr;

	for (int i = 1; i < size; i++) {
		int elem = arr[i]; 
		int j = i;
		
		while (j >= 1 && arr[j - 1] > elem) {
			arr[j] = arr[j - 1];
			j--;
		}
		arr[j] = elem;
	}

	return arr;
}

int* sorts::selection_sort(int* arr, int size)
{
	if (size <= 1) return arr;

	for (int i = 0; i < size - 1; i++) {
		int min_idx = i;

		for (int j = i + 1; j < size; j++) {
			if (arr[j] < arr[min_idx]) {
				min_idx = j;
			}
		}
		
		swap(arr[i], arr[min_idx]);
	}

	return arr;
}

int* sorts::bubble_sort(int* arr, int size)
{
	if (size <= 1) return arr;

	for (int i = 0; i < size; i++) {
		bool flag = 1;
		for (int j = 0; j < size - (i + 1); j++) {
			if (arr[j] > arr[j + 1]) {
				flag = 0;
				swap(arr[j], arr[j + 1]);
			}
		}
		if (flag) return arr;
	}

	return arr;
}

int* sorts::heap_sort(int* arr, int size)
{
	if (size <= 1) return arr;

	for (int i = size - 1; i >= 0; i--) {
		heapify(arr, size, i);
	}

	for (int i = size - 1; i > 0; i--) {
		swap(arr[i], arr[0]);
		heapify(arr, i, 0);
	}

	return arr;
}

void sorts::heapify(int* arr, int size, int root_idx)
{
	int largest = root_idx;
	int l_kid = (2 * root_idx) + 1;
	int r_kid = (2 * root_idx) + 2;

	if (l_kid < size && arr[l_kid] > arr[largest]) largest = l_kid;

	if (r_kid < size && arr[r_kid] > arr[largest]) largest = r_kid;

	if (largest != root_idx) {
		swap(arr[root_idx], arr[largest]);
		heapify(arr, size, largest);
	}
}

int* sorts::reverse_quick_sort(int* arr, int size) {
	if (size <= 1) return arr;

	int pivot = arr[rand() % size];
	int l_i = 0, m_i = 0, r_i = 0;

	int* l_arr = new int[size];
	int* m_arr = new int[size];
	int* r_arr = new int[size];

	for (int i = 0; i < size; i++) {
		if (arr[i] < pivot) { 
			l_arr[l_i++] = arr[i];
		}
		else if (arr[i] > pivot) { 
			r_arr[r_i++] = arr[i];
		}
		else {
			m_arr[m_i++] = arr[i];
		}
	}

	int* sorted_left = reverse_quick_sort(l_arr, l_i);
	int* sorted_right = reverse_quick_sort(r_arr, r_i);

	int* result = new int[size];

	std::copy(sorted_right, sorted_right + r_i, result);
	std::copy(m_arr, m_arr + m_i, result + r_i);
	std::copy(sorted_left, sorted_left + l_i, result + r_i + m_i);

	delete[] l_arr;
	delete[] m_arr;
	delete[] r_arr;

	return result;
}

bool gaps::is_prime(int num)
{
	if (num < 2) {
		return false;
	}
	for (int x = 2; x <= static_cast<int>(sqrt(num)) + 1; ++x) {
		if (num % x == 0) {
			return false;
		}
	}
	return true;
}

int* gaps::my_simple_gaps(int n, int& gaps_size)
{
	int* temp = new int[n + 1];
	int count = 2;
	int size = 1;

	temp[0] = 1;

	while (count <= n) {
		if (is_prime(count)) {
			temp[size] = count;
			size++;
			count *= static_cast<int>(1.5 * exp((count - 1) / static_cast<double>(count)));
		}
		else {
			++count;
		}
	}

	int* gaps_1 = new int[size];

	for (int i = 0; i < size; i++) {
		gaps_1[i] = temp[i];
	}

	for (int i = 0; i < size / 2; ++i) {
		swap(gaps_1[i], gaps_1[size - i - 1]);
	}

	gaps_size = size;

	return gaps_1;
}

int* gaps::shell_gaps(int n, int& gaps_size)
{
	int* gaps = new int[log2(n)];
	gaps_size = 0;

	for (int i = n / 2; i > 1; i /= 2) {
		gaps[gaps_size] = i;
		gaps_size++;
	}
	int* real_gaps = new int[++gaps_size];

	for (int i = 0; i < gaps_size - 1; i++) {
		real_gaps[i] = gaps[i];
	}

	real_gaps[gaps_size - 1] = 1;

	if (gaps) delete[] gaps;

	return real_gaps;
}

int* gaps::hib_gaps(int n, int& gaps_size)
{
	int max_size = log2(n) + 1;
	int* gaps = new int[max_size];

	int res = 0;
	gaps_size = 0;

	for (int i = 0; res <= n; i++) {
		res = pow(2, i + 1) - 1;
		if (res > n) break;
		gaps[gaps_size++] = res;
	}

	int* real_gaps = new int[gaps_size];
	for (int i = 0; i < gaps_size; i++) {
		real_gaps[i] = gaps[gaps_size - 1 - i];
	}

	delete[] gaps;
	return real_gaps;
}

int* gaps::prat_gaps(int n, int& gaps_size)
{
	std::list<int> unique_sequence;

	for (int i = 0; (1 << i) <= n; ++i) {
		for (int j = 0; (1 << i) * static_cast<int>(pow(3, j)) <= n; ++j) {
			int value = (1 << i) * static_cast<int>(pow(3, j));
			if (value <= n) {
				if (std::find(unique_sequence.begin(), unique_sequence.end(), value) == unique_sequence.end()) {
					unique_sequence.push_back(value);
				}
			}
		}
	}

	std::vector<int> sorted_vector(unique_sequence.begin(), unique_sequence.end());
	std::sort(sorted_vector.begin(), sorted_vector.end(), std::greater<int>());

	gaps_size = sorted_vector.size();
	int* result_array = new int[gaps_size];
	std::copy(sorted_vector.begin(), sorted_vector.end(), result_array);

	return result_array;
}
