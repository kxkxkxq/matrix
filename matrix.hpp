#pragma once
#include <cstddef>
#include <utility>

namespace matrices
{
    template <typename T> class SquareMatrix
    {
        template <typename U> class Buffer_
        {
            size_t bufSize_; 
            U* pBuf_;
            
            void swap(Buffer_& rhs) noexcept;

        public :

            Buffer_(const size_t size) : bufSize_(size), pBuf_(new U[size]) {};
            Buffer_(const size_t size, U val = U{}) : bufSize_(size), pBuf_(new U[size](val)) {};
            template <typename Iter>
            Buffer_(const size_t size, const Iter begin, const Iter end);
            
            Buffer_(const Buffer_& rhs);
            Buffer_(Buffer_&& rhs) noexcept : bufSize_(std::move(rhs.bufSize_)), 
                                              pBuf_(std::exchange(rhs.pBuf_, nullptr)) {};

            Buffer_& operator=(const Buffer_& rhs);
            Buffer_& operator=(Buffer_&& rhs) noexcept;

            ~Buffer_() {delete[] pBuf_;};

            const size_t size() const noexcept {return bufSize_;};
            
            U& front() {return pBuf_[0];};
            const U& front() const {return pBuf_[0];};

            U& back() {return pBuf_[bufSize_ - 1];};
            const U& back() const {return pBuf_[bufSize_ - 1];};
        
            U& operator[](const int indx) {return pBuf_[indx];};
            const U& operator[](const int indx) const {return pBuf_[indx];};

        };

        Buffer_<Buffer_<T>> contSqMatrix_;
        const size_t matrixSize_; 

    public :

        const size_t size() const noexcept {return matrixSize_;};

        SquareMatrix(const size_t size, T val = T{});
        template <typename Iter> 
        SquareMatrix(const size_t size, const Iter begin, const Iter end);
        
        const long determinant();
    };

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

//      SQUAREMATRIX










}   //  namespace matrices