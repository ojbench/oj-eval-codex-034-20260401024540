#include <bits/stdc++.h>
#include "SkipList.hpp"

// We implement a driver that supports operations:
// I x -> insert x
// D x -> delete x
// S x -> search x (prints 1 if exists, 0 otherwise)
// The input is a sequence of lines until EOF.
// T can be 64-bit signed integers for testing.

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    SkipList<long long> sl;
    char op;
    long long x;
    while (std::cin >> op >> x) {
        if (op == 'I') {
            sl.insert(x);
        } else if (op == 'D') {
            sl.deleteItem(x);
        } else if (op == 'S') {
            std::cout << (sl.search(x) ? 1 : 0) << '\n';
        }
    }
    return 0;
}

