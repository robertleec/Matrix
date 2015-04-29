#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <vector>
#include "assert.h"

namespace std {
    
    typedef unsigned long SizeType;
    typedef double MultipleNumberType;
    typedef unsigned long RankValueType;
    typedef double TraceValueType;
    
    template<typename ElementType>
    class Matrix {
        
    public:
        Matrix() {
            
        }
        
        Matrix(const Matrix& rhs):data(rhs.data) {
            
        }
        
        Matrix& operator=(const Matrix& rhs) {
            Matrix temp(rhs);
            this->swap(temp);
            return *this;
        }
        
        Matrix(SizeType rowNumber, SizeType columNumber) {
            if (rowNumber == 0 || columNumber == 0) {
                return;
            }
            
            for (size_t index = 0; index < rowNumber; ++index) {
                vector<ElementType> row(columNumber);
                this->data.push_back(row);
            }
        }
        
        ~Matrix() {
            
        }
        
        void swap(Matrix& other) {
            using std::swap;
            swap(this->data, other.data);
        }
        
        bool isEmpty() const {
            
            if (this->getRowNumber() > 0 && this->getColumNumber() > 0) {
                return false;
            }
            
            return true;
        }
        
        bool isSquareMatrix() const {
            
            if (this->getRowNumber() == this->getColumNumber()) {
                return true;
            }
            
            return false;
        }
        
        inline const SizeType getRowNumber() const {
            return (this->data).size();
        }
        
        inline const SizeType getColumNumber() const {
            
            if (this->getRowNumber() > 0) {
                
                const vector<ElementType>& firstColum = (this->data).at(0);
                
                return firstColum.size();
            }
            
            return 0;
        }
        
        inline const vector<ElementType> getRow(SizeType rowIndex) const {
            
            assert(this->getRowNumber() > rowIndex);
            
            return vector<ElementType>(this->data.at(rowIndex));
        }
        
        inline const vector<ElementType> getColum(SizeType columIndex) const {
            
            assert(this->getColumNumber() > columIndex);
            
            vector<ElementType> colum;
            
            for (size_t rowIndex = 0; rowIndex < this->getRowNumber(); ++rowIndex) {
                colum.push_back(this->data.at(rowIndex).at(columIndex));
            }
            
            return vector<ElementType>(colum);
        }
        
        void addRow(const vector<ElementType>& rowData) {
            
            if (this->getRowNumber() == 0) {
                
                this->data.push_back(rowData);
                
            } else {
                
                assert(rowData.size() == this->getColumNumber());
                this->data.push_back(rowData);
            }
        }
        
        void deleteRow(SizeType rowIndex) {
            assert(this->getRowNumber() > rowIndex);
            
            typename vector< vector<ElementType> >::iterator deleteIterator = this->data.begin() + rowIndex;
            
            this->data.erase(deleteIterator);
        }
        
        void addColum(const vector<ElementType>& columData) {
            
            if (this->getRowNumber() == 0) {
                for (size_t index = 0; index < columData.size(); ++index) {
                    vector<ElementType> row(1, columData.at(index));
                    this->data.push_back(row);
                }
            } else {
                
                assert(columData.size() == this->getRowNumber());
                
                for (size_t index = 0; index < columData.size(); ++index) {
                    this->data.at(index).push_back(columData.at(index));
                }
            }
        }
        
        void deleteColum(SizeType columIndex) {
            
            assert(this->getColumNumber() > columIndex);
            
            if (this->getColumNumber() == 1 && columIndex == 0) {
                this->data.clear();
            } else {
                
                for (size_t index = 0; index < this->getRowNumber(); ++index) {
                    vector<ElementType>& row = this->data.at(index);
                    typename vector<ElementType>::iterator deleteIterator = row.begin() + columIndex;
                    row.erase(deleteIterator);
                }
            }
        }
        
        friend inline const Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
            
            assert(lhs.isEmpty() == false && rhs.isEmpty() == false);
            assert(lhs.getRowNumber() == rhs.getRowNumber() && lhs.getColumNumber() == rhs.getColumNumber());
            
            Matrix result(lhs.getRowNumber(), lhs.getColumNumber());
            
            for (SizeType rowIndex = 0; rowIndex < lhs.getRowNumber(); ++rowIndex) {
                for (SizeType columIndex = 0; columIndex < lhs.getColumNumber(); ++columIndex) {
                    result.data.at(rowIndex).at(columIndex) = lhs.data.at(rowIndex).at(columIndex) + rhs.data.at(rowIndex).at(columIndex);
                }
            }
            
            return Matrix(result);
        }
        
        friend inline const Matrix operator*(MultipleNumberType multipleNumber, const Matrix& rhs) {
            
            Matrix result(rhs);
            
            if (rhs.isEmpty() == false) {
                
                for (SizeType rowIndex = 0; rowIndex < rhs.getRowNumber(); ++rowIndex) {
                    for (SizeType columIndex = 0; columIndex < rhs.getColumNumber(); ++columIndex) {
                        result.data.at(rowIndex).at(columIndex) *= multipleNumber;
                    }
                }
                
            }
            
            return Matrix(result);
        }
        
        friend inline const Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
            
            assert(lhs.isEmpty() == false && rhs.isEmpty() == false);
            assert(lhs.getColumNumber() == rhs.getRowNumber());
            
            Matrix result(lhs.getRowNumber(), rhs.getColumNumber());
            
            for (SizeType rowIndex = 0; rowIndex < result.getRowNumber(); ++rowIndex) {
                for (SizeType columIndex = 0; columIndex < result.getColumNumber(); ++columIndex) {
                    
                    ElementType multipleElement = 0;
                    
                    for (SizeType multipleElementIndex = 0; multipleElementIndex < lhs.getColumNumber(); ++multipleElementIndex) {
                        
                        multipleElement += lhs.data.at(rowIndex).at(multipleElementIndex) * rhs.data.at(multipleElementIndex).at(columIndex);
                    }
                    
                    result.data.at(rowIndex).at(columIndex) = multipleElement;
                }
            }
            
            return Matrix(result);
        }
        
        inline const Matrix transposeMatrix() {
            
            Matrix result(this->getColumNumber(), this->getRowNumber());
            
            if (this->isEmpty() == false) {
                
                for (SizeType rowIndex = 0; rowIndex < result.getRowNumber(); ++rowIndex) {
                    for (SizeType columIndex = 0; columIndex < result.getColumNumber(); ++columIndex) {
                        result.data.at(rowIndex).at(columIndex) = this->data.at(columIndex).at(rowIndex);
                    }
                }
            }
            
            return Matrix(result);
        }
        
        void switchTwoRow(SizeType rowIndex0, SizeType rowIndex1) {
            
            assert(this->getRowNumber() > rowIndex0 && this->getRowNumber() > rowIndex1);
            
            using std::swap;
            swap(this->data.at(rowIndex0), this->data.at(rowIndex1));
        }
        
        void multipleRow(MultipleNumberType multipleNumber, SizeType rowIndex) {
            
            assert(this->getRowNumber() > rowIndex);
            
            vector<ElementType>& row = this->data.at(rowIndex);
            
            for (size_t index = 0; index < row.size(); ++index) {
                row.at(index) *= multipleNumber;
            }
        }
        
        void addOneMultipleRowToAnotherRow(SizeType rowIndex0, MultipleNumberType multipleNumber, SizeType rowIndex1) {
            
            assert(this->getRowNumber() > rowIndex0 && this->getRowNumber() > rowIndex1);
            
            const vector<ElementType>& row0 = this->data.at(rowIndex0);
            vector<ElementType>& row1 = this->data.at(rowIndex1);
            
            for (size_t index = 0; index < row0.size(); ++index) {
                row1.at(index) += row0.at(index) * multipleNumber;
            }
        }
        
        void switchTwoColum(SizeType columIndex0, SizeType columIndex1) {
            
            assert(this->getColumNumber() > columIndex0 && this->getColumNumber() > columIndex1);
            
            using std::swap;
            
            for (size_t index = 0; index < this->getRowNumber(); ++index) {
                
                vector<ElementType>& row = this->data.at(index);
                swap(row.at(columIndex0), row.at(columIndex1));
            }
        }
        
        void multipleColum(MultipleNumberType multipleNumber, SizeType columIndex) {
            
            assert(this->getColumNumber() > columIndex);
            
            for (size_t index = 0; index < this->getRowNumber(); ++index) {
                
                vector<ElementType>& row = this->data.at(index);
                row.at(columIndex) *= multipleNumber;
            }
        }
        
        void addOneMultipleColumToAnotherColum(SizeType columIndex0, MultipleNumberType multipleNumber, SizeType columIndex1) {
            
            assert(this->getColumNumber() > columIndex0 && this->getColumNumber() > columIndex1);
            
            for (size_t index = 0; index < this->getRowNumber(); ++index) {
                
                vector<ElementType>& row = this->data.at(index);
                
                row.at(columIndex1) += row.at(columIndex0) * multipleNumber;
            }
        }
        
        inline const Matrix inverseOfSquareMatrix() {
            
            assert(this->isEmpty() == false);
            assert(this->isSquareMatrix() == true);
 
            Matrix matrixCopy(*this);
            Matrix result = Matrix::unitaryMatrix(this->getRowNumber());
            
            for (size_t rowIndex = 0; rowIndex < matrixCopy.getRowNumber(); ++rowIndex) {
                
                SizeType firstRowNonZeroInColum = matrixCopy.firstRowContainsNonZeroElementColumUpRow(rowIndex, rowIndex);
                
                //Matrix is singular matrix because its rank isn't equals its order.
                if (firstRowNonZeroInColum == matrixCopy.getRowNumber()) {
                    result = Matrix::emptyMatrix();
                    break;
                }
                
                result.switchTwoRow(rowIndex, firstRowNonZeroInColum);
                matrixCopy.switchTwoRow(rowIndex, firstRowNonZeroInColum);
                
                result.multipleRow(1.0 / matrixCopy.data.at(rowIndex).at(rowIndex), rowIndex);
                matrixCopy.multipleRow(1.0 / matrixCopy.data.at(rowIndex).at(rowIndex), rowIndex);
                
                for (size_t eliminationIndex = 0; eliminationIndex < matrixCopy.getRowNumber(); ++eliminationIndex) {
                    
                    if (eliminationIndex == rowIndex) {
                        continue;
                    }
                    
                    result.addOneMultipleRowToAnotherRow(rowIndex, (-1) * matrixCopy.data.at(eliminationIndex).at(rowIndex), eliminationIndex);
                    matrixCopy.addOneMultipleRowToAnotherRow(rowIndex, (-1) * matrixCopy.data.at(eliminationIndex).at(rowIndex), eliminationIndex);
                }
            }
            
            return Matrix(result);
        }
        
        RankValueType getRank() {
            
            Matrix matrixCopy(*this);
            
            RankValueType rank = 0;
            
            for (size_t rowIndex = 0; rowIndex < matrixCopy.getRowNumber(); ++rowIndex) {
                
                SizeType firstColumNonZero = matrixCopy.firstColumNonZeroElementUpRow(rowIndex);
                
                //Not found non-zero element up row index.
                if (firstColumNonZero == matrixCopy.getColumNumber()) {
                    break;
                }
                
                ++rank;
                
                SizeType firstRowNonZeroInColum = matrixCopy.firstRowContainsNonZeroElementColumUpRow(firstColumNonZero, rowIndex);
                
                matrixCopy.switchTwoRow(rowIndex, firstRowNonZeroInColum);
                
                for (size_t eliminationIndex = rowIndex + 1; eliminationIndex < matrixCopy.getRowNumber(); ++eliminationIndex) {
                    
                    matrixCopy.addOneMultipleRowToAnotherRow(rowIndex, (-1) * (matrixCopy.data.at(eliminationIndex).at(firstColumNonZero) / matrixCopy.data.at(rowIndex).at(firstColumNonZero)), eliminationIndex);
                }
            }
            
            return rank;
        }
        
        TraceValueType getTrace() {
            
            assert(this->isSquareMatrix() == true);
            
            TraceValueType trace = 0;
            
            for (size_t rowIndex = 0; rowIndex < this->getRowNumber(); ++rowIndex) {
                trace += this->data.at(rowIndex).at(rowIndex);
            }
            
            return trace;
        }
        
        static inline const Matrix unitaryMatrix(SizeType size) {
            
            Matrix result(size, size);
            
            for (SizeType index = 0; index < size; ++index) {
                result.data.at(index).at(index) = 1;
            }
            
            return Matrix(result);
        }
        
        static inline const Matrix emptyMatrix() {
            
            return Matrix();
        }
        
    private:
        vector< vector<ElementType> > data;
        
        SizeType firstRowContainsNonZeroElementColumUpRow(SizeType columIndex, SizeType upRowIndex) {
            
            assert(this->getColumNumber() > columIndex);
            assert(this->getRowNumber() > upRowIndex);
            
            SizeType firstRowIndex = this->getRowNumber();
            
            for (size_t rowIndex = upRowIndex; rowIndex < this->getRowNumber(); ++rowIndex) {
                
                if (this->data.at(rowIndex).at(columIndex) != 0) {
                    firstRowIndex = rowIndex;
                    break;
                }
            }
            
            return firstRowIndex;
        }
        
        SizeType firstColumNonZeroElementUpRow(SizeType upRowIndex) {
            
            assert(this->getRowNumber() > upRowIndex);
            
            SizeType firstColumIndex = this->getColumNumber();
            
            for (size_t rowIndex = upRowIndex; rowIndex < this->getRowNumber(); ++rowIndex) {
                
                vector<ElementType>& row = this->data.at(rowIndex);
                
                for (size_t columIndex = 0; columIndex < row.size(); ++columIndex) {
                    
                    if (row.at(columIndex) != 0 && firstColumIndex > columIndex) {
                        firstColumIndex = columIndex;
                        break;
                    }
                }
            }
            
            return firstColumIndex;
        }
    };
    
}

namespace std {
    template<typename ElementType>
    void swap(std::Matrix<ElementType>& a, std::Matrix<ElementType>& b) {
        a.swap(b);
    }
}

#endif