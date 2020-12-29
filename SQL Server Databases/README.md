# SQL Server Databases

This project consists of **two main parts**, and was conducted using **DBMS Microsoft SQL Server**. The general purpose of the **1<sup>st</sup> part** is to learn the basics of DBMS Microsoft SQL Server and to examine the practical use of indexes inside a database. The general purpose of the **2<sup>nd</sup> part** is to build a **Star Schema Data Warehouse**, which will ease the statistical analysis of loans per location, material, department, gender and time.  

## Data
The database is about a university library, having information about the documents, the borrowers and the loans of the documents.
As I'm unaware of what rights I have to the data given by my professor, I haven't uploaded the data nor have I added any source connecting the data to this repo.  
- **data_description.sql** contains the description of each of the tables (*stored in txt form*) used as data in this project

## Part 1
In the **1<sup>st</sup> Part**, the database *LIBRARY* is created.  
- **CreateLibrarySchema.sql** contains all scripts to create the database
- **LoadLibraryData.sql** contains all scripts to load the database
- **queries.sql** contains all queries and index creations requested to be done (specifically asked to not creat or use any views or temporary tables). The purpose of most of these queries, apart from showing the requested entries, is to improve their performance using indexes. So, for this purpose **statistics** are used to have evidence of these improvements (check *Additional_files*).
- **free_text_search.sql** contains creation of tables and indexes to support **free text search** in **free text fields**, such as *title*. An example of the form of the queries supported is the following:  
"*Show id and title of bibliographical entries whose* ***title*** *contains word 'οικονομία',* ***series*** *contains word 'ελληνική' and* ***author*** *contains word 'Οικονόμου'*"  

## Part 2  
In the **2<sup>nd</sup> Part**, the database *LIBDW* (Library Data Warehouse) is created using the data of *LIBRARY* database.  
- **Create_DataWarehouse.sql** contains all scripts to create and load the Star Schema Data Warehouse.  
![Warehouse Star Schema](/Additional_files/star_schema.png)
- **warehouse_scripts.sql** contains queries that help in statistical analysis of loans per different factors, such as time or gender.
- **data_cube.sql** contains scripts that create the same **data cube**, but in different ways.

## Additional_files  
Additional_files folder contains execution plans, messages, examples of the requests of the assignment and the **Star Schema** of the Warehouse.