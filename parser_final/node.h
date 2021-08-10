#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

using namespace std;

enum T{terminal, non_terminal , initial , punto , nulltype}; 

class Node{
    public:
        string produccion_string;
        T type;

        Node() = default;

        Node(string element_of_grammar , T type){
            this -> produccion_string = element_of_grammar;
            this -> type = type;
        }

        vector<Node> readNode(string& text, int start_cad_text ,int end_cad_text ){
            
            bool flag = false;
            bool no_terminal;
            Node node;
            vector<Node> vectorNodeList;
            string cadena = "";

            for(int iterator = start_cad_text ; iterator<=end_cad_text ; iterator++){
                if(text[iterator] != ' '){
                    if(text[iterator] == '<'){
                        flag = true;
                        no_terminal = true;
                    }

                    else if(text[iterator] == '\"' && !flag){
                        flag = true;
                        no_terminal = false;
                    }

                    else if(flag && ((text[iterator] == '>')||(text[iterator] == '\"'))){
                        flag = false;
                        if(no_terminal){
                            node.produccion_string = cadena;
                            node.type = non_terminal;
                        }
                        else{
                            node.produccion_string = cadena;
                            node.type = terminal;
                        }
                        vectorNodeList.push_back(node);
                        cadena = "";
                    }
                    else if(flag){
                        cadena += text[iterator];
                    }
                }
            }
            return vectorNodeList;
        }

        bool operator ==(const Node &t) const{
            if(( this->type == t.type) && (this->produccion_string == t.produccion_string))
                 return true;
            return false;
        }

        friend ostream &operator<<( ostream &output, const Node &D )
        { 
            output << D.produccion_string <<" " << D.type;
            return output;             
        }

};

#endif 