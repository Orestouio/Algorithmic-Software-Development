class ExitFile
{
private:
    struct Neighbor
    {
        int imageNumber;
        double distanceLSH;
        double distanceTrue;
    };

    struct Query
    {
        int queryNumber;
        std::vector<Neighbor> neighbors;
    };

    // int queryImageNumber;
    std::vector<Query>
        Queries;
    double tLSH;
    double tTrue;
    // list<ImageVector *> *table;

public:
    ExitFile();
    ~ExitFile();
    void addNeighbor(int, int, double, double);
    // void createFile(int, int, vector<ImageVector>, bool);
    void createFile(int, int, string, bool);
};

class Exit2
{
private:
    struct Neigh
    {
        int Number;
        double approximate;
        double distanceTrue;
    };

    int imageNumber;
    int N;
    int saved;
    int M;
    std::vector<Neigh> NeighboursFound;

public:
    int file;
    double MAF;
    int time;
    int timeT;
    Exit2(int, int, int, int);
    bool addNeig(int, double, double);
    ~Exit2();
    void createExit2(std::ofstream &outputFile);
};

class ExitFile2
{
private:
    int quees;
    string Filename;

public:
    std::vector<Exit2> Querries;
    ExitFile2(string, int);
    bool addQ(int, int, int, int);
    bool addNeighQ(int, int, int, double, double);
    bool addTimes(int, int, int);
    void createExit();
};