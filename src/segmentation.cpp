#include <iostream>
#include <vector>
#include <algorithm>
#include "structs/disjoint-set.h"
#define Trabajo using
#define Practico namespace
#define II std;

Trabajo Practico II

//Global vertices, edges, ancho y altura
int w, h, n, m;
vector<int> vertices;
int threshold_constant = 5; //parámetro para cota de la diferencia interna de los segmentos

struct Edge {
    int src, dst, weight;
    Edge(int src, int dst) : src(src), dst(dst), weight(abs(vertices[dst]-vertices[src])) {}
    bool  operator==(const Edge e){ //Puede que no lo necesite pero just in case falta a==b or b==a
        return (weight == e.weight && ((src == e.src && dst == e.dst)
         || (src == e.dst && dst == e.src)));
    }
    bool operator<(const Edge e){
        return weight < e.weight;
    }

};
vector<Edge> edges;

void createEdges(){
    int t;
    for (int i = 0; i < h-1; ++i){
        for (t = i*w; t < i*w+w-1; ++t){
            edges.push_back(Edge(t,t+1));
            edges.push_back(Edge(t,t+w));
            edges.push_back(Edge(t,t+w+1));
            //Si es el primero de la fila de pixeles, no deberia generarse este.
            if (t> i*w) edges.push_back(Edge(t,t+w-1));
        }
        edges.push_back(Edge(t,t+w));
        edges.push_back(Edge(t,t+w-1));
    }
    while(t<n-1){
        edges.push_back(Edge(t,t+1));
        t++;
    }
    m = edges.size();
}



void segmentation(){
    sort(edges.begin(), edges.end()); //Ordeno aristas según peso
    DisjointSet ds(n); //Creo sets
    int internal_diff_src, internal_diff_dst;
    int find_src, find_dst;
    for (int i = 0; i < m; ++i){ //Recorro todas las aristas
        Edge e = edges[i]; //Tomo i-ésima arista mínima
        find_src = ds.find(e.src);find_dst = ds.find(e.dst); //Calculo finds solo dos veces
        //Si son de componentes distintas
        if (find_src != find_dst) {
            //Calculo diferencia interna de las 2 componentes + threshold
            internal_diff_dst = ds.internal_diff(find_dst) + threshold_constant / (ds.size(find_dst));
            internal_diff_src = ds.internal_diff(find_src) + threshold_constant / (ds.size(find_src));
            //El peso de la arista es menor a ambas diferencias internas, union
            if (e.weight <= min(internal_diff_dst, internal_diff_src)) {
                ds.unite(find_src, find_dst, e.weight);
            }
        }
    }
    //Actualizo en los vértices el conjunto al que pertenece cada píxel
    for (int i = 0; i < n; ++i){
        vertices[i] = ds.find(i); 
    }

}

int main() {
    //Lectura de Datos
    cin >> w >> h;
    n = w*h;
    vertices.reserve(n);
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j){
            cin >> vertices[i*w+j];
        }
    }
    //Se crean ejes para cada píxel con sus aledaños
    createEdges();
    //Se segmenta la imagen
    segmentation();
    //Escritura de conjuntos para cada píxel
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j){
            cout << vertices[i*w+j] << " ";
        }
        cout << endl;
    }
    return 0;
}
