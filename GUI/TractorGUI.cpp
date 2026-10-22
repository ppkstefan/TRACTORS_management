#include "TractorGUI.h"

TractorGUI::TractorGUI(TractorService& srv) : srv{ srv } {
    initGUI();
    connectSignals();
    reloadData(); // Încărcăm datele din fișier la pornire
}

void TractorGUI::initGUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // 1. Tabelul
    table = new QTableView();
    model = new TractorTableModel(srv);
    table->setModel(model);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    mainLayout->addWidget(table);

    // 2. ComboBox pentru filtrarea tipului (Cerința 3)
    comboTip = new QComboBox();
    mainLayout->addWidget(comboTip);

    // 3. Formularul de adăugare
    QFormLayout* formLayout = new QFormLayout();
    txtId = new QLineEdit();
    txtDenumire = new QLineEdit();
    txtTip = new QLineEdit();
    txtRoti = new QLineEdit();
    
    formLayout->addRow("ID:", txtId);
    formLayout->addRow("Denumire:", txtDenumire);
    formLayout->addRow("Tip:", txtTip);
    formLayout->addRow("Numar Roti:", txtRoti);
    mainLayout->addLayout(formLayout);

    btnAdd = new QPushButton("Adauga Tractor");
    mainLayout->addWidget(btnAdd);

    // 4. Zona de desenare (Cerința 4)
    wheelsWidget = new WheelsWidget();
    wheelsWidget->setMinimumHeight(50); // Forțăm un spațiu minim ca să aibă loc cercurile
    mainLayout->addWidget(wheelsWidget);
}

void TractorGUI::reloadData() {
    std::string tipSelectat = comboTip->currentText().toStdString();
    
    // Trimitem noile date către model (Tabelul se va actualiza singur din cauza la beginResetModel() pe care l-am scris ieri)
    model->setTractoare(srv.getAllSorted(), tipSelectat);

    // Repopulăm ComboBox-ul ca să includă eventualele tipuri noi
    comboTip->clear();
    comboTip->addItem(""); // Opțiune goală la început pentru a anula filtrul roșu
    for (const auto& tip : srv.getDistinctTypes()) {
        comboTip->addItem(QString::fromStdString(tip));
    }
    // Setăm înapoi textul ca să nu ne strice selecția
    comboTip->setCurrentText(QString::fromStdString(tipSelectat));
}

void TractorGUI::connectSignals() {
    // A. Apăsarea butonului de Adaugă
    QObject::connect(btnAdd, &QPushButton::clicked, this, [this]() {
        try {
            int id = txtId->text().toInt();
            std::string den = txtDenumire->text().toStdString();
            std::string tip = txtTip->text().toStdString();
            int roti = txtRoti->text().toInt();

            srv.addTractor(id, den, tip, roti);
            reloadData(); // Actualizăm vizual
            
            // Curățăm text field-urile
            txtId->clear(); txtDenumire->clear(); txtTip->clear(); txtRoti->clear();
        }
        catch (const std::exception& ex) {
            // Cerința 2: Afișăm eroarea de la Service folosind QMessageBox
            QMessageBox::warning(this, "Eroare de validare", ex.what());
        }
    });

    // B. Schimbarea textului în ComboBox
    QObject::connect(comboTip, &QComboBox::currentTextChanged, this, [this]() {
        std::string tipSelectat = comboTip->currentText().toStdString();
        // Când se schimbă, re-trimitem lista modelului ca să știe ce tip să facă roșu
        model->setTractoare(srv.getAllSorted(), tipSelectat);
    });

    // C. Dăm click pe un rând din tabel -> Actualizăm desenul
    QObject::connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this]() {
        if (table->selectionModel()->selectedIndexes().isEmpty()) {
            wheelsWidget->setTractor(-1, 0); 
            return;
        }
        
        // Luăm rândul proaspăt selectat
        int row = table->selectionModel()->selectedIndexes().at(0).row();
        
        // Citim din Model ID-ul (coloana 0) și numărul de roți (coloana 3)
        int id = model->data(model->index(row, 0), Qt::DisplayRole).toInt();
        int roti = model->data(model->index(row, 3), Qt::DisplayRole).toInt();
        
        // Transmitem widget-ului să redeseneze
        wheelsWidget->setTractor(id, roti);
    });

    // D. Dăm click pe cercuri în widget-ul de jos -> Scădem numărul de roți
    QObject::connect(wheelsWidget, &WheelsWidget::wheelClicked, this, [this](int idTractor) {
        srv.decreaseRoti(idTractor); // Apelăm business logic-ul
        reloadData(); // Aducem pe ecran varianta din fișier cu roțile scăzute

        // Re-selectăm rândul automat ca utilizatorul să vadă instant cum dispar 2 cercuri
        for (int i = 0; i < model->rowCount(); i++) {
            if (model->data(model->index(i, 0), Qt::DisplayRole).toInt() == idTractor) {
                table->selectRow(i);
                break;
            }
        }
    });
}