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
         << search.getSize()[1] << endl
         << "fps: "
         << search.getFPS() << endl;

    // schrittweise das Video durchlaufen und die Servos korrigieren
    int i = 0;
    while (i < 75) {
        vector<int> ballPos = search.loader(i);

        cout << "X: "
         << ballPos[0]
         << " Y: "
         << ballPos[1]
         << " FC: "
         << search.getFC() << endl;
        i++;
    }
    return 0;
}