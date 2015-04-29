#include "Matrix.h"

using namespace std;

int main(int argc, char* argv[]) {
    
    Matrix<double> matrixA;
    
    double arrayA1[] = {1, 0, 3, -1};
    vector<double> vectorA1(arrayA1, arrayA1 + 4);
    matrixA.addRow(vectorA1);
    
    double arrayA2[] = {2, 1, 0, 2};
    vector<double> vectorA2(arrayA2, arrayA2 + 4);
    matrixA.addRow(vectorA2);
    
    Matrix<double> matrixB;
    
    double arrayB1[] = {4, 1, 0};
    vector<double> vectorB1(arrayB1, arrayB1 + 3);
    matrixB.addRow(vectorB1);
    
    double arrayB2[] = {-1, 1, 3};
    vector<double> vectorB2(arrayB2, arrayB2 + 3);
    matrixB.addRow(vectorB2);
    
    double arrayB3[] = {2, 0, 1};
    vector<double> vectorB3(arrayB3, arrayB3 + 3);
    matrixB.addRow(vectorB3);
    
    double arrayB4[] = {1, 3, 4};
    vector<double> vectorB4(arrayB4, arrayB4 + 3);
    matrixB.addRow(vectorB4);
    
    Matrix<double> matrixC = matrixA * matrixB;
    
    Matrix<double> matrix;
    
    double array1[] = {1, 0, 1};
    vector<double> vector1(array1, array1 + 3);
    matrix.addRow(vector1);
    
    double array2[] = {2, 1, 0};
    vector<double> vector2(array2, array2 + 3);
    matrix.addRow(vector2);
    
    double array3[] = {-3, 2, -5};
    vector<double> vector3(array3, array3 + 3);
    matrix.addRow(vector3);
    
    Matrix<double> inverseMatrix = matrix.inverseOfSquareMatrix();
    
    return 0;
}