#include <iostream>
#include <climits>

class TicTacToe {

public: 

  TicTacToe(char playerPiece){
    //Build the board
    for(int i = 0; i < sizeof(board); i++)
      board[i] = char(i+49);
    player = playerPiece;
    computer = (player == 'X') ? 'O' : 'X';
  }

  void play() {
    while(determineWinner() == '?' && !isFull()) {
      drawboard();
      playerMove(getPlayerPosition());
      if(determineWinner() == '?' && !isFull()) {
	    computerMove();
      }
    } 
    char winner = determineWinner();
    drawboard();
    if(winner == player)
      std::cout << "You won! Congratulations!";
    else if(winner == computer)
      std::cout << "You lost...sorry! Try again!";
    else
      std::cout << "Tie! Great playing!";
  }

private:
  void drawboard(){
    std::cout << " " << board[0] << " | " << board[1] << " | " << board[2] << std::endl;
    std::cout << " " << board[3] << " | " << board[4] << " | " << board[5] << std::endl;
    std::cout << " " << board[6] << " | " << board[7] << " | " << board[8] << std::endl;
  }

  char determineWinner() {
    if(board[0] == board[1] && board[1] == board[2])
      return board[0];
    if(board[3] == board[4] && board[4] == board[5])
      return board[3];
    if(board[6] == board[7] && board[7] == board[8])
      return board[6];
    if(board[0] == board[3] && board[3] == board[6])
      return board[0];
    if(board[1] == board[4] && board[4] == board[7])
      return board[1];
    if(board[2] == board[5] && board[5] == board[8])
      return board[2];
    if(board[0] == board[4] && board[4] == board[8])
      return board[0];
    if(board[2] == board[4] && board[4] == board[6])
      return board[2];
    return '?';
  }
    void computerMove() {
    int bestMove = -1;
    int bestScore = -10000; // Replace with a reasonable low value

    for (int i = 0; i < sizeof(board); i++) {
        if (isAvailable(char(i + 49))) {
            // Try the move
            board[i] = computer; // Use the 'computer' variable here

            // Calculate the score for this move
            int score = miniMax(player); // Call miniMax for the player

            // Undo the move
            board[i] = char(i + 49);

            // Update bestMove and bestScore if needed
            if (score > bestScore) {
                bestScore = score;
                bestMove = i;
            }
        }
    }

    // Make the best move for the computer
    board[bestMove] = computer; // Use the 'computer' variable here
}
  int miniMax(char currentPlayer){
    char winner = determineWinner();
    /*this first if/else code block is used as the base case for our recursive call.
    if the winner is determined to be the computer then the function returns 1 which is a positive
    for the computer. If the player was to win, then the function returns -1, which is negative meaning
    it is not a favorable move for the computer*/
    if (winner == computer)
      return 1;
    else if (winner == player)
      return -1;
    else if (isFull())
      return 0;

/*Inatilize the "BestScore" dependant on whos turn it is. If it is the computers turn it initializes to a 
low value so any positive moves will increase the value
if it is the players turn it inatializes to an extremely high value so that any postive moves decrease the value.
Useing this method with extrememly high/low values will ensure that any change will be lower or greater
than the inital value*/
    int bestScore;
    if (currentPlayer==computer){
      bestScore= -INT_MAX;
    } else {
      bestScore=INT_MAX;
    }

    for (int i=0; i < sizeof(board);i++){
      if(isAvailable(char(i+49))) {
        board[i] = currentPlayer;
        int score;

        if (currentPlayer == computer) {
    // It's the computer's turn, call minimax for the opponent (player)
          score = miniMax(player);
        } else {
    // It's the opponent's (player's) turn, call minimax for the computer
          score = miniMax(computer);
        }
        board[i]=char(i+49);

        if (currentPlayer == computer) {
                    bestScore = std::max(bestScore, score);
                } else {
                    bestScore = std::min(bestScore, score);
                }
            }
        }
        return bestScore;
        }
  void playerMove(char move) {
    int pos = int(move) - 49;
    board[pos] = player;
  }

  char getPlayerPosition() {
    char move;
    do {
      std::cout << "Enter a move (1-9): ";
      std::cin >> move;
    } while(!isAvailable(move));
    return move;
  }

  bool isAvailable(char pos) {
    int position = int(pos) - 48;
    if(board[position - 1] == pos)
      return true;
    return false;
  }

  bool isFull() {
    for(int i = 0; i < sizeof(board); i++) {
      if(board[i] == char(i+49))
	return false;
    }
    return true;
  }

    char board[9];
    char player;
    char computer;
  };
  int main() {
    char piece;   
    std::cout << "Do you want to be X or O? ";
    std::cin >> piece;

    TicTacToe gameOn(piece);
    gameOn.play();

    return 0;
  }
