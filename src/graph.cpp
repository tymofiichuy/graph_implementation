#include <iostream>
#include "graph.hpp"

using namespace std;

bool edge::operator==(edge cmp){
    return(out == cmp.out && in == cmp.in && weight == cmp.weight);
};

void edge::redirect(){
    int tmp = in;
    in = out;
    out = tmp;
}

void edge::reset_weight(){
    weight = 1;
}

edge::edge(int o, int i, int w){
    out = o;
    in = i;
    weight = w;
}

node<int>::node(int i){
    data = i;
}

node<edge>::node(edge e){
    data = e;
}

node<int>* directed_weighted_graph::vertex_search(int v){
    if (vertices == nullptr){
        return nullptr;
    }

    node<int>* temp = vertices;
    while (temp){
        if (temp->data == v){
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

void directed_weighted_graph::add_vertex(int v){
    if (!vertex_search(v)){
        node<int>* tmp = new node<int>(v);
        size++;
        if (vertices == nullptr){
            vertices = tmp;
        }
        else{
            tmp->next = vertices;
            vertices->prev = tmp;
            vertices = tmp;
        }
    }
}

directed_weighted_graph::directed_weighted_graph(int size){
    for (int i = 1; i <= size; i++){
        add_vertex(i);
    }
}

void directed_weighted_graph::delete_vertex(int v){
    node<int>* tmp = vertex_search(v);
    if(tmp){
        size--;
        if (tmp == vertices){
            vertices = tmp->next;
            if(vertices){
                vertices->prev = nullptr;  
            }
            delete tmp;
        }
        else{
            tmp->prev->next = tmp->next;
            if (tmp->next){
                tmp->next->prev = tmp->prev;  
            }
            delete tmp;  
        }        
    }
    else{
        throw invalid_argument("Nothing to delete");
    }
}

directed_weighted_graph::~directed_weighted_graph(){
    while(vertices){
        delete_vertex(vertices->data);
    }
}

node<edge>* directed_weighted_graph::edge_search(edge e){
    if (edges == nullptr){
        return nullptr;
    }

    node<edge>* temp = edges;
    while (temp){
        if (temp->data == e){
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

void directed_weighted_graph::add_edge(edge e){
    if (!edge_search(e)){
        node<edge>* tmp = new node<edge>(e);
        if (edges == nullptr){
            edges = tmp;
        }
        else{
            tmp->next = edges;
            edges->prev = tmp;
            edges = tmp;
        }
    }
}

void directed_weighted_graph::delete_edge(edge e){
    node<edge>* tmp = edge_search(e);
    if (tmp){
        if (tmp == edges){
            edges = tmp->next;
            if(edges){
                edges->prev = nullptr;  
            }
            delete tmp;
        }
        else{
            tmp->prev->next = tmp->next;
            if (tmp->next){
                tmp->next->prev = tmp->prev;  
            }
            delete tmp;  
        }        
    }
    else{
        throw invalid_argument("Nothing to delete");
    }   
}

int* directed_weighted_graph::to_matrix(){
    int* matrix = new int[size*size];
    for(int i = 0; i < size*size; i++){
        matrix[i] = 0;
    }
    node<edge>* tmp = edges;
    while(tmp){
        matrix[size*(tmp->data.out - 1) + (tmp->data.in - 1)] = tmp->data.weight;
        tmp = tmp->next;
    }

    return matrix;
}

void undirected_weighted_graph::delete_edge(edge e){
    bool flag = true;
    node<edge>* tmp = edge_search(e);
    if (tmp){
        if (tmp == edges){
            edges = tmp->next;
            if(edges){
                edges->prev = nullptr;  
            }
            delete tmp;
        }
        else{
            tmp->prev->next = tmp->next;
            if (tmp->next){
                tmp->next->prev = tmp->prev;  
            }
            delete tmp;  
        }        
    }
    else{
        flag = false;
    }
    if(flag){
        e.redirect();
        delete_edge(e);        
    } 
}

void undirected_weighted_graph::add_edge(edge e){
    if (!edge_search(e)){
        size = size+2;
        node<edge>* tmp1 = new node<edge>(e);
        e.redirect();
        node<edge>* tmp2 = new node<edge>(e);
        if (edges == nullptr){
            tmp1->next = tmp2;
            tmp2->prev = tmp1;
            edges = tmp1;
        }
        else{
            tmp1->next = tmp2;
            tmp2->next = edges;
            tmp2->prev = tmp1;
            edges->prev = tmp2;
            edges = tmp1;
        }
    }
}

undirected_weighted_graph::undirected_weighted_graph(int size){
    directed_weighted_graph::directed_weighted_graph(size);
}

undirected_weighted_graph::~undirected_weighted_graph(){
    directed_weighted_graph::~directed_weighted_graph();
}

void directed_unweighted_graph::add_edge(edge e){
    e.reset_weight();
    directed_weighted_graph::add_edge(e);
}

directed_unweighted_graph::directed_unweighted_graph(int size){
    directed_weighted_graph::directed_weighted_graph(size);
}

directed_unweighted_graph::~directed_unweighted_graph(){
    directed_weighted_graph::~directed_weighted_graph();
}

void undirected_unweighted_graph::add_edge(edge e){
    e.reset_weight();
    undirected_weighted_graph::add_edge(e);
}

undirected_unweighted_graph::undirected_unweighted_graph(int size){
    directed_weighted_graph::directed_weighted_graph(size);
}

undirected_unweighted_graph::~undirected_unweighted_graph(){
    directed_weighted_graph::~directed_weighted_graph();
}