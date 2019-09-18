#ifndef BINARYHELPER_H
#define BINARYHELPER_H

#include <fstream>

template<typename T>
std::ostream& MWrite(std::ostream& _ostream, const T& value){
    return _ostream.write(reinterpret_cast<const char*>(&value), sizeof(T));
}

#endif
