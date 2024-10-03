OBJS1	= LSHmain.o HashTableLSH.o ImageVector.o Graph.o Vertex.o Functions.o comFunctions.o exitFunctions.o
OBJS2	= HypercubeMain.o Hypercube.o ImageVector.o CubeFunctions.o DictionaryF.o comFunctions.o exitFunctions.o
OBJS3	= ClusterMain.o ImageVector.o Kmeans.o Cluster.o ClusterFunctions.o comFunctions.o
OBJS4	= GraphSearchmain.o HashTableLSH.o ImageVector.o Functions.o comFunctions.o exitFunctions.o Graph.o Vertex.o

SOURCE1	= LSHmain.cpp HashTableLSH.cpp ImageVector.cpp Graph.cpp Vertex.cpp Functions.cpp comFunctions.cpp exitFuctnions.cpp 
SOURCE2	= HypercubeMain.cpp Hypercube.cpp ImageVector.cpp CubeFunctions.cpp DictionaryF.cpp comFunctions.cpp exitFuctnions.cpp
SOURCE3	= ClusterMain.cpp ImageVector.cpp Kmeans.cpp Cluster.cpp ClusterFunctions.cpp comFunctions.cpp
SOURCE4	= GraphSearchmain.cpp HashTableLSH.cpp ImageVector.cpp Functions.cpp comFunctions.cpp exitFuctnions.cpp Graph.cpp Vertex.cpp

HEADER1	= ImageVector.h HashTableLSH.h Functions.h Neighbour.h comFunctions.h exitFunctions.h
HEADER2	= ImageVector.h Hypercube.h CubeFunctions.h DictionaryF.h comFunctions.h exitFunctions.h
HEADER3	= ImageVector.h Kmeans.h Cluster.h ClusterFunctions.h comFunctions.h
HEADER4	= ImageVector.h HashTableLSH.h Functions.h Neighbour.h comFunctions.h exitFunctions.h Graph.h Vertex.h Edge.h

OUT1	= lsh
OUT2	= cube
OUT3	= cluster
OUT4	= graph_search


CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 


all:	$(OUT1) $(OUT2) $(OUT3) $(OUT4) 

$(OUT1): $(OBJS1) 
	$(CC) -g $(OBJS1) -o $(OUT1) $(LFLAGS)
	
$(OUT2): $(OBJS2) 
	$(CC) -g $(OBJS2) -o $(OUT2) $(LFLAGS)
	
$(OUT3): $(OBJS3) 
	$(CC) -g $(OBJS3) -o $(OUT3) $(LFLAGS)

$(OUT4): $(OBJS4) 
	$(CC) -g $(OBJS4) -o $(OUT4) $(LFLAGS)
	

LSHmain.o: LSHmain.cpp
	$(CC) $(FLAGS) LSHmain.cpp -lcppunit

HashTableLSH.o: HashTableLSH.cpp
	$(CC) $(FLAGS) HashTableLSH.cpp -lcppunit

ImageVector.o: ImageVector.cpp
	$(CC) $(FLAGS) ImageVector.cpp -lcppunit
	
Functions.o: Functions.cpp
	$(CC) $(FLAGS) Functions.cpp -lcppunit
	
HypercubeMain.o: HypercubeMain.cpp
	$(CC) $(FLAGS) HypercubeMain.cpp -lcppunit

exitFunctions.o: exitFunctions.cpp
	$(CC) $(FLAGS) exitFunctions.cpp -lcppunit


	
Hypercube.o: Hypercube.cpp
	$(CC) $(FLAGS) Hypercube.cpp -lcppunit 
	
CubeFunctions.o: CubeFunctions.cpp
	$(CC) $(FLAGS) CubeFunctions.cpp -lcppunit
	
DictionaryF.o: DictionaryF.cpp
	$(CC) $(FLAGS) DictionaryF.cpp -lcppunit
	
	
ClusterMain.o: ClusterMain.cpp
	$(CC) $(FLAGS) ClusterMain.cpp -lcppunit
	
Kmeans.o: Kmeans.cpp
	$(CC) $(FLAGS) Kmeans.cpp -lcppunit
	
Cluster.o: Cluster.cpp
	$(CC) $(FLAGS) Cluster.cpp -lcppunit

ClusterFunctions.o: ClusterFunctions.cpp
	$(CC) $(FLAGS) ClusterFunctions.cpp -lcppunit


comFunctions.o: comFunctions.cpp
	$(CC) $(FLAGS) comFunctions.cpp -lcppunit
	
GraphSearchmain.o: GraphSearchmain.cpp
	$(CC) $(FLAGS) GraphSearchmain.cpp -lcppunit

Graph.o: Graph.cpp
	$(CC) $(FLAGS) Graph.cpp -lcppunit

Vertex.o: Vertex.cpp
	$(CC) $(FLAGS) Vertex.cpp -lcppunit

clean:
	rm -f $(OBJS1) $(OUT1) $(OBJS2) $(OUT2) $(OBJS3) $(OUT3) $(OBJS4) $(OUT4)  
	

