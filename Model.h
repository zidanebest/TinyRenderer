#pragma once
#include <vector>

#include "Math.hpp"

class Model
{
public:
    Model(const char* inPath);
    size_t VertSize(){return verts.size();}
    size_t FaceSize(){return faces.size();}
    const Vec3f& GetVert(size_t index)const{return verts[index];}
    Vec3f& GetVert(size_t index){return const_cast<Vec3f&>(static_cast<const Model&>(*this).GetVert(index));}
    const Vec3i& GetFace(size_t index)const{return faces[index];}
    Vec3i& GetFace(size_t index){return const_cast<Vec3i&>(static_cast<const Model&>(*this).GetFace(index));}
private:
    std::vector<Vec3f> verts;
    std::vector<Vec3i> faces;
};
