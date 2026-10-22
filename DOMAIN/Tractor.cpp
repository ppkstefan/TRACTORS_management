#include "Tractor.h"
#include <string>
#include <utility>

Tractor::Tractor(int id, string denumire, string tip, int numarRoti): id{ id }, denumire{ denumire }, tip{ tip }, numarRoti{ numarRoti } {}


//gettere
int Tractor::getId() const noexcept {
    return id;
}
string Tractor::getDenumire() const  {
    return denumire;
}
string Tractor::getTip() const  {
    return tip;
}
int Tractor::getNumarRoti() const noexcept {
    return numarRoti;
}

//settere
void Tractor::setId(int id) noexcept {
    this->id = id;
}
void Tractor::setDenumire(string denumire)  {
    this->denumire = denumire;
}
void Tractor::setTip(string tip)  {
    this->tip = tip;
}
void Tractor::setNumarRoti(int numarRoti) noexcept{
    this->numarRoti = numarRoti;
}