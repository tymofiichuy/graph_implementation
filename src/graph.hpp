#pragma once

class edge{
public:
    int out;
    int in;
    int weight;
    void redirect();
    void reset_weight();

    bool operator==(edge);
    edge(int = 0, int = 0, int = 0);
};

template<class T> struct node{
    T data;
    node<T>* next = nullptr;
    node<T>* prev = nullptr;

    node<T>(T);
};

class abstract_graph{
protected:
    int size = 0;
    node<edge>* edges = nullptr;
    node<int>* vertices = nullptr;
public:
    virtual void add_vertex(int) = 0;
    virtual void add_edge(edge) = 0;
    virtual void delete_vertex(int) = 0;
    virtual void delete_edge(edge) = 0;

    virtual void random_graph(int, int, int) = 0;
    virtual int* to_matrix() = 0;
};

class directed_weighted_graph : public abstract_graph{
public:
    node<int>* vertex_search(int);
    node<edge>* edge_search(edge);

    void add_vertex(int);
    void add_edge(edge);
    void delete_vertex(int);
    void delete_edge(edge);

    void random_graph(int, int, int);
    int* to_matrix();

    directed_weighted_graph(int = 0);
    ~directed_weighted_graph();
};

class undirected_weighted_graph : public virtual directed_weighted_graph{
public:
    void delete_edge(edge);
    void add_edge(edge);
    void random_graph(int, int, int);

    undirected_weighted_graph(int = 0);
    ~undirected_weighted_graph();
};

class directed_unweighted_graph : public virtual directed_weighted_graph{
public:
    void add_edge(edge);

    directed_unweighted_graph(int = 0);
    ~directed_unweighted_graph();
};

class undirected_unweighted_graph : public undirected_weighted_graph{
public:  
    void add_edge(edge);

    undirected_unweighted_graph(int = 0);
    ~undirected_unweighted_graph();
};