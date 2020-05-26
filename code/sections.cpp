#include "sections.h"


float sections_total = 0;
int sections_threads_num=32;
si sections_triplet_keys;

//(@name: sections_proccessing)
//(@signature: void ->void)
//(@purpose: sections pipline)
//
//(@progress: completed)
//(@template: sections_proccessing())
void sections_proccessing()
{
    // open files for read and write
    freopen("InputSeq.dat.txt", "r", stdin);
    freopen("sections_output.txt", "w", stdout);
	string sequence, temp;
	si triplets;
	msfp triplets_frequency,acids_frequency;
    
    omp_set_num_threads(sections_threads_num);
     while (getline(cin, temp))
    {
        temp = sections_trim_String(temp);
        sequence += temp;
    }
    triplets = sections_to_triplets(sequence);


    double tick = omp_get_wtime();

	triplets_frequency = sections_triplet_frequency(triplets);
	sections_triplet_percentage(triplets_frequency);
    acids_frequency = sections_acid_frequency(triplets);
    sections_acid_percentage(acids_frequency);

    double tock = omp_get_wtime();
    
    cout << "     sections      *The Triplets Frequency*\n\n";
    print_frequencyPER(triplets_frequency);
    cout << "____________________________________________________________________________\n";
    cout << "     sections      *The Acids Frequency*\n\n";
    print_frequencyPER(acids_frequency);
    cout << "____________________________________________________________________________\n";
    cout << "      sections     *Time Taken*\n\n";
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
string sections_trim_String(string& s){    
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
si sections_to_triplets(string& s){
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
msfp sections_triplet_frequency(si& tri) {
	sections_triplet_keys = tri;
	int triplet_vector_size = tri.size();
	msfp frequency;
    int chunk = tri.size() / 4;
    #pragma omp parallel
    {
        #pragma omp sections nowait
		{
			#pragma omp section
			{
                for (int i =  (chunk * 0); i < (chunk * (0+1)); i++)
                {
                    string s = tri[i];
                    #pragma omp critical
                    frequency[s].first++;
                }
			}
			#pragma omp section
			{
                for (int i =  (chunk * 1); i < (chunk * (1+1)); i++)
                {
                    string s = tri[i];
                    #pragma omp critical
                    frequency[s].first++;
                }
			}
            #pragma omp section
			{
                for (int i =  (chunk * 2); i < (chunk * (2+1)); i++)
                {
                    string s = tri[i];
                    #pragma omp critical
                    frequency[s].first++;
                }
			}
            #pragma omp section
			{
                for (int i =  (chunk * 3); i < tri.size(); i++)
                {
                    string s = tri[i];
                    #pragma omp critical
                    frequency[s].first++;
                }
			}

		} 
    }
	sections_total = triplet_vector_size;
	return frequency;
}


//(@name: triplet_percentage)
//(@signature: map<string,pair<int, float>& -> void)
//(@purpose: Calculate the percentage of each triplet)
//(@progress: completed)
//(@template: triplet_percentage( $map<string,pair<int, float> ))
void sections_triplet_percentage(msfp& tri)
{
    int number_of_keys = (int)sections_total;
    int chunk = sections_triplet_keys.size() / 4;
    #pragma omp parallel
    {
        #pragma omp sections nowait
		{
			#pragma omp section
			{
				for (int i =  (chunk * 0); i < (chunk * (0+1)); i++)
                {
                   string s = sections_triplet_keys[i];
                   float x = (tri[sections_triplet_keys[i]].first / sections_total) * 100;
                   #pragma omp critical
                   tri[s].second = x;
                }
			}
			#pragma omp section
			{
				for (int i =  (chunk * 1); i < (chunk * (1+1)); i++)
                {
                   string s = sections_triplet_keys[i];
                   float x = (tri[sections_triplet_keys[i]].first / sections_total) * 100;
                   #pragma omp critical
                   tri[s].second = x;
                }
			}
            #pragma omp section
			{
				for (int i =  (chunk * 2); i < (chunk * (2+1)); i++)
                {
                   string s = sections_triplet_keys[i];
                   float x = (tri[sections_triplet_keys[i]].first / sections_total) * 100;
                   #pragma omp critical
                   tri[s].second = x;
                }
			}
            #pragma omp section
			{
				for (int i =  (chunk * 3); i < sections_triplet_keys.size(); i++)
                {
                   string s = sections_triplet_keys[i];
                   float x = (tri[sections_triplet_keys[i]].first / sections_total) * 100;
                   #pragma omp critical
                   tri[s].second = x;
                }
			}

		} 
    }
}

//(@name: triplet_frequency)
//(@signature: vector<string>& -> map<string,int>)
//(@purpose: take ptr to string and return dict of triplet:frequency)
//
//(@progress: completed)
//(@template: $map<string,int>  = triplet_frequency( $vector<string> ))
msfp sections_acid_frequency(si& tri) {
	int triplet_vector_size = tri.size();
	msfp frequency;
    int chunk = tri.size() / 4;
    #pragma omp parallel
    {
        #pragma omp sections nowait
		{
			#pragma omp section
			{
				for (int i =  (chunk * 0); i < (chunk * (0+1)); i++)
                {
                   string s = sections_add_acids(tri[i]);
                   #pragma omp critical
                   frequency[s].first++;
                }
			}
			#pragma omp section
			{
				for (int i =  (chunk * 1); i < (chunk * (1+1)); i++)
                {
                   string s = sections_add_acids(tri[i]);
                   #pragma omp critical
                   frequency[s].first++;
                }
			}
			#pragma omp section
			{
				for (int i =  (chunk * 2); i < (chunk * (2+1)); i++)
                {
                   string s = sections_add_acids(tri[i]);
                   #pragma omp critical
                   frequency[s].first++;
                }
			}
			#pragma omp section
			{
				for (int i =  (chunk * 3); i < tri.size(); i++)
                {
                   string s = sections_add_acids(tri[i]);
                   #pragma omp critical
                   frequency[s].first++;
                }
			}
		} 
    }
	sections_total = triplet_vector_size;
	return frequency;
}

si sections_acids_vect{"Phe","Leu","Lle","Met","Pro","Val","Ser","Thr","Ala","Tyr","Stop","Hls","Gln","Asn","Lys","Asp","Glu","Arg","Trp","Cys","Gly"};
//(@name: triplet_percentage)
//(@signature: map<string,pair<int, float>& -> void)
//(@purpose: Calculate the percentage of each triplet)
//(@progress: completed)
//(@template: triplet_percentage( $map<string,pair<int, float> ))
void sections_acid_percentage(msfp& tri)
{
    int chunk = sections_acids_vect.size() / 4;
    #pragma omp parallel
    {
        #pragma omp sections nowait
		{
			#pragma omp section
			{
                for (int i =  (chunk * 0); i < (chunk * (0+1)); i++)
                {
                   string s = sections_acids_vect[i];
                   float x = (tri[sections_acids_vect[i]].first / sections_total) * 100;
                   #pragma omp critical
                   tri[s].second = x;
                }
			}
			#pragma omp section
			{
                for (int i =  (chunk * 1); i < (chunk * (1+1)); i++)
                {
                   string s = sections_acids_vect[i];
                   float x = (tri[sections_acids_vect[i]].first / sections_total) * 100;
                   #pragma omp critical
                   tri[s].second = x;
                }
			}
			#pragma omp section
			{
                for (int i =  (chunk * 2); i < (chunk * (2+1)); i++)
                {
                   string s = sections_acids_vect[i];
                   float x = (tri[sections_acids_vect[i]].first / sections_total) * 100;
                   #pragma omp critical
                   tri[s].second = x;
                }
			}
			#pragma omp section
			{
                for (int i =  (chunk * 3); i < sections_acids_vect.size(); i++)
                {
                   string s = sections_acids_vect[i];
                   float x = (tri[sections_acids_vect[i]].first / sections_total) * 100;
                   #pragma omp critical
                   tri[s].second = x;
                }
			}
		} 
    }
}

string sections_add_acids(string s){
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