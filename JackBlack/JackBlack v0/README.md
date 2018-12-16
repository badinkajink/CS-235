## Assignment 2 - JackBlack

See the assignment specification pdf. Don't forget to update this README. Happy coding!


For this JackBlack project, I will use the data structures vector and stack.  I will have 5 main classes: NumCard, WordCard, SymoblCard, Player, Round.

Card class:
This Card class contains two data fields:
    char cType;
    int iValue;
This Card class has basic functions like get/set for each of the data fields.

NumCard class:
This Card class contains no additional fields:
    char cType;
    int iValue;
This Card class has basic functions like get/set for each of the data fields.

WordCard class:
This Card class contains one additional data fields:
    string sWord;
This Card class has basic functions like get/set for each of the data fields, and a function calcValueFromWord() to calcuate the value of word.

SymbolCard class:
This Card class contains three additional data fields:
    char cSymbol;
    int iLow, iHigh;
This Card class has basic functions like get/set for each of the data fields.


Player class:
This Player class contains data fields like: name, Max Hit, a vector of cards for a given round, its final score, number of Number cards, and bool value isWinner.
    string sName;
    int	iMaxHit;
    vector <Card*> vHand;

    int	iScore;
    bool isSymbolLow;
    bool isWinning;
    bool isTie;

This Player class has functions:
    string getName() {return sName;}
    int getMaxHit () {return iMaxHit;}

    int getScore() {return iScore;}
    bool getIsSymbolLow() {return isSymbolLow;}
    bool getIsWinning() {return isWinning;}
    bool getIsTie () { return isTie;}

    vector <Card*> getHand() { return vHand;}

    void setName(string name) {sName=name;}
    void setIsWinning (bool winning) {isWinning=winning;}
    void setIsTie (bool tie) {isTie=tie;}

    bool deal(Card* card); // add one card to a player
    bool hit(Card* card); // to decide if we shall keep hitting another card. if yes, add this card to the vHand, and return true to hit another card.


Round class:
This Round class contains data fields like a vector of players and various stats.
    vector<Player*> *vPlayer;

    int total_num_winning_hands;
    int total_num_losing_hands;
    int total_hits;
    int total_num_cards_winning;
    int total_num_cards_losing;

    int total_num_numcard_winning;
    int total_num_wordcard_winning;
    int total_num_symbolcard_winning;
    string sWinningWords;

This Round class has functions:
    int getTotal_num_winning_hands() { return total_num_winning_hands;}
    int getTotal_num_losing_hands() { return total_num_losing_hands;}
    int getTotal_hits () { return total_hits;}
    int getTotal_num_cards_winning () { return total_num_cards_winning;}
    int getTotal_num_cards_losing () { return total_num_cards_losing;}

    int getTotal_num_numcard_winning () { return total_num_numcard_winning;}
    int getTotal_num_wordcard_winning () { return total_num_wordcard_winning;}
    int getTotal_num_symbolcard_winning () { return total_num_symbolcard_winning;}
    string getWinningWords () { return sWinningWords;}

    void setVPlayer (vector<Player*> *player) {vPlayer=player;}
    vector<Player*> *getVPlayer() { return vPlayer;}

    string PrintRoundStats(int iRound);


JackBlackSimulator class:
This Game class has function:
    int readDeckFile(stack<Card*> &myDeck, string deckFile);
    int PrintDeck(stack <Card*> &myDeck);
    int readPlayersFile(vector <Player*> &vPlayer, string playersFile);
    int printPlayers(vector<Player*>vPlayer);
    int PlayGame (stack <Card*> &myDeck, const vector <Player*> &vPlayer, vector <Round*> &vRound);
     void PrintAnalytics (const vector <Player*> &vPlayer, const vector <Round*> &vRound);



The logical flow of the game:
	1. read the command line args.
	2. create the deck of cards from the deck file.
	3. create the list of players from the player file.
	4. play the game. Inside this PlayGame function, there is a while loop to check if the deck is empty. 
		If not, we we create a Player vector, and then Player objects and add one card to each player.
		Inside a while loop, while the deck is not empty, we keep hit a card for a player until it either busts or its total value exceeds max hit.
		Inside the while loop, create a Round vector, and then Round objects, and add Player vector to the Round object.
		In a high level, you can visualize this sequence: cards-> players -> rounds.
	5. print out the statistics.

