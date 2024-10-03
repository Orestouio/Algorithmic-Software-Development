OBJS	= GraphSearchmain.o HashTableLSH.o ImageVector.o Functions.o comFunctions.o exitFunctions.o Graph.o Vertex.o


SOURCE	= GraphSearchmain.cppHashTableLSH.cpp ImageVector.cpp Functions.cpp comFunctions.cpp exitFuctnions.cpp Graph.cpp Vertex.cpp


HEADER	= ImageVector.h HashTableLSH.h Functions.h Neighbour.h comFunctions.h exitFunctions.h Graph.h Vertex.h Edge.h


OUT	= graph_search


CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 


all: $(OUT)

$(OUT): $(OBJS) 
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)
	

HashTableLSH.o: HashTableLSH.cpp
	$(CC) $(FLAGS) HashTableLSH.cpp -lcppunit

ImageVector.o: ImageVector.cpp
	$(CC) $(FLAGS) ImageVector.cpp -lcppunit
	
Functions.o: Functions.cpp
	$(CC) $(FLAGS) Functions.cpp -lcppunit
	

exitFunctions.o: exitFunctions.cpp
	$(CC) $(FLAGS) exitFunctions.cpp -lcppunit


comFunctions.o: comFunctions.cpp
	$(CC) $(FLAGS) comFunctions.cpp -lcppunit
	
GraphSearchmain.o: GraphSearchmain.cpp
	$(CC) $(FLAGS) GraphSearchmain.cpp -lcppunit

Graph.o: Graph.cpp
	$(CC) $(FLAGS) Graph.cpp -lcppunit

Vertex.o: Vertex.cpp
	$(CC) $(FLAGS) Vertex.cpp -lcppunit

clean:
	rm -f $(OBJS) $(OUT)  
	

