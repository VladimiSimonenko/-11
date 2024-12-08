#include <iostream>
#include <vector>
using namespace std;

class DiagonalMatrix {
private:
    vector<int> diag;
    int size;

public:
    DiagonalMatrix(int n) : size(n) {
        diag.resize(n);
    }

    void setElement(int i, int val) {
        if (i < size && i >= 0) {
            diag[i] = val;
        }
    }

    int getElement(int i) const {
        if (i < size && i >= 0) {
            return diag[i];
        }
        else {
            return 0; // вне диагонального элемента всегда 0
        }
    }

    int getSize() const {
        return size;
    }

    DiagonalMatrix operator+(const DiagonalMatrix& other) {
        DiagonalMatrix result(size);
        for (int i = 0; i < size; ++i) {
            result.setElement(i, this->getElement(i) + other.getElement(i));
        }
        return result;
    }

    DiagonalMatrix operator-(const DiagonalMatrix& other) {
        DiagonalMatrix result(size);
        for (int i = 0; i < size; ++i) {
            result.setElement(i, this->getElement(i) - other.getElement(i));
        }
        return result;
    }

    DiagonalMatrix operator*(const DiagonalMatrix& other) {
        DiagonalMatrix result(size);
        for (int i = 0; i < size; ++i) {
            result.setElement(i, this->getElement(i) * other.getElement(i));
        }
        return result;
    }

    void print() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (i == j) {
                    cout << getElement(i) << " ";
                }
                else {
                    cout << 0 << " ";
                }
            }
            cout << endl;
        }
    }
};

int main() {
    int size;
    cout << "Введите размер диагональных матриц: ";
    cin >> size;

    DiagonalMatrix matrix1(size);
    DiagonalMatrix matrix2(size);

    cout << "Введите элементы первой диагональной матрицы:\n";
    for (int i = 0; i < size; ++i) {
        int val;
        cin >> val;
        matrix1.setElement(i, val);
    }

    cout << "Введите элементы второй диагональной матрицы:\n";
    for (int i = 0; i < size; ++i) {
        int val;
        cin >> val;
        matrix2.setElement(i, val);
    }

    DiagonalMatrix sum = matrix1 + matrix2;
    DiagonalMatrix diff = matrix1 - matrix2;
    DiagonalMatrix prod = matrix1 * matrix2;

    cout << "Сумма матриц:\n";
    sum.print();
    cout << "Разность матриц:\n";
    diff.print();
    cout << "Произведение матриц:\n";
    prod.print();

    return 0;
}
