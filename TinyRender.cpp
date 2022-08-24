#include <cassert>
#include <future>
#include <iostream>
#include <sstream>

#include "Math.hpp"
#include "Model.h"
#include "tgaimage.h"

const TGAColor white=TGAColor(255,255,255,255);
const TGAColor red=TGAColor(255,0,0,255);
const int width=400;
const int height=300;

Vec2f Model2Screen(Vec3f vert)
{
    return Vec2f((vert.x+1)*width/2.0f,(vert.y+1)*height/2.0f);
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
template<class T>
struct str
{
    T Print()
    {
      return data;  
    }
    T data;
};
int main(int argc, char* argv[])
{
    try
    {
        TGAImage image(width,height,TGAImage::RGB);
        Model model("africanHead.obj");
        for(size_t i=0;i<model.FaceSize();++i)
        {
            auto& face=model.GetFace(i);
            for(int index=0;index<3;++index)
            {
                auto Loc1=Model2Screen(model.GetVert(face[index]));
                auto Loc2=Model2Screen(model.GetVert(face[(index+1)%3]));
                DrawLine(Loc1.x,Loc2.x,Loc1.y,Loc2.y,image,white);
            }
        }
        image.flip_vertically();
        image.write_tga_file("output.tga");  
    }
    catch (std::runtime_error& e)
    {
        std::cerr<<e.what()<<std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
    
}
