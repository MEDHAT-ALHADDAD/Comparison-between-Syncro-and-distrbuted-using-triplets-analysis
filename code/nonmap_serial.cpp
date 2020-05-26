#include "nonmap_serial.h"


si nonserial_triplet_keys,nonserial_acid_keys;
si nonserial_acids_vect{"Phe", "Leu", "Lle", "Met", "Pro", "Val", "Ser", "Thr", "Ala", "Tyr", "Stop", "Hls", "Gln", "Asn", "Lys", "Asp", "Glu", "Arg", "Trp", "Cys", "Gly"};
float nonserial_total = 0;

//(@name: nonserial_proccessing)
//(@signature: void ->void)
//(@purpose: nonserial pipline)
//
//(@progress: completed)
//(@template: nonserial_proccessing())
void nonserial_proccessing()
{
    // open files for read and write
    freopen("InputSeq.dat.txt", "r", stdin);
    freopen("nonserial_output.txt", "w", stdout);

    //decleration
    string  input_line; // string
    si triplets,sequance;                 //vector string
    vsfp triplets_frequency,acids_frequency;              // map<string,int>

    // proccess input to a stream of upper alpha
    while (getline(cin, input_line))
    {
        input_line = nonserial_trim_String(input_line);
        sequance.push_back( input_line );
    }

    //create a vector of strings(codins)
    triplets = nonserial_to_triplets(sequance);

    double tick = omp_get_wtime();

    triplets_frequency = nonserial_triplet_frequency(triplets);
    nonserial_triplet_percentage(triplets_frequency);
    acids_frequency = nonserial_acid_frequency(triplets);
    nonserial_acid_percentage(acids_frequency);

    double tock = omp_get_wtime();

    cout << "      nonserial     *The Triplets Frequency*\n\n";
    print_frequency(triplets_frequency);
    cout << "____________________________________________________________________________\n";
    cout << "      nonserial     *The Acids Frequency*\n\n";
    print_frequency(acids_frequency);
    cout << "____________________________________________________________________________\n";
    cout << "      nonserial     *Time Taken*\n\n";
    cout << "Numbers Of Threads: " << omp_get_num_threads() << endl;
    cout << tock - tick << endl;
    ;

    cin.clear();
}

//(@name: trim_string)
//(@signature: string& s -> string)
//(@purpose: take ptr to string and trim non alpha char and returen to uppper string)
//
//(@progress: completed)
//(@template: $vector<string> = trim_string( $string ))
string nonserial_trim_String(string &s)
{
    string result;
    for (auto &ch : s)
    {
        if (isalpha(ch))
        {
            result.pb(toupper(ch));
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
si nonserial_to_triplets(si &s)
{
    si tri;
    for (auto &&str : s)
    {
        FOR(i, str.length())
        {
            if (i % 3 == 0)
            {
                tri.pb("");
            }
            tri.back().pb(str[i]);
        }   
    }
    return tri;
}

bool In_Vector(string s, vsfp &v){
    for (auto &&elem : v)
    {
        if( elem.first == s){
            return true;
        }
    }
    return false;
}

//(@name: triplet_frequency)
//(@signature: vector<string>& -> map<string,int>)
//(@purpose: take ptr to string and return dict of triplet:frequency)
//
//(@progress: completed)
//(@template: $map<string,int>  = triplet_frequency( $vector<string> ))
vsfp nonserial_triplet_frequency(si &tri)
{
    nonserial_triplet_keys = tri;
    vsfp frequency;
    for (auto &s : tri)
    {
        if (!In_Vector(s,frequency))
        {
            pair<string,fp> temp;
            temp.first = s; 
            frequency.pb(temp);
        }        
        
        for (auto &elem : frequency)
        {
            if (elem.first == s)
            {
                elem.second.first++;
            }
        }
    }
    sort(frequency.begin(), frequency.end()); 
    nonserial_total = tri.size();
    return frequency;
}

//(@name: triplet_percentage)
//(@signature: map<string,pair<int, float>& -> void)
//(@purpose: Calculate the percentage of each triplet)
//(@progress: completed)
//(@template: triplet_percentage( $map<string,pair<int, float> ))
void nonserial_triplet_percentage(vsfp &tri)
{
    int number_of_keys = (int)nonserial_total;
    for (int i = 0; i < tri.size(); i++)
    {
        tri[i].second.second = (tri[i].second.first / nonserial_total) * 100;
    }
}

//(@name: triplet_frequency)
//(@signature: vector<string>& -> map<string,int>)
//(@purpose: take ptr to string and return dict of triplet:frequency)
//
//(@progress: completed)
//(@template: $map<string,int>  = triplet_frequency( $vector<string> ))
vsfp nonserial_acid_frequency(si& tri) {
	int triplet_vector_size = tri.size();
	vsfp frequency;
    for (auto &&acid : nonserial_acids_vect)
    {
        pair<string,fp> temp;
        temp.first = acid; 
        frequency.pb(temp);
    }
    
	for (int i = 0; i < tri.size(); i++) {
        for (auto &&elem : frequency)
        {
            if (elem.first == nonserial_add_acids(tri[i]))
            {
                elem.second.first++;
            }
        }
	}
    sort(frequency.begin(), frequency.end()); 
	nonserial_total = triplet_vector_size;
	return frequency;
}
//(@name: triplet_percentage)
//(@signature: map<string,pair<int, float>& -> void)
//(@purpose: Calculate the percentage of each triplet)
//(@progress: completed)
//(@template: triplet_percentage( $map<string,pair<int, float> ))
void nonserial_acid_percentage(vsfp &tri)
{
    int number_of_keys = (int)nonserial_total;
    for (int i = 0; i < tri.size(); i++)
    {
        tri[i].second.second = (tri[i].second.first / nonserial_total) * 100;
    }
}

string nonserial_add_acids(string s){
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