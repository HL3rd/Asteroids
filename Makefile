# Makefile for asteroids.pp
# Horacio Lopez and Yifan Yu

CMP = g++ -std=c++11
CLASS = ast_move
MAIN = project
EXEC = run

$(EXEC): $(CLASS).o $(MAIN).o $(CLASS).h
	$(CMP) $(CLASS).o $(MAIN).o gfx.o -lX11 -o $(EXEC)

$(CLASS).o: $(CLASS).cpp $(CLASS).h
	$(CMP) -c $(CLASS).cpp -o $(CLASS).o

$(MAIN).o: $(MAIN).cpp $(CLASS).h
	$(CMP) -c $(MAIN).cpp -o $(MAIN).o

clean:
	rm *.o
	rm $(EXEC)
