#include "Matrix.h"

using namespace std;

int main(int argc, char* argv[]) {
    
    Matrix matrixA;
    
    ElementType arrayA1[] = {1, 0, 3, -1};
    vector<ElementType> vectorA1(arrayA1, arrayA1 + 4);
    matrixA.addRow(vectorA1);
    
    ElementType arrayA2[] = {2, 1, 0, 2};
    vector<ElementType> vectorA2(arrayA2, arrayA2 + 4);
    matrixA.addRow(vectorA2);
    
    Matrix matrixB;
    
    ElementType arrayB1[] = {4, 1, 0};
    vector<ElementType> vectorB1(arrayB1, arrayB1 + 3);
    matrixB.addRow(vectorB1);
    
    ElementType arrayB2[] = {-1, 1, 3};
    vector<ElementType> vectorB2(arrayB2, arrayB2 + 3);
    matrixB.addRow(vectorB2);
    
    ElementType arrayB3[] = {2, 0, 1};
    vector<ElementType> vectorB3(arrayB3, arrayB3 + 3);
    matrixB.addRow(vectorB3);
    
    ElementType arrayB4[] = {1, 3, 4};
    vector<ElementType> vectorB4(arrayB4, arrayB4 + 3);
    matrixB.addRow(vectorB4);
    
    Matrix matrixC = matrixA * matrixB;
    
    Matrix matrix;
    
    ElementType array1[] = {1, 0, 1};
    vector<ElementType> vector1(array1, array1 + 3);
    matrix.addRow(vector1);
    
    ElementType array2[] = {2, 1, 0};
    vector<ElementType> vector2(array2, array2 + 3);
    matrix.addRow(vector2);
    
    ElementType array3[] = {-3, 2, -5};
    vector<ElementType> vector3(array3, array3 + 3);
    matrix.addRow(vector3);
    
    Matrix inverseMatrix = matrix.inverseOfSquareMatrix();
    
    return 0;
}