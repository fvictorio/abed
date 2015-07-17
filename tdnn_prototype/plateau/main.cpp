#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

void plateau_divide(vector<double> &v, unsigned int delay) {
    vector<int> divide_by(v.size(), 0);

    for (unsigned int i = 0; i+delay <= v.size(); i++) {
        for (unsigned int delta = 0; delta < delay; delta++) {
            divide_by[i+delta]++;
        }
    }

    for (unsigned int i = 0; i < v.size(); i++) {
        v[i] /= divide_by[i];
    }
}

void plateau_divide_fast(vector<double> &v, unsigned int delay) {
    const unsigned int n = v.size();
    const unsigned int plateau = min(n - delay + 1, delay);

    unsigned int i = 0;

    while (i < plateau) {
        v[i] /= i + 1;
        ++i;
    }
    while (i + plateau < n) {
        v[i] /= plateau;
        ++i;
    }
    while (i < n) {
        v[i] /= n - i;
        ++i;
    }
}

int main () {
    string line;
    unsigned int delay;

    while (getline(cin, line) && cin >> delay) {
        stringstream ss;
        ss << line;

        vector<double> v;

        double x;
        while (ss >> x) {
            v.push_back(x);
        }

        plateau_divide_fast(v, delay);

        for (unsigned int i = 0; i < v.size(); i++) {
            cout << v[i] << " ";
        }
        cout << endl;

        cin.ignore();
    }
}
