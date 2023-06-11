
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
    int puntosTotales = 3;



}Ciudades;

Guardian reeplazarGuardian(Guardian i) {

    i.Name = "Angron";
    int max;
    srand((unsigned)time(NULL));
    int min = 0;
    list<Guardian>::iterator it;
    for (it = i.Maestro.begin(); it !=i.Maestro.end(); it++) {

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
   
    int random = min + (rand() % (max-min+1));
    cout << "soy random " << random << endl;
    i.PowerLevel = random;

    return i;
}
bool pelea(list<Guardian>* Guardianes, list<Ciudades>* misCiudades, Guardian* miGuardian,string enemigoElegido){

    srand((unsigned)time(NULL));
    list<Guardian>::iterator it;
    int playerPower;
    int enemyPower;
    for (it = Guardianes->begin(); it != Guardianes->end(); it++) {

        if (it->Name == enemigoElegido) {
            int random = 1 + (rand() % (20));
            playerPower = miGuardian->PowerLevel * random;
             random = 1 + (rand() % (20));
             enemyPower = it->PowerLevel * random;
            if (playerPower >= enemyPower) {
                
                return true;
            }
            else {

                return false;
            }
        }

    }



    return false;
}
int entrenar(list<Guardian> *Guardianes, list<Ciudades> *misCiudades, Guardian *miGuardian) {


    Ciudades CiudadActual;
    for (auto const& i : *misCiudades) {
        if (i.Nombre == miGuardian->Village) {
            CiudadActual = i;
            cout << "mi ciudad es " << CiudadActual.Nombre << endl;
        }

    }

    int min;
    int max;
    int cont = 0;
    Guardian MaestroActual;
    Guardian Recomendado;
    string selector;

    for (auto const& i : CiudadActual.guardianes) {
        
        if (cont == 0) {
            min = i.PowerLevel;
            max = i.PowerLevel;
            MaestroActual = i;
        }else if(i.PowerLevel>=max && i.Name != "") {
            max = i.PowerLevel;
            MaestroActual = i;
        }
        else if(i.PowerLevel<=min && i.Name != ""){
            min = i.PowerLevel;
            Recomendado = i;
        }

        if (i.Name != miGuardian->Name) {
            cout << i.Name << endl;
        }
        
        cont++;
    }
    system("cls");
    cout << "Elija con quien quiere entrenar(introdusca el nombre exactio)" << endl;
    if (miGuardian->Village != "Tesla" ) {

        list<Guardian>::iterator it2;
        cout << "Maestro " << MaestroActual.Name << MaestroActual.PowerLevel << endl;
        cout << "Aprendiz recomendad " << Recomendado.Name << Recomendado.PowerLevel << endl;
        cout << "Otras opciones" << endl;
        for (it2 = CiudadActual.guardianes.begin(); it2 != CiudadActual.guardianes.end(); it2++) {

            if (it2->Name != MaestroActual.Name && it2->Name != Recomendado.Name && it2->Name != "") {
                cout << it2->Name << " " << it2->PowerLevel << endl;
            }

        }

    }
    else {
        if (miGuardian->PowerLevel >= 90) {
            cout << "deseas pelear contra " << MaestroActual.Name << " " << MaestroActual.PowerLevel << endl;
        }
        else {
            cout << "No estas listo para pelear en contra de " << MaestroActual.Name << endl;
            return 0;
        }
        
    }

    do {
        cin >> selector;
        bool resultado;
        list<Guardian>::iterator it3;
        for (it3 = CiudadActual.guardianes.begin(); it3 != CiudadActual.guardianes.end(); it3++) {

            if (it3->Name == MaestroActual.Name && selector == it3->Name) {
                resultado = pelea(Guardianes,misCiudades,miGuardian, it3->Name);
                if (resultado == true) {
                    return 2;
                }
                else {
                    return 0;
                }
            }
            else if (selector == it3->Name) {
                resultado = pelea(Guardianes, misCiudades, miGuardian, it3->Name);
                if (resultado == true) {
                    return 1;
                }
                else {
                    return 0;
                }
            }


        }
        selector = "Nulo";
    }while (selector == "Nulo");





    return 0;
}
string viajar(Guardian *miGuardian, list<Ciudades>misCiudades) {

    system("cls");
    srand((unsigned)time(NULL));
    cout << "A que ciudad desea usted viajar" << endl;
    list<string>normal;
    list<string>alquimea;
    Ciudades CiudadActual;
    string voydeviaje;
    cout << "\n" << endl;
    for (auto const& i : misCiudades) {
        if (i.Nombre == miGuardian->Village) {
            CiudadActual = i;
            cout <<"mi ciudad es "<< CiudadActual.Nombre << endl;
        }

    }
    cout << "Viaje regular (ganar 1 punto)" << endl;
    cout << "------------------------------" << endl;
    for (auto const& i : CiudadActual.Vecinos) {

        cout << i << endl;
        normal.push_back(i);

    }

    cout << "\n\n" << endl;
    cout << "Viaje con alquimea (perder de 2 a 4 puntos)" << endl;
    cout << "------------------------------" << endl;
    bool yaesxiste = false;
    list<Ciudades>::iterator it2;
    for (it2 = misCiudades.begin(); it2 != misCiudades.end(); it2++) {
        list<string>::iterator it3;
        for (it3 = normal.begin(); it3 !=normal.end(); it3++) {

            if (it2->Nombre == *it3) {

                yaesxiste = true;
            }

        }

        if (yaesxiste == false && it2->Nombre!="comodin" && it2->Nombre!=""){
            cout << it2->Nombre << endl;
        }

        yaesxiste = false;
    }

    while(voydeviaje!="yaviaje"){
        getline(cin,voydeviaje);
        for (auto const& i : normal) {

            if (voydeviaje == i) {
                system("cls");
                cout << "viajaste a " << i << " ganaste 1 punto" << endl;
                miGuardian->PowerLevel += 1;
                cout << "\n\n" << endl;
                return i;
            }
            
        }
        
        for (auto const& i : alquimea) {

            if (voydeviaje == i) {
                system("cls");
                int random = 2 + (rand() % (4 - 2 + 1));
                cout << "viajaste a " << i << " perdiste "<<random<< " puntos" << endl;
                
                miGuardian->PowerLevel -= random;
                cout << "\n\n" << endl;
                return i;
            }
            
        }

        cout << "porfavor ingrese un valor valido" << endl;
    }
    
    

    return "test1";
}

void menuInicial(list<Guardian>Guardianes, list<Ciudades>misCiudades){
    system("cls");
    Guardian miGuardian;
    queue<string>recorrido;
    miGuardian.Name = "Nulo";
    cout << "Bienvenido a el juego" << endl;
    cout << "selecione un guardian con el que quiere jugar (escriba el nombre exactamente igual)"<<endl;
    cout << "---------------------------------------------------\n" << endl;
  
  

    list<Ciudades>::iterator it;
    for (it = misCiudades.begin(); it != misCiudades.end(); it++) {

        for (auto const& i : it->guardianes) {

            if (i.Name != "Stormheart" && i.Name != "") {
                cout << i.Name << endl;
            }
           
            
            
        }
           
    }

    string buscar;
    Guardian Pointer;
    list<Ciudades>::iterator it9;
 
    while (miGuardian.Name == "Nulo") {
        cin >> buscar;

        list<Guardian>::iterator it;
        for (it = Guardianes.begin(); it != Guardianes.end(); it++) {
            list<Ciudades>::iterator it2;
            for (it2 = misCiudades.begin(); it2 != misCiudades.end(); it2++) {
                list<Guardian>::iterator it3;
                for (it3 = it2->guardianes.begin(); it3 != it2->guardianes.end(); it3++) {
                    if (buscar == it->Name && it->Name == it3->Name && buscar != "Stormheart" && buscar != "") {
                        miGuardian.Name = it->Name;
                        miGuardian.Village = it->Village;
                        miGuardian.MainMaster = it->MainMaster;
                        miGuardian.PowerLevel = it->PowerLevel / 2;
                        //cout << "original power level" << it->PowerLevel << endl;

                        *it = reeplazarGuardian(*it);
                        *it3 = *it;
                        //añadir funcion para reparar el guardian clonado, debe revisar su maestro y aprendces para  que no sea mas debil que sus aprendices y no sea mas fuerte que su maestro

                        //cout << it->Name << endl;
                        //cout << it->PowerLevel << endl;
                    }
                }

            }

        }

    }


    system("cls");
    bool StormhartDefeated = false;
    string selector1;
    recorrido.push(miGuardian.Village);
    while (StormhartDefeated == false) {
        cout << "Jugando con " << miGuardian.Name << endl;
        cout << "Poder Actual " << miGuardian.PowerLevel << endl;
        cout << "Ciudad Actual " << miGuardian.Village << endl;
        cout << "------------------------------------------------" << endl;
        cout << "Quiere viajar o entrenar" << endl;
        cout << "(escriba que prefiere)" << endl;
        cin >> selector1;
        if (selector1 == "viajar") {
            miGuardian.Village=viajar(&miGuardian, misCiudades);
            recorrido.push(miGuardian.Village);
        }
        if (selector1 == "entrenar") {
            miGuardian.PowerLevel+=entrenar(&Guardianes, &misCiudades, &miGuardian);
            miGuardian.auxPowerLevel = 90;
        }
       
    }

    system("cls");

    list<Guardian>::iterator it3;
    for (it3 = Guardianes.begin(); it3  != Guardianes.end(); it3++) {
        
        if (it3->Name != ""){
            cout << "nombre " << it3->Name << " maestro " << it3->MainMaster << endl;
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


Ciudades ValidacionFinalCiudades(list<Ciudades>misCiudades,string Nombre) {
    Ciudades AuxCity;
    bool ciudadExiste = false;


    list<Ciudades>::iterator it;
    for (it = misCiudades.begin(); it != misCiudades.end(); it++)
    {
        if (it->Nombre == Nombre) {

            ciudadExiste = true;
        }

    }

    if (ciudadExiste == false) {
        return crearC(Nombre, " ", misCiudades);
    }
    else {
        return crearC("comodin", " ", misCiudades);
    }
  

   
   
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
    while (getline(inFile, mystring)) {
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

    //capital,forest,mountain,desert,coast,river,valley,hill
    //forest,mountain,capital,desert,coast,river,valley,hill,

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
        getline(ss, ciudad, ',');
        getline(ss, vecino, ',');
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

    list<Ciudades>::iterator yt;
    for (yt = misCiudades.begin(); yt != misCiudades.end(); yt++)
    {
        list<string>::iterator yt2;
        for (yt2 = yt->Vecinos.begin(); yt2 != yt->Vecinos.end(); yt2++)
        {

            misCiudades.push_back(ValidacionFinalCiudades(misCiudades, *yt2));
        }
    }

    if (tesla == false) {

        misCiudades.push_back(crearC("Tesla", "", misCiudades));
    }

    list<Ciudades>::iterator it2;
    for (it2 = misCiudades.begin(); it2 != misCiudades.end(); it2++)
    {   
        if(it2->Nombre!="comodin")
        cout << it2->Nombre << endl;
    }

    list<string>auxNombres;

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
        if (it4->Nombre != "comodin" && it4->Nombre!=" ") {
            for (auto const& i : it4->guardianes) {

                if (it4->Nombre != "Tesla") {
                    // cout << i.Name << endl;
                    contHabitantes++;

                }
                else {
                    contHabitantes = 2;
                }

                cout << it4->Nombre << " " << i.Name<<endl;

            }
            cout << contHabitantes << endl;
            if (contHabitantes < 2 ) {
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

            if (it5->MainMaster == it6->Name) {
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