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
    Vec(const Vec<3,T>& inT):x(inT.x),y(inT.y),z(inT.z){}
    Vec<3,T>& operator=(const Vec<3,T>& inT){x=inT.x;y=inT.y;z=inT.z;return *this;}
    T& operator[](size_t index){return const_cast<T&>(static_cast<const Vec<3,T>&>(*this).operator[](index));}
    const T& operator[](size_t index)const {assert(index<3);return index==0 ? x:(index==1? y:z);}
    Vec<3,T> operator* (T t){return Vec<3,T>(this->x*t,this->y*t,this->z*t);}
    float Norm() {return std::sqrt(x*x+y*y+z*z);}
    Vec<3, T> & Normalize() {*this=(*this)*T(1/Norm()); return *this;}
public:
    union{T x,u;};
    union{T y,v;};
    T z;
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

template<size_t Dim,typename T>
Vec<Dim,T> operator-(const Vec<Dim,T>& inVec0,const Vec<Dim,T>& inVec1)
{
    Vec<Dim,T> ret;
    for(size_t i=0;i<Dim;++i)
    {
        ret[i]=inVec0[i]-inVec1[i];
    }
    return ret;
}

template<size_t Dim,typename T>
Vec<Dim,T> operator/(const Vec<Dim,T>& inVec0,T t)
{
    Vec<Dim,T> ret;
    for(size_t i=0;i<Dim;++i)
    {
        ret[i]=inVec0[i]/t;
    }
    return ret;
}

template<typename T>
Vec<3,T> Cross(const Vec<3,T>& inVec0,const Vec<3,T>& inVec1)
{
    return Vec<3,T>(inVec0.y*inVec1.z-inVec1.y*inVec0.z,
        inVec0.z*inVec1.x-inVec1.z*inVec0.x,
        inVec0.x*inVec1.y-inVec1.x*inVec0.y);
}
template<typename T>
T Dot(const Vec<3,T>& inVec0,const Vec<3,T>& inVec1)
{
    return T(inVec0.x*inVec1.x+inVec0.y*inVec1.y+inVec0.z*inVec1.z);
}

typedef Vec<3,float> Vec3f;
typedef Vec<3,int> Vec3i;
typedef Vec<2,float> Vec2f;
typedef Vec<2,int> Vec2i;