#include <complex>

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
    if(std::abs<int>(x1-x0)<std::abs<int>(y1-y0))
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


void FillTriangle(Model& model,const Vec3i& face,const Vec3i& face_uv,TGAImage& image,TGAColor color,Vec3f light_dir,
    std::vector<float>& depth_buffer,int texture_idx)
{
    auto& vert_loc0=model.GetVert(face[0]);
    auto& vert_loc1=model.GetVert(face[1]);
    auto& vert_loc2=model.GetVert(face[2]);

    Vec3f screen_locs[3];
    screen_locs[0]=Model2Screen3f(vert_loc0);
    screen_locs[1]=Model2Screen3f(vert_loc1);
    screen_locs[2]=Model2Screen3f(vert_loc2);

    Vec3f vert_uvs[3];
    vert_uvs[0]=model.GetUVVert(face_uv[0]);
    vert_uvs[1]=model.GetUVVert(face_uv[1]);
    vert_uvs[2]=model.GetUVVert(face_uv[2]);
    
    if(screen_locs[0].y>screen_locs[1].y)
    {
        std::swap(screen_locs[0],screen_locs[1]);
        std::swap(vert_uvs[0],vert_uvs[1]);
    }
    if(screen_locs[1].y>screen_locs[2].y)
    {
        std::swap(screen_locs[1],screen_locs[2]);
        std::swap(vert_uvs[1],vert_uvs[2]);
    }
    if(screen_locs[0].y>screen_locs[1].y)
    {
        std::swap(screen_locs[0],screen_locs[1]);
        std::swap(vert_uvs[0],vert_uvs[1]);
    }

    // Vec3f normal=Cross(VertLoc1-VertLoc0,VertLoc2-VertLoc0);
    // normal.Normalize();
    // lightDir.Normalize();
    // float intensity=Dot(normal,lightDir);
    // if(intensity<=0) return;
    // TGAColor actualColor(255*intensity,255*intensity,255*intensity,255);
    //
    float totalHeight=screen_locs[2].y-screen_locs[0].y;
    
    float segmentHeight=screen_locs[1].y-screen_locs[0].y;
    if(int(segmentHeight)!=0)
    {
        for(int y=int(screen_locs[0].y);y<=int(screen_locs[1].y);++y)
        {
            float k0=float(y-screen_locs[0].y)/segmentHeight;
            int x0=int(screen_locs[0].x+(screen_locs[1].x-screen_locs[0].x)*k0);
            float k1=float(y-screen_locs[0].y)/totalHeight;
            int x1=int(screen_locs[0].x+(screen_locs[2].x-screen_locs[0].x)*k1);
            if(x0>x1) std::swap(x0,x1);
            for(int x=x0;x<=x1;++x)
            {
                Vec3f barycentric=Barycentric(screen_locs[0],screen_locs[1],screen_locs[2],x,y);
                if (barycentric.x < 0 || barycentric.y < 0 || barycentric.z < 0 ) continue;
                float z=0;
                Vec2f pixel_uv(0,0);
                for (int i=0; i<3; i++) z += screen_locs[i][2]*barycentric[i];
                for (int i=0; i<3; i++) pixel_uv[0] += vert_uvs[i][0]*barycentric[i];
                for (int i=0; i<3; i++) pixel_uv[1] += vert_uvs[i][1]*barycentric[i];
                if(z>=depth_buffer[x+width*y])
                {
                    depth_buffer[x+width*y]=z;
                    TGAColor color=Sampler(model,texture_idx,pixel_uv);
                    image.set(x,y,color);
                }
                
            }
        }
    }
    segmentHeight=screen_locs[2].y-screen_locs[1].y;
    if(int(segmentHeight)!=0)
    {
        for(int y=int(screen_locs[1].y);y<=int(screen_locs[2].y);++y)
        {
            float k0=float(y-screen_locs[1].y)/segmentHeight;
            int x0=int(screen_locs[1].x+(screen_locs[2].x-screen_locs[1].x)*k0);
            float k1=float(y-screen_locs[0].y)/totalHeight;
            int x1=int(screen_locs[0].x+(screen_locs[2].x-screen_locs[0].x)*k1);
            if(x0>x1) std::swap(x0,x1);
            for(int x=x0;x<=x1;++x)
            {
                Vec3f barycentric=Barycentric(screen_locs[0],screen_locs[1],screen_locs[2],x,y);
                if (barycentric.x < 0 || barycentric.y < 0 || barycentric.z < 0 ) continue;
                float z=0;
                Vec2f pixel_uv(0,0);
                for (int i=0; i<3; i++) z += screen_locs[i][2]*barycentric[i];
                for (int i=0; i<3; i++) pixel_uv[0] += vert_uvs[i][0]*barycentric[i];
                for (int i=0; i<3; i++) pixel_uv[1] += vert_uvs[i][1]*barycentric[i];
                if(z>=depth_buffer[x+width*y])
                {
                    depth_buffer[x+width*y]=z;
                    TGAColor color=Sampler(model,texture_idx,pixel_uv);
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
    if(std::abs(barycentric.z)<1e-2)
    {
        return Vec3f(-1,1,1);
    }
    return Vec3f(barycentric.z-barycentric.u-barycentric.v,barycentric.u,barycentric.v)/barycentric.z;
}

TGAColor Sampler(Model& model,int index,Vec2f uv)
{
    TGAImage& texture=model.GetTexture(index);
    return texture.get(static_cast<int>(uv.u*static_cast<float>(texture.get_width())),
        static_cast<int>(uv.v*static_cast<float>(texture.get_height())));
}