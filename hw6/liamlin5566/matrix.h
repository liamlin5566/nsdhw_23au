#include <cstddef>
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <limits>

#ifndef MATRIX_H
#define MATRIX_H


class Matrix {

public:

    Matrix()
      : m_nrow(0), m_ncol(0), m_buffer({})
    {
        
    }


    Matrix(std::size_t nrow, std::size_t ncol)
      : m_nrow(nrow), m_ncol(ncol), m_buffer(std::vector<double>(nrow * ncol)) //m_buffer(std::vector<double, CustomAllocator<double>>(nrow * ncol))
    {
        
    }

    Matrix(Matrix const & other);
    Matrix & operator=(Matrix const & other);

    
    

    // TODO: move constructors and assignment operators.
    Matrix(Matrix && other);
    Matrix & operator=(Matrix && other);


    bool operator==(Matrix const &other) const;
    double   operator() (std::size_t row, std::size_t col) const
    {
        return m_buffer[index(row, col)];
    }
    double & operator() (std::size_t row, std::size_t col)
    {
        return m_buffer[index(row, col)];
    }

    

    std::size_t nrow() const { return m_nrow; }
    std::size_t ncol() const { return m_ncol; }
    std::size_t size() const { return m_nrow * m_ncol; }


    double buffer(std::size_t i) const { return m_buffer[i]; }
    double * data() const { return (double *)m_buffer.data(); }
    
    // std::vector<double, CustomAllocator<double>> buffer_vector() const
    // {
    //     return std::vector<double, CustomAllocator<double>>(m_buffer.begin(), m_buffer.end());
    // }
    std::vector<double> & buffer_vector() 
    {
        return m_buffer;//std::vector<double>(m_buffer.begin(), m_buffer.end());
    }

    std::vector<double> const & buffer_vector() const
    {
        return m_buffer;//std::vector<double>(m_buffer.begin(), m_buffer.end());
    }



    bool is_transposed() const { return m_transpose; }

    Matrix & transpose()
    {
        m_transpose = !m_transpose;
        std::swap(m_nrow, m_ncol);
        return *this;
    }

    

    std::string toString() const;

    
private:

    std::size_t index(std::size_t row, std::size_t col) const
    {
        if (m_transpose) { return row          + col * m_nrow; }
        else             { return row * m_ncol + col         ; }
    }

    //void reset_buffer(std::size_t nrow, std::size_t ncol);
    

    std::size_t m_nrow = 0;
    std::size_t m_ncol = 0;
    bool m_transpose = false;
    
    //std::vector<double, CustomAllocator<double>> m_buffer;
    std::vector<double> m_buffer;

};

Matrix multiply_naive(Matrix const &mat1, Matrix const &mat2);
Matrix multiply_tile(Matrix const &mat1, Matrix const &mat2, std::size_t tsize);
Matrix multiply_mkl(const Matrix& mat1, const Matrix& mat2);
#endif