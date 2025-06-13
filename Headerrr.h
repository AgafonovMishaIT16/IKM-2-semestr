#pragma once

class BinaryTree {
private:
    struct TreeNode {
        int value;
        TreeNode* left;
        TreeNode* right;

        TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
    };

    TreeNode* root;
    vector<pair<int, string>> entries;

    void insertNode(int value, const string& path);
    void printTree(TreeNode* node, const string& prefix = "", bool isLeft = false) const;
    void clearTree(TreeNode* node);
    void printFileContents(const string& filename) const;
    bool hasDuplicatePath(const string& path) const;
    bool hasSameValueDifferentPath(int value, const string& path) const;
    bool isValueAndPathEqualForbidden(int value, const string& path) const;
    bool checkPathContinuity(const string& path) const;
    bool isPositiveInteger(const string& s) const;
    void splitString(const string& s, vector<string>& tokens) const;

public:
    BinaryTree();
    ~BinaryTree();

    void buildFromFile(const string& filename = "Текст.txt");
    void printTree() const;
    bool isEmpty() const;
};