#include <iostream>
#include <string>
#include "FlashcardDeck.h"
#include "catch.h"


TEST_CASE ( "adding/removing/containment of cards preserves uniqueness", "[card]") {
  FlashcardDeck deck;

  SECTION ( "checking deck is empty" ) {
    REQUIRE ( deck.listFlashcards() == "" );
  }


  SECTION ( "adding and removing and checking if deck contains correct cards while maintaing uniqueness" ) {
    REQUIRE ( deck.addCard("Captain America", "Chris Evans") == true );
    REQUIRE ( deck.containsCard ("Captain America") == true );
    REQUIRE ( deck.addCard("Captain America", "Chris Evans") == false );
    REQUIRE ( deck.listFlashcards() == "Captain America\nChris Evans\n\n" );


    REQUIRE ( deck.containsCard("Ant-Man") == false );


    REQUIRE ( deck.addCard("Iron Man", "RDJ") == true );
    REQUIRE ( deck.addCard("Black Widow", "ScarJo") == true );
    REQUIRE ( deck.containsCard("Iron Man") == true );
    REQUIRE ( deck.containsCard("Black Widow") == true );
    REQUIRE ( deck.addCard("Iron Man", "RDJ") == false );
    REQUIRE ( deck.addCard("Black Widow", "ScarJo") == false );

    REQUIRE ( deck.listFlashcards() == "Captain America\nChris Evans\n\nIron Man\nRDJ\n\nBlack Widow\nScarJo\n\n");


    //removing non-existing cards in empty deck returns false
    REQUIRE ( deck.removeCard("Quicksilver") == false );



    //removing existing cards
    //removing from middle of deck
    REQUIRE ( deck.containsCard("Iron Man") == true );
    REQUIRE ( deck.removeCard("Iron Man") == true );
    REQUIRE ( deck.containsCard("Iron Man") == false );
    REQUIRE ( deck.listFlashcards() == "Captain America\nChris Evans\n\nBlack Widow\nScarJo\n\n");

    //removing from all cards
    REQUIRE ( deck.removeCard("Captain America") == true);
    REQUIRE ( deck.removeCard("Black Widow") == true);
    REQUIRE ( deck.containsCard("Captain America") == false );
    REQUIRE ( deck.containsCard("Black Widow") == false );
    REQUIRE ( deck.listFlashcards() == "");


    //removing students in empty deck returns false
    REQUIRE ( deck.removeCard("Iron Man") == false );
    REQUIRE ( deck.removeCard("Quicksilver") == false );
  }


}


TEST_CASE ( "combining FlashCards", "[combine]" ) {

  FlashcardDeck deck1, deck2;

  SECTION ( "combine empty decks" ) {
    deck1.combineFlashcards(deck2);
    REQUIRE ( deck1.listFlashcards() == "" );
  }

  SECTION ( "combine one empty deck" ) {
    REQUIRE ( deck1.addCard("A", "1") == true );
    deck1.combineFlashcards(deck2);
    deck2.combineFlashcards(deck1);
    REQUIRE ( deck1.listFlashcards() == "A\n1\n\n" );
    REQUIRE ( deck1.listFlashcards() == "A\n1\n\n" );

  }

  SECTION ( "simple combine" ) {
    REQUIRE ( deck1.addCard("A", "1") == true );
    REQUIRE ( deck1.addCard("B", "2") == true );
    REQUIRE ( deck1.addCard("C", "3") == true );

    REQUIRE ( deck2.addCard("D", "4") == true );
    REQUIRE ( deck2.addCard("E", "5") == true );
    REQUIRE ( deck2.addCard("F", "6") == true );

    deck1.combineFlashcards(deck2);

    REQUIRE ( deck1.containsCard("A")  == true );
    REQUIRE ( deck1.containsCard("B")  == true );
    REQUIRE ( deck1.containsCard("C")  == true );
    REQUIRE ( deck1.containsCard("D")  == true );
    REQUIRE ( deck1.containsCard("E")  == true );
    REQUIRE ( deck1.containsCard("F")  == true );

    REQUIRE ( deck1.listFlashcards() == "A\n1\n\nB\n2\n\nC\n3\n\nD\n4\n\nE\n5\n\nF\n6\n\n" );

    //deck2 remains unchanged
    REQUIRE ( deck2.containsCard("A")  == false );
    REQUIRE ( deck2.containsCard("B")  == false );
    REQUIRE ( deck2.containsCard("C")  == false );
    REQUIRE ( deck2.containsCard("D")  == true );
    REQUIRE ( deck2.containsCard("E")  == true );
    REQUIRE ( deck2.containsCard("F")  == true );
    REQUIRE ( deck2.listFlashcards() == "D\n4\n\nE\n5\n\nF\n6\n\n" );

    deck2.combineFlashcards(deck1);
    REQUIRE ( deck2.containsCard("A")  == true );
    REQUIRE ( deck2.containsCard("B")  == true );
    REQUIRE ( deck2.containsCard("C")  == true );
    REQUIRE ( deck2.containsCard("D")  == true );
    REQUIRE ( deck2.containsCard("E")  == true );
    REQUIRE ( deck2.containsCard("F")  == true );
    REQUIRE ( deck2.listFlashcards() == "D\n4\n\nE\n5\n\nF\n6\n\nA\n1\n\nB\n2\n\nC\n3\n\n" );
  }

  SECTION ("combine non-unique sets") {
    REQUIRE ( deck1.addCard("A", "1") == true );
    REQUIRE ( deck1.addCard("B", "2") == true );
    REQUIRE ( deck1.addCard("C", "3") == true );
    REQUIRE ( deck1.addCard("D", "4") == true );


    REQUIRE ( deck2.addCard("B", "2") == true );
    REQUIRE ( deck2.addCard("C", "3") == true );
    REQUIRE ( deck2.addCard("D", "4") == true );
    REQUIRE ( deck2.addCard("E", "5") == true );
    REQUIRE ( deck2.addCard("F", "6") == true );

    deck1.combineFlashcards(deck2);

    REQUIRE ( deck1.listFlashcards() == "A\n1\n\nB\n2\n\nC\n3\n\nD\n4\n\nE\n5\n\nF\n6\n\n" );
  }

}


TEST_CASE ( "combine with SHUFFLE", "[shuffle]" ) {

  FlashcardDeck deck1, deck2;

  SECTION ( "combine empty decks" ) {
    deck1.shuffleFlashcards(deck2);
    REQUIRE ( deck1.listFlashcards() == "" );
  }

  SECTION ( "combine one empty deck" ) {
    REQUIRE ( deck1.addCard("A", "1") == true );
    deck1.shuffleFlashcards(deck2);
    deck2.shuffleFlashcards(deck1);
    REQUIRE ( deck1.listFlashcards() == "A\n1\n\n" );
    REQUIRE ( deck1.listFlashcards() == "A\n1\n\n" );

  }

  SECTION ( "combining non-unique sets" ) {
    REQUIRE ( deck1.addCard("A", "1") == true );
    REQUIRE ( deck1.addCard("B", "2") == true );
    REQUIRE ( deck1.addCard("C", "3") == true );


    REQUIRE ( deck2.addCard("D", "4") == true );
    REQUIRE ( deck2.addCard("E", "5") == true );
    REQUIRE ( deck2.addCard("F", "6") == true );
    REQUIRE ( deck2.addCard("G", "7") == true );
    REQUIRE ( deck2.addCard("H", "8") == true );

    deck1.shuffleFlashcards(deck2);

    //check if deck1 is shuffled
    REQUIRE ( deck1.containsCard("A")  == true );
    REQUIRE ( deck1.containsCard("B")  == true );
    REQUIRE ( deck1.containsCard("C")  == true );
    REQUIRE ( deck1.containsCard("D")  == true );
    REQUIRE ( deck1.containsCard("E")  == true );
    REQUIRE ( deck1.containsCard("F")  == true );
    REQUIRE ( deck1.containsCard("G")  == true );
    REQUIRE ( deck1.containsCard("H")  == true );

    REQUIRE ( deck1.listFlashcards() == "A\n1\n\nD\n4\n\nB\n2\n\nE\n5\n\nC\n3\n\nF\n6\n\nG\n7\n\nH\n8\n\n" );


    //deck2 remains unchanged
    REQUIRE ( deck2.containsCard("A")  == false );
    REQUIRE ( deck2.containsCard("B")  == false );
    REQUIRE ( deck2.containsCard("C")  == false );
    REQUIRE ( deck2.containsCard("D")  == true );
    REQUIRE ( deck2.containsCard("E")  == true );
    REQUIRE ( deck2.containsCard("F")  == true );
    REQUIRE ( deck2.containsCard("G")  == true );
    REQUIRE ( deck2.containsCard("H")  == true );
    REQUIRE ( deck2.listFlashcards() == "D\n4\n\nE\n5\n\nF\n6\n\nG\n7\n\nH\n8\n\n" );


    deck2.shuffleFlashcards(deck1);
    //check if deck2 is shuffled
    REQUIRE ( deck2.containsCard("A")  == true );
    REQUIRE ( deck2.containsCard("B")  == true );
    REQUIRE ( deck2.containsCard("C")  == true );
    REQUIRE ( deck2.containsCard("D")  == true );
    REQUIRE ( deck2.containsCard("E")  == true );
    REQUIRE ( deck2.containsCard("F")  == true );
    REQUIRE ( deck2.containsCard("G")  == true );
    REQUIRE ( deck2.containsCard("H")  == true );
    REQUIRE ( deck2.listFlashcards() == "D\n4\n\nA\n1\n\nE\n5\n\nB\n2\n\nF\n6\n\nC\n3\n\nG\n7\n\nH\n8\n\n" );

  }

  SECTION ( "combining non-unique sets with overlap and other has more cards" ) {

    //this
    REQUIRE ( deck2.addCard("D", "4") == true );
    REQUIRE ( deck2.addCard("E", "5") == true );
    REQUIRE ( deck2.addCard("F", "6") == true );
    REQUIRE ( deck2.addCard("G", "7") == true );
    REQUIRE ( deck2.addCard("H", "8") == true );

    //other
    REQUIRE ( deck1.addCard("H", "8") == true );
    REQUIRE ( deck1.addCard("E", "5") == true );
    REQUIRE ( deck1.addCard("A", "1") == true );
    REQUIRE ( deck1.addCard("G", "7") == true );
    REQUIRE ( deck1.addCard("B", "2") == true );
    REQUIRE ( deck1.addCard("C", "3") == true );
    REQUIRE ( deck1.addCard("I", "9") == true );
    REQUIRE ( deck1.addCard("J", "10") == true );
    REQUIRE ( deck1.addCard("K", "11") == true );
    REQUIRE ( deck1.addCard("L", "12") == true );



    deck2.shuffleFlashcards(deck1);
    //check if deck2 is shuffled
    REQUIRE ( deck2.containsCard("A")  == true );
    REQUIRE ( deck2.containsCard("B")  == true );
    REQUIRE ( deck2.containsCard("C")  == true );
    REQUIRE ( deck2.containsCard("D")  == true );
    REQUIRE ( deck2.containsCard("E")  == true );
    REQUIRE ( deck2.containsCard("F")  == true );
    REQUIRE ( deck2.containsCard("G")  == true );
    REQUIRE ( deck2.containsCard("H")  == true );
    REQUIRE ( deck2.containsCard("I")  == true );
    REQUIRE ( deck2.containsCard("J")  == true );
    REQUIRE ( deck2.containsCard("K")  == true );
    REQUIRE ( deck2.containsCard("L")  == true );

    REQUIRE ( deck2.listFlashcards() == "D\n4\n\nA\n1\n\nE\n5\n\nB\n2\n\nF\n6\n\nC\n3\n\nG\n7\n\nI\n9\n\nH\n8\n\nJ\n10\n\nK\n11\n\nL\n12\n\n" );
  }

  SECTION ( "combining non-unique sets with overlap and this is has more cards" ) {
    REQUIRE ( deck1.addCard("H", "8") == true );
    REQUIRE ( deck1.addCard("E", "5") == true );
    REQUIRE ( deck1.addCard("A", "1") == true );
    REQUIRE ( deck1.addCard("G", "7") == true );
    REQUIRE ( deck1.addCard("B", "2") == true );
    REQUIRE ( deck1.addCard("C", "3") == true );
    REQUIRE ( deck1.addCard("F", "6") == true );


    REQUIRE ( deck2.addCard("D", "4") == true );
    REQUIRE ( deck2.addCard("E", "5") == true );
    REQUIRE ( deck2.addCard("F", "6") == true );
    REQUIRE ( deck2.addCard("I", "9") == true );
    REQUIRE ( deck2.addCard("G", "7") == true );
    REQUIRE ( deck2.addCard("H", "8") == true );

    deck1.shuffleFlashcards(deck2);
    //check if deck2 is shuffled
    REQUIRE ( deck1.containsCard("A")  == true );
    REQUIRE ( deck1.containsCard("B")  == true );
    REQUIRE ( deck1.containsCard("C")  == true );
    REQUIRE ( deck1.containsCard("D")  == true );
    REQUIRE ( deck1.containsCard("E")  == true );
    REQUIRE ( deck1.containsCard("F")  == true );
    REQUIRE ( deck1.containsCard("G")  == true );
    REQUIRE ( deck1.containsCard("H")  == true );
    REQUIRE ( deck1.containsCard("I")  == true );

    REQUIRE ( deck1.listFlashcards() == "H\n8\n\nD\n4\n\nE\n5\n\nI\n9\n\nA\n1\n\nG\n7\n\nB\n2\n\nC\n3\n\nF\n6\n\n" );
  }

  SECTION ( "combining sets with same elements but different orders" ) {
    REQUIRE ( deck1.addCard("H", "8") == true );
    REQUIRE ( deck1.addCard("E", "5") == true );
    REQUIRE ( deck1.addCard("A", "1") == true );
    REQUIRE ( deck1.addCard("G", "7") == true );



    REQUIRE ( deck2.addCard("G", "7") == true );
    REQUIRE ( deck2.addCard("E", "5") == true );
    REQUIRE ( deck2.addCard("H", "8") == true );
    REQUIRE ( deck2.addCard("A", "1") == true );


    deck1.shuffleFlashcards(deck2);
    deck2.shuffleFlashcards(deck1);


    //should be unchanged
    REQUIRE ( deck1.containsCard("H")  == true );
    REQUIRE ( deck1.containsCard("E")  == true );
    REQUIRE ( deck1.containsCard("A")  == true );
    REQUIRE ( deck1.containsCard("G")  == true );
    REQUIRE ( deck2.containsCard("H")  == true );
    REQUIRE ( deck2.containsCard("E")  == true );
    REQUIRE ( deck2.containsCard("A")  == true );
    REQUIRE ( deck2.containsCard("G")  == true );

    REQUIRE ( deck1.listFlashcards() == "H\n8\n\nE\n5\n\nA\n1\n\nG\n7\n\n" );
    REQUIRE ( deck2.listFlashcards() == "G\n7\n\nE\n5\n\nH\n8\n\nA\n1\n\n" );

    // Add another card to deck2
    REQUIRE ( deck2.addCard("I", "9") == true );
    deck1.shuffleFlashcards(deck2);
    REQUIRE ( deck2.containsCard("I")  == true );
    REQUIRE ( deck1.listFlashcards() == "H\n8\n\nI\n9\n\nE\n5\n\nA\n1\n\nG\n7\n\n" );

  }

}

TEST_CASE ( "ostream operator for Flashcard", "[ostream]" ) {

  Flashcard card = {"test", "back"};
  stringstream ss;

  //change the underlying buffer and save the old buffer
  auto old_buf = std::cout.rdbuf(ss.rdbuf());
  cout << card; //all the std::cout goes to ss
  std::cout.rdbuf(old_buf); //reset

  REQUIRE ( ss.str() == "test\nback\n\n" );

}
