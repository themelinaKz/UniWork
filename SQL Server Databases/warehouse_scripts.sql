-- 1. Request to show a catalog with the number of loans per year and department
SELECT t_year, depcode, COUNT(lid) AS NumberOfLoans
FROM time_info AS t, borrowers AS b, loans AS l
WHERE t.time_key = l.time_key AND b.bid = l.bid
GROUP BY t_year, depcode

-- 2. Request to show a catalog with the number of loans per location and material
SELECT copyloc, material, COUNT(lid) AS NumberOfLoans
FROM copies as c, bibrecs as b, loans as l
WHERE c.copyno = l.copyno AND b.bibno = l.bibno
GROUP BY copyloc, material

-- 3. Request to show a catalog with the number of loans per month and gender in 2000
SELECT t_month, sex, COUNT(lid) AS NumberOfLoans
FROM time_info as t, borrowers as b, loans as l
WHERE t.time_key = l.time_key AND b.bid = l.bid AND t_year = 2000
GROUP BY t_month, sex

-- 4. Request to show a catalog with the months of each year when the number of loans got over 800
SELECT DISTINCT t_year, t_month, COUNT(lid) AS NumberOfLoans
FROM time_info as t, loans as l
WHERE t.time_key = l.time_key
GROUP BY t_year, t_month
HAVING COUNT(lid) > 800
ORDER BY t_year, t_month

/* 5. Request to show a report with the following data: 
	  - the total number of loans
	  - the number of loans per year
	  - the number of loans per year and department 
	  - the number of loans per year, department and gender */
SELECT t_year, depcode, sex, COUNT(lid) AS NumberOfLoans
FROM time_info as t, borrowers as b, loans as l
WHERE t.time_key = l.time_key AND b.bid = l.bid
GROUP BY ROLLUP (t_year, depcode, sex)

-- 6. Request to show the departments whose total number of female students is higher than the total number of male students
SELECT depcode, COUNT(CASE WHEN sex='F' THEN 1 END) as FemaleStCount, 
			    COUNT(CASE WHEN sex='M' THEN 1 END) as MaleStCount, 
			    COUNT(lid) AS TotalNumberOfLoans
FROM borrowers as b, loans as l
WHERE b.bid = l.bid
GROUP BY depcode
HAVING COUNT(CASE WHEN sex = 'F' THEN 1 END) > COUNT(CASE WHEN sex = 'M' THEN 1 END)
