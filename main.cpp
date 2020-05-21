#include "main.h"

//(@name: main)
//(@signature: argc,argv ->int)
//(@purpose: init the program)
//
//(@progress: completed)
//(@template: cmd$make run)
int main(int argc, char const* argv[])
{
	freopen("InputSeq.dat.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	string sequence, temp;
	si triplets;
	msfp frequency;

	omp_set_num_threads(4);

	double tick = omp_get_wtime();
//#pragma omp parallel 
	//{
//#pragma omp single
		//{
			while (cin >> temp)
			{
//#pragma omp task firstprivate(temp) lastprivate(temp)
				temp = trim_String(temp);
				sequence += temp;
			}
		//}

	//}
	triplets = to_triplets(sequence);
	frequency = triplet_frequency(triplets);
	triplet_percentage(frequency);
	//print_triplets(triplets);
	print_frequency(frequency);
	double tock = omp_get_wtime();
	cout << tock - tick << endl;
}
