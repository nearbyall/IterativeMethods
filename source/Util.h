#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <map>

class Util
{

private:

	Util() {}

public:

	//Считывание матрицы произвольного размера из файла
	static double** slaeFromFile(std::string slaepath);

	//Считывание из слау матрицы коэффицентов
	static double** aFromSlae(double** slae, int n);

	//Генерация матрицы коэффицентов размерности n
	static double** randMatrixA(int n);

	//Клонирование матрицы
	static double** matrixClone(double** matrix, int n);

	//Считывание из слау свободных членов
	static double* bFromSlae(double** slae, int n);

	//Генерация свободных членов размерности n
	static double* randMatrixB(int n);

	//Клонирование массива
	static double* arrayClone(double* array, int n);

	//Считывание размерности матрицы из файла
	static int dimensionOfMatrixFromFile(std::string slaepath);

};

