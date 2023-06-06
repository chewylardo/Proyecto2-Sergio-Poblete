
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
    
    char str[100];                                                                                                                     
    ifstream inFile;

    inFile.open("Guardianes.txt");
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    while (inFile.getline(str, 100, '#'))
    {
        cout << str << endl;
    }

    inFile.close();
    
    
   
    return 0;
}
