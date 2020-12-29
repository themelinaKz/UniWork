-- 1. Request to create an index that makes the query below run faster
CREATE INDEX index_title ON bibrecs(title)

CHECKPOINT
DBCC DROPCLEANBUFFERS
SET STATISTICS IO ON

SELECT title
FROM bibrecs
WHERE title LIKE 'Οικ%'
ORDER BY title

SET STATISTICS IO OFF

-- each index is dropped after getting the execution plan, to not interfere in the results of the other exercises
DROP INDEX [index_title] ON [dbo].[bibrecs] 



-- 2. Request to show entries' title whose exhibit's title contains word 'πληροφορική' using index created in Request 1 (in this case it doesn't help)
CREATE INDEX index_title ON bibrecs(title)

CHECKPOINT
DBCC DROPCLEANBUFFERS
SET STATISTICS IO ON

SELECT title
FROM bibrecs
WHERE title LIKE '%πληροφορική%'

SET STATISTICS IO OFF

DROP INDEX [index_title] ON [dbo].[bibrecs] 



-- 3. Request to show entries' title and material whose exhibit's title is 'Economics' using index created in Request 1 (in this case it helps)
CREATE INDEX index_title ON bibrecs(title)

CHECKPOINT
DBCC DROPCLEANBUFFERS
SET STATISTICS IO ON

SELECT title, material
FROM bibrecs
WHERE title = 'Economics'

SET STATISTICS IO OFF

DROP INDEX [index_title] ON [dbo].[bibrecs] 



-- 4. Request to show entries' title and material whose exhibit's title starts with 'Economics' using index created in Request 1 (in this case it doesn't help)
CREATE INDEX index_title ON bibrecs(title)

CHECKPOINT
DBCC DROPCLEANBUFFERS
SET STATISTICS IO ON

SELECT title, material
FROM bibrecs
WHERE title LIKE 'Economics%'

SET STATISTICS IO OFF

DROP INDEX [index_title] ON [dbo].[bibrecs]



-- 5. Request to show entries' title and language whose publisher is 'Κλειδάριθμος' using index(es) that accelerates query's performance
CREATE INDEX index_pubname ON publishers(pubname)
CREATE INDEX index_pubid ON bibrecs(pubid) INCLUDE(title, lang)

CHECKPOINT 
DBCC DROPCLEANBUFFERS
SET STATISTICS IO ON 

SELECT title, lang
FROM publishers, bibrecs
WHERE publishers.pubid = bibrecs.pubid AND pubname = 'Κλειδάριθμος'

SET STATISTICS IO OFF

DROP INDEX [index_pubname] ON [dbo].[publishers]
DROP INDEX [index_pubid] ON [dbo].[bibrecs]



-- 6. Request to show for each department the total number of loans in 2000 using index(es) that accelerates query's performance
CREATE INDEX index_loandate_bid ON loanstats(loandate, bid)

CHECKPOINT
DBCC DROPCLEANBUFFERS
SET STATISTICS IO ON

SELECT depname, COUNT(lid) as total_loans
FROM departments, borrowers, loanstats
WHERE loanstats.bid = borrowers.bid AND departments.depcode = borrowers.depcode AND loandate>='2000-01-01' AND loandate<='2000-12-31'
GROUP BY depname

SET STATISTICS IO OFF

DROP INDEX [index_loandate_bid] ON [dbo].[loanstats] 



-- 7. Request to show entries' title, language and author's name whore subject term is 'Databases' using index(es) that accelerates query's performance
CREATE INDEX index_tid ON bibterms(tid)
CREATE INDEX index_term ON sterms(term)

CHECKPOINT
DBCC DROPCLEANBUFFERS
SET STATISTICS IO ON

SELECT title, lang, author
FROM bibrecs, bibauthors, authors, sterms, bibterms
WHERE bibrecs.bibno = bibauthors.bibno AND 
	  bibauthors.aid = authors.aid AND 
	  bibrecs.bibno = bibterms.bibno AND 
	  bibterms.tid = sterms.tid AND 
	  term LIKE 'Databases'
	  
SET STATISTICS IO OFF

DROP INDEX [index_tid] ON [dbo].[bibterms]
DROP INDEX [index_term] ON [dbo].[sterms]



-- 8. Request to show (with 2-4 different ways) entries' id and book's title for which library has at least one copy at location 'OPA' and at least one copy at location 'ANA'. Fourth query has the best performance, so for this query it's requested to accelerate its performance using index(es).
/*1st way with INTERSECT*/
CHECKPOINT
DBCC DROPCLEANBUFFERS
SET STATISTICS IO ON
SELECT bibrecs.bibno, title
FROM bibrecs, copies
WHERE bibrecs.bibno = copies.bibno AND copyloc LIKE 'ANA'
INTERSECT
SELECT bibrecs.bibno, title
FROM bibrecs, copies
WHERE bibrecs.bibno = copies.bibno AND copyloc LIKE 'OPA'
SET STATISTICS IO OFF

/*2nd way with inner SELECT*/
CHECKPOINT
DBCC DROPCLEANBUFFERS
SET STATISTICS IO ON
SELECT DISTINCT bibrecs.bibno, title
FROM bibrecs, copies
WHERE bibrecs.bibno = copies.bibno AND 
	  copyloc LIKE 'OPA' AND 
	  bibrecs.bibno IN (SELECT copies.bibno 
						FROM bibrecs, copies 
						WHERE bibrecs.bibno = copies.bibno AND
						      copyloc LIKE 'ANA')
SET STATISTICS IO OFF

/*3rd way with ANY*/
CHECKPOINT
DBCC DROPCLEANBUFFERS
SET STATISTICS IO ON
SELECT DISTINCT bibrecs.bibno, title
FROM bibrecs, copies
WHERE bibrecs.bibno = copies.bibno AND copyloc LIKE 'OPA' AND bibrecs.bibno = ANY(SELECT copies.bibno 
																				  FROM bibrecs, copies 
																				  WHERE bibrecs.bibno = copies.bibno AND copyloc LIKE 'ANA')
SET STATISTICS IO OFF*/

/*4th way with EXISTS*/
CREATE INDEX index_title ON bibrecs(title)
CREATE INDEX index_copyloc ON copies(copyloc) INCLUDE(bibno)

CHECKPOINT 
SET STATISTICS IO ON
SELECT DISTINCT bibrecs.bibno, title
FROM bibrecs, copies
WHERE bibrecs.bibno = copies.bibno AND 
	  copyloc LIKE 'OPA' AND 
	  EXISTS (SELECT DISTINCT copies.bibno 
						FROM copies AS c
						WHERE bibrecs.bibno = c.bibno AND
						      copyloc LIKE 'ANA')
SET STATISTICS IO OFF

DROP INDEX [index_copyloc] ON [dbo].[copies]
DROP INDEX [index_title] ON [dbo].[bibrecs]