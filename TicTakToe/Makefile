CXX = g++
OBJECTS = tictactoe.o
FLAGS = -std=c++2a
SOURCE = $(wildcard *.cpp)

demo: $(OBJECTS)
	$(CXX) $(FLAGS) $(OBJECTS) -o demo

%.o: %.cpp
	$(CXX) -c $^


run: demo
	./demo
echo:
	echo $(SOURCE)

clean:
	rm -f *.o demo