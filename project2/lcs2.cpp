#include <iostream>
#include <string> 
#include <set>
#include <math.h>
using namespace std; 

#define N 21
int dp[N][N]; 
set<string> s[N][N];		

set<string> Traceback_LCS(string X, string Y, int m, int n){
	set<string> s; 

	if (m == 0 || n == 0){ 
		s.insert(""); 
		return s; 
	} 

	if (X[m - 1] == Y[n - 1]){ 
		set<string> prev = Traceback_LCS(X, Y, m - 1, n - 1);
		for (set<string>::iterator it=prev.begin(); it!=prev.end(); ++it)
			s.insert(*it + X[m - 1]); 
	}
	else{
		if (dp[m - 1][n] >= dp[m][n - 1]) 
			s = Traceback_LCS(X, Y, m - 1, n); 
		if (dp[m][n - 1] >= dp[m - 1][n]){
			set<string> prev = Traceback_LCS(X, Y, m, n - 1);
			s.insert(prev.begin(), prev.end()); 
		}
	}

	return s; 
} 


void LCS(string X, string Y, int n){ 
	for (int i = 0; i <= n; i++){ 
		for (int j = 0; j <= n; j++){ 	
			if (i == 0 || j == 0){ 
				dp[i][j] = 0;
				set<string> ss;
				ss.insert("");
				s[i][j] = ss;	
			}
			else if (X[i - 1] == Y[j - 1]){
				dp[i][j] = dp[i - 1][j - 1] + 1;
				set<string> ss;	
				for(set<string>::iterator it=s[i-1][j-1].begin(); it!=s[i-1][j-1].end(); ++it){
					ss.insert(*it+X[i-1]);
				}
				s[i][j] = ss;	
			}
			else{
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
				if(dp[i-1][j] > dp[i][j-1]){
					s[i][j] = s[i-1][j];
				}else if(dp[i-1][j] < dp[i][j-1]){
					s[i][j] = s[i][j-1];
				}else{
					set<string> ss;	
					set<string> s1 = s[i-1][j];
					set<string> s2 = s[i][j-1];
					set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), inserter(ss, ss.begin()));
					s[i][j] = ss;	
				}
			}
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
	n = stoi(argv[1]);
	x = stoi(argv[2]);
	y = stoi(argv[3]);

	
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

	// compute the dp
	LCS(bin_x, bin_y, n);

	// traceback the list of those LCS's
	// set<string> s = Traceback_LCS(bin_x, bin_y, n, n);

	// dispaly the results
	cout << "binstring(n,x) = " << bin_x << endl;
	cout << "binstring(n,y) = " << bin_y << endl;
	cout << "the determined number of distinct LCS's = " << s[n][n].size() << endl;
	cout << "the list of those LCS's:" << endl;
	for (set<string>::iterator it=s[n][n].begin(); it!=s[n][n].end(); ++it)
		cout << *it << endl;

	return 0; 
}