#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;

#define pogr 0.1

double f(const double& x) {
    return (-sqrt(x) * sin(x));
}

std::vector<std::pair<double, double>> opt_passive(const double& a, const double& b) {
    std::vector<std::pair<double, double>> values;
    size_t N = 1;
    double delta = (b - a) / (N + 1);
    double x_min_y;
    while (delta > pogr / 2) {
        std::vector<double> vec_y;
        delta = (b - a) / (N + 1);
        for (size_t k = 1; k <= N; ++k) {
            vec_y.push_back(f((b - a) / (N + 1) * k + a));
        }
        size_t y_min_k = std::min_element(vec_y.begin(), vec_y.end()) - vec_y.begin() + 1;
        x_min_y = (b - a) / (N + 1) * y_min_k + a;
        values.push_back({ x_min_y, delta });
        N++;
    }
    return values;
}

unsigned int Fib(const size_t& n) {
    if (n < 1)
        return 0;
    unsigned int f1 = 0, f2 = 1, fn = 0;
    for (size_t i = 1; i < n; ++i) {
        fn = f1 + f2;
        f1 = f2;
        f2 = fn;
    }
    return fn;
}


std::vector<double> fib(size_t N, double& a, double& b) {
    std::vector<double> values;
    double  x1 = a + (b - a) * Fib(N) / Fib(N + 2);
    double  x2 = a + b - x1;
    double  y1 = f(x1);
    double  y2 = f(x2);
    while (N--) {
        if (y1 > y2) {
            a = x1;
            x1 = x2;
            x2 = b - (x1 - a);
            y1 = y2;
            y2 = f(x2);
            values.push_back(x2);
        }
        else {
            b = x2;
            x2 = x1;
            x1 = a + (b - x2);
            y2 = y1;
            y1 = f(x1);
            values.push_back(x1);
        }
    }
    return values;
}

void PrintValues(const std::vector<double>& values) {
    cout << std::string(45, '-') << endl;
    cout << std::setw(23) << std::left << "| Количество точек (N) " << "|";
    cout << std::setw(24) << std::left << " Значение x в точке |" << endl;
    cout << std::string(45, '-') << endl;

    for (size_t i = 0; i < values.size(); i++) {
        cout << "|";
        cout << std::setw(12) << std::right << i + 1;
        cout << std::setw(11) << "|";
        cout << std::setw(17) << std::right << std::setprecision(11) << values[i];
        cout << std::setw(4) << "|" << endl;
    }
    cout << std::string(45, '-') << endl;
    cout << values[7] << endl;
}

void PrintValues(const std::vector<std::pair<double, double>>& values) {
    cout << std::string(62, '-') << endl;
    cout << std::setw(23) << std::left << "| Количество точек (N) " << "|";
    cout << std::setw(23) << std::left << " Значение x в минимуме |";
    cout << std::setw(15) << std::left << " Погрешность |" << endl;
    cout << std::string(62, '-') << endl;

    int i = 0;
    double ans1, ans2;
    for (auto const& val : values)
    {
        cout << "|";
        cout << std::setw(12) << std::right << i + 1;
        cout << std::setw(11) << "|";
        cout << std::setw(18) << std::setprecision(11) << val.first << std::setw(6) << "|";
        cout << std::setw(9) << std::setprecision(3) << val.second;
        cout << std::setw(5) << "|" << endl;
        i++;
        ans1 = val.first;
        ans2 = val.second;
    }
    cout << std::string(62, '-') << endl;
    cout << ans1 << " +- " << ans2 << endl;
}
int main() {
    setlocale(LC_ALL, "Russian");

    size_t N = 29;
    double a = 0.0, b = 3.0;

    cout << "Вариант №3:" << endl;
    cout << "Функция -sqrt(x) * sin(x) для интервала [0, 3]" << endl << endl;
    cout << "Первый метод: метод оптимального пассивного поиска" << endl;
    cout << "Для погрешности 0,1" << endl;
    PrintValues(opt_passive(a, b));
    cout << endl;
    cout << "Второй метод: метод Фибоначчи" << endl;
    cout << "N задается заранее" << endl;
    cout << "При N=29 для точности 0,1 достаточно 8 итераций" << endl;
    PrintValues(fib(N, a, b));
    return 0;
}
