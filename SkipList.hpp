#ifndef SKIP_LIST_HPP
#define SKIP_LIST_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <memory>

template<typename T>
class SkipList {
private:
    struct Node {
        T value;
        std::vector<Node*> forward;
        Node(int level, const T& val) : value(val), forward(level, nullptr) {}
    };

    int maxLevel;
    float p;
    int level;
    Node* header;

    int randomLevel() {
        int lvl = 1;
        while (((double) std::rand() / RAND_MAX) < p && lvl < maxLevel) {
            ++lvl;
        }
        return lvl;
    }

public:
    SkipList(int maxLevel_ = 32, float p_ = 0.5f) : maxLevel(maxLevel_), p(p_), level(1) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        // header with dummy value; we don't use its value
        header = new Node(maxLevel, T());
    }

    ~SkipList() {
        Node* cur = header->forward[0];
        while (cur) {
            Node* nxt = cur->forward[0];
            delete cur;
            cur = nxt;
        }
        delete header;
    }

    void insert(const T & item) {
        std::vector<Node*> update(maxLevel, nullptr);
        Node* x = header;
        for (int i = level - 1; i >= 0; --i) {
            while (x->forward[i] && x->forward[i]->value < item) {
                x = x->forward[i];
            }
            update[i] = x;
        }

        x = x->forward[0];
        if (x && !(item < x->value) && !(x->value < item)) {
            return; // already exists
        }

        int lvl = randomLevel();
        if (lvl > level) {
            for (int i = level; i < lvl; ++i) {
                update[i] = header;
            }
            level = lvl;
        }
        Node* newNode = new Node(lvl, item);
        for (int i = 0; i < lvl; ++i) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }

    bool search(const T & item) {
        Node* x = header;
        for (int i = level - 1; i >= 0; --i) {
            while (x->forward[i] && x->forward[i]->value < item) {
                x = x->forward[i];
            }
        }
        x = x->forward[0];
        if (x && !(item < x->value) && !(x->value < item)) return true;
        return false;
    }

    void deleteItem(const T & item) {
        std::vector<Node*> update(maxLevel, nullptr);
        Node* x = header;
        for (int i = level - 1; i >= 0; --i) {
            while (x->forward[i] && x->forward[i]->value < item) {
                x = x->forward[i];
            }
            update[i] = x;
        }
        x = x->forward[0];
        if (!x || (item < x->value) || (x->value < item)) return; // not found

        for (int i = 0; i < level; ++i) {
            if (update[i]->forward[i] != x) break;
            update[i]->forward[i] = x->forward[i];
        }
        delete x;
        while (level > 1 && header->forward[level-1] == nullptr) {
            --level;
        }
    }
};

#endif

