#ifndef GRAMATICA_H
#define GRAMATICA_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include "node.h"
#include "arch_aux.h"
#include "producciones.h"

using namespace std;
struct Common
{
    string common_LeftSide;
    vector<int> common_Productions;
};

class Gramatica
{
public:
    vector<Node> _non_terminal;
    vector<Node> _terminal;
    vector<Production> production;

    vector<Common> indx;
    string initial;

    Gramatica() = default;

    Gramatica(vector<Production> production)
    {
        this->production = production;
    }

    void Init()
    {
        bool visitedProductions[production.size()];
        memset(visitedProductions, false, production.size());
        Common common;

        for (int iterator = 0; iterator < production.size(); iterator++)
        {
            if (!visitedProductions[iterator])
            {
                visitedProductions[iterator] = true;
                common.common_LeftSide = production[iterator].production_leftside.produccion_string;
                common.common_Productions.push_back(iterator);

                for (int p = 0; p < production.size(); p++)
                {
                    if (production[iterator].production_leftside.produccion_string == production[p].production_leftside.produccion_string &&
                        (!visitedProductions[p] && (p != iterator)))
                    {
                        visitedProductions[p] = true;
                        common.common_Productions.push_back(p);
                    }
                }
                indx.push_back(common);
                common.common_Productions.clear();
            }
        }
    }

    void readtxt(string _file)
    {
        ifstream archive(_file);
        string current;
        Production prod;

        while (getline(archive, current))
        {
            vector<Production> vectorProduction = prod.readProduction(current);

            for (int i = 0; i < vectorProduction.size(); i++)
            {
                production.push_back(vectorProduction[i]);
            }
        }
        string init;
        cout << "Ingrese el simbolo inicial: ";
        cin >> init;
        cin.ignore();

        for (int iterator = 0; iterator < production.size(); iterator++)
        {
            _non_terminal.push_back(production[iterator].production_leftside);
            if (production[iterator].production_leftside.produccion_string == init)
                this->initial = init;

            auto temp = production[iterator].production_rightside;
            for (int p = 0; p < temp.size(); p++)
            {
                if ((temp[p].type == terminal) && !content<Node>(temp[p], _terminal))
                    _terminal.push_back(temp[p]);
                else if ((temp[p].type == non_terminal) && !content<Node>(temp[p], _non_terminal))
                    _non_terminal.push_back(temp[p]);
            }
        }
        Init();
    }

    void p()
    {
        fstream archivo("frecuencias.txt");
        for (int iterator = 0; iterator < production.size(); iterator++)
        {
            string cadena_Produccion = "";
            cadena_Produccion += "< ";
            cadena_Produccion += production[iterator].production_leftside.produccion_string;
            cadena_Produccion += " > ::= [ ";
            for (int j = 0; j < production[iterator].production_rightside.size(); j++)
            {
                if (production[iterator].production_rightside[j].type == terminal)
                {
                    cadena_Produccion += production[iterator].production_rightside[j].produccion_string;
                }
                else if (production[iterator].production_rightside[j].type != nulltype)
                    cadena_Produccion += production[iterator].production_rightside[j].produccion_string;
                cadena_Produccion += " ";
            }
            cadena_Produccion += "]  \t";
            cadena_Produccion += "Frecuencia: \t";
            cadena_Produccion += to_string(production[iterator].frecuencia);
            cadena_Produccion += "  Probabilidad:\t";
            cadena_Produccion += to_string(production[iterator].prob);
            archivo << production[iterator].frecuencia << endl;
            cout << cadena_Produccion << endl;
        }
    }
};

#endif