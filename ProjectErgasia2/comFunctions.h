#include <iostream>
#include <string>


//for LSH 
struct CommandLineArgsLsh {
    std::string inputFile;
    std::string queryFile;
    int k = 4;  //Number of LSH functions
    int L = 5;  //Number of tables
    std::string outputFile;
    int numNearest = 1;
    double radius = 10000;
};

//for Cube
struct CommandLineArgsCube {
    std::string inputFile;
    std::string queryFile;
    int k = 14;  //Number of LSH functions
    int M = 10;  //Number of tables
    int probes = 2;
    std::string outputFile;
    int numNearest = 1;
    double radius = 10000;
};


//for Cluster
struct CommandLineArgsCluster {
    std::string inputFile;
    std::string configurationFile;
    //complete variable ;
    std::string outputFile;
    //method to be stored as needed by the code;
};

//for Graph
struct CommandLinesArgsGraph {
    int m = 0;
    std::string inputFile;
    std::string queryFile;
    int k = 50;
    int E = 30;
    int R = 1;
    int N = 1;
    int I = 20;
    //int l;
    std::string outputFile;
};

struct configFile{
    int K; //number_of_clusters
    int L = 3; //number_of_vector_hash_tables
    int k_LSH = 4; //number_of_vector_hash_functions
    int M = 10 ; //max_number_M_hypercube
    int k_HC = 3; //number_of_hypercube_dimensions
    int proves = 2; //number_of_probes
};

CommandLineArgsLsh parseCommandLineArgsLsh(int , char**);
CommandLineArgsCube parseCommandLineArgsCube(int , char**);
CommandLineArgsCluster parseCommandLineArgsCluster(int , char**);
CommandLinesArgsGraph parseCommandLineArgsGraph(int , char**);
configFile parseCommandconfigFile(std::string);