#include <iostream>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

int bfsOdleglosc(const vector<vector<int>>& graph, int start);

vector<vector<int>> listaSasiedztwa;
vector<int> wektorSymetrii;


void barabasiRavaszVicsek(int n) {

    listaSasiedztwa.clear();
    wektorSymetrii.clear();

    vector<vector<int>> tempListaSasiedztwa;
    vector<int> dolneWezly;
    vector<int> tempDolneWezly;
    

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
    wektorSymetrii.push_back(1);
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
                    wektorSymetrii.push_back(tempListaSasiedztwa.size());
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

void luSuGuo(int wezel) {

    listaSasiedztwa.clear();
    if (wezel == 0) return;

    // 1 wezel
    listaSasiedztwa.push_back({});
    if (wezel == 1) return;

    // 2 wezly
    listaSasiedztwa[0].push_back({ 1 });
    listaSasiedztwa.push_back({ 0 });
    if (wezel == 2) return;

    // 3 wezly
    listaSasiedztwa[0].push_back({ 2 });
    listaSasiedztwa[1].push_back({ 2 });
    listaSasiedztwa.push_back({ 0,1 });
    if (wezel == 3) return;

    // kolejne wezly
    
    for (int i=3; i <= wezel; i++) {
        
        int brat, rodzic, przodek, krok, warunek;

        // sąsiedtwo z przodkiem
        krok = 0;
        warunek = 0;
        while (i > warunek) {
            krok++;
            warunek += pow(2, krok);
        }
        przodek = floor((i - 1) / 2);
        przodek = przodek % (krok - 1);
        listaSasiedztwa.push_back({ przodek });
        listaSasiedztwa[przodek].push_back({ i });
  
        // sąsiedztwo z rodzicem
        rodzic = floor((i - 1) / 2);
        listaSasiedztwa[i].push_back({rodzic});
        listaSasiedztwa[rodzic].push_back({ i });
    

        // sąsiedztwo z bratem
        if ((i & 1) == 0) {
            brat = i - 1;
            listaSasiedztwa[i].push_back({brat});
            listaSasiedztwa[brat].push_back({ i });
        }
        // cout << i << ": " << krok << endl;
    }
}

void DCN(int wezel) {

    listaSasiedztwa.clear();
    if (wezel == 0) return;

    // 1 wezel
    listaSasiedztwa.push_back({});
    if (wezel == 1) return;

    // 2 węzły
   // listaSasiedztwa[0].push_back({ 1 });
   // listaSasiedztwa.push_back({ 0 });
   // if (wezel == 2) return;
   // 
   // // 3 węzły
   // listaSasiedztwa[0].push_back({ 2 });
   // listaSasiedztwa.push_back({ 0 });
   // if (wezel == 3) return;

    // >3 węzły
    int rodzic;
    for (int i = 1; i < wezel; i++) {

        rodzic = floor((i - 1) / 2);

        listaSasiedztwa.push_back(listaSasiedztwa[rodzic]);
        if (!(i & 1)) {
            listaSasiedztwa[i].pop_back();
        }
        listaSasiedztwa[i].push_back(rodzic);

        for (int j : listaSasiedztwa[i]) {
            listaSasiedztwa[j].push_back(i);
        }
    }

}

int bfsOdleglosc(const vector<vector<int>>& graf, int start) {
    int n = graf.size();                // liczba wierzchołków
    vector<int> odleglosci(n, -1);      // wektor odleglosci o wielkości n, zainicjalizowany samymi -1 (-1 oznacza nieosiągalne)
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

//*
void wypiszGraf(const vector<vector<int>>& graf) {
    for (int i = 0; i < graf.size(); i++) {
        cout << i << ": ";
        for (int sasiad : graf[i]) {
            cout << sasiad << " ";
        }
        cout << endl;
    }
}//*/

/*
int main() {

    int a = 45;
    
    // 23   => 440
    // 45   => 1812
    // 91   => 7764
    // 242  => 56875
    DCN(a);

    int sumaCalkowita = 0;
    for (int i = 0; i < listaSasiedztwa.size(); ++i) {
        sumaCalkowita += bfsOdleglosc(listaSasiedztwa, i);
    }

    //Obliczanie sumy odległości między wszystkimi parami węzłów
    //int sumaOdleglosci = bfsOdleglosc(listaSasiedztwa, 0) ;
       
    //for (int wezel : wektorSymetrii) {
    //    sumaOdleglosci += bfsOdleglosc(listaSasiedztwa, wezel);
    //}
       
    cout << a << ": " << sumaCalkowita/2 << endl;
    //wypiszGraf(listaSasiedztwa);
    cout << endl;
    
    return 0;
}
//*/

//*
int main() {
    int model, parametr1 = 0, parametr2;
    int sumaOdleglosci;
    int sumaCalkowita;

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
            sumaOdleglosci = bfsOdleglosc(listaSasiedztwa, 0) / 2;
                
            for (int wezel : wektorSymetrii) {
                sumaOdleglosci += bfsOdleglosc(listaSasiedztwa, wezel);
            }
            cout << sumaOdleglosci << endl;
            break;
        case 1:
            // Implementacja modelu Lu–Su–Guo
            luSuGuo(parametr1-1);

            //Obliczanie sumy odległości między wszystkimi parami węzłów
            sumaCalkowita = 0;
            for (int i = 0; i < listaSasiedztwa.size(); ++i) {
                sumaCalkowita += bfsOdleglosc(listaSasiedztwa, i);
            }
            cout << sumaCalkowita/2 << endl;
            break;
        
        //case 2:
        //    // Implementacja modelu Simplical
        //    cout << 0 << endl;
        //    break;
        //case 3:
        //    // Implementacja modelu Wzrostowo-iteracyjnego
        //    cin >> parametr2; // Wczytanie parametru r
        //    cout << 0 << endl;
        //    break;
        case 4:
            // Implementacja modelu DCN
            DCN(parametr1);
            sumaCalkowita = 0;
            for (int i = 0; i < listaSasiedztwa.size(); ++i) {
                sumaCalkowita += bfsOdleglosc(listaSasiedztwa, i);
            }
            cout << sumaCalkowita/2 << endl;
            break;
        //case 5:
        //    // Implementacja modelu GFG
        //    cout << 0 << endl;
        //    break;
        //case 6:
        //    // Implementacja modelu Kronecker
        //    cout << 0 << endl;
        //    break;
        
        }
    }
    return 0;
}
//*/
