#include "main.h"

//(@name: main)
//(@signature: argc,argv ->int)
//(@purpose: initthe program)
//
//(@progress: completed)
//(@template: cmd$make run)
int main(int argc, char const *argv[])
{
    freopen("InputSeq.dat.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    string sequance,temp;
    si triplets;
    msi frequency;

    while (cin >> temp)
    {
        temp = trim_String(temp);
        sequance += temp;
    }
    triplets = to_triplets(sequance);
    frequency = triplet_frequency(triplets);
    // print_triplets(triplets);
    print_frequency(frequency);
}
