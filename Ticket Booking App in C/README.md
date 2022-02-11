# Tickets Booking App in C
A group project developed in the course of Operating Systems. This project simulates the ticket booking process of a theater with phone operators and cashiers using **pthreads**  in C, implemented on a VM running Ubuntu Linux. 

## Ticket Booking Process
The theater is represented by three variables, one for each zone (check *theater's plan* below). For each customer a new thread is created. 

Customer initially waits to be connected to a phone operator, at least in case there is none available. When the connection is established, the phone operator checks whether there are enough consecutive seats available, while customer waits until the phone operator finishes hi/her task. In case there are enough seats available, customer waits to be connected to a cashier to proceed to payment. 

Each time a phone operator or a cashier gets available, a condition variable signals all waiting threads so as for one to start running again. All variables and arrays used are isolated using mutexes, so as to be accessed only by one thread at a time. 

### Transaction Failure
There are three main reasons why a transaction may fail.
1. The theater is full.
2. There aren't enough consecutive seats available.
3. The card used for payment was not accepted.

## Theater's Plan
The theater consists of three zones, each having different number of rows and different seat cost. Each row has a standard number of seats, equal to N<sub>seats</sub>.

![Theater Plan](https://github.com/themelinaKz/UniWork/blob/master/Tickets%20Booking%20App%20in%20C/theater_plan.png)

## Inputs
- **N<sub>cust</sub>**: the number of customers
- **seedp**: the seed used for pseudo-random generator

**test-res2.sh** contains the executable command with default required input values. 

## Outputs
- **theater's final plan** with all reserved seats and customers ids (*Seat _ / Client _ / Zone _*)
- **total earnings**
- **average waiting time** of customers to be connected to a phone operator
- **average service time** , from the time a customer waits to be connected to a phone operator to the time the transaction succeeds or fails
- number of **succeeded transactions**
- number of **card failure transactions**
- number of **transactions failed due to seat unavailabity**

## Group
I did this project with [Lydia Athanasiou](https://github.com/lydia-ath) and [Stella Douka](https://github.com/stelladk)

*Spring 2019*