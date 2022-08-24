#pragma once

#include <assert.h>
#include <cmath>
#include <fstream>


template<size_t Dim,typename T>
struct Vec
{
public:
    Vec()
    {
        for(size_t i=0;i<Dim;++i)
        {
            data[i]=T();
        }
    }
    T& operator[](size_t index){return const_cast<T&>(operator[](index));}
    const T& operator[](size_t index)const {assert(index<Dim);return data[index];}
private:
    T data[Dim];
};


template<typename T>
struct Vec<2,T>
{
public:
    Vec():x(T()),y(T()){}
    Vec(T inX,T inY):x(inX),y(inY){}
    T& operator[](size_t index){return const_cast<T&>(static_cast<const Vec<2,T>&>(*this).operator[](index));}
    const T& operator[](size_t index)const {assert(index<2);return index==0 ? x:y;}
public:
    T x,y;
};

template<typename T>
struct Vec<3,T>
{
public:
    Vec():x(T()),y(T()),z(T()){}
    Vec(T inX,T inY,T inZ):x(inX),y(inY),z(inZ){}
    Vec(const T& inT):x(inT.x),y(inT.y),z(inT.z){}
    T& operator[](size_t index){return const_cast<T&>(static_cast<const Vec<3,T>&>(*this).operator[](index));}
    const T& operator[](size_t index)const {assert(index<3);return index==0 ? x:(index==1? y:z);}
    Vec<3,T> operator* (T t){return Vec<3,T>(this->x*t,this->y*t,this->z*t);}
    float Norm() {return std::sqrt(x*x+y*y+z*z);}
    Vec<3, T> & Normalize() {*this = (*this)*T(1/Norm()); return *this;}
public:
    T x,y,z;
};

template<size_t Dim,typename T>
std::istream& operator>>(std::istream& is,Vec<Dim,T>& inVec)
{
    for(size_t i=0;i<Dim;++i)
    {
        is>>inVec[i];
    }
    return is;
}

typedef Vec<3,float> Vec3f;
typedef Vec<3,int> Vec3i;
typedef Vec<2,float> Vec2f;
typedef Vec<2,int> Vec2i;