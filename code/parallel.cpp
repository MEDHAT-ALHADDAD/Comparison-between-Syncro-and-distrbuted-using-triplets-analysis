#include "parallel.h"


float total = 0;
int threads_num=32;
si triplet_keys,acid_keys;
si parallel_triplets;

//(@name: serial_proccessing)
//(@signature: void ->void)
//(@purpose: parallel pipline)
//
//(@progress: completed)
//(@template: parallel_proccessing())
void parallel_proccessing()
{
    // open files for read and write
    freopen("InputSeq.dat.txt", "r", stdin);
    freopen("parallel_output.txt", "w", stdout);
	string temp;
	si sequence;
	msfp triplets_frequency,acids_frequency;

    omp_set_num_threads(threads_num);
      while (getline(cin, temp))
    {
        sequence.pb(temp);
    }
    
    for (int i = 0; i < sequence.size(); i++)
    {
        temp = trim_String(sequence[i]);
	    to_triplets(temp);
    }
    
    

    
    double tick = omp_get_wtime();

	triplets_frequency = triplet_frequency(parallel_triplets);
	triplet_percentage(triplets_frequency);
    acids_frequency = acid_frequency(parallel_triplets);
    acid_percentage(acids_frequency);

	double tock = omp_get_wtime();

    cout << "      parallel     *The Triplets Frequency*\n\n";
    print_frequencyPER(triplets_frequency);
    cout << "____________________________________________________________________________\n";
    cout << "      parallel     *The Acids Frequency*\n\n";
    print_frequencyPER(acids_frequency);
    cout << "____________________________________________________________________________\n";
    cout << "     parallel      *Time Taken*\n\n";
    // omp_thread_count work instead of omp_get_num_threads using gcc
    cout << "Numbers Of Threads: " << omp_thread_count() << endl;
	cout << tock - tick << endl;

    cin.clear();
}



//(@name: trim_string)
//(@signature: string& s -> string)
//(@purpose: take ptr to string and trim non alpha char and returen to uppper string)
//
//(@progress: completed)
//(@template: $vector<string> = trim_string( $string ))
string trim_String(string& s){    
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
//(@purpose: take ptr to string and return vector of strings each contain  triplet)
//
//(@progress: completed)
//(@template: $vector<string> = to_triplets( $string ))
void to_triplets(string& s){
    si tri;
    FOR(i,s.length()){
        if (i%3 == 0){parallel_triplets.pb("");}
        parallel_triplets.back().pb(s[i]);
    }
}



//(@name: triplet_frequency)
//(@signature: vector<string>& -> map<string,int>)
//(@purpose: take ptr to string and return dict of triplet:frequency)
//
//(@progress: completed)
//(@template: $map<string,int>  = triplet_frequency( $vector<string> ))
msfp triplet_frequency(si& tri) {
	triplet_keys = tri;
	int triplet_vector_size = tri.size();
	msfp frequency;
	#pragma omp parallel for schedule(dynamic)
	for (int i = 0; i < tri.size(); i++) 
    {
        string s = tri[i];
        #pragma omp critical
        frequency[s].first++;
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
	#pragma omp parallel for schedule(dynamic)
	for (int i = 0; i < triplet_keys.size(); i++) {
        string s = triplet_keys[i];
        float x = (tri[triplet_keys[i]].first / total) * 100;
        #pragma omp critical
		tri[s].second = x;
	}
}

//(@name: triplet_frequency)
//(@signature: vector<string>& -> map<string,int>)
//(@purpose: take ptr to string and return dict of triplet:frequency)
//
//(@progress: completed)
//(@template: $map<string,int>  = triplet_frequency( $vector<string> ))
msfp acid_frequency(si& tri) {
	int triplet_vector_size = tri.size();
	msfp frequency;
	#pragma omp parallel for schedule(dynamic)
	for (int i = 0; i < tri.size(); i++) {
        string s = add_acids(tri[i]);
        #pragma omp critical
        frequency[s].first++;
	}
	total = triplet_vector_size;
	return frequency;
}

si acids_vect{"Phe","Leu","Lle","Met","Pro","Val","Ser","Thr","Ala","Tyr","Stop","Hls","Gln","Asn","Lys","Asp","Glu","Arg","Trp","Cys","Gly"};
//(@name: triplet_percentage)
//(@signature: map<string,pair<int, float>& -> void)
//(@purpose: Calculate the percentage of each triplet)
//(@progress: completed)
//(@template: triplet_percentage( $map<string,pair<int, float> ))
void acid_percentage(msfp& tri)
{
	#pragma omp parallel for schedule(dynamic)
	for (int i = 0; i < acids_vect.size(); i++) {
        string s = acids_vect[i];
        float x = (tri[acids_vect[i]].first / total) * 100;
		#pragma omp critical
        tri[s].second = x;
	}
}

string add_acids(string s){
    if( s == "TTT" || s == "TTC" )
        return "Phe";
    else if (  s == "TTA" || s == "TTG" ||  s == "CTT" || s == "CTC" ||  s == "CTA" || s == "CTG" )
        return "Leu";
    else if (  s == "ATT" || s == "ATC" ||  s == "ATA" )
        return "Lle";
    else if (  s == "ATG" )
        return "Met";
    else if (  s == "CCT" || s == "CCC" ||  s == "CCA" || s == "CCG" )
        return "Pro";
    else if (  s == "GTT" || s == "GTC" ||  s == "GTA" || s == "GTG" )
        return "Val";
    else if (  s == "TCT" || s == "TCC" ||  s == "TCA" || s == "TCG" ||  s == "AGT" || s == "AGC" )
        return "Ser";
    else if (  s == "ACT" || s == "ACC" ||  s == "ACA" || s == "ACG" )
        return "Thr";
    else if (  s == "GCT" || s == "GCC" ||  s == "GCA" || s == "GCG" )
        return "Ala";
    else if (  s == "TAT" || s == "TAC" )
        return "Tyr";
    else if (  s == "TAA" || s == "TAG" ||  s == "TGA" )
        return "Stop";
    else if (  s == "CAT" || s == "CAC" )
        return "Hls";
    else if (  s == "CAA" || s == "CAG" )
        return "Gln";
    else if (  s == "AAT" || s == "AAC" )
        return "Asn";
    else if (  s == "AAA" || s == "AAG" )
        return "Lys";
    else if (  s == "GAT" || s == "GAC" )
        return "Asp";
    else if (  s == "GAA" || s == "GAG")
        return "Glu";
    else if (  s == "CGT" || s == "CGC" ||  s == "CGA" || s == "CGG" || s == "AGA" || s == "AGG" )
        return "Arg";
    else if (  s == "TGG" )
        return "Trp";
    else if (  s == "TGT" || s == "TGC" )
        return "Cys";
    else if (  s == "GGT" || s == "GGC" ||  s == "GGA" || s == "GGG" )
        return "Gly";
}