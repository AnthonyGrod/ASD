#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_set>

int main() {
    int n, m;
    std::string s;
    std::vector<int> first_line;
    std::vector< std::vector<int> > matches_players;

    // Wczytywanie pierwszej linijki
    unsigned int helper;
    getline(std::cin, s);
    std::istringstream my_stream(s);
    while (my_stream) {
        my_stream >> helper;
        if (my_stream) {
            first_line.push_back(helper);
        }
    }

    n = first_line[0];
    m = first_line[1];

    // Wczytywanie reszty danych
    for (int i = 0; i < m; i++) {
        getline(std::cin, s);
        std::istringstream my_stream(s);
        std::vector<int> line;
        while (my_stream) {
            my_stream >> helper;
            if (my_stream) {
                line.push_back(helper);
            }
        }
        matches_players.push_back(line);
    }

    /** Tworze n elementowy wektor wypelniony 64-bitowymi zerami. Dla każdego meczu
     * patrzymy, czy dany zawodnik (ma swoje pole w wektorze (na pozycji i-1)) jest
     * po lewej czy po prawej. Jeśli po lewej to nic nie robimy, a jeśli po prawej to
     * w jego numerze w bicie o numerze j-1 od początku wpisujemy 1. Potem parsujemy
     * wektor do setu i patrzymy, czy się zmniejszył
     */
    std::vector<uint64_t> players_bit(n, 0);
    // Iterujemy się po meczach
    for (int i = 0; i < m; i++) {
        // Iterujemy się po zawodnikach z drugiej połowy w danym meczu
        for (int j = n / 2; j < n; j++) {
            players_bit[matches_players[i][j] - 1] |= 1ULL << i;
        }
    }

    std::unordered_set<uint64_t> unique;
    for (int i = 0; i < n; i++) {
        unique.insert(players_bit[i]);
    }

    if (unique.size() != players_bit.size()) {
        std::cout << "NIE\n";
    } 
    else {
        std::cout << "TAK\n";
    }

}