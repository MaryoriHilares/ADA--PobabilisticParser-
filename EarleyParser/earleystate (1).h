//copyright(C) Carlos Eduardo Atencio Torres
#ifndef EARLEY_STATE_H
#define EARLEY_STATE_H
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <fstream>
#include <vector>

using namespace std;

int S[size + 1];
const int size = sizeof(S) / sizeof(S[0]);

/*Los EarleyState se encargar´an de almacenar los subproblemas en que ser´a
dividido el analisis.*/
class Production{
    public:
        string prod;
        bool no_terminal;

        Production()=default;

        Production(string prod){
            this -> prod = prod;
        }
};

class EarleyState{//la situacion en la que se encuentra el punto
    public:
        Production* production;//S -> aB
        int indicePunto;//posicion del punto
        int indiceChart;//ya que chart es un arreglo de estados {S(0),S(1),S(2),S(3)}
        int estadoChart;// 0 , 1 , 2
        int Chart[size];
        EarleyState* staterefence;//guarda la referencia con respecto al estado  
        list<Production> lista_anteriores;//solo para la operacion "complete" pero dentro de un mismo chart

        EarleyState()=default;

        void init(string cadena){
            for(int k = 0 ; cadena.size() ; ++k){
                S[k] = 0;
            }
        }

        void earleyparser(string cadena , list<Production>* gramatica){
            init(cadena);
            indiceChart = 0;
            for(;indiceChart < Chart.size(); indiceChart++){
                EarleyState* earleystate;
                //earleystate = 
            }
        }

        /*void predictor()
        void completer()
        void scaneer()
        */
        
};

#endif
