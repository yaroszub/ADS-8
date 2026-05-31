// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <vector>
#include <utility>

template <typename T>
class BST {
 private:
    struct Vertex {
        T key;
        int freq;
        Vertex* lLink;
        Vertex* rLink;

        explicit Vertex(const T& k) : key(k), freq(1), lLink(nullptr), rLink(nullptr) {}
    };

    Vertex* m_root;

    // Рекурсивная вставка (возвращает изменённый корень поддерева)
    Vertex* add(Vertex* v, const T& k) {
        if (!v) {
            return new Vertex(k);
        }
        if (k < v->key) {
            v->lLink = add(v->lLink, k);
        } else if (k > v->key) {
            v->rLink = add(v->rLink, k);
        } else {
            v->freq++;
        }
        return v;
    }

    // Рекурсивное вычисление глубины (высота)
    int getDepth(const Vertex* v) const {
        if (!v) return -1;
        int leftDepth = getDepth(v->lLink);
        int rightDepth = getDepth(v->rLink);
        return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
    }

    // Рекурсивный поиск вершины по ключу
    const Vertex* findVertex(const Vertex* v, const T& k) const {
        if (!v || v->key == k) return v;
        if (k < v->key) return findVertex(v->lLink, k);
        return findVertex(v->rLink, k);
    }

    // Рекурсивный симметричный обход для сбора пар
    void inOrder(const Vertex* v, std::vector<std::pair<T, int>>& out) const {
        if (!v) return;
        inOrder(v->lLink, out);
        out.emplace_back(v->key, v->freq);
        inOrder(v->rLink, out);
    }

    // Рекурсивное удаление всех вершин
    void erase(Vertex* v) {
        if (!v) return;
        erase(v->lLink);
        erase(v->rLink);
        delete v;
    }

 public:
    BST() : m_root(nullptr) {}

    ~BST() {
        erase(m_root);
    }

    void insert(const T& key) {
        m_root = add(m_root, key);
    }

    int depth() const {
        return getDepth(m_root);
    }

    int search(const T& value) const {
        const Vertex* v = findVertex(m_root, value);
        return v ? v->freq : 0;
    }

    std::vector<std::pair<T, int>> getAllSortedByKey() const {
        std::vector<std::pair<T, int>> result;
        inOrder(m_root, result);
        return result;
    }

    bool empty() const {
        return m_root == nullptr;
    }
};

#endif  // INCLUDE_BST_H_
