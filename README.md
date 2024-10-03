
# **Algorithmic Software Development Project**

**Developed by:**
- Dimitrios Stavros Kostis - AM: 1115201700304
- Orestis Theodorou - AM: 1115202000058

**Course:** Software Development for Algorithmic Problems  
**Semester:** Fall Semester 2023

---

## **Project Overview**

This project focuses on solving algorithmic problems using different computational approaches, including autoencoders for dimension reduction and clustering algorithms for data grouping. The key goals include exploring neural network architectures and clustering techniques to optimize the performance of algorithms on various datasets.

---

## **Project Structure**

The project consists of the following components:

### 1. **Autoencoder for Dimension Reduction**
   - This module implements an autoencoder for reducing the dimensionality of datasets. It includes experiments with different hyperparameters like convolutional layers, filter sizes, and optimizers.
   - The code and results are found in the `autoencoder/` folder.
   - Key files: 
      - `reduce.py`: Main script to perform dimension reduction.
      - Experiment data and results are stored in respective folders.
   - [Autoencoder README for details](path-to-autoencoder-readme).

### 2. **Nearest Neighbor Search Algorithms**
   - Algorithms implemented include:
     - Locality Sensitive Hashing (LSH)
     - Hypercube Nearest Neighbor Search
     - Brute Force Search
   - These algorithms are used to find the nearest neighbors in high-dimensional spaces efficiently.
   - The code and test results are found in the `nearest-neighbors/` folder.
   - Key files:
      - `LSHmain.cpp`: Implements the LSH algorithm.
      - `HypercubeMain.cpp`: Implements the hypercube search algorithm.
      - Other supporting files for functions and data structures.

### 3. **Clustering with K-means**
   - K-means and its variations (K-means++, Lloyd's method) are implemented for clustering data points in different dimensional spaces.
   - Key files:
      - `Kmeans.cpp`: Implements the K-means clustering algorithm.
      - `ClusterMain.cpp`: Main script for clustering experiments.
   - Results for clustering are stored in the `clustering/` folder.

---

## **Installation Instructions**

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/Orestouio/Algorithmic-Software-Development.git
   cd Algorithmic-Software-Development
   ```

2. **Set Up Dependencies**:
   - Ensure you have installed the required software such as **Python 3**, **g++**, and **make**.
   - For Python packages, use:
     ```bash
     pip install -r requirements.txt
     ```
   - For C++ compilation, run:
     ```bash
     make all
     ```

3. **Running the Autoencoder**:
   Navigate to the `autoencoder/` folder and use the following command:
   ```bash
   python reduce.py -d <dataset> -q <queryset> -od <output_dataset_file> -oq <output_query_file>
   ```

4. **Running Nearest Neighbor Search**:
   - To run the LSH or hypercube algorithm, navigate to the `nearest-neighbors/` folder:
   ```bash
   ./lsh <input_file> <query_file> <output_file>
   ./hypercube <input_file> <query_file> <output_file>
   ```

5. **Running K-means Clustering**:
   Navigate to the `clustering/` folder and execute:
   ```bash
   ./kmeans <input_file> <output_file>
   ```

---

## **Results and Analysis**

Each component of the project provides detailed output files that summarize the performance and results of the implemented algorithms. These files are stored in the respective experiment folders (`autoencoder/`, `nearest-neighbors/`, `clustering/`). Plots and tables summarize key findings, such as:

- Model accuracy and loss metrics for the autoencoder.
- Time complexity and accuracy metrics for nearest neighbor search algorithms.
- Clustering accuracy and quality metrics for K-means.

---

## **Contributions and Collaboration**

This project was developed collaboratively using Git for version control and GitHub for collaboration.

---
