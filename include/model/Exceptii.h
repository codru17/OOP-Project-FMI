#pragma once
#include <stdexcept>
#include <string>

class ExceptieSpital: public std::runtime_error {
    public:
        ExceptieSpital(const std::string &mesaj) : std::runtime_error(mesaj) {

    }
};

class DateInvalide: public ExceptieSpital {
    public:
        DateInvalide(const std::string &mesaj) : ExceptieSpital(mesaj) {

    }
};
class EntitateNegasita: public ExceptieSpital {
    public:
        EntitateNegasita(const std::string &mesaj) : ExceptieSpital(mesaj) {

    }
};
class ProgramareSuprapusa:   public ExceptieSpital {
    public:
        ProgramareSuprapusa(const std::string &mesaj) : ExceptieSpital(mesaj) {}
};
class SectiePlina: public ExceptieSpital {
    public:
        SectiePlina(const std::string &mesaj) : ExceptieSpital(mesaj) {}
};
