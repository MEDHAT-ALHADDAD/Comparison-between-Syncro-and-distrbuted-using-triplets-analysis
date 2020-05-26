#include "tasks.h"


float tasks_total = 0;
int tasks_threads_num=32;
si tasks_triplet_keys;

//(@name: tasks_proccessing)
//(@signature: void ->void)
//(@purpose: tasks pipline)
//
//(@progress: completed)
//(@template: tasks_proccessing())
void tasks_proccessing()
{
    // open files for read and write
    freopen("InputSeq.dat.txt", "r", stdin);
    freopen("tasks_output.txt", "w", stdout);
	string sequence, temp;
	si triplets;
	msfp triplets_frequency,acids_frequency;
    
    omp_set_num_threads(tasks_threads_num);
     while (getline(cin, temp))
    {
        temp = tasks_trim_String(temp);
        sequence += temp;
    }
    triplets = tasks_to_triplets(sequence);


    double tick = omp_get_wtime();

	triplets_frequency = tasks_triplet_frequency(triplets);
	tasks_triplet_percentage(triplets_frequency);
    acids_frequency = tasks_acid_frequency(triplets);
    tasks_acid_percentage(acids_frequency);

    double tock = omp_get_wtime();
    
    cout << "     tasks      *The Triplets Frequency*\n\n";
    print_frequencyPER(triplets_frequency);
    cout << "____________________________________________________________________________\n";
    cout << "     tasks      *The Acids Frequency*\n\n";
    print_frequencyPER(acids_frequency);
    cout << "____________________________________________________________________________\n";
    cout << "      tasks     *Time Taken*\n\n";
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
string tasks_trim_String(string& s){    
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
si tasks_to_triplets(string& s){
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
msfp tasks_triplet_frequency(si& tri) {
	tasks_triplet_keys = tri;
	int triplet_vector_size = tri.size();
	msfp frequency;
    #pragma omp parallel
    {
        #pragma omp single 
        {
            int chunk = tri.size() / tasks_threads_num;
            for (int i = 0; i < tasks_threads_num; ++i) 
            {
                if (i == tasks_threads_num - 1)
                #pragma omp task
                {
                    for (int j = chunk * i ; j < tri.size() ; j++)
                    {
                        string s = tri[j];
                        #pragma omp critical
                        frequency[s].first++;
                    }
                }
                else
                #pragma omp task
                {
                     for (int j = chunk * i ; j < (chunk * (i+1)) ; j++)
                    {
                        string s = tri[j];
                        #pragma omp critical
                        frequency[s].first++;
                    }
                }
            }
        }
        // Let the threads process all tasks
        #pragma omp taskwait
    }
	tasks_total = triplet_vector_size;
	return frequency;
}


//(@name: triplet_percentage)
//(@signature: map<string,pair<int, float>& -> void)
//(@purpose: Calculate the percentage of each triplet)
//(@progress: completed)
//(@template: triplet_percentage( $map<string,pair<int, float> ))
void tasks_triplet_percentage(msfp& tri)
{
    int number_of_keys = (int)tasks_total;
    #pragma omp parallel
    {
        #pragma omp single 
        {
            int chunk = tasks_triplet_keys.size() / tasks_threads_num;
            for (int i = 0; i < tasks_threads_num; ++i) 
            {
                if (i == tasks_threads_num - 1)
                #pragma omp task
                {
                    for (int j = chunk * i ; j < tasks_triplet_keys.size() ; ++j )
                    {
                        string s = tasks_triplet_keys[j];
                        float x = (tri[s].first / tasks_total) * 100;
                        #pragma omp critical
                        tri[s].second = x;
                    }
                }
                else
                #pragma omp task
                {
                     for (int j = chunk * i ; j < (chunk * (i+1)) ; ++j )
                    {
                        string s = tasks_triplet_keys[j];
                        float x = (tri[s].first / tasks_total) * 100;
                        #pragma omp critical
                        tri[s].second = x;
                    }
                }
                
               
            }
        }
        // Let the threads process all tasks
        #pragma omp taskwait
    }
}

//(@name: triplet_frequency)
//(@signature: vector<string>& -> map<string,int>)
//(@purpose: take ptr to string and return dict of triplet:frequency)
//
//(@progress: completed)
//(@template: $map<string,int>  = triplet_frequency( $vector<string> ))
msfp tasks_acid_frequency(si& tri) {
	int triplet_vector_size = tri.size();
	msfp frequency;
    #pragma omp parallel
    {
        #pragma omp single 
        {
            int chunk = tri.size() / tasks_threads_num;
            for (int i = 0; i < tasks_threads_num; ++i) 
            {
                if (i == tasks_threads_num - 1)
                #pragma omp task
                {
                    for (int j = chunk * i ; j < tri.size() ; j++)
                    {
                        string s = tasks_add_acids(tri[j]);
                        #pragma omp critical
                        frequency[s].first++;
                    }
                }
                else
                #pragma omp task
                {
                    for (int j = chunk * i ; j < (chunk * (i+1)) ; j++)
                    {
                        string s = tasks_add_acids(tri[j]);
                        #pragma omp critical
                        frequency[s].first++;
                    }
                }
            }
        }
        // Let the threads process all tasks
        #pragma omp taskwait
    }
	tasks_total = triplet_vector_size;
	return frequency;
}

si tasks_acids_vect{"Phe","Leu","Lle","Met","Pro","Val","Ser","Thr","Ala","Tyr","Stop","Hls","Gln","Asn","Lys","Asp","Glu","Arg","Trp","Cys","Gly"};
//(@name: triplet_percentage)
//(@signature: map<string,pair<int, float>& -> void)
//(@purpose: Calculate the percentage of each triplet)
//(@progress: completed)
//(@template: triplet_percentage( $map<string,pair<int, float> ))
void tasks_acid_percentage(msfp& tri)
{
    #pragma omp parallel
    {
        #pragma omp single 
        {
            int chunk = tasks_acids_vect.size() / tasks_threads_num;
            for (int i = 0; i < tasks_threads_num; ++i) 
            {
                if (i == tasks_threads_num - 1)
                #pragma omp task
                {
                    for (int j = chunk * i ; j < tasks_acids_vect.size() ; ++j )
                    {
                        string s = tasks_acids_vect[j];
                        float x = (tri[s].first / tasks_total) * 100;
                        #pragma omp critical
                        tri[s].second = x;
                    }
                }
                else
                #pragma omp task
                {
                    for (int j = chunk * i ; j < (chunk * (i+1)) ; ++j )
                    {
                        string s = tasks_acids_vect[j];
                        float x = (tri[s].first / tasks_total) * 100;
                        #pragma omp critical
                        tri[s].second = x;
                    }
                }  
            }
        }
        // Let the threads process all tasks
        #pragma omp taskwait
    }
}

string tasks_add_acids(string s){
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
    else
        return "";
}