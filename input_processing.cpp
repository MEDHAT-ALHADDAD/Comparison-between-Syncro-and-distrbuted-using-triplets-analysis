#include "input_processing.h"

float total = 0;
si keys;
//(@name: trim_string)
//(@signature: string& s -> string)
//(@purpose: take ptr to string and trim non alpha char and return to upper string)
//
//(@progress: completed)
//(@template: $vector<string> = trim_string( $string ))
string trim_String(string& s) {
	string result;
	char c;
	for (int i = 0; i < s.length(); i++)
	{
			if (isalpha(s[i])) {
				c = toupper(s[i]);
				result.pb(c);
			}
	}
	return result;
}

//(@name: to_triplets)
//(@signature: string& s -> vector<string>&)
//(@purpose: take ptr to string and return vector of strings each containing a triplet)
//
//(@progress: completed)
//(@template: $vector<string> = to_triplets( $string ))
si to_triplets(string& s) {
	si tri;
	FOR(i, s.length()) {
		if (i % 3 == 0) { tri.pb(""); }
		tri.back().pb(s[i]);
	}
	return tri;
}



//(@name: triplet_frequency)
//(@signature: vector<string>& -> map<string,pair<int,float>)
//(@purpose: take ptr to string and return dict of triplet:frequency)
//
//(@progress: completed)
//(@template: $map<string,int>  = triplet_frequency( $vector<string> ))
msfp triplet_frequency(si& tri) {
	keys = tri;
	int triplet_vector_size = tri.size();
	msfp frequency;
	map<string, omp_lock_t> hist_locks;
	vector<omp_lock_t> locks;
	locks.resize(triplet_vector_size);
	#pragma omp parallel for schedule(static)
	for (int i = 0; i < locks.size(); i++) {
		omp_init_lock(&locks[i]);
		omp_set_lock(&locks[i]);
		hist_locks[tri[i]] = locks[i];
		omp_unset_lock(&locks[i]);
	}
	#pragma omp parallel for schedule(static)
	for (int i = 0; i < tri.size(); i++) {
		//#pragma omp atomic
		omp_set_lock(&hist_locks[tri[i]]);
		frequency[tri[i]].first++;
		omp_unset_lock(&hist_locks[tri[i]]);
		//total++;
	}
	#pragma omp parallel for schedule(static)
	for (int i = 0; i < locks.size(); i++) {
		omp_destroy_lock(&hist_locks[tri[i]]);
	}
	total = triplet_vector_size;
	return frequency;
}

//(@name: triplet_percentage)
//(@signature: map<string,pair<int, float>& -> void)
//(@purpose: Calculate the percentage of each triplet)
//(@progress: completed)
//(@template: triplet_percentage( $map<string,pair<int, float> ))
void triplet_percentage(msfp& tri)
{
	int number_of_keys = (int)total;
	#pragma omp parallel for schedule(static)
	for (int i = 0; i < number_of_keys; i++) {
		//#pragma omp critical
		tri[keys[i]].second = (tri[keys[i]].first / total) * 100;
	}
}

//(@name: print_triplets)
//(@signature: vector<string>& -> void)
//(@purpose: print the triplets each on a line)
// for debug
//(@progress: completed)
//(@template: print_triplets( $vector<string> ))
void print_triplets(si& tri) {
	for (auto& s : tri) {
		cout << s << "\n";
	}
}


//(@name: print_frequency)
//(@signature: map<string,pair<int,float>& -> void)
//(@purpose: print the triplets:frequency & Percentage each on a line)
// final output
//(@progress: completed)
//(@template: print_frequency( $map<string,int> ))
void print_frequency(msfp& tri_freq) {
	for (auto& s : tri_freq) {
		cout << s.first << ":" << s.second.first << "   " << s.second.second << "%" << endl;
	}
}

void init_acids(msi& acid)
{
	acid["Phe"] = 0;
	acid["Leu"] = 0;
	acid["Lle"] = 0;
	acid["Met"] = 0;
	acid["Pro"] = 0;
	acid["Val"] = 0;
	acid["Ser"] = 0;
	acid["Thr"] = 0;
	acid["Ala"] = 0;
	acid["Tyr"] = 0;
	acid["Stop"] = 0;
	acid["Hls"] = 0;
	acid["Gln"] = 0;
	acid["Asn"] = 0;
	acid["Lys"] = 0;
	acid["Asp"] = 0;
	acid["Glu"] = 0;
	acid["Arg"] = 0;
	acid["Trp"] = 0;
	acid["Cys"] = 0;
	acid["Gly"] = 0;
}