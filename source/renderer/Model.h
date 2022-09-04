#pragma once
#include <vector>

#include "Vec.h"

#include <direct.h>

#include "tgaimage.h"

inline static std::string GetProjectDir()
{
    char buffer[256];
    char* dicPath = _getcwd(buffer, sizeof(buffer));
    char* ret=dicPath;
    for(;*dicPath!='\0';++dicPath)
    {
        if(*dicPath=='\\')
            *dicPath='/';
    }
    return std::string(ret)+"/../source/renderer/";
}
static const std::string& projectDir=GetProjectDir();

class Model
{
public:
    Model(const std::string& inPath);
    int LoadTexture(const std::string& file_name);
    size_t VertSize(){return verts.size();}
    size_t FaceSize(){return faces.size();}
    
    inline const Vec3f& GetVert(size_t index)const{return verts[index];}
    inline Vec3f& GetVert(size_t index){return const_cast<Vec3f&>(static_cast<const Model&>(*this).GetVert(index));}
    
    inline const Vec3i& GetFace(size_t index)const{return faces[index];}
    inline Vec3i& GetFace(size_t index){return const_cast<Vec3i&>(static_cast<const Model&>(*this).GetFace(index));}
    
    inline const Vec3i& GetUVFace(size_t index)const{return faces_uv[index];}
    inline Vec3i& GetUVFace(size_t index){return const_cast<Vec3i&>(static_cast<const Model&>(*this).GetUVFace(index));}
    
    inline const Vec3f& GetUVVert(size_t index)const{return verts_uv[index];}
    inline Vec3f& GetUVVert(size_t index){return const_cast<Vec3f&>(static_cast<const Model&>(*this).GetUVVert(index));}
    
    inline const TGAImage& GetTexture(size_t index)const{assert(index<textures.size());return textures[index];}
    inline TGAImage& GetTexture(size_t index){return const_cast<TGAImage&>(static_cast<const Model&>(*this).GetTexture(index));}
private:
    // model vert coordination
    std::vector<Vec3f> verts;
    // model vert indexes
    std::vector<Vec3i> faces;
    // model uv vert indexes
    std::vector<Vec3i> faces_uv;
    // model uv vert coordination
    std::vector<Vec3f> verts_uv;
    std::vector<TGAImage> textures;
};
