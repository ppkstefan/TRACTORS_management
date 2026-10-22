#pragma once
#include <QWidget>
#include <QTableView>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include "TractorService.h"
#include "TractorTableModel.h"
#include "WheelsWidget.h"

class TractorGUI : public QWidget {
    Q_OBJECT
private:
    TractorService& srv;
    TractorTableModel* model;

    QTableView* table;
    QComboBox* comboTip;
    QLineEdit* txtId;
    QLineEdit* txtDenumire;
    QLineEdit* txtTip;
    QLineEdit* txtRoti;
    QPushButton* btnAdd;
    WheelsWidget* wheelsWidget;

    void initGUI();
    void connectSignals();
    void reloadData();

public:
    explicit TractorGUI(TractorService& srv);
};