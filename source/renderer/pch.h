#include <cassert>
#include <future>
#include <iostream>
#include <sstream>


#define Assert(condition,info) if(!(condition)){ std::cout<<info<<std::endl;__debugbreak();}
#define PRAGMA_OPT_DISABLE #pragma optimize( "", off)
#define PRAGMA_OPT_ENAGLE  #pragma optimize( "", on)