//#include "bits/stdc++.h" // include all ess cpp lib.
#include <iostream>
#include <vector>
#include <map>
#include <omp.h>
#include <string>

using namespace std;

//defines
#define FOR(i,n) for(int(i)=0;(i)<(int)(n);(i)++)
#define pb push_back

typedef pair<string, int> ii;
typedef vector<string> si;
typedef vector<ii> vii;
typedef pair<int, float> fp;
typedef map<string, fp> msfp;
typedef map<string, int> msi;

string trim_String(string& s);
si to_triplets(string& s);
msfp triplet_frequency(si& tri);
void triplet_percentage(msfp& tri);
void print_triplets(si& tri);
void print_frequency(msfp& tri_freq);
void init_acids(msi& acid);