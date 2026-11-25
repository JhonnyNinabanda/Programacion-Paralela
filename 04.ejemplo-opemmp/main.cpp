#include <fmt/core.h>
#include <omp.h>
#include <vector>
#include <fmt/ranges.h>
#include <map>
#include <algorithm>

int main(int argsc, char** argv){

    //########################################################################################
    fmt::print("------- Region paralela con OpenMP --------\n");

    //Definimos la region paralela, donde cada hilo ejecutara el mismo codigo
    #pragma omp parallel
    {
        int thread_count = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        fmt::print(" Goodbye, serial world, hello OpenMP!\n");
        fmt::print(" I have {} thread(s) and my thread_id is {}", thread_count, thread_id);
    }

    //########################################################################################
    fmt::print("\n-------------- Region paralela threads = 2");

    //controlamos el numero de hilos que se van a crear en la region paralela
     #pragma omp parallel num_threads(2)
    {
        int thread_count = omp_get_num_threads();
        int thread_id = omp_get_thread_num();

        fmt::print("\nI have {} thread(s) and my thread_id is {}", thread_count, thread_id);
    }

    //########################################################################################
     fmt::print("\n-------------- Region paralela Master threads");

    //controlamos el numero de hilos que se van a crear en la region paralela
     #pragma omp parallel 
    {
        int thread_id = omp_get_thread_num();

        // define al hilo maestro
        #pragma omp master
        {
            int threads_count = omp_get_num_threads();
            fmt::print("\nI have {} thread(s)", threads_count);
        }

        fmt::print("\nMy thread_id is {}", thread_id);
    }

    //########################################################################################
       fmt::print("\n-------------- Region paralela FOR");
       
       //similar a arrayList en java, aqui se lo conoce como template vector 
       std::vector<int> datos;
       for(int i = 0; i < 20; i++){

        //agregamos datos al vector
           datos.push_back(i);
       }

       #pragma omp parallel for num_threads(2)
         for(int i = 0; i < datos.size(); i++){
            int thread_id = omp_get_thread_num();
            fmt::print("\nMy thread_id is {} and datos[{}] = {}", thread_id, i, datos[i]);
         }

         fmt::print("\n-------------- Region paralela FOR con region paralela");

         std:: map<int, std::vector <int>> datos_map;
         datos_map[0] = {};
         datos_map[1] = {};

         #pragma omp parallel num_threads(2)
         {
            #pragma omp for
            for(int i = 0; i < datos.size(); i++){
                int thread_id = omp_get_thread_num();
                fmt::print("\nMy thread_id is {} and datos[{}] = {}", thread_id, i, datos[i]);
            }
         }


         //version iterativa de la impresion del mapa
         for(auto it: datos_map){
            fmt::println("datos_map[{}] = {}", it.first, it.second);
         }

         //version funcional de la impresion del mapa
         std::for_each(datos_map.begin(), datos_map.end(), [](const std::pair<int, std::vector<int>>& it){
            fmt::println("datos_map[{}] = {}", it.first, it.second);
         });

    return 0;
}