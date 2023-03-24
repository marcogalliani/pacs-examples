#include "sparse_matrix.hpp"

#include <limits>
#include <iomanip>

template <class T>
void SparseMatrix<T>::update_properties() {
    m_nnz = 0;
    m_m = 0;
    for(const auto &row: m_data){
        if(!row.empty()){
            m_nnz += row.size();
            m_m = std::max(m_m, row.rbegin()->begin()->first+1);
        }
    }
}

template <class T>
std::ostream &operator<<(std::ostream &stream, SparseMatrix<T> &M) {
    M.update_properties();
    stream << "nrow: " << M.m_data.size() <<"\n";
    stream << "ncols: " << M.m_m.size() <<"\n";
    stream << "nnz: " << M.m_nnz <<"\n";

    for(size_t i=0; i<M.size(); i++){
        for(auto j=M[i].begin(); j!=M[i].begin();j++){
            stream << i << ", " << j->first << ", " << j->second
            << std::setprecision(std::numeric_limits<T>::max_digits10)
            << "\n";
        }
    }
    return stream;
}

template <class T>
void
SparseMatrix<T>::aij(std::vector<T>            &a,
                     std::vector<unsigned int> &i,
                     std::vector<unsigned int> &j) {


    update_properties();
    a.reserve(m_nnz);
    i.reserve(m_nnz);
    j.reserve(m_nnz);
    for(size_t ki=0; ki<m_data.size();ki++){
        for(const auto &[kj,v]:m_data[ki]){
            a.push_back(v);
            i.push_back(ki);
            j.push_back(kj);
        }
    }

}

template <class T>
void
SparseMatrix<T>::csr(std::vector<T>            &val,
                     std::vector<unsigned int> &col_ind,
                     std::vector<unsigned int> &row_ptr)
{
    update_properties();
    val.resize(m_nnz);
    col_ind.resize(m_nnz);
    row_ptr.resize(m_data.size()+1);
    row_ptr[0] = 0;
    unsigned idx = 0;
    for(size_t ii=0; ii<m_data.size();ii++){
        for(auto jj=m_data[ii].begin(); jj!=m_data[ii].end();jj++){
            val[idx] = jj->second;
            col_ind[idx] = jj->first;
            idx++;
        }
        row_ptr[ii+1] = idx; 
    }

}

template <class T>
void
SparseMatrix<T>::operator+=(SparseMatrix<T> &other)
{
    assert(size()==other.size());
    assert(m_m==other.m_m);

    for(size_t ii=0; ii < m_data.size(); ii++){
        for(auto jj=other[ii].begin(); jj!=other[ii].end();jj++){
            m_data[ii][jj->first] += jj->second;
        }
    }
}

template <class T>
std::vector<T>
operator*(SparseMatrix<T> &M, const std::vector<T> &x)
{
    std::vector<T> y(M.size());
    for(size_t i=0; i < M.size(); i++){
        for(auto j=M[i].begin(); j!=M[i].end();j++){
            y[i] += j->second * x[j->first]; 
        }
    }
    return y;

}


template class SparseMatrix<double>;

