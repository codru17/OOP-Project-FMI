#include <iostream>
#include "model/Exceptii.h"

int main() {
    try {
        throw DateInvalide("Datele introduse sunt invalide.");
    } catch (const ExceptieSpital &e) {
        std::cerr << "Eroare: " << e.what() << std::endl;
    }
}
