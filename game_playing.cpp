#include"game_control.h"
#include"game_playing.h"

game_playing::game_playing(){
		/*	vector<int> temp(col);
			for (int i = 0;i < row;i++)
				graph.push_back(temp);*/
			score = 0;
			first = true;
			item = false;
			row = col = 10;
			//step = 20;
			
			
}


void game_playing::setmode(int m){
			int candidate3[10][10] =
		{{-1,0,0,0,0,0,0,0,0,-1},	
		{0,-1,0,0,0,0,0,0,-1,0},
		{0,0,-1,0,0,0,0,-1,0,0},
		{0,0,0,-1,0,0,-1,0,0,0},
		{0,0,0,0,0,-1,0,0,0,0},
	//	{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,-1,0,0,0,0},
		{0,0,0,-1,0,0,-1,0,0,0},
		{0,0,-1,0,0,0,0,-1,0,0},
		{0,-1,0,0,0,0,0,0,-1,0},
		{-1,0,0,0,0,0,0,0,0,-1},
		};

	int candidate2[10][10] =
		{{1, 2, 1, 2, 1, 2, 1, 2, 1, 2},
		{ 3, 1, 3, 4, 3, 4, 3, 4, 3, 4},
		{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
		{-1,-1,-1, 2, 2, 4, 3,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1, 2, 2, 4, 3,-1,-1,-1},
		{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
		{ 3, 4, 3, 4, 3, 4, 3, 4, 3, 4},
		{ 1, 2, 1, 2, 1, 2, 1, 2, 1, 2},
		};
		
	int candidate1[10][10] =
		{{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		};
	mode = m;	
	switch (m){
		case 0 :
			for (int i = 0;i < 10;i++)
				for (int j = 0;j < 10;j++)
					graph[i][j] = candidate1[i][j];
			step = 10;
			target = 1000;
			jam = 0;
			break;
				
		case 1 :
		step = 20;
			for (int i = 0;i < 10;i++)
				for (int j = 0;j < 10;j++)
					graph[i][j] = candidate2[i][j];	
					target = 2000;
					jam = 5;
					break;
		case 2 : 
			step = 30;
			for (int i = 0;i < 10;i++)
				for (int j = 0;j < 10;j++)
					graph[i][j] = candidate3[i][j];
			//item = true;
			target = 5000;
			jam = 10;
			break;
	}
			//mode =;
	generate();
	print();
						//game_start();
}
		
void game_playing::game_start(int p1_x,int p1_y,int p2_x,int p2_y){
	int temp;
	p1.first = p1_x;
	p1.second = p1_y;
	p2.first = p2_x;
	p2.second = p2_y;
		bool flag = true;;
		if (graph[p1.first][p1.second] == -1 || graph[p2.first][p2.second] == -1){
			print();
			return;
		}
				
		if (p1_x == p2_x && abs(p1_y-p2_y)!=1)
			return;
				
		if (p1_y == p2_y && abs(p1_x-p2_x)!=1)
			return;
		if (p1_x == p2_x && p1_y == p2_y)
			return;
				
		if (p1_x != p2_x && p1_y != p2_y)
			return;
				
		temp = graph[p1.first][p1.second];
		graph[p1.first][p1.second] = graph[p2.first][p2.second];
		graph[p2.first][p2.second] = temp;
		print();
		sleep(2);
		eliminating();
		if (!eliminate.empty()){
			drop();
			print();
			//flag = false;
			while(flag){
				eliminating();
				if (eliminate.empty()){
					if (is_dead()){
						generate();
						print();
					}
					flag = false;
				}
				else{
					drop();
					print();
				}
			}
			step--;
		}
		else{
			temp = graph[p1.first][p1.second];
			graph[p1.first][p1.second] = graph[p2.first][p2.second];
			graph[p2.first][p2.second] = temp;
			print();
		}
}


void game_playing::print(){
	for (int i = 0;i < row;i ++){
		for (int j = 0;j < 10;j++){
		
			switch(graph[i][j]){
				case 0 :
					if (jam_graph[i][j]){
						attron(COLOR_PAIR(5));
						mvprintw(10+i,20+j,"%c",'B' );
						attroff(COLOR_PAIR(5));
					}
					else{
						attron(COLOR_PAIR(10));
						//mvprintw(i,j,"%d",graph[i][j]);
						mvprintw(10+i,20+j,"%c",'B' );
						attroff(COLOR_PAIR(10));
						//mvprintw(i,j,"%c",'B' );
					}
					break;
				case 1 :
					if (jam_graph[i][j]){
							attron(COLOR_PAIR(6));
							mvprintw(10+i,20+j,"%c",'Y' );
							attroff(COLOR_PAIR(6));
					}
					else{
						attron(COLOR_PAIR(1));
						//mvprintw(i,j,"%d",graph[i][j]);
						mvprintw(10+i,20+j,"%c",'Y' );
						attroff(COLOR_PAIR(1));	
						//mvprintw(i,j,"%c",'Y' );
					}
					break;
				case 2 :
					if (jam_graph[i][j]){
						attron(COLOR_PAIR(7));
						mvprintw(10+i,20+j,"%c",'W' );
						attroff(COLOR_PAIR(7));
					}
					else{
						attron(COLOR_PAIR(2));
						mvprintw(10+i,20+j,"%c",'W' );
						//mvprintw(i,j,"%d",graph[i][j]);
						attroff(COLOR_PAIR(2));	
						//mvprintw(i,j,"%c",'W' );
					}
					break;
				case 3 :
					if (jam_graph[i][j]){
						attron(COLOR_PAIR(8));
						mvprintw(10+i,20+j,"%c",'G' );
						attroff(COLOR_PAIR(8));
					}
					else{
						attron(COLOR_PAIR(3));
						//mvprintw(i,j,"%d",graph[i][j]);
						mvprintw(10+i,20+j,"%c",'G' );
						attroff(COLOR_PAIR(3));
						//mvprintw(i,j,"%c",'G' );
					}
					break;
				case 4 :
					if (jam_graph[i][j]){
						attron(COLOR_PAIR(9));
						mvprintw(10+i,20+j,"%c",'R' );
						attroff(COLOR_PAIR(9));
					}
					else{
						attron(COLOR_PAIR(4));
						mvprintw(10+i,20+j,"%c",'R' );	
						//mvprintw(i,j,"%d",graph[i][j]);
						attroff(COLOR_PAIR(4));	
						//mvprintw(i,j,"%c",'R' );		
					}							
					break;
				case -1 : 
					mvprintw(10+i,20+j,"%c",' ' );
					break;
				case -2 :
					mvprintw(10+i,20+j,"%c",'!' );
				
				}
		}
		refresh();
	}
	refresh();
			//sleep(20);
			//cout << is_dead();	
}


void game_playing::generate(){
	bool flag = true;
	while(flag){
		for (int i = 0;i < row;i++){
			for (int j = 0;j < col;j++){
				if (graph[i][j] == -1 )
					continue;
				else
					graph[i][j] = rand()%5;
			}
		}
		
		//test = false;
			/*graph[0][0] = 1;
			graph[0][1] = 7;
			graph[0][2] = 8;
			graph[1][0] = 1;
			graph[1][1] = 8;
			graph[1][2] = 1;
			graph[2][0] = 4;
			graph[2][1] = 1;
			graph[2][2] = 4;*/

			
			/*while (item){			
				i = rand() % 10;
				j = rand() %10;
				if (graph[i][j] == -1)
					continue;
				else{
					graph[i][j] = -2;
					break;
				}
				
				
			}*/
			
		if ((!is_dead()) && origin_can_eliminate()){
			//sleep(20);
			//		cout << is_dead(); //<< can_eliminate();
			flag = false;
		}
		/*else{
			//sleep(20);
			//break;
			clear();
			refresh();
			sleep(1);
			mvprintw(0,0,"dead");
			refresh();
			sleep(1);
		}*/
		
				//cout << is_dead();
	}
			int i=0,j=0;
			
			
	if (first) {
		int temp = jam;
				
		while (temp){
			i = rand()%10;
			j = rand()%10;
			if (graph[i][j] == -1 || jam_graph[i][j] == 1)
				continue;
			else{
				jam_graph[i][j] = 1;
				temp--;
			}
					
		}
	}
			
	if (first == true)
		first = false;
			
}
	
void game_playing::drop(){
	pair<int,int> temp;
	int init;
	int pivot;
	int tag = 1;
	int init_num = eliminate.size();
	while(!eliminate.empty()){
		temp = eliminate.front();
		eliminate.pop();
		//cout << temp.first << temp.second << endl;
		init = temp.first;
		pivot = temp.first - 1 ;
		for (int i = 0;i < temp.first;i++){
			if (graph[init][temp.second] == -1){
				init--;
				i--;
				continue;
			}
			if (graph[pivot][temp.second] == -1){
				pivot--;
				continue;
			}

			graph[init][temp.second] = graph[pivot][temp.second];
			init--;
			pivot--;
		}
		while (graph[init][temp.second] == -1)
			init--;
		graph[init][temp.second] = rand()%5;
		score+= 20;
			//	mvprintw(0,20,"score : %d  step : %d",score,step);
				//if (init_num)
				//print();
			//	sleep(2);
				
				/*for(int i = 0;i < 10;i++){
					cout << setw(2) << graph[i][temp.second]<< endl;
				}*/
	}
	mvprintw(0,20,"score : %4d\n",score);
	mvprintw(1,20,"step : %2d\n ",step);
	mvprintw(2,20,"target : %4d\n",target);
	mvprintw(3,20,"remain jam : %2d\n",jam);

	refresh();
	print();
	sleep(2);
}

void game_playing::eliminating(){
	int up = 0;
	int down = 0;
	int left = 0;
	int right = 0;
	int tempx ;
	int tempy;
	set<pair<int,int>> contain;
	//cout << graph[2][0] << graph[2][1];
	for (int i = 0;i < row;i++){
		for (int j = 0;j < col;j++){
			if (graph[i][j] == -1)
				continue;
		    up = 0;
			down = 0;
			left = 0;
			right = 0;
			tempx = i;
			tempy = j;
					
			//up
			while (((tempx-1) >= 0) && (graph[tempx-1][j] == graph[i][j])){
				up++;
				tempx--;
			}
						
			tempx = i;
			tempy = j;
					
			//down
			while (((tempx+1) < row) && (graph[tempx+1][j] == graph[i][j])){
						
				down++;
				tempx++;
			}
					
			if ((up + down) >= 2){
			//	cout << up << down;
				while(up){
					if (!contain.count({i-up,j})){
						contain.insert({i-up,j});
						eliminate.push({i-up,j});
						if (jam_graph[i-up][j] == 1){
							jam_graph[i-up][j] = 0;
							jam--;
						}
									
								//cout << i-up <<j<< endl;
					}
					up--;
				}
				if (!contain.count({i,j})){
					contain.insert({i,j});	
					eliminate.push({i,j});	
					if (jam_graph[i][j] == 1){
							jam_graph[i][j] = 0;
							jam--;
					}
						//cout << i <<j;
				}
											
				int counter = 1;
				while(down){
							
					if (!contain.count({i+counter,j})){
						contain.insert({i+counter,j});
						eliminate.push({i+counter,j});
						if (jam_graph[i+counter][j] == 1){
							jam_graph[i+counter][j] = 0;
							jam--;
						}
						//cout << i+counter<<j<<endl;
					}
					down--;
					counter++;
				}
			
				
			}
					
					
					
			tempx = i;
			tempy = j;
					
			//left
			while (((tempy-1) >= 0) && (graph[i][tempy-1] == graph[i][j])){
				left++;
				tempy--;
			}
					
			tempx = i;
			tempy = j;
					
			//right
			while (((tempy+1) < col) && (graph[i][tempy+1] == graph[i][j])){
				right++;
				tempy++;
			}
					
			if ((left + right) >= 2){
					//	cout << i << j;
				while(left){
					if (!contain.count({i,j-left})){
						contain.insert({i,j-left});
						eliminate.push({i,j-left});		
					}
					if (jam_graph[i][j-left] == 1){
							jam_graph[i][j-left] = 0;
							jam--;
						}
					left--;
				}
		
				if (!contain.count({i,j})){
					contain.insert({i,j});
					eliminate.push({i,j});
					if (jam_graph[i][j] == 1){
						jam_graph[i][j] = 0;
						jam--;
					}
				}	
						
				while(right){
					if (!contain.count({i,j+right})){
						contain.insert({i,j+right});
						eliminate.push({i,j+right});
						if (jam_graph[i][j+right] == 1){
							jam_graph[i][j+right] = 0;
							jam--;
						}
					}
					right--;
							
				}
			
				}
					
					
		}
	}	
			
			/*
			right = 1;
			down = 0;
			set<pair<int,int>> special;
			
			for (int i = 0;i < 10;i++){
				for (int j = 0;j < 10;j++){
					if (contain.count({i,j})){
						while (contain.count{i,j+1}){
							
							
							
						}
					}
						
					
					
				}
			}
			*/
			
			
}

bool game_playing::origin_can_eliminate(){
	int up = 0;
	int down = 0;
	int left = 0;
	int right = 0;
	int tempx ;
	int tempy;
	//cout << graph[2][0] << graph[2][1];
	for (int i = 0;i < row;i++){
		for (int j = 0;j < col;j++){
			if (graph[i][j] == -1)
				continue;
		    up = 0;
			down = 0;
			left = 0;
			right = 0;
			tempx = i;
			tempy = j;
					
			//up
			while (((tempx-1) >= 0) && (graph[tempx-1][j] == graph[i][j])){
				up++;
				tempx--;
			}
						
			tempx = i;
			tempy = j;
					
			//down
			while (((tempx+1) < row) && (graph[tempx+1][j] == graph[i][j])){
						
				down++;
				tempx++;
			}
					
			if ((up + down) >= 2){
			//	cout << up << down;
				return false;
				/*while(up){
					if (!contain.count({i-up,j})){
						contain.insert({i-up,j});
					}
					up--;
				}
						
						while(down){
							if (!contain.count({i+down,j})){
								contain.insert({i+down,j});
							}
							down--;
							
						}
			
						contain.insert({i,j});	*/		
			}
					
					
					
			tempx = i;
			tempy = j;
					
			//left
			while (((tempy-1) >= 0) && (graph[i][tempy-1] == graph[i][j])){
				left++;
				tempy--;
			}
					
			tempx = i;
			tempy = j;
					
			//right
			while (((tempy+1) < col) && (graph[i][tempy+1] == graph[i][j])){
				right++;
				tempy++;
			}
					
			if ((left + right) >= 2){
					//	cout << i << j;
				return false;
						/*while(left){
							if (!contain.count({i,j-left})){
								contain.insert({i,j-left});
							}
							left--;
						}
						
						while(right){
							if (!contain.count({i,j+right})){
								contain.insert({i,j+right});
							}
							right--;
							
						}
			
						if (!contain.count({i,j})){
							contain.insert({i,j});
						}*/	
			}
					
					
		}
	}	
	return true;
}
		
		
bool game_playing::is_dead(){
	//case1
	for (int i = 0;i < row;i++){
		for (int j = 0;j < col;j++){
			if (graph[i][j] == -1)
				continue;
			if ( (i < (row-1)) && (graph[i+1][j] == graph[i][j])  ){ // case1
				if (((i-1) >= 0) && ((j-1) >= 0) && (graph[i-1][j-1] == graph[i][j]) && (graph[i-1][j] != -1)) /*&& (graph[i-1][j-1] != -1)*/ {//左上
				//	cout << 1;
				//cout << i << j<< endl;
					return false;
				}
						
				if (((i+2) < row) && ((j-1) >= 0) && (graph[i+2][j-1] == graph[i][j]) &&(graph[i+2][j] != -1)/*&& (graph[i+2][j-1] != -1) */){//左下
				//	cout << 2;
				//	cout << i << j<< endl;
					return false;
				}
				if (((i-1) >= 0) && ((j+1) < col) && (graph[i-1][j+1] == graph[i][j]) && (graph[i-1][j] != -1)/* && (graph[i-1][j+1] != -1)*/){//右上
				//	cout << 3;
				//	cout << i << j<< endl;
					return false;	
				}
				if (((i+2) < row) && ((j+1) < col) && (graph[i+2][j+1] == graph[i][j]) && (graph[i+2][j] != -1)/*&& (graph[i+2][j+1] != -1)*/){//右下
				//	cout << 4;
				//	cout << i << j<< endl;
					return false;
				}
			}
					
					
			if ((i != 0&& j != 0) && ((i != 0) && (j != col-1)) && ((i != row-1) && (j != 0)) && ((i != row-1) && (j != col-1))){//case2
				if (((i-1) >= 0)  && ((j-1)>=0)  &&  ((i-1) >= 0)  && ((j+1) < col) && (graph[i-1][j-1] == graph[i][j]) && (graph[i-1][j+1] == graph[i][j]) && (graph[i-1][j] != -1)){//上二
				//	cout << 5;
				//	cout << i << j<< endl;
					return false;
				}
				if (((i-1) >= 0)  && ((j-1)>=0)  &&  ((i+1) < row)  && (graph[i-1][j-1] == graph[i][j]) && (graph[i+1][j-1] == graph[i][j]) && (graph[i][j-1] != -1)){//左二
				//	cout << 6 << i << j;
				//	cout << i << j<< endl;
					return false;
				}
				if (((i+1) < row)  && ((j+1) < col)  &&  ((i-1) >= 0)  && ((j+1) < col) && (graph[i+1][j+1] == graph[i][j]) && (graph[i-1][j+1] == graph[i][j]) && (graph[i][j+1] != -1)){//右二
				//	cout <<7;
				///	cout << i << j<< endl;
					return false;
				}
				if (((i+1) < row)  && ((j+1) < col)  &&  ((i+1) < row)  && ((j-1) >= 0) && (graph[i+1][j+1] == graph[i][j]) && (graph[i+1][j-1] == graph[i][j]) && (graph[i+1][j] != -1) ){//下二
				//	cout <<8;
				//	cout << i << j<< endl;
					return false;
				}
			}
					
					
			if ((j < (col-1)) && (graph[i][j+1] == graph[i][j])){//case3
				if (((i-1) >= 0) && ((j-1) >= 0) && (graph[i-1][j-1] == graph[i][j]) && (graph[i][j-1] != -1)){//左上
				//	cout <<9;
				//	cout << i << j<< endl;
					return false;
				}
				if (((i+1) < row) && ((j-1) >= 0) && (graph[i+1][j-1] == graph[i][j]) && (graph[i][j-1] != -1)){//左下
					//cout << 10;
					//	cout << i << j<< endl;
					return false;
				}
				if (((i-1) >= 0) && ((j+2) < col) && (graph[i-1][j+2] == graph[i][j]) && (graph[i][j+2] != -1)){//右上
				//	cout <<11;
				//	cout << i << j<< endl;
					return false;	
				}
				if (((i+1) < row) && ((j+2) < col) && (graph[i+1][j+2] == graph[i][j]) && (graph[i][j+2] != -1)){//右下
				//	cout << 12;
				//	cout << i << j<< endl;
					return false;
				}
			}		
		}
	}
			
		return true;
}