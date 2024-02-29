#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <filesystem>

class Vector {
public:
    Vector(int size) : size(size), entries(std::make_unique<VectorEntry[]>(size)) {}

    ~Vector() {}

    void readVectorFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error opening vector file: " << filename << std::endl;
            exit(1);
        }

        for (int i = 0; i < size; ++i) {
            file >> entries[i];
        }

        file.close();
    }

    void printVector() const {
        for (int i = 0; i < size; ++i) {
            std::cout << entries[i] << ' ';
        }
        std::cout << std::endl;
    }

    void addAbsolute(const Vector& other, Vector& result) const {
        for (int i = 0; i < size; ++i) {
            result.entries[i] = std::abs(entries[i]) + std::abs(other.entries[i]);
        }
    }

private:
    typedef double VectorEntry;
    std::unique_ptr<VectorEntry[]> entries;
    int size;
    inline VectorEntry get(int i) const {
        return entries[i];
    }
    inline void set(int i, VectorEntry value) {
        entries[i] = value;
    }
};

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[1] << " fuck you " << std::endl;
        return 1;
    }

    std::string filename(argv[1]);
    int N_OPS = std::stoi(argv[2]);
    int N_ENTRIES = std::stoi(argv[3]);

    Vector result(N_ENTRIES);
    std::cout << "From " << filename << ":\n";
    std::cout << N_OPS << " rows with " << N_ENTRIES << " vectors each:\n";

    for (int op = 0; op < N_OPS; ++op) {
        Vector vector1(N_ENTRIES), vector2(N_ENTRIES);

        // Read vectors from files
        vector1.readVectorFromFile(filename + "-" + std::to_string(op) + "-" + std::to_string(N_ENTRIES));
        vector2.readVectorFromFile(filename + "-" + std::to_string(op) + "-" + std::to_string(N_ENTRIES));

        // Add absolute values of vectors
        vector1.addAbsolute(vector2, result);

        // Print result
        result.printVector();
    }

    return 0;
}
