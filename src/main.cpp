#include <iostream>
#include "model/DataOra.h"
#include "model/Exceptii.h"

void test(int zi, int luna, int an, int ora, int minut) {
    try {
        
    } catch (const DateInvalide &e) {
    }

}

int main() {
    try {
        DataOra data(17, 2, 2024, 10, 30); // Aceasta va arunca o exceptie DateInvalide
        std::cout << "Data creata: " << data.toString() << std::endl;
    } catch (const DateInvalide &e) {
        std::cerr << "Eroare: " << e.what() << std::endl;
    }
}
