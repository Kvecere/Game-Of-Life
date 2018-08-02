#include <iostream>
#include <string>
#include <vector>
#include <climits>
using namespace std;
int getNeighborCount(vector<vector<char>> oldBoard,int row,int col){
	int count=0;
	for(int i=-1;i<2;i++){
		for(int j=-1;j<2;j++){
			if((row+i>=0 && col+j>=0) && (row+i<oldBoard.size() && col+j<oldBoard.size())){
				if(oldBoard[row+i][col+j]=='0'){count++;}
			}
		}
	}
	return count;
}
int main(){ 
	cout<<"Hello. Welcome to the Game of Life."<<endl;
	int boardSize=0;
	vector<vector<char>> board;
	do{
		cout<<"Please enter your board size (the board will be of square size)."<<endl;
		cin>>boardSize;
		if(cin.fail()||boardSize<1){
			cout<<"Invalid input. Please try again"<<endl;
			boardSize=0;
		}
		cin.clear();
		cin.ignore(INT_MAX,'\n');
	}while(boardSize==0);
	cout<<"Enter your first generation board row-by-row. Use 0 for live cells and - for dead ones."<<endl;
	int currentRow=0;
	//Create first gen board
	while(currentRow<boardSize){
		bool hasError=false;
		string rowInfo;
		cout<<"Enter info for row "<<currentRow<<endl;
		cin>>rowInfo;
		if(rowInfo.length()!=boardSize){
			cout<<"Invalid row length. Please try again."<<endl;
			cout<<rowInfo.length()<<"\t"<<boardSize<<endl;
			hasError=true;
		}
		vector<char> boardRow;
		if(!hasError){
			for(int cell=0;cell<rowInfo.length();cell++){
				if(rowInfo.at(cell)!='0' && rowInfo.at(cell)!='-'){
					cout<<"Invalid character in row. Please try again."<<endl;
					hasError=true;
					break;
				}
				else{
					boardRow.push_back(rowInfo[cell]);
				}
			}
		}
		currentRow=!hasError ? currentRow+=1: currentRow;
		if(rowInfo.length()==boardSize){board.push_back(boardRow);}
		cin.clear();
		cin.ignore(INT_MAX,'\n');
	}
	cout<<"How many generations do you want to obtain?"<<endl;
	int totalGens=0;
	do{
		cin>>totalGens;
		if(cin.fail()||totalGens<0){
			cout<<"Invalid input. Try again"<<endl;
			totalGens=0;
		}
		cin.clear();
		cin.ignore(INT_MAX,'\n');
	}while(totalGens==0);
	vector<vector<char>> nextGen=board;
	for(int gen=0;gen<totalGens;gen++){
		int topLine=boardSize<=16 ? 2 : int((boardSize/2)-6);
		cout<<string(topLine,'=')<<"Generation "<<gen+1<<string(topLine,'=')<<endl;
		for(int row=0;row<boardSize;row++){
			for(int col=0;col<boardSize;col++){
				int neighborCount=getNeighborCount(board,row,col)-1;//-1 assumes that the cell is live
				if(board[row][col]=='0' && (neighborCount<2 || neighborCount>3)){//cell dies
					nextGen[row][col]='-';
					cout<<"-";
				}
				if(board[row][col]=='-' && neighborCount+1==3){//dead cell comes alive
					nextGen[row][col]='0';
					cout<<"0";
				}
				if(board[row][col]=='0' && (neighborCount==2 || neighborCount==3)){//cell stays alive
					nextGen[row][col]='0';
					cout<<"0";
				}
				if(board[row][col]=='-' && neighborCount+1!=3){//cell stays dead
					nextGen[row][col]='-';
					cout<<"-";
				}
			}
			cout<<endl;
		}
		cout<<string(topLine,'=')<<"============"<<string(topLine,'=')<<endl;
		board=nextGen;
	}
	return 0;
}