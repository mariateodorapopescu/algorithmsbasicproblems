#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <numeric>
using namespace std;
int task1(int n, int m, int x, vector <int>& p, vector <vector <int> >& g) {
	int i, j, sol_aux;
	vector<int> values;
	values.assign(m, 0);
	for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            values[i] = values[i] + g[j][i];
        }
    }

    vector<vector<int>> dp(m + 1);
    for (i = 0; i <= m; ++i) {
        dp[i].resize(n*x + 1);
    }
	// o versiune modificata a recurentei de la
	// cursul de la seria CC, "curs 3 PD", slide 13
	for (i = 0; i <= m; i++) {
	for (j = 0; j <= n * x; j++) {
	// caz de baza
	if (i == 0) {
		dp[0][j] = 0;
	} else if (j == 0) {
		dp[i][0] = 0;
	// caz general
	} else if (j - p[i - 1] >= 0) {
	// daca pot lua un platou o data, trebuie sa am macar j - p[i - 1] bani
		sol_aux = values[i - 1] + dp[i - 1][j - p[i - 1]];
            dp[i][j] = max(sol_aux, dp[i - 1][j]);
        } else {
	// altfel e solutia de la pasul anterior
            dp[i][j] = dp[i - 1][j];
        }
    }
}
    return dp[m][n*x];
}

int task2(int n, int m, int x, vector <int> &p, vector <vector <int> > &g) {
	// task1 modificat, asa incat sa pot lua si doua platouri
	// o versiune modificata a recurentei de la
	// cursul de la seria CC, "curs 3 PD", slide 13
    int i, j, k, sol_aux;
    vector<int> values;
    values.assign(m, 0);
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            values[i] = values[i] + g[j][i];
        }
    }
    vector<vector<int>> dp(m + 1);
    for (i = 0; i <= m; ++i) {
        dp[i].resize(2 * n * x + 1);
    }
    // caz general
    for (i = 0; i <= m; i++) {
        for (j = 0; j <= 2 * n * x; j++) {
            if (i == 0) {
		dp[0][j] = 0;
	} else if (j == 0) {
		dp[i][0] = 0;
	// caz general
	} else {
                for (k = 1; k <= 2; k++) {
		// acum iau pe rand k platouri, k = 1, 2 si vad ce se intampla
		// normal ca trebuie sa verific daca mai am bani
		// deci ca sa cumpar 2 platouri trebuie sa am macar j-k*p[i-1]
			if (j - k * p[i - 1] >= 0) {
                   		sol_aux = k * values[i - 1] +
dp[i - 1][j - k * p[i - 1]];
            				dp[i][j] = max(sol_aux, dp[i - 1][j]);
			} else {
				dp[i][j] = dp[i - 1][j];
				}
		}
	}
        }
    }
    return dp[m][n * x];
}

int task3(int n, int m, int x, vector <int> &p, vector <vector <int> > &g) {
	// adaptat dupa codul din lab, dar slightly modificat
	// ca am mai pus o dimensiune in matricea dp
	// ca sa-mi faca pentru k platouri per total
	int i, j;
	vector<int> values;
	values.assign(m, 0);
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            values[i] = values[i] + g[j][i];
        }
    }
	// dp este o matrice de dimensiune
	// (n+1) x (m+1) x (total+1)
	// dp[k][i][j] = suma maxima de note cumparand
	// primele i platouri, avand un buget de j si folosind exact k platouri
	vector<vector<vector<int>>> dp(n+1,
vector<vector<int>>(m+1, vector<int>(n*x+1)));
    // cazul de baza
	for (int i = 0; i <= m; ++i) {
		for (int cap = 0; cap <= n*x; ++cap) {
			dp[0][i][cap] = 0;
		}
	}
    // caz general
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= m; ++i) {
            for (int j = 0; j <= n * x; ++j) {
                // nu cumpar platoul i => e solutia de la pasul i - 1
                dp[k][i][j] = dp[k][i - 1][j];
                // cumpar platoul i O DATA,
		// deci trebuie sa iau costuri[i] bani din ce am
                // inseamna ca inainte trebuie sa am maxim j - costuri[i] bani
                if (j - p[i] >= 0 && k >= 1) {
                    int sol_aux = dp[k - 1][i - 1][j - p[i]] + values[i];
			// ^ mai adaug un platou la cele
			// k - 1 pe care le aveam, ca sa fie k
                    dp[k][i][j] = max(dp[k][i][j], sol_aux);
                }
                // cumpar platoul i DE DOUA ORI,
		// deci trebuie sa iau 2 * costuri[i] bani din ce am
                // inseamna ca inainte trebuie sa am maxim j - 2 * costuri[i]
                if (j - 2 * p[i] >= 0 && k >= 2) {
                    int sol_aux = dp[k - 2][i - 1][j - 2 *
p[i]] + 2 * values[i];
			// ^ mai adaug 2 platouri la cele
			// k - 2 pe care le aveam, ca sa fie k
                    dp[k][i][j] = max(dp[k][i][j], sol_aux);
                }
            }
        }
    }
    return dp[n][m][n*x];
}


int main() {
	freopen("sushi.in", "r", stdin);
	freopen("sushi.out", "w", stdout);

	int task;  // task number

	int n;  // number of friends
	int m;  // number of sushi types
	int x;  // how much each of you is willing to spend

	vector <int> prices;  // prices of each sushi type
	// the grades you and your friends gave to each sushi type
	vector <vector <int> > grades;

	cin >> task;
	cin >> n >> m >> x;

	prices.assign(m, 0);
	grades.assign(n, vector <int> (m, 0));

	// price of each sushi
	for(int i = 0; i < m; ++i) {
		cin >> prices[i];
	}

	// each friends rankings of sushi types
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			cin >> grades[i][j];
		}
	}

	int ans = -1;

	switch(task) {
		case 1:
			ans = task1(n, m, x, prices, grades);
			break;
		case 2:
			ans = task2(n, m, x, prices, grades);
			break;
		case 3:
			ans = task3(n, m, x, prices, grades);
			break;
		default:
			cout << "wrong task number" << endl;
	}

	cout << ans << endl;

	return 0;
}
