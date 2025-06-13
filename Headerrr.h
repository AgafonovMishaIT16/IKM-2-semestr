#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class BinaryTree {
private:
    // Внутренняя структура для представления узла дерева
    struct TreeNode {
        int value;         // Значение, хранящееся в узле
        TreeNode* left;    // Указатель на левого потомка
        TreeNode* right;   // Указатель на правого потомка

        // Конструктор узла
        TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
    };

    TreeNode* root;                       // Указатель на корневой узел дерева
    vector<pair<int, string>> entries;    // Вектор для хранения пар (значение, путь)

    // Приватные методы класса:

    // Вставка узла с указанным значением по заданному пути
    void insertNode(int value, const string& path);
    
    // Рекурсивная функция для вывода дерева (вспомогательная для printTree())
    void printTree(TreeNode* node, const string& prefix = "", bool isLeft = false) const;
    
    // Рекурсивная функция для удаления всех узлов дерева
    void clearTree(TreeNode* node);
    
    // Вывод содержимого файла на экран
    void printFileContents(const string& filename) const;
    
    // Проверка наличия дубликата пути
    bool hasDuplicatePath(const string& path) const;
    
    // Проверка, есть ли такое же значение с другим путем
    bool hasSameValueDifferentPath(int value, const string& path) const;
    
    // Проверка запрета на совпадение значения и интерпретации пути
    bool isValueAndPathEqualForbidden(int value, const string& path) const;
    
    // Проверка непрерывности пути (все подпути должны существовать)
    bool checkPathContinuity(const string& path) const;
    
    // Проверка, является ли строка положительным целым числом
    bool isPositiveInteger(const string& s) const;
    
    // Разделение строки на токены по пробелам
    void splitString(const string& s, vector<string>& tokens) const;

public:
    // Публичный интерфейс класса:

    BinaryTree();   // Конструктор по умолчанию
    ~BinaryTree();  // Деструктор

    // Построение дерева из файла (по умолчанию "Text.txt")
    void buildFromFile(const string& filename = "Text.txt");
    
    // Вывод структуры дерева на экран
    void printTree() const;
    
    // Проверка, пусто ли дерево
    bool isEmpty() const;
};
