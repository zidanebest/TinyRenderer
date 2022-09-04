#include "Vec.h"

// template<size_t Dim>
// template<>
// Vec<Dim,int>::Vec(const Vec<Dim,float>& v){}

template<>
template<> Vec<3,int>::Vec(const Vec<3,float>& v):x(static_cast<int>(v.x+.5f)),
    y(static_cast<int>(v.y+.5f)),z(static_cast<int>(v.z+.5f)){}
template<>
template<> Vec<2,int>::Vec(const Vec<2,float>& v):x(static_cast<int>(v.x+.5f)),
    y(static_cast<int>(v.y+.5f)){}
