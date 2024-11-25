import numpy as np
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt
import os

algorithms = [
    "Shell Sort (Shell gaps)",
    "Shell Sort (Pratt gaps)",
    "Shell Sort (Hibbard gaps)",
    "Insertion Sort",
    "Selection Sort",
    "Bubble Sort",
    "Heap Sort",
    "Merge Sort",
    "Quick Sort"
]

colors = ['blue',
          'green',
          'red',
          'purple',
          'pink',
          'brown',
          'aqua',
          'cyan',
          'yellow']

class Models:
    @staticmethod
    def n_log_n(x, a):
        return a * x * np.log2(x)

    @staticmethod
    def n_square(x, a):
        return a * x * x

    @staticmethod
    def n_3_2(x, a):
        return a * x ** (3 / 2)

    @staticmethod
    def n(x, a):
        return a * x

    @staticmethod
    def n_log_2_n(x, a):
        return a * x * np.log2(x) * np.log2(x)


# Модели для регрессии по каждому отрезку
regression_models = [
    Models.n_log_n, Models.n_square, Models.n_log_n, Models.n_3_2,  # Shell Sort (Shell gaps)
    Models.n_log_n, Models.n_square, Models.n_log_n, Models.n_square,  # Shell Sort (Pratt gaps)
    Models.n_log_n, Models.n_3_2, Models.n_log_n, Models.n_3_2,  # Shell Sort (Hibbard gaps)
    Models.n, Models.n_square, Models.n, Models.n_square,  # Insertion Sort
    Models.n_square, Models.n_square, Models.n_square, Models.n_square,  # Selection Sort
    Models.n, Models.n_square, Models.n, Models.n_square,  # Bubble Sort
    Models.n_log_n, Models.n_log_n, Models.n_log_n, Models.n_log_n,  # Heap Sort
    Models.n_log_n, Models.n_log_n, Models.n_log_n, Models.n_log_n,  # Merge Sort
    Models.n_log_n, Models.n_log_n, Models.n_log_n, Models.n_log_n  # Quick Sort
]


# Считывание данных с файла
def load_data_from_file(file_path):
    with open(file_path, 'r') as file:
        data = file.readlines()

    graphs = []
    current_graph = []

    for line in data:
        line = line.strip()
        if line == "":
            if current_graph:
                graphs.append(current_graph)
                current_graph = []
        elif line:
            elements = line.split()
            current_graph.append((int(elements[0]), float(elements[1])))

    if current_graph:
        graphs.append(current_graph)

    return graphs


# Функция для построения графиков с регрессией и без
def plot_graph_with_and_without_regression(graphs, save_folder, title, reg_mod, reg_label):
    names = ['Sorted', 'Reversed', '90% Sorted', 'Random']

    # График без регрессии
    plt.figure(figsize=(10, 6))
    for i, graph in enumerate(graphs):
        x, y = zip(*graph)
        plt.scatter(x, y, s=20, marker='o', color=colors[i % len(colors)])
        plt.plot(x, y, linestyle='-', color=colors[i % len(colors)], label=f"{names[i]}")
    plt.xlabel("Количество элементов")
    plt.ylabel("Время выполнения")
    plt.title(f"{title} (без регрессии)")
    plt.legend()
    plt.grid(True)
    plt.savefig(os.path.join(save_folder, f"{title}_без_регрессии.png"))
    plt.close()

    # График с регрессией
    plt.figure(figsize=(10, 6))
    for i, graph in enumerate(graphs):
        x, y = zip(*graph)
        x = np.array(x)
        y = np.array(y)
        s = np.array(10) * 100
        plt.scatter(x, y, s=20, marker='o', color=colors[i % len(colors)])
        # Вывод начальных точек
        # plt.plot(x, y, marker='o', linestyle='none', color=colors[i % len(colors)])

        # Применяем регрессию для текущих данных
        popt, _ = curve_fit(reg_mod[i], x, y)

        # Строим гладкую линию регрессии с большим количеством точек
        x_fit = np.linspace(min(x), max(x), 500)  # увеличиваем количество точек для плавной кривой
        y_fit = reg_mod[i](x_fit, *popt)

        # Строим только кривую регрессии
        plt.plot(x_fit, y_fit, linestyle='-', color=colors[i % len(colors)], label=f"{names[i]} ({reg_label})")

    plt.xlabel("Количество элементов")
    plt.ylabel("Время выполнения")
    plt.title(f"{title} (с регрессией)")
    plt.legend()
    plt.grid(True)
    plt.savefig(os.path.join(save_folder, f"{title}_с_регрессией.png"))
    plt.close()


# Главная функция для построения всех графиков
def build_all_graphs(file_path, save_folder):
    if not os.path.exists(save_folder):
        os.makedirs(save_folder)

    graphs = load_data_from_file(file_path)

    graph_count = len(graphs) // 4  # Всего будет 9 групп по 4 графика

    a = 0

    for i in range(graph_count):
        reg_mod = [regression_models[4 * a],
                   regression_models[4 * a + 1],
                   regression_models[4 * a + 2],
                   regression_models[4 * a + 3]]
        a += 1
        current_graphs = graphs[i * 4:(i + 1) * 4]
        algorithm_title = algorithms[i]
        plot_graph_with_and_without_regression(
            current_graphs, save_folder, algorithm_title, reg_mod,
            reg_label=f'Регрессия'
        )


def plot_all_average():
    for i in range(2):
        n = np.linspace(1, 100, 500)

        functions_q = {
            'Shell(Shell)/Shell(Hibbard) Sort': n ** (3 / 2),
            'Bubble/Selection/Insertion/Shell(Pratt) Sort': n ** 2,
        }
        functions_s = {
            'Heap/Merge/Quick sort': n * np.log(n)
        }
        plt.figure(figsize=(10, 6))

        if i - 1:
            for label, func in functions_s.items():
                plt.plot(n, func, label=label)
        else:
            for label, func in functions_q.items():
                plt.plot(n, func, label=label)

        plt.xlabel('n')
        plt.ylabel('Value')
        plt.title('Comparison of Functions')
        plt.legend()
        plt.grid(True)
        plt.savefig(f"allsort_{i + 1}.png")
        plt.show()

# Вызов основной функции
file_path = r"Z:\programming\cpp proj\AiSD\graph.txt"
save_folder = r"Z:\programming\pythonproj\AISDDO\graphs_pract"
plot_all_average()
# build_all_graphs(file_path, save_folder)