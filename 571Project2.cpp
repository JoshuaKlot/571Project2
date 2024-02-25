#include <iostream>
#include <fstream>

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
    // Read N_OPS from file
    std::ifstream opsFile("N_OPS");
    if (!opsFile) {
        std::cerr << "Error opening N_OPS file" << std::endl;
        return 1;
    }
    int N_OPS;
    opsFile >> N_OPS;
    opsFile.close();

    // Read N_ENTRIES from file
    std::ifstream entriesFile("N_ENTRIES");
    if (!entriesFile) {
        std::cerr << "Error opening N_ENTRIES file" << std::endl;
        return 1;
    }
    int N_ENTRIES;
    entriesFile >> N_ENTRIES;
    entriesFile.close();

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