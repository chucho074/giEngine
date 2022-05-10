/**
 * @file    giStdHeaders.h
 * @author  Jesus Alberto Del Moral Cupil
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
#include <locale>
#include <filesystem>
#include <iostream>
//#include <Windows.h>

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

  namespace fsys = std::filesystem;

  using Path = std::filesystem::path;

  //Wstring & String converters functions
 /* String 
  to_string(wString wstr) {
    int count = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), wstr.length(), NULL, 0, NULL, NULL);
    std::string str(count, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], count, NULL, NULL);
    return str;
  }

  wString 
  to_wstring(String str) {
    int count = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), NULL, 0);
    std::wstring wstr(count, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), &wstr[0], count);
    return wstr;
  }*/

  //Console output
  #define ConsoleOut std::cout

  //Console input
  #define ConsoleIn std::cin;

}