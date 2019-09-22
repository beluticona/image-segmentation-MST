#ifndef DISJOINT_SET
#define DISJOINT_SET

#include <vector>
#include <algorithm>

//En esta se usa la heurística union-by-rank.
class DisjointSet {
    const int none = -1;
    //p = vector de padres, r = rank, s = size
    std::vector<int> p, r, s;
    std::vector<int> internal_diffs;
public:
    //Creo n conjuntos disjuntos, de 0 a n - 1: {0}, {1}, ... , {n - 1}
    //Pre: n > 0
    //Complejidad temporal: O(n)
    DisjointSet(int n) {
        p.assign(n, none);
        s.assign(n, 1);
        r.assign(n, 0);
        internal_diffs.assign(n, 0); //No tengo aristas unidas a otro vertice al principio
    }

    //Devuelvo el identificador del conjunto que pertenece i, que es la raiz del árbol.
    //Pre: 0 <= i < s.size
    //Complejidad temporal: O(|i|) = O(n), donde |i| es la distancia hasta la raiz.
    int find(int i) {
        while (p[i] != none)
            i = p[i];
        return i;
    }

    //Uno el conjunto de i con el de j, usando union-by-rank.
    //Pre: 0 <= i,j < s.size
    //Complejidad temporal: O(n)
    void unite(int i, int j, int new_edge) {
        i = find(i);
        j = find(j);
        if(i == j)
            return;
        if(r[i]<r[j]){
            p[i] = j;
            s[j]+=s[i];
            internal_diffs[j] = std::max(internal_diffs[j],std::max(internal_diffs[i],new_edge));
        }else if(r[i]>r[j]){
            p[j] = i;
            s[i]+=s[j];
            internal_diffs[i] = std::max(internal_diffs[j],std::max(internal_diffs[i],new_edge));
        }else{
            p[i] = j;
            r[j] += 1;
            s[j] += s[i];
            internal_diffs[j] = std::max(internal_diffs[j],std::max(internal_diffs[i],new_edge));
        }

    }

    //Devuelvo el tamaño del conjunto en el que esta i
    int size(int i) {
        return s[find(i)];
    }

    int internal_diff(int i) {
        return internal_diffs[find(i)];
    }
};

#endif //DISJOINT_SET
