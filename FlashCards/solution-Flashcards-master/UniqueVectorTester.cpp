#include <iostream>
#include <string>
#include "UniqueVector.h"
#include "catch.h"

// This tests that the capacity of UniqueVector is maintained properly throughout a number of insertions
// Note that testVector is reset between each section
TEST_CASE( "Capacity is maintained", "[capacity]" ){

  UniqueVector<int> testVector;

  SECTION( "vector capacity starts off at 3" ){
    REQUIRE( testVector.capacity() == 3 );
  }

  SECTION( "vector capacity doesn't change after inserting <= 3 unique elements" ){
    REQUIRE( testVector.insert(1) == true );
    REQUIRE( testVector.capacity() == 3 );
    REQUIRE( testVector.insert(2) == true );
    REQUIRE( testVector.capacity() == 3 );
    REQUIRE( testVector.insert(3) == true );
    REQUIRE( testVector.capacity() == 3 );
  }

  SECTION( "vector capacity doesn't change after inserting <= 3 non-unique elements" ){
    testVector.insert(1);
    REQUIRE( testVector.capacity() == 3 );
    testVector.insert(2);
    REQUIRE( testVector.capacity() == 3 );
    testVector.insert(3);
    REQUIRE( testVector.capacity() == 3 );

    REQUIRE( testVector.insert(1) == false );
    REQUIRE( testVector.capacity() == 3 );
    REQUIRE( testVector.insert(2) == false );
    REQUIRE( testVector.capacity() == 3 );
    REQUIRE( testVector.insert(3) == false );
    REQUIRE( testVector.capacity() == 3 );
  }

  SECTION( "vector capacity increases accordingly after successive insertions" ){
    testVector.insert(1);
    REQUIRE( testVector.capacity() == 3 );
    testVector.insert(1);
    testVector.insert(2);
    REQUIRE( testVector.capacity() == 3 );
    testVector.insert(2);
    testVector.insert(3);
    REQUIRE( testVector.capacity() == 3 );
    testVector.insert(2);
    testVector.insert(3);
    testVector.insert(4);
    REQUIRE( testVector.capacity() == 6 );
    testVector.insert(3);
    testVector.insert(4);
    testVector.insert(5);
    testVector.insert(5);
    REQUIRE( testVector.capacity() == 6 );
    testVector.insert(6);
    REQUIRE( testVector.capacity() == 6 );
    testVector.insert(7);
    REQUIRE( testVector.capacity() == 12 );
    testVector.insert(8);
    REQUIRE( testVector.capacity() == 12 );
    testVector.insert(9);
    REQUIRE( testVector.capacity() == 12 );
    testVector.insert(10);
    REQUIRE( testVector.capacity() == 12 );
    testVector.insert(11);
    REQUIRE( testVector.capacity() == 12 );
    testVector.insert(12);
    REQUIRE( testVector.capacity() == 12 );
    testVector.insert(13);
    REQUIRE( testVector.capacity() == 24 );
  }
}

// This tests that the size of UniqueVector is maintained properly throughout a number of insertions
TEST_CASE( "Size is maintained", "[size]" ){

  UniqueVector<int> testVector;

  SECTION( "vector size starts off at 0" ){
    REQUIRE( testVector.size() == 0 );
  }

  SECTION( "vector size increases linearly upon inserting unique elements" ){
    testVector.insert(1);
    REQUIRE( testVector.size() == 1 );
    testVector.insert(2);
    REQUIRE( testVector.size() == 2 );
    testVector.insert(3);
    REQUIRE( testVector.size() == 3 );
    testVector.insert(4);
    REQUIRE( testVector.size() == 4 );
    testVector.insert(5);
    REQUIRE( testVector.size() == 5 );
    testVector.insert(6);
    REQUIRE( testVector.size() == 6 );

  }
  SECTION( "vector size doesn't increase upon inserting non-unique elements" ){
    testVector.insert(1);
    REQUIRE( testVector.size() == 1 );
    testVector.insert(2);
    REQUIRE( testVector.size() == 2 );
    testVector.insert(3);
    REQUIRE( testVector.size() == 3 );
    testVector.insert(4);
    REQUIRE( testVector.size() == 4 );
    testVector.insert(5);
    REQUIRE( testVector.size() == 5 );
    testVector.insert(6);
    REQUIRE( testVector.size() == 6 );

    testVector.insert(1);
    REQUIRE( testVector.size() == 6 );
    testVector.insert(2);
    REQUIRE( testVector.size() == 6 );
    testVector.insert(3);
    REQUIRE( testVector.size() == 6 );
    testVector.insert(4);
    REQUIRE( testVector.size() == 6 );
    testVector.insert(5);
    REQUIRE( testVector.size() == 6 );
    testVector.insert(6);
    REQUIRE( testVector.size() == 6 );
  }
}

// This tests that UniqueVector.empty() returns the appropriate boolean value after a number of insertions/removals
TEST_CASE( "emptiness is maintained", "[empty]" ){

  UniqueVector<int> testVector;

  SECTION( "vector empty() is true when no actions has been taken" ){
    REQUIRE( testVector.empty() == true );
  }

  SECTION( "empty() always false after inserting elements"){
    testVector.insert(1);
    REQUIRE( testVector.empty() == false );
    testVector.insert(2);
    REQUIRE( testVector.empty() == false );
    testVector.insert(3);
    REQUIRE( testVector.empty() == false );
  }

  SECTION( "empty() true after inserting 3 elements then removing 3 elements" ){
    testVector.insert(1);
    testVector.insert(2);
    testVector.insert(3);
    REQUIRE( testVector.empty() == false);
    testVector.remove(1);
    REQUIRE( testVector.empty() == false);
    testVector.remove(2);
    REQUIRE( testVector.empty() == false);
    testVector.remove(3);
    REQUIRE( testVector.empty() == true );
  }
}

// This tests contains() to ensure that it returns the correct corresponding boolean value
TEST_CASE( "vector contains all elements inserted and no others", "[contains]" ){
  UniqueVector<int> testVector;

  testVector.insert(1);
  testVector.insert(2);
  testVector.insert(3);
  testVector.insert(4);
  testVector.insert(5);
  testVector.insert(6);
  testVector.insert(7);

  REQUIRE( testVector.contains(1) == true );
  REQUIRE( testVector.contains(2) == true );
  REQUIRE( testVector.contains(3) == true );
  REQUIRE( testVector.contains(4) == true );
  REQUIRE( testVector.contains(5) == true );
  REQUIRE( testVector.contains(6) == true );
  REQUIRE( testVector.contains(7) == true );

  REQUIRE( testVector.contains(8) == false );
  REQUIRE( testVector.contains(9) == false );
  REQUIRE( testVector.contains(10) == false );
  REQUIRE( testVector.contains(11) == false );
  REQUIRE( testVector.contains(12) == false );

}

// This tests that UniqueVector.at() returns the appropriate values after inserting elements
// both the overall boolean return and the 'return by reference'
TEST_CASE( "elements 'at' the correct index", "[at]" ){
  int temp = -1;
  UniqueVector<int> testVector;

  SECTION( "no elements at beginning on empty vector" ){
    REQUIRE( testVector.at(0,temp) == false );
  }

  SECTION( "elements are inserted into consecutive indexes" ){
    testVector.insert(0);
    REQUIRE( testVector.at(0,temp) == true );
    REQUIRE( temp == 0 );

    testVector.insert(1);
    REQUIRE( testVector.at(1,temp) == true );
    REQUIRE( temp == 1 );

    testVector.insert(2);
    REQUIRE( testVector.at(2,temp) == true );
    REQUIRE( temp == 2 );
  }

  SECTION( "elements remain at the right index after enough insertions to resize the vector" ){
    testVector.insert(0);
    testVector.insert(1);
    testVector.insert(2);
    testVector.insert(3);
    testVector.insert(4);

    REQUIRE( testVector.at(0,temp) == true);
    REQUIRE( temp == 0 );
    REQUIRE( testVector.at(1,temp) == true);
    REQUIRE( temp == 1 );
    REQUIRE( testVector.at(2,temp) == true);
    REQUIRE( temp == 2 );
    REQUIRE( testVector.at(3,temp) == true);
    REQUIRE( temp == 3 );
    REQUIRE( testVector.at(4,temp) == true);
    REQUIRE( temp == 4 );


  }

  SECTION( "elements remain at the right index after non-unique insertions" ){
    testVector.insert(0);
    testVector.insert(1);
    testVector.insert(2);

    testVector.insert(1);
    REQUIRE( testVector.at(0,temp) == true);
    REQUIRE( temp == 0 );
    REQUIRE( testVector.at(1,temp) == true);
    REQUIRE( temp == 1 );
    REQUIRE( testVector.at(2,temp) == true);
    REQUIRE( temp == 2 );

    testVector.insert(2);
    REQUIRE( testVector.at(0,temp) == true);
    REQUIRE( temp == 0 );
    REQUIRE( testVector.at(1,temp) == true);
    REQUIRE( temp == 1 );
    REQUIRE( testVector.at(2,temp) == true);
    REQUIRE( temp == 2 );

    testVector.insert(3);
    REQUIRE( testVector.at(0,temp) == true);
    REQUIRE( temp == 0 );
    REQUIRE( testVector.at(1,temp) == true);
    REQUIRE( temp == 1 );
    REQUIRE( testVector.at(2,temp) == true);
    REQUIRE( temp == 2 );
  }

}

// This tests clear() to ensure that the vector returns to a capacity of 3 and a size of 0 after clearing
TEST_CASE( "clear resets capacity and size", "[clear]" ){
  UniqueVector<int> testVector;
  testVector.insert(1);
  testVector.insert(2);
  testVector.insert(3);
  testVector.insert(4);
  testVector.insert(5);
  testVector.insert(6);
  testVector.insert(7);
  testVector.insert(8);
  testVector.insert(9);
  testVector.insert(10);
  testVector.insert(11);
  testVector.insert(12);
  testVector.insert(13);

  REQUIRE( testVector.size() == 13 );
  REQUIRE( testVector.capacity() == 24 );

  testVector.clear();
  REQUIRE( testVector.size() == 0 );
  REQUIRE( testVector.capacity() == 3 );
}

TEST_CASE( "Inserting elements into the vector at a certain position", "[insert at position]"){
  UniqueVector<int> testVector;
  int temp = -1;

  SECTION( "Inserting elements via position into an empty list" ){

    REQUIRE( testVector.insert(100, 1) == false );
    REQUIRE( testVector.insert(100, 0) == true );
    REQUIRE( testVector.size() == 1 );
    REQUIRE( testVector.capacity() == 3 );
    testVector.at(0,temp);
    REQUIRE( temp == 100 );
  }

  SECTION( "Inserting elements into beginning position of a non-empty list" ){

    testVector.insert(200);
    REQUIRE( testVector.insert(100, 0) == true );
    REQUIRE( testVector.size() == 2 );
    REQUIRE( testVector.capacity() == 3 );
    testVector.at(0,temp);
    REQUIRE( temp == 100 );
    testVector.at(1,temp);
    REQUIRE( temp == 200 );

    testVector.insert(300);
    testVector.insert(400);
    REQUIRE( testVector.insert(50, 0) == true );
    REQUIRE( testVector.size() == 5 );
    REQUIRE( testVector.capacity() == 6 );
    testVector.at(0,temp);
    REQUIRE( temp == 50 );
    testVector.at(1,temp);
    REQUIRE( temp == 100 );
    testVector.at(2,temp);
    REQUIRE( temp == 200 );
    testVector.at(3,temp);
    REQUIRE( temp == 300 );
    testVector.at(4,temp);
    REQUIRE( temp == 400 );

    REQUIRE( testVector.insert(50, 0) == false );
    REQUIRE( testVector.insert(100, 0) == false );
    REQUIRE( testVector.insert(200, 0) == false );
    REQUIRE( testVector.insert(300, 0) == false );
    REQUIRE( testVector.insert(400, 0) == false );

  }

  SECTION( "Inserting elements into middle positions of a non-empty list" ){

    testVector.insert(100);
    testVector.insert(200);
    testVector.insert(500);
    testVector.insert(700);
    testVector.insert(800);

    REQUIRE( testVector.insert(300, 2) == true );
    REQUIRE( testVector.size() == 6 );
    REQUIRE( testVector.capacity() == 6 );
    testVector.at(0,temp);
    REQUIRE( temp == 100 );
    testVector.at(1,temp);
    REQUIRE( temp == 200 );
    testVector.at(2,temp);
    REQUIRE( temp == 300 );
    testVector.at(3,temp);
    REQUIRE( temp == 500 );
    testVector.at(4,temp);
    REQUIRE( temp == 700 );
    testVector.at(5,temp);
    REQUIRE( temp == 800 );

    REQUIRE( testVector.insert(400, 3) == true );
    REQUIRE( testVector.size() == 7 );
    REQUIRE( testVector.capacity() == 12 );
    testVector.at(0,temp);
    REQUIRE( temp == 100 );
    testVector.at(1,temp);
    REQUIRE( temp == 200 );
    testVector.at(2,temp);
    REQUIRE( temp == 300 );
    testVector.at(3,temp);
    REQUIRE( temp == 400 );
    testVector.at(4,temp);
    REQUIRE( temp == 500 );
    testVector.at(5,temp);
    REQUIRE( temp == 700 );
    testVector.at(6,temp);
    REQUIRE( temp == 800 );

    REQUIRE( testVector.insert(600, 5) == true );
    REQUIRE( testVector.size() == 8 );
    REQUIRE( testVector.capacity() == 12 );
    testVector.at(0,temp);
    REQUIRE( temp == 100 );
    testVector.at(1,temp);
    REQUIRE( temp == 200 );
    testVector.at(2,temp);
    REQUIRE( temp == 300 );
    testVector.at(3,temp);
    REQUIRE( temp == 400 );
    testVector.at(4,temp);
    REQUIRE( temp == 500 );
    testVector.at(5,temp);
    REQUIRE( temp == 600 );
    testVector.at(6,temp);
    REQUIRE( temp == 700 );
    testVector.at(7,temp);
    REQUIRE( temp == 800 );

    REQUIRE( testVector.insert(300, 1) == false );
    REQUIRE( testVector.insert(300, 3) == false );
    REQUIRE( testVector.insert(300, 5) == false );
    REQUIRE( testVector.insert(400, 1) == false );
    REQUIRE( testVector.insert(400, 3) == false );
    REQUIRE( testVector.insert(400, 5) == false );
    REQUIRE( testVector.insert(600, 1) == false );
    REQUIRE( testVector.insert(600, 3) == false );
    REQUIRE( testVector.insert(600, 5) == false );

  }

  SECTION( "Inserting elements into ending position of a non-empty list" ){

    testVector.insert(100);
    testVector.insert(200);
    testVector.insert(300);
    testVector.insert(400);
    testVector.insert(500);

    REQUIRE( testVector.insert(600, 5) == true );
    REQUIRE( testVector.size() == 6 );
    REQUIRE( testVector.capacity() == 6 );
    testVector.at(0,temp);
    REQUIRE( temp == 100 );
    testVector.at(1,temp);
    REQUIRE( temp == 200 );
    testVector.at(2,temp);
    REQUIRE( temp == 300 );
    testVector.at(3,temp);
    REQUIRE( temp == 400 );
    testVector.at(4,temp);
    REQUIRE( temp == 500 );
    testVector.at(5,temp);
    REQUIRE( temp == 600 );

    REQUIRE( testVector.insert(700, 6) == true );
    REQUIRE( testVector.size() == 7 );
    REQUIRE( testVector.capacity() == 12 );
    testVector.at(0,temp);
    REQUIRE( temp == 100 );
    testVector.at(1,temp);
    REQUIRE( temp == 200 );
    testVector.at(2,temp);
    REQUIRE( temp == 300 );
    testVector.at(3,temp);
    REQUIRE( temp == 400 );
    testVector.at(4,temp);
    REQUIRE( temp == 500 );
    testVector.at(5,temp);
    REQUIRE( temp == 600 );
    testVector.at(6,temp);
    REQUIRE( temp == 700 );

    REQUIRE( testVector.insert(100, 7) == false );
    REQUIRE( testVector.insert(200, 7) == false );
    REQUIRE( testVector.insert(300, 7) == false );
    REQUIRE( testVector.insert(400, 7) == false );
    REQUIRE( testVector.insert(500, 7) == false );
    REQUIRE( testVector.insert(600, 7) == false );
    REQUIRE( testVector.insert(700, 7) == false );
  }


  SECTION( "Inserting elements into out-of-bounds positions of a non-empty list" ){

    testVector.insert(100);
    testVector.insert(200);
    testVector.insert(300);
    testVector.insert(400);
    testVector.insert(500);

    REQUIRE( testVector.insert(600, 6) == false );
    testVector.at(0,temp);
    REQUIRE( temp == 100 );
    testVector.at(1,temp);
    REQUIRE( temp == 200 );
    testVector.at(2,temp);
    REQUIRE( temp == 300 );
    testVector.at(3,temp);
    REQUIRE( temp == 400 );
    testVector.at(4,temp);
    REQUIRE( temp == 500 );

    REQUIRE( testVector.insert(700, 6) == false );
    testVector.at(0,temp);
    REQUIRE( temp == 100 );
    testVector.at(1,temp);
    REQUIRE( temp == 200 );
    testVector.at(2,temp);
    REQUIRE( temp == 300 );
    testVector.at(3,temp);
    REQUIRE( temp == 400 );
    testVector.at(4,temp);
    REQUIRE( temp == 500 );


    REQUIRE( testVector.insert(100, 7) == false );
    REQUIRE( testVector.insert(200, 7) == false );
    REQUIRE( testVector.insert(300, 7) == false );
    REQUIRE( testVector.insert(400, 7) == false );
    REQUIRE( testVector.insert(500, 7) == false );

  }

}

TEST_CASE( "push_front inserts an element at position 0", "[push_front]"){
  UniqueVector<int> testVector;
  int temp = -1;

  SECTION("push_front onto an empty list") {
    REQUIRE( testVector.push_front(0) == true );
    REQUIRE( testVector.size() == 1 );
    REQUIRE( testVector.capacity() == 3 );
    testVector.at(0,temp);
    REQUIRE( temp == 0 );
  }

  SECTION("push_front onto a non-empty list") {
    REQUIRE( testVector.push_front(0) == true );
    REQUIRE( testVector.size() == 1 );
    REQUIRE( testVector.capacity() == 3 );
    testVector.at(0,temp);
    REQUIRE( temp == 0 );

    REQUIRE( testVector.push_front(1) == true );
    REQUIRE( testVector.size() == 2 );
    REQUIRE( testVector.capacity() == 3 );
    testVector.at(0,temp);
    REQUIRE( temp == 1 );
    testVector.at(1,temp);
    REQUIRE( temp == 0 );

    REQUIRE( testVector.push_front(2) == true );
    REQUIRE( testVector.size() == 3 );
    REQUIRE( testVector.capacity() == 3 );
    testVector.at(0,temp);
    REQUIRE( temp == 2 );
    testVector.at(1,temp);
    REQUIRE( temp == 1 );
    testVector.at(2,temp);
    REQUIRE( temp == 0 );

    REQUIRE( testVector.push_front(3) == true );
    REQUIRE( testVector.size() == 4 );
    REQUIRE( testVector.capacity() == 6 );
    testVector.at(0,temp);
    REQUIRE( temp == 3 );
    testVector.at(1,temp);
    REQUIRE( temp == 2 );
    testVector.at(2,temp);
    REQUIRE( temp == 1 );
    testVector.at(3,temp);
    REQUIRE( temp == 0 );

    REQUIRE( testVector.push_front(1) == false);
    REQUIRE( testVector.push_front(2) == false);

  }

}

// This tests remove(data) to ensure that only elements the vector contains can be removed and more importantly
// that the removal of an element results in a corresponding shift of the remaining elements left in the vector
TEST_CASE( "removing element from the vector", "[remove]"){
  UniqueVector<int> testVector;
  int temp = -1;


  SECTION( "Removing elements that exist in the beginning" ){

    testVector.insert(100);
    testVector.insert(200);
    testVector.insert(300);
    testVector.insert(400);
    testVector.insert(500);
    testVector.insert(600);
    testVector.insert(700);
    testVector.insert(800);
    testVector.insert(900);
    testVector.insert(1000);

    REQUIRE( testVector.remove(100) == true );
    REQUIRE( testVector.size() == 9 );
    REQUIRE( testVector.capacity() == 12 );
    REQUIRE( testVector.contains(100) == false );
    testVector.at(0,temp);
    REQUIRE( temp == 200 );
    testVector.at(1,temp);
    REQUIRE( temp == 300 );
    testVector.at(2,temp);
    REQUIRE( temp == 400 );
    testVector.at(3,temp);
    REQUIRE( temp == 500 );
    testVector.at(4,temp);
    REQUIRE( temp == 600 );
    testVector.at(5,temp);
    REQUIRE( temp == 700 );
    testVector.at(6,temp);
    REQUIRE( temp == 800 );
    testVector.at(7,temp);
    REQUIRE( temp == 900 );
    testVector.at(8,temp);
    REQUIRE( temp == 1000 );

    REQUIRE( testVector.remove(200) == true );
    REQUIRE( testVector.size() == 8 );
    REQUIRE( testVector.capacity() == 12 );
    REQUIRE( testVector.contains(200) == false );
    testVector.at(0,temp);
    REQUIRE( temp == 300 );
    testVector.at(1,temp);
    REQUIRE( temp == 400 );
    testVector.at(2,temp);
    REQUIRE( temp == 500 );
    testVector.at(3,temp);
    REQUIRE( temp == 600 );
    testVector.at(4,temp);
    REQUIRE( temp == 700 );
    testVector.at(5,temp);
    REQUIRE( temp == 800 );
    testVector.at(6,temp);
    REQUIRE( temp == 900 );
    testVector.at(7,temp);
    REQUIRE( temp == 1000 );

  }

  SECTION( "Removing middle elements" ){
    testVector.insert(100);
    testVector.insert(200);
    testVector.insert(300);
    testVector.insert(400);
    testVector.insert(500);
    testVector.insert(600);
    testVector.insert(700);
    testVector.insert(800);
    testVector.insert(900);
    testVector.insert(1000);

    REQUIRE( testVector.remove(400) == true );
    REQUIRE( testVector.size() == 9 );
    REQUIRE( testVector.capacity() == 12 );
    REQUIRE( testVector.contains(400) == false );
    testVector.at(0,temp);
    REQUIRE( temp == 100 );
    testVector.at(1,temp);
    REQUIRE( temp == 200 );
    testVector.at(2,temp);
    REQUIRE( temp == 300 );
    testVector.at(3,temp);
    REQUIRE( temp == 500 );
    testVector.at(4,temp);
    REQUIRE( temp == 600 );
    testVector.at(5,temp);
    REQUIRE( temp == 700 );
    testVector.at(6,temp);
    REQUIRE( temp == 800 );
    testVector.at(7,temp);
    REQUIRE( temp == 900 );
    testVector.at(8,temp);
    REQUIRE( temp == 1000 );

    REQUIRE( testVector.remove(600) == true );
    REQUIRE( testVector.size() == 8 );
    REQUIRE( testVector.capacity() == 12 );
    REQUIRE( testVector.contains(600) == false );
    testVector.at(0,temp);
    REQUIRE( temp == 100 );
    testVector.at(1,temp);
    REQUIRE( temp == 200 );
    testVector.at(2,temp);
    REQUIRE( temp == 300 );
    testVector.at(3,temp);
    REQUIRE( temp == 500 );
    testVector.at(4,temp);
    REQUIRE( temp == 700 );
    testVector.at(5,temp);
    REQUIRE( temp == 800 );
    testVector.at(6,temp);
    REQUIRE( temp == 900 );
    testVector.at(7,temp);
    REQUIRE( temp == 1000 );
  }

  SECTION( "Removing last elements" ){
    testVector.insert(100);
    testVector.insert(200);
    testVector.insert(300);
    testVector.insert(400);
    testVector.insert(500);
    testVector.insert(600);
    testVector.insert(700);
    testVector.insert(800);
    testVector.insert(900);
    testVector.insert(1000);

    REQUIRE( testVector.remove(1000) == true );
    REQUIRE( testVector.size() == 9 );
    REQUIRE( testVector.capacity() == 12 );
    REQUIRE( testVector.contains(1000) == false );
    testVector.at(0,temp);
    REQUIRE( temp == 100 );
    testVector.at(1,temp);
    REQUIRE( temp == 200 );
    testVector.at(2,temp);
    REQUIRE( temp == 300 );
    testVector.at(3,temp);
    REQUIRE( temp == 400 );
    testVector.at(4,temp);
    REQUIRE( temp == 500 );
    testVector.at(5,temp);
    REQUIRE( temp == 600 );
    testVector.at(6,temp);
    REQUIRE( temp == 700 );
    testVector.at(7,temp);
    REQUIRE( temp == 800 );
    testVector.at(8,temp);
    REQUIRE( temp == 900 );

    REQUIRE( testVector.remove(900) == true );
    REQUIRE( testVector.size() == 8 );
    REQUIRE( testVector.capacity() == 12 );
    REQUIRE( testVector.contains(900) == false );
    testVector.at(0,temp);
    REQUIRE( temp == 100 );
    testVector.at(1,temp);
    REQUIRE( temp == 200 );
    testVector.at(2,temp);
    REQUIRE( temp == 300 );
    testVector.at(3,temp);
    REQUIRE( temp == 400 );
    testVector.at(4,temp);
    REQUIRE( temp == 500 );
    testVector.at(5,temp);
    REQUIRE( temp == 600 );
    testVector.at(6,temp);
    REQUIRE( temp == 700 );
    testVector.at(7,temp);
    REQUIRE( temp == 800 );

  }

}

// This tests remove(pos, data) to ensure that only elements the vector contains can be removed and more importantly
// that the removal of an element results in a corresponding shift of the remaining elements left in the vector
TEST_CASE( "removing elements from the vector via position", "[remove by position]"){

  UniqueVector<int> testVector;
  int temp = -1;

  SECTION( "Removing elements that exist in the beginning" ){

    testVector.insert(100);
    testVector.insert(200);
    testVector.insert(300);
    testVector.insert(400);
    testVector.insert(500);
    testVector.insert(600);
    testVector.insert(700);
    testVector.insert(800);
    testVector.insert(900);
    testVector.insert(1000);

    REQUIRE( testVector.remove(0,temp) == true );
    REQUIRE( temp == 100 );
    REQUIRE( testVector.size() == 9 );
    REQUIRE( testVector.capacity() == 12 );
    REQUIRE( testVector.contains(100) == false );
    testVector.at(0,temp);
    REQUIRE( temp == 200 );
    testVector.at(1,temp);
    REQUIRE( temp == 300 );
    testVector.at(2,temp);
    REQUIRE( temp == 400 );
    testVector.at(3,temp);
    REQUIRE( temp == 500 );
    testVector.at(4,temp);
    REQUIRE( temp == 600 );
    testVector.at(5,temp);
    REQUIRE( temp == 700 );
    testVector.at(6,temp);
    REQUIRE( temp == 800 );
    testVector.at(7,temp);
    REQUIRE( temp == 900 );
    testVector.at(8,temp);
    REQUIRE( temp == 1000 );

    REQUIRE( testVector.remove(0,temp) == true );
    REQUIRE( temp == 200 );
    REQUIRE( testVector.size() == 8 );
    REQUIRE( testVector.capacity() == 12 );
    REQUIRE( testVector.contains(200) == false );
    testVector.at(0,temp);
    REQUIRE( temp == 300 );
    testVector.at(1,temp);
    REQUIRE( temp == 400 );
    testVector.at(2,temp);
    REQUIRE( temp == 500 );
    testVector.at(3,temp);
    REQUIRE( temp == 600 );
    testVector.at(4,temp);
    REQUIRE( temp == 700 );
    testVector.at(5,temp);
    REQUIRE( temp == 800 );
    testVector.at(6,temp);
    REQUIRE( temp == 900 );
    testVector.at(7,temp);
    REQUIRE( temp == 1000 );

  }

  SECTION( "Removing middle elements" ){
    testVector.insert(100);
    testVector.insert(200);
    testVector.insert(300);
    testVector.insert(400);
    testVector.insert(500);
    testVector.insert(600);
    testVector.insert(700);
    testVector.insert(800);
    testVector.insert(900);
    testVector.insert(1000);

    REQUIRE( testVector.remove(3,temp) == true );
    REQUIRE( temp == 400 );
    REQUIRE( testVector.size() == 9 );
    REQUIRE( testVector.capacity() == 12 );
    REQUIRE( testVector.contains(400) == false );
    testVector.at(0,temp);
    REQUIRE( temp == 100 );
    testVector.at(1,temp);
    REQUIRE( temp == 200 );
    testVector.at(2,temp);
    REQUIRE( temp == 300 );
    testVector.at(3,temp);
    REQUIRE( temp == 500 );
    testVector.at(4,temp);
    REQUIRE( temp == 600 );
    testVector.at(5,temp);
    REQUIRE( temp == 700 );
    testVector.at(6,temp);
    REQUIRE( temp == 800 );
    testVector.at(7,temp);
    REQUIRE( temp == 900 );
    testVector.at(8,temp);
    REQUIRE( temp == 1000 );

    REQUIRE( testVector.remove(4,temp) == true );
    REQUIRE( temp == 600 );
    REQUIRE( testVector.size() == 8 );
    REQUIRE( testVector.capacity() == 12 );
    REQUIRE( testVector.contains(600) == false );
    testVector.at(0,temp);
    REQUIRE( temp == 100 );
    testVector.at(1,temp);
    REQUIRE( temp == 200 );
    testVector.at(2,temp);
    REQUIRE( temp == 300 );
    testVector.at(3,temp);
    REQUIRE( temp == 500 );
    testVector.at(4,temp);
    REQUIRE( temp == 700 );
    testVector.at(5,temp);
    REQUIRE( temp == 800 );
    testVector.at(6,temp);
    REQUIRE( temp == 900 );
    testVector.at(7,temp);
    REQUIRE( temp == 1000 );
  }

  SECTION( "Removing last elements" ){
    testVector.insert(100);
    testVector.insert(200);
    testVector.insert(300);
    testVector.insert(400);
    testVector.insert(500);
    testVector.insert(600);
    testVector.insert(700);
    testVector.insert(800);
    testVector.insert(900);
    testVector.insert(1000);

    REQUIRE( testVector.remove(9,temp) == true );
    REQUIRE( temp == 1000 );
    REQUIRE( testVector.size() == 9 );
    REQUIRE( testVector.capacity() == 12 );
    REQUIRE( testVector.contains(1000) == false );
    testVector.at(0,temp);
    REQUIRE( temp == 100 );
    testVector.at(1,temp);
    REQUIRE( temp == 200 );
    testVector.at(2,temp);
    REQUIRE( temp == 300 );
    testVector.at(3,temp);
    REQUIRE( temp == 400 );
    testVector.at(4,temp);
    REQUIRE( temp == 500 );
    testVector.at(5,temp);
    REQUIRE( temp == 600 );
    testVector.at(6,temp);
    REQUIRE( temp == 700 );
    testVector.at(7,temp);
    REQUIRE( temp == 800 );
    testVector.at(8,temp);
    REQUIRE( temp == 900 );

    REQUIRE( testVector.remove(8,temp) == true );
    REQUIRE( temp == 900 );
    REQUIRE( testVector.size() == 8 );
    REQUIRE( testVector.capacity() == 12 );
    REQUIRE( testVector.contains(900) == false );
    testVector.at(0,temp);
    REQUIRE( temp == 100 );
    testVector.at(1,temp);
    REQUIRE( temp == 200 );
    testVector.at(2,temp);
    REQUIRE( temp == 300 );
    testVector.at(3,temp);
    REQUIRE( temp == 400 );
    testVector.at(4,temp);
    REQUIRE( temp == 500 );
    testVector.at(5,temp);
    REQUIRE( temp == 600 );
    testVector.at(6,temp);
    REQUIRE( temp == 700 );
    testVector.at(7,temp);
    REQUIRE( temp == 800 );
  }

  SECTION ("removing from empty list") {

    REQUIRE ( testVector.remove(1000) == false );
    REQUIRE ( testVector.remove(0,temp) == false );


  }

}

TEST_CASE("pop_back removes last element in vector","[pop_back]"){
  UniqueVector<int> testVector;
  int temp = -1;

  REQUIRE( testVector.pop_back(temp) == false );

  testVector.insert(0);
  testVector.insert(1);
  testVector.insert(2);
  testVector.insert(3);
  testVector.insert(4);

  REQUIRE( testVector.pop_back(temp) == true );
  REQUIRE( temp == 4 );
  REQUIRE( testVector.pop_back(temp) == true );
  REQUIRE( temp == 3 );
  REQUIRE( testVector.pop_back(temp) == true );
  REQUIRE( temp == 2 );
  REQUIRE( testVector.pop_back(temp) == true );
  REQUIRE( temp == 1 );
  REQUIRE( testVector.pop_back(temp) == true );
  REQUIRE( temp == 0 );
  REQUIRE( testVector.pop_back(temp) == false );

  REQUIRE( testVector.empty() == true );
  REQUIRE( testVector.size() == 0 );

}

TEST_CASE("equality operator compares two vectors", "[equality]"){
  UniqueVector<int> testVector1;
  UniqueVector<int> testVector2;
  REQUIRE( testVector1 == testVector2 );

  testVector1.insert(0);

  REQUIRE( (testVector1 == testVector2) == false);

  testVector1.insert(1);
  testVector1.insert(2);
  testVector1.insert(3);
  testVector1.insert(4);

  testVector2.insert(0);
  testVector2.insert(1);
  testVector2.insert(2);
  testVector2.insert(3);
  testVector2.insert(4);

  REQUIRE( testVector1 == testVector2 );

  testVector1.remove(2);
  testVector1.remove(3);

  REQUIRE( (testVector1 == testVector2) == false );

  testVector2.remove(2);
  testVector2.remove(3);

  REQUIRE( testVector1 == testVector2 );

  testVector1.clear();
  testVector2.clear();

  REQUIRE( testVector1 == testVector2 );

}
