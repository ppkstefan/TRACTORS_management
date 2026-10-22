#include "TractorTableModel.h"
#include <QBrush>
#include <QColor>

TractorTableModel::TractorTableModel(TractorService& srv, QObject* parent)
    : QAbstractTableModel{ parent }, srv{ srv } {}

void TractorTableModel::setTractoare(const std::vector<Tractor>& noiTractoare, const std::string& tip) {
    // beginResetModel anunță interfața grafică (QTableView) că datele se vor schimba complet
    beginResetModel();
    this->tractoare = noiTractoare;
    this->tipSelectat = tip;
    // endResetModel obligă QTableView să se redeseneze cu noile date
    endResetModel();
}

int TractorTableModel::rowCount(const QModelIndex& parent) const {
    return static_cast<int>(tractoare.size());
}

int TractorTableModel::columnCount(const QModelIndex& parent) const {
    return 5; // id, denumire, tip, numarRoti, numar tractoare de acelasi tip
}

QVariant TractorTableModel::data(const QModelIndex& index, int role) const {
    // Verificăm dacă indexul este valid
    if (!index.isValid() || index.row() >= static_cast<int>(tractoare.size())) {
        return QVariant();
    }

    const auto& t = tractoare[index.row()];

    // Rolul de afișare text (ce scrie efectiv în fiecare celulă)
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
            case 0: return t.getId();
            case 1: return QString::fromStdString(t.getDenumire());
            case 2: return QString::fromStdString(t.getTip());
            case 3: return t.getNumarRoti();
            case 4: return srv.countByType(t.getTip()); // Cerința 1: număr tractoare de același tip
            default: return QVariant();
        }
    }

    // Cerința 3: Colorarea cu roșu a rândurilor care au tipul selectat în QComboBox
    if (role == Qt::BackgroundRole) {
        if (!tipSelectat.empty() && t.getTip() == tipSelectat) {
            return QBrush(Qt::red); // Returnăm o pensulă de culoare roșie pentru fundalul celulei
        }
    }

    return QVariant();
}

QVariant TractorTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    // Setăm etichetele doar pentru header-ul orizontal (coloane)
    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0: return "ID";
            case 1: return "Denumire";
            case 2: return "Tip";
            case 3: return "Numar Roti";
            case 4: return "Total acelasi tip";
            default: return QVariant();
        }
    }

    return QVariant();
}