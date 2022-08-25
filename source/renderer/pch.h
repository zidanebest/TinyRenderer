#include <cassert>
#include <future>
#include <iostream>
#include <sstream>


#define Assert(condition,info) if(!condition) throw std::runtime_error(info);