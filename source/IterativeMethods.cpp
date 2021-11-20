#include "IterativeMethods.h"

double* IterativeMethods::zeidelMethod(double** slae, double epsilon, int n, int& count)
{
    double* previousVariableValues = new double[n];

    for (int i = 0; i < n; i++) {
        previousVariableValues[i] = 1;
    }

    count = 0;

    // Будем выполнять итерационный процесс до тех пор, 
    // пока не будет достигнута необходимая точность    
    while (true)
    {
        // Введем вектор значений неизвестных на текущем шаге       
        double* currentVariableValues = new double[n];

        // Посчитаем значения неизвестных на текущей итерации
        // в соответствии с теоретическими формулами
        for (int i = 0; i < n; i++)
        {
            // Инициализируем i-ую неизвестную значением 
            // свободного члена i-ой строки матрицы
            currentVariableValues[i] = slae[i][n];

            // Вычитаем сумму по всем отличным от i-ой неизвестным
            for (int j = 0; j < n; j++)
            {
                // При j < i можем использовать уже посчитанные
                // на этой итерации значения неизвестных
                if (j < i)
                {
                    currentVariableValues[i] -= slae[i][j] * currentVariableValues[j];
                }

                // При j > i используем значения с прошлой итерации
                if (j > i)
                {
                    currentVariableValues[i] -= slae[i][j] * previousVariableValues[j];
                }
            }

            // Делим на коэффициент при i-ой неизвестной
            currentVariableValues[i] /= slae[i][i];

        }

        // Посчитаем текущую погрешность относительно предыдущей итерации
        long double error = 0.0;

        for (int i = 0; i < n; i++)
        {
            error += abs(currentVariableValues[i] - previousVariableValues[i]);
        }

        // Если необходимая точность достигнута, то завершаем процесс
        if (error < epsilon)
        {
            break;
        }

        // Переходим к следующей итерации, так 
        // что текущие значения неизвестных 
        // становятся значениями на предыдущей итерации
        previousVariableValues = currentVariableValues;

        count++;

    }

    return previousVariableValues;

}

double* IterativeMethods::yakobiMethod(double** slae, double epsilon, int n, int& count)
{

    double* previousVariableValues = new double[n];
    for (int i = 0; i < n; i++)
        previousVariableValues[i] = 1.0;

    double norm, * currentVariableValues = new double[n], start, end;
    for (int k = 0; k < n; k++)
        currentVariableValues[k] = previousVariableValues[k];

    count = 0;

    do {

        for (int i = 0; i < n; i++)
        {
            currentVariableValues[i] = slae[i][n];

            for (int g = 0; g < n; g++)
                if (i != g)
                    currentVariableValues[i] -= slae[i][g] * previousVariableValues[g];

            currentVariableValues[i] /= slae[i][i];
        }

        //Текущая погрешность
        norm = abs(previousVariableValues[0] - currentVariableValues[0]);

        // Переходим к следующей итерации, так 
        // что текущие значения неизвестных 
        // становятся значениями на предыдущей итерации
        for (int h = 0; h < n; h++)
        {

            if (abs(previousVariableValues[h] - currentVariableValues[h]) > norm)
                norm = abs(previousVariableValues[h] - currentVariableValues[h]);
            previousVariableValues[h] = currentVariableValues[h];

        }

        count++;

        // Если необходимая точность достигнута, то завершаем процесс
    } while (norm > epsilon);

    delete[] currentVariableValues;

    return previousVariableValues;

}

std::map<double, int> IterativeMethods::dependenceZeidel(double** slae, int n)
{ 
    
    std::map<double, int> table;

    for (double i = 0.1; i > 0.00000000000001; i /= 10.0) {

        double** temp = Util::matrixClone(slae, n);
        int count = 0;

        double* result = IterativeMethods::zeidelMethod(slae, i, n, count);

        table.insert(std::pair<double, int>(i, count));

        for (int j = 0; j < n; j++) {
            delete[] temp[j];
        }
        delete[] temp;
        delete[] result;

    }

    return table;

}

std::map<double, int> IterativeMethods::dependeceYakobi(double** slae,  int n)
{

    std::map<double, int> table;

    for (double i = 0.1; i > 0.00000000000001; i /= 10.0) {

        double** temp = Util::matrixClone(slae, n);
        int count = 0;

        double* result = IterativeMethods::yakobiMethod(slae, i, n, count);

        table.insert(std::pair<double, int>(i, count));

        for (int j = 0; j < n; j++) {
            delete[] temp[j];
        }
        delete[] temp;
        delete[] result;

    }

    return table;

}
