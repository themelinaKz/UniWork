-- Data Cube
-- 1. Request to create a data cube whose each cell has the number of loans for a specific combination of the values of year,location and gender fields.
SELECT t_year, copyloc, sex, COUNT(lid) AS NumberOfLoans
FROM time_info as t, copies as c, borrowers as b, loans as l
WHERE t.time_key = l.time_key AND c.copyno = l.copyno AND b.bid = l.bid
GROUP BY CUBE(t_year, copyloc, sex)


-- 2. Request to create the same data cube as the above without using the CUBE operator or creating additional tables.
CHECKPOINT
DBCC DROPCLEANBUFFERS
SET STATISTICS IO ON 

SELECT t_year, copyloc, sex, COUNT(lid) AS NumberOfLoans
FROM time_info as t, copies as c, borrowers as b, loans as l
WHERE t.time_key = l.time_key AND c.copyno = l.copyno AND b.bid = l.bid
GROUP BY t_year, copyloc, sex
UNION 
SELECT t_year, copyloc, NULL AS sex, COUNT(lid) AS NumberOfLoans
FROM time_info as t, copies as c, loans as l
WHERE t.time_key = l.time_key AND c.copyno = l.copyno
GROUP BY t_year, copyloc
UNION 
SELECT t_year, NULL as copyloc, sex, COUNT(lid) AS NumberOfLoans
FROM time_info as t, borrowers as b, loans as l
WHERE t.time_key = l.time_key AND b.bid = l.bid
GROUP BY t_year, sex
UNION 
SELECT t_year, NULL as copyloc, NULL as sex, COUNT(lid) AS NumberOfLoans
FROM time_info as t, loans as l
WHERE t.time_key = l.time_key
GROUP BY t_year
UNION
SELECT NULL as t_year, copyloc, sex, COUNT(lid) AS NumberOfLoans
FROM copies as c, borrowers as b, loans as l
WHERE c.copyno = l.copyno AND b.bid = l.bid
GROUP BY copyloc, sex
UNION 
SELECT NULL as t_year, copyloc, NULL as sex, COUNT(lid) AS NumberOfLoans
FROM copies as c, loans as l
WHERE c.copyno = l.copyno
GROUP BY copyloc
UNION
SELECT NULL as t_year, NULL as copyloc, sex, COUNT(lid) AS NumberOfLoans
FROM borrowers as b, loans as l
WHERE b.bid = l.bid
GROUP BY sex
UNION
SELECT NULL as t_year, NULL as copyloc, NULL as sex, COUNT(lid) AS NumberOfLoans
FROM loans as l

SET STATISTICS IO OFF


-- 3. Request to create the same data cube without using CUBE operator, but with the ability to create and use additional tables.
-- 1st way using ROLLUP
CHECKPOINT
DBCC DROPCLEANBUFFERS
SET STATISTICS IO ON
SELECT t_year, copyloc, sex, COUNT(lid) AS NumberOfLoans
FROM time_info as t, copies as c, borrowers as b, loans as l
WHERE t.time_key = l.time_key AND c.copyno = l.copyno AND b.bid = l.bid
GROUP BY ROLLUP(t_year, copyloc, sex)
UNION 
SELECT t_year, copyloc, sex, COUNT(lid) AS NumberOfLoans
FROM time_info as t, copies as c, borrowers as b, loans as l
WHERE t.time_key = l.time_key AND c.copyno = l.copyno AND b.bid = l.bid
GROUP BY ROLLUP(copyloc, sex, t_year)
UNION 
SELECT t_year, copyloc, sex, COUNT(lid) AS NumberOfLoans
FROM time_info as t, copies as c, borrowers as b, loans as l
WHERE t.time_key = l.time_key AND c.copyno = l.copyno AND b.bid = l.bid
GROUP BY ROLLUP(sex, t_year, copyloc)
SET STATISTICS IO OFF

-- 2nd way using additional tables
CREATE TABLE Temp1 (
	lid int, 
	t_year int,
	copyloc char(3),
	sex char(1)
);
CREATE TABLE Temp2 (
	lid int, 
	copyloc char(3),
	sex char(1),
	t_year int
);
CREATE TABLE Temp3 (
	lid int, 
	sex char(1),
	t_year int,
	copyloc char(3)
);

INSERT INTO Temp1
	SELECT lid, t_year, copyloc, sex
	FROM time_info as t, copies as c, borrowers as b, loans as l
	WHERE t.time_key = l.time_key AND c.copyno = l.copyno AND b.bid = l.bid
	GROUP BY lid, ROLLUP(t_year, copyloc, sex)
INSERT INTO Temp2
	SELECT lid, copyloc, sex, t_year
	FROM time_info as t, copies as c, borrowers as b, loans as l
	WHERE t.time_key = l.time_key AND c.copyno = l.copyno AND b.bid = l.bid
	GROUP BY lid, ROLLUP(copyloc, sex, t_year)
	order by lid
INSERT INTO Temp3
	SELECT lid, sex, t_year, copyloc
	FROM time_info as t, copies as c, borrowers as b, loans as l
	WHERE t.time_key = l.time_key AND c.copyno = l.copyno AND b.bid = l.bid
	GROUP BY lid, ROLLUP(sex, t_year, copyloc)
	order by lid

CREATE INDEX temp1_lid ON Temp1(lid)
CREATE INDEX temp2_lid ON Temp2(lid)
CREATE INDEX temp3_lid ON Temp3(lid)

CHECKPOINT
DBCC DROPCLEANBUFFERS
SET STATISTICS IO ON 

SELECT t1.t_year, t2.copyloc, t3.sex, COUNT(t1.lid) as NumberOfLoans
FROM Temp1 as t1
FULL OUTER JOIN Temp2 as t2
ON t1.lid = t2.lid
FULL OUTER JOIN Temp3 as t3
ON t1.lid = t3.lid
GROUP BY t1.t_year, t2.copyloc, t3.sex

SET STATISTICS IO OFF