#include "input_processing.h"

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
void print_frequency(vsfp& tri_freq){
    for (auto& s : tri_freq) {
        to_string(s.second.first).resize (5,' ');
        to_string(s.second.second).resize (5,' ');
		cout << s.first << " : " << s.second.first << "   " << s.second.second << "%" << endl;
	}
}


//(@name: print_frequencyPER)
//(@signature: map<string,pair<int,float>& -> void)
//(@purpose: print the triplets:frequency & Percentage each on a line)
// final output
//(@progress: completed)
//(@template: print_frequencyPER( $map<string,int> ))
void print_frequencyPER(msfp& tri_freq) {
	for (auto& s : tri_freq) {
        to_string(s.second.first).resize (5,' ');
        to_string(s.second.second).resize (5,' ');
		cout << s.first << " : " << s.second.first << "   " << s.second.second << "%" << endl;
	}
}

int omp_thread_count() {
    int n = 0;
    #pragma omp parallel reduction(+:n)
    n += 1;
    return n;
}