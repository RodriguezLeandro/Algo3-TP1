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
int maxCant = -1;
vector<vector<int>> memoizacion;

/***
Algoritmo de fuerza bruta.

Parametros:
  - vector<jambo_elemento> jambo_elementos: Vector de jambo_elementos fijo con los elementos desde 0 hasta n.
  - int i: indice del primer elemento de la cinta a ser considerado. 
  - int R: maxima resistencia del jambo-tubo.

Returns:
  - int: Maxima cantidad posible de elementos en la cinta
***/
int BruteForce(vector<jambo_elemento> &jambo_elementos, int i, int R){
    if (i == jambo_elementos.size()){
        return R >= 0 ? cant_parcial : 0;
    }
    else {
        int res_p1 = BruteForce(jambo_elementos, i+1, R);
        cant_parcial++;
        int res_p2 = BruteForce(jambo_elementos, i+1, min(jambo_elementos[i].res, R - jambo_elementos[i].peso));
        cant_parcial--;
        return max(res_p1, res_p2);
    }
}

int Backtracking_pro(vector<jambo_elemento> &jambo_elementos, int i, int R,int cant){
    if(R<0){                                    // poda por factibilidad
        return  -9999;

    }    
    if(i==jambo_elementos.size()){              // caso base
        return 0;
    }
    
    if (cant > maxCant){                       // actualizo el maximo
        maxCant=cant;
    }
    if(cant+(jambo_elementos.size()-i)<maxCant){        // poda por optimalidad
        return -9999;
    }
    int no_agrego;
    int agrego;
    
    no_agrego=Backtracking_pro(jambo_elementos,i+1,R,cant);
    agrego=1+Backtracking_pro(jambo_elementos,i+1,min(R-jambo_elementos[i].peso,jambo_elementos[i].res),cant+1);
    
    return max(agrego,no_agrego);     
        
}


int Backtracking_f(vector<jambo_elemento> &jambo_elementos, int i, int R,int cant){
    if(R<0){                            // poda por factibilidad
        return  -9999;

    }    
    if(i==jambo_elementos.size()){       // caso base
        return 0;
    }
    int agrego;
    int no_agrego;
    agrego=Backtracking_f(jambo_elementos,i+1,min(R-jambo_elementos[i].peso,jambo_elementos[i].res),cant+1)+1;
    no_agrego=Backtracking_f(jambo_elementos,i+1,R,cant);
    return max(agrego,no_agrego);     
        
}

int Backtracking_op(vector<jambo_elemento> &jambo_elementos, int i, int R){
    if (cant_parcial+((int)jambo_elementos.size()-i)<maxCant){
        return 0;
    }
    if (i == jambo_elementos.size()){
        if (R < 0){
            return 0;
        }
        if (cant_parcial > maxCant){
            maxCant = cant_parcial;
        }
        return cant_parcial;
    }
    else {
        int res_p1 = Backtracking_op(jambo_elementos, i+1, R);
        cant_parcial++;
        int res_p2 = Backtracking_op(jambo_elementos, i+1, min(jambo_elementos[i].res, R - jambo_elementos[i].peso));
        cant_parcial--;
        return max(res_p1, res_p2);
    }
}

int pd(vector<jambo_elemento> &jambo_elementos, int i, int R){
    if(R<0){
        return -9999;
    }
    if(i==jambo_elementos.size()){
        return 0;
    }
    if (memoizacion[i][R]==-1){
        
        int agrego = pd(jambo_elementos,i+1,min(R-jambo_elementos[i].peso,jambo_elementos[i].res))+1;
        int no_agrego = pd(jambo_elementos,i+1,R);

        memoizacion[i][R]=max(no_agrego,agrego);
        
    }
    
    return memoizacion[i][R];     
}

int main(int argc, char** argv){

    printf("Starting program of jambo-tubos\n");

    vector<jambo_elemento> jambo_elementos;
    

    int peso;
    int res;
    int R;
    int n;
    
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
    // int maxCant = -1;

    auto start = chrono::steady_clock::now();
    if (algoritmo == "BF")
    {
        printf("Ejecutando algoritmo de fuerza bruta:\n");

        cant_parcial = 0;
        maxCant = BruteForce(jambo_elementos, 0, R);
    }
    // 
    //    codigo Backtracking con todas las podas
    //
    else if (algoritmo == "BT-0")
    {

        printf("Ejecutando algoritmo de Backtracking con todas las podas:\n");

        
        maxCant = Backtracking_pro(jambo_elementos, 0, R, 0);

    }
    // 
    //    codigo Backtracking con la poda por optimalidad
    //
    
    else if (algoritmo == "BT-O")
    {
        printf("Ejecutando algoritmo de Backtracking con solo poda de optimalidad:\n");

        cant_parcial = 0;
        maxCant = Backtracking_op(jambo_elementos, 0, R);

    }

    // 
    //    codigo Backtracking con la poda por factibilidad
    //

    else if (algoritmo == "BT-F")
    {

        printf("Ejecutando algoritmo de Backtracking con solo poda de factibilidad:\n");

        
        maxCant = Backtracking_f(jambo_elementos, 0, R, 0);


    }

    // 
    //    codigo PROGRAMACION DINAMICA
    //

    else if (algoritmo == "DP"){
    
    // Precomputamos la solucion para los estados.
        
    
    //vector<vector<int>> memoizacion;

    
    memoizacion = vector<vector<int>>(n+1, vector<int>(R+1, -1));
    //memoizacion.assign(n,R,{});



  //  std::fill(*memoizacion, *memoizacion + n*7000, -1); //relleno con -1 la estructura

      //int ** m; 

      /*
      int * m;
      m=&memoizacion;
      */
      
        // Obtenemos la solucion optima.

        printf("Ejecutando algoritmo de programacion dinamica:\n");

        
      
        maxCant = pd(jambo_elementos, 0, R);
    }

    auto end = chrono::steady_clock::now();
    double total_time = chrono::duration<double, milli>(end - start).count();

    // Imprimimos el resultado por stdout.
    cout << "Resultado de la ejecucion: " << maxCant << endl;

    cout << "Tiempo de ejecucion: " << endl;
    // Imprimimos el tiempo de ejecución por stderr.
    clog << total_time << endl;
    
    return 0;
}
