import java.util.*;
public class Player {
	static final int numColumns = 10;
	static final int numRows = 10;

	public int playerNum;
	public int numShips = 5;

	// ~ = open ocean, ! = ship, - = incorrect guess
	public char[][] guessBoard;
	//Board guessBoard;

	// ~ = open ocean, x = ship, @ = sunken ship
	public char[][] gameBoard;
	//	Board gameBoard;

	// constructors (int num = player number)
	public Player(){
		playerNum = 1;
		guessBoard = new char[numRows][numColumns];
		gameBoard = new char[numRows][numColumns];
		createGameBoard();
	}
	public Player(int num){
		playerNum = num;
		guessBoard = new char[numRows][numColumns];
		gameBoard = new char[numRows][numColumns];
		createGameBoard();
	}

	// initializes empty game board
	private void createGameBoard(){

		for(int i = 0; i < gameBoard.length; i++)
		{
			for(int j = 0; j < gameBoard[i].length; j++)
				gameBoard[i][j] = '~';
		}

		for (int i = 0; i < guessBoard.length; i++)
		{
			for (int j = 0; j < guessBoard[i].length; j++)
				guessBoard[i][j] = '~';
		}

	}//end of createGameBoard()

	// checks if guess was correct or not
	  public char attack(Player enemy, int xC, int yC){

		// Player gave correct guess
		if (enemy.gameBoard[xC][yC] == 'x')
		{
			guessBoard[xC][yC] = '!';
			enemy.gameBoard[xC][yC]  =  '@';
			enemy.numShips--;
			return '!';
		}
		// Player gave incorrect guess
		else
		{
			guessBoard[xC][yC] = '-';
			return '-';
		}

	}//end of attack()

}//end of player

