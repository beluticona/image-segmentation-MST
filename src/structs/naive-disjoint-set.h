#ifndef NAIVE_DISJOINT_SET
#define NAIVE_DISJOINT_SET

#include <vector>

#define INF 0

class NaiveDisjointSet {
    //s = set.
    std::vector<int> s;
    std::vector<int> tam;
    std::vector<int> internal_diffs; //exclusivo para la segmentation
public:
    //Creo n conjuntos disjuntos, de 0 a n - 1: {0}, {1}, ... , {n - 1}
    //Pre: n > 0
    //Complejidad temporal: O(n)
    NaiveDisjointSet(int n) {
        for(int i = 0; i < n; ++i)
            s.push_back(i);
        tam.assign(n,1);
        internal_diffs.assign(n, INF); //No tengo aristas unidas a otro vertice al principio
    }
    //Devuelvo el identificador del conjunto que pertenece i.
    //Pre: 0 <= i < s.size
    //Complejidad temporal: O(1)
    int find(int i) {
        return s[i];
    }
    //Uno el conjunto de i con el de j. Toda aparición del conjunto j lo cambio
    //por el conjunto i.
    //Pre: 0 <= i,j < s.size
    //Complejidad temporal: O(n)
    void unite(int i, int j, int new_edge) {
        using std::swap;
        i = find(i); j = find(j);
        if(i != j){
        	internal_diffs[i] = std::max(internal_diffs[i],std::max(internal_diffs[j],new_edge));
            for(int h = 0; h < s.size(); ++h)
                if(s[h] == j) {
                    s[h] = i;
                    tam[i]++;
                }
            for(int h = 0; h < s.size(); ++h)
                if(s[h] == i){
                    tam[h] = tam[i];
                    internal_diffs[h] = internal_diffs[i];
                }
        }
    }

    //Devuelvo el tamaño del conjunto en el que esta i
    int size(int i){
        return tam[i];
    }
    //Retorna la minima diferencia interna del set donde pertenece i por medio de su representante
    //Pre: 0 <= i < s.size
    //Complejidad temporal: O(1)
    int internal_diff(int i){
        return internal_diffs[find(i)];
    }
};

#endif //NAIVE_DISJOINT_SET
