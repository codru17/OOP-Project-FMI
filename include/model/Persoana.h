#include <string>
#include "model/Exceptii.h"

class Persoana {
    private:
        std::string nume;
        std::string prenume;
        std::string cnp;
        int id;
        std::string telefon;
    public:
        Persoana() : nume(""), prenume(""), cnp("") {}
        Persoana(const std::string &nume, const std::string &prenume, const std::string &cnp) : nume(nume), prenume(prenume), cnp(cnp) {
            if (cnp.length() != 13) {
                throw DateInvalide("CNP invalid: " + cnp);
            }
            if (id <= 0) {
                throw DateInvalide("ID invalid: " + std::to_string(id));
            }
        }
        std::string getNume() const { return nume; }
        std::string getPrenume() const { return prenume; }
        std::string getCNP() const { return cnp; }
};