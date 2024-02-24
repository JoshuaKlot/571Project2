#include <iostream>

class Vector {
public:
    Vector(int size) : size(size) {
        data = new double[size];
    }

    ~Vector() {
        delete[] data;
    }

    void readVector() {
        for (int i = 0; i < size; ++i) {
            std::cin >> data[i];
        }
    }

    void printVector() const {
        for (int i = 0; i < size; ++i) {
            std::cout << data[i] << ' ';
        }
        std::cout << std::endl;
    }

    void add(const Vector& other, Vector& result) const {
        for (int i = 0; i < size; ++i) {
            result.data[i] = data[i] + other.data[i];
        }
    }

private:
    double* data;
    int size;
};

int main() {
    int N_OPS, N_ENTRIES;
    std::cin >> N_OPS >> N_ENTRIES;

    for (int op = 0; op < N_OPS; ++op) {
        Vector vector1(N_ENTRIES), vector2(N_ENTRIES), result(N_ENTRIES);

        // Read vectors
        vector1.readVector();
        vector2.readVector();

        // Add vectors
        vector1.add(vector2, result);

        // Print result
        result.printVector();
    }

    return 0;
}
