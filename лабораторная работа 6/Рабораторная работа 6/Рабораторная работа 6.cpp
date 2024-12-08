﻿#include <iostream>
#include <iomanip> // Для std::setprecision
#include <vector>
#include <fstream> // Для работы с файлами

using namespace std;

const int mf = 500;

int main() {
    int i, j, N;
    vector<double> T(mf), alfa(mf), beta(mf);
    double ai, bi, ci, fi;
    double lamda, ro, c, h, tau;
    double Tl, T0, Tr, L, t_end, time;

    // Очистка экрана (необязательно, в C++ это не требуется)
    // system("cls"); // Для Windows
    // или
    // system("clear"); // Для Linux/Unix

    // Ввод всех необходимых входных параметров
    cout << "Введите количество пространственных узлов, N: ";
    cin >> N;
    cout << "Введите окончание по времени, t_end: ";
    cin >> t_end;
    cout << "Введите толщину пластины, L: ";
    cin >> L;
    cout << "Введите коэффициент теплопроводности материала пластины, lamda: ";
    cin >> lamda;
    cout << "Введите плотность материала пластины, ro: ";
    cin >> ro;
    cout << "Введите теплоемкость материала пластины, c: ";
    cin >> c;
    cout << "Введите начальную температуру, T0: ";
    cin >> T0;
    cout << "Введите температуру на границе x=0, Tl: ";
    cin >> Tl;
    cout << "Введите температуру на границе x=L, Tr: ";
    cin >> Tr;

    // Определяем расчетный шаг сетки по пространственной координате
    h = L / (N - 1);
    // Определяем расчетный шаг сетки по времени
    tau = t_end / 100.0;

    // Определяем поле температуры в начальный момент времени
    for (i = 1; i <= N; i++) {
        T[i - 1] = T0; // Массив в C++ начинается с индекса 0
    }

    // Проводим интегрирование нестационарного уравнения теплопроводности
    time = 0;
    while (time < t_end) { // Используем цикл с предусловием
        time += tau;

        // Определяем начальные прогоночные коэффициенты на основе левого граничного условия
        alfa[0] = 0.0; // Индексация начинается с 0
        beta[0] = Tl;

        // Цикл с параметром для определения прогоночных коэффициентов
        for (i = 1; i < N - 1; i++) {
            ai = lamda / (h * h);
            bi = 2.0 * lamda / (h * h) + ro * c / tau;
            ci = lamda / (h * h);
            fi = -ro * c * T[i] / tau;

            // alfa[i] и beta[i] – прогоночные коэффициенты
            alfa[i] = ai / (bi - ci * alfa[i - 1]);
            beta[i] = (ci * beta[i - 1] - fi) / (bi - ci * alfa[i - 1]);
        }

        // Определяем значение температуры на правой границе
        T[N - 1] = Tr;

        // Используя соотношение, определяем неизвестное поле температуры
        for (i = N - 2; i >= 0; i--) {
            T[i] = alfa[i] * T[i + 1] + beta[i];
        }
    } // Цикл с предусловием окончен

    // Вывод результатов в файл
    ofstream f("res.txt");
    f << fixed << setprecision(4);
    f << "Толщина пластины L = " << L << endl;
    f << "Число узлов по координате N = " << N << endl;
    f << "Коэффициент теплопроводности материала пластины lamda = " << lamda << endl;
    f << "Плотность материала пластины ro = " << ro << endl;
    f << "Теплоемкость материала пластины c = " << c << endl;
    f << "Начальная температура T0 = " << T0 << endl;
    f << "Температура на границе x = 0, Tl = " << Tl << endl;
    f << "Температура на границе x = L, Tr = " << Tr << endl;
    f << "Результат получен с шагом по координате h = " << h << endl;
    f << "Результат получен с шагом по времени tau = " << tau << endl;
    f << "Температурное поле в момент времени t = " << t_end << endl;
    f.close();

    // Вывод температурного поля в другой файл
    ofstream g("tempr.txt");
    g << fixed << setprecision(3);
    for (i = 0; i < N; i++) {
        g << " " << h * i << " " << setprecision(5) << T[i] << endl;
    }
    g.close();

    return 0;
}
