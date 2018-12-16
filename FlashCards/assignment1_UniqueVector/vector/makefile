CC = g++
LFLAGS = -std=c++11
CFLAGS = -c -Wall

# Set the EXECUTABLE_NAME variable to the preferred generated executable name
# Set the SOURCES variable to a space-separated list of all the .cpp files to compile
EXECUTABLE_NAME = Flashcards
SOURCES = Flashcard.h Flashcard.cpp UniqueVector.h UniqueVector.cpp catch.h FlashcardDeck.h FlashcardDeck.cpp FlashcardDeckTester.cpp main.cpp
#SOURCES = UniqueVector.h UniqueVector.cpp catch.h UniqueVectorTester.cpp main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(EXECUTABLE_NAME)

$(EXECUTABLE_NAME): $(OBJECTS)
	$(CC) -o $(EXECUTABLE_NAME) $(OBJECTS)

.cpp.o:
	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@

clean:
	$(RM) *.o *~ $(EXECUTABLE_NAME)
