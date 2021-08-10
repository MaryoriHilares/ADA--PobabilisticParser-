#ifndef PRODUCCIONES_H
#define PRODUCCIONES_H

#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include "node.h"
#include "earleystate.h"

using namespace std;

class Production{
    public:
        Node production_leftside;
        vector<Node> production_rightside;
        float prob;
        int frecuencia;
        
        Production() = default;

        Production(Node production_leftside, vector<Node> production_rightside){
            this -> production_leftside = production_leftside;
            this -> production_rightside = production_rightside;
        }
        Production(Node production_leftside, vector<Node> production_rightside,float prob){
            this -> production_leftside = production_leftside;
            this -> production_rightside = production_rightside;
            this -> prob=prob;
        }

        vector<vector<Node>> readProduction_Right(string &cadena, int &ind){
            vector<vector<Node>> production_rightside_list;
            int ind_current =ind;
            while (ind < cadena.size())
            {
                if (cadena[ind] == '|')
                {
                    Node nodo;
                    vector<Node> vectorNodes = nodo.readNode(cadena,ind_current,ind-1);
                    production_rightside_list.push_back(vectorNodes); 
                    ind_current = ind + 1;
                }
                ind++;
            }
            Node nodo1;
            vector<Node> vectorNodes = nodo1.readNode(cadena,ind_current,ind);
            production_rightside_list.push_back(vectorNodes); 
            return production_rightside_list;
        }

        void readProduction_Left(string& cadena,int &ind){
            Node node;
            while (ind < cadena.size() && cadena[ind] != ':')
                ind++;
            if (node.readNode(cadena, 0 , ind - 1)[0].type == non_terminal){
                production_leftside = node.readNode(cadena, 0, ind)[0];
            }
            else
                std::cout <<cadena <<"Produccion incorrecta\n";  
                
            ind += 3;
        }

        vector<Production> readProduction(string cadena){
 
            int indice=0;
            vector<Production> production;
            readProduction_Left(cadena,indice);
            Production produc;
            vector<vector<Node>> current = readProduction_Right(cadena,indice);

            produc.production_leftside = production_leftside;
            for(int i = 0; i < current.size(); i++){
                produc.production_rightside = current[i];
                production.push_back(produc);
            }

            return production;
        }
        
        EarleyState convertToState(int value){
            EarleyState es;
            es.earley_state_left = this -> production_leftside;
            Node node;
            node.produccion_string = '.';
            node.type = punto;
            vector<Node> temp = production_rightside;
            temp.insert(temp.begin() + value, node);
            es.earley_state_right = temp;
            es.position_point = value;
            return es;
        }


        bool operator==(const Production& o) const{ 
            if (this->production_rightside == o.production_rightside && this->production_leftside == o.production_leftside)
                  return true;
           return false;
        }

};



#endif