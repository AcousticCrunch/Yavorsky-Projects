import java.util.*;
import javax.swing.*;
import java.awt.*;
import java.io.*;
import java.lang.*;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class Board extends JFrame{

	public Player player1 = new Player();	// two player objects
	public Player player2 = new Player(2);
    private JButton cells[][] = new JButton[10][10];	// cells for buttons
    BattleshipPanel panel = new BattleshipPanel();
    JFrame frame = new JFrame( "Battleship" );
    int counter;
    int player1or2 = 1;

  // Frame Constructor
  public Board()
  {
     frame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
     frame.setResizable(false);
     
    panel.setBackground(new Color(131, 209, 232));

    // grid of 10 rows, 10 columns, buttons in each grid spot
    panel.setLayout(new GridLayout(10, 10));

    //create each button on the grid:
    for(int i = 0; i < 10; i++)
    {
      for(int j = 0; j < 10; j++)
      {
        cells[i][j] = new JButton();
        cells[i][j].addActionListener(new DeployListener(i,j));
        panel.add(cells[i][j]);
      }
    }
     frame.add(panel); //add panel to frame
     frame.setSize(1000, 1000); //default frame size
     frame.setVisible(true);

  }//end of Board
 
// Deploy Phase (triggered by button push)
public class DeployListener implements ActionListener
{
    int row;
    int column;
    
    public DeployListener(int r, int c)
    {
        row = r;
        column = c;
    }

    public void actionPerformed(ActionEvent evt)
    {
    	if (player1or2 == 1)
    	{
    		if (player1.gameBoard[row][column] != 'x')
    		{
    			cells[row][column].setBackground(Color.RED);
                cells[row][column].setOpaque(true);
                player1.gameBoard[row][column] = 'x';
                counter++;
    		}
            
    	}
    	else
    	{
    		if (player2.gameBoard[row][column] != 'x')
    		{
    			cells[row][column].setBackground(Color.RED);
                cells[row][column].setOpaque(true);
                player2.gameBoard[row][column] = 'x';
                counter++;
    		}
    	}
    	
    	if (counter == 5 && player1or2 == 1)
    	{
    		counter = 0;
    		player1or2 = 2;
    		clearButtons();
    	}
    	if (counter == 5 && player1or2 == 2)
    	{
    		clearButtons();
    		switchToAttack();
    	}
    }
    
    public void clearButtons()
    {
    	for(int i = 0; i < 10; i++)
        {
          for(int j = 0; j < 10; j++)
          {
            cells[i][j].setBackground(new JButton().getBackground());
          }
        }
    }
    
    public void switchToAttack()
    {
          frame.dispose();
          
          JFrame frame = new JFrame( "Battleship" );
    	  JButton passButton = new JButton("Please pass the device to player 1");
    	  panel = new BattleshipPanel();
    	  
    	  frame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
    	  frame.setResizable(false);
    	  
    	  passButton.addActionListener(new SwitchToAttackListener());  	  
		  panel.setLayout(new GridLayout(1,1));
		  panel.add(passButton);
		  frame.add(panel);
		  frame.setSize(1000, 1000);
		  frame.setVisible(true);
		  
    }
}//end of DeployListener

// Button that switches to Attack Phase (triggered by button push)
public class SwitchToAttackListener implements ActionListener
{
	
	public void actionPerformed(ActionEvent evt)
	{
		
		  frame.dispose();
	    
	      JFrame frame = new JFrame( "Battleship" );
		  panel = new BattleshipPanel();
		  
		  frame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
		  frame.setResizable(false);
		 
		  panel.setLayout(new GridLayout(10,10));
		  panel.setBackground(new Color(131, 209, 232));
		
		for(int i = 0; i < 10; i++)
        {
          for(int j = 0; j < 10; j++)
          {
        	  for (ActionListener currentListener : cells[i][j].getActionListeners())
            	  cells[i][j].removeActionListener(currentListener);
        	  
        	  cells[i][j].addActionListener(new AttackListener(i,j));
        	  
        	  panel.add(cells[i][j]);
          }
        }
    	player1or2 = 1;
    	frame.add(panel);
		frame.setSize(1000, 1000);
		frame.setVisible(true);
	}
}// end of SwitchToAttackListener

// Attack Phase (Triggered by button push)
public class AttackListener implements ActionListener
{
	int row;
    int column;

    public AttackListener(int r, int c)
    {
        row = r;
        column = c;
    }
    
	public void actionPerformed(ActionEvent evt)
    {
		
		if (player1or2 == 1)
		{
			char result = player1.attack(player2, row, column);
			System.out.print(result);
			if (result == '!')	// Button turns green if guess is correct
				cells[row][column].setBackground(Color.GREEN);
			
			if (result == '-')	// Button turns red and switches players if guess is incorrect
			{
				player1or2 = 2;
				clearButtons();
				switchPlayers(2);
			
			}
			
			if (player2.numShips == 0)	// if other player's ships are all destroyed, current player wins
				victoryScreen(1);
		}
		else
		{
			char result = player2.attack(player1, row, column);
			System.out.print(player1.numShips);
			if (result == '!')	// Button turns green if guess is correct
				cells[row][column].setBackground(Color.GREEN);
			
			if (result == '-')	// Button turns red and switches players if guess is incorrect
			{
				player1or2 = 1;
				clearButtons();
				switchPlayers(1);
			}
			
			if (player1.numShips == 0)	// If other player's ships are all destroyed, current player wins
				victoryScreen(2);
		}
        
    }
	
	public void clearButtons()
    {
    	for(int i = 0; i < 10; i++)
        {
          for(int j = 0; j < 10; j++)
            cells[i][j].setBackground(new JButton().getBackground());
        }
    }
	
	public void switchPlayers(int playerNum)
	{
		frame.dispose();
        
        JFrame frame = new JFrame( "Battleship" );
        JButton passButton = new JButton("Please pass the device to player " + playerNum);
  	  	panel = new BattleshipPanel();
  	  
  	  	frame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
  	  	frame.setResizable(false);
  	  
  	  	passButton.addActionListener(new SwitchToPlayerListener());  	  
  	  	panel.setLayout(new GridLayout(1,1));
  	  	panel.add(passButton);
  	  	frame.add(panel);
  	  	frame.setSize(1000, 1000);
	 	frame.setVisible(true);
	  
	}

	public void victoryScreen(int playerNum)
	{
		  JFrame frame = new JFrame( "Congratualtions!" );
	      frame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
	      frame.setResizable(false);
		  panel = new BattleshipPanel();
		  panel.setLayout(new GridLayout(1,1));
		  panel.add(new JButton("Congatulations Player " + playerNum + " you win!"));
		  frame.add(panel);
		  frame.setSize(500, 500);
		  frame.setVisible(true);
	}
} // end of AttackListener

// Button that switches between the turns of two players 
public class SwitchToPlayerListener implements ActionListener
{
	public void actionPerformed(ActionEvent evt) {
		 frame.dispose();
	    
	     JFrame frame = new JFrame( "Battleship" );
		 panel = new BattleshipPanel();
		  
		 frame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
		 frame.setResizable(false);
		 
		 panel.setLayout(new GridLayout(10,10));
		 panel.setBackground(new Color(131, 209, 232));
		
		for(int i = 0; i < 10; i++)
        {
          for(int j = 0; j < 10; j++)
          {
        	  for (ActionListener currentListener : cells[i][j].getActionListeners())
            	  cells[i][j].removeActionListener(currentListener);
        	  
        	  cells[i][j].addActionListener(new AttackListener(i,j)); 
        	  
        	  if (player1or2 == 1)
        	  {
        		  if (player1.guessBoard[i][j] == '!')
        			  cells[i][j].setBackground(Color.GREEN);
        		  
        		  if (player1.guessBoard[i][j]  == '-')
        			  cells[i][j].setBackground(Color.RED);
        	  }
        	  else
        	  {
        		  if (player2.guessBoard[i][j] == '!')
        			  cells[i][j].setBackground(Color.GREEN);
        		  
        		  if (player2.guessBoard[i][j]  == '-')
        			  cells[i][j].setBackground(Color.RED);
        	  }
        	  
        	  panel.add(cells[i][j]);
          }
        }
		frame.add(panel);
		frame.setSize(1000, 1000);
		frame.setVisible(true);
	}
} // end of SwitchToPlayerListener

// Panel class
class BattleshipPanel extends JPanel
   {

     public void paintComponent(Graphics g)
     {
         super.paintComponent(g);  //call superclass' paintComponent
         Graphics2D g2d = ( Graphics2D ) g; // cast g to Graphics2D
     }

   }//end of BattleshipPanel

}//end of board


