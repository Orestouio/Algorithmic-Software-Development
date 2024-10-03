
# UNIVERSITY OF ATHENS
## DEPARTMENT OF INFORMATICS AND TELECOMMUNICATIONS

### **Dimension Reduction Using Autoencoders**

**Student names:**
- Dimitrios Stavros Kostis - AM: 1115201700304
- Orestis Theodorou - ΑΜ: 1115202000058

**Course:** Software Development for Algorithmic Problems  
**Semester:** Fall Semester 2023

## Contents:

1. Question 1  
    1.1 Abstract  
    1.2 Convolutional Layer Number  
    1.3 Filter Size  
    1.4 Filter Number  
    1.5 Epochs  
    1.6 Batch Size  
    1.7 Optimizers  
    1.8 Activation Layers  
   
2. Question 2  
3. Question 3

---

### **1. Question 1**

#### **1.1 Abstract**
In this project, we will attempt to construct an autoencoder with which we will perform a series of experiments on tuning its hyperparameters to achieve an optimal model. During the preprocessing phase, we will normalize our dataset to have values between [0,1]. The metrics we will use to evaluate our model are the Mean Squared Error (MSE), the Structural Similarity Index Measure (SSIM), which is a measure of the quality of two compared images (i.e., how similar two images are in terms of structure, brightness, and contrast), and the training loss/validation loss.

The project was developed on Google Colab. While the process worked fine in Google Colab, when using the same code locally, the process did not work due to excessive memory usage during prediction. We created a prediction function using batches, but this did not work either. Therefore, we only export the query file with lower dimensions.

Execution command:

```
python reduce.py -d <dataset> -q <queryset> -od <output_dataset_file> -oq <output_query_file>
```

The project was implemented using Git version control and collaboration:  
[GitHub Repository](https://github.com/dimitriskostis/ProjectErgasia3/tree/main)
