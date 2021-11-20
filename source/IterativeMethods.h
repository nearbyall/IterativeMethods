#pragma once

#include <cmath>
#include <map>

#include "Util.h"

class IterativeMethods
{

private:
	
	IterativeMethods() {}

public:

	//Метод Зейделя
	static double* zeidelMethod(double** slae, double epsilon, int n, int& count);

	//Метод Якоби
	static double* yakobiMethod(double** slae, double epsilon, int n, int& count);

	//Нахождение зависимости кол-ва итераций от точности для метода Зейделя
	static std::map<double, int> dependenceZeidel(double** slae, int n);

	//Нахождение зависимости кол-ва итераций от точности для метода Якоби
	static std::map<double, int> dependeceYakobi(double** slae, int n);

};

