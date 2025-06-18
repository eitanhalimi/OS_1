#include <iostream>
#include <string>
#include <complex>
#include "mandelbrot.hpp"
using namespace std;

bool is_in_mandelbrot(complex <double> c, int N){
    complex<double> z = 0;
    for (int i = 0; i < N; i++) { 
        z = pow(z, 2) + c;
        if (abs(z) > 2) {
            return false; // Diverges: c is not in the Mandelbrot set
        }
    }
    return true; // Remains bounded: c is probably in the Mandelbrot set
}

