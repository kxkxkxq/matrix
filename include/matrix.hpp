#pragma once

#include <algorithm>
#include <cstddef>
#include <cmath>
#include <utility>

namespace matrices
{
    template <typename T> class SquareMatrix
    {
        template <typename U> class Buffer_ final
        {
            size_t bufSize_; 
            U* pBuf_;
            
            void swap(Buffer_& rhs) noexcept;

        public :

            Buffer_(const size_t size = 0) : bufSize_(size), pBuf_(new U[size]()) {};
            template <typename Iter>
            Buffer_(const size_t size, const Iter begin, const Iter end);
            Buffer_(const size_t size, U val); 
            
            Buffer_(const Buffer_& rhs);
            Buffer_(Buffer_&& rhs) noexcept : bufSize_(std::move(rhs.bufSize_)), 
                                              pBuf_(std::exchange(rhs.pBuf_, nullptr)) {};

            Buffer_& operator=(const Buffer_& rhs);
            Buffer_& operator=(Buffer_&& rhs) noexcept;
            
            U& operator[](const int indx) {return pBuf_[indx];};
            const U& operator[](const int indx) const {return pBuf_[indx];};

            ~Buffer_() {delete[] pBuf_;};

            const size_t size() const noexcept {return bufSize_;};
            
            U& front() {return pBuf_[0];};
            const U& front() const {return pBuf_[0];};

            U& back() {return pBuf_[bufSize_ - 1];};
            const U& back() const {return pBuf_[bufSize_ - 1];};
        };

        Buffer_<Buffer_<T>> contSqMatrix_;
        size_t matrixSize_; 
        double det_ = std::nan("");
        
        const double calculate_determinant();
        const double get_determinant() {return det_;};

        void swap_rows(Buffer_<T>& row1, Buffer_<T>& row2);

    public :

    template <typename Iter> 
    SquareMatrix(const size_t size, const Iter begin, const Iter end);
    
    SquareMatrix(const size_t size, T val = T{}) : contSqMatrix_(size, Buffer_<T>{size, val}), 
                                                   matrixSize_(size) {};

    SquareMatrix(const SquareMatrix& rhs) : contSqMatrix_(rhs.contSqMatrix_), 
                                            matrixSize_(rhs.matrixSize_),
                                            det_(rhs.det_) {};

    SquareMatrix(SquareMatrix&& rhs) noexcept : contSqMatrix_(std::move(rhs.contSqMatrix_)),
                                                matrixSize_(std::move(rhs.matrixSize_)),
                                                det_(std::move(rhs.det_)) {};

    SquareMatrix& operator=(const SquareMatrix& rhs);
    SquareMatrix& operator=(SquareMatrix&& rhs) noexcept;
    
    Buffer_<T>& operator[](const int indx) {return contSqMatrix_[indx];};

    ~SquareMatrix() = default; 
    
    const size_t size() const noexcept {return matrixSize_;};
    const double determinant();
    };

//-------------------------------------------------------------------------------------------------
//      SQUAREMATRIX

    template <typename T>
    template <typename Iter> 
    SquareMatrix<T>::SquareMatrix(const size_t size, const Iter begin, const Iter end) 
        : SquareMatrix<T>::SquareMatrix(size)
    {
        auto i = begin, e = end; 
        for(size_t rowIndx = 0; i != e && rowIndx < size; ++rowIndx)
            for(size_t colIndx = 0; colIndx < size; ++colIndx)
                contSqMatrix_[rowIndx][colIndx] = *i++;
    }

    template <typename T>
    SquareMatrix<T>&
    SquareMatrix<T>::operator=(const SquareMatrix<T>& rhs)
    {
        
    } 

    template <typename T>
    SquareMatrix<T>&
    SquareMatrix<T>::operator=(SquareMatrix<T>&& rhs) noexcept
    {
        contSqMatrix_ = std::move(rhs.contSqMatrix_);
        matrixSize_ = std::move(rhs.matrixSize_);
        det_ = std::move(rhs.det_);
        return *this;
    }

    template <typename T>
    const double 
    SquareMatrix<T>::determinant()
    {
        return (std::isnan(det_)) ? calculate_determinant() : get_determinant(); 
    }

    template <typename T>
    void 
    SquareMatrix<T>::swap_rows(Buffer_<T>& row1, Buffer_<T>& row2)
    {
        assert(row1.size() == row2.size());
        for(size_t i = 0; i < row1.size(); ++i)
        {
            T tmp = row1[i];
            row1[i] = row2[i];
            row2[i] = tmp;
        }
    }

    template <typename T>
    const double 
    SquareMatrix<T>::calculate_determinant()
    {
        if(matrixSize_ == 0)
            return contSqMatrix_[0][0];

        SquareMatrix tmp{contSqMatrix_};

        if(tmp[0][0] == 0)
        {
            size_t nonZeroElemIndx = 1;
            while((nonZeroElemIndx < matrixSize_) && (tmp[nonZeroElemIndx][0] != 0))
                ++nonZeroElemIndx;
            swap_rows(tmp[0], tmp[1]);
        }
        assert(tmp[0][0] != 0);

        for(size_t colIndx = 0, rowIndx = 0; colIndx < matrixSize_; ++colIndx, ++colIndx)
        {
            assert(colIndx == rowIndx);
            for(size_t nextRowIndx = colIndx + 1; nextRowIndx < matrixSize_; ++nextRowIndx)
            {
                multiply_row_by_number();
                multiply_row_by_number();
                subtract_rows();
            }
        }        
    }

//-------------------------------------------------------------------------------------------------
//      SQUAREMATRIX::BUFFER_ 

    template <typename T> 
    template <typename U> 
    SquareMatrix<T>::Buffer_<U>::Buffer_(const SquareMatrix<T>::Buffer_<U>& rhs)
    {
        pBuf_ = new U[rhs.bufSize_];
        try
        {
            for(size_t i = 0; i < rhs.bufSize_; ++i)
                pBuf_[i] = rhs.pBuf_[i];
        }
        catch(...)
        {
            delete [] pBuf_;
            throw;
        }

        bufSize_ = rhs.bufSize_; 
    }

    template <typename T>
    template <typename U>
    template <typename Iter>
    SquareMatrix<T>::Buffer_<U>::Buffer_(const size_t size, const Iter begin, const Iter end)
    {
        pBuf_ = new U[size];
        try
        {
            for(auto i = begin, e = end, j = size_t{0}; i != e; ++i, ++j)
                pBuf_[j] = *i;
        }
        catch(...)
        {
            delete [] pBuf_;
            throw;
        }
    
        bufSize_ = size; 
    }

    template <typename T>
    template <typename U>
    SquareMatrix<T>::Buffer_<U>::Buffer_(const size_t size, U val)
    {
        pBuf_ = new U[size];
        try
        {
            std::fill_n(pBuf_, size, val);  
        }
            catch(...)
        {
            delete [] pBuf_;
            throw;
        }
    
        bufSize_ = size; 
    }

    template <typename T> 
    template <typename U> 
    SquareMatrix<T>::Buffer_<U>& 
    SquareMatrix<T>::Buffer_<U>::operator=(SquareMatrix<T>::Buffer_<U>&& rhs) noexcept
    {
        delete [] pBuf_;
        bufSize_ = std::move(rhs.bufSize_);
        pBuf_ = std::exchange(rhs.pBuf_, nullptr);
        return *this;
    }    

    template <typename T> 
    template <typename U> 
    void 
    SquareMatrix<T>::Buffer_<U>::swap(SquareMatrix<T>::Buffer_<U>& rhs) noexcept
    {
        std::swap(bufSize_, rhs.bufSize_);
        std::swap(pBuf_, rhs.pBuf_);
    }

    template <typename T> 
    template <typename U> 
    SquareMatrix<T>::Buffer_<U>& 
    SquareMatrix<T>::Buffer_<U>::operator=(const SquareMatrix<T>::Buffer_<U>& rhs)
    {
        Buffer_<U> tmp{rhs};
        swap(tmp);
        return *this;
    }
}   //  namespace matrices