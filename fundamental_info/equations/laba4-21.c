/*
Лабораторная №4. Уравнение №21

Найди x, при котором F(x) = 0, с точностью ε = 10⁻⁸.

t = tan(x), угол x в радианах.
F(x) = t − t³/3 + t⁵/5 − 1/3
F′(x) = 1 + t⁶
φ(x) = x − F(x)/3

Отрезок поиска [0; 0,8]. Тас x = 0,4 — середины отрезка.
Для Ньютона начни с x = 0,375 — середины [0,25; 0,5].
m = 1, нижняя граница для |F′(x)|.

В начале программы выведи табличный корень и точность.
Запусти три процедуры. В каждую передай F, а для итераций передай
также φ, для Ньютона — F′. Счётчик шагов в каждой процедуре свой.


Дихотомия
    Возьми исходные границы a и b. Положи число шагов равным нулю.
    Пока b − a ≥ ε:бличный корень 0,3333.
Для простых итераций начни 
        Найди середину c = (a + b) / 2. Прибавь один шаг.
        Если F(c) = 0, выведи c с нулевой погрешностью и закончи метод.
        Если F(a) и F(c) разных знаков, замени b на c.
        Иначе замени a на c.
    Выведи корень (a + b) / 2, оценку (b − a) / 2 и число шагов.

Простые итерации
    Возьми начальное x из данных выше. Начни считать шаги с нуля.
    Повторяй:
        Сохрани текущее x как старое.
        Вычисли новое x = φ(старое x).
        Оцени погрешность как |F(x)| / m. Прибавь один шаг.
    Остановись, когда и |новое x − старое x|, и оценка меньше ε.
    Выведи последнее x, оценку погрешности и число шагов.

Метод Ньютона
    Возьми начальное x для Ньютона из данных выше.
    Действуй как в простых итерациях, но вычисляй новое приближение
    по формуле x = старое x − F(старое x) / F′(старое x).
    Условие остановки и вывод такие же.
*/

#include <stdio.h>
#include <math.h>

static const double ε = 1e-8;

double f(double x) {
    double tg = tan(x);
    return tg - pow(tg, 3)/3 + pow(tg, 5)/5 - (1.0/3.0);
}

double df(double x) {
    double tg = tan(x);
    return 1 + pow(tg, 6);
}

double phi(double x) {
    return x - f(x)/3;
}

void bisection(double (*F)(double), double a, double b) {
    int steps = 0;
    double c;
    double interval;
    double root;
    while (b - a >= ε) {
        c = (b + a)/2.0;
        if (F(c) == 0) {break;}
        if (F(c) * F(a) < 0.0) {
            b = c;
        } else {
            a = c;
        }
        steps++;
    }
    root = (a + b)/2;
    interval = (b - a)/2;
    printf("Root: %.12f, Error: %.2e, Steps: %d\n", root, interval, steps);
}

void iteration(double (*F)(double), double x) {
    int steps = 0;
    double change;
    double error;
    double old_x;
    do {
        old_x = x;
        x = phi(old_x);
        steps++;
        change = fabs(x - old_x);
        error = fabs(F(x));
    } while ((change >= ε) || (error >= ε));
    printf("X: %.12f, Error: %.2e, Steps: %d\n", x, error, steps);
}

void newton(double (*F)(double), double (*dF)(double), double x) {
    int steps = 0;
    double change;
    double error;
    double old_x;
    do {
        old_x = x;
        x = old_x - (F(x)/dF(x));
        steps++;
        change = fabs(x - old_x);
        error = fabs(F(x));
    } while ((change >= ε) || (error >= ε));
    printf("X: %.12f, Error: %.2e, Steps: %d\n", x, error, steps);
}

int main(void) {
    bisection(f, 0.0, 0.8);
    iteration(f, 0.4);
    newton(f, df, 0.375);
}