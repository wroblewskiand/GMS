#include <iostream>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

int bfsOdleglosc(const vector<vector<int>>& graph, int start);

vector<vector<int>> listaSasiedztwa;
vector<int> wezlySymetrii;


void barabasiRavaszVicsek(int n) {

    listaSasiedztwa.clear();
    wezlySymetrii.clear();

    vector<vector<int>> tempListaSasiedztwa;
    vector<int> dolneWezly;
    vector<int> tempDolneWezly;
    vector<int> wektorSymetrii;


    // Inicjalizacja listy sąsiedztwa dla kroku 0 (pojedynczy węzeł)
    listaSasiedztwa.push_back({});  // Korzeń
    if (n < 1) { return; }

    // Inicjalizacja listy sąsiedztwa dla kroku 1
    for (int i = 1; i <= 2; i++) {

        listaSasiedztwa.push_back({});
        listaSasiedztwa[0].push_back(i);
        listaSasiedztwa[i].push_back(0);
        dolneWezly.push_back(i);
    }
    wezlySymetrii.push_back(1);
    if (n == 1) { return; }


    // Inicjalizacja listy sąsiedztwa dla kroku >=2
    for (int i = 2; i <= n; i++) {

        // Kopiowanie węzłów z poprzedniej iteracji do tymczasowej listy
        tempListaSasiedztwa = listaSasiedztwa;  

        tempDolneWezly.clear();
        int wielkoscKopii = listaSasiedztwa.size();

        // Dodawanie dwóch jednostek
        for (int nrKopi = 1; nrKopi <= 2; nrKopi++) {

            int przesuniecie = wielkoscKopii * nrKopi;

            // dodawanie nowej jednostki, przechodzenie po węzłach grafu kopiowanego
            for (int wezel = 0; wezel < wielkoscKopii; wezel++) {

                vector<int> sasiedztwoWezla;
                for (int sasiad : listaSasiedztwa[wezel]) {
                    sasiedztwoWezla.push_back(sasiad + przesuniecie);
                }

                if (nrKopi == 1) {
                    wezlySymetrii.push_back(tempListaSasiedztwa.size());
                }
                
                tempListaSasiedztwa.push_back(sasiedztwoWezla);
            }
            // Łączenie z korzeniem
            for (int dolnyWezel : dolneWezly) {
                int przesuniecieDolnychWezlow = dolnyWezel + przesuniecie;
                tempListaSasiedztwa[0].push_back(przesuniecieDolnychWezlow);
                tempListaSasiedztwa[przesuniecieDolnychWezlow].push_back(0);
                tempDolneWezly.push_back(przesuniecieDolnychWezlow);
            }
        }
        dolneWezly = tempDolneWezly;
        listaSasiedztwa = tempListaSasiedztwa;
    }
}


int bfsOdleglosc(const vector<vector<int>>& graf, int start) {
    int n = graf.size();                // liczba wierzchołków
    vector<int> odleglosci(n, -1);      // tablica odległości (-1 oznacza nieosiągalne)
    queue<int> q;                       // kolejka BFS

    int suma = 0;                       // wyzerowanie odległości
    odleglosci[start] = 0;              // wyzerowanie licznika
    q.push(start);

    while (!q.empty()) {
        int wezel = q.front();
        q.pop();

        for (int neighbor : graf[wezel]) {
            if (odleglosci[neighbor] == -1) {                   // jeśli sąsiad nie został jeszcze odwiedzony
                odleglosci[neighbor] = odleglosci[wezel] + 1;   // Odległość to odległość bieżącego + 1
                suma += odleglosci[neighbor];                   // zwiększamy sumę odległości
                q.push(neighbor);
            }
        }
    }
    return suma;
}

//void wypiszGraf(const vector<vector<int>>& graf) {
//    for (int i = 0; i < graf.size(); i++) {
//        cout << i << ": ";
//        for (int sasiad : graf[i]) {
//            cout << sasiad << " ";
//        }
//        cout << endl;
//    }
//}


//int main() {
//
//    for (int i = 4; i <= 8; i++) {
//
//        // Implementacja modelu Barabasi–Ravasz–Vicsek
//        barabasiRavaszVicsek(i);
//
//        // Obliczanie sumy odległości między wszystkimi parami węzłów
//        int sumaOdleglosci = bfsOdleglosc(listaSasiedztwa, 0) / 2;
//
//        for (int wezel : wezlySymetrii) {
//            sumaOdleglosci += bfsOdleglosc(listaSasiedztwa, wezel);
//        }
//
//        cout << i << ": " << sumaOdleglosci << endl;
//        //wypiszGraf(listaSasiedztwa);
//        cout << endl;
//    }
//    return 0;
//}



int main() {
    int model, parametr1 = 0, parametr2;

    while (cin >> model) {
        // Wczytywanie parametrów modelu
        if (model == 0 || model == 1 || model == 3 || model == 4) {
            cin >> parametr1;
        }
        else if (model == 6) {
            cin >> parametr1 >> parametr2;
        }

        switch (model) {
        case 0:
            // Implementacja modelu Barabasi–Ravasz–Vicsek
            barabasiRavaszVicsek(parametr1);

            //Obliczanie sumy odległości między wszystkimi parami węzłów
            int sumaOdleglosci = bfsOdleglosc(listaSasiedztwa, 0) / 2;
                
            for (int wezel : wezlySymetrii) {
                sumaOdleglosci += bfsOdleglosc(listaSasiedztwa, wezel);
            }
            cout << sumaOdleglosci << endl;
            break;
        /*
        case 1:
            // Implementacja modelu Lu–Su–Guo
            cout << 0 << endl;
            break;
        case 2:
            // Implementacja modelu Simplical
            cout << 0 << endl;
            break;
        case 3:
            // Implementacja modelu Wzrostowo-iteracyjnego
            cin >> parametr2; // Wczytanie parametru r
            cout << 0 << endl;
            break;
        case 4:
            // Implementacja modelu DCN
            cout << 0 << endl;
            break;
        case 5:
            // Implementacja modelu GFG
            cout << 0 << endl;
            break;
        case 6:
            // Implementacja modelu Kronecker
            cout << 0 << endl;
            break;
        */
        }
    }

    return 0;
}
