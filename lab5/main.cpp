#include <iostream>
#include <stdexcept>

template <typename T>
class Matrix {
private:
    T** data;
    int rows, cols;

    bool is_valid_index(int i, int j) { return (i < rows && j < cols); }

public:
    Matrix(int rows, int cols) : rows(rows), cols(cols) {
        data = new T*[rows];
        for (int i = 0; i < rows; i++) 
            data[i] = new T[cols]();
    }

    Matrix(const Matrix<T>& m) : rows(m.rows), cols(m.cols) {
        data = new T*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new T[cols];
            for (int j = 0; j < cols; j++) {
                data[i][j] = m.data[i][j];
            }
        }
    }

    ~Matrix() {
        for (int i = 0; i < rows; i++) 
            delete[] data[i];
        delete[] data;
    }

    int getRows() { return rows; }
    int getCols() { return cols; }

    void resize(int new_rows, int new_cols) { 
        T** new_data = new T*[new_rows];
        for (int i = 0; i < new_rows; i++) {
            new_data[i] = new T[new_cols];
            for (int j = 0; j < new_cols; j++){
                if (i < rows && j < cols)
                    new_data[i][j] = data[i][j];
                else 
                    new_data[i][j] = T();
            }
        }

        for (int i = 0; i < rows; i++) 
            delete[] data[i];
        delete[] data;

        data = new_data;
        rows = new_rows;
        cols = new_cols;
    }

    void setElem(int i, int j, const T& value) {
        if (is_valid_index(i, j)) data[i][j] = value;
    }

    T& getElem(int i, int j) {
        if (!is_valid_index(i, j)) throw std::out_of_range("Invalid index");
        return data[i][j];
    }

    Matrix<T> transpose() {
        Matrix<T> newMatrix(cols, rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                newMatrix.data[j][i] = data[i][j];
            }
        }
        return newMatrix;
    }

    void print() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    Matrix<int> mat(3, 2);

    for (int i = 0; i < mat.getRows(); i++) {
        for (int j = 0; j < mat.getCols(); j++) {
            int val = i * 10 + j;
            mat.setElem(i, j, val);
        }
    }

    std::cout << "Original matrix:" << std::endl;
    mat.print();

    Matrix<int> transposed = mat.transpose();
    std::cout << "Transposed matrix:" << std::endl;
    transposed.print();

    return 0;
}