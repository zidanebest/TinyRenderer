#include <cassert>
#include <future>
#include <iostream>
#include <sstream>


#define Assert(condition,info) if(!condition){ std::cout<<info<<std::endl;__debugbreak();}
