#include "Headerrr.h"

// Конструктор дерева: создает корневой узел со значением 0
BinaryTree::BinaryTree() : root(new TreeNode(0)) {}

// Деструктор дерева: очищает память, удаляя все узлы
BinaryTree::~BinaryTree() {
    clearTree(root);
}

// Рекурсивная функция для удаления всех узлов дерева
void BinaryTree::clearTree(TreeNode* node) {
    if (node) {
        clearTree(node->left);  // Рекурсивно удаляем левое поддерево
        clearTree(node->right); // Рекурсивно удаляем правое поддерево
        delete node;            // Удаляем текущий узел
    }
}

// Разделение строки на токены по пробелам
void BinaryTree::splitString(const string& s, vector<string>& tokens) const {
    tokens.clear();
    string current;
    for (char c : s) {
        if (isspace(c)) {       // Если встретили пробел
            if (!current.empty()) {
                tokens.push_back(current); // Добавляем текущее слово в токены
                current.clear();
            }
        }
        else {
            current += c;       // Продолжаем накапливать символы слова
        }
    }
    if (!current.empty()) {     // Добавляем последнее слово, если оно есть
        tokens.push_back(current);
    }
}

// Проверка, является ли строка положительным целым числом
bool BinaryTree::isPositiveInteger(const string& s) const {
    if (s.empty()) return false; // Пустая строка не число

    // Проверяем, что все символы - цифры
    for (char c : s) {
        if (c < '0' || c > '9') {
            return false;
        }
    }

    // Проверяем на ведущие нули
    if (s.length() > 1 && s[0] == '0') {
        return false;
    }

    return true;
}

// Проверка на дублирование пути
bool BinaryTree::hasDuplicatePath(const string& path) const {
    for (const auto& entry : entries) {
        if (entry.second == path) {
            return true; // Нашли дубликат пути
        }
    }
    return false;
}

// Проверка, есть ли такое же значение с другим путем
bool BinaryTree::hasSameValueDifferentPath(int value, const string& path) const {
    for (const auto& entry : entries) {
        if (entry.first == value && entry.second != path) {
            return true; // Нашли такое же значение с другим путем
        }
    }
    return false;
}

// Проверка запрета на совпадение значения и интерпретации пути
bool BinaryTree::isValueAndPathEqualForbidden(int value, const string& path) const {
    // Специальное разрешение для случая 1 и "1"
    if (value == 1 && path == "1") {
        return false;
    }

    if (path.empty()) return false;

    // Преобразуем путь в число (бинарная интерпретация)
    int pathValue = 0;
    for (char c : path) {
        if (c != '0' && c != '1') {
            return false;
        }
        pathValue = pathValue * 2 + (c - '0');
    }
    return pathValue == value; // Сравниваем значение узла и интерпретацию пути
}

// Проверка непрерывности пути (все подпути должны существовать)
bool BinaryTree::checkPathContinuity(const string& path) const {
    for (size_t len = 1; len < path.length(); ++len) {
        string subpath = path.substr(0, len); // Берем подпуть
        bool subpathExists = false;

        // Проверяем, существует ли такой подпуть
        for (const auto& entry : entries) {
            if (entry.second == subpath) {
                subpathExists = true;
                break;
            }
        }

        if (!subpathExists) {
            return false; // Подпуть не найден
        }
    }
    return true;
}

// Вывод содержимого файла на экран
void BinaryTree::printFileContents(const string& filename) const {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл");
    }

    cout << "\nСодержимое файла " << filename << ":\n";
    string line;
    while (getline(file, line)) {
        cout << line << endl; // Выводим каждую строку файла
    }
    file.close();
}

// Вставка узла в дерево по указанному пути
void BinaryTree::insertNode(int value, const string& path) {
    if (value == 0) {
        throw runtime_error("Нулевое значение запрещено (кроме корня)");
    }

    // Проверки различных условий перед вставкой
    if (hasDuplicatePath(path)) {
        throw runtime_error("Дубликат пути: '" + path + "'");
    }
    if (hasSameValueDifferentPath(value, path)) {
        throw runtime_error("Значение " + to_string(value) + " уже существует с другим путем");
    }
    if (isValueAndPathEqualForbidden(value, path)) {
        throw runtime_error("Значение " + to_string(value) + " совпадает с интерпретацией пути '" + path + "'");
    }
    if (!path.empty() && !checkPathContinuity(path)) {
        throw runtime_error("Пропущен подпуть для пути: '" + path + "'");
    }

    // Проходим по пути и создаем узлы при необходимости
    TreeNode* current = root;
    for (char direction : path) {
        if (direction == '0') {
            if (!current->left) {
                current->left = new TreeNode(0);
            }
            current = current->left;
        }
        else if (direction == '1') {
            if (!current->right) {
                current->right = new TreeNode(0);
            }
            current = current->right;
        }
        else {
            throw runtime_error("Недопустимый символ в пути: '" + string(1, direction) + "'");
        }
    }

    current->value = value; // Устанавливаем значение
    entries.emplace_back(value, path); // Добавляем запись
}

// Построение дерева из файла
void BinaryTree::buildFromFile(const string& filename) {
    printFileContents(filename); // Выводим содержимое файла

    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл");
    }

    entries.clear();
    entries.emplace_back(0, ""); // Добавляем корень

    string line;
    int lineNumber = 0;
    while (getline(file, line)) {
        lineNumber++;
        vector<string> tokens;
        splitString(line, tokens); // Разбиваем строку на токены

        if (tokens.size() != 2) {
            throw runtime_error("Строка " + to_string(lineNumber) +
                ": должно быть ровно два значения (число и путь)");
        }

        const string& valueStr = tokens[0];
        const string& path = tokens[1];

        // Проверка формата данных
        if (!isPositiveInteger(valueStr)) {
            throw runtime_error("Строка " + to_string(lineNumber) +
                ": значение должно быть положительным целым числом");
        }

        // Преобразование строки в число
        int value = 0;
        for (char c : valueStr) {
            value = value * 10 + (c - '0');
        }

        // Проверка корректности пути
        for (char c : path) {
            if (c != '0' && c != '1') {
                throw runtime_error("Строка " + to_string(lineNumber) +
                    ": путь может содержать только 0 и 1");
            }
        }

        insertNode(value, path); // Вставляем узел
    }

    if (file.bad()) {
        throw runtime_error("Ошибка чтения файла");
    }
}

// Рекурсивная функция для вывода дерева
void BinaryTree::printTree(TreeNode* node, const string& prefix, bool isLeft) const {
    if (node == nullptr) return;

    cout << prefix;
    cout << (isLeft ? "+--(" : "+--(") << node->value << ")" << endl;

    // Рекурсивный вывод поддеревьев
    printTree(node->right, prefix + (isLeft ? "|   " : "    "), true);
    printTree(node->left, prefix + (isLeft ? "|   " : "    "), false);
}

// Функция для вывода всего дерева
void BinaryTree::printTree() const {
    cout << "\nСтруктура дерева:\n";
    cout << "(" << root->value << ")" << endl; // Выводим корень
    printTree(root->left, "", true);  // Выводим левое поддерево
    printTree(root->right, "", false); // Выводим правое поддерево
}
