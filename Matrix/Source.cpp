#include <iostream>
#include <ctime>
#include <limits>
using namespace std;

class A
{
public:
    int value;

    A() : value(0) {}
    A(int val) : value(val) {}

    A operator+(const A& other) const 
    {
        return A(value + other.value);
    }

    A operator-(const A& other) const 
    {
        return A(value - other.value);
    }

    A operator*(const A& other) const  
    {
        return A(value * other.value);
    }

    A operator/(const A& other) const
    {
        if (other.value != 0)
        {
            return A(value / other.value);
        }
        else 
        {
            throw runtime_error("Division by zero");
        }
    }

    friend ostream& operator<<(ostream& os, const A& a) 
    {
        os << a.value;
        return os;
    }

    friend istream& operator>>(istream& is, A& a) 
    {
        is >> a.value;
        return is;
    }
};

template <typename T>
class Matrix 
{
private:
    int rows;
    int cols;
    T** data;

    void allocateMemory() 
    {
        data = new T * [rows];
        for (int i = 0; i < rows; ++i)
        {
            data[i] = new T[cols];
        }
    }

    void freeMemory() 
    {
        for (int i = 0; i < rows; ++i) 
        {
            delete[] data[i];
        }
        delete[] data;
    }

public:
    Matrix(int r, int c) : rows(r), cols(c) 
    {
        allocateMemory();
    }

    ~Matrix() 
    {
        freeMemory();
    }

    void fillFromKeyboard() 
    {
        cout << "Enter elements of the matrix:\n";
        for (int i = 0; i < rows; ++i) 
        {
            for (int j = 0; j < cols; ++j)
            {
                cin >> data[i][j];
            }
        }
    }

    void fillRandom()
    {
        srand(static_cast<unsigned int>(time(0)));
        for (int i = 0; i < rows; ++i) 
        {
            for (int j = 0; j < cols; ++j) 
            {
                data[i][j] = T(rand() % 100);
            }
        }
    }

    void display() const 
    {
        for (int i = 0; i < rows; ++i) 
        {
            for (int j = 0; j < cols; ++j) 
            {
                cout << data[i][j] << " ";
            }
        }
    }

    Matrix operator+(const Matrix& other) const 
    {
        if (rows != other.rows || cols != other.cols) 
        {
            throw runtime_error("Matrix dimensions must match for addition");
        }
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) 
        {
            for (int j = 0; j < cols; ++j) 
            {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator-(const Matrix& other) const 
    {
        if (rows != other.rows || cols != other.cols) 
        {
            throw runtime_error("Matrix dimensions must match for subtraction");
        }
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const 
    {
        if (cols != other.rows)
        {
            throw runtime_error("Matrix dimensions must match for multiplication");
        }

        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i) 
        {
            for (int j = 0; j < other.cols; ++j) 
            {
                result.data[i][j] = T();
                for (int k = 0; k < cols; ++k) 
                {
                    result.data[i][j] = result.data[i][j] + data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    Matrix operator/(const T& scalar) const 
    {
        if (scalar == T()) {
            throw runtime_error("Division by zero");
        }
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) 
        {
            for (int j = 0; j < cols; ++j) 
            {
                result.data[i][j] = data[i][j] / scalar;
            }
        }
        return result;
    }

    T findMax() const 
    {
        T maxElement = data[0][0];
        for (int i = 0; i < rows; ++i) 
        {
            for (int j = 0; j < cols; ++j)
            {
                if (data[i][j] > maxElement)
                {
                    maxElement = data[i][j];
                }
            }
        }
        return maxElement;
    }

    T findMin() const 
    {
        T minElement = data[0][0];
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j) 
            {
                if (data[i][j] < minElement)
                {
                    minElement = data[i][j];
                }
            }
        }
        return minElement;
    }
};

int main()
{
    Matrix<A> mat1(1, 2);
    Matrix<A> mat2(3, 4);

    mat1.fillRandom();
    mat2.fillRandom();

    cout << "Matrix 1:\n";
    mat1.display();

    cout << "Matrix 2:\n";
    mat2.display();

    Matrix<A> mat3 = mat1 + mat2;
    cout << "Matrix 1 + Matrix 2:\n";
    mat3.display();

    A maxElement = mat1.findMax();
    A minElement = mat1.findMin();

    cout << "Max element in Matrix 1: " << maxElement << "\n";
    cout << "Min element in Matrix 1: " << minElement << "\n";

    return 0;
}