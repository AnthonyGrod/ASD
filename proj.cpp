#include <iostream>
#include <tuple>
#include <queue>
#include <vector>
#include <algorithm>
#include <functional>
#include <utility>

void erase_element(std::vector<int> &vec, int value) {
    vec.erase(std::remove(std::begin(vec), std::end(vec), value), std::end(vec));
}

int find_index(std::vector<int> v, int val) {
    auto lower = std::lower_bound(v.begin(), v.end(), val);
    auto idx = std::distance(v.begin(), lower);
    return (int) idx;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    int n, m, k;
    std::cin >> n >> m >> k;
    int cost[n], needed_projects[n]; // ilu programistów jest potrzebnych dla danego projektu
    std::vector<uint64_t> needed_for[n];

    for (int i = 0; i < n; i++) {
        std::cin >> cost[i];
        needed_projects[i] = 0;
    }

    int a, b;
    for (int i = 0; i < m; i++) {
        std::cin >> a >> b;
        needed_for[b - 1].push_back(a - 1);
        needed_projects[a - 1]++;
    }

    for (int i = 0; i < n; i++) {
        sort(needed_for[i].begin(), needed_for[i].end());
    }

    std::vector<int> selected;

    std::priority_queue<std::tuple<int, int>, std::vector<std::tuple<int, int> >, std::greater<std::tuple<int, int> > > q;

    // Dodawanie lisci
    for (int i = 0; i < n; i++) {
        if (needed_projects[i] == 0) {
            std::tuple<int, int> temp = std::make_tuple(cost[i], i);
            q.push(temp);
        }
    }

    int max = 0;

    // do czego dany jest potrzebny i ile potrzeba projektow zeby wykonac dany projekt
    while (selected.size() < k) {
        std::tuple<int, int> elem = q.top(); // pobieramy najmniejszy liść
        if (std::get<0>(elem) > max) {
            max = std::get<0>(elem);
        }
        selected.push_back(std::get<1>(elem)); // dodajemy jego id do wybranych
        q.pop(); // usuwamy go
        int elem_nexts = needed_for[std::get<1>(elem)].size(); // dzieci naszego
        for (int i = 0; i < elem_nexts; i++) {
            needed_projects[needed_for[std::get<1>(elem)][i]] -= 1;
            if (needed_projects[needed_for[std::get<1>(elem)][i]] == 0) {
                std::tuple<int, int> temp = std::make_tuple(cost[needed_for[std::get<1>(elem)][i]], needed_for[std::get<1>(elem)][i]);
                q.push(temp);
            }
        }
    }

    std::cout << max << "\n";

}