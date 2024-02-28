#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <filesystem>

class Vector {
public:
    Vector(int size) : size(size) {
        data = new double[size];
    }

    ~Vector() {
        delete[] data;
    }

    void readVectorFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error opening vector file: " << filename << std::endl;
            exit(1);
        }

        for (int i = 0; i < size; ++i) {
            file >> data[i];
        }

        file.close();
    }

    void printVector() const {
        for (int i = 0; i < size; ++i) {
            std::cout << data[i] << ' ';
        }
        std::cout << std::endl;
    }

    void addAbsolute(const Vector& other, Vector& result) const {
        for (int i = 0; i < size; ++i) {
            result.data[i] = std::abs(data[i]) + std::abs(other.data[i]);
        }
    }

private:
    double* data;
    int size;
};

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <filename> <N_OPS> <N_ENTRIES>" << std::endl;
        return 1;
    }

    std::string filename(argv[1]);
    int N_OPS = std::stoi(argv[2]);
    int N_ENTRIES = std::stoi(argv[3]);

    Vector result(N_ENTRIES);
    std::cout<<"From "<<filename<<":\n";
    std::cout<<N_OPS<<" rows with "<<N_ENTRIES<<" vectors each:\n";
    
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
