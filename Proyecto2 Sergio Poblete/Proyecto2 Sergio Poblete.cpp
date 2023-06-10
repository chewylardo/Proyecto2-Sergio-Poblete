
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>
#include<cstdlib>
#include <string>
using namespace std;


typedef struct guardian {

    string Name, auxPowerLevel, Village, MainMaster;
    int PowerLevel;
    list<guardian>misAprendices;
    list<guardian>Maestro;
    string estado = "sin vencer";


} Guardian;


typedef struct ciudades {
    string Nombre;
    list<string>Vecinos;
    list<ciudades>newVecinos;
    list<Guardian>guardianes;



}Ciudades;
Guardian reeplazarGuardian(Guardian i) {

    i.Name = "Angron";
    int max;
    srand((unsigned)time(NULL));
    int min = 0;
    list<Guardian>::iterator it;
    for (it = i.Maestro.begin(); it != i.Maestro.end(); it++) {

        max = it->PowerLevel;
        cout <<"max: "<< max << endl;
    }

    list<Guardian>::iterator it2;
    for (it2 = i.misAprendices.begin(); it2 != i.misAprendices.end(); it2++) {

        if (it2->PowerLevel > min) {
            min = it2->PowerLevel;
            cout << "min: " << min << endl;
        }

    }
   
    int random = min + (rand() % (max));
    cout << "soy random " << random << endl;
    i.PowerLevel = random;

    return i;
}

int entrenar() {

    return 0;
}
string viajar(Guardian miGuardian, list<Ciudades>misCiudades) {

    system("cls");
    cout << "A que ciudad desea usted viajar" << endl;
    list<string>normal;
    list<string>alquimea;
    Ciudades CiudadActual;
    string voydeviaje;
    cout << "\n" << endl;
    for (auto const& i : misCiudades) {
        if (i.Nombre == miGuardian.Village) {
            CiudadActual = i;
            cout <<"mi ciudad es "<< CiudadActual.Nombre << endl;
        }

    }
    cout << "Viaje regular + 1 punto" << endl;
    cout << "------------------------------" << endl;
    for (auto const& i : CiudadActual.Vecinos) {
        
        cout << i << endl;
        normal.push_back(i);
      
    }
    
    cout << "\n\n" << endl;
    cout << "Viaje con alquimea -4 puntos" << endl;
    cout << "------------------------------" << endl;
    int aux = 0;
    list<Ciudades>::iterator it2;
    for (it2 = misCiudades.begin(); it2 != misCiudades.end(); it2++) {

        for (auto const& i : CiudadActual.newVecinos) {
            
            if (it2->Nombre == i.Nombre) {
                aux++;
            }
        }

        if (it2->Nombre != "comodin" && aux == 0) {
            cout << it2->Nombre << endl;
            alquimea.push_back(it2->Nombre);
        }
    }

    while(voydeviaje!="yaviaje"){
        getline(cin,voydeviaje);
        for (auto const& i : normal) {

            if (voydeviaje == i) {
                system("cls");
                cout << "viajaste a " << i << " ganaste 1 punto" << endl;
                cout << "\n\n" << endl;
                return i;
            }
            
        }
        
        for (auto const& i : alquimea) {

            if (voydeviaje == i) {
                system("cls");
                cout << "viajaste a " << i << " perdiste 4 puntos" << endl;
                cout << "\n\n" << endl;
                return i;
            }
            
        }

        cout << "porfavor ingrese un valor valido" << endl;
    }
    
    

    return "test1";
}

void menuInicial(list<Guardian>Guardianes, list<Ciudades>misCiudades){

    Guardian miGuardian;
    queue<string>recorrido;
    miGuardian.Name = "Nulo";
    cout << "Bienvenido a el juego" << endl;
    cout << "selecione un guardian con el que quiere jugar (escriba el nombre exactamente igual)"<<endl;
    cout << "\n" << endl;
  
  

    list<Ciudades>::iterator it;
    for (it = misCiudades.begin(); it != misCiudades.end(); it++) {

        for (auto const& i : it->guardianes) {

            cout << i.Name << endl;
            cout << i.auxPowerLevel << endl;
            
        }
           
    }

    string buscar;
 
    
    while (miGuardian.Name == "Nulo") {
        cin >> buscar;

        list<Guardian>::iterator it;
        for (it = Guardianes.begin(); it != Guardianes.end(); it++) {

            if (buscar == it->Name) {
                miGuardian.Name = it->Name;
                miGuardian.Village = it->Village;
                miGuardian.MainMaster = it->MainMaster;
                miGuardian.PowerLevel = it->PowerLevel;
                //cout << "original power level" << it->PowerLevel << endl;
                *it=reeplazarGuardian(*it);
                //añadir funcion para reparar el guardian clonado, debe revisar su maestro y aprendces para  que no sea mas debil que sus aprendices y no sea mas fuerte que su maestro

                //cout << it->Name << endl;
                //cout << it->PowerLevel << endl;
            }
        }
        
    }
    


    system("cls");
    bool StormhartDefeated = false;
    string selector1;
    
    while (StormhartDefeated == false) {
        cout << "Jugando con " << miGuardian.Name << endl;
        cout << "Poder Actual " << miGuardian.PowerLevel << endl;
        cout << "Ciudad Actual " << miGuardian.Village << endl;
        cout << "------------------------------------------------" << endl;
        cout << "Quiere viajar o entrenar" << endl;
        cout << "(escriba que prefiere)" << endl;
        cin >> selector1;
        if (selector1 == "viajar") {
            miGuardian.Village=viajar(miGuardian, misCiudades);
        }
        if (selector1 == "entrenar") {

        }
    }
    

}




Guardian crearG(string name,  string  village, string  mainMaster, int powerlevel) {

    Guardian newGuardian;

    newGuardian.Name = name;
    newGuardian.Village = village;
    newGuardian.MainMaster = mainMaster;
    newGuardian.PowerLevel = powerlevel;
   // newGuardian.PowerLevel = stoi(newGuardian.auxPowerLevel);

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

    return *it;

}

void ListaDevecinos(list<Ciudades>misCiudades) {


    list<Ciudades>::iterator it;
    for (it = misCiudades.begin(); it != misCiudades.end(); it++)
    {
        for (auto const& i : it->Vecinos) {

            it->newVecinos.push_back(buscarVecino(misCiudades, i));

           // cout << i << endl;
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

               // cout << "entre" << endl;
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
       // cout << PowerLevel << endl;
       
      
       
        Guardianes.push_back(crearG(Name, Village, MainMaster, PowerLevel));
        //cout << Village<< endl;
    }

    //cout << "\n\n\n\n" << endl;
    inFile.close();
    list<Guardian>::iterator it;
    for (it = Guardianes.begin(); it != Guardianes.end(); it++)
    {
        string name = it->Name;
       // cout << name << endl;
        //cout << it->PowerLevel << endl;
        
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
        if (it4->Nombre != "comodin" ) {
            for (auto const& i : it4->guardianes) {

                if (it4->Nombre != "Tesla") {
                    // cout << i.Name << endl;
                    contHabitantes++;

                }
                else {
                    contHabitantes = 2;
                }


            }
            //cout << contHabitantes << endl;
            if (contHabitantes < 2) {
                //cout << it4->Nombre << endl;
                cout << "Porfavor reparar archivo Guardianes.txt" << endl;
                cout << "Se requieren minimo 2 guardianes por ciudad(sin incluir tesla, este solo necesita 1)";
                return 0;
            }
        }
    }

    list<Guardian>::iterator it5;
    for (it5 = Guardianes.begin(); it5 != Guardianes.end(); it5++)
    {

        list<Guardian>::iterator it6;
        for (it6 = Guardianes.begin(); it6 != Guardianes.end(); it6++) {

            if (it5->MainMaster == it6->Name){
                it5->Maestro.push_back(*it6);
            }

        }

        list<Guardian>::iterator it7;
        for (it7 = Guardianes.begin(); it7 != Guardianes.end(); it7++) {

            if (it7->MainMaster == it5->Name) {
                it5->misAprendices.push_back(*it7);
            }

        }

    }

    menuInicial(Guardianes, misCiudades);



    return 0;
}