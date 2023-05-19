#ifndef EXAMPLES_SRC_INTERP1D_INTERP1D_HPP_
#define EXAMPLES_SRC_INTERP1D_INTERP1D_HPP_

#include <algorithm>
#include <array>
#include <exception>
#include <functional>
#include <iterator>
#include <limits>
#include <type_traits>

/*! A general piecewise-linear interpolator
 *
 * This function is the building block for rather general
 * piecewise-liner interpolation It requires to have a range defined
 * by two bidirectional iterators in input. The iterators iterates
 * over a container of a generic type from which we can extract a
 * Key and a Value. The range must be strictly ordered with respect
 * to the key (i.e. without repetition of elements with equivalent
 * keys). The ordering relation must be specified as argument,
 * together as the functors that extract the key and the value from
 * the container, respectively. It is also assumed that usual
 * arithmetic operations may be performed on keys and values.
 *
 * If the value of the key where to interpolate falls between the
 * interval defined by the keys in the range, piecewise-linear
 * interpolation is performed. Otherwise, extrapolation is performed
 * using the last or first two elements of the container, depending
 * on the case.
 *
 * The procedure followed is a binary search (bisection) on the
 * keys.
 *
 * Complexity: if the iterator is a forward iterator the complexity
 * is log2 N, N being  the size of the range. otherwise complexity
 * is basically linear, because we need to advance iterators and
 * this is linear on non forward iterators
 *
 * @note We recall that the range is defined by [begin, end[
 *
 * @tparam RAIterator A bi-directional random-access iterator
 * @tparam Key The type of the Key
 * @tparam ExtractKey The type of the functor that extracts the key form a
 * dereferenced iterator
 * @tparam ExtractValue The type of functor that extracts the value form a
 * dereferenced iterator
 * @tparam CompareKey Type of comparison operator between keys
 * @param begin Start of the range
 * @param end   End of the range
 * @param keyVal The value of the key to interpolate
 * @param extractKey The actual functor for extraction of key
 * @param extractValue The actual functor for extraction of values
 * @param comp The comparison operator for keys (defaulted to std::less<Key>()
 * @return the value found in correspondence of keyVal. Type is automatically deduced.
 * @pre I need to have at least two interpolation nodes.
 * @pre Interpolation nodes must be distinct and sorted.
 * @pre Iterators must be (at least) bidirectional.
 * @throw a runtime standard exception if I do not have at least 2
 * interpolation nodes
 */
template <class RAIterator,
          class Key, 
          class ExtractKey, 
          class ExtractValue,
          class CompareKey = std::less<Key>>
auto
interp1D(RAIterator const &  begin, 
         RAIterator const &  end,
         Key const &         keyVal,
         ExtractKey const &  extractKey,
         ExtractValue const &extractValue,
         CompareKey const &  comp = std::less<Key>())
{
  // I avoid users using wrong iterators
  // I nice use of iterator_traits and iterator_tags
  using category = typename std::iterator_traits<RAIterator>::iterator_category;

  static_assert(std::is_same_v<category, std::bidirectional_iterator_tag> ||
                  std::is_same_v<category, std::random_access_iterator_tag>,
                "Iterators must be (at least) bidirectional");

  // I need at least two point for interpolating anything. This
  // checks also that end is after begin!
  if (std::distance(begin, end) < 1)
    throw std::runtime_error(
      "Interp1D: I need at least 2 points to interpolate!");

  // 1. find the interval [a,b] that contains keyVal
  // we have to use iterators to keep it generic
  /*
  auto b = std::next(begin);
  //generic loop theough iterators
  while(b != end){
    if(!comp(extractKey(b),keyVal)){
      break;
    }
    b = std::next(b); // std::advance(b) // b++
  }
  a = std::next(b; -1); //going back of 1, we can do this since the iterator is bidirectional and then we can go back
  */

  /*
  RAIterator a = begin;
  RAIterator b = end;
  for(auto dis = std::distance(a,b); dis > 1;){
    RAIterator c = std::next(a,dis/2); //computing the midpoint
    // safer wrt overflow: a + (b-a)/2 (== (b+a)/2 usual formula for midpoint)
    if(comp(keyVal,extractKey(c))){
      b = c;
    }
    else{
      a = c;
      
    }
    dis = std::distance(a,b);
  }
  b = std::next(a,1);
  */

  //there's also a function in the standard library that does the same thing (check the doc)
  const auto b = std::lower_bound(
    std::next(begin),
    std::next(end,-1),
    keyVal,
    [&comp, &extractKey](const auto &elem, const Key &to_find){
      return comp(extractKey(&elem),to_find); //passing the adress of elem
    }    
  );
  const auto a = std::next(b,-1);

  if(b == end){
    b = a;
    a = std:.next(a,-1);
  }

  // 2. do a linear interpolation according to [a,b] [f(a),f(b)]
  const auto valueLeft = extractValue(a); //f(a) 
  const auto keyLeft = extractKey(a); //a
  const auto valueRight = extractValue(b); //f(b) 
  const auto keyRight = extractKey(b); //b

  const auto len = keyRight - keyLeft;

  // I assume no nodes are repeated
  const auto coeffRight = (keyVal - keyLeft) / len;
  const auto coeffLeft  = 1.0 - coeffRight;

  return valueLeft * coeffLeft + valueRight * coeffRight;


}

#endif /* EXAMPLES_SRC_INTERP1D_INTERP1D_HPP_ */
