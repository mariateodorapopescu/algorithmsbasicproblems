#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

int ok(vector<unsigned long long> g, unsigned long long n,
unsigned long long k, unsigned long long limit) {
	// functie care verifica daca se pot transporta masinile
	// pe un feribot de greutate maxima limit
	// in k ture, cele k ture fiind, de fapt, cele k feribot-uri
    unsigned long long nr, sum;
	int i;
	nr = 1;
    	sum = 0;
    for (i = 0; i < n; i++) {
        if (g[i] > limit) {
	// daca greutatea masinii depaseste cat poate duce, skip
            return 0;
        }
        if (sum + g[i] > limit) {
            nr = nr + 1;
	// daca nu poate lua urmatoarea masina,
	// face o grup noua de masini,
	// si marcheaza faptul ca se mai foloseste un feribot
            sum = g[i];
        } else {
            sum = sum + g[i];
	// altfel, cat timp poate lua masini, le ia
        }
    }
	if (nr <= k) {
		return 1;
	 // daca s-au folosit maxim k feribot-uri
	} else {
		return 0;
	}
}

unsigned long long divide_and_impera(vector<unsigned long long> g,
unsigned long long n, unsigned long long k, unsigned long long st,
unsigned long long dr) {
    while (st < dr) {
        unsigned long long mijl = (st + dr) / 2;
        if (ok(g, n, k, mijl) == 1) {
	// iau posibilitati de greutati per feribot, cu divide et imp
	// verificand cat de mult poate duce, tot miscorand
            dr = mijl;
        } else {
            st = mijl + 1;
	// si daca nu mai poate duce, creste minimul sa vada cat poate duce
	// asta, e de fapt, minimul
        }
    }
	return st;
}

int main() {
    freopen("feribot.in", "r", stdin);
    freopen("feribot.out", "w", stdout);
	unsigned long long n, k, st, dr;
	int i;
	cin >> n >> k;
	vector<unsigned long long> g(n);
    for (i = 0; i < n; i++) {
        cin >> g[i];
    }
	st = 0;
	dr = std::numeric_limits<unsigned long long>::max();
	// cum feribotul are capacitate infinita,
	// am luat ca margine dreapta acea capacitate infinita
    cout << divide_and_impera(g, n, k, st, dr);
	// caut greutate optima, greutatea totala fiind profitul

    return 0;
}
