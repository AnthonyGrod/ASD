#include <iostream>

using namespace std;

int drzewo[1 << 21], obciazenie[1 << 21];
int ll;

bool czyLisc(int wierzcholek) {
    if (wierzcholek >= ll)
        return true;
    return false;
}

void wypelnij(int wierzcholek, int lewySyn, int prawySyn, int c) {
    drzewo[lewySyn] = (drzewo[wierzcholek] / 2) * (c - 1);
    drzewo[prawySyn] = (drzewo[wierzcholek] / 2) * (c - 1);
    obciazenie[lewySyn] = c;
    obciazenie[prawySyn] = c;
}

void spychanie(int wierzcholek) {
    int lewySyn = wierzcholek * 2;
    int prawySyn = wierzcholek * 2 + 1;
    if (obciazenie[wierzcholek] == 1 && !czyLisc(wierzcholek))
        wypelnij(wierzcholek, lewySyn, prawySyn, 1);
    else if (obciazenie[wierzcholek] == 2 && !czyLisc(wierzcholek))
        wypelnij(wierzcholek, lewySyn, prawySyn, 2);

    obciazenie[wierzcholek] = 0;
}

void malowanie(int a, int b, int c, int lewy, int prawy, int wierzcholek) {
    if (lewy > b || prawy < a)
        return;
    if (a <= lewy && prawy <= b) {
        obciazenie[wierzcholek] = c + 1;
        drzewo[wierzcholek] = c * (prawy - lewy + 1);
        return;
    }

    int lewySyn = wierzcholek * 2;
    int prawySyn = wierzcholek * 2 + 1;
    spychanie(wierzcholek);
    malowanie(a, b, c, lewy, (lewy + prawy) / 2, lewySyn);
    malowanie(a, b, c, (lewy + prawy) / 2 + 1, prawy, prawySyn);
    drzewo[wierzcholek] = drzewo[lewySyn] + drzewo[prawySyn];
}

int main() {
    int n, m, a, b;
    cin >> n >> m;
    ll = 1;
    for (ll = 1; ll < n; ll <<= 1);
    while (ll <= n)
        ll <<= 1;
    char c;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        if (c == 'B')
            malowanie(a, b, 1, 1, ll, 1);
        else
            malowanie(a, b, 0, 1, ll, 1);
        cout << drzewo[1] << '\n';
    }

}