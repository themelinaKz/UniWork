#include <stdio.h> 

/* number of phoners */
const unsigned int Ntel = 8;

/* number of cashiers */
const unsigned int Ncash = 4;

/* number of seats per row */
const unsigned int Nseat = 100;

/* number of zone A rows */
const unsigned int NzoneA = 5;
/* number of zone B rows */
const unsigned int NzoneB = 10;
/* number of zone C rows */
const unsigned int NzoneC = 10;

/* probability to choose zone A*/
const unsigned int PzoneA = 20;
/* probability to choose zone B*/
const unsigned int PzoneB = 40;
/* probability to choose zone C*/
const unsigned int PzoneC = 40;

/* zone A ticket cost */
const unsigned int CzoneA = 30;
/* zone B ticket cost */
const unsigned int CzoneB = 25;
/* zone C ticket cost */
const unsigned int CzoneC = 20;

/* minimum number of tickets per customer */
const unsigned int Nseatlow = 1;
/*  maximum number of tickets per customer */
const unsigned int Nseathigh = 5;

/* minimum needed time for the phoner to check seats availability */
const unsigned int Tseatlow = 5;
/* maximum needed time for the phoner to check seats availability */
const unsigned int Tseathigh = 10;

/* minimum time for the cashier to make the transaction */
const unsigned int Tcashlow = 2;
/* maximum time for the cashier to make the transaction */
const unsigned int Tcashhigh = 4;

/* probability of payment success */
const double Pcardsuccess = 90;