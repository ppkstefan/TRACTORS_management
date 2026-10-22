#pragma once
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class WheelsWidget : public QWidget {
    Q_OBJECT // Macro obligatoriu în Qt pentru orice clasă care definește semnale/sloturi proprii
private:
    int idTractorCurent = -1;
    int numarRoti = 0;

public:
    explicit WheelsWidget(QWidget* parent = nullptr) : QWidget(parent) {}

    // Metodă apelată când selectăm un tractor în tabel
    void setTractor(int id, int roti) {
        idTractorCurent = id;
        numarRoti = roti;
        update(); // Spune sistemului Qt: "Atenție, trebuie să redesenezi widget-ul!"
    }

    signals:
        // Semnal pe care îl vom "emite" când utilizatorul dă click corect
        void wheelClicked(int idTractor);

protected:
    // Metodă automată apelată de Qt când trebuie să afișeze componenta pe ecran
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);

        // Desenăm un cerc pentru fiecare roată
        for (int i = 0; i < numarRoti; i++) {
            // (x, y, lățime, înălțime). Spațiem cercurile cu 30 de pixeli pe axa X.
            painter.drawEllipse(10 + i * 30, 10, 20, 20);
        }
    }

    // Metodă automată apelată de Qt când se dă click oriunde pe acest widget
    void mousePressEvent(QMouseEvent* event) override {
        if (idTractorCurent != -1) {
            // Verificăm dacă click-ul a fost exact în perimetrul unde sunt desenate cercurile
            int clickX = event->pos().x();
            int clickY = event->pos().y();

            if (clickY >= 10 && clickY <= 30 && clickX >= 10 && clickX <= 10 + numarRoti * 30) {
                // "Aruncăm" semnalul în aer. Cineva (TractorGUI) îl va prinde.
                emit wheelClicked(idTractorCurent);
            }
        }
    }
};