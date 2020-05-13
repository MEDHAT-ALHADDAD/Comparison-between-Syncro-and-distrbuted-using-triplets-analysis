#include "input_processing.h"

float total = 0;
//(@name: trim_string)
//(@signature: string& s -> string)
//(@purpose: take ptr to string and trim non alpha char and return to upper string)
//
//(@progress: completed)
//(@template: $vector<string> = trim_string( $string ))
string trim_String(string& s){    
    string result;
    for (auto& ch:s)
    {
        if(isalpha(ch)){result.pb(toupper(ch));}
    }
    return result;
}

//(@name: to_triplets)
//(@signature: string& s -> vector<string>&)
//(@purpose: take ptr to string and return vector of strings each containing a triplet)
//
//(@progress: completed)
//(@template: $vector<string> = to_triplets( $string ))
si to_triplets(string& s){
    si tri;
    FOR(i,s.length()){
        if (i%3 == 0){tri.pb("");}
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
msfp triplet_frequency(si& tri){
    msfp frequency;
#pragma omp parallel
    for(auto& s:tri){
#pragma omp atomic
        frequency[s].first++;
		total++;
    }
    return frequency;
}

//(@name: triplet_percentage)
//(@signature: map<string,pair<int, float>& -> void)
//(@purpose: Calculate the percentage of each triplet)
//(@progress: completed)
//(@template: triplet_percentage( $map<string,pair<int, float> ))
void triplet_percentage(msfp& tri)
{
#pragma omp parallel
	for (auto& s : tri) {
#pragma omp critical
		tri[s.first].second = (s.second.first / total) * 100;
	}
}

//(@name: print_triplets)
//(@signature: vector<string>& -> void)
//(@purpose: print the triplets each on a line)
// for debug
//(@progress: completed)
//(@template: print_triplets( $vector<string> ))
void print_triplets(si& tri){
    for(auto& s:tri){
        cout << s << "\n";
    }
}


//(@name: print_frequency)
//(@signature: map<string,pair<int,float>& -> void)
//(@purpose: print the triplets:frequency & Percentage each on a line)
// final output
//(@progress: completed)
//(@template: print_frequency( $map<string,int> ))
void print_frequency(msfp& tri_freq){
    for(auto& s:tri_freq){
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