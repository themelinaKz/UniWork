# MIPS - Sparse Array Converter 

## About
A **sparse array** is an array of data in which the majority of the elements have a value of zero. In order to **reduce the amount of memory** this array consumes, any sparse array can be converted to an smaller in size array that will store only the **non-zero** values and their indexes on the original sparse array.   

> For instance, the following sparse array  
| 0 | 0 | 0 | 0 | 0 | 8 | 0 | 0 | 0 | -3 |  
can be converted to   
| 5 | 8 | 9 | -3 |
##### According to the example above, element 8 is in index 5 and element -3 is in index 9.
---

This program, written in **MIPS assemply**, converts two sparse arrays to a smaller in size arrays using the method explained above, and then if the user wants to, it adds them to one. As assembly isn't one of the most user-friendly programming languages, the code is well documented.

## Algorithmic logic
The following code, implemented in *Java*, shows the algorithmic logic behind the conversion described above.  
``` java
int createSparse (int [ ] pin, int [ ] sparse) { 
int i, k=0; 
for (i=0; i<pin.length; i++) 
   if (pin [i] != 0){ 
       sparse [k++] = i; 
       sparse [k++] = pin [i]; 
    } return k;
}
```

## User's Part
The user has the following options :  
1 Read Array A  
2 Read Array B   
3 Create Sparse Array A   
4 Create Sparse Array B   
5 Create Sparse Array C = A + B   
6 Display Sparse Array A   
7 Display Sparse Array B   
8 Display Sparse Array C  
0 Exit

