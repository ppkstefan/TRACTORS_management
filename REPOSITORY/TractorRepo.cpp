//
// Created by PPK on 6/24/2026.
//

#include "../REPOSITORY/TractorRepo.h"
#include <fstream>
#include <stdexcept>

using std::string;
using std::vector;

TractorRepo::TractorRepo(string fileName): fName{ fileName } {
    loadFromFile();//incarcam datele imediat ce repo ul e creat
}

void TractorRepo::loadFromFile() {
    std::ifstream in(fName);
    if (!in.is_open()) {
        return;
    }

    int id, nrRoti;
    string denumire, tip;

    while (in >> denumire >> tip >> nrRoti) {
        tractoare.push_back(Tractor(id, denumire, tip, nrRoti));
    }
    in.close();
}

void TractorRepo::saveToFile() {
    std::ofstream out(fName);
    for (const auto& tractor : tractoare) {
        out<<tractor.getId()<<" "<<tractor.getDenumire()<<" "
        <<tractor.getTip()<<" "<<tractor.getNumarRoti()<<std::endl;
    }
    out.close();
}

void TractorRepo::store(const Tractor& t) {
    //verificam sa nu bagam un tractor cu acelasi id ca altul
    for (const auto& tractor : tractoare) {
        if (t.getId() == tractor.getId()) {
            throw std::invalid_argument("Tractor ID does not match Tractor ID");
        }
    }
    tractoare.push_back(t);
    saveToFile();
}

void TractorRepo::decreaseRoti(int id) {
    for (auto& tractor : tractoare) {
        if (tractor.getId() == id) {
            int rotiNoi = tractor.getNumarRoti() - 2;
            if (rotiNoi < 0) {
                rotiNoi = 0; // Prevenim un număr negativ de roți, de siguranță
            }
            tractor.setNumarRoti(rotiNoi);
            saveToFile();
            break;
        }
    }
}

const vector<Tractor>& TractorRepo::getAll() const noexcept {
    return tractoare;
}