#include "serial.h"


si serial_triplet_keys,serial_acid_keys;
float serial_total = 0;

//(@name: serial_proccessing)
//(@signature: void ->void)
//(@purpose: serial pipline)
//
//(@progress: completed)
//(@template: serial_proccessing())
void serial_proccessing()
{
    // open files for read and write
    freopen("InputSeq.dat.txt", "r", stdin);
    freopen("serial_output.txt", "w", stdout);

    //decleration
    string  input_line; // string
    si triplets,sequance;                 //vector string
    msfp triplets_frequency,acids_frequency;              // map<string,int>

    // proccess input to a stream of upper alpha
    while (getline(cin, input_line))
    {
        input_line = serial_trim_String(input_line);
        sequance.push_back( input_line );
    }

    //create a vector of strings(codins)
    triplets = serial_to_triplets(sequance);

    double tick = omp_get_wtime();

    triplets_frequency = serial_triplet_frequency(triplets);
    serial_triplet_percentage(triplets_frequency);
    acids_frequency = serial_acid_frequency(triplets);
    serial_acid_percentage(acids_frequency);

    double tock = omp_get_wtime();

    cout << "      serial     *The Triplets Frequency*\n\n";
    print_frequencyPER(triplets_frequency);
    cout << "____________________________________________________________________________\n";
    cout << "      serial     *The Acids Frequency*\n\n";
    print_frequencyPER(acids_frequency);
    cout << "____________________________________________________________________________\n";
    cout << "      serial     *Time Taken*\n\n";
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
string serial_trim_String(string &s)
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
si serial_to_triplets(si &s)
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

//(@name: triplet_frequency)
//(@signature: vector<string>& -> map<string,int>)
//(@purpose: take ptr to string and return dict of triplet:frequency)
//
//(@progress: completed)
//(@template: $map<string,int>  = triplet_frequency( $vector<string> ))
msfp serial_triplet_frequency(si &tri)
{
    serial_triplet_keys = tri;
    msfp frequency;
    for (auto &s : tri)
    {
        frequency[s].first++;
    }
    serial_total = tri.size();
    return frequency;
}

//(@name: triplet_percentage)
//(@signature: map<string,pair<int, float>& -> void)
//(@purpose: Calculate the percentage of each triplet)
//(@progress: completed)
//(@template: triplet_percentage( $map<string,pair<int, float> ))
void serial_triplet_percentage(msfp &tri)
{
    int number_of_keys = (int)serial_total;
    for (int i = 0; i < serial_triplet_keys.size(); i++)
    {
        tri[serial_triplet_keys[i]].second = (tri[serial_triplet_keys[i]].first / serial_total) * 100;
    }
}

//(@name: triplet_frequency)
//(@signature: vector<string>& -> map<string,int>)
//(@purpose: take ptr to string and return dict of triplet:frequency)
//
//(@progress: completed)
//(@template: $map<string,int>  = triplet_frequency( $vector<string> ))
msfp serial_acid_frequency(si& tri) {
	int triplet_vector_size = tri.size();
	msfp frequency;
	for (int i = 0; i < tri.size(); i++) {
        string s = serial_add_acids(tri[i]);
        frequency[s].first++;
	}
	serial_total = triplet_vector_size;
	return frequency;
}


si serial_acids_vect{"Phe", "Leu", "Lle", "Met", "Pro", "Val", "Ser", "Thr", "Ala", "Tyr", "Stop", "Hls", "Gln", "Asn", "Lys", "Asp", "Glu", "Arg", "Trp", "Cys", "Gly"};
//(@name: triplet_percentage)
//(@signature: map<string,pair<int, float>& -> void)
//(@purpose: Calculate the percentage of each triplet)
//(@progress: completed)
//(@template: triplet_percentage( $map<string,pair<int, float> ))
void serial_acid_percentage(msfp &tri)
{
    int number_of_keys = (int)serial_total;
    for (int i = 0; i < serial_acids_vect.size(); i++)
    {
        //#pragma omp critical
        tri[serial_acids_vect[i]].second = (tri[serial_acids_vect[i]].first / serial_total) * 100;
    }
}

string serial_add_acids(string s){
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


msfp init_acids(msfp &temp)
{
    msfp serial_acid;
    serial_acid["Phe"].first = temp["TTT"].first + temp["TTC"].first;
    serial_acid["Leu"].first = temp["TTA"].first + temp["TTG"].first + temp["CTT"].first + temp["CTC"].first + temp["CTA"].first + temp["CTG"].first;
    serial_acid["Lle"].first = temp["ATT"].first + temp["ATC"].first + temp["ATA"].first;
    serial_acid["Met"].first = temp["ATG"].first;
    serial_acid["Pro"].first = temp["CCT"].first + temp["CCC"].first + temp["CCA"].first + temp["CCG"].first;
    serial_acid["Val"].first = temp["GTT"].first + temp["GTC"].first + temp["GTA"].first + temp["GTG"].first;
    serial_acid["Ser"].first = temp["TCT"].first + temp["TCC"].first + temp["TCA"].first + temp["TCG"].first + temp["AGT"].first + temp["AGC"].first;
    serial_acid["Thr"].first = temp["ACT"].first + temp["ACC"].first + temp["ACA"].first + temp["ACG"].first;
    serial_acid["Ala"].first = temp["GCT"].first + temp["GCC"].first + temp["GCA"].first + temp["GCG"].first;
    serial_acid["Tyr"].first = temp["TAT"].first + temp["TAC"].first;
    serial_acid["Stop"].first = temp["TAA"].first + temp["TAG"].first + temp["TGA"].first;
    serial_acid["Hls"].first = temp["CAT"].first + temp["CAC"].first;
    serial_acid["Gln"].first = temp["CAA"].first + temp["CAG"].first;
    serial_acid["Asn"].first = temp["AAT"].first + temp["AAC"].first;
    serial_acid["Lys"].first = temp["AAA"].first + temp["AAG"].first;
    serial_acid["Asp"].first = temp["GAT"].first + temp["GAC"].first;
    serial_acid["Glu"].first = temp["GAA"].first + temp["GAG"].first;
    serial_acid["Arg"].first = temp["CGT"].first + temp["CGC"].first + temp["CGA"].first + temp["CGG"].first + temp["AGA"].first + temp["AGG"].first;
    serial_acid["Trp"].first = temp["TGG"].first;
    serial_acid["Cys"].first = temp["TGT"].first + temp["TGC"].first;
    serial_acid["Gly"].first = temp["GGT"].first + temp["GGC"].first + temp["GGA"].first + temp["GGG"].first;
    return serial_acid;
}

