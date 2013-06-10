/****************************************************************************
 *
 *    StreamUtils.h by z.keyring (c) 2013 All Rights Reserved.
 *
 *                                      --code with Emacs :)
 *
 *    DESC: Various useful functions that operate on or with streams.
 ***************************************************************************/

#ifndef __STREAMUTILS_H__
#define __STREAMUTILS_H__

#include <sstream>
#include <string>
#include <iomanip>

template <class T>
inline std::string ttos( const T &t, int precision = 2 ){
  /* convert a type to a string */
  std::ostringstream buffer;
  buffer << std::fixed << std::setprecision(precision) << t;

  return buffer.str();
}

inline std::string btos(bool b){
  /* convert a bool to a string */
  if(b) return "true";
  return "false";
}

template <typename T>
inline T GetValueFromStream( std::ifstream &stream ){
  /* grabs a value of the specified type from an input stream */
  T val;
  stream >> val;

  if(!stream){
    throw std::runtime_error("wrong type");
  }

  return val;
}

template <typename T>
void WriteBitsToStream( std::ostream &stream, const T &val ){
  /* writes the value as a binary string of bits */
  int numBits =  sizeof(T) * 8;

  while(--numBits >= 0){
    if((numBits + 1) % 8 == 0) stream << " ";
    unsigned long mask = 1 << numBits;
    if(val & mask) stream << "1";
    else stream << "0";
  }
}

#endif	/* __STREAMUTILS_H__ */
