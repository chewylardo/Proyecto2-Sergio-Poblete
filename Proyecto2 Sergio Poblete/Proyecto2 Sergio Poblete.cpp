
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>
#include <string>
using namespace std;


int main(int argc, char** argv)
{

    string mystring;
    ifstream inFile;

    inFile.open("Guardianes.txt");
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    inFile >> mystring; // pipe file's content into stream
    cout << mystring;

    inFile.close();



    return 0;
}