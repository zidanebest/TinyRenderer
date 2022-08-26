#pragma once

#include <assert.h>
#include <cmath>
#include <fstream>

#include "pch.h"


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

    union{T x,u;};
    union{T y,v;};
};

template<typename T>
struct Vec<3,T>
{
public:
    Vec():x(T()),y(T()),z(T()){}
    Vec(T inX,T inY,T inZ):x(inX),y(inY),z(inZ){}
    Vec(const Vec<3,T>& inT):x(inT.x),y(inT.y),z(inT.z){}

    T& operator[](size_t index){return const_cast<T&>(static_cast<const Vec<3,T>&>(*this).operator[](index));}
    const T& operator[](size_t index)const {assert(index<3);return index==0 ? x:index==1? y:z;}
    
    Vec<3, T>& Normalize() {*this=(*this)*T(1/Norm(*this)); return *this;}
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
Vec<Dim,T> operator+(const Vec<Dim,T>& inVec0,T t)
{
    Vec<Dim,T> ret;
    for(size_t i=Dim;i--;ret[i]=inVec0[i]+t);
    return ret;
}

template<size_t Dim,typename T>
Vec<Dim,T> operator-(const Vec<Dim,T>& inVec0,T t)
{
    Vec<Dim,T> ret;
    for(size_t i=Dim;i--;ret[i]=inVec0[i]-t);
    return ret;
}

template<size_t Dim,typename T>
Vec<Dim,T> operator*(const Vec<Dim,T>& vec0,T t)
{
    Vec<Dim,T> ret;
    for(size_t i=Dim;i--;ret[i]=vec0[i]*t);
    return ret;
}

template<size_t Dim,typename T>
Vec<Dim,T> operator/(const Vec<Dim,T>& inVec0,T t)
{
    Vec<Dim,T> ret;
    for(size_t i=Dim;i--;ret[i]=inVec0[i]/t);
    return ret;
}

template<size_t Dim,typename T>
Vec<Dim,T> operator+(const Vec<Dim,T>& inVec0,const Vec<Dim,T>& inVec1)
{
    Vec<Dim,T> ret;
    for(size_t i=Dim;i--;ret[i]=inVec0[i]+inVec1[i]);
    return ret;
}

template<size_t Dim,typename T>
Vec<Dim,T> operator-(const Vec<Dim,T>& inVec0,const Vec<Dim,T>& inVec1)
{
    Vec<Dim,T> ret;
    for(size_t i=Dim;i--;ret[i]=inVec0[i]-inVec1[i]);
    return ret;
}

template<size_t Dim,typename T>
T operator*(const Vec<Dim,T>& vec0,const Vec<Dim,T> vec1)
{
    T ret=0;
    for(size_t i=Dim;i--;ret+=vec0[i]*vec1[i]);
    return ret;
}

template<typename T>
Vec<3,T> Cross(const Vec<3,T>& vec0,const Vec<3,T>& vec1)
{
    return Vec<3,T>(vec0.y*vec1.z-vec1.y*vec0.z,
        vec0.z*vec1.x-vec1.z*vec0.x,
        vec0.x*vec1.y-vec1.x*vec0.y);
}

template<size_t Dim,typename T>
T Dot(const Vec<Dim,T>& vec0,const Vec<Dim,T>& vec1)
{
    T ret;
    for(size_t i=Dim;i--;ret+=vec0[i]*vec1[i]);
    return ret;
}

template<size_t Dim,typename T>
T Norm(const Vec<Dim,T>& vec)
{
    T ret;
    for(size_t i=Dim;i--;ret+=vec[i]*vec[i]);
    return std::sqrt<T>(ret);
}

template<size_t Len,size_t Dim,typename T>
Vec<Len,T> Proj(const Vec<Dim,T>& vec)
{
    Assert(Len<Dim,"Can not project to a lower dim");
    Vec<Len,T> ret;
    for(size_t i=Dim;i--;ret[i]=vec[i]);
    return ret;
}

template<size_t Len,size_t Dim,typename T>
Vec<Len,T> Embed(const Vec<Dim,T>& vec,T fill=1)
{
    Vec<Len,T> ret;
    for(size_t i=Dim;i--;ret[i]=i<Len?vec[i]:fill);
    return ret;
}

typedef Vec<3,float> Vec3f;
typedef Vec<3,int> Vec3i;
typedef Vec<2,float> Vec2f;
typedef Vec<2,int> Vec2i;

template<size_t R,size_t C,typename T>
struct Matrix
{
private:
    Vec<C,T> rows;
public:
    Vec<R,T> Col(size_t index)
    {
        Assert(index<C,"index out of range");
        Vec<R,T> ret;
        for(size_t i=R;i--;ret[i]=rows[index][i]);
        return ret;
    }

    const Vec<C,T>& operator[](size_t index)
    {
        Assert(index<R,"index out of range");
        return rows;
    }
    Vec<C,T>& operator[](size_t index)const
    {
        return const_cast<Vec<C,T>&>(static_cast<const Vec<C,T>*>(this)->operator[](index));
    }
    void SetCol(size_t index,const Vec<R,T>& vec)
    {
        Assert(index<C,"index out of range");
        for(size_t i=R;i--;rows[i][index]=vec[i]);
    }
    Matrix<R,C,T> Identity()
    {
        Matrix<R,C,T> ret;
        for(size_t i=R;i--;)
            for(size_t j=C;j--;ret[i][j]= i==j?1:0);
        return ret;
    }
    Matrix<C,R,T> Transpose()
    {
        Matrix<C,R,T> ret;
        for(size_t i=C;i--;ret[i]=Col(i));
        return ret;
    }
    Matrix<R,C,T> Inverse()
    {
        Assert(R==C,"can not calculate inverse of non-square mat")
        Matrix<R,C,T> ret;
        // inverse mat = adj mat/det mat
        
    }
    T Confact(size_t r,size_t c)
    {
        Assert(r<R && c<C,"index out of range");
        return (r+c)%2==0? Minor(r,c):-Minor(r,c);
    }
    T Minor(size_t r,size_t c)
    {
        Assert(r<R && c<C,"index out of range");
        return MinorMat(r,c).Det();
    }
    Matrix<R-1,C-1,T> MinorMat(size_t r,size_t c)
    {
        Assert(r<R && c<C,"index out of range");
        Matrix<R-1,C-1,T> ret;
        for(size_t i=R-1;i--;)
            for(size_t j=C-1;j--;ret[i][j]=r<R)
    }
    T Det()
    {
        
    }
};