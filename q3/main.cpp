#include <iostream>
#include <complex>
#include "mandelbrot.hpp"

using namespace std;
int main() {


    double real, imag;
     int N = 1000;
	cout << "Enter values for <real> <image>: " << endl;
    while(scanf("%lf %lf" , &real ,&imag) == 2)
    {
        if(real == 0.0 && imag == 0.0){
        	cout << "program finish" << endl;
            exit(0);
        }

        complex<double> c(real, imag);

        if(is_in_mandelbrot(c, N)){
             cout << real << " + " << imag << "i : is in the Mandelbrot set.\n";
        } else {
            cout << real << " + " << imag << "i : is not in the Mandelbrot set.\n";
        }
	
	cout << "\nEnter another complex number (re im), or 0 0 to quit:\n" ;
    }

    return 0;
}