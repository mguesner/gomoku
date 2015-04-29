#ifndef GOMOKU_HPP
#define GOMOKU_HPP
#include <vector>

#include <chrono>
#include <iostream>


enum eState
{
	NONE = 0,
	BLACK,
	WHITE
};

#define TIMEOUT 1
#define DEFAULT_MY_BEST -100000000
#define DEFAULT_ENEMY_BEST 100000000
#define ALPHA_START -300000
#define BETA_START 300000
#define MAXDEPTH 15
typedef std::chrono::time_point<std::chrono::system_clock,std::chrono::duration<long long, std::ratio<1, 1000000> >> Timer;
#endif
