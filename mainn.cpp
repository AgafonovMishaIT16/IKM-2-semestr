#include "Headerrr.h"
#include <windows.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    cout << "Агафонов Михаил. ИТ-16-2024" << endl;
    cout << " " << endl;
    cout << "ИКМ по C++. 2 семестр. 19 вариант" << endl;
    cout << " " << endl;
    cout << "Задание:" << endl;
    cout << "В файле даны n целых чисел, и здесь же указан путь их размещения в бинарном" << endl;
    cout << "дереве виде двоичного кода(коды не повторяются).Построить двоичное" << endl;
    cout << "дерево целых чисел, в котором путь по дереву определяется указанным" << endl;
    cout << "двоичным кодом в этом листе(1 – переход к правому потомку, 0 - переход к" << endl;
    cout << "потомку).В корень автоматически заносится значение 0." << endl;
    cout << " " << endl;

    try {
        BinaryTree tree;
        tree.buildFromFile();
        tree.printTree();
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }
    return 0;
}