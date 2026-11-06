#include <string>
#include "model/DataOra.h"
#include "model/Exceptii.h"

DataOra::DataOra() : zi(1), luna(1), an(2000), ora(0), minut(0) {}
DataOra::DataOra(int zi, int luna, int an, int ora, int minut) : zi(zi), luna(luna), an(an), ora(ora), minut(minut) {
    if(an < 0 || an > 9999) {
        throw DateInvalide("An invalid: " + std::to_string(an));
    }
    if (luna < 1 || luna > 12) {
        throw DateInvalide("Luna invalida: " + std::to_string(luna));
    }
    int zileMax = zileInLuna(luna, an);
    if (zi < 1 || zi > zileMax) {
        throw DateInvalide("Zi invalida: " + std::to_string(zi) + " pentru luna: " + std::to_string(luna) + " si anul: " + std::to_string(an));
    }
    if (ora < 0 || ora > 23) {
        throw DateInvalide("Ora invalida: " + std::to_string(ora));
    }
    if (minut < 0 || minut > 59) {
        throw DateInvalide("Minut invalid: " + std::to_string(minut));
    }
}

bool DataOra::anBisect(int an) {
    return (an % 4 == 0 && an % 100 != 0) || (an % 400 == 0);
}

int DataOra::zileInLuna(int luna, int an) {
    switch (luna) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return anBisect(an) ? 29 : 28;
        default:
            return -1; // Luna invalida
    }
}

bool DataOra::operator==(const DataOra &other) const {
    return zi == other.zi && luna == other.luna && an == other.an && ora == other.ora && minut == other.minut;
}

bool DataOra::operator<(const DataOra &other) const {
    if (an != other.an) return an < other.an;
    if (luna != other.luna) return luna < other.luna;
    if (zi != other.zi) return zi < other.zi;
    if (ora != other.ora) return ora < other.ora;
    return minut < other.minut;
}

std::string DataOra::toString() const {
    return douaCifre(zi) + "/" + douaCifre(luna) + "/" + std::to_string(an) + " " +
           douaCifre(ora) + ":" + douaCifre(minut);
}

std::string DataOra::douaCifre(int numar)  {
    return (numar < 10 ? "0" : "") + std::to_string(numar);
}

DataOra DataOra::adaugaMinute(int minuteAdaugate) const {
    int totalMinute = minut + minuteAdaugate;
    int newMinut = totalMinute % 60;
    int totalOre = (totalMinute / 60) + ora;
    int newOra = totalOre % 24;
    int zileAdaugate = totalOre / 24;
    int newZi = zi + zileAdaugate;
    int newLuna = luna;
    int newAn = an;
    while(newZi > zileInLuna(newLuna, newAn)) {
        newZi -= zileInLuna(newLuna, newAn);
        newLuna++;
        if (newLuna > 12) {
            newLuna = 1;
            newAn++;
        }
    }

    return DataOra(newZi, newLuna, newAn, newOra, newMinut);
}