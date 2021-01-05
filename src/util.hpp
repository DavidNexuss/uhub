#pragma once
#define DEBUG
#ifdef DEBUG
#include <iostream>

#define LOG(...) std::cerr << __FILE__ << ":" << __LINE__ << "-> "; fprintf( stderr, __VA_ARGS__); std::cerr << std::endl;
#define EVAL(x) std::cerr << __FILE__ << ":" << __LINE__ << "-> " << # x " = " << (x) << std::endl
#define ERR(...) std::cerr << "\033[0;33m" << __FILE__ << ":" << __LINE__ << "-> "; fprintf( stderr, __VA_ARGS__); std::cerr << << "\033[0m" << std::endl;
#else
#define LOG(...)
#define EVAL(x)
#define ERR(...)
#endif