#ifndef GAME_CONTROL 
#define GAME_CONTROL
#include"game_playing.h"
#include<iostream>
#include<ncurses.h>
#include<vector>
#include<set>
#include<queue>
#include<ctime>
#include<cmath>
#include<utility>
#include<bits/stdc++.h> 
#include<unistd.h>
#include<iomanip>
using namespace std;
class game_control{
	public :
		int mode;
		bool s ;
		bool win ;
		bool quit ;
		game_playing token;
		game_control();
		void start_screen(int);
		void game_final();
		void game_loop();
		void select();
};
#endif