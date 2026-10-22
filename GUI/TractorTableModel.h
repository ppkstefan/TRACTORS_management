#pragma once
#include <QAbstractTableModel>
#include "Tractor.h"
#include "TractorService.h"
#include <vector>
#include <string>

class TractorTableModel : public QAbstractTableModel {
    Q_OBJECT
private:
    std::vector<Tractor> tractoare;
    TractorService& srv;
    std::string tipSelectat; // Reținem tipul selectat în ComboBox pentru colorare (Cerința 3)

public:
    // Constructorul primește o referință către service pentru a putea apela countByType
    explicit TractorTableModel(TractorService& srv, QObject* parent = nullptr);

    // Metodă pentru a actualiza lista de tractoare din model și tipul curent selectat pentru filtru
    void setTractoare(const std::vector<Tractor>& noiTractoare, const std::string& tip = "");

    // Returnează numărul de rânduri (câte tractoare avem în listă)
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    // Returnează numărul de coloane (5 în total, conform cerinței)
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    // Returnează datele pentru o anumită celulă în funcție de rol (afișare text, culoare text, culoare fundal etc.)
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    // Setează titlurile coloanelor (Header-ul orizontal al tabelului)
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};