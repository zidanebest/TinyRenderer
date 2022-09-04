#pragma once

#include <assert.h>
#include <cmath>
#include <fstream>

#include "pch.h"

#pragma optimize( "", off )

template<size_t Dim,typename T>
struct Vec
{
public:
    Vec()
    {
        for(size_t i=Dim;i--;data[i]=T());
    }
    // Vec(const Vec<Dim,T>& vec)
    // {
    //     for(size_t i=Dim;i--;data[i]=vec.data[i]);
    // }
    template<typename U>
    Vec(const Vec<Dim,U>& vec);
    Vec(const std::initializer_list<T>& list)
    {
        size_t i=0;
        for(auto it=list.begin();it!=list.end();++it,++i)
        {
            data[i]=*it;
        }
    }
    Vec<Dim,T>& operator=(const Vec<Dim,T>& vec)
    {
        for(size_t i=Dim;i--;data[i]=vec.data[i]);
        return *this;
    }
    T& operator[](size_t index){return const_cast<T&>(static_cast<const Vec<Dim,T>*>(this)->operator[](index));}
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
    Vec(const std::initializer_list<T>& list)
    {
        size_t i=0;
        for(auto it=list.begin();it!=list.end();++it,++i)
        {
            this->operator[](i)=*it;
        }
    }
    template<typename U>
    Vec(const Vec<2,U>& vec);//:x(vec.x),y(vec.y){}
    // Vec(const Vec<2,T>& vec)
    // {
    //     for(size_t i=2;i--;this->operator[](i)=vec[i]);
    // }
    // Vec<2,T>& operator=(const Vec<2,T>& vec)
    // {
    //     for(size_t i=2;i--;this->operator[](i)=vec[i]);
    //     return *this;
    // }
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
    Vec(const std::initializer_list<T>& list)
    {
        size_t i=0;
        for(auto it=list.begin();it!=list.end();++it,++i)
        {
            this->operator[](i)=*it;
        }
    }
    template<typename U>
    Vec(const Vec<3,U>& vec);//:x(vec.x),y(vec.y),z(vec.z){}
    // Vec(const Vec<3,T>& inT):x(inT.x),y(inT.y),z(inT.z){}
    // Vec<3,T>& operator=(const Vec<3,T>& vec)
    // {
    //     for(size_t i=3;i--;this->operator[](i)=vec[i]);
    //     return *this;
    // }
    T& operator[](size_t index){return const_cast<T&>(static_cast<const Vec<3,T>&>(*this).operator[](index));}
    const T& operator[](size_t index)const {assert(index<3);return index==0 ? x:index==1? y:z;}
    
    Vec<3, T>& Normalize() {*this=(*this)*T(1/Norm(*this)); return *this;}
public:
    union{T x{},u;};
    union{T y{},v;};
    T z{};
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
    T ret=0;
    for(size_t i=Dim;i--;ret+=vec0[i]*vec1[i]);
    return ret;
}

template<size_t Dim,typename T>
T Norm(const Vec<Dim,T>& vec)
{
    T ret=0;
    for(size_t i=Dim;i--;ret+=vec[i]*vec[i]);
    return std::sqrt(ret);
}

template<size_t Len,size_t Dim,typename T>
Vec<Len,T> Proj(const Vec<Dim,T>& vec)
{
    Assert(Len<Dim,"can not project to a lower dim");
    Vec<Len,T> ret;
    for(size_t i=Len;i--;ret[i]=vec[i]);
    return ret;
}

template<size_t Len,size_t Dim,typename T>
Vec<Len,T> Embed(const Vec<Dim,T>& vec,T fill=1)
{
    Vec<Len,T> ret;
    for(size_t i=Dim;i--;ret[i]=i<Len?vec[i]:fill);
    return ret;
}



// why???
// template<size_t Dim>
// template<size_t Dim> Vec<Dim,float>::Vec(const Vec<Dim,int>& v)
// {
//     
// }



template<size_t R,size_t C,typename T>
struct Matrix
{

    Vec<C,T> rows[R];
    Matrix()=default;
    Matrix(const std::initializer_list<Vec<C,T>>& list)
    {
        size_t i=0;
        for(auto it=list.begin();it!=list.end();++it,++i)
        {
            rows[i]=*it;
        }
    }
    Vec<R,T> Col(size_t index) const
    {
        Assert(index<C,"index out of range");
        Vec<R,T> ret;
        for(size_t i=R;i--;ret[i]=rows[i][index]);
        return ret;
    }

    const Vec<C,T>& operator[](size_t index)const
    {
        Assert(index<R,"index out of range");
        return rows[index];
    }
    Vec<C,T>& operator[](size_t index)
    {
        return const_cast<Vec<C,T>&>(static_cast<const Matrix<R,C,T>*>(this)->operator[](index));
    }
    void SetCol(size_t index,const Vec<R,T>& vec)
    {
        Assert(index<C,"index out of range");
        for(size_t i=R;i--;rows[i][index]=vec[i]);
    }
    
    Matrix<C,R,T> Transpose()const
    {
        Matrix<C,R,T> ret;
        for(size_t i=C;i--;ret[i]=Col(i));
        return ret;
    }
    Matrix<R,C,T> Inverse()const
    {
        Assert(R==C,"can not calculate inverse of non-square matrix")
        auto adjoint=Adjoint();
        T det=adjoint[0]*Col(0);
        return adjoint/(1.0f*det);
    }
    Matrix<C,R,T> Adjoint()const
    {
        Assert(R==C,"can not calculate adjoint of non-square matrix")
        Matrix<C,R,T> ret;
        for(size_t i=C;i--;)
            for(size_t j=R;j--;ret[i][j]=Cofactor(j,i));
        return ret;
    }
    T Cofactor(size_t r,size_t c)const
    {
        Assert(r<R && c<C,"index out of range");
        return (r+c)%2==0? Minor(r,c).Det():-Minor(r,c).Det();
    }

    Matrix<R-1,C-1,T> Minor(size_t r,size_t c)const
    {
        Assert(r<R && c<C,"index out of range");
        Matrix<R-1,C-1,T> ret;
        for(size_t i=R-1;i--;)
            for(size_t j=C-1;j--;ret[i][j]=rows[i<r?i:i+1][j<c?j:j+1]);
        return ret;
    }
    T Det()const
    {
        Assert(R==C,"can not calculate determinant of non-square matrix");
        return ::Det(*this);
    }
    static Matrix<R,C,T> Identity();
};

template<size_t R,size_t C,typename T>
Matrix<R,C,T> Matrix<R,C,T>::Identity()
{
    Assert(R==C,"identity matrix must be a square matrix")
    Matrix<R,C,T> ret;
    for(size_t i=R;i--;)
        for(size_t j=C;j--;ret[i][j]= i==j?1:0);
    return ret;
}

template<size_t Dim,typename T>
T Det(const Matrix<Dim,Dim,T>& mat)
{
    T ret=0;
    for(size_t i=Dim;i--;ret+=mat.rows[0][i]*mat.Cofactor(0,i));
    return ret;
}
template<typename T>
T Det(const Matrix<1,1,T>& mat)
{
    return mat.rows[0][0];
}
template<typename T>
T Det(const Matrix<2,2,T>& mat)
{
    return mat[0][0]*mat[1][1]-mat[0][1]*mat[1][0];
}

template<size_t R,size_t C,typename T>
Matrix<R,C,T> operator*(const Matrix<R,C,T>& mat,T scalar)
{
    Matrix<R,C,T> ret;
    for(size_t i=R;i--;)
        for(size_t j=C;j--;ret[i][j]*=scalar);
    return ret;
}

template<size_t R,size_t C,typename T>
Matrix<R,C,T> operator/(const Matrix<R,C,T>& mat,T scalar)
{
    Matrix<R,C,T> ret;
    for(size_t i=R;i--;)
        for(size_t j=C;j--;ret[i]=mat[i]/scalar);
    return ret;
}

template<size_t R0,size_t C0,size_t R1,size_t C1,typename T>
Matrix<R0,C1,T> operator*(const Matrix<R0,C0,T>& mat0,const Matrix<R1,C1,T>& mat1)
{
    Assert(C0==R1,"matrix product:error dim");
    Matrix<R0,C1,T> ret;
    for(size_t i=R0;i--;)
        for(size_t j=C1;j--;ret[i][j]=mat0[i]*mat1.Col(j));
    return ret;
}

template<size_t R0,size_t C0,typename T>
Vec<C0,T> operator*(const Matrix<R0,C0,T>& mat,const Vec<C0,T>& vec)
{
    Vec<C0,T> ret;
    for(size_t i=R0;i--;ret[i]=mat[i]*vec);
    return ret;
}

typedef Vec<3,float> Vec3f;
typedef Vec<3,int> Vec3i;
typedef Vec<2,float> Vec2f;
typedef Vec<2,int> Vec2i;
typedef Vec<4,float> Vec4f;
typedef Vec<4,int> Vec4i;
typedef Matrix<3,3,float> Mat3f;
typedef Matrix<4,4,float> Mat4f;


static Mat4f LookAt(Vec3f eye,Vec3f center,Vec3f up)
{
    Mat4f rot_mat;
    Mat4f trans_mat;
    Vec3f forward=Vec3f(eye-center).Normalize();
    Vec3f right=Cross(up,forward).Normalize();
    up=Cross(forward,right);
    
    rot_mat.rows[0]=Embed<4,3,float>(right,0);
    rot_mat.rows[1]=Embed<4,3,float>(up,0);
    rot_mat.rows[2]=Embed<4,3,float>(forward,0);
    rot_mat.rows[3]=Vec4f{0,0,0,1};
    trans_mat[0]=Vec4f{1,0,0,-center.x};
    trans_mat[1]=Vec4f{0,1,0,-center.y};
    trans_mat[2]=Vec4f{0,0,1,-center.z};
    trans_mat[3]=Vec4f{0,0,0,1};
    return rot_mat*trans_mat;
}
static Mat4f lookat(Vec3f eye, Vec3f center, Vec3f up) {
    Vec3f z = (eye-center).Normalize();
    Vec3f x = Cross(up,z).Normalize();
    Vec3f y = Cross(z,x).Normalize();
    Mat4f Minv =Mat4f::Identity();
    Mat4f Tr  =Mat4f::Identity();
    for (int i=0; i<3; i++) {
        Minv[0][i] = x[i];
        Minv[1][i] = y[i];
        Minv[2][i] = z[i];
        Tr[i][3] = -center[i];
    }
    return Minv*Tr;
}


#pragma optimize( "", on )