#include "pch.h"
#include "RenderPipe.h"
#include "Vec.h"
#include "Model.h"
#include "tgaimage.h"




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
         
         Model model(projectDir+"african_head.obj");
         model.LoadTexture(projectDir+"african_head_diffuse.tga");
         std::vector<float> depth;
         
         //model space coordination transform 2 screen space coordination，x~[0,width],y~[0,height]
         depth.reserve((width+1)*(height+1));
         for(int i=0;i<width+1;++i)
         {
             for(int j=0;j<height+1;++j)
             {
                 depth.push_back(std::numeric_limits<float>::lowest());
             }
         }
         for(size_t i=0;i<model.FaceSize();++i)
         {
             auto& face=model.GetFace(i);
             auto& face_uv=model.GetUVFace(i);
             //DrawTriangle(model,face,image,white);
             
             FillTriangle(model,face,face_uv,image,white,Vec3f(0,0,1),depth,0);
         }
         image.flip_vertically();
         image.write_tga_file(std::string(projectDir+"output.tga").c_str());
        //  Mat4f mat=LookAt(Vec3f(0,0,-1),Vec3f(0,0,0),Vec3f(0,1,0));
        // auto m=lookat(Vec3f(0,0,-1),Vec3f(0,0,0),Vec3f(0,1,0));
        //  int a=1;
        //  Vec<3,float> v(0.3,0.4,0.5);
        //  Vec<3,int> vt(v);
        //  Mat3f mat={
        //         {2,3,4},
        //         {1,2,2},
        //         {6,5,3}};
        //  // Matrix<3,1,float> rmat={
        //  //   {1},
        //  //     {2},
        //  //     {3}
        //  // };
        //  Vec<3,float> vec(1,2,3);
        //  auto nm=mat*vec;
        // //  for(size_t i=3;i--;)
        // //      for(size_t j=3;j--;mat[i][j]=3);
        // //
        // //  auto id=mat.Identity();
        // // auto nm=mat*id;
        //   int i=1;
     }
     catch (std::runtime_error& e)
     {
         std::cerr<<e.what()<<std::endl;
         return EXIT_FAILURE;
     }
     return EXIT_SUCCESS;
    }
