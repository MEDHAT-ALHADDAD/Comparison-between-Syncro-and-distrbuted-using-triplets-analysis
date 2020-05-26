#include "input_processing.h"


string serial_trim_String(string& s);
si serial_to_triplets(si& s);
msfp serial_triplet_frequency(si& tri);
void serial_triplet_percentage(msfp& tri);
msfp serial_acid_frequency(si& tri);
void serial_acid_percentage(msfp& tri);
string serial_add_acids(string s);
msfp init_acids(msfp& temp);

void serial_proccessing();