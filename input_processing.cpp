#include "input_processing.h"


//(@name: trim_string)
//(@signature: string& s -> string)
//(@purpose: take ptr to string and trim non alpha char and returen to uppper string)
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
//(@purpose: take ptr to string and return vector of strings each contain  triplet)
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
//(@signature: vector<string>& -> map<string,int>)
//(@purpose: take ptr to string and return dict of triplet:frequency)
//
//(@progress: completed)
//(@template: $map<string,int>  = triplet_frequency( $vector<string> ))
msi triplet_frequency(si& tri){
    msi frequency;
    for(auto& s:tri){
        frequency[s]++;
    }
    return frequency;
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
//(@signature: map<string,int>& -> void)
//(@purpose: print the triplets:frequency each on a line)
// final output
//(@progress: completed)
//(@template: print_frequency( $map<string,int> ))
void print_frequency(msi& tri_freq){
    for(auto& s:tri_freq){
        cout << s.first << ":" << s.second << endl;
    }
}

