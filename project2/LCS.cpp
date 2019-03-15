#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std; 

vector<vector<int> > dp(21);


vector<string> Traceback_LCS(string &X, string &Y, int m, int n){
	vector<string> s;
	if (dp[m][n] == 0){ 
		s.push_back(""); 
		return s;
	}

	if (X[m - 1] == Y[n - 1]){ 
		vector<string> prev = Traceback_LCS(X, Y, m - 1, n - 1);
		for (vector<string>::iterator it=prev.begin(); it!=prev.end(); ++it)
			s.push_back(*it + X[m - 1]); 
	}
	else{
		int i=m-1, j=n-1;
		while (i>0 && X[i-1]!=Y[n-1]) --i;
		if (dp[i][n] == dp[m][n])
			s = Traceback_LCS(X, Y, i, n);
		while (j>0 && X[m-1]!=Y[j-1]) --j;
		if (dp[m][j] == dp[m][n]){
			vector<string> prev = Traceback_LCS(X, Y, m, j);
			s.insert(s.end(), prev.begin(), prev.end()); 
		}
	}

	return s; 
} 


void LCS(string X, string Y, int n){ 
	for (int i = 0; i <= n; i++){
		dp[i].resize(n+1);
		for (int j = 0; j <= n; j++){ 
			if (i == 0 || j == 0) 
				dp[i][j] = 0; 
			else if (X[i - 1] == Y[j - 1]) 
				dp[i][j] = dp[i - 1][j - 1] + 1; 
			else
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]); 
		} 
	}
} 


int main(int argc, char *argv[]){
	int n;
	int x, y;
	string bin_x = "";
	string bin_y = "";

	// read the input
	if (argc!=4){
		cout << "please make sure you input n, x, and y!" << endl;
		exit(1);
	}
	n = atoi(argv[1]);
	x = atoi(argv[2]);
	y = atoi(argv[3]);

	
	// cout << "Enter the interger n: ";
	// cin >> n;
	if (n < 3 || n > 20){
		cout << "n is not in range [3:20]!" << endl;
		exit(1);
	}
	
	// cout << "Enter the interger x: ";
	// cin >> x;
	if (x<0 || x>pow(2,n)-1){
		cout << "x is not in range [0:2^n-1]!" << endl;
		exit(1);
	}

	// cout << "Enter the interger y: ";
	// cin >> y;
	if (y<0 || y>pow(2,n)-1){
		cout << "y is not in range [0:2^n-1]!" << endl;
		exit(1);
	}

	cout << "n = " << n << "; x = " << x << "; y = " << y << endl;

	// compute the binstring of x and y
	for (int i=0;i<n;i++){
		if((x&1) == 1)
			bin_x = "1" + bin_x;
		else
			bin_x = "0" + bin_x;
		if((y&1) == 1)
			bin_y = "1" + bin_y;
		else
			bin_y = "0" + bin_y;
		x = x>>1;
		y = y>>1;
	}

	dp.resize(n+1);
	// compute the dp
	LCS(bin_x, bin_y, n);

	// traceback the list of those LCS's
	vector<string> s = Traceback_LCS(bin_x, bin_y, n, n);

	// dispaly the results
	cout << "binstring(n,x) = " << bin_x << endl;
	cout << "binstring(n,y) = " << bin_y << endl;
	cout << "the determined number of distinct LCS's = " << s.size() << endl;
	cout << "the list of those LCS's:" << endl;
	for (vector<string>::iterator it=s.begin(); it!=s.end(); ++it)
		cout << *it << endl;

	return 0; 
}