
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


typedef struct guardian {

    string Name, auxPowerLevel, Village, MainMaster;
    int PowerLevel;
    guardian newMainMaster();

}Guardian;


typedef struct ciudades {
    string Nombre;
    list<string>Vecinos;
    list<ciudades>newVecinos;
    list<Guardian>guardianes;


}Ciudades;

void menuInicial(list<Guardian>Guardianes, list<Ciudades>misCiudades){

    Guardian miGuardian;

    cout << "selecione un guardian con el que quiere jugar"<<endl;




}

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

Ciudades buscarVecino(list<Ciudades>misCiudades, string vecino) {

    Ciudades auxCity;

    list<Ciudades>::iterator it;
    for (it = misCiudades.begin(); it != misCiudades.end(); it++)
    {
        if (it->Nombre == vecino) {

            return *it;
        }

    }


}

void ListaDevecinos(list<Ciudades>misCiudades) {


    list<Ciudades>::iterator it;
    for (it = misCiudades.begin(); it != misCiudades.end(); it++)
    {
        for (auto const& i : it->Vecinos) {

            it->newVecinos.push_back(buscarVecino(misCiudades, i));

            cout << i << endl;
        }

    }



}

list<Ciudades> Habitantes(list<Guardian>Guardianes, list<Ciudades>misCiudades){



    list<Guardian>::iterator it;
    for (it = Guardianes.begin(); it != Guardianes.end(); it++)
    {   
      
        list<Ciudades>::iterator it2;
        for (it2 = misCiudades.begin(); it2 != misCiudades.end(); it2++) {
         
            if (it->Village == it2->Nombre){

                cout << "entre" << endl;
                it2->guardianes.push_back(*it);

            }

        }

    }

    
    return misCiudades;

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
        getline(ss, MainMaster, ',');
        getline(ss, Village, ',');
       
      

        Guardianes.push_back(crearG(Name, Village, MainMaster, PowerLevel));
        cout << Village<< endl;
    }

    cout << "\n\n\n\n" << endl;
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
    bool tesla = false;
    while (getline(inFile2, mynewstring)) {
        stringstream ss(mynewstring);
        getline(ss,ciudad, ',');
        getline(ss,vecino, ',');
        list<Ciudades>::iterator it2;
        for (it2 = misCiudades.begin(); it2 != misCiudades.end(); it2++)
        {
            if (it2->Nombre == ciudad) {
                
                it2->Vecinos.push_back(vecino);

                continue;
            }
        }
        misCiudades.push_back(crearC(ciudad, vecino, misCiudades));
        if (ciudad == "Tesla") {
            tesla = true;
        }
    }

    if (tesla == false) {

        misCiudades.push_back(crearC("Tesla", "", misCiudades));
    }


    inFile2.close();
    int contciudades = 0;
    list<Ciudades>::iterator it3;
    for (it3 = misCiudades.begin(); it3 != misCiudades.end(); it3++)
    {
        if (it3->Nombre != "comodin") {
           // cout << "\n" << it3->Nombre << endl;
            //cout << "\nse conecta con\n" ;
            for (auto const& i : it3->Vecinos) {
               //cout << i << endl;
            }

            
        }
        contciudades++;
    }

    if (contciudades < 3) {

        cout << "no hay suficientes ciudades para jugar" << endl;
        cout << "porfavor reparar archivo Villages.txt";
        return 0;
    }

    misCiudades = Habitantes(Guardianes, misCiudades);

    
    int contHabitantes = 0;
    list<Ciudades>::iterator it4;
    for (it4 = misCiudades.begin(); it4 != misCiudades.end(); it4++) {
        contHabitantes = 0;
        if (it4->Nombre != "comodin" && it4->Nombre != "River Village") {
            for (auto const& i : it4->guardianes) {

                if (it4->Nombre != "Tesla") {
                    // cout << i.Name << endl;
                    contHabitantes++;

                }
                else {
                    contHabitantes = 2;
                }


            }
            cout << contHabitantes << endl;
            if (contHabitantes < 2) {
                cout << it4->Nombre << endl;
                cout << "Porfavor reparar archivo Guardianes.txt" << endl;
                cout << "Se requieren minimo 2 guardianes por ciudad(sin incluir tesla, este solo necesita 1)";
                return 0;
            }
        }
    }

    



    return 0;
}