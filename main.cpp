#include <QApplication>
#include "../REPOSITORY/TractorRepo.h"
#include "../SERVICE/TractorService.h"
#include "../GUI/TractorGUI.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Conectăm instanțele între ele:
    // Repo lucrează cu fișierul -> Service folosește Repo -> GUI folosește Service

    // IMPORTANT: Asigură-te că fișierul "tractoare.txt" există în folderul în care se generează executabilul!
    // Dacă nu ești sigur unde, dă calea absolută, ex: "C:\\Proiecte\\OOP\\tractoare.txt"
    TractorRepo repo("tractoare.txt");
    TractorService srv(repo);
    TractorGUI gui(srv);

    gui.setWindowTitle("Gestiune Tractoare");
    gui.resize(700, 500); // Îi dăm niște dimensiuni ok la pornire
    gui.show();

    return a.exec();
}