#include "Model.h"

#include <fstream>
#include <sstream>
#include <string>

Model::Model(const char* inPath)
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
            else if(line.substr(0,2)=="f ")
            {
                char trash;
                iss>>trash;
                Vec3i face;
                int itrash;
                for(size_t i=0;i<3;++i)
                {
                    int index;
                    iss>>index>>trash>>itrash>>trash>>itrash;
                    --index;  //obj索引从1开始，这里减去1
                    face[i]=index;
                }
                faces.push_back(face);
            }
        }
        
    }
    else
    {
        throw std::runtime_error("Open file failed!");
    }
}
