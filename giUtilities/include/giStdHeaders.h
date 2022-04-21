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
#include <memory>

#include <codecvt>
#include <locale>
#include <iostream>

namespace giEngineSDK {
  using String = std::string;
  using wString = std::wstring;

  /**
   * @brief      Vector.
   * @param      T 
   * @param      Alloc 
   */
  template<typename T, typename Alloc = std::allocator<T>>
  using Vector = std::vector<T, Alloc>;

  /**
   * @brief      Stack.
   * @param      T 
   * @param      Alloc 
   */
  template<typename T, typename Alloc = std::allocator<T>>
  using Stack = std::stack<T, Alloc>;

  /**
   * @brief      Queue.
   * @param      T 
   * @param      Alloc 
   */
  template<typename T, typename Alloc = std::allocator<T>>
  using Queue = std::queue<T, Alloc>;

  /**
   * @brief      List.
   * @param      T 
   * @param      Alloc 
   */
  template<typename T, typename Alloc = std::allocator<T>>
  using List = std::list<T, Alloc>;

  /**
   * @brief      Pair.
   */
  template<class K, class T>
  using Pair = std::pair<const K, T>;

  /**
   * @brief      Maps.
   * @tparam     Key 
   * @tparam     T 
   * @tparam     Compare 
   * @tparam     Alloc 
   */
  template<class Key,
           class T,
           class Compare = std::less<Key>,
           class Alloc = std::allocator<Pair<const Key, T>>>
  using Map = std::map<Key, T, Compare, Alloc>;
  
  /**
   * @brief      Shared Pointers.
   * @tparam     T 
   */
  template <typename T>
  using SharedPtr = std::shared_ptr<T>;

  /**
   * @brief      Weak Pointers.
   * @tparam     T 
   */
  template <typename T>
  using WeakPtr = std::weak_ptr<T>;

  /**
   * @brief      Unique Pointers.
   * @tparam     T 
   */
  template<typename T>
  using UniquePtr = std::unique_ptr<T>;

  //Make unique function
  using std::make_unique; 

  //Cast to dynamic pointer
  using std::dynamic_pointer_cast;

  //Cast to static pointer
  using std::static_pointer_cast;

  //Making shared 
  using std::make_shared;

  //Wstring & String converters functions
  //using convert_t = std::codecvt_utf8<wchar_t>;

  ////wString to String Function
  //String 
  //to_string(wString wstr) {
  //  
  //  std::wstring_convert<convert_t, wchar_t> strConverter;
  //  return strConverter.to_bytes(wstr);
  //}

  ////String to wString Function
  //wString 
  //to_wstring(String str) {
  //  std::wstring_convert<convert_t, wchar_t> strConverter;
  //  return strConverter.from_bytes(str);
  //}

  //Console output
  #define ConsoleOut std::cout

  //Console input
  #define ConsoleIn std::cin;

}