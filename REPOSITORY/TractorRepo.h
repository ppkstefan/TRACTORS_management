//
// Created by PPK on 6/24/2026.
//

#ifndef TRACTOARE_TRACTORREPO_H
#define TRACTOARE_TRACTORREPO_H
#pragma once
#include "../DOMAIN/Tractor.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

class TractorRepo {
private:
    vector<Tractor> tractoare;
    string fName;

    void loadFromFile();
    void saveToFile();
    public:
    TractorRepo(string fName);

    // Adaugă un tractor nou și salvează în fișier
    // Aruncă excepție dacă ID-ul există deja
    void store(const Tractor& tractor);

    // Scade numărul de roți cu 2 pentru tractorul cu id-ul dat și actualizează fișierul
    void decreaseRoti(int id);

    //get all
    const vector<Tractor>& getAll() const noexcept;

};


#endif //TRACTOARE_TRACTORREPO_H