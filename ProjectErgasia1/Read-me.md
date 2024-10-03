
# SOFTWARE DEVELOPMENT FOR ALGORITHMIC PROBLEMS

## 1st Programming Project: Vector Search and Clustering

**Team Members:**
- Dimitrios Stavros Kostis (ID: 1115201700304)
- Orestis Theodorou (ID: 1115202000058)

In the following files, we implement the creation of an LSH (Locality Sensitive Hashing) algorithm and a hypercube structure for finding nearest neighbors, as well as the implementation of the K-means algorithm for finding clusters.

### LSH Algorithm

The LSH algorithm is implemented in the following files:

- **LSHmain.cpp**: 
  Contains the main function, which based on input variables, creates the LSH hash table based on MNIST images, inserts the queries, and finds their nearest neighbors. It also calls functions to find the nearest neighbors using BruteForce. Lastly, it calls output functions to write the results into an output file with the appropriate information.

- **ImageVector.cpp** and **ImageVector.h**: 
  The `ImageVector` class represents the vector of MNIST images and contains additional information for each image and corresponding functions that help in the LSH implementation. These functions manage neighbor elements that store data points representing the nearest neighbors.

- **HashTableLSH.cpp** and **HashTableLSH.h**: 
  The `Hash_Table_LSH` class implements the LSH algorithm.

### Functions

The following functions are implemented in **Functions.cpp** and **Functions.h**:

- `calculateEuclideanDistance`: Computes the Euclidean distance between two `ImageVectors`.
- `CreateHashTables`: Creates the LSH hash tables (custom `w` values are used).
- `readImages`: Reads an MNIST dataset file and inserts each data point into an `ImageVector`.
- `readQuery`: Reads the query with MNIST dataset specifications and returns the corresponding `ImageVector`.
- `BruteForce`: Finds the nearest neighbors using a brute-force approach, calling `FindNearestNeighborsBruteForce`, which calculates the distance of each image from the query.

### Exit Functions

In **exitFunctions.cpp** and **exitFunctions.h**, we define:
- `ExitFile` structure that stores the information needed for the output file.
- `createFile`: Generates the output file based on the specified format.

### Hash Functions

In **HashTableLSH.cpp** and **HashTableLSH.h**, we implement the following functions:

- `NormalDistributionSeeder`: Generates normally distributed values for the `v[]` array used to create the `h` functions.
- `UniformDistributionSeeder`: Generates uniformly distributed values for the `t[]` array for the `h` functions.
- `calculateH`: Computes the `h` functions.
- `AmplifiedFunctionG`: Computes the index using the `G` function.
- `InsertItem`: Finds the index and inserts the data point into the LSH hash table.
- `FakeInsert`: Finds the index for insertion without actually inserting the element.
- `FindNeighbours`: Finds the nearest neighbors for each query.
- `LSHnn`: Finds the nearest neighbors using the LSH hash table.
- `RangeSearch`: Finds the nearest neighbors within a given radius.

### HyperCube

The following functions are implemented in **HyperCube.cpp** and **HyperCube.h**:

- `getIndex`: Retrieves the index.
- `CalculateF`: Computes the `F` value to determine the cube's vertex where the item is stored.
- `InsertItem`: Inserts the data point into the hypercube at the correct index.
- `FakeInsert`: Finds the index without inserting the data point.
- `FindNeighbours`: Finds the nearest neighbors by searching the vertex and other `m` vertices.
- `PrintTable`: Prints the cube's elements.
- `GetProbe`: Retrieves the vertex to probe based on Hamming distance.
- `RangeSearch`: Finds the nearest neighbors within a given radius.
- `CubeSearch`: Finds the nearest neighbors using the hypercube structure.
- `BruteForce`: Performs an exhaustive search within the cube.

### K-means Algorithm

Implemented in **Kmeans.cpp** and **Kmeans.h**:

- `InitializationKmeansPlusPlus`: Initializes K-means++.
- `LloydMethod`: Assigns data points using Lloyd's method.
- `MacQueenMethod`: Partially implements MacQueen’s method.
- `PrintClusters`: Prints the clusters.
- `PrintCentroids`: Prints the centroids.

### Cluster

In **Cluster.cpp** and **Cluster.h**, the `Cluster` class represents a cluster.

Helper functions for K-means are implemented in **ClusterFunctions.cpp** and **ClusterFunctions.h**.

The main K-means initialization and update function is in **ClusterMain.cpp**.

### Makefile

The **Makefile** compiles the files and generates the executable files (`lsh`, `cube`, and `cluster`). These executables follow the project specifications.

To compile: `make all`  
To clean: `make clean`

The project was implemented using version control and collaboration tools (git).
