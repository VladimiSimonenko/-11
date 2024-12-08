#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

std::vector<int> readDataFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }

    int count;
    file >> count;  // Читаем количество элементов

    std::vector<int> data(count);
    for (int i = 0; i < count; ++i) {
        file >> data[i];  // Читаем сами данные
    }

    file.close();
    return data;
}

std::vector<int> sumVectors(const std::vector<int>& vec1, const std::vector<int>& vec2) {
    size_t size = std::min(vec1.size(), vec2.size());
    std::vector<int> result(size);
    for (size_t i = 0; i < size; ++i) {
        result[i] = vec1[i] + vec2[i];  // Складываем соответствующие элементы
    }
    return result;
}

std::vector<int> subtractVectors(const std::vector<int>& vec1, const std::vector<int>& vec2) {
    size_t size = std::min(vec1.size(), vec2.size());
    std::vector<int> result(size);
    for (size_t i = 0; i < size; ++i) {
        result[i] = vec1[i] - vec2[i];  // Вычитаем соответствующие элементы
    }
    return result;
}

int scalarProduct(const std::vector<int>& vec1, const std::vector<int>& vec2) {
    size_t size = std::min(vec1.size(), vec2.size());
    int scalar = 0;
    for (size_t i = 0; i < size; ++i) {
        scalar += vec1[i] * vec2[i];  // Скалярное произведение
    }
    return scalar;
}

void printVector(const std::vector<int>& vec) {
    for (int value : vec) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

int main() {
    system("chcp 1251");  // Установка кодировки для русских символов
    system("cls");        // Очистка экрана
    try {
        std::vector<int> data1 = readDataFromFile("file1.txt");
        std::vector<int> data2 = readDataFromFile("file2.txt");

        std::vector<int> sum = sumVectors(data1, data2);
        std::vector<int> difference = subtractVectors(data1, data2);
        int scalar = scalarProduct(data1, data2);

        std::cout << "Сумма векторов: ";
        printVector(sum);
        std::cout << "Разность векторов: ";
        printVector(difference);
        std::cout << "Скалярное произведение: ";
        std::cout << scalar << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}