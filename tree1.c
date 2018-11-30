#include <stdio.h>
#include <stdlib.h>

struct position{

	int cell_computer[6];
	int cell_player[6];
	
	bool isComputer;//who's turn
	int seeds_player; //seeds taken by player
	int seeds_computer;
};

position init_Pos(){
	struct position iniposition;
	iniposition.cell_computer={4,4,4,4,4,4};
	iniposition.cell_player={4,4,4,4,4,4};
	
	iniposition.isComputer=1;
	iniposition.seeds_player=0;
	iniposition.seeds_computer=0;
	return iniposition;
};

position play(state,movehole,isComputer){
	int sowseed;
	if(isComputer){
		sowseed=state.cell_computer[movehole];
		index=movehole+sowseed;
		for (int i = 0; i < count; ++i)
		{
			/* code */
		}
	}else{
		sowseed=state.cell_player[movehole];
		
	}
}

void main(){
	init_Pos()；

}