#include<random>
#include "graph.hpp"

using namespace std;

void directed_weighted_graph::random_graph(int probability, int min_weight, int max_weight){
    random_device rd;
    mt19937 mt (rd());
    uniform_int_distribution<int> dist_w (min_weight, max_weight);
    uniform_int_distribution<int> dist_e (1, 100);

    node<int>* tmp_i = vertices;
    node<int>* tmp_j = vertices;
    while(tmp_i){
        while(tmp_j){
            int check = dist_e(mt);
            if (check <= probability){
                int w = dist_w(mt);
                edge e(tmp_i->data, tmp_j->data, w);
                add_edge(e);
            }
        tmp_j = tmp_j->next;
        }
        tmp_j = vertices;
    tmp_i = tmp_i->next;    
    }
}

void undirected_weighted_graph::random_graph(int probability, int min_weight, int max_weight){
    random_device rd;
    mt19937 mt (rd());
    uniform_int_distribution<int> dist_w (min_weight, max_weight);
    uniform_int_distribution<int> dist_e (1, 100);

    node<int>* tmp_i = vertices;
    node<int>* tmp_j = vertices;
    while(tmp_i){
        while(tmp_j){
            int check = dist_e(mt);
            if (check <= probability){
                int w = dist_w(mt);
                edge e(tmp_i->data, tmp_j->data, w);
                add_edge(e);
            }
        tmp_j = tmp_j->next;
        }
    tmp_i = tmp_i->next;
    tmp_j = tmp_i;    
    }
}