#include "pch.h"
#include "Math.hpp"
#include "Model.h"
#include "tgaimage.h"


const TGAColor white=TGAColor(255,255,255,255);
const TGAColor red=TGAColor(255,0,0,255);
const int width=1200;
const int height=1200;

Vec3f Barycentric(const Vec3f& inVert0,const Vec3f& inVert1,const Vec3f& inVert2,int inPosx,int inPosy);
TGAColor Sampler(Model& model,int index,Vec2f uv);

Vec2i Model2Screen2i(Vec3f vert)
{
    return Vec2i(int((vert.x+1)*width/2.0f+0.5f),int((vert.y+1)*height/2.0f+0.5f));
}
Vec3f Model2Screen3f(Vec3f vert)
{
    return Vec3f(int((vert.x+1)*width/2.0f+0.5f),int((vert.y+1)*height/2.0f+0.5f),vert.z);
}
void DrawLine(int x0,int x1,int y0,int y1,TGAImage& image,TGAColor color)
{
    bool hasSwap=false;
    if(std::abs(x1-x0)<std::abs(y1-y0))
    {
        std::swap(x0,y0);
        std::swap(x1,y1);
        hasSwap=true;
    }
    if(x0>x1)
    {
        std::swap(x0,x1);
        std::swap(y0,y1);
    }
    for(int x=x0;x<=x1;++x)
    {
        float k=static_cast<float>(y1-y0)/static_cast<float>(x1-x0);
        int y=k*(x-x0)+y0;
        if(hasSwap)
            image.set(y,x,color);
        else
            image.set(x,y,color);
    }
}

void DrawTriangle(const Model& inModel,const Vec3i& inFace,TGAImage& image,TGAColor color)
{
    for(int index=0;index<3;++index)
    {
        auto Loc1=Model2Screen2i(inModel.GetVert(inFace[index]));
        auto Loc2=Model2Screen2i(inModel.GetVert(inFace[(index+1)%3]));
        DrawLine(Loc1.x,Loc2.x,Loc1.y,Loc2.y,image,white);
    }
}
Vec3f Barycentric(Vec3f A, Vec3f B, Vec3f C, Vec3f P) {
    Vec3f s[2];
    for (int i=2; i--; ) {
        s[i][0] = C[i]-A[i];
        s[i][1] = B[i]-A[i];
        s[i][2] = A[i]-P[i];
    }
    Vec3f u = Cross(s[0], s[1]);
    if (std::abs(u[2])>1e-2) // dont forget that u[2] is integer. If it is zero then triangle ABC is degenerate
        return Vec3f(1.f-(u.x+u.y)/u.z, u.y/u.z, u.x/u.z);
    return Vec3f(-1,1,1); // in this case generate negative coordinates, it will be thrown away by the rasterizator
}
void FillTriangle(Model& inModel,const Vec3i& inFace,const Vec3i& face_uv,TGAImage& image,TGAColor color,Vec3f lightDir,
    std::vector<float>& depthBuffer,int texture_idx)
{
    auto& VertLoc0=inModel.GetVert(inFace[0]);
    auto& VertLoc1=inModel.GetVert(inFace[1]);
    auto& VertLoc2=inModel.GetVert(inFace[2]);

    auto& vert_uv0=inModel.GetUVVert(face_uv[0]);
    auto& vert_uv1=inModel.GetUVVert(face_uv[1]);
    auto& vert_uv2=inModel.GetUVVert(face_uv[2]);
    
    auto ScreenLoc0=Model2Screen3f(VertLoc0);
    auto ScreenLoc1=Model2Screen3f(VertLoc1);
    auto ScreenLoc2=Model2Screen3f(VertLoc2);
    
    if(ScreenLoc0.y>ScreenLoc1.y)
    {
        std::swap(ScreenLoc0,ScreenLoc1);
        std::swap(vert_uv0,vert_uv1);
    }
    if(ScreenLoc1.y>ScreenLoc2.y)
    {
        std::swap(ScreenLoc1,ScreenLoc2);
        std::swap(vert_uv1,vert_uv2);
    }
    if(ScreenLoc0.y>ScreenLoc1.y)
    {
        std::swap(ScreenLoc0,ScreenLoc1);
        std::swap(vert_uv0,vert_uv1);
    }

    // Vec3f normal=Cross(VertLoc1-VertLoc0,VertLoc2-VertLoc0);
    // normal.Normalize();
    // lightDir.Normalize();
    // float intensity=Dot(normal,lightDir);
    // if(intensity<=0) return;
    // TGAColor actualColor(255*intensity,255*intensity,255*intensity,255);
    //
    float totalHeight=ScreenLoc2.y-ScreenLoc0.y;
    
    float segmentHeight=ScreenLoc1.y-ScreenLoc0.y;
    if(int(segmentHeight)!=0)
    {
        for(int y=int(ScreenLoc0.y);y<=int(ScreenLoc1.y);++y)
        {
            float k0=float(y-ScreenLoc0.y)/segmentHeight;
            int x0=int(ScreenLoc0.x+(ScreenLoc1.x-ScreenLoc0.x)*k0);
            float k1=float(y-ScreenLoc0.y)/totalHeight;
            int x1=int(ScreenLoc0.x+(ScreenLoc2.x-ScreenLoc0.x)*k1);
            if(x0>x1) std::swap(x0,x1);
            for(int x=x0;x<=x1;++x)
            {
                Vec3f barycentric=Barycentric(ScreenLoc0,ScreenLoc1,ScreenLoc2,x,y);
                if(barycentric.u<0||barycentric.v<0||barycentric.u+barycentric.v>1)
                    continue;
                float z         =   VertLoc0.z*(1-barycentric.u-barycentric.v)+VertLoc1.z*barycentric.u+VertLoc2.z*barycentric.v;
                float frag_u    =   vert_uv0.u*(1-barycentric.u-barycentric.v)+vert_uv1.u*barycentric.u+vert_uv2.u*barycentric.v;
                float frag_v    =   vert_uv0.v*(1-barycentric.u-barycentric.v)+vert_uv1.v*barycentric.u+vert_uv2.v*barycentric.v;
                if(z>depthBuffer[x+width*y])
                {
                    depthBuffer[x+width*y]=z;
                    TGAColor color=Sampler(inModel,texture_idx,Vec2f(frag_u,frag_v));
                    image.set(x,y,color);
                }
                
            }
        }
    }
    segmentHeight=ScreenLoc2.y-ScreenLoc1.y;
    if(int(segmentHeight)!=0)
    {
        for(int y=int(ScreenLoc1.y);y<=int(ScreenLoc2.y);++y)
        {
            float k0=float(y-ScreenLoc1.y)/segmentHeight;
            int x0=int(ScreenLoc1.x+(ScreenLoc2.x-ScreenLoc1.x)*k0);
            float k1=float(y-ScreenLoc0.y)/totalHeight;
            int x1=int(ScreenLoc0.x+(ScreenLoc2.x-ScreenLoc0.x)*k1);
            if(x0>x1) std::swap(x0,x1);
            for(int x=x0;x<=x1;++x)
            {
                Vec3f barycentric=Barycentric(ScreenLoc0,ScreenLoc1,ScreenLoc2,x,y);
                if(barycentric.u<0||barycentric.v<0||barycentric.u+barycentric.v>1)
                    continue;
                float z         =   VertLoc0.z*(1-barycentric.u-barycentric.v)+VertLoc1.z*barycentric.u+VertLoc2.z*barycentric.v;
                float frag_u    =   vert_uv0.u*(1-barycentric.u-barycentric.v)+vert_uv1.u*barycentric.u+vert_uv2.u*barycentric.v;
                float frag_v    =   vert_uv0.v*(1-barycentric.u-barycentric.v)+vert_uv1.v*barycentric.u+vert_uv2.v*barycentric.v;
                
                if(z>depthBuffer[x+width*y])
                {
                    depthBuffer[x+width*y]=z;
                    TGAColor color=Sampler(inModel,texture_idx,Vec2f(frag_u,frag_v));
                    image.set(x,y,color);
                }
                
            }
        }
    }
}

Vec3f Barycentric(const Vec3f& inVert0,const Vec3f& inVert1,const Vec3f& inVert2,int inPosx,int inPosy)
{
    Vec3f barycentric=Cross(Vec3f(inVert1.x-inVert0.x,inVert2.x-inVert0.x,inVert0.x-inPosx),
        Vec3f(inVert1.y-inVert0.y,inVert2.y-inVert0.y,inVert0.y-inPosy));
    if(std::abs(barycentric.z)<1e-5)
    {
        return Vec3f(-1,1,1);
    }
    return barycentric/barycentric.z;
}

TGAColor Sampler(Model& model,int index,Vec2f uv)
{
    TGAImage& texture=model.GetTexture(index);
    Vec2i uvwh(uv[0]*texture.get_width(), uv[1]*texture.get_height());
    TGAColor color= texture.get(uvwh[0],uvwh[1]);
    return color;
    return texture.get(static_cast<int>(uv.u*static_cast<float>(texture.get_width())),
        static_cast<int>(uv.v*static_cast<float>(texture.get_height())));
}