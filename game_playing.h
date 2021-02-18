#ifndef GAME_PLAYING 
#define GAME_PLAYING
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



class game_playing{
	public :
		//bool test = true;
		pair<int,int> p1,p2;
		int score;
		int step;
		int mode;
		int target;
		bool first ;
		bool item ;
		queue<pair<int,int>> eliminate;
		//vector<vector<int>> graph;
		int row ;
		int col ;
		int  graph[10][10];
		int jam_graph[10][10] = {0};
		int jam;
		game_playing();		
		void setmode(int );	
		void game_start(int ,int ,int ,int);
		void print();
		void generate();
		void drop();
		void eliminating();	
		bool origin_can_eliminate();
		bool is_dead();
	
	
	
};
#endif