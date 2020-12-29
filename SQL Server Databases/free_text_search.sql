-- Tables creation
CREATE TABLE titwords (
	tlid int PRIMARY KEY,
	title varchar(30)
);

CREATE TABLE bibtitlewords (
	tlid int PRIMARY KEY,
	bibno int FOREIGN KEY REFERENCES bibrecs(bibno)
);

CREATE TABLE serwords (
	sid int PRIMARY KEY,
	series varchar(30)
);

CREATE TABLE bibserieswords (
	sid int PRIMARY KEY,
	bibno int FOREIGN KEY REFERENCES bibrecs(bibno)
);

CREATE TABLE authwords (
	authid int PRIMARY KEY,
	author varchar(30)
);

CREATE TABLE bibauthorwords	(
	authid int PRIMARY KEY,
	bibno int FOREIGN KEY REFERENCES bibrecs(bibno)
);

-- Index creation
CREATE INDEX index_title ON titwords(title)
CREATE INDEX index_series ON serwords(series)
CREATE INDEX index_author ON authwords(author)