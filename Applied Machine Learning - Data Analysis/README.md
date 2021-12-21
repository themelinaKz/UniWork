# Applied Machine Learning - Data Analysis
Three **iPython Jupyter** projects developed in the course of Applied Machine Learning. The projects include **data analysis** on elections, studies and Parliament's proceedings, and machine learning regarding **classification** using different algorithms with **cross-validation** and a **neural network**. 

> ### Contents  
> 1. [FEC elections 2016](#1)
> 2. [Rosetta Code working paper](#2)
> 3. [Greek Parliament's proceedings](#3)
> 4. [Libraries used](#4)

<div id="1"></div>  

## 1. FEC elections 2016 
This notebook contains a study regarding the FEC elections of 2016. In particular, the study focuses on the contributions made by fundraising committees, PACs[<sup id="pacs">1</sup>](#fn1) or individuals to support each of the two presidential candidates in the FEC elections of 2016. In more detail, the following were required:  
1. Top 5 PACs that supported each of the two presidential candidates
2. Top 10 individual donors with the amount they spent for each of the two presidential candidates, directly or indirectly
3. The chronological evolution of the contributions made to and the expenditures made by the campaigns
4. The biggest recipients of campaign expenditures
5. The geographical distribution at the state level of the campaign expenditures, and calculation of the expenditures per voter per state

<div id="2"></div>  

## 2. Rosetta Stone working paper
This notebook contains a study based on the working paper [*A Rosetta Stone of Human Capital*](https://www.cgdev.org/publication/rosetta-stone-human-capital), which introduces a way to faciliate conversion between tests scores in different countries. The tests scores used are TIMSS and PIRLS, evaluating math and reading skills accordingly.  
For each country the factors taken into account that affect the tests scores are the GDP per capital and the years of schooling. The relation between these factors and the logged income is shown with regressions.  
The results of the study are compared to learning outcome estimates from the World Bank using the Spearman test, in order to check their accuracy.  
In the final part, the relationship between the value of a country's exports and the skills possessed by the workforce in this country, such as high school or college degrees, is analyzed.
### Resources used
A bried explanation for each file used in this notebook, categorized by their sources.
- **Complete replication materials** for the original paper ([source](https://www.cgdev.org/publication/rosetta-stone-human-capital))
    - *[country_scores](https://www.cgdev.org/sites/default/files/patel-sandefur-human-capital-final-results.xlsx)* : contains part of the results of the study, grouped by country (only portion of people above the *Low International Benchmark* of 400 on TIMSS and PIRLS scales are included).
	- *WDI_data.dta* : contains income data per country as given by the World Bank
	- *BL2013_MF1599_v2.2.dta* : contains average years of schooling (only values reported for 2010 are used)
	- *HLO Panel Data (mean, thresh) - Jan 2018.dta* : contains learning outcome estimates from the World Bank
    - David Dorn's crosswalk files ([source](https://www.ddorn.net/data.htm))
	    - *cw_hs6_sic87dd.dta* : contains the mapping of the HS 6-digit codes to SIC87[<sup id="sic">2</sup>](#fn2) industry codes, along with the share values
	    - *cw_sic87_ind1990ddx.dta* : contains the mapping of the SIC87 industry codes to the 1990 census industry codes
	    - *cw_ind2000_ind1990ddx.dta* : contains the mapping of the industry codes between 1990 and 2000, with the weights to account for the differences in this decade
- **IPUMS USA** (access graciously granted for the assignment by [IPUMS USA](https://www.ipums.org/projects/ipums-usa/d010.v10.0), thus not available in this repo)
	- *usa_00001.csv.gz* : contains all the needed information to extract college and high school graguated employees per industry
- **BACI Country Trade Data** (Original publication: *BACI: International Trade Database at the Product-Level. The 1994-2007 Version CEPII Working Paper, N°2010-23, Octobre 2010, Guillaume Gaulier, Soledad Zignago*) ([source](http://www.cepii.fr/cepii/en/bdd_modele/presentation.asp?id=37))
	- *BACI_HS17_Y2018_V202001.csv* : contains records showing the exports of different countries in 2018 for different industry sectors. 
	- *country_codes_V202001.csv* : contains the mapping of the ISO 3-digit country codes to the 3-letter country codes

<div id="3"></div>  

## 3. Greek Parliament's speeches
This notebook contains data preprocessing, analysis regarding Greek Parliament's proceedings and classification of speeches with target variable the political party of the speaker.  
Data preprocessing includes removal of punctuations, stopwords, unnecessary speeches and duplicated entries. Lowercasing is also applied.  
Data exploration includes the distribution of the speeches among the political parties and over time, as well as a combination of the above.  
Classification of speeches is approached using three different algorithms, Multinominal Naive Bayes, SGD and Linear SVC. These models are evaluated by accuracy and compared to each other using cross validation. Best hyperparameters for the best algorithm of the above is later discovered using Grid Search, and compared to a Dummy Classifier.  
The final part of this notebook is classification of speeches using a LSTM based neural network with 4 layers and 32 dimensions, trained in 8 epochs.

<div id="4"></div>  

## 4. Libraries used 
The libraries used in all or some of the Jupyter notebooks are the following :
- General
    - **pandas**
    - **numpy**
    - defaultdict from collections
- Data Visualization
    - **matplotlib**
    - **plotnine** 
- Regression
    - **statsmodels.formula.api**
    - **scipy**.stats
- Data Preprocess
    - string
    - **nltk**.tokenize (RegexpTokenizer)
    - **spacy**.lang.el.stop_words (STOP_WORDS)
- Classification 
    - **sklearn**
    - **tensorflow**
    - **keras**

<br>  

---  

<span id="fn1"></span> [<sup>1](#pacs) _Political Action Committees_  
<span id="fn2"></span> [<sup>2](#sic) _Standard Industrial Codes_