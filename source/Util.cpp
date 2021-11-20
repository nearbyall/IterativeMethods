#include "Util.h"

double** Util::slaeFromFile(std::string slaepath)
{

	//Считаем СЛАУ из файла в двумерный динамический массив
	std::ifstream file;
	file.open(slaepath);
	if (file.is_open())
	{
		//Если открытие файла прошло успешно

		//Подсчитаем кол-во чисел в файле
		int count = 0;
		int temp;

		while (!file.eof())
		{
			file >> temp;
			count++;
		}

		//Вначале переведем каретку в потоке в начало файла
		file.seekg(0, std::ios::beg);
		file.clear();

		//Подсчитаем кол-во отступов в строке
		int count_space = 0;
		char symbol;

		while (!file.eof())
		{
			file.get(symbol);
			if (symbol == '\t') count_space++;
			if (symbol == '\n') break;
		}

		//Опять переходим в потоке в начало файл
		file.seekg(0, std::ios::beg);
		file.clear();

		//Теперь мы знаем сколько чисел в файле и сколько пробелов в первой строке.
		//Теперь можем считать матрицу.
		int n = count / (count_space + 1);
		int m = count_space + 1;
		double** slae = new double* [n];
		for (int i = 0; i < n; i++) slae[i] = new double[m];

		//Считаем матрицу из файла
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				file >> slae[i][j];

		return slae;

		file.close();
	}
	else
	{
		//Если открытие файла прошло не успешно
		std::cout << "Файл не найден.";
		return nullptr;
	}

}

double** Util::aFromSlae(double** slae, int n)
{
	double** A = new double* [n];
	for (int i = 0; i < n; i++) A[i] = new double[n];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			A[i][j] = slae[i][j];
	}
	return A;
}

double** Util::randMatrixA(int n)
{
	double** a = new double* [n];
	for (int i = 0; i < n; i++)
		a[i] = new double[n];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			a[i][j] = (rand() % 100) + 1;

	return a;
}

double** Util::matrixClone(double** matrix, int n)
{
	double** newMatrix = new double* [n];
	for (int i = 0; i < n; i++) newMatrix[i] = new double[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			newMatrix[i][j] = matrix[i][j];
	return newMatrix;
}

double* Util::bFromSlae(double** slae, int n)
{
	double* B = new double[n];
	for (int i = 0; i < n; i++) {
		B[i] = slae[i][n];
	}
	return B;
}

double* Util::randMatrixB(int n)
{
	double* b = new double[n];
	for (int i = 0; i < n; i++)
		b[i] = (rand() % 100) + 1;
	return b;
}

double* Util::arrayClone(double* array, int n)
{
	double* newArray = new double[n];
	for (int i = 0; i < n; i++) newArray[i] = array[i];
	return newArray;
}

int Util::dimensionOfMatrixFromFile(std::string slaepath)
{

	std::ifstream file;
	file.open(slaepath);
	if (file.is_open())
	{
		//Если открытие файла прошло успешно

		//Подсчитаем кол-во чисел в файле
		int count = 0;
		int temp;

		while (!file.eof())
		{
			file >> temp;
			count++;
		}

		//Вначале переведем каретку в потоке в начало файла
		file.seekg(0, std::ios::beg);
		file.clear();

		//Подсчитаем кол-во отступов в строке
		int count_space = 0;
		char symbol;

		while (!file.eof())
		{
			file.get(symbol);
			if (symbol == '\t') count_space++;
			if (symbol == '\n') break;
		}

		//Теперь мы знаем сколько чисел в файле и сколько пробелов в первой строке.
		int n = count / (count_space + 1);
		return n;
		file.close();
	}
	else
	{
		//Если открытие файла прошло не успешно
		std::cout << "Файл не найден.";
		return 0;
	}

}