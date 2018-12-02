#include <stdio.h>
#include <stdlib.h>

struct position{

	int cell_computer[6];
	int cell_player[6];
	
	int isComputer;//who's turn
	int seeds_player; //seeds taken by player
	int seeds_computer;
};

void init_Pos(struct position * p){

	//initialization for the game
	for(int i=0;i<6;++i){
		(p->cell_computer)[i]=4;
		(p->cell_player)[i]=4;
	}
	//who's turn, computer or player
	p->isComputer=1;
	//initial number of seeds taken by player or computer
	p->seeds_player=0;
	p->seeds_computer=0;
}

//*nextstate
void playMove(struct position * state,int movehole,int isComputer){
	int sowseed;
	if(isComputer){
		//Computer's turn
		printf("hahahahahahah\n");
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
		printf("hahhaha\n");
		sowseed=(state->cell_player)[movehole];
		printf("movehole is: %d\n", movehole);
		printf("sowseed is: %d\n", sowseed);

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

void main(){
	struct position pos;
	struct position * po = & pos;
	init_Pos(po);
	for (int i = 0; i < 6; ++i)
	{
		printf("cell_computer [%d] is: %d\n ", i,(po->cell_computer)[i] );

	}
	for (int i = 0; i < 6; ++i)
	{
		printf("cell_player [%d] is: %d\n ", i,(po->cell_player)[i] );

	}
	int movehole = 2; // I want to move hole 4 (starts from 0)
	int isComputer=0; //computer first
	playMove(po,movehole,isComputer);

	printf("after move hole %d: \n", movehole);
	for (int i = 0; i < 6; ++i)
	{
		printf("cell_computer [%d] is: %d\n ", i,(po->cell_computer)[i] );

	}
	for (int i = 0; i < 6; ++i)
	{
		printf("cell_player [%d] is: %d\n ", i,(po->cell_player)[i] );

	}

}