//
// Created by PPK on 6/24/2026.
//

#ifndef TRACTOARE_TRACTOR_H
#define TRACTOARE_TRACTOR_H
#pragma once
#include <string>
using std::string;

class Tractor {
private:
        int id;
        string denumire;
        string tip;
        int numarRoti;
public:
        //constructor
        Tractor(int id, string denumire, string tip, int numarRoti);

        //metode de access
        int getId() const noexcept;
        string getDenumire() const;
        string getTip() const;
        int getNumarRoti() const noexcept;

        void setId(int id) noexcept;
        void setTip(string newTip) ;
        void setDenumire(string denumire);
        void setNumarRoti(int numarRoti) noexcept;
};


#endif //TRACTOARE_TRACTOR_H