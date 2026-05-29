// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BSTREE_H_
#define INCLUDE_BSTREE_H_

#include <vector>
#include <utility>
#include <algorithm>
#include <stack>

template<typename KeyType>
class BSTree {
private:
    struct TreeNode {
        KeyType key;
        int freq;                // частота встречаемости
        TreeNode* left;
        TreeNode* right;

        TreeNode(const KeyType& k) : key(k), freq(1), left(nullptr), right(nullptr) {}
    };

    TreeNode* m_root;

    // Вспомогательная функция для удаления всех узлов (пост-обход)
    void deleteSubtree(TreeNode* node) {
        if (!node) return;
        deleteSubtree(node->left);
        deleteSubtree(node->right);
        delete node;
    }

    // Рекурсивный обход для сбора пар (ключ, частота) в отсортированном порядке
    void inorderCollect(TreeNode* node, std::vector<std::pair<KeyType, int>>& out) const {
        if (!node) return;
        inorderCollect(node->left, out);
        out.emplace_back(node->key, node->freq);
        inorderCollect(node->right, out);
    }

public:
    BSTree() : m_root(nullptr) {}

    ~BSTree() {
        deleteSubtree(m_root);
    }

    // Итеративная вставка (или обновление частоты)
    void add(const KeyType& key) {
        if (!m_root) {
            m_root = new TreeNode(key);
            return;
        }

        TreeNode* curr = m_root;
        while (curr) {
            if (key < curr->key) {
                if (!curr->left) {
                    curr->left = new TreeNode(key);
                    return;
                }
                curr = curr->left;
            } else if (key > curr->key) {
                if (!curr->right) {
                    curr->right = new TreeNode(key);
                    return;
                }
                curr = curr->right;
            } else {
                // ключ уже существует
                curr->freq++;
                return;
            }
        }
    }

    // Высота дерева (рекурсивно)
    int height() const {
        std::function<int(TreeNode*)> h = [&](TreeNode* node) -> int {
            if (!node) return -1;
            return 1 + std::max(h(node->left), h(node->right));
        };
        return h(m_root);
    }

    // Поиск частоты по ключу (0 – если ключ отсутствует)
    int getFrequency(const KeyType& key) const {
        TreeNode* curr = m_root;
        while (curr) {
            if (key < curr->key)
                curr = curr->left;
            else if (key > curr->key)
                curr = curr->right;
            else
                return curr->freq;
        }
        return 0;
    }

    // Возвращает все пары (ключ, частота), отсортированные по ключу
    std::vector<std::pair<KeyType, int>> getAllSortedByKey() const {
        std::vector<std::pair<KeyType, int>> result;
        inorderCollect(m_root, result);
        return result;
    }

    bool isEmpty() const {
        return m_root == nullptr;
    }
};

#endif  // INCLUDE_BSTREE_H_
