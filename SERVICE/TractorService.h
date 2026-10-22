//
// Created by PPK on 6/24/2026.
//

#ifndef TRACTOARE_TRACTORSERVICE_H
#define TRACTOARE_TRACTORSERVICE_H
#pragma once
#include "../REPOSITORY/TractorRepo.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class TractorService {
private:
    TractorRepo &repo;
public:
    explicit TractorService(TractorRepo &r);

    void addTractor(int id, const string &denumire, const string &tip, int nrRoti);
    void decreaseRoti(int id);

    vector<Tractor> getAllSorted() const;

    // Returnează numărul de tractoare care au un anumit tip
    int countByType(const string &tip) const;

    // Returnează o listă cu toate tipurile distincte (pentru popularea QComboBox-ului)
    std::vector<std::string> getDistinctTypes() const;
};


#endif //TRACTOARE_TRACTORSERVICE_H