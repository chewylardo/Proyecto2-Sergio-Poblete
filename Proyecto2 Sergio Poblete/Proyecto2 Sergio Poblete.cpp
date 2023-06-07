
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
    string Name, auxPowerLevel, Village, MainMaster;
    int PowerLevel;
}Guardian;


typedef struct ciudades {
    string Nombre;
    list<ciudades>Vecinos;

}Ciudades;


Guardian crearG(string name,  string  village, string  mainMaster, int powerlevel) {

    Guardian newGuardian;

    newGuardian.Name = name;
    newGuardian.Village = village;
    newGuardian.MainMaster = mainMaster;
    newGuardian.auxPowerLevel = powerlevel;


    return newGuardian;
}



int main(int argc, char** argv)
{

    string mystring;
    ifstream inFile;
    list<Guardian>Guardianes;
    list<Ciudades>misCiudades;
    

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
      

        Guardianes.push_back(crearG(Name, Village, MainMaster, PowerLevel));
    }

    inFile.close();
    list<Guardian>::iterator it;
    for (it = Guardianes.begin(); it != Guardianes.end(); it++)
    {
        string name = it->Name;
        std::cout << name << endl;
    }





    return 0;
}