#include"game_control.h"
#include"game_playing.h"

game_control::game_control(){
	s = true;
	win = false;
	quit = false;
	initscr();
	cbreak();
	noecho();
	keypad(stdscr,TRUE);
	start_screen(2);
	start_color();			
	select();
			
	token.setmode(mode);
	game_loop();
	game_final();
}

void game_control::start_screen(int i){
	while(i--){
		erase();
		printw("\n\n\n\n\n\n");
		printw("                             Welcome to play Candy Crush game ~                                  \n\n");
		printw("         w  c(..)o___                   /|__/|                           ,-.__.-,                           \n");
		printw("          \\__(-) /   \\  	      / 0,0  |                         (``-''-//).___..--'''`-._           \n");
		printw("           w__/\\/     \\             /_____   |                          `6_ 6  )   `-.  (     ).`-.__.`)   \n");
		printw("             _(_)                  /^ ^ ^ \\  |                         (_Y_.)'  ._   )  `._ `. ``-..-'    \n");
		printw("            /   \\                 |^ ^ ^ ^ |w|                     _..`--'_..-_/  /--'_.' ,'               \n");
		printw("           m    m                  \\m___m__|_|                   (il),-''  (li),'  ((!.-'                 \n");
		printw("                                                                                                 \n");
		printw("             EASY                      Medium                                   HARD                     \n");
		refresh();
		sleep(1);
		erase();
		printw("\n\n\n\n\n\n");
		printw("                             Welcome to play Candy Crush game ~                                  \n\n");
		printw("         w  c(@@)o___                   /|__/|                           ,-.__.-,                           \n");
		printw("          \\__(-) /   \\  	      / -,-  |                         (``-''-//).___..--'''`-._           \n");
		printw("           w__/\\/     \\             /_____   |                          `m_ m  )   `-.  (     ).`-.__.`)   \n");
		printw("             _(_)                  /^ ^ ^ \\  |                         (_Y_.)'  ._   )  `._ `. ``-..-'    \n");
		printw("            /   \\                 |^ ^ ^ ^ |w|                     _..`--'_..-_/  /--'_.' ,'               \n");
		printw("           m    m                  \\m___m__|_|                   (il),-''  (li),'  ((!.-'                 \n");
		printw("                                                                                                 \n");
		printw("             EASY                      Medium                                   HARD                     \n");
		refresh();
		sleep(1);
	}		

}

		
void game_control::game_final(){
	clear();
	if (quit == true)
		mvprintw(0,20,"                   You press quit ");
			
	else if (win == false)
		mvprintw(0,20,"                   Oh no, you lose it~            ");
	else if (win == true)
		mvprintw(0,20,"                   Congratulations !!! you are Candy Crush professor~   ");
	refresh();
	sleep(5);
	endwin();
			
}



void game_control::game_loop(){
	int instruction;
	int x=0, y = 0;
	int pre_x = 0,pre_y = 0;
	int p1_x,p1_y,p2_x,p2_y;
	int time = 0;


	while(1){	
	mvprintw(0,20,"score : %4d\n",token.score);
	mvprintw(1,20,"step : %2d\n ",token.step);
	mvprintw(2,20,"target : %4d\n",token.target);
	mvprintw(3,20,"remain jam : %2d\n",token.jam);
	mvprintw(4,20,"press q to quit");
	mvprintw(5,20,"press s to start");
	refresh();			
				/*if (token.item == false && token.score >= token.target){
					win = true;
				}*/
				
				/*for (int i = 0;i < 10;i++){
					if (token.graph[9][i] == -2){
						win = true;
					}
				}*/
				
		if (token.jam == 0 && token.score >= token.target){
			win = true;
			break;
		}
				
		if (token.step <= 0){
			break;
		}
				
		move(10+x,20+y);
		instruction = getch();
		switch(instruction){
			case KEY_LEFT :
				if (--y < 0)
					y += 10;
					break;
			case KEY_RIGHT :
				if (++y > 10-1)
					y = 0;
					break;
			case KEY_UP :
				if (--x < 0)
					x += 10;
					break;
			case KEY_DOWN :
				if (++x > 10-1)
					x = 0;
					break;
			default :
				if (instruction == 'q'){
					quit = true;
					return;
				}
				if (s == true)
					s = false;
				else{
					time++;
					if (time == 1){
						p1_x = x;
						p1_y = y;
					}
					else{
						p2_x = x;
						p2_y = y;
								
						token.game_start( p1_x,p1_y, p2_x, p2_y);
						mvprintw(0,20,"score : %4d\n",token.score);
						mvprintw(1,20,"step : %2d\n ",token.step);
						mvprintw(2,20,"target : %4d\n",token.target);
						mvprintw(3,20,"remain jam : %2d\n",token.jam);
						time = 0;
					}
				}

		}
				
				
				
				/*int i = x,j = y;
				switch(token.graph[x][y]){
					case 0 :
						attron(COLOR_PAIR(0));
						//attrset(A_UNDERLINE);
						mvprintw(i,j,"%c",' ');
						attroff(COLOR_PAIR(0));
						//mvprintw(i,j,"%c",' ' );
						break;
					case 1 :
						attron(COLOR_PAIR(1));
						//attrset(A_UNDERLINE);
						mvprintw(i,j,"%c",' ' );
						attroff(COLOR_PAIR(1));	
						//mvprintw(i,j,"%c",' ' );
						break;
					case 2 :
						attron(COLOR_PAIR(2));
						//attrset(A_UNDERLINE);
						mvprintw(i,j,"%c",' ' );
						attroff(COLOR_PAIR(2));	
						//mvprintw(i,j,"%c",' ' );
						break;
					case 3 :
						attron(COLOR_PAIR(3));
						//attrset(A_UNDERLINE);
						mvprintw(i,j,"%c",' ' );
						attroff(COLOR_PAIR(3));
						//mvprintw(i,j,"%c",' ' );
						break;20+i,20+jf
					case 4 :
						attron(COLOR_PAIR(4));
						//attrset(A_UNDERLINE);
						mvprintw(i,j,"%c",' ' );
						attroff(COLOR_PAIR(4));	
						//mvprintw(i,j,"%c",' ' );							
						break;
							
				}*/
	}
			
}

void game_control::select(){
	int c;
	int direct = 0;
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_YELLOW);
	init_pair(2,  COLOR_BLACK, COLOR_WHITE);
	init_pair(3, COLOR_BLACK, COLOR_GREEN);
	init_pair(4, COLOR_BLACK, COLOR_RED);
	init_pair(10,COLOR_BLACK, COLOR_BLUE);
	init_pair(6, COLOR_YELLOW,COLOR_YELLOW);
	init_pair(7, COLOR_WHITE,COLOR_WHITE);
	init_pair(8, COLOR_GREEN, COLOR_GREEN);
	init_pair(9, COLOR_RED, COLOR_RED);
	init_pair(5, COLOR_BLUE, COLOR_BLUE);	
	init_pair(11,COLOR_WHITE,COLOR_BLACK);
			
	mode = 0;
	int row,col;
			//attron(COLOR_PAIR(1));
			//mvprintw(9,15,"EASY");
			//attroff(COLOR_PAIR(1));
	refresh();
	while(1){
		switch(mode){
			case 0 :
				attron(COLOR_PAIR(1));
				mvprintw(15,13,"EASY");
				attroff(COLOR_PAIR(1));
				attron(COLOR_PAIR(11));
				mvprintw(15,39,"Medium");
				mvprintw(15,80,"Hard");
				attroff(COLOR_PAIR(11));
				break;
					
			case 1 :
				attron(COLOR_PAIR(1));

				mvprintw(15,39,"Medium");

				attroff(COLOR_PAIR(1));
				attron(COLOR_PAIR(11));
				mvprintw(15,13,"EASY");
				mvprintw(15,80,"Hard");
				attroff(COLOR_PAIR(11));
				break;	

			case 2 : 
				attron(COLOR_PAIR(1));

				mvprintw(15,80,"Hard");

				attroff(COLOR_PAIR(1));
				attron(COLOR_PAIR(11));
				mvprintw(15,13,"EASY");
				mvprintw(15,39,"Medium");
				attroff(COLOR_PAIR(11));
				break;						
					
					
					
		}
		c = getch();
		switch (c){
			case KEY_LEFT :
				mode = mode-1 < 0 ?  2 : mode-1;
						/*attron(COLOR_PAIR(2));
						mvprintw(9,63,"HARD");
						attroff(COLOR_PAIR(2));
						attron(COLOR_PAIR(1));
						mvprintw(9,15,"EASY");
						attroff(COLOR_PAIR(1));*/
						//mvprintw(0,0,"%d",mode);
						
				break;
			case KEY_RIGHT : 
				mode = mode+1 > 2 ?  0 : mode+1;
					/*	attron(COLOR_PAIR(2));
						mvprintw(9,15,"EASY");
						attroff(COLOR_PAIR(2));
						attron(COLOR_PAIR(1));
						mvprintw(9,63,"HARD");
						attroff(COLOR_PAIR(1));*/
					//	mvprintw(0,0,"%d",mode);
				break;
			default :
					//	mvprintw(0,0,"%d",mode);
				clear();
				refresh();
				return;
	}
				

				
				
		refresh();
	} 			
}	
		
		