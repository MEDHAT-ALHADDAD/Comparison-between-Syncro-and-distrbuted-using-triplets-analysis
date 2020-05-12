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
msi triplet_frequency(si& tri){
    msi frequency;
    for(auto& s:tri){
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
void triplet_percentage(msi& tri)
{
	for (auto& s : tri) {
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
void print_frequency(msi& tri_freq){
    for(auto& s:tri_freq){
		cout << s.first << ":" << s.second.first << "   " << s.second.second << "%" << endl;
    }
}

