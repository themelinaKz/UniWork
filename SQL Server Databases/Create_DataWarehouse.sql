-- Dimension Tables 
CREATE TABLE time_info (
	time_key datetime primary key,
	t_year int,
	t_month int,
	t_quanter int,
	t_week int,
	t_dayofyear int,
	t_dayofmonth int,
	t_dayofweek int,
);

CREATE TABLE borrowers (
	bid int PRIMARY KEY,
	depcode int,
	sex char(1)
);

CREATE TABLE bibrecs (
	bibno int PRIMARY KEY,
	material varchar(30)
);

CREATE TABLE copies (
	copyno char(8) PRIMARY KEY,
	copyloc char(3)
);

-- Fact Table
CREATE TABLE loans (
	lid int,
	time_key datetime,
	copyno char(8),
	bid int,
	bibno int
	PRIMARY KEY(lid, time_key, copyno, bid, bibno),
	FOREIGN KEY (time_key) REFERENCES time_info(time_key),
	FOREIGN KEY (copyno) REFERENCES copies(copyno),
	FOREIGN KEY (bid) REFERENCES borrowers(bid),
	FOREIGN KEY (bibno) REFERENCES bibrecs(bibno)
);

-- fill time_info
SET DATEFIRST 1; --set Monday as the first day of the week
INSERT INTO time_info
	SELECT DISTINCT loandate, DATEPART(YEAR, loandate), DATEPART(MONTH, loandate),
							  DATEPART(QUARTER, loandate), DATEPART(WEEK, loandate),
							  DATEPART(DAYOFYEAR, loandate), DATEPART(DD, loandate),
							  DATEPART(DW, loandate)
	FROM LIBRARY.dbo.loanstats

-- fill borrowers
INSERT INTO borrowers
	SELECT DISTINCT bid, depcode, sex
	FROM LIBRARY.dbo.borrowers

-- fill bibrecs
INSERT INTO bibrecs
	SELECT DISTINCT bibno, material
	FROM LIBRARY.dbo.bibrecs
	
-- fill copies
INSERT INTO copies
	SELECT DISTINCT copyno, copyloc
	FROM LIBRARY.dbo.copies

-- fill loans
INSERT INTO loans
	SELECT DISTINCT lid, loandate, l.copyno, bid, bibno
	FROM LIBRARY.dbo.loanstats as l, LIBRARY.dbo.copies as c
	WHERE l.copyno = c.copyno