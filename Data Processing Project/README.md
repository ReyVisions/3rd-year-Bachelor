# Digital Data Processing (TND) Project

**Author**: Remy XU
**Project type**: Group Project of 3 students

## Overview

This project, conducted by Team 3, focuses on the analysis of the Haberman dataset, which contains medical data related to the survival of patients who underwent surgery for breast cancer. The analysis includes univariate, bivariate, and multivariate statistical techniques to understand the factors influencing patient survival.

## Table of Contents

1. [Introduction](#introduction)
2. [Dataset Description](#dataset-description)
3. [Preprocessing](#preprocessing)
4. [Univariate Analysis](#univariate-analysis)
5. [Bivariate Analysis](#bivariate-analysis)
6. [Multivariate Analysis](#multivariate-analysis)
7. [Conclusion](#conclusion)
8. [Appendix](#appendix)

## Introduction

As part of the Digital Data Processing course, this report details our observations and comments after analyzing the Haberman dataset. The analysis includes a detailed description of the methods used, as well as an analysis and commentary on the results obtained.

## Dataset Description

### Overview

The dataset was provided in two files:

- `haberman.data`: Contains the data with columns separated by commas and rows by new lines.
- `haberman.names`: Provides additional information about the nature, origin of the data, and the names of the different columns in the dataset.

### Reading the Dataset

The Haberman dataset contains no missing values and consists of 306 instances defined by the following 4 variables:

- Age of patient at time of operation (numerical, integer): Represents the patient's age at the time of the operation. This is a discrete quantitative variable.
- Patient's year of operation (numerical, integer): Represents the year in which the patient underwent the operation. This is a discrete quantitative variable.
- Number of positive axillary nodes detected (numerical): Represents the number of positive axillary nodes detected in the patient. This is a discrete quantitative variable.
- Survival status (numerical): Represents the survival status of the patient after the operation. This is a binary qualitative variable with two categories: 1 = the patient survived 5 years or more, and 2 = the patient died within 5 years.

## Preprocessing

- The dataset contains no missing values.
- Only the "Survival Status" variable is a binary categorical variable (1 or 2), which can be considered as an additional variable in the subsequent analysis of this dataset.

## Univariate Analysis

### Quantitative Variables

#### Position Criteria

Using the "summary" command, we obtained an overview of the different distributions of the variables in our dataset by calculating basic statistics for each variable. This helped us detect any anomalies in their distributions and obtain some orders of magnitude for each attribute in the dataset.

| Age | Operation Year | Positive Axillary Nodes |
|-----|----------------|------------------------|
| Min.: 30.00 | Min.: 58.00 | Min.: 0.000 |
| 1st Qu.: 44.00 | 1st Qu.: 60.00 | 1st Qu.: 0.000 |
| Median: 52.00 | Median: 63.00 | Median: 1.000 |
| Mean: 52.46 | Mean: 62.85 | Mean: 4.026 |
| 3rd Qu.: 60.75 | 3rd Qu.: 65.75 | 3rd Qu.: 4.000 |
| Max.: 83.00 | Max.: 69.00 | Max.: 52.000 |

#### Dispersion Criteria

| Variable | Range | Variance | Standard Deviation | Conclusion |
|----------|-------|----------|--------------------|------------|
| Age of patient at time of operation | 53 | 116.7146 | 10.80345 | The distribution of patients' ages at the time of operation shows significant variation, with a range of 53 years. This indicates considerable diversity in the ages of patients in the sample. |
| Patient's year of operation | 11 | 10.55863 | 3.249405 | The years of patients' operations show a relatively narrow range of 11 years. This indicates that the operations were performed over a specific and limited period. |
| Number of positive axillary nodes detected | 52 | 51.69112 | 7.189654 | The number of positive axillary nodes detected varies considerably. This indicates a significant disparity in the results of positive axillary node detection tests among patients. |

### Qualitative Variables

The only qualitative variable is the "Survival Status," which indicates whether a patient survived for 5 years or more after the operation (value 1) or died within 5 years following the operation (value 2).

#### Absolute Frequency

- For value 1, indicating long-term survival, the frequency is 225.
- For value 2, indicating non-long-term survival, the frequency is 81.

#### Relative Frequency

- For value 1, the relative frequency is approximately 73.53%.
- For value 2, the relative frequency is approximately 26.47%.

#### Interpretation

There appears to be a greater number of patients who survived for 5 years or more compared to those who died within 5 years after the operation. This indicates that the data is not balanced. This difference could be explored to understand the factors influencing patient survival.

## Bivariate Analysis

### Correlation

Most pairs of variables are weakly correlated. The age and year of operation show a weak positive correlation (0.0895), indicating that older patients tend to be operated on later. The age and number of positive axillary nodes show a weak negative correlation (-0.0632), indicating that older patients tend to have a lower number of positive axillary nodes. The year of operation and the number of positive axillary nodes show a very weak negative correlation (-0.0038), indicating that patients operated on later tend to have a lower number of positive axillary nodes. The number of positive axillary nodes and survival status show a moderate positive correlation (0.2868), indicating that patients with a higher number of positive axillary nodes tend to have a poorer survival prognosis. Age and survival status show a weak positive correlation (0.0680), indicating that older patients tend to have a poorer survival prognosis.

## Multivariate Analysis

### PCA

In the graph of variables, we notice that the "Age" variable is strongly correlated with the first axis, meaning that this variable significantly contributes to the definition of the first principal component of the PCA. The first two axes together represent 70.27% of the total variance in the data, meaning that approximately 70.27% of the observed variation in the data can be explained by these two principal components.

### Classification

To better understand our database, we can use clustering methods. This allows us to group individuals who have certain similarities to better understand and predict future data. One of the first clustering methods is hierarchical agglomerative clustering (HAC).

#### Hierarchical Agglomerative Clustering (HAC)

Due to a relatively low number of individuals (306), we were able to perform HAC, and the interpretation of this was reasonable. We used Euclidean distance as the metric. In the dendrogram, we can observe the grouping of individuals into several classes (4, 8, or 32). There are a multitude of groupings that will not be the subject of our study; we will limit ourselves to studying the grouping into 4 classes for simplicity. We observe 4 distinctly different classes framed in green on the figure.

#### Non-Hierarchical Classification (K-means)

In the case of studying a large amount of data, it is always possible to use non-hierarchical classification to obtain results in a reasonable time by omitting certain information. Here, we still take the trouble to use the clustering technique to compare these results with HAC. First, we will try to determine the optimal number of clusters, assuming that the maximum number of clusters is 8. We observe an ideal number of clusters of 2. However, we choose to keep the number of clusters at k=4 to be able to compare with HAC. Then, we will display the clusters and which points are associated with which clusters. The graph shows that the points are very mixed together, making it quite difficult to distinguish them impartially.

## Conclusion

Following these two analyses of individual classifications of breast cancer patients, we notice that both are quite possible. However, HAC seems to provide more subtleties, which is consistent as it is the classification that takes into account the most factors. Classification with K-means with k=4 groups all patients who died before 5 years without differentiation, whereas with HAC, we differentiate between unexpected deaths (individuals with few nodes who had an operation) and those with many nodes. The latter also highlights that there is a high chance of death if there are many nodes, but there is still a small chance of premature death from cancer.

## Appendix

The appendix includes various figures and tables that support the analysis and findings of the report. These include histograms, density plots, cumulative distribution functions, box plots, correlation matrices, pair plots, PCA graphs, dendrograms, and tables summarizing the similarities and conclusions of the clusters identified in the analysis.
