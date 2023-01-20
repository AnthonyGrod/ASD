#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Wczytujemy dane i je sortujemy 
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n, k, l, x;
    cin >> n >> k >> l;
    vector<int> robotnicy;
    for (int i = 0; i < n; i++) {
        cin >> x;
        robotnicy.push_back(x);
    }
    sort(robotnicy.begin(), robotnicy.end());

    // Tworzę tablicę określającą którym z rzędu członkiem komitetu mógłby być i-ty robotnik
    vector<int> miejsceWKomitecie(n, 0);
    int miejsce = 1;
    // Taka może być maksymalna odległość między dwoma następnymi członkami komitetu aby nie było dziury
    int odleglosc = 2 * k;
    // Pierwszy robotnik zawsze będzie musiał być jako pierwszy członek komitetu (o ile w ogóle nim będzie)
    miejsceWKomitecie[0] = 1;
    int aktualneMiejsce = 2;
    bool pierwszy = true;
    int ostatniPierwszy = 0;
    int liczbaZnacznikow = 0;
    // Iterujemy się po tych początkowych robotnikach którzy mogą być pierwszymi członkami komitetu
    for (int i = 1; i < n && pierwszy; i++) {
        if (robotnicy[i] - robotnicy[0] <= k) {
            ostatniPierwszy++;
            miejsceWKomitecie[i] = 1;
        }
        else {
            pierwszy = false;
            liczbaZnacznikow++;
            cout << "Znacznik na indeksie " << i + 1 << endl;
        }
    }
    int pierwszyWczesniejszy = ostatniPierwszy + 1;
    int ostatniaZamiana = 0;
    for (int i = ostatniPierwszy + 1; i < n; i++) {
        if (robotnicy[i] - robotnicy[pierwszyWczesniejszy] > odleglosc) {
            aktualneMiejsce++;
            pierwszyWczesniejszy = i;
            liczbaZnacznikow++;
            ostatniaZamiana = i;
            cout << "Znacznik na indeksie " << i + 1 << endl;
        }
        miejsceWKomitecie[i] = aktualneMiejsce;
    }

    // Teraz trzeba sprawdzić, czy ostatnia pinezka pokrywa robotników do końca
    
    for (int i = 0; i < n; i++) {
        cout << miejsceWKomitecie[i] << " ";
    }
    cout << endl;
    cout << "liczbaZnacznikow: " << liczbaZnacznikow << endl;
    cout << "ostatniaZamiana: " << ostatniaZamiana << endl;


}
