#include <iostream>
#include <vector>
#include <algorithm> // For std::max

// Định nghĩa cấu trúc Node cho cây tìm kiếm nhị phân
struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int val) : key(val), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    Node* root;

    // Hàm hỗ trợ để chèn một node một cách đệ quy
    Node* _insert_recursive(Node* node, int key) {
        if (node == nullptr) {
            return new Node(key);
        }

        if (key < node->key) {
            node->left = _insert_recursive(node->left, key);
        } else { // key >= node->key (xử lý các giá trị trùng lặp bằng cách đặt chúng vào cây con bên phải)
            node->right = _insert_recursive(node->right, key);
        }
        return node;
    }

    // Hàm hỗ trợ duyệt cây theo thứ tự pre-order
    void _pre_order_recursive(Node* node, std::vector<int>& result) {
        if (node) {
            result.push_back(node->key);
            _pre_order_recursive(node->left, result);
            _pre_order_recursive(node->right, result);
        }
    }

    // Hàm hỗ trợ duyệt cây theo thứ tự in-order
    void _in_order_recursive(Node* node, std::vector<int>& result) {
        if (node) {
            _in_order_recursive(node->left, result);
            result.push_back(node->key);
            _in_order_recursive(node->right, result);
        }
    }

    // Hàm hỗ trợ duyệt cây theo thứ tự post-order
    void _post_order_recursive(Node* node, std::vector<int>& result) {
        if (node) {
            _post_order_recursive(node->left, result);
            _post_order_recursive(node->right, result);
            result.push_back(node->key);
        }
    }

    // Hàm hỗ trợ tìm kiếm giá trị một cách đệ quy
    Node* _find_value_recursive(Node* node, int key) {
        if (node == nullptr || node->key == key) {
            return node;
        }
        if (key < node->key) {
            return _find_value_recursive(node->left, key);
        } else {
            return _find_value_recursive(node->right, key);
        }
    }

    // Hàm hỗ trợ đếm tổng số node một cách đệ quy
    int _count_nodes_recursive(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + _count_nodes_recursive(node->left) + _count_nodes_recursive(node->right);
    }

    // Hàm hỗ trợ đếm số node nội bộ một cách đệ quy
    int _count_internal_nodes_recursive(Node* node) {
        if (node == nullptr || (node->left == nullptr && node->right == nullptr)) {
            // Node lá hoặc cây rỗng không phải là node nội bộ
            return 0;
        }
        return 1 + _count_internal_nodes_recursive(node->left) + _count_internal_nodes_recursive(node->right);
    }

    // Hàm hỗ trợ tính chiều cao của cây một cách đệ quy
    int _get_height_recursive(Node* node) {
        if (node == nullptr) {
            return -1; // Chiều cao của cây rỗng là -1
        }
        int left_height = _get_height_recursive(node->left);
        int right_height = _get_height_recursive(node->right);
        return 1 + std::max(left_height, right_height);
    }

    // Hàm hỗ trợ tìm node có giá trị nhỏ nhất trong một cây con
    Node* _min_value_node(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // Hàm hỗ trợ xóa một node một cách đệ quy
    Node* _delete_node_recursive(Node* root_node, int key) {
        if (root_node == nullptr) {
            return root_node;
        }

        if (key < root_node->key) {
            root_node->left = _delete_node_recursive(root_node->left, key);
        } else if (key > root_node->key) {
            root_node->right = _delete_node_recursive(root_node->right, key);
        } else {
            // Node với key được tìm thấy

            // Trường hợp 1: Node không có con hoặc chỉ có một con
            if (root_node->left == nullptr) {
                Node* temp = root_node->right;
                delete root_node;
                return temp;
            } else if (root_node->right == nullptr) {
                Node* temp = root_node->left;
                delete root_node;
                return temp;
            }

            // Trường hợp 2: Node có hai con
            // Tìm phần tử kế nhiệm theo thứ tự (nhỏ nhất trong cây con bên phải)
            Node* temp = _min_value_node(root_node->right);

            // Sao chép nội dung của phần tử kế nhiệm theo thứ tự vào node này
            root_node->key = temp->key;

            // Xóa phần tử kế nhiệm theo thứ tự
            root_node->right = _delete_node_recursive(root_node->right, temp->key);
        }
        return root_node;
    }

    // Hàm hỗ trợ giải phóng bộ nhớ của cây (đệ quy)
    void _delete_tree_recursive(Node* node) {
        if (node) {
            _delete_tree_recursive(node->left);
            _delete_tree_recursive(node->right);
            delete node;
        }
    }


public:
    BinarySearchTree() : root(nullptr) {}

    // Destructor để giải phóng bộ nhớ
    ~BinarySearchTree() {
        _delete_tree_recursive(root);
    }

    // a) Chèn một node vào cây
    void insert(int key) {
        root = _insert_recursive(root, key);
    }

    // b) Duyệt cây theo thứ tự pre-order / in-order / post-order.
    std::vector<int> pre_order_traversal() {
        std::vector<int> result;
        _pre_order_recursive(root, result);
        return result;
    }

    std::vector<int> in_order_traversal() {
        std::vector<int> result;
        _in_order_recursive(root, result);
        return result;
    }

    std::vector<int> post_order_traversal() {
        std::vector<int> result;
        _post_order_recursive(root, result);
        return result;
    }

    // c) Tìm phần tử nhỏ nhất / lớn nhất.
    int find_smallest() {
        if (root == nullptr) {
            std::cerr << "Cây rỗng, không có phần tử nhỏ nhất.\n";
            return -1; // Hoặc ném ngoại lệ
        }
        Node* current = root;
        while (current->left) {
            current = current->left;
        }
        return current->key;
    }

    int find_largest() {
        if (root == nullptr) {
            std::cerr << "Cây rỗng, không có phần tử lớn nhất.\n";
            return -1; // Hoặc ném ngoại lệ
        }
        Node* current = root;
        while (current->right) {
            current = current->right;
        }
        return current->key;
    }

    // d) Tìm một giá trị đã cho.
    bool find_value(int key) {
        return _find_value_recursive(root, key) != nullptr;
    }

    // e) Đếm số node.
    int count_nodes() {
        return _count_nodes_recursive(root);
    }

    // f) Đếm số node nội bộ.
    int count_internal_nodes() {
        return _count_internal_nodes_recursive(root);
    }

    // g) Xác định chiều cao của cây.
    int get_height() {
        return _get_height_recursive(root);
    }

    // h) Xóa một node khỏi cây.
    void delete_node(int key) {
        root = _delete_node_recursive(root, key);
    }
};

// Hàm tiện ích để in vector
void print_vector(const std::vector<int>& vec) {
    for (int val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

// --- Chương trình chính ---
int main() {
    BinarySearchTree bst;

    // Tạo cây tìm kiếm nhị phân dựa trên hình ảnh
    std::vector<int> elements = {8, 3, 10, 1, 6, 9, 14, 4, 7, 13};
    for (int element : elements) {
        bst.insert(element);
    }

    std::cout << "Cây tìm kiếm nhị phân đã được tạo từ hình ảnh:\n";

    // Thực hiện các thao tác:

    // a) Chèn một node vào cây.
    std::cout << "\na) Chèn node 5 vào cây.\n";
    bst.insert(5);
    std::cout << "Duyệt cây theo thứ tự in-order sau khi chèn 5: ";
    print_vector(bst.in_order_traversal());

    // b) Duyệt cây theo thứ tự pre-order / in-order / post-order.
    std::cout << "\nb) Duyệt cây:\n";
    std::cout << "Duyệt cây theo thứ tự pre-order: ";
    print_vector(bst.pre_order_traversal());
    std::cout << "Duyệt cây theo thứ tự in-order: ";
    print_vector(bst.in_order_traversal());
    std::cout << "Duyệt cây theo thứ tự post-order: ";
    print_vector(bst.post_order_traversal());

    // c) Tìm phần tử nhỏ nhất / lớn nhất.
    std::cout << "\nc) Phần tử nhỏ nhất và lớn nhất:\n";
    std::cout << "Phần tử nhỏ nhất: " << bst.find_smallest() << std::endl;
    std::cout << "Phần tử lớn nhất: " << bst.find_largest() << std::endl;

    // d) Tìm một giá trị đã cho.
    std::cout << "\nd) Tìm một giá trị đã cho:\n";
    int value_to_find_1 = 6;
    if (bst.find_value(value_to_find_1)) {
        std::cout << "Giá trị " << value_to_find_1 << " được tìm thấy trong cây.\n";
    } else {
        std::cout << "Giá trị " << value_to_find_1 << " không được tìm thấy trong cây.\n";
    }

    int value_to_find_2 = 100;
    if (bst.find_value(value_to_find_2)) {
        std::cout << "Giá trị " << value_to_find_2 << " được tìm thấy trong cây.\n";
    } else {
        std::cout << "Giá trị " << value_to_find_2 << " không được tìm thấy trong cây.\n";
    }

    // e) Đếm số node.
    std::cout << "\ne) Đếm số node:\n";
    std::cout << "Tổng số node: " << bst.count_nodes() << std::endl;

    // f) Đếm số node nội bộ.
    std::cout << "\nf) Đếm số node nội bộ:\n";
    std::cout << "Số node nội bộ: " << bst.count_internal_nodes() << std::endl;

    // g) Xác định chiều cao của cây.
    std::cout << "\ng) Xác định chiều cao của cây:\n";
    std::cout << "Chiều cao của cây: " << bst.get_height() << std::endl;

    // h) Xóa một node khỏi cây.
    std::cout << "\nh) Xóa một node khỏi cây:\n";
    std::cout << "Duyệt cây theo thứ tự in-order trước khi xóa: ";
    print_vector(bst.in_order_traversal());

    int node_to_delete_1 = 6; // Node có hai con
    std::cout << "Đang xóa node " << node_to_delete_1 << "...\n";
    bst.delete_node(node_to_delete_1);
    std::cout << "Duyệt cây theo thứ tự in-order sau khi xóa 6: ";
    print_vector(bst.in_order_traversal());

    int node_to_delete_2 = 1; // Node lá
    std::cout << "Đang xóa node " << node_to_delete_2 << "...\n";
    bst.delete_node(node_to_delete_2);
    std::cout << "Duyệt cây theo thứ tự in-order sau khi xóa 1: ";
    print_vector(bst.in_order_traversal());

    // Tạo lại cây để minh họa các trường hợp xóa khác
    BinarySearchTree bst_recreated;
    std::vector<int> elements_recreated = {8, 3, 10, 1, 6, 9, 14, 4, 7, 13};
    for (int element : elements_recreated) {
        bst_recreated.insert(element);
    }
    std::cout << "\nĐang tạo lại cây để kiểm tra xóa thêm.\n";
    std::cout << "Duyệt cây theo thứ tự in-order của cây đã tạo lại: ";
    print_vector(bst_recreated.in_order_traversal());

    int node_to_delete_3 = 3; // Node có hai con
    std::cout << "Đang xóa node " << node_to_delete_3 << "...\n";
    bst_recreated.delete_node(node_to_delete_3);
    std::cout << "Duyệt cây theo thứ tự in-order sau khi xóa 3: ";
    print_vector(bst_recreated.in_order_traversal());

    int node_to_delete_4 = 8; // Xóa node gốc
    std::cout << "Đang xóa node gốc " << node_to_delete_4 << "...\n";
    bst_recreated.delete_node(node_to_delete_4);
    std::cout << "Duyệt cây theo thứ tự in-order sau khi xóa 8 (gốc): ";
    print_vector(bst_recreated.in_order_traversal());

    return 0;
}