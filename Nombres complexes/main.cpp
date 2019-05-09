#include <iostream>
#include <complex>

int main() {
    using namespace std::literals;

    std::cout << ((2.0 + 3.0i) + (4.0 + 5.0i)) << std::endl; // addition
    std::cout << ((2.0 + 3.0i) - (4.0 + 5.0i)) << std::endl; // soustraction

    std::cout << ((2.0 + 3.0i) + 4.0) << std::endl;          // addition
    std::cout << ((2.0 + 3.0i) - 4.0) << std::endl;          // soustraction
    std::cout << ((2.0 + 3.0i) * 4.0) << std::endl;          // multiplication
    std::cout << ((2.0 + 3.0i) / 4.0) << std::endl;          // division

    std::cout << real(2.0 + 3.0i) << std::endl;  // partie réelle
    std::cout << imag(2.0 + 3.0i) << std::endl;  // partie imaginaire
    std::cout << abs(2.0 + 3.0i) << std::endl;   // module (valeur absolue en anglais)
    std::cout << arg(2.0 + 3.0i) << std::endl;   // argument
    std::cout << norm(2.0 + 3.0i) << std::endl;  // norme
    std::cout << conj(2.0 + 3.0i) << std::endl;  // conjugué
    std::cout << proj(2.0 + 3.0i) << std::endl;  // projection
    std::cout << polar(2.0 + 3.0i) << std::endl; // coordonnées polaires

    return 0;
}
