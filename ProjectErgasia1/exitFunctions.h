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
    //void createFile(int, int, vector<ImageVector>, bool);
    void createFile(int, int, string, bool);
};