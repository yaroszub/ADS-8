// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main(int argc, char* argv[]) {
    // Определяем имя файла: из аргументов или по умолчанию
    const char* filename = (argc > 1) ? argv[1] : "src/war_peace.txt";
    BST<std::string> wordTree;
    std::cout << "Чтение файла: " << filename << std::endl;
    makeTree(wordTree, filename);
    if (wordTree.empty()) {
        std::cerr << "Ошибка: дерево пусто. Возможно, файл не найден или не содержит слов." << std::endl;
        return 1;
    }
    // Вычисляем общее количество уникальных слов и общее число слов
    auto allPairs = wordTree.getAllSortedByKey();
    int totalUnique = allPairs.size();
    int totalWords = 0;
    for (const auto& p : allPairs) {
        totalWords += p.second;
    }
    std::cout << "\n=== Статистика ===" << std::endl;
    std::cout << "Глубина (высота) дерева: " << wordTree.depth() << std::endl;
    std::cout << "Уникальных слов: " << totalUnique << std::endl;
    std::cout << "Всего слов в тексте: " << totalWords << std::endl;
    std::cout << "\n=== Частоты слов (по убыванию) ===" << std::endl;
    printFreq(wordTree);
    std::cout << "\nРезультат сохранён в result/freq.txt" << std::endl;
    return 0;
}
