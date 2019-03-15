# Project 2

### 1. Description

The main idea of the algorithm is dynamic algorithm.

* The element dp\[i][j] int the array dp denotes the maximum length of commom subsequence between $x_0x_1x_2……x_i$ and $y_0y_1y_2……y_i$.
* So we can have the following formula:
  * when $x_i = y_j$, if i = 0 or j = 0, dp\[i][j] = 1, else dp\[i][j] = dp\[i-1][j-1]+1
  * when $x_i \neq y_j$, if i = 0 or j = 0, dp\[i][j] = 0, else dp\[i][j] = Max(dp\[i-1][j], dp\[i][j-1])
* After iterating from $x = 0, y = 0$ to $x = n-1, y = n-1$, it gets the result in dp\[n-1][n-1].
* Finally using backtrack to get the set of distinct LCS.



### 2. Asymptotic worst-case time complexity

The worst-case time complexity is $\theta(n^2)$.

For the bottom-up dp process, it will iterate $n^2$ times, so the time complexity is $T_1(n) = \theta(n^2)$.

For the backtrack process, we have formula $T_2(n) = T_2(n-1)+k*n​$, so the time complexity is also $\theta(n^2)​$.

Therefore, the total time complexity is $T_1(n)+T_2(n) = \theta(n^2)$. 



### 3. How to compile and use

Using the following command to compile:

```shell
g++ Lcs.cpp -o Lcs -O2
```

Using the following command to use, among which the first param is name of Lcs program, the second is n, the third is x, and the last is y:

```shell
./Lcs 14 12642 5735
```

Using the following command to measure the time:

```shell
time ./Lcs 14 12642 5735
```



### 4. Sample input and output

Input 1: n = 3, x = 3, y = 6

Output 1:

![image-20181201155447299](/Users/txwyy123/Library/Application Support/typora-user-images/image-20181201155447299.png)



Input 2: n = 14, x = 12642, y = 5735

Output 2:

![image-20181201155957471](/Users/txwyy123/Library/Application Support/typora-user-images/image-20181201155957471.png)