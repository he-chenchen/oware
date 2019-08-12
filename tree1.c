#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>
//INT_MAX;
//INT_MIN;

//2018-12-10
struct position{
	int cell_computer[6];
	int cell_player[6];
	int isComputer;//who's turn
	int seeds_player; //seeds taken by player
	int seeds_computer;
	int score; // to save the score the current position
	int bestmove; // to show which is best next move for current position
};

void init_Pos(struct position * p){

	//initialization for the game
	for(int i=0;i<6;++i){
		(p->cell_computer)[i]=4;
		(p->cell_player)[i]=4;
	}
	//who's turn, computer or player
	p->isComputer=1; //I will use "1" to represent computer's turn, and use "-1" to represent human player's turn
	//initial number of seeds taken by player or computer
	p->seeds_player=0;
	p->seeds_computer=0;
	p->score=0;
	p->bestmove=-1;// "-1" means: there has no best next move
}

void playMove(struct position * nextstate,struct position * state,int movehole);
// given a position and the movehole, we generate next position
void capture(struct position * state);
// when given a position, we capture the seeds if capture condition is qualified
int evaluation(struct position pos); 
//return the value of evaluation for a certain position
int generateBestmove(struct position * p,int index,int depth, int maxdepth);
// when given a position, return the best next movehole
int sizeoftree(int branch, int depth); 
//return the size of our array "tree"
int validMove(struct position * state,int holeNum);
// check if current playMove is valid or not, return 1-valid or 0-invalid
void copyPosition(struct position * copypo,struct position * po);
// copy a position for preventing modify parent node when we generating the tree
void printboard(struct position * state);
// print out current status of the game
void Move(struct position * state,int movehole);

void main()
{
	//generating a position
	struct position pos;
	//initialize the position
	init_Pos(&pos);
	// we have to keep in mind that we want computer win the game!!!
	int idx=0;
	int depth=10;
	int branch=6;
	int size=sizeoftree(branch,depth);
	//important!! Here we are allocating memory for our tree!
	struct position * p = malloc(size*sizeof(struct position));
	//start the game!!
	//print the game board
	printboard(&pos);
	int round=5; // we can play 15 times in total
	for (int i = 0; i < depth; ++i)
	{
		int movehole;
		if(pos.isComputer==1)
			printf("This is computer's turn: \n");
		else
			printf("This is human player's turn: \n");
		printf("Choose the hole you wanna play: ");
		scanf("%d",&movehole);
		//to prevent invalid move
		while(validMove(&pos,movehole)==0){
			printf("Invalid move, please type again: \n");
			scanf("%d",&movehole);
		}
		Move(&pos,movehole);
		capture(&pos);
		printboard(&pos);
		pos.isComputer=(pos.isComputer==1)? 0 : 1;
	}
}

void Move(struct position * state,int movehole){
	int sowseed;
	//if(state->isComputer)
	if(state->isComputer==1){
		//Computer's turn
		sowseed=(state->cell_computer)[movehole];
		for (int i = 0; i < sowseed; ++i)
		{
			int index=movehole+i+1;
			if(index>5){
				if(index>11){
					index=index %12;
					(state->cell_computer)[index]+=1;
				}
				index=index % 6;
				(state->cell_player)[index]+=1;
			}else{
				(state->cell_computer)[index]+=1;
			}
		}
		(state->cell_computer)[movehole]=0;
	}
	else{
		sowseed=(state->cell_player)[movehole];
		for(int i=0; i< sowseed;++i){
			int index=movehole+i+1;
			if(index>5){
				if(index>11){
					index=index % 12;
					(state->cell_player)[index]+=1;
				}
				index= index % 6;
				(state->cell_computer)[index]+=1;
			}else{
				(state->cell_player)[index]+=1;
			}
		}
		(state->cell_player)[movehole]=0;
	}
}
void playMove(struct position * nextstate,struct position * state,int movehole){
	copyPosition(nextstate,state);
	int sowseed;
	//if(state->isComputer)
	if(nextstate->isComputer==1){
		//Computer's turn
		sowseed=(nextstate->cell_computer)[movehole];
		for (int i = 0; i < sowseed; ++i)
		{
			int index=movehole+i+1;
			if(index>5){
				if(index>11){
					index=index %12;
					(nextstate->cell_computer)[index]+=1;
				}
				index=index % 6;
				(nextstate->cell_player)[index]+=1;
			}else{
				(nextstate->cell_computer)[index]+=1;
			}
		}
		(nextstate->cell_computer)[movehole]=0;
	}
	else{
		sowseed=(nextstate->cell_player)[movehole];
		for(int i=0; i< sowseed;++i){
			int index=movehole+i+1;
			if(index>5){
				if(index>11){
					index=index % 12;
					(nextstate->cell_player)[index]+=1;
				}
				index= index % 6;
				(nextstate->cell_computer)[index]+=1;
			}else{
				(nextstate->cell_player)[index]+=1;
			}
		}
		(nextstate->cell_player)[movehole]=0;
	}
}

void capture(struct position * state){
	//find the capture start point
	int start=-1; // where the capture starts
	if(state->isComputer==1){
		//if it's computer's turn, then we capture player's side
		for (int i = 5; i >=0; --i){
			if(state->cell_player[i]>=2&&state->cell_player[i]<=3){
				start=i;
				printf("the capture hole starts from: %d\n", start);
				break;
			}
		}
		if(start!=-1){
			for (int i = start; i >=0; --i){
				if(state->cell_player[i]>=2 && state->cell_player[i]<=3){
					state->seeds_computer+=state->cell_player[i];
					state->cell_player[i]=0;
				}else{
					break;
				}
			}
		}
	}else{
		//find out the start point
		//if it's player's turn, then we capture computer's side
		for(int i = 5; i >=0; --i){
			if(state->cell_computer[i]>=2&&state->cell_computer[i]<=3){
				start=i;
				printf("the capture hole is: %d\n",start );
				break;
			}
		}
		if(start!=-1){
			for(int i=start; i>=0;--i){
				if(state->cell_computer[i]>=2&&state->cell_computer[i]<=3){
					state->seeds_player+=state->cell_computer[i];
					state->cell_computer[i]=0;
				}else{
					break;
				}
			}
		}
	}
}
	
//evaluation function
int evaluation(struct position pos){
	return pos.seeds_computer-pos.seeds_player;
}

int generateBestmove(struct position * p,int index,int depth, int maxdepth)
{
	if(depth>0){
		//if depth>0 generate next move
		for (int i = 0; i < 6; ++i){
			if(validMove(&p[index],i)){
				//if it's valid we can continue playMove
				playMove(&p[index*6+i+1],&p[index],i);
				//after playMove, we will do the capture
				capture(&p[index*6+i+1]);
				//after caputer, we already get the gain seeds for the 
				//do something like call the minimax function? or do the evaluation???
				p[index*6+i+1].isComputer=pow(-1,maxdepth-depth);
				p[index*6+i+1].score=evaluation(p[index*6+i+1]);
				generateBestmove(p,index*6+i+1,depth-1,maxdepth);
			}
		}
	}else{
		p[index].score=evaluation(p[index]);
		if(p[index/6].isComputer=1){
			p[index/6].score=INT_MIN;
			if(p[index/6].score>p[index/6].score){
				p[index/6].score=p[index].score;
				if(index%6==0){
					p[index/6].bestmove=6;
				}else{
					p[index/6].bestmove=index%6;
				}
			}
			return p[index/6].bestmove;// return the best move
		}else{
			p[index/6].score=INT_MAX;
			if(p[index/6].score<p[index/6].score){
				p[index/6].score=p[index].score;
				if(index%6==0){
					p[index/6].bestmove=6;
				}else{
					p[index/6].bestmove=index%6;
				}
			}
			return p[index/6].bestmove;
		}
	}
}

int sizeoftree(int branch, int depth){
	int size = 0;
	for (int i = 0; i < depth+1; ++i)
	{
		size+=pow(branch,i);
	}
	return size;
}

int validMove(struct position * state,int holeNum){
	if(state->isComputer==-1){
		if(state->cell_computer[holeNum]==0)
			return 0;
		else
			return 1;
	}else{
		if(state->cell_player[holeNum]==0)
			return 0;
		else
			return 1;
	}
}
void copyPosition(struct position * copypo,struct position * po){
	memcpy(copypo->cell_computer,po->cell_computer,sizeof(int)*6);
	memcpy(copypo->cell_player,po->cell_player,sizeof(int)*6);
	copypo->isComputer=po->isComputer;
	copypo->seeds_computer=po->seeds_computer;
	copypo->seeds_player=po->seeds_player;
}

void printboard(struct position * state){
	printf("           0   1   2   3   4   5 \n");
	printf("	 |-----------------------|\n");
	printf("computer |%2d |%2d |%2d |%2d |%2d |%2d | gain=%d\n",state->cell_computer[0],state->cell_computer[1],state->cell_computer[2],state->cell_computer[3],state->cell_computer[4],state->cell_computer[5],state->seeds_computer);
	printf("	 |-----------------------|\n");
	printf("  player |%2d |%2d |%2d |%2d |%2d |%2d | gain=%d\n",state->cell_player[5],state->cell_player[4],state->cell_player[3],state->cell_player[2],state->cell_player[1],state->cell_player[0],state->seeds_player);
	printf("	 |-----------------------|\n");
	printf("           5   4   3   2   1   0 \n");
}