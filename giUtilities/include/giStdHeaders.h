/**
 * @file    giStdHeaders.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    05/04/2021
 * @brief   .
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include <vector>
#include <stack>
#include <queue>
#include <array>
#include <string>
#include <list>
#include <map>


namespace giEngineSDK {
  using String = std::string;
  using wString = std::wstring;

  /**
   * @brief 
   * @param T 
   * @param Alloc 
   */
  template<typename T, typename Alloc = std::allocator<T>>
  using Vector = std::vector<T, Alloc>;

  /**
   * @brief 
   * @param T 
   * @param Alloc 
   */
  template<typename T, typename Alloc = std::allocator<T>>
  using Stack = std::stack<T, Alloc>;

  /**
   * @brief 
   * @param T 
   * @param Alloc 
   */
  template<typename T, typename Alloc = std::allocator<T>>
  using Queue = std::queue<T, Alloc>;

  /**
   * @brief 
   * @param T 
   * @param Alloc 
   */
  template<typename T, typename Alloc = std::allocator<T>>
  using List = std::list<T, Alloc>;

  /**
   * @brief 
   * @tparam Key 
   * @tparam T 
   * @tparam Compare 
   * @tparam Alloc 
   */
  template<class Key,
           class T,
           class Compare = std::less<Key>,
           class Alloc = std::allocator<std::pair<const Key, T>>> 
  using Map = std::map<Key, T, Compare, Alloc>;


}