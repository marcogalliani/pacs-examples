#include <cassert>
#include <iostream>
#include <vector>
#include <chrono>

template <class T, class Container = std::vector<T>>
class MyVector
{
public:
  // MyVector with initial size.
  MyVector(const size_t &n)
    : m_data(n)
  {}

  // MyVector with initial size and value.
  MyVector(const size_t &n, const double &initial_value)
    : m_data(n, initial_value)
  {}

  // Constructor for underlying container. 
  MyVector(const Container &other)
    : m_data(other)
  {}

  // Assignment operator for MyVector of different type.
  template <class T2, class R2>
  MyVector &
  operator=(const MyVector<T2, R2> &other)
  {
    assert(size() == other.size());

    for (size_t i = 0; i < m_data.size(); ++i)
      m_data[i] = other[i];

    return (*this);
  }

  size_t
  size() const
  {
    return m_data.size();
  }

  T
  operator[](const size_t &i) const
  {
    return m_data[i];
  }

  T &
  operator[](const size_t &i)
  {
    return m_data[i];
  }

  const Container &
  data() const
  {
    return m_data;
  }

  Container &
  data()
  {
    return m_data;
  }

private:
  Container m_data;
};

//element-wise sum
template <class T, class Op1, class Op2>
class MyVectorAdd
{
public:
  MyVectorAdd(const Op1 &a, const Op2 &b)
    : m_op1(a)
    , m_op2(b)
  {
    assert(a.size() == b.size());
  }

  T
  operator[](const size_t &i) const
  {
    return m_op1[i] + m_op2[i];
  }

  size_t
  size() const
  {
    return m_op1.size();
  }

private:
  const Op1 &m_op1;
  const Op2 &m_op2;
};


template<class T, class V1, class V2> 
MyVector<T,MyVectorAdd<T,V1,V2>> operator+(const MyVector<T,V1> &a, const MyVector<T,V2> &b){
  return MyVector<T,MyVectoAdd<T,V1,V2>>(MyVectorAdd<T,V1,V2>(a,data(),b.data()));
}

//using MyV = MyVector<double, std::vector<double>>;

// MyV a(N), b(N), c(N);
// MyV d = (a + b) +c;

// (a + b) -> MyVector<double, MyVectorAdd<double, MyVector, Myvector>>   //we're just storing values in MyVector, no op. is done
/* (a + b) + c -> MyVector<double, 
                            MyVectorAdd<double, 
                                        MyVector<double, MyVectorAdd<double,MyV,MyV>>,
                                        MyV
                                        >
                          >
    IMPORTANT: what triggers the operation it's just the assignment operator (=), before no operation is done
*/

//same goes for multiplication
class MyVectorMul
{
public:
  MyVectorMul(const Op1 &a, const Op2 &b)
    : m_op1(a)
    , m_op2(b)
  {
    assert(a.size() == b.size());
  }

  T
  operator[](const size_t &i) const
  {
    return m_op1[i] * m_op2[i];
  }

  size_t
  size() const
  {
    return m_op1.size();
  }

private:
  const Op1 &m_op1;
  const Op2 &m_op2;
};

template<class T, class V1, class V2> 
MyVector<T, MyVectorMul<T,V1,V2>> operator*(const MyVector<T,V1> &a, const MyVector<T,V2> &b){
  return MyVector<T,MyVectoMulr<T,V1,V2>>(MyVectorMul<T,V1,V2>(a,data(),b.data()));
}



// A program that evaluates (x + x + y * y).
int
main(int argc, char **argv)
{
  constexpr size_t N = 1e8;

  MyVector<double> x(N, 5.4);
  MyVector<double> y(N, 10.3);

  // Compute x + x + y * y
  {
  using namespace std::chrono;
  auto start = high_resolution_clock::now();
  MyVector<double> result(N);
  result = x + x + y * y;
  auto stop = high_resolution_clock::now();
  auto dt = duration_cast<milliseconds>(stop-start).count();

  std::cout << "ET elapsed: " << dt << "[ms]" << std::endl;
  }

  {
  using namespace std::chrono;
  auto start = high_resolution_clock::now();
  MyVector<double> result(N),tmp1(N),tmp2(N);
  tmp1 = x + x;
  tmp2 = y * y;
  result = tmp1 +tmp2;
  auto stop = high_resolution_clock::now();
  auto dt = duration_cast<milliseconds>(stop-start).count();

  std::cout << "Naive elapsed: " << dt << "[ms]" << std::endl;
  }


  return 0;
}
