#ifndef RKFTRAITS_HPP
#define RKFTRAITS_HPP

#include <type_traits>

// Define a type that is convertible to a scalar (e.g. double& is accepted)
template<typename T>
concept Scalar = std::is_floating_point<std::decay_t<T>>::value;

// Define a vector
// by the definition of (normed) vectorial space 
// - Normable
// - Addable
// - ScalarMultiplicable
//we're requirinq the existence of a norm method
template<typename T>
concept normable = requires(T x){ 
    {x.norm()} -> Scalar;
};
//we're requiring the type to be addable
template<typename T>
concept Addable = requires(T a, T b){
    {a += b} -> std::convertible_to<T>;
    {a -= b} -> std::convertible_to<T>;
}

template<typename T>
concept ScalarMultiplicable = requires(T x){
    {1.0 * x} -> std::convertible<T>;
} 

// To output the solution to a file we need the object to be subscriptable
template <typename T>
concept Subscriptable = requires(Tx){
    {x[0]} -> Scalar;
    {x.size()} -> std::integral;
}

// Define Vector concept
template <typename T>
concept Vector = Normable<T> && Addable<T> && ScalarMultiplicable<T> && Subscriptable<T>;

// We want to use our ODE solver for both scalar and vectorial problems
template <typename T>
concept ScalarOrVector = Scalar<T> || Vector<T>;


#endif /* RKFTRAITS_HPP */
