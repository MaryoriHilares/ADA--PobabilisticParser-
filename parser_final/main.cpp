#include <iostream>
#include <fstream>
#include <vector>
#include "earleyparser.h"

using namespace std;
 
int main(){
    string cadena;
    EarleyParser ep("gramatica.txt");
    
    ep.leerFreq("frecuencias.txt");
    ep.printProb();    
    ep.input();//Funcion para ingresar la cadena 

    bool acceptado = ep.EarleyParser_();
    ep.ActualizarFrec();//Esta funcion ayuda a los incrementos y actualizaciones de las frecuencias
    if (acceptado)
        cout<< "La cadena ingresada ha sido aprobada por la gramatica"<<endl;
    else
        cout<< "La cadena NO ha sido aprobada"<<endl;
    ep.printProb();
    
    return 0;
}