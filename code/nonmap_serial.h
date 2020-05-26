#include "input_processing.h"

string nonserial_trim_String(string& s);
si nonserial_to_triplets(si& s);
vsfp nonserial_triplet_frequency(si& tri);
void nonserial_triplet_percentage(vsfp& tri);
vsfp nonserial_acid_frequency(si& tri);
void nonserial_acid_percentage(vsfp& tri);
string nonserial_add_acids(string s);

void nonserial_proccessing();