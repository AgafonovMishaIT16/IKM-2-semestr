#include "Headerrr.h"

BinaryTree::BinaryTree() : root(new TreeNode(0)) {}

BinaryTree::~BinaryTree() {
    clearTree(root);
}

void BinaryTree::clearTree(TreeNode* node) {
    if (node) {
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
}

void BinaryTree::splitString(const string& s, vector<string>& tokens) const {
    tokens.clear();
    string current;
    for (char c : s) {
        if (isspace(c)) {
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            }
        }
        else {
            current += c;
        }
    }
    if (!current.empty()) {
        tokens.push_back(current);
    }
}

bool BinaryTree::isPositiveInteger(const string& s) const {
    if (s.empty()) return false;

    for (char c : s) {
        if (c < '0' || c > '9') {
            return false;
        }
    }

    if (s.length() > 1 && s[0] == '0') {
        return false;
    }

    return true;
}

bool BinaryTree::hasDuplicatePath(const string& path) const {
    for (const auto& entry : entries) {
        if (entry.second == path) {
            return true;
        }
    }
    return false;
}

bool BinaryTree::hasSameValueDifferentPath(int value, const string& path) const {
    for (const auto& entry : entries) {
        if (entry.first == value && entry.second != path) {
            return true;
        }
    }
    return false;
}

bool BinaryTree::isValueAndPathEqualForbidden(int value, const string& path) const {
    // Специальное разрешение для случая 1 и "1"
    if (value == 1 && path == "1") {
        return false;
    }

    if (path.empty()) return false;

    int pathValue = 0;
    for (char c : path) {
        if (c != '0' && c != '1') {
            return false;
        }
        pathValue = pathValue * 2 + (c - '0');
    }
    return pathValue == value;
}

bool BinaryTree::checkPathContinuity(const string& path) const {
    for (size_t len = 1; len < path.length(); ++len) {
        string subpath = path.substr(0, len);
        bool subpathExists = false;

        for (const auto& entry : entries) {
            if (entry.second == subpath) {
                subpathExists = true;
                break;
            }
        }

        if (!subpathExists) {
            return false;
        }
    }
    return true;
}

void BinaryTree::printFileContents(const string& filename) const {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл");
    }

    cout << "\nСодержимое файла " << filename << ":\n";
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

void BinaryTree::insertNode(int value, const string& path) {
    if (value == 0) {
        throw runtime_error("Нулевое значение запрещено (кроме корня)");
    }

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

    current->value = value;
    entries.emplace_back(value, path);
}

void BinaryTree::buildFromFile(const string& filename) {
    printFileContents(filename);

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
        splitString(line, tokens);

        if (tokens.size() != 2) {
            throw runtime_error("Строка " + to_string(lineNumber) +
                ": должно быть ровно два значения (число и путь)");
        }

        const string& valueStr = tokens[0];
        const string& path = tokens[1];

        if (!isPositiveInteger(valueStr)) {
            throw runtime_error("Строка " + to_string(lineNumber) +
                ": значение должно быть положительным целым числом");
        }

        int value = 0;
        for (char c : valueStr) {
            value = value * 10 + (c - '0');
        }

        for (char c : path) {
            if (c != '0' && c != '1') {
                throw runtime_error("Строка " + to_string(lineNumber) +
                    ": путь может содержать только 0 и 1");
            }
        }

        insertNode(value, path);
    }

    if (file.bad()) {
        throw runtime_error("Ошибка чтения файла");
    }
}

void BinaryTree::printTree(TreeNode* node, const string& prefix, bool isLeft) const {
    if (node == nullptr) return;

    cout << prefix;
    cout << (isLeft ? "+--(" : "+--(") << node->value << ")" << endl;

    printTree(node->right, prefix + (isLeft ? "|   " : "    "), true);
    printTree(node->left, prefix + (isLeft ? "|   " : "    "), false);
}

void BinaryTree::printTree() const {
    cout << "\nСтруктура дерева:\n";
    cout << "(" << root->value << ")" << endl;
    printTree(root->left, "", true);
    printTree(root->right, "", false);
}