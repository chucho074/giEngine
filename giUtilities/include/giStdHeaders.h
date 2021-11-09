/**
 * @file    giStdHeaders.h
 * @author  Jes�s Alberto Del Moral Cupil
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
#include <fstream>
#include <sstream>

//#include <codecvt>
//#include <locale>

namespace giEngineSDK {
  using String = std::string;
  using wString = std::wstring;
  using inStream = std::ifstream;
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
  
  /**
   * @brief 
   * @tparam T 
   */
  template <typename T>
  using SharedPtr = std::shared_ptr<T>;

  /**
   * @brief 
   * @tparam T 
   */
  template <typename T>
  using WeakPtr = std::weak_ptr<T>;

  /**
   * @brief 
   * @tparam T 
   */
  template<typename T>
  using UniquePtr = std::unique_ptr<T>;

  using std::make_unique; 

  //template <typename T>
  using std::dynamic_pointer_cast;

  using std::static_pointer_cast;

  //template <typename T>
  using std::make_shared;


  ////Wstring & String converters functions
  //using convert_t = std::codecvt_utf8<wchar_t>;
  //std::wstring_convert<convert_t, wchar_t> strconverter;

  //String 
  //to_string(wString wstr) {
  //  return strconverter.to_bytes(wstr);
  //}

  //wString 
  //to_wstring(String str) {
  //  return strconverter.from_bytes(str);
  //}

}