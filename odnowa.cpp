#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    int min_color;
    int min_color_num;
    int max_color;
    int max_color_num;
    int subtree_size;

    Node():
        min_color(0), min_color_num(0), max_color(0), max_color_num(0), subtree_size(-1)
    {};

    Node(int p_min_color, int p_min_color_num, int p_max_color, int p_max_color_num, int p_subtree_size):
        min_color(p_min_color), min_color_num(p_min_color_num), max_color(p_max_color), max_color_num(p_max_color_num),
        subtree_size(p_subtree_size)
    {};

    inline bool is_ok() {
        if (min_color == max_color)
            return true;
        return (min_color_num + max_color_num == subtree_size && (min_color_num == 1 || max_color_num == 1));
    }
};

Node p_tree[1 << 19];

inline Node merge(const Node &left_node, const Node &right_node) {
    Node result;
    if (left_node.subtree_size == -1) {
        if (right_node.subtree_size == -1)
            return result;
        return merge(right_node, left_node);
    } else if (right_node.subtree_size == -1) {
        result = left_node;
        return result;
    }
    result.min_color = min(left_node.min_color, right_node.min_color);
    result.max_color = max(left_node.max_color, right_node.max_color);
    result.min_color_num = (result.min_color == left_node.min_color) * left_node.min_color_num + (result.min_color == right_node.min_color) * right_node.min_color_num;
    result.max_color_num = (result.max_color == left_node.max_color) * left_node.max_color_num + (result.max_color == right_node.max_color) * right_node.max_color_num;
    result.subtree_size = left_node.subtree_size + right_node.subtree_size;
    return result;
}

inline void update_color(int color, int dfs_index) {
    int index = dfs_index + (1 << 18);
    p_tree[index].max_color = color;
    p_tree[index].min_color = color;
    p_tree[index].max_color_num = 1;
    p_tree[index].min_color_num = 1;
    p_tree[index].subtree_size = 1;

    index /= 2;
    while (index > 0) {
        p_tree[index] = merge(p_tree[index * 2], p_tree[index * 2 + 1]);
        index /= 2;
    }
}

inline bool check(int beg, int end) {
    beg += (1 << 18);
    end += (1 << 18);
    Node result;
    while (beg <= end) {
        if (beg % 2 == 1)
            result = merge(result, p_tree[beg]);
        if (end % 2 == 0)
            result = merge(result, p_tree[end]);
        beg = (beg + 1) / 2;
        end = (end - 1) / 2;
    }
    return result.is_ok();
}

inline void dfs(vector<vector<int> >& children, vector<int>& dfs_numeration, vector<int>& subtree_sizes, int *counter, int my_num) {
    subtree_sizes[my_num] = *counter; // zapisuje numer najmniejszego potomka
    for (auto node: children[my_num])
        dfs(children, dfs_numeration, subtree_sizes, counter, node);
    dfs_numeration[my_num] = *counter; // przypisuje swoj numer --> znam przedzial
    (*counter)++;
    subtree_sizes[my_num] = dfs_numeration[my_num] - subtree_sizes[my_num] + 1;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    int father;
    int colors[n];
    vector<vector<int> > childs(n);
    vector<int> dfs_numeration(n);
    vector<int> subtree_sizes(n);
    for (int i = 0; i < n - 1; i++) {
        cin >> father;
        childs[father - 1].push_back(i + 1);
    }
    for (int i = 0; i < n; i++)
        cin >> colors[i];
    int dfs_counter = 0;
    dfs(childs, dfs_numeration, subtree_sizes, &dfs_counter, 0);
    for (int i = 0; i < n; i++)
        update_color(colors[i], dfs_numeration[i]);
    char op;
    int node_num, new_color;
    for (int i = 0; i < q; i++) {
        cin >> op;
        if (op == 'z') {
            cin >> node_num >> new_color;
            update_color(new_color, dfs_numeration[node_num - 1]);
        } else if (op == '?') {
            cin >> node_num;
            if (check(dfs_numeration[node_num - 1] - subtree_sizes[node_num - 1] + 1, dfs_numeration[node_num - 1]))
                cout << "TAK" << "\n";
            else
                cout << "NIE" << "\n";
        }
    }
}
