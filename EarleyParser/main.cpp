#include <iostream>
#include <fstream>
#include <vector>
//#include "earleystate.h"

using namespace std;

ifstream archivo_entrada("gramatica.txt");//accede a los archivos que desee
string linea;
int p=0;

void reconocer(){
    vector<string> vec;
    while(getline(archivo_entrada,linea)){
        int len=0 , n=0;
        string gram;
        for(int i=0 ; linea[i] != '\0' ; i++){
            len++;
            if(linea[i] == '-' && linea[i+1] == '>'){
               gram = linea.substr(n,len);
               n = i+1;
               len = 0;
               vec.push_back(gram);
            }
            if(linea[i] == '|' || linea[i] == ' ' ){
                gram = linea.substr(n, len);
                n = i+1;
                len = 0;
                vec.push_back(gram);
            } 
        }
    }
    for(int i=0 ; i<linea.size() ; i++){
        cout<<vec[i];
    }
}

int main(){
    string cadena;
    //EarleyState es;
    /*Producion pro*
    S -> NP VP
    PP -> P NP
    VP -> V NP
    VP -> VP PP
    .
    .
    .
    */
    //es.earleyparse(cadena , pro.dasdad)
    reconocer();
    return 0;
}
