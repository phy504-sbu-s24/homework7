#include <iostream>
#include <iomanip>
#include <numbers>

#include "integrate.H"

int main() {

    {
        std::cout << "integrating sin^2(x) from 0 to 2pi" << std::endl;

        auto I = trapezoid(0.0, 2.0*std::numbers::pi, 32,
                           [] (double x) {return std::pow(std::sin(x), 2.0);});

        std::cout << I << std::endl;
    }


    std::cout << "integrating exp(-x^2) from -5 to 5" << std::endl;

    for (auto N : {8, 16, 32, 64, 128, 256}) {

        auto I = trapezoid(-5.0, 5.0, N,
                           [] (double x) {return std::exp(-x*x);});

        auto I_mc = mc(-5.0, 5.0, N,
                       [] (double x) {return std::exp(-x*x);});

        std::cout << std::setw(4) << N << " "
                  << std::setprecision(12)
                  << std::setw(20) << I << " "
                  << std::setw(20) << I_mc << std::endl;

    }


    std::cout << "integrating sin^2 (1 / (x (2-x))) from 0 to 2" << std::endl;

    for (auto N : {8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4192, 8192, 16384, 32768, 65535}) {

        double eps{1.e-12};

        auto I = trapezoid(0.0, 2.0, N,
                           [=] (double x) {return std::pow(std::sin(1.0 / (x * (2-x) + eps)), 2.0);});

        auto I_mc = mc(0.0, 2.0, N,
                       [=] (double x) {return std::pow(std::sin(1.0 / (x * (2-x) + eps)), 2.0);});

        std::cout << std::setw(4) << N << " "
                  << std::setprecision(12)
                  << std::setw(20) << I << " "
                  << std::setw(20) << I_mc << std::endl;

    }

}
