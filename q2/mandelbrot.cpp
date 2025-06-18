#include <iostream>
#include <string>
#include <complex>
using namespace std;

bool checkIfMandelbrot(complex<double> c, int N) {
    complex<double> z = 0;
    for (int i = 0; i < N; i++) { 
        z = pow(z, 2) + c;
        if (abs(z) > 2) {
            return false; // Diverges: c is not in the Mandelbrot set
        }
    }
    return true; // Remains bounded: c is probably in the Mandelbrot set
}

int main (int argc ,char* argv[]){

    if(argc<3 ||argc>4){
        cerr << "Usage: " << argv[0] << " <real part> <imaginary part> [<iterations>]\n"; 
        return 1;
    }

    complex<double> c(stod(argv[1]), stod(argv[2]));
    int n = 1000; // Default number of iterations
    if (argc == 4) {
        n = stoi(argv[3]);
    }
    if (checkIfMandelbrot(c, n)) {
        cout << c.real() << " + " << c.imag() << "i : is in the Mandelbrot set.\n";
    } else {
        cout << c.real() << " + " << c.imag() << "i : is not in the Mandelbrot set.\n";
    }
}