//#include "bits/stdc++.h" // include all ess cpp lib.
#include <iostream>
#include <vector>
#include <map>

using namespace std;

//defines
#define FOR(i,n) for(int(i)=0;(i)<(int)(n);(i)++)
#define pb push_back

typedef pair<string, int> ii;
typedef vector<string> si;
typedef vector<ii> vii;
typedef map<string,int> msi;

string trim_String(string& s);
si to_triplets(string& s);
msi triplet_frequency(si& tri);
void print_triplets(si& tri);
void print_frequency(msi& tri_freq);