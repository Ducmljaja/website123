#include <iostream>
using namespace std;

// ---------------- CẤU TRÚC STACK DÙNG LIÊN KẾT ----------------
struct Node {
    char data;
    Node* next;
};

class Stack {
private:
    Node* top;

public:
    Stack() {
        top = nullptr;
    }

    void push(char ch) {
        Node* newNode = new Node{ch, top};
        top = newNode;
    }

    char pop() {
        if (!top) return '\0';
        char val = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return val;
    }

    char peek() {
        return (top) ? top->data : '\0';
    }

    bool isEmpty() {
        return top == nullptr;
    }

    ~Stack() {
        while (!isEmpty()) pop();
    }
};

// ------------ HÀM KIỂM TRA NGOẶC --------------------
bool isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

bool isBalanced(const string& expr) {
    Stack s;
    for (char ch : expr) {
        if (ch == '(' || ch == '{' || ch == '[') {
            s.push(ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (s.isEmpty() || !isMatchingPair(s.pop(), ch)) {
                return false;
            }
        }
    }
    return s.isEmpty(); // phải hết sạch ngoặc
}

// ---------------- MAIN ---------------------
int main() {
    string expr;
    cout << "Nhap bieu thuc can kiem tra: ";
    getline(cin, expr);

    if (isBalanced(expr)) {
        cout << "✅ Bieu thuc HOP LE (ngoac dung thu tu)." << endl;
    } else {
        cout << "❌ Bieu thuc KHONG HOP LE (ngoac sai)." << endl;
    }

    return 0;
}
