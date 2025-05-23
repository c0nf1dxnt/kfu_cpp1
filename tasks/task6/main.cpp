/**
 * @file main.cpp
 * @brief задача написать программу, которая будет высчитывать значение интеграла через метод трапеций
 * Особенность этой задачи: использовать потоки(threads) для ускорения вычислений (нужно разделить задачу для вычисления части интеграла на каждый поток)
 *
 * на вход программе при запуске(это в argv[]) подается 3 числа: a, b, n, tn где [a, b] - интервал (целочисленный, неотрицательный и не больше 50 для задачи), n - количество разбиений, tn - threads number - количество потоков для подсчёта
 * примечание: n - количество разбиений в тестах будет явно нацело делиться на tn - количество потоков.
 *
 * на выход программе выведите значение интеграла через метод трапеций (вывод в стандартный поток std::cout, в конце выведите '\n'), вывод в поток с точностью до 4 знака
 * в функции trapezoidalIntegral есть переменная const std::function<double (double)> &f, при вызове подсчётов передайте ссылку на функцию из задания
 * реализовать подсчёт интеграла S(a, b) = (1+e^x)^0.5 dx
 * 
 *
 * литература:
 * https://ru.wikipedia.org/wiki/Метод_трапеций
 * https://habr.com/ru/articles/420867/
 */

#include <cmath>
#include <functional>
#include <numeric>
#include <vector>
#include <thread>
#include <iostream>
#include <iomanip>

class Integral {
private:
    int a, b, n, tn;

public:
    Integral(int& argc, char** argv) {
        if (argc != 5) {
            throw std::invalid_argument("Wrong number of arguments");
        }
        a  = std::stoi(argv[1]);
        b  = std::stoi(argv[2]);
        n  = std::stoi(argv[3]);
        tn = std::stoi(argv[4]);
    }

    static double integralFunction(double x) {
        return std::sqrt(1 + std::exp(x));
    }
    
    static double calculatePartialIntegral(double start, double end, int segments) {
        double h = (end - start) / segments;
        double sum = 0.5 * (integralFunction(start) + integralFunction(end));
        
        for (int i = 1; i < segments; i++) {
            sum += integralFunction(start + i * h);
        }
        
        return h * sum;
    }

    double calculateIntegral() {
        if (tn <= 0 || n <= 0) return 0;

        int segmentsPerThread = n / tn;
        double rangePerThread = static_cast<double>(b - a) / tn;
        
        std::vector<double> results(tn);
        std::vector<std::thread> threads;
        
        for (int i = 0; i < tn; i++) {
            double start = a + i * rangePerThread;
            double end = (i == tn - 1) ? b : start + rangePerThread;
            
            threads.emplace_back([&results, i, start, end, segmentsPerThread]() {
                results[i] = calculatePartialIntegral(start, end, segmentsPerThread);
            });
        }
        
        for (auto &thread : threads) {
            if (thread.joinable()) {
                thread.join();
            }
        }
        return std::accumulate(results.begin(), results.end(), 0.0);
    }
};


int main(int argc, char** argv) {
    auto i = Integral(argc, argv);
    std::cout << std::fixed << std::setprecision(4);
    std::cout << i.calculateIntegral() << std::endl;
    return 0;
}
