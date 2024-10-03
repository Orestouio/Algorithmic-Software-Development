#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#include "comFunctions.h"


using namespace std;

CommandLineArgsLsh parseCommandLineArgsLsh(int argc, char* argv[]) {
    CommandLineArgsLsh args;
    if(argc< 5){
        cout << "Not enough arguments in command line." << endl;
        exit(1);
    }
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "-d") {
            args.inputFile = argv[++i];
        } else if (arg == "-q") {
            args.queryFile = argv[++i];
        } else if (arg == "-k") {
            args.k = stoi(argv[++i]);
        } else if (arg == "-L") {
            args.L = stoi(argv[++i]);
        } else if (arg == "-o") {
            args.outputFile = argv[++i];
        } else if (arg == "-N") {
            args.numNearest = stoi(argv[++i]);
        } else if (arg == "-R") {
            args.radius = stod(argv[++i]);
        }
    }
    return args;
}




CommandLineArgsCube parseCommandLineArgsCube(int argc, char* argv[]){
    CommandLineArgsCube args;
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "-d") {
            args.inputFile = argv[++i];
        } else if (arg == "-q") {
            args.queryFile = argv[++i];
        } else if (arg == "-k") {
            args.k = stoi(argv[++i]);
        } else if (arg == "-M") {
            args.M = stoi(argv[++i]);
        } else if(arg == "-probes"){
            args.probes = stoi(argv[++i]);
        }else if (arg == "-o") {
            args.outputFile = argv[++i];
        } else if (arg == "-N") {
            args.numNearest = stoi(argv[++i]);
        } else if (arg == "-R") {
            args.radius = stod(argv[++i]);
        }
    }
    return args;
}


CommandLineArgsCluster parseCommandLineArgsCluster(int argc, char* argv[]){
    CommandLineArgsCluster args;
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "-i") {
            args.inputFile = argv[++i];
        } else if (arg == "-c") {
            args.configurationFile = argv[++i];
        } else if (arg == "-complete") {
            ++i;
            //args.variable = stoi(argv[++i]);
        } else if (arg == "-m") {
            //if(argv[++i] == "Classic" || argv[i] == "LSH" || argv[i] == "Hypercube")
            //args.method = stoi(argv[i]);
            cout << "Not implemented yet" << endl;
        } 
    }
    return args;
}


configFile parseCommandconfigFile(std::string file){
    configFile conf;
    // Open the configuration file for reading
    std::ifstream configFile(file);
    if (configFile.is_open()) {
        std::string line;
        while (std::getline(configFile, line)) {
            // Split the line into words
            std::istringstream iss(line);
            std::string key;
            std::string value;

            if (iss >> key >> value) {
                if (key == "number_of_clusters:") {
                    conf.K = std::stoi(value);
                } else if (key == "number_of_vector_hash_tables:") {
                    conf.L = std::stoi(value);
                } else if (key == "number_of_vector_hash_functions:") {
                    conf.k_LSH = std::stoi(value);
                } else if (key == "max_number_M_hypercube:") {
                    conf.M = std::stoi(value);
                } else if (key == "number_of_hypercube_dimensions:") {
                    conf.k_HC = std::stoi(value);
                } else if (key == "number_of_probes:") {
                    conf.proves = std::stoi(value);
                }
            }
        }

        configFile.close();
    }
    return conf;
}