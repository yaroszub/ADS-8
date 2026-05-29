// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
#include "bst.h"

// Вспомогательная функция: извлечение слов из потока (без изменения логики)
static void readWordsFromStream(std::ifstream& input, BST<std::string>& tree) {
    std::string word;
    char ch;
    while (input.get(ch)) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            word += std::tolower(static_cast<unsigned char>(ch));
        } else {
            if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
    }
    if (!word.empty()) {
        tree.insert(word);
    }
}

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: cannot open file " << filename << std::endl;
        return;
    }
    readWordsFromStream(file, tree);
    file.close();
}

void printFreq(BST<std::string>& tree) {
    auto pairs = tree.getAllSortedByKey();

    // Сортировка по убыванию частоты, затем по возрастанию слова
    std::sort(pairs.begin(), pairs.end(),
        [](const auto& a, const auto& b) {
            if (a.second != b.second)
                return a.second > b.second;
            return a.first < b.first;
        });

    // Вывод на экран
    for (const auto& entry : pairs) {
        std::cout << entry.first << " : " << entry.second << "\n";
    }

    // Запись в файл
    std::ofstream out("result/freq.txt");
    if (!out) {
        std::cerr << "Error: cannot create result/freq.txt" << std::endl;
        return;
    }
    for (const auto& entry : pairs) {
        out << entry.first << " : " << entry.second << "\n";
    }
    out.close();
}
