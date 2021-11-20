#include <iostream>
#include <iomanip>

#include "IterativeMethods.h"
#include "Util.h"

int main() {
	
	setlocale(LC_ALL, "Russian");

	//Считаем СЛАУ из файла
	double** slae = Util::slaeFromFile("zeidel_41.lb2");
	int n = Util::dimensionOfMatrixFromFile("zeidel_41.lb2");
	int count;

	//Найдем решения СЛАУ обоими методами
	double* result;
	result = IterativeMethods::zeidelMethod(slae, 0.00000001, n, count);
	for (int i = 0; i < n; i++) {
		std::cout << "X" << i + 1 << "= " << std::setw(10) << result[i] << "\n";
	}
	std::cout << count << std::endl;
	result = IterativeMethods::yakobiMethod(slae, 0.00000001, n, count);
	for (int i = 0; i < n; i++) {
		std::cout << "X" << i + 1 << "= " << std::setw(10) << result[i] << "\n";
	}
	std::cout << count << std::endl;

	//Найдем и выведем зависимость кол-ва итераций от точности для метода Зейделя
	std::map<double, int> table = IterativeMethods::dependenceZeidel(slae, n);

	for (const auto& kv : table) {
		std::cout << kv.first << "              " << kv.second << std::endl;
	}

	//Найдем и выведем зависимость кол-ва итераций от точности для метода Якоби
	table = IterativeMethods::dependeceYakobi(slae, n);

	for (const auto& kv : table) {
		std::cout << kv.first << "              " << kv.second << std::endl;
	}

	//Притворимся GarbageCollector'ом
	for (int i = 0; i < n; i++) {
		delete[] slae[i];
	}
	delete[] slae;
	delete[] result;

	return 1;
}