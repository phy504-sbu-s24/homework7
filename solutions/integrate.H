#ifndef INTEGRATE_H
#define INTEGRATE_H

#include <cmath>
#include <functional>
#include <random>

double trapezoid(const double a, const double b, const int N,
                 std::function<double(double)> f) {

    double dx = (b - a) / static_cast<double>(N);

    double I{0.0};

    for (int n = 0; n < N; ++n) {
        const double xl = a + n * dx;
        const double xr = a + (n + 1) * dx;

        I += 0.5 * dx * (f(xl) + f(xr));
    }

    return I;
}


double mc(const double a, const double b, const int N,
          std::function<double(double)> f) {

    double I{0.0};

    std::random_device rd;
    std::mt19937 generator(rd());

    std::uniform_real_distribution<double> distribution(a, b);

    for (int n = 0; n < N; ++n) {
        auto x = distribution(generator);
        I += f(x);
    }

    return I / static_cast<double>(N) * (b - a);

}
#endif
