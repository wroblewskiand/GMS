// GMS.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

int bfsOdleglosc(const vector<vector<int>>& graph, int start);

// Lista sąsiedztwa do przechowywania grafu
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

        tempListaSasiedztwa = listaSasiedztwa;  // Kopiowanie węzłów z poprzedniej iteracji do tymczasowej listy
        tempDolneWezly.clear();
        int wielkoscJednostki = listaSasiedztwa.size();
        //int wielkoscJednostki = pow(3, i - 1);

        // Dodawanie dwóch jednostek
        for (int jednostkaID = 1; jednostkaID <= 2; jednostkaID++) {

            int przesuniecie = wielkoscJednostki * jednostkaID;
            //int przesuniecie = tempListaSasiedztwa.size() * jednostkaID;

            // dodawanie nowej jednostki
            for (int wezel = 0; wezel < wielkoscJednostki; wezel++) {
                listaSasiedztwa.push_back({});
            }

            for (int wezel = 0; wezel < wielkoscJednostki; wezel++) {

                int aktualnyWezel = wezel + przesuniecie;
                for (int sasiad = 0; sasiad < tempListaSasiedztwa[wezel].size(); sasiad++) {

                    int aktualnySasiad = tempListaSasiedztwa[wezel][sasiad] + przesuniecie;

                    listaSasiedztwa[aktualnyWezel].push_back(aktualnySasiad);
                    listaSasiedztwa[aktualnySasiad].push_back(aktualnyWezel);

                    if (jednostkaID == 1) {
                        wezlySymetrii.push_back(listaSasiedztwa.size());
                    }
                }

            }
            // Łączenie z korzeniem
            for (int wezel : dolneWezly) {
                listaSasiedztwa[0].push_back(wezel + przesuniecie);
                listaSasiedztwa[wezel + przesuniecie].push_back(0);
                tempDolneWezly.push_back(wezel + przesuniecie);
            }
        }
        dolneWezly = tempDolneWezly;
    }
}


int bfsOdleglosc(const vector<vector<int>>& listaSasiedztwa, int start) {
    int n = listaSasiedztwa.size();                   // liczba wierzchołków
    vector<int> odleglosci(n, -1);           // tablica odległości (-1 oznacza nieosiągalne)
    queue<int> q;                           // kolejka BFS

    int suma = 0;                          // suma wszystkich odległości
    odleglosci[start] = 0;                   // odległość do siebie samego to 0
    q.push(start);

    while (!q.empty()) {
        int wezel = q.front();
        q.pop();

        for (int neighbor : listaSasiedztwa[wezel]) {
            if (odleglosci[neighbor] == -1) { // jeśli sąsiad nie został jeszcze odwiedzony
                odleglosci[neighbor] = odleglosci[wezel] + 1; // Odległość to odległość bieżącego + 1
                suma += odleglosci[neighbor]; // zwiększamy sumę odległości
                q.push(neighbor);
            }
        }
    }
    return suma;
}


// Funkcja do obliczania najkrótszej ścieżki między dwoma węzłami
//int bfs(int start, int end) {
//    vector<bool> odwiedzone(listaSasiedztwa.size(), false);
//    vector<int> odleglosc(listaSasiedztwa.size(), 0);
//    queue<int> kolejka;
//
//    odwiedzone[start] = true;
//    kolejka.push(start);
//
//    while (!kolejka.empty()) {
//        int v = kolejka.front();
//        kolejka.pop();
//
//        for (int sasiad : listaSasiedztwa[v]) {
//            if (!odwiedzone[sasiad]) {
//                odwiedzone[sasiad] = true;
//                odleglosc[sasiad] = odleglosc[v] + 1;
//                kolejka.push(sasiad);
//
//                if (sasiad == end) {
//                    return odleglosc[end];
//                }
//            }
//        }
//    }
//    return -1; // Nie ma ścieżki między węzłami
//}

//int obliczSumeOdleglosci(const vector<vector<int>>& listaSasiedztwa) {
//    int sumaOdleglosci = 0;
//    for (int i = 0; i < listaSasiedztwa.size(); i++) {
//        for (int j = i + 1; j < listaSasiedztwa.size(); j++) {
//            sumaOdleglosci += bfs(i, j);
//        }
//    }
//    return sumaOdleglosci;
//}


void wypiszGraf(const vector<vector<int>>& graf) {
    for (int i = 0; i < graf.size(); i++) {
        cout << i << ": ";
        for (int sasiad : graf[i]) {
            cout << sasiad << " ";
        }
        cout << endl;
    }
}


int main() {

    for (int i = 2; i <= 3; i++) {

        // Implementacja modelu Barabasi–Ravasz–Vicsek
        barabasiRavaszVicsek(i);

        // Obliczanie sumy odległości między wszystkimi parami węzłów
        int sumaOdleglosci = bfsOdleglosc(listaSasiedztwa, 0) / 2;

        for (int wezel : wezlySymetrii) {
            sumaOdleglosci += bfsOdleglosc(listaSasiedztwa, wezel);
        }

        cout << i << ": " << sumaOdleglosci << endl;
        wypiszGraf(listaSasiedztwa);
        cout << endl;
    }
    return 0;
}


/*
*
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

            cout << listaSasiedztwa.size() << endl;
            break;

        case 1:
            // Implementacja modelu Lu–Su–Guo
            break;
        case 2:
            // Implementacja modelu Simplical
            break;
        case 3:
            // Implementacja modelu Wzrostowo-iteracyjnego
            cin >> parametr2; // Wczytanie parametru r
            break;
        case 4:
            // Implementacja modelu DCN
            break;
        case 5:
            // Implementacja modelu GFG
            break;
        case 6:
            // Implementacja modelu Kronecker
            break;
        }
    }

    return 0;
}
// */


// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
