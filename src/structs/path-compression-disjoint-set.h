#ifndef PATH_COMPRESSION_DISJOINT_SET
#define PATH_COMPRESSION_DISJOINT_SET

#include <vector>
#include <algorithm>

//A diferencia de los otros, este tiene O(alfa(n)) tiempo amortizado en find y unite,
//donde alfa(n) es la inversa de Ackermann. Aplica heurística union-by-rank tal
//cual detalla el paper en la sección 4.1.
class PathCompressionDisjointSet {
    const int none = -1;
    //p = vector de padres, r = rank, s = size
    std::vector<int> p, r, s;
    std::vector<int> internal_diffs;
public:
    //Creo n conjuntos disjuntos, de 0 a n - 1: {0}, {1}, ... , {n - 1}
    //Pre: n > 0
    //Complejidad temporal: O(n)

    PathCompressionDisjointSet(int n) {
        p.assign(n, none);
        s.assign(n, 1); 
        r.assign(n, 0); // Inicializo ranking 0 para todos los sets
        internal_diffs.assign(n, 0); //No tengo aristas unidas a otro vertice al principio
    }

    //Devuelvo el identificador del conjunto que pertenece i, que es la raiz del árbol.
    //Pre: 0 <= i < s.size
    //Complejidad temporal: O(|i|) = O(n) (peor caso), donde |i| es la distancia hasta la raiz
    //Se hace path compression aquí.
    int find(int i) {
        return p[i] == none ? i : (p[i] = find(p[i]));
    }

    //Uno el conjunto de i con el de j, usando union-by-rank. Actualiza internal_diff con la 
    //arista pasada por parámetro por ser la más pesada del MST.
    //Pre: 0 <= i,j < s.size
    //Complejidad temporal: O(find) = O(n) (peor caso)
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
    //Pre: 0 <= i < s.size
    int size(int i) {
        return s[find(i)];
    }

    //Devuelvo la diferencia interna (aka peso de la última arista agregada al set) del set
    //donde i es raiz
    //Pre: 0 <= i < s.size && i es raíz del set
    int internal_diff(int i) {
        return internal_diffs[find(i)];
    }

};

#endif //PATH_COMPRESSION_DISJOINT_SET
