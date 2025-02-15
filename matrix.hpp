#pragma once

namespace matrices
{
    template <typename T> class Matrix
    {
        class Row_
        {
            T* pRow_;
            const size_t rowLength_; 
            
        public :

            Row_(const size_t rl) : pRow_(new T[rl]), rowLength_(rl) {};
            
            Row_(const Row_ &rhs);
            Row_(const Row_ &&rhs);

            Row_& operator=(const Row_& rhs);
            Row_& operator=(Row_& rhs);

            ~Row_() {delete[] pRow_;};

            const size_t size() const noexcept {return rowLength_;};
            
            T& front() {return *pRow_;};
            const T& front() {return *pRow_;};

            T& back() {return *(pRow_ + rowLength_ - 1);};
            const T& back() {return *(pRow_ + rowLength_ - 1);};
        
            T& operator[](const int indx) {return pRow_[indx];};
            const T& operator[](const int indx) const {return pRow_[indx];};

        };

        Row_* matrixRows_;
        const size_t numRows_;
        const size_t numColumns_; 

    public :

        const size_t num_of_rows() const noexcept {return numRows_;};
        const size_t num_of_columns() const noexcept {return numColumns_;};

        template <typename Iter> 
        Matrix( const size_t numRows, const size_t numColumns, const Iter begin, const Iter end);
        
        Matrix(const size_t numRows, const size_t numColumns, T val = T{});

        const long determinant();


        






    };









































}   //  namespace matrices