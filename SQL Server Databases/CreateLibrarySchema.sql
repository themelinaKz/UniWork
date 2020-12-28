CREATE TABLE departments (
	depcode int PRIMARY KEY, 
	depname varchar(30) 
);

CREATE TABLE publishers ( 
	pubid int PRIMARY KEY, 
	pubname VARCHAR(100) 
);

CREATE TABLE authors (
	aid int PRIMARY KEY, 
	author varchar(50) 
);

CREATE TABLE sterms (
	tid int PRIMARY KEY, 
	term varchar(60) 
);

CREATE TABLE bibrecs (
	bibno int PRIMARY KEY, 
	title varchar(200), 
	material varchar(30), 
	lang char(3), 
	place varchar(40), 
	series varchar(200), 
	pubid int FOREIGN KEY references publishers(pubid), 
);

CREATE TABLE bibauthors (
	bibno int FOREIGN KEY references bibrecs(bibno), 
	aid int FOREIGN KEY references authors(aid), 
	PRIMARY KEY(bibno, aid), 
);

CREATE TABLE bibterms (
	bibno int FOREIGN KEY references bibrecs(bibno), 
	tid int FOREIGN KEY references sterms(tid), 
	PRIMARY KEY (bibno, tid) 
);

CREATE TABLE copies ( 
	copyno char(8) PRIMARY KEY, 
	bibno int FOREIGN KEY references bibrecs(bibno), 
	copyloc char(3) 
);

CREATE TABLE borrowers (
	bid int PRIMARY KEY, 
	depcode int, sex char(1), 
	bname varchar(60), 
);

CREATE TABLE loanstats (
	lid int PRIMARY KEY, 
	copyno char(8) FOREIGN KEY references copies(copyno), 
	bid int FOREIGN KEY references borrowers(bid), 
	loandate date 
);