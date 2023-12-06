/*
 * Acest schelet citește datele de intrare și scrie răspunsul generat de voi,
 * astfel că e suficient să completați cele două funcții.
 *
 * Scheletul este doar un punct de plecare, îl puteți modifica oricum doriți:
 * puteți schimba parametrii, reordona funcțiile etc.
 */

#include <cstdint>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <utility>

using namespace std;

// functia de mai jos a fost adaptata de pe geekforgeeks
// dupa ce am cautat cum sa returnez pozitia unui element din vector
int getIndex(vector<int> v, int K) {
    auto it = find(v.begin(), v.end(), K);
	// iteratorul intoarce unde se afla k in vector
    int index;
    if (it != v.end()) {
	// daca a gasit elementul
        index = it - v.begin();
	// intoarce indexul, ca iteratorul intoarce o pozitie
    } else {
       index = -1;
    }
    return index;
}

int64_t SolveTask1(const vector<int>& a, const vector<int>& b) {
    int sum, mina, maxb, aux;
	vector<int> acopy = a;
	vector<int> bcopy = b;
	// creez doua copii ale vectorilor ca la cum sunt dati ca argumente
	// nu ii pot modifica si imi iau o suma initial nula
    sum = 0;
    maxb = *max_element(bcopy.begin(), bcopy.end());
    mina = *min_element(acopy.begin(), acopy.end());
	// iau progresiv max din a si min din b si pana cand
	// minimul din a e mare decat maximul din b
	// adica sa am in a toate maximile
	// interschimb
	// as fi incercat cu swap dar nu merge, nu stiu de ce
	// dar compilatorul nu-l vede, orice as incerca
    while (mina < maxb) {
	aux = acopy[getIndex(acopy, mina)];
	acopy[getIndex(acopy, mina)] = bcopy[getIndex(bcopy, maxb)];
	bcopy[getIndex(bcopy, maxb)] = aux;
        maxb = *max_element(bcopy.begin(), bcopy.end());
        mina = *min_element(acopy.begin(), acopy.end());
    }
    sum = accumulate(acopy.begin(), acopy.end(), 0);
	// si la final fac suma din a-ul modificat, acolo avand numai maxime
    return sum;
}

int64_t SolveTask2(const vector<int>& a, const vector<int>& b, int moves) {
	// la fel ca la task1, dar acum numar in while-ul in care interschimb
    int sum, mina, maxb, nr, aux;
	vector<int> acopy = a;
	vector<int> bcopy = b;
    sum = 0;
    nr = 0;
    maxb = *max_element(bcopy.begin(), bcopy.end());
    mina = *min_element(acopy.begin(), acopy.end());
    while (mina < maxb && nr <= moves) {
	aux = acopy[getIndex(acopy, mina)];
	acopy[getIndex(acopy, mina)] = bcopy[getIndex(bcopy, maxb)];
	bcopy[getIndex(bcopy, maxb)] = aux;
        maxb = *max_element(bcopy.begin(), bcopy.end());
        mina = *min_element(acopy.begin(), acopy.end());
        nr++;
    }
    sum = accumulate(acopy.begin(), acopy.end(), 0);
    return sum;
}

vector<int> ReadVector(istream& is, int size) {
    vector<int> vec(size);
    for (auto& num : vec) {
        is >> num;
    }
    return vec;
}

int main() {
    ifstream fin("nostory.in");
    ofstream fout("nostory.out");

    int task;
    fin >> task;

    int n, moves;
    if (task == 1) {
        fin >> n;
    } else {
        fin >> n >> moves;
    }

    auto a = ReadVector(fin, n);
    auto b = ReadVector(fin, n);

    auto res = task == 1 ? SolveTask1(a, b) : SolveTask2(a, b, moves);
    fout << res << "\n";

    return 0;
}

