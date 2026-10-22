//
// Created by PPK on 6/24/2026.
//

#include "TractorService.h"
#include <algorithm>
#include <stdexcept>

TractorService::TractorService(TractorRepo &r): repo{ r } {}

void TractorService::addTractor(int id, const string& denumire, const string& tip, int nrRoti) {
    string errors="";
    if (denumire.empty()) {
        errors += "Denumirea nu poate fi vida!\n";
    }
    if (tip.empty()) {
        errors += "Tipul nu poate fi vid!\n";
    }
    if (nrRoti < 2 || nrRoti > 16 || nrRoti % 2 != 0) {
        errors += "Numarul de roti trebuie sa fie par, cuprins intre 2 si 16!\n";
    }

    if (!errors.empty()) {
        throw std::runtime_error(errors);
    }

    Tractor t(id,denumire,tip,nrRoti);
    repo.store(t);
}

void TractorService::decreaseRoti(int id) {
    repo.decreaseRoti(id);
}

vector<Tractor> TractorService::getAllSorted() const {
    vector<Tractor> t= repo.getAll();

    std::sort(t.begin(), t.end(), [](const Tractor &a, const Tractor &b) {
        return a.getDenumire() < b.getDenumire();
    });

    return t;
}

int TractorService::countByType(const string &tip) const {
    int cnt=0;
    for (const auto &t : repo.getAll()) {
        if (t.getTip()==tip) {
            cnt++;
        }
    }
    return cnt;
}

std::vector<std::string> TractorService::getDistinctTypes() const {
    vector<string> tipuri;
    for (const auto &t : repo.getAll()) {
        // Varianta corectă:
        if (std::find(tipuri.begin(), tipuri.end(), t.getTip()) == tipuri.end()) {
            tipuri.push_back(t.getTip());
        }
    }
    return tipuri;
}