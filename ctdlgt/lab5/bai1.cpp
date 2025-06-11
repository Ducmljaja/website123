#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

// Cấu trúc một nút của cây biểu thức
struct TreeNode {
    string value;       // Giá trị: toán tử hoặc toán hạng
    TreeNode* left;     // Con trái
    TreeNode* right;    // Con phải

    TreeNode(string val) {
        value = val;
        left = right = nullptr;
    }
};

// a) Duyệt tiền tố (prefix - pre-order)
void printPrefix(TreeNode* root) {
    if (!root) return;
    cout << root->value << " ";
    printPrefix(root->left);
    printPrefix(root->right);
}

// b) Duyệt trung tố (infix - in-order)
void printInfix(TreeNode* root) {
    if (!root) return;
    if (root->left && root->right) cout << "(";
    printInfix(root->left);
    cout << root->value << " ";
    printInfix(root->right);
    if (root->left && root->right) cout << ")";
}

// c) Duyệt hậu tố (postfix - post-order)
void printPostfix(TreeNode* root) {
    if (!root) return;
    printPostfix(root->left);
    printPostfix(root->right);
    cout << root->value << " ";
}

// d) Tính giá trị biểu thức từ cây
float evaluate(TreeNode* root) {
    if (!root->left && !root->right) {
        return stof(root->value); // Chuyển operand thành số thực
    }

    float leftVal = evaluate(root->left);
    float rightVal = evaluate(root->right);

    if (root->value == "+") return leftVal + rightVal;
    if (root->value == "-") return leftVal - rightVal;
    if (root->value == "*") return leftVal * rightVal;
    if (root->value == "/") return leftVal / rightVal;

    return 0;
}

int main() {
    // Tạo cây biểu thức cho ((8 - 5) * ((4 + 2) / 3))
    TreeNode* root = new TreeNode("*");

    // Nhánh trái: (8 - 5)
    root->left = new TreeNode("-");
    root->left->left = new TreeNode("8");
    root->left->right = new TreeNode("5");

    // Nhánh phải: ((4 + 2) / 3)
    root->right = new TreeNode("/");
    root->right->left = new TreeNode("+");
    root->right->left->left = new TreeNode("4");
    root->right->left->right = new TreeNode("2");
    root->right->right = new TreeNode("3");

    cout << "a) Prefix (Tiền tố): ";
    printPrefix(root);
    cout << endl;

    cout << "b) Infix (Trung tố): ";
    printInfix(root);
    cout << endl;

    cout << "c) Postfix (Hậu tố): ";
    printPostfix(root);
    cout << endl;

    cout << "d) Giá trị biểu thức hậu tố: " << evaluate(root) << endl;

    return 0;
}
