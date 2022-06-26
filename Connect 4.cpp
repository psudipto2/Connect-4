#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

struct playerInfo
{
	string playerName;
	char playerID;
};

void typeWriter(string str,int sleepTime){
    for(int i=0; i<str.length();i++){
        cout<<str[i];
        Sleep(sleepTime);
    }
    cout<<endl;
}

bool checkFullBoard( char board[][10] )
{
	int full;
	full = 0;
	for ( int i = 1; i <= 7; ++i )
	{
		if ( board[1][i] != '*' )
			++full;
	}
	if(full==7){
        return true;
	}
	return false;
}

bool restartGame ( char board[][10] )
{
	char restart;
	string endGame[2];
	endGame[0]="Would you like to restart? Yes(Y) No(N): ";
	endGame[1]="Goodbye!";
	typeWriter(endGame[0],30);
	cin  >> restart;
	if ( restart == 'Y' )
	{
		for(int i = 1; i <= 6; i++)
		{
			for(int j = 1; j <= 7; j++)
			{
				board[i][j] = '*';
			}
		}
		return true;
	}
	else{
        typeWriter(endGame[1],30);
		return false;
	}
}

void PlayerWin ( playerInfo activePlayer )
{
    string winMessage=activePlayer.playerName+" Connected Four, You Win!";
	typeWriter(winMessage,30);
}

bool checkWin ( char board[][10], playerInfo activePlayer )
{
	char RB= activePlayer.playerID;
	for( int i = 7; i >0; --i )
	{
		for( int j = 8; j >0; --j )
		{
			if( board[i][j] == RB && board[i-1][j-1] == RB && board[i-2][j-2] == RB && board[i-3][j-3] == RB ){  //diagonal
				return true;
			}
			else if( board[i][j] == RB && board[i][j-1] == RB && board[i][j-2] == RB && board[i][j-3] == RB ){
				return true;
			}

			else if( board[i][j] == RB && board[i-1][j] == RB && board[i-2][j] == RB && board[i-3][j] == RB ){
				return true;
			}

			else if( board[i][j] == RB && board[i-1][j+1] == RB && board[i-2][j+2] == RB && board[i-3][j+3] == RB ){
				return true;
			}

			else if( board[i][j] == RB && board[i][j+1] == RB && board[i][j+2] == RB && board[i][j+3] == RB ){
				return true;
			}
		}
	}
return false;
}

void putBall ( char board[][10], playerInfo activePlayer, int dropBall )
{
	int length=6;
	bool turn = false;
	while (turn==false)
	{
		if ( board[length][dropBall] != 'R' && board[length][dropBall] != 'B' )
		{
			board[length][dropBall] = activePlayer.playerID;
			turn = true;
		}
		else
		--length;
	}
}

int PlayerDrop(char board[][10],playerInfo activePlayer)
{
	int dropBall;
	string drop[3];
	drop[0]=activePlayer.playerName+"'s Turn ";
	drop[1]="Please enter a number between 1 and 7: ";
	drop[2]="That row is full, please enter a new row: ";
	while ( dropBall < 1 || dropBall > 7 )
	{
		typeWriter(drop[0],30);
		typeWriter(drop[1],30);
		cin  >> dropBall;

		while(board[1][dropBall]=='R'||board[1][dropBall]=='B')
		{
			typeWriter(drop[3],30);
			cin  >> dropBall;
		}
	}
    return dropBall;
}

void PrintBoard(char board[][10])
{
	int rows=6, columns=7;
	for(int i=1;i<=rows;i++)
	{
		cout <<"|";
		for(int j=1;j<=columns;j++)
		{
			if((board[i][j]!='R')&&(board[i][j]!='B')){
                board[i][j]='*';
			}
			cout<<board[i][j];
		}
		cout<<"|"<<endl;
	}

}

void gameController(){
    playerInfo playerOne, playerTwo;
	char Board[9][10];
	//char**Board= new char*[10];
	int Choice;
	bool Win=false, Full=false, Repeat=false;
	string startGame[3];
	startGame[0]="Let's Play Connect 4";
	startGame[1]="Player One please enter your name: ";
	startGame[2]="Player Two please enter your name: ";
	string drawMessage="The board is full, it is a draw!";
	for(int i=0;i<3;i++){
        typeWriter(startGame[i],30);
        if(i==1){
            cin  >> playerOne.playerName;
            playerOne.playerID = 'R';
        }
        else if(i==2){
            cin  >> playerTwo.playerName;
            playerTwo.playerID = 'B';
        }
        else{
            cout<<endl<<endl;
        }
    }
    cout<<endl<<endl<<endl;
    Sleep(2000);
    PrintBoard(Board);
    Sleep(1000);
    do{
	    Choice = PlayerDrop( Board, playerOne );
		putBall( Board, playerOne, Choice );
		PrintBoard( Board );
		Win = checkWin(Board, playerOne );
		if ( Win  )
		{
			PlayerWin(playerOne);
			Repeat = restartGame(Board);
			if (Repeat == false)
			{
				break;
			}
		}

		Choice = PlayerDrop(Board, playerTwo );
		putBall( Board, playerTwo, Choice );
		PrintBoard( Board );
		Win = checkWin( Board, playerTwo );
		if ( Win )
		{
			PlayerWin(playerTwo);
			Repeat = restartGame(Board);
			if (Repeat == false)
			{
				break;
			}
		}
		Full = checkFullBoard( Board );
		if ( Full  )
		{
		    typeWriter(drawMessage,30);
			Repeat = restartGame(Board);
		}

	} while ( Repeat != true );
}

void welcomeMessage(){
    string welcome[5];
    string rules[5];
    string play[4];
    welcome[0]="                --------------------------------------------------------";
    welcome[1]="                |                                                      |";
    welcome[2]="                |               WELCOME TO CONNECT-4 GAME              |";
    welcome[3]="                |                                                      |";
    welcome[4]="                --------------------------------------------------------";
    rules[0]="RULES:";
    rules[1]="1. TWO-PLAYER(RED(R) & BLUE(B)) GAME.";
    rules[2]="2. BOARD SIZE IS 6 ROWS & 7 COLOUMNS.";
    rules[3]="3. A PLAYER WINS IF HE/SHE ABLE TO CONNECTS 4 DOTS HORIZONTALLY, VERTICALLY OR DIAGONALLY.";
    rules[4]="4. DRAW WHEN BOARD IS FULLY FILLED BUT NO ONE ABLE TO CONNECT 4 DOTS.";
    play[0]="HOW TO PLAY: ";
    play[1]="1. GAME STARTS WITH PLAYER 1.";
    play[2]="2. IN EACH STEP CHOOSE COLUMN NUMBER WHICH YOU WANT TO DROP THE BALL.";
    play[3]="3. ROWS WILL BE FILLED FROM BOTTOM TO TOP IN ANY COLUMN.";
    for(int i=0;i<5;i++){
        typeWriter(welcome[i],10);
    }
    cout<<endl<<endl<<endl;
    Sleep(2000);
    for(int i=0;i<5;i++){
        typeWriter(rules[i],30);
    }
    cout<<endl<<endl<<endl;
    Sleep(2000);
    for(int i=0;i<4;i++){
        typeWriter(play[i],30);
    }
    cout<<endl<<endl<<endl;
    Sleep(2000);
}

int main() {
    welcomeMessage();
    gameController();
}
