#include "player.h"

/*Initialize the square of the board by providing:
 * 1.PlayerName: which is provided from the constructor paramter of the GameWindow class
 * 2.PlayerNumber: indicate the index of the two player, in which the first playing player
 * takes index 0, the other takes 1.
 * 3.IsMaximizer: which is a boolean variable indicate if the current player is maximizer or not.
 */
Player::Player(QString name,int PlayerNumber, bool IsMaximizer,int  playerLevel)
{
    this->name=name;
    this->PlayerNumber=PlayerNumber;
    this->IsMaximizer=IsMaximizer;

   /*the player following attributes is set initialy to:
    * 1.Player score is initialy set to zero.
    * (then, it will be calculated by summing the (white, or black) disks
    * on the board. In which every (white or black) disk adds 1 point to
    * the player score).
    */
    this->Score=0;

   /*2.RemindedPieces is set initialy to 30 pieces for every player,
    * then RemindedPieces will decrease by 1 for every:
    *  2.1)valid move the player make
    *  2.2)if a player can make a valid move, but doesn't have enough pieces
    *  the second player gives one piece (if he has) to the first one.
    */

    this->RemindedPieces=30;
    /*3.isWin:is set initialy to zero, if the player won, isWin will be set to 1.*/
    this->isWin=0;

    this->playerLevel=playerLevel;
}

/*---------------------Setter--------------------------*/

/*this function is called using one of the players in the PlayerList in the gameBoard class.
 it's only called when game end.
*/
void Player::setWinFlag(bool isWin)
{
    QString GameOverMessage="";

   /*check if isWin:
    * 1.equal 1 (this means that the player which called the function won the game).
    * In this case the game over message will be (PlayerName Win!).
    */
    if(isWin==1)GameOverMessage=this->name+" Win!";

   /* 2.else if:
    * isWin equal 0 (this means it's a draw game).
    * In this case the game over message will be (Draw!).
    */
    else if(isWin==0)GameOverMessage="Draw!";

   /*sending a signal to the gameWindow with the title (GameOver) containing:
    * 1.the score of the player who called the function after converting it to a QString.
    * 2.the game over message.
    */
    emit SendPlayerSignal({"GameOver",QString::number(Score),GameOverMessage});
}

void Player::setIsThereValidMoves(bool isThereValidMoves)
{
    this->IsTherevalidMoves=isThereValidMoves;
}

/*this function is called using one of the players in the PlayerList in the gameBoard class.
 * the parameter score is calculated by summing the (white, or black) disks on the board.
 * In which every (white or black) disk adds 1 point to the player score).
 * --------------------------------------------------------------------
 * the score parameter is calculated using the function calculateScoreForAPlayer from the
 * GameDisplayCalculation class.
 * The function calculateScoreForAPlayer is used in the gameBoard class.
 */
void Player::UpdateScore(int score)
{
    this->Score=score;

    /*sending a signal to the gameWindow with the title (Update Player Score) containing:
    * 1.the score of the player who called the function after converting it to a QString.
    * 2.the player number (0 for first player, 1 for the second) after converting it to a QString.
    */
    emit SendPlayerSignal({"Update Player Score",QString::number(Score),QString::number(this->PlayerNumber)});
}

/*this function is called using one of the players in the PlayerList in the gameBoard class.
 * then RemindedPieces will decrease by 1 for every:
 *  2.1)valid move the player make
 *  2.2)if a player can make a valid move, but doesn't have enough pieces
 *  the second player gives one piece (if he has) to the first one.
 */
void Player::UpdateRemindedPices(int RemindedPieces)
{

    if(RemindedPieces==-1)
    this->RemindedPieces--;

    //for testing ##############################################################################################################################
    else
    this->RemindedPieces=RemindedPieces;
    //end

    /*sending a signal to the gameWindow with the title (Update Player Reminded Pieces) containing:
    * 1.the reminded pieces of the player who called the function after converting it to a QString.
    * 2.the player number (0 for first player, 1 for the second) after converting it to a QString.
    */
    emit SendPlayerSignal({"Update Player Reminded Pieces",QString::number(this->RemindedPieces),QString::number(this->PlayerNumber)});
}


/*this function is called using one of the players in the PlayerList in the gameBoard class.
 * it's called every turn to display the name of the current player to the user.
 */
void Player::UpdatePlayerTurn()
{
    /*sending a signal to the gameWindow with the title (Update turn) containing:
    * 1.the player name.
    */
    emit SendPlayerSignal({"Update turn",this->name});
}

/*---------------------Getter--------------------------*/

/*get reminded pieces of the player*/
int Player::getRemindedPieces()
{
    return RemindedPieces;
}

int Player::getPlayerLevel()
{
    return playerLevel;
}

QString Player::getPlayerName()
{
    return name;
}

bool Player::IsThereValidMoves()
{
    return IsTherevalidMoves;
}

/*return 1(if maximizer), -1(minimizer) */
int Player::IsPlayerMaximizer()
{
    return IsMaximizer?IsMaximizer:-1;
}

/*get the score of the player*/
int Player::getScore()
{
    return Score;
}

//add comment###########################################################################################################################
void Player::NoValidMovesThisTurn()
{
    emit SendPlayerSignal({"Player skip This Turn",this->name});
}

void Player::TakePiecesFromOppenent()
{
    emit SendPlayerSignal({"Player will take a piece from opponent",this->name});
}
