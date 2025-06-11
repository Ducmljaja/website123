#include <iostream>
using namespace std;

// Cấu trúc nút của đa thức
struct Node {
    int coeff;   // hệ số
    int pow;     // số mũ
    Node* next;
};

// Thêm một hạng tử vào cuối đa thức
void appendTerm(Node*& head, int coeff, int pow) {
    Node* newNode = new Node{coeff, pow, nullptr};

    if (!head) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }
}

// Nhập đa thức
void inputPolynomial(Node*& poly) {
    int coeff, pow;
    cout << "Nhập đa thức (nhập hệ số = 0 để dừng):\n";
    while (true) {
        cout << "Hệ số: ";
        cin >> coeff;
        if (coeff == 0) break;
        cout << "Số mũ: ";
        cin >> pow;
        appendTerm(poly, coeff, pow);
    }
}

// In đa thức
void printPolynomial(Node* poly) {
    if (!poly) {
        cout << "0\n";
        return;
    }

    while (poly) {
        cout << (poly->coeff > 0 && poly != nullptr ? (poly != nullptr ? " + " : "") : "")
             << poly->coeff << "x^" << poly->pow;
        poly = poly->next;
    }
    cout << endl;
}

// Cộng hai đa thức
Node* addPolynomials(Node* poly1, Node* poly2) {
    Node* result = nullptr;
    while (poly1 && poly2) {
        if (poly1->pow > poly2->pow) {
            appendTerm(result, poly1->coeff, poly1->pow);
            poly1 = poly1->next;
        } else if (poly2->pow > poly1->pow) {
            appendTerm(result, poly2->coeff, poly2->pow);
            poly2 = poly2->next;
        } else {
            appendTerm(result, poly1->coeff + poly2->coeff, poly1->pow);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }
    while (poly1) {
        appendTerm(result, poly1->coeff, poly1->pow);
        poly1 = poly1->next;
    }
    while (poly2) {
        appendTerm(result, poly2->coeff, poly2->pow);
        poly2 = poly2->next;
    }
    return result;
}

// Trừ hai đa thức
Node* subtractPolynomials(Node* poly1, Node* poly2) {
    Node* result = nullptr;
    while (poly1 && poly2) {
        if (poly1->pow > poly2->pow) {
            appendTerm(result, poly1->coeff, poly1->pow);
            poly1 = poly1->next;
        } else if (poly2->pow > poly1->pow) {
            appendTerm(result, -poly2->coeff, poly2->pow);
            poly2 = poly2->next;
        } else {
            appendTerm(result, poly1->coeff - poly2->coeff, poly1->pow);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }
    while (poly1) {
        appendTerm(result, poly1->coeff, poly1->pow);
        poly1 = poly1->next;
    }
    while (poly2) {
        appendTerm(result, -poly2->coeff, poly2->pow);
        poly2 = poly2->next;
    }
    return result;
}

// Giải phóng bộ nhớ
void freePolynomial(Node*& poly) {
    while (poly) {
        Node* temp = poly;
        poly = poly->next;
        delete temp;
    }
}

int main() {
    Node* poly1 = nullptr;
    Node* poly2 = nullptr;

    cout << "Nhập đa thức thứ nhất:\n";
    inputPolynomial(poly1);

    cout << "Nhập đa thức thứ hai:\n";
    inputPolynomial(poly2);

    cout << "Đa thức thứ nhất là: ";
    printPolynomial(poly1);

    cout << "Đa thức thứ hai là: ";
    printPolynomial(poly2);

    Node* sum = addPolynomials(poly1, poly2);
    cout << "Tổng hai đa thức là: ";
    printPolynomial(sum);

    Node* diff = subtractPolynomials(poly1, poly2);
    cout << "Hiệu hai đa thức là: ";
    printPolynomial(diff);

    // Giải phóng bộ nhớ
    freePolynomial(poly1);
    freePolynomial(poly2);
    freePolynomial(sum);
    freePolynomial(diff);

    return 0;
}
