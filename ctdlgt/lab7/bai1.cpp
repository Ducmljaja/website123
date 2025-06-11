#include <iostream> // Để sử dụng cout, cin
#include <vector>   // Để sử dụng std::vector cho ma trận kề và danh sách visited
#include <queue>    // Để sử dụng std::queue cho thuật toán BFS
#include <stack>    // Để sử dụng std::stack cho thuật toán DFS (phi đệ quy)
#include <set>      // Để theo dõi các node đã thăm (không thực sự cần thiết ở đây với vector<bool> nhưng hữu ích trong các trường hợp phức tạp hơn)

// Định nghĩa lớp Graph để biểu diễn đồ thị và thực hiện các thao tác
class Graph {
private:
    int numVertices; // Số lượng đỉnh của đồ thị
    std::vector<std::vector<int>> adjMatrix; // Ma trận kề để lưu trữ các cạnh

public:
    // Hàm khởi tạo (Constructor) để khởi tạo đồ thị với n đỉnh
    // Kích thước ma trận kề là (n+1)x(n+1) để dễ dàng làm việc với các đỉnh được đánh số từ 1 đến n
    Graph(int n) : numVertices(n) {
        adjMatrix.resize(n + 1, std::vector<int>(n + 1, 0)); // Khởi tạo tất cả các giá trị là 0 (không có cạnh)
    }

    // Hàm thêm một cạnh giữa hai đỉnh u và v
    // Vì đây là đồ thị vô hướng, nên nếu có cạnh (u,v) thì cũng có cạnh (v,u)
    void addEdge(int u, int v) {
        // Kiểm tra xem các đỉnh có hợp lệ không (trong phạm vi từ 1 đến numVertices)
        if (u >= 1 && u <= numVertices && v >= 1 && v <= numVertices) {
            adjMatrix[u][v] = 1; // Đặt 1 để chỉ ra có cạnh từ u đến v
            adjMatrix[v][u] = 1; // Đặt 1 để chỉ ra có cạnh từ v đến u (đồ thị vô hướng)
        } else {
            std::cout << "Chỉ số đỉnh không hợp lệ khi thêm cạnh (" << u << ", " << v << ")\n";
        }
    }

    // Hàm in ma trận kề của đồ thị
    void printAdjMatrix() {
        std::cout << "Ma tran ke:\n";
        // In tiêu đề cột (các số đỉnh)
        std::cout << "  ";
        for (int i = 1; i <= numVertices; ++i) {
            std::cout << i << " ";
        }
        std::cout << "\n";
        // In từng hàng của ma trận
        for (int i = 1; i <= numVertices; ++i) {
            std::cout << i << " "; // In số đỉnh của hàng hiện tại
            for (int j = 1; j <= numVertices; ++j) {
                std::cout << adjMatrix[i][j] << " "; // In giá trị tại ô [i][j] (0 hoặc 1)
            }
            std::cout << "\n";
        }
    }

    // a) Duyệt đồ thị theo chiều rộng (Breadth-First Search - BFS)
    // Bắt đầu từ một đỉnh được chỉ định
    void BFS(int startNode) {
        // Kiểm tra đỉnh bắt đầu có hợp lệ không
        if (startNode < 1 || startNode > numVertices) {
            std::cout << "Dinh bat dau khong hop le cho BFS.\n";
            return;
        }

        std::queue<int> q; // Hàng đợi để lưu trữ các đỉnh sẽ được thăm
        // Vector 'visited' để đánh dấu các đỉnh đã được thăm.
        // Kích thước (numVertices + 1) để dễ dàng làm việc với các đỉnh từ 1 đến numVertices.
        std::vector<bool> visited(numVertices + 1, false);

        q.push(startNode);       // Đẩy đỉnh bắt đầu vào hàng đợi
        visited[startNode] = true; // Đánh dấu đỉnh bắt đầu là đã thăm

        std::cout << "Duyet BFS (bat dau tu dinh " << startNode << "): ";
        while (!q.empty()) { // Trong khi hàng đợi chưa rỗng
            int currentNode = q.front(); // Lấy đỉnh ở đầu hàng đợi
            q.pop();                     // Xóa đỉnh đó khỏi hàng đợi
            std::cout << currentNode << " "; // In đỉnh hiện tại

            // Duyệt qua tất cả các đỉnh kề của đỉnh hiện tại
            for (int i = 1; i <= numVertices; ++i) {
                // Nếu có cạnh giữa currentNode và i, VÀ i chưa được thăm
                if (adjMatrix[currentNode][i] == 1 && !visited[i]) {
                    visited[i] = true; // Đánh dấu i là đã thăm
                    q.push(i);         // Đẩy i vào hàng đợi để thăm sau
                }
            }
        }
        std::cout << std::endl; // Xuống dòng sau khi kết thúc duyệt
    }

    // b) Duyệt đồ thị theo chiều sâu (Depth-First Search - DFS) - đệ quy
    // Bắt đầu từ một đỉnh được chỉ định
    void DFS(int startNode) {
        // Kiểm tra đỉnh bắt đầu có hợp lệ không
        if (startNode < 1 || startNode > numVertices) {
            std::cout << "Dinh bat dau khong hop le cho DFS.\n";
            return;
        }

        // Vector 'visited' để đánh dấu các đỉnh đã được thăm.
        std::vector<bool> visited(numVertices + 1, false);
        std::cout << "Duyet DFS (bat dau tu dinh " << startNode << "): ";
        _DFS_recursive(startNode, visited); // Gọi hàm hỗ trợ đệ quy
        std::cout << std::endl; // Xuống dòng sau khi kết thúc duyệt
    }

private:
    // Hàm hỗ trợ đệ quy cho DFS
    void _DFS_recursive(int currentNode, std::vector<bool>& visited) {
        visited[currentNode] = true; // Đánh dấu đỉnh hiện tại là đã thăm
        std::cout << currentNode << " "; // In đỉnh hiện tại

        // Duyệt qua tất cả các đỉnh kề của đỉnh hiện tại
        for (int i = 1; i <= numVertices; ++i) {
            // Nếu có cạnh giữa currentNode và i, VÀ i chưa được thăm
            if (adjMatrix[currentNode][i] == 1 && !visited[i]) {
                _DFS_recursive(i, visited); // Gọi đệ quy để thăm đỉnh i
            }
        }
    }

public:
    // Tùy chọn: Duyệt đồ thị theo chiều sâu (DFS) - phi đệ quy (sử dụng stack)
    void DFS_iterative(int startNode) {
        // Kiểm tra đỉnh bắt đầu có hợp lệ không
        if (startNode < 1 || startNode > numVertices) {
            std::cout << "Dinh bat dau khong hop le cho DFS lap.\n";
            return;
        }

        std::stack<int> s; // Stack để lưu trữ các đỉnh sẽ được thăm
        std::vector<bool> visited(numVertices + 1, false);

        s.push(startNode);       // Đẩy đỉnh bắt đầu vào stack
        visited[startNode] = true; // Đánh dấu đỉnh bắt đầu là đã thăm ngay khi đẩy vào stack

        std::cout << "Duyet DFS (lap, bat dau tu dinh " << startNode << "): ";
        while (!s.empty()) { // Trong khi stack chưa rỗng
            int currentNode = s.top(); // Lấy đỉnh ở đầu stack
            s.pop();                     // Xóa đỉnh đó khỏi stack
            std::cout << currentNode << " "; // In đỉnh hiện tại

            // Duyệt qua tất cả các đỉnh kề của đỉnh hiện tại
            // Duyệt ngược từ numVertices xuống 1 để có thứ tự đầu ra tương tự như DFS đệ quy
            // (nếu DFS đệ quy cũng duyệt các hàng xóm theo thứ tự tăng dần)
            for (int i = numVertices; i >= 1; --i) {
                // Nếu có cạnh giữa currentNode và i, VÀ i chưa được thăm
                if (adjMatrix[currentNode][i] == 1 && !visited[i]) {
                    s.push(i);         // Đẩy i vào stack
                    visited[i] = true; // Đánh dấu i là đã thăm ngay khi đẩy vào stack
                }
            }
        }
        std::cout << std::endl; // Xuống dòng sau khi kết thúc duyệt
    }
};

// Hàm chính của chương trình
int main() {
    // Đồ thị có 8 đỉnh (được đánh số từ 1 đến 8)
    Graph g(8);

    // Thêm các cạnh dựa trên hình ảnh đã cho
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(1, 5);
    g.addEdge(2, 6);
    g.addEdge(3, 4);
    g.addEdge(3, 8);
    g.addEdge(4, 8);
    g.addEdge(5, 8);
    g.addEdge(6, 7);
    g.addEdge(6, 8); // Cạnh giữa 6 và 8 cũng có mặt

    // In ma trận kề
    g.printAdjMatrix();

    // a) Duyệt đồ thị bằng phương pháp BFS
    std::cout << "\n--- Duyet do thi ---\n";
    g.BFS(1); // Bắt đầu BFS từ đỉnh 1
    g.BFS(4); // Bắt đầu BFS từ đỉnh 4

    // b) Duyệt đồ thị bằng phương pháp DFS (đệ quy)
    g.DFS(1); // Bắt đầu DFS từ đỉnh 1
    g.DFS(4); // Bắt đầu DFS từ đỉnh 4

    // Tùy chọn: Duyệt đồ thị bằng phương pháp DFS (phi đệ quy)
    std::cout << "\n--- Tuy chon: DFS lap ---\n";
    g.DFS_iterative(1); // Bắt đầu DFS phi đệ quy từ đỉnh 1
    g.DFS_iterative(4); // Bắt đầu DFS phi đệ quy từ đỉnh 4

    return 0; // Trả về 0 báo hiệu chương trình kết thúc thành công
}