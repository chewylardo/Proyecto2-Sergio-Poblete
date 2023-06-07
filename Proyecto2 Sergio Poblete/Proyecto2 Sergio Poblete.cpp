
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
    list<string>Vecinos;

}Ciudades;


Guardian crearG(string name,  string  village, string  mainMaster, int powerlevel) {

    Guardian newGuardian;

    newGuardian.Name = name;
    newGuardian.Village = village;
    newGuardian.MainMaster = mainMaster;
    newGuardian.auxPowerLevel = powerlevel;


    return newGuardian;
}

Ciudades crearC(string nombre,string vecino,list<Ciudades> auxlist) {

    Ciudades newCiudad;
   
    
    list<Ciudades>::iterator it;
    for (it = auxlist.begin(); it != auxlist.end(); it++)
    {   
        if (it->Nombre == nombre) {

          
            it->Vecinos.push_back(vecino);
            newCiudad.Nombre = "comodin";
            return newCiudad;
        }
    }

   

    newCiudad.Nombre = nombre;
    newCiudad.Vecinos.push_back(vecino);
    
   

    return newCiudad;
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

    ifstream inFile2;
    string mynewstring;
    inFile2.open("Villages.txt");
    if (!inFile2) {
        cout << "Unable to open file";
        exit(1); 
    }

    string ciudad, vecino;

    while (getline(inFile2, mynewstring)) {
        stringstream ss(mynewstring);
        getline(ss,ciudad, ',');
        getline(ss,vecino, ',');

        misCiudades.push_back(crearC(ciudad, vecino, misCiudades));
    }
    inFile2.close();

    list<Ciudades>::iterator it2;

    for (it2 = misCiudades.begin(); it2 != misCiudades.end(); it2++)
    {
        if (it2->Nombre == "comodin") {

            misCiudades.erase(it2++);

        }
        
    }
   
  
    list<Ciudades>::iterator it3;
    for (it3 = misCiudades.begin(); it3 != misCiudades.end(); it3++)
    {   
            cout << it3->Nombre << endl;
    }

    return 0;
}