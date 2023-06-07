
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


typedef struct Guardian {

}Guardian;

int main(int argc, char** argv)
{

    string mystring;
    ifstream inFile;

    inFile.open("Guardianes.txt");
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    string Name, auxPowerLevel, Village, MainMaster;
    int PowerLevel;
  while(getline(inFile, mystring)){ 
      stringstream ss(mystring);
      getline(ss, Name, ',');
      getline(ss, auxPowerLevel, ',');
      PowerLevel = stoi(auxPowerLevel);
      getline(ss, Village, ',');
      getline(ss, MainMaster, ',');
      cout << Name << "\n"; 
      }
    inFile.close();



    return 0;
}