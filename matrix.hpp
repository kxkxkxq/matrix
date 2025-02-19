#pragma once
#include <cstddef>

namespace matrices
{
    template <typename T> class SquareMatrix
    {
        template <typename U> class Buffer_
        {
            U* pBuf_;
            const size_t bufSize_; 
            
            void swap(Buffer_& rhs) noexcept;

        public :

            Buffer_(const size_t size = 0) : pBuf_(new U[size]), bufSize_(size) {};
            Buffer_(const size_t size, U val);
            Buffer_(const size_t size, U& val);
            
            Buffer_(const Buffer_& rhs);
            Buffer_(Buffer_&& rhs);

            Buffer_& operator=(const Buffer_& rhs);
            Buffer_& operator=(Buffer_&& rhs);

            ~Buffer_() {delete[] pBuf_;};

            const size_t size() const noexcept {return bufSize_;};
            
            U& front() {return pBuf_[0];};
            const U& front() const {return pBuf_[0];};

            U& back() {return pBuf_[bufSize_ - 1];};
            const U& back() const {return pBuf_[bufSize_ - 1];};
        
            U& operator[](const int indx) {return pBuf_[indx];};
            const U& operator[](const int indx) const {return pBuf_[indx];};

        };

        Buffer_<Buffer<T>> contSqMatrix_;
        const size_t matrixSize_; 

    public :

        const size_t size() const noexcept {return matrixSize_;};

        template <typename Iter> 
        SquareMatrix( const size_t size, const Iter begin, const Iter end);
        
        SquareMatrix(const size_t size, T val = T{});

        const long determinant();


        






    };


















//  MATRIX::BUFFER_ 

    template <typename T> 
    template <typename U> 
    SquareMatrix<T>::Buffer_<U>::Buffer_(const SquareMatrix<T>::Buffer_<U>& rhs)
    {
        pBuf_ = new(U[rhs.bufSize_]);
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
    SquareMatrix<T>::Buffer_<U>::Buffer_(SquareMatrix<T>::Buffer_<U>&& rhs)
    {



    }

    template <typename T> 
    template <typename U> 
    void 
    SquareMatrix<T>::Buffer_<U>::swap(SquareMatrix<T>::Buffer_<U>& rhs) noexcept
    {
        std::swap(pBuf_, rhs.pBuf_);
        std::swap(bufSize_, rhs.bufSize_);
    }

    template <typename T> 
    template <typename U> 
    SquareMatrix<T>::Buffer_<U>& 
    SquareMatrix<T>::Buffer_<U>::operator=(const SquareMatrix<T>::Buffer_<U>& rhs)
    {
        Buffer<U> tmp{rhs};
        swap(tmp);
    }





















}   //  namespace matrices