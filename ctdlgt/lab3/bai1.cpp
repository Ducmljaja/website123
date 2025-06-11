#include <iostream>
#include <string>
#include <cctype>   // isdigit, isalpha
#include <cmath>    // pow
using namespace std;

// -------------------- CẤU TRÚC STACK ----------------------
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

    void push(char value) {
        Node* newNode = new Node{value, top};
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

// ---------------------- HÀM TIỆN ÍCH ------------------------
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

// -------------------- B) INFIX TO POSTFIX -------------------
string infixToPostfix(const string& infix) {
    Stack st;
    string postfix = "";

    for (char ch : infix) {
        if (isspace(ch)) continue;

        if (isalnum(ch)) {
            postfix += ch;
        } else if (ch == '(') {
            st.push(ch);
        } else if (ch == ')') {
            while (!st.isEmpty() && st.peek() != '(') {
                postfix += st.pop();
            }
            st.pop(); // pop '('
        } else if (isOperator(ch)) {
            while (!st.isEmpty() && precedence(st.peek()) >= precedence(ch)) {
                postfix += st.pop();
            }
            st.push(ch);
        }
    }

    while (!st.isEmpty()) {
        postfix += st.pop();
    }

    return postfix;
}

// --------------- C) & D) TÍNH GIÁ TRỊ POSTFIX -----------------
class StackInt {
private:
    struct NodeInt {
        int data;
        NodeInt* next;
    };
    NodeInt* top;

public:
    StackInt() { top = nullptr; }

    void push(int value) {
        NodeInt* newNode = new NodeInt{value, top};
        top = newNode;
    }

    int pop() {
        if (!top) return 0;
        int val = top->data;
        NodeInt* temp = top;
        top = top->next;
        delete temp;
        return val;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    ~StackInt() {
        while (!isEmpty()) pop();
    }
};

int evaluatePostfix(const string& postfix) {
    StackInt st;
    for (char ch : postfix) {
        if (isdigit(ch)) {
            st.push(ch - '0'); // convert char to int
        } else if (isOperator(ch)) {
            int b = st.pop();
            int a = st.pop();
            switch (ch) {
                case '+': st.push(a + b); break;
                case '-': st.push(a - b); break;
                case '*': st.push(a * b); break;
                case '/': st.push(a / b); break;
                case '^': st.push(pow(a, b)); break;
            }
        }
    }
    return st.pop();
}

// ------------------------ MAIN -------------------------
int main() {
    string infix;
    cout << "Nhap bieu thuc trung to (vi du: 3+4*(2-1)) : ";
    getline(cin, infix);

    string postfix = infixToPostfix(infix);
    cout << "Bieu thuc hau to: " << postfix << endl;

    cout << "Gia tri bieu thuc: " << evaluatePostfix(postfix) << endl;

    return 0;
}
