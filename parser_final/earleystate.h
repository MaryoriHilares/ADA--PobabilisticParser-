#ifndef EARLEY_STATE_H
#define EARLEY_STATE_H
#include <iostream>
#include <vector> 
#include <string>
#include <vector>
#include "node.h"

using namespace std;

class EarleyState{
    public:
        Node earley_state_left;
        vector<Node> earley_state_right;
        int position_point;
        int reference_1;
        int reference_2;

        EarleyState() = default;

        EarleyState(Node earley_state_left , vector<Node> earley_state_right){
            this -> earley_state_left = earley_state_left;
            this -> earley_state_right = earley_state_right;
        }
        EarleyState(Node earley_state_left , vector<Node> earley_state_right,int position_point){
            this -> earley_state_left = earley_state_left;
            this -> earley_state_right = earley_state_right;
            Node p{".",punto};
            this-> earley_state_right.insert(this->earley_state_right.begin() + position_point, p);
        }
        

        bool complete_finished(){
            if((position_point == earley_state_right.size()-1) && earley_state_right[position_point].type==punto)
                return true;
            return false;
        }

        Node next(){
            Node node;
            if(earley_state_right[position_point].type == punto){
                node = earley_state_right[position_point+1];
            }
            return node;
        }

        void simulation_move_point(){
            Node current = earley_state_right[position_point];
            earley_state_right[position_point] = earley_state_right[position_point+1];
            earley_state_right[position_point+1] = current;

            position_point++;
        }

        bool operator==(const EarleyState& o)const{
            if (this->earley_state_right == o.earley_state_right && this->earley_state_left == o.earley_state_left)
                return true;
           return false;
        }
            
        friend ostream &operator<<( ostream &output, const EarleyState &D )
        { 
            for(int i = 0; i < D.earley_state_right.size(); i++){
                output << D.earley_state_left << D.earley_state_right[i];
                return output; 
            }                   
        }
};

#endif
