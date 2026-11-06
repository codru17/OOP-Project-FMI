#pragma once
#include <string>

class DataOra {
    private:
        int zi;
        int luna;
        int an;
        int ora;
        int minut;

        static bool anBisect(int an) ;
        static int zileInLuna(int luna, int an) ;
        static std::string douaCifre(int numar)  ;
    public:
        DataOra() ;
        DataOra(int zi, int luna, int an, int ora, int minut) ;
        int getZi() const { return zi; }
        int getLuna() const { return luna; }
        int getAn() const { return an; }
        int getOra() const { return ora; }
        int getMinut() const { return minut; }

        bool operator==(const DataOra &other) const ;
        bool operator<(const DataOra &other) const ;

        std::string toString() const ;
};