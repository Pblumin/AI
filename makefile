checker.exe: playGame.o board.o ai.o
	g++  -std=c++11 -o checker.exe playGame.o board.o ai.o

playGame.o: playGame.cpp 
	g++  -std=c++11 -c playGame.cpp

board.o: board.cpp board.h
	g++  -std=c++11 -c board.cpp

ai.o: ai.cpp ai.h
	g++  -std=c++11 -c ai.cpp

debug:
	g++  -std=c++11 -g -o playDebug.exe playGame.cpp board.cpp ai.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups