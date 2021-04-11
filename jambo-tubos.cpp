#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <set>
#include <map>
using namespace std;

struct jambo_elemento{
    int peso;
    int res;
};

int cant_parcial;
int res_parcial;

/***
Algoritmo de fuerza bruta.

Parametros:
  - vector<jambo_elemento> jambo_elementos: Vector de jambo_elementos fijo con los elementos desde 0 hasta n.
  - vector<jambo_elemento> jambo_vec_parc: Vector de jambo_elementos con los elementos desde 0 hasta i.
  - int i: indice del primer elemento de la cinta a ser considerado. 
  - int R: maxima resistencia del jambo-tubo.

Returns:
  - int: Maxima cantidad posible de elementos en la cinta
***/
int BruteForce(vector<jambo_elemento> jambo_elementos,vector<jambo_elemento> jambo_vec_parc, int i, int R){
    if (i == jambo_elementos.size())
    {
        //Proceso las hojas del arbol de fuerza bruta
        int n = jambo_vec_parc.size();

        // Si llego a una hoja sin tener elementos es que estaba vacio mi vector
        if (n == 0) return 0;

        printf("Iniciando nuevo procesar");
        int suma_pesos = jambo_vec_parc[n-1].peso;

        for (int j = n-1; j >= 0 ; j--)
        {
            printf("Suma Pesos : %d, \n", suma_pesos);
            if ((j < n-1) && (suma_pesos > jambo_vec_parc[j].res || suma_pesos + jambo_vec_parc[j].peso > R))
            {
                cant_parcial = 0;
                return 0;
            }
            else
            {
               suma_pesos += jambo_vec_parc[j].peso;
               cant_parcial++;
            }
        }    

        if (cant_parcial > res_parcial)
        {
            res_parcial = cant_parcial;
            cant_parcial = 0;
        }

        return res_parcial;
    }
    else
    {
        int res_p1 = BruteForce(jambo_elementos, jambo_vec_parc, i+1, R);

        jambo_vec_parc.push_back(jambo_elementos[i]);
        int res_p2 = BruteForce(jambo_elementos, jambo_vec_parc, i+1, R);
        jambo_vec_parc.pop_back();

        return max(res_p1, res_p2);
    }
}

int main(int argc, char** argv){

    printf("Starting program of jambo-tubos\n");

    vector<jambo_elemento> jambo_elementos;
    int n;
    int R;
    int peso;
    int res;
    
    // Leemos el parametro que indica el algoritmo a ejecutar.
    map<string, string> algoritmos_implementados = {
        {"BF", "Fuerza Bruta"}, {"BT-0", "Backtracking con podas"}, {"BT-F", "Backtracking con poda por factibilidad"}, 
        {"BT-O", "Backtracking con poda por optimalidad"}, {"DP", "Programacion dinámica"}
    };

    // Verificar que el algoritmo pedido exista.
    if (argc < 2 || algoritmos_implementados.find(argv[1]) == algoritmos_implementados.end())
    {
        cerr << "Algoritmo no encontrado: " << argv[1] << endl;
        cerr << "Los algoritmos existentes son: " << endl;
        for (auto& alg_desc: algoritmos_implementados) cerr << "\t- " << alg_desc.first << ": " << alg_desc.second << endl;
        return 0;
    }
    string algoritmo = argv[1];

    // Leemos el input.
    cin >> n >> R;

    jambo_elementos.assign(n,{});

    for (int i = 0; i < n; ++i) 
    {
        cin >> jambo_elementos[i].peso >> jambo_elementos[i].res;
    }

    // Ejecutamos el algoritmo y obtenemos su tiempo de ejecución.
    int maxCant = -1;

    auto start = chrono::steady_clock::now();
    if (algoritmo == "BF")
    {
        printf("Ejecutando algoritmo de fuerza bruta:\n");

        vector<jambo_elemento> jambo_vec_parc;
        jambo_vec_parc.assign(0,{});

        cant_parcial = 0;
        res_parcial = 0;

        maxCant = BruteForce(jambo_elementos, jambo_vec_parc, 0, R);
    }
    else if (algoritmo == "BT-0")
    {

    }
    else if (algoritmo == "BT-F")
    {

    }
    else if (algoritmo == "BT-O")
    {

    }
    else if (algoritmo == "DP")
    {
        // Precomputamos la solucion para los estados.

        // Obtenemos la solucion optima.
    }
    auto end = chrono::steady_clock::now();
    double total_time = chrono::duration<double, milli>(end - start).count();

    // Imprimimos el resultado por stdout.
    cout << "Resultado de la ejecucion: " << maxCant << endl;

    // Imprimimos el tiempo de ejecución por stderr.
    clog << "Tiempo de ejecucion: " << total_time << endl;
    
    return 0;
}
