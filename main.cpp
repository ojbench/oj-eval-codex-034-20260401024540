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
    bool first_token_maybe_count = true;
    long long expected = -1;
    std::string tok;
    while (std::cin >> tok) {
        // Handle a leading operation count
        if (first_token_maybe_count) {
            first_token_maybe_count = false;
            char* endptr = nullptr;
            long long maybe_num = std::strtoll(tok.c_str(), &endptr, 10);
            if (endptr && *endptr == '\0') {
                expected = maybe_num; // ignore enforcing, just informational
                continue;
            }
        }

        long long x;
        if (!(std::cin >> x)) break;

        if (tok.size() == 1) {
            char op = tok[0];
            if (op == 'I' || op == '+') {
                sl.insert(x);
            } else if (op == 'D' || op == '-') {
                sl.deleteItem(x);
            } else if (op == 'S' || op == '?') {
                std::cout << (sl.search(x) ? 1 : 0) << '\n';
            }
            continue;
        }

        // Normalize token to lowercase
        std::string low = tok;
        for (auto &c : low) c = std::tolower(static_cast<unsigned char>(c));
        if (low == "insert" || low == "ins" || low == "i" || low == "+") {
            sl.insert(x);
        } else if (low == "delete" || low == "del" || low == "erase" || low == "remove" || low == "d" || low == "-") {
            sl.deleteItem(x);
        } else if (low == "search" || low == "find" || low == "exists" || low == "s" || low == "?") {
            std::cout << (sl.search(x) ? 1 : 0) << '\n';
        }
    }
    return 0;
}
