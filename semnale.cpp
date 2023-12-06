#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <numeric>

using namespace std;

const int mod = 1000000007;

int type1(int x, int y) {
	int i, j;
	// dp este o matrice de dimensiune (x+1) x (y+1) x (2)
	// dp[i][j][0/1] = nr de semnale cu i biti de 0 si j biti de 1,
	// care se termina in 0 sau 1
	vector<vector<vector<int>>> dp(x + 1,
	vector<vector<int>>(y + 1, vector<int>(2)));
	// cazuri de baza
	for (i = 0; i <= x; ++i) {
		dp[i][0][0] = 1;  // prima coloana dp 0
		dp[i][0][1] = 0;  // prima coloana dp 1
        }
	for (j = 1; j <= y; ++j) {
		dp[0][j][0] = 0;  // prima linie dp 0
		dp[0][j][1] = 1;  // prima linie dp 1
        }
	// caz general
        for (i = 1; i <= x; i++) {
            for (j = 1; j <= y; j++) {
		dp[i][j][0] = (dp[i - 1][j][0] + dp[i - 1][j - 1][0]) % mod;
		dp[i][j][1] = dp[i][j - 1][0];
               }
	}
    return (dp[x][y][0] + dp[x][y][1]) % mod;
}

int type2(int x, int y) {
	// dp este o matrice de dimensiune (x+1) x (y+1) x (2)
	// dp[i][j][0/1] = nr de semnale cu i biti de 0 si j biti de 1,
	// care se termina in 0 sau 1
	vector<vector<vector<int>>> dp(x + 1,
	vector<vector<int>>(y + 1, vector<int>(2)));
	int i, j;
	// cazuri de baza
	for (i = 0; i <= x; ++i) {
		dp[i][0][0] = 1;  // prima coloana dp 0
		dp[i][0][1] = 0;  // prima coloana dp 1
        }
	for (j = 1; j <= y; ++j) {
		dp[0][j][0] = 0;  // prima linie dp 0
		dp[0][j][1] = 1;  // prima linie dp 1
        }
	dp[0][1][1] = 1;  // semnal = 0...0001
	dp[0][2][1] = 1;  // semnal = 0...0011
	// caz general
        for (i = 1; i <= x; ++i) {
            for (j = 1; j <= y; ++j) {
		dp[i][j][0] = (dp[i - 1][j][0] + dp[i - 1][j - 1][0]) % mod;
		dp[i][j][1] = (dp[i - 1][j][1] + dp[i][j - 1][1]) % mod;
               }
	}
    return (dp[x][y][0] + dp[x][y][1]) % mod;
}


int main() {
    freopen("semnale.in", "r", stdin);
	freopen("semnale.out", "w", stdout);

	int sig_type, x, y;

	cin >> sig_type >> x >> y;

    switch (sig_type) {
		case 1:
			cout << type1(x, y);;
			break;
		case 2:
			cout << type2(x, y);
			break;
		default:
			cout << "wrong task number" << endl;
	}

    return 0;
}
