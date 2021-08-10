#ifndef EARLEY_PARSER_H
#define EARLEY_PARSER_H

#include "node.h"
#include <string>
#include <vector>
#include <fstream>
#include <list>
#include <algorithm>
#include "gramatica.h"
#include "chart.h"
#include "producciones.h"
#include "gramatica.h"
#include "earleystate.h"
#include "arch_aux.h"

using namespace std;

EarleyState StartStateSimulation(string S)
{
    Node leftSide{"TOP", non_terminal};
    vector<Node> rightSide;
    Node n{S, non_terminal};
    rightSide.push_back(n);

    EarleyState StartStateSimulation{leftSide, rightSide, 0};
    StartStateSimulation.reference_1 = 0;
    StartStateSimulation.reference_2 = 0;
    StartStateSimulation.position_point = 0;

    return StartStateSimulation;
}

class EarleyParser
{
public:
    Gramatica grammar;
    string text;
    vector<string> vector_cad;
    Chart chart;

    EarleyParser() = default;

    EarleyParser(Gramatica g, string text)
    {
        this->text = text;
        grammar = g;
    }

    EarleyParser(string text)
    {
        cout << text << endl;
        grammar.readtxt(text);
    }
    
    float frecuenciaTotal(string derecha){
        float total = 0;
        for (int i = 0; i < grammar.production.size(); i++)
        {
            if(grammar.production[i].production_leftside.produccion_string==derecha){
                total+=grammar.production[i].frecuencia;
            }
        }
        return total;
    }
    
    void hacerProb()
    {
        for (int i = 0; i < grammar.production.size(); i++)
        {
            float totalAbs=frecuenciaTotal(grammar.production[i].production_leftside.produccion_string);
            float proba= grammar.production[i].frecuencia/totalAbs;
            grammar.production[i].prob=grammar.production[i].frecuencia/totalAbs;
            if(grammar.production[i].frecuencia == 0){
                grammar.production[i].prob=0;
            }
       }
    }

 
    void printProb(){
        
        hacerProb();
        this->grammar.p();
    }
    void leerFreq(string _file)
    {
        fstream archive(_file);
        string current;
        int freq;
        float freq1;
        int i = 0, j = 0;
        for (int iterator = 0; iterator < grammar.production.size(); iterator++)
            {
                getline(archive, current);
                string a=current;
                freq = atoi(a.c_str());
                grammar.production[iterator].frecuencia=freq;
            }
    }

    void PREDICTOR(EarleyState predictor)
    {
        int pos_i = predictor.reference_2;
        Node node = predictor.next();
        EarleyState current;

        for (int i = 0; i < grammar.indx.size(); i++)
        {
            if (grammar.indx[i].common_LeftSide == node.produccion_string)
            {
                for (int p = 0; p < grammar.indx[i].common_Productions.size(); p++)
                {
                    current = grammar.production[grammar.indx[i].common_Productions[p]].convertToState(0);
                    current.reference_1 = pos_i;
                    current.reference_2 = pos_i;

                    if (!content<EarleyState>(current, chart.vector_chart[pos_i]))
                        chart.vector_chart[pos_i].push_back(current);
                }
                break;
            }
        }
    }
    void incrementar(string left, string right){
        for(int i = 0; i < grammar.production.size(); i++){
            if(grammar.production[i].production_leftside.produccion_string==left){
                string temp;
                for(int j = 0; j < grammar.production[i].production_rightside.size();j++){
                    temp += grammar.production[i].production_rightside[j].produccion_string;
                }
                 if(temp==right){
                       grammar.production[i].frecuencia++;
                 }
            }

        }
    }
    void ActualizarFrec(){
        string left;
        vector<string> puntitos;
        for(int i = 0; i <chart.vector_chart.size(); i++){
                string right;
                for(int j = 0; j <chart.vector_chart[i].size(); j++){
                    
                    left= chart.vector_chart[i][j].earley_state_left.produccion_string;
                    for(int k = 0; k <chart.vector_chart[i][j].earley_state_right.size(); k++){
                       if (chart.vector_chart[i][j].earley_state_right[k].type != nulltype &&
                          chart.vector_chart[i][j].earley_state_right[k].type != punto){
                           right += chart.vector_chart[i][j].earley_state_right[k].produccion_string;
                       }     
                    }
                    if(chart.vector_chart[i][j].earley_state_right[chart.vector_chart[i][j].earley_state_right.size()-1].type == punto){
                           puntitos.push_back(right);
                    }
                    incrementar(left, right);
                    right="";
                }
        }
        for(int m=0;m< grammar.production.size(); m++){
               string c;
               bool present=false;
               for(int n=0; n <grammar.production[m].production_rightside.size(); n++){
                     c+=grammar.production[m].production_rightside[n].produccion_string;
               }
               for(int k=0;k<puntitos.size(); k++){
                 if(puntitos[k]==c){
                     present=true;
                 }
               }
               if(present==false){
                   grammar.production[m].frecuencia=0;
               }
               else grammar.production[m].frecuencia--;
               c="";
        }
    }

    void SCANNER(EarleyState scanner)
    {   
        EarleyState current = scanner;
        int pos_i = current.reference_2;
        Node node = current.next();

        Production prod;
        prod.production_leftside = node;

        Node current_nodo{vector_cad[pos_i], terminal};
        vector<Node> vector_current;
        vector_current.push_back(current_nodo);
        prod.production_rightside = vector_current;

        if ((content<Production>(prod, this->grammar.production)) ||
            (node.type == terminal && node.produccion_string == vector_cad[pos_i]))
        {
            current.simulation_move_point();
            current.reference_1 = pos_i;
            current.reference_2 = pos_i + 1;
            chart.vector_chart[pos_i + 1].push_back(current);
        }
    }

    void COMPLETER(EarleyState completer)
    {
        EarleyState current;
        int index;
        vector<EarleyState> temp = chart.vector_chart[completer.reference_1];
        string grammar_left_side = completer.earley_state_left.produccion_string;

        for (int i = 0; i < temp.size(); i++)
        {
            current = temp[i];
            index = current.position_point + 1;

            if (current.earley_state_right.size() > index && current.earley_state_right[index].produccion_string == grammar_left_side)
            {
                current.simulation_move_point();
                current.reference_2 = completer.reference_2;

                if (!content<EarleyState>(current, chart.vector_chart[completer.reference_2]))
                {
                    chart.vector_chart[completer.reference_2].push_back(current);
                }
            }
        }
    }

    void input()
    {
        cout << " Cadena a analizar: ";
        getline(cin, this->text);
        string cad_entrada = "";
        for (int i = 0; i < text.size(); i++)
        {
            if (text[i] != ' ')
            {
                cad_entrada += text[i];
            }

            else if (cad_entrada != "")
            {
                vector_cad.push_back(cad_entrada);
                cad_entrada = "";
            }
        }
        if (cad_entrada != "")
        {
                vector_cad.push_back(cad_entrada);
                cad_entrada = "";
        }
        chart.insetChart(vector_cad.size());
    }

    bool EarleyParser_()
    {
        EarleyState temp_StateS = StartStateSimulation(this->grammar.initial);
        chart.vector_chart[0].push_back(temp_StateS);
        EarleyState TempSS_change = temp_StateS;
        TempSS_change.simulation_move_point();
         

        for (int i = 0; i < vector_cad.size() + 1; i++) //
        {
            for (int j = 0; j < chart.vector_chart[i].size(); j++)
            {
                if(content<EarleyState>(TempSS_change, chart.vector_chart[chart.vector_chart.size()-1])){
                    vector_cad.clear();
                    return true;
                }
                if (!chart.vector_chart[i][j].complete_finished())
                {
                    if (chart.vector_chart[i][j].next().type == non_terminal)
                    {
                        PREDICTOR(chart.vector_chart[i][j]);
                    }

                    else if (chart.vector_chart[i][j].next().type == terminal)
                    {
                        SCANNER(chart.vector_chart[i][j]);
                    }
                }

                else{
                    COMPLETER(chart.vector_chart[i][j]);
                }      
            }
        }
        vector_cad.clear();
        return false;
    }

};

#endif