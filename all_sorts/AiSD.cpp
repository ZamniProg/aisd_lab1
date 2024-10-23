#include <iostream>
#include <locale.h>
#include <ctime>
#include <chrono>
#include <fstream>
#include "sorts.h"


using namespace std;

const int N = 100;

bool is_sorted(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}

int* generate_array(int size, int min_value, int max_value) {
    int* array = new int[size];

    for (int i = 0; i < size; ++i) {
        array[i] = rand() % (max_value - min_value + 1) + min_value;
    }

    return array;
}

void test_for_lab(ofstream& ofs, ofstream& ofs1, int check_up=0) {
    std::cout << "\n\tНачало тестов для лабы.\n\n";
    int test_now = 0;
    int test_counts = 3;

    int gap_size = 0;
    int* gap = nullptr;
    int check_gap = 1;

    int num_of_sort = 7;

    int size_step = 15000;
    int size_max = 600000;

    if (!check_up) {
        std::cout << "\n\n\tВведи через клавишу Enter:\n1 - количество тестов\n2 - максимальное количество элементов\n3 - шаг количества элементов\n- ";
        std::cin >> test_counts;
        std::cout << "- ";
        std::cin >> size_max;
        std::cout << "- ";
        std::cin >> size_step;
        std::cout << "\n\n";
    }

    int start_size_max = size_max;
    int start_size_step = size_step;

    while (num_of_sort != 8) {
        if (check_up && (num_of_sort == 2 || num_of_sort == 3 || num_of_sort == 4 || num_of_sort == 1)) {
            size_max = 150000;
            size_step = 10000;
        }
        else if (check_up) {
            size_max = start_size_max;
            size_step = start_size_step;
        }
        cout << num_of_sort << "\n";
        if (!check_up) {
            std::cout << "\tВведи номер сортировки, которую хочешь использовать:\n";
            std::cout << "1 - ShellSort\n2 - InsertionSort\n3 - SelectionSort\n4 - BubbleSort\n";
            std::cout << "5 - HeapSort\n6 - MergeSort\n7 - QuickSort\n\n";
            std::cout << "Ввод - ";

            std::cin >> num_of_sort;
        }

        if (num_of_sort == 1) {
            ofs << "\tНачало тестов для ShellSort";
            if (!check_up) {
                ofs << "\n\n";
                std::cout << "\n\nВы выбрали ShellSort, поэтому стоит выбрать определенный шаг:\n1 - ShellGap\n2 - PrattGap\n3 - HibbardGap\n4 - MyGap(test)\nВвод - ";
                std::cin >> check_gap;
            }
            else {
                if (check_gap == 1) ofs << " - Shell Gaps\n\n";
                else if (check_gap == 2) ofs << " - Pratt Gaps\n\n";
                else if (check_gap == 3) ofs << " - Hibbard Gaps\n\n";
                else {
                    ofs << " - My Gaps(test)\n\n";
                }
            }
        }
        else if (num_of_sort == 2) ofs << "\tНачало тестов для InsertionSort\n\n";
        else if (num_of_sort == 3) ofs << "\tНачало тестов для SelectionSort\n\n";
        else if (num_of_sort == 4) ofs << "\tНачало тестов для BubbleSort\n\n";
        else if (num_of_sort == 5) ofs << "\tНачало тестов для HeapSort\n\n";
        else if (num_of_sort == 6) ofs << "\tНачало тестов для MergeSort\n\n";
        else ofs << "\tНачало тестов для QuickSort\n\n";

        sorts sorter;

        gaps gap_generator;

        for (int k = 0; k < 4; k++) {
            int i = 0;
            for (check_up ? i = 0 : i = 0; i <= size_max;) {
                if (check_up) {
                    if (i < 25000) i += 2500;
                    else if (i < 50000) i += 5000;
                    else if (i < 100000) i += 10000;
                    else i += size_step;
                }
                else i += size_step;
                //i += size_step;
                if (i > size_max) break;
                chrono::duration<double>* average_time = new chrono::duration<double>[test_counts];
                chrono::duration<double> a_time = chrono::duration<double>();

                for (int test_no = 0; test_no < test_counts; ++test_no) {
                    int* arr = new int[1];

                    if (k == 0) {
                        arr = generate_array(i, -10000, 10000);
                        arr = sorter.quick_sort(arr, i);
                    }
                    else if (k == 1) {
                        arr = generate_array(i, -10000, 10000);
                        arr = sorter.reverse_quick_sort(arr, i);
                    }
                    else if (k == 2) {
                        int st = 0;

                        int* new_arr = new int[i - (i / size_step)];
                        new_arr = sorter.quick_sort(generate_array(i - (i / size_step), -10000, 10000), i - (i / size_step));

                        int* random_elements = new int[i / size_step];
                        random_elements = generate_array(i / size_step, -10000, 10000);

                        arr = new int[i];

                        for (int z = 0; z < i - (i / size_step); z++) {
                            arr[z] = new_arr[z];
                        }

                        for (int z = i - (i / size_step); z < i; z++) {
                            arr[z] = random_elements[st++];
                        }
                    }
                    else {
                        arr = generate_array(i, -10000, 10000);
                    }

                    if (arr == nullptr) {
                        std::cerr << "Ошибка выделения памяти для массива!\n";
                        return;
                    }

                    if (check_gap) {
                        switch (check_gap) {
                        case 1:
                            gap = gap_generator.shell_gaps(i, gap_size);
                            break;
                        case 2:
                            gap = gap_generator.prat_gaps(i, gap_size);
                            break;
                        case 3:
                            gap = gap_generator.hib_gaps(i, gap_size);
                            break;
                        case 4:
                            gap = gap_generator.my_simple_gaps(i, gap_size);
                            break;
                        default:
                            std::cerr << "Неверный выбор промежутка!\n";
                            delete[] arr;
                            return;
                        }

                        if (gap == nullptr) {
                            std::cerr << "Ошибка выделения памяти для промежутков!\n";
                            delete[] arr;
                            return;
                        }
                    }

                    auto start = chrono::high_resolution_clock::now();

                    switch (num_of_sort) {
                    case 1: arr = sorter.shell_sort(arr, gap, i, gap_size); break;
                    case 2: arr = sorter.insertion_sort(arr, i); break;
                    case 3: arr = sorter.selection_sort(arr, i); break;
                    case 4: arr = sorter.bubble_sort(arr, i); break;
                    case 5: arr = sorter.heap_sort(arr, i); break;
                    case 6: arr = sorter.merge_sort(arr, i); break;
                    case 7: arr = sorter.quick_sort(arr, i); break;
                    default: std::cerr << "Неверный номер сортировки!" << std::endl;
                        delete[] arr;
                        return;
                    }

                    auto end = chrono::high_resolution_clock::now();
                    chrono::duration<double> duration = end - start;

                    average_time[test_no] = duration;

                    delete[] arr;

                    if (check_gap) delete[] gap;
                }

                for (int j = 0; j < test_counts; j++) {
                    a_time += average_time[j];
                }
                a_time /= test_counts;   

                if (k == 0) {
                    ofs << "Тест #" << i / size_step << " для полностью ОТСОРТИРОВАННОГО массива размера " << i
                        << ": " << "УСПЕШНО"
                        << " - Среднее время: " << a_time.count() << " секунд" << std::endl;
                    cout << "Тест #" << i / size_step << " для полностью ОТСОРТИРОВАННОГО массива размера " << i
                        << ": " << "УСПЕШНО"
                        << " - Среднее время: " << a_time.count() << " секунд" << std::endl;
                }
                else if (k == 1) {
                    ofs << "Тест #" << i / size_step << " для ОБРАТНО отсортированного массива размера " << i
                        << ": " << "УСПЕШНО"
                        << " - Среднее время: " << a_time.count() << " секунд" << std::endl;
                    cout << "Тест #" << i / size_step << " для ОБРАТНО отсортированного массива размера " << i
                        << ": " << "УСПЕШНО"
                        << " - Среднее время: " << a_time.count() << " секунд" << std::endl;
                }
                else if (k == 2) {
                    ofs << "Тест #" << i / size_step << " для ЧАСТИЧНО отсортированного массива размера " << i
                        << ": " << "УСПЕШНО"
                        << " - Среднее время: " << a_time.count() << " секунд" << std::endl;
                    cout << "Тест #" << i / size_step << " для ЧАСТИЧНО отсортированного массива размера " << i
                        << ": " << "УСПЕШНО"
                        << " - Среднее время: " << a_time.count() << " секунд" << std::endl;
                }
                else {
                    ofs << "Тест #" << i / size_step << " для СЛУЧАЙНОГО массива размера " << i
                        << ": " << "УСПЕШНО"
                        << " - Среднее время: " << a_time.count() << " секунд" << std::endl;
                    cout << "Тест #" << i / size_step << " для СЛУЧАЙНОГО массива размера " << i
                        << ": " << "УСПЕШНО"
                        << " - Среднее время: " << a_time.count() << " секунд" << std::endl;
                }

                ofs1 << i << " " << a_time.count() << endl;

                delete[] average_time;
            }
            ofs << endl;
            ofs1 << endl;
            cout << endl;
        }
        if (!check_up) break;
        if (num_of_sort == 1 && check_gap < 3) {
            num_of_sort--;
            check_gap++;
        }
        else {
            check_gap = 0;
        }
        num_of_sort++;
    }
    std::cout << "Конец тестов для лабы.\n";
}

int main() {
	setlocale(LC_ALL, "Ru");
    srand(time(0));
	
    ofstream ofs("result.txt");
    ofstream ofs1("graph.txt");

    test_for_lab(ofs, ofs1, 1);

	return 0;
}
