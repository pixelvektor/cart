//
// Created by Fabian on 02.07.17.
//

#include "main.h"

using namespace std;

int main() {
    SearchCART search;

    // Ausgabe der Größe des Videos
    cout << "width:  "
         << search.getSize()[0] << endl
         << "height: "
         << search.getSize()[1] << endl;

    // schrittweise das Video durchlaufen und die Servos korrigieren
    int i = 0;
    while (i < 100) {
        search.loader();
        i++;
    }
    return 0;
}