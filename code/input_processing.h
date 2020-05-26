//#include "bits/stdc++.h" // include all ess cpp lib.
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <omp.h>
#include <string>
#include <math.h> 

using namespace std;

//defines
#define FOR(i,n) for(int(i)=0;(i)<(int)(n);(i)++)
#define pb push_back

typedef pair<string, int> ii;
typedef vector<string> si;
typedef vector<ii> vii;
typedef map<string,int> msi;
typedef pair<int, float> fp;
typedef map<string, fp> msfp;
typedef vector<pair<string,fp>> vsfp;

void print_triplets(si& tri);
void print_frequency(vsfp& tri_freq);
void print_frequencyPER(msfp& tri_freq);
int omp_thread_count();