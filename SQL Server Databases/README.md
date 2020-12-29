# SQL Server Databases

This project consists of **two main parts**, and was conducted using **DBMS Microsoft SQL Server**.  

## Data
As I'm unaware of what rights I have to the data given by my professor, I haven't uploaded the data nor have I added any source connecting the data to this repo.  
- **data_description.sql** contains the description of each of the tables (*stored in txt form*) used as data in this project

## Additional_files  
Additional_files folder contains execution plans, messages and examples of the requests of the assignment in png form.

## Part 1
In the **1<sup>st</sup> Part**, the database *LIBRARY* is created. 
- **CreateLibrarySchema.sql** contains all scripts to create the database
- **LoadLibraryData.sql** contains all scripts to load the database
- **queries.sql** contains all queries and index creations requested to be done (specifically asked to not be created or used any views or temporary tables). The purpose of most of these queries, apart from showing the requested entries, is to improve their performance using indexes. So, for this purpose **statistics** are used to have evidence of these improvements (check *Additional_files*).
- **free_text_search.sql** contains creation of tables and indexes to support **free text search** in **free text fields**, such as *title*. The form of the queries supported is the following:  
"*Show id and title of bibliographical entries whose* ***title*** *contains word 'οικονομία',* ***series*** *contains word 'ελληνική' and* ***author*** *contains word 'Οικονόμου'*"