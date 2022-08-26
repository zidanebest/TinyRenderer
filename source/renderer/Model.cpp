#include "Model.h"

#include <fstream>
#include <sstream>
#include <string>

#include "tgaimage.h"


Model::Model(const std::string& inPath)
{
    std::ifstream ifs(inPath,std::ifstream::in);
    if(ifs.is_open())
    {
        std::string line;
        while(std::getline(ifs,line))
        {
            std::istringstream iss(line);
            if(line.substr(0,2)=="v ")
            {
                char trash;
                iss>>trash;
                Vec3f vert;
                iss>>vert;
                verts.push_back(vert);
            }
            else if(line.substr(0,3)=="vt ")
            {
                char trash;
                iss>>trash>>trash;
                Vec3f vert_uv;
                iss>>vert_uv;
                verts_uv.push_back(vert_uv);
            }
            else if(line.substr(0,2)=="f ")
            {
                char trash;
                iss>>trash;
                Vec3i face_idx;
                Vec3i face_uv_idx;
                int itrash;
                for(size_t i=0;i<3;++i)
                {
                    int index;
                    int index_uv;
                    iss>>index>>trash>>index_uv>>trash>>itrash;
                    --index;  //obj索引从1开始，这里减去1
                    --index_uv;
                    face_idx[i]=index;
                    face_uv_idx[i]=index_uv;
                }
                faces.push_back(face_idx);
                faces_uv.push_back(face_uv_idx);
            }
        }
    }
    else
    {
        throw std::runtime_error("open file failed!");
    }
}

int Model::LoadTexture(const std::string& file_name)
{
    TGAImage image;
    if(image.read_tga_file(file_name.c_str()))
    {
        image.flip_vertically();
        textures.push_back(image);
        return static_cast<int>(textures.size()-1);
    }
    return -1;
}

