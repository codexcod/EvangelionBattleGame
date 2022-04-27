#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <random>
#include <chrono>
#include <math.h>
#include <sys/mman.h>  
#include <string.h>  
#include <atomic>
#include <tuple>
#include <cassert>
#include "functions.h"

using namespace std;

int main(int argc, char* argv[])
{
	// Utilizamos los parámetros que recibe main para obtener los valores de la 
	// simulacion (ver orden en pdf)
	int max_days = atoi(argv[1]); 
	int reprod_evitas = atoi(argv[2]);
	int reprod_angels = atoi(argv[3]); 
	float probs[3];
	probs[0] = stof(argv[4]); // prob nacimiento evita
	probs[1] = stof(argv[5]); // prob nacimiento angel
	probs[2] = stof(argv[6]); // prob nacimiento berserker
	float power_margin = stof(argv[7]);

 	// Vamos a almacenar la cantidad de evitas/angeles nuevos al termino de cada
 	// dia en un arreglo de floats y el poder acumulado de cada especia por día.
 	// Podemos pensarlo como un arreglo de 2 filas x max_days columnas.
 	// Es probable que necesiten que este arreglo sea compartido por todos los 
 	// procesos.
 	// Notar que en realidad estamos usando un float "atomico". Esto nos da 
 	// propiedades interesantes para evitar algunos problemas en caso de que
 	// ocurran escrituras concurrentes sobre el mismo espacio de memoria.
 	// Pueden asumir que funciona como cualquier otro float. 

 	int size = max_days;
	atomic<float> *evitas = (atomic<float> *) share_mem(size * sizeof(atomic<int>));
	atomic<float> *angels = (atomic<float> *) share_mem(size * sizeof(atomic<int>));
	
	// Por las dudas, fijamos a 0 todos los valores
	for(int i = 0;i < 2*size; i++)evitas[i] = 0;
	for(int i = 0;i < 2*size; i++)angels[i] = 0;

	// Inicializamos el conteo para para el dia 0
	evitas[0] = 1;
	angels[0] = 1;

  	int termianlPid = getpid();

  	// Atributos de cada especie. Sugerencia, setear cada variable según tipo.
  	atomic<float> *newborns;
    int reprod_tries;
  	float max_children, prob_born, prob_berserk;
  	string my_type = "";

  	// Crear a Adam y Lilith 
    int adamPid = fork();
    
    if (adamPid == 0) // Si es adam
    {
        prob_born = probs[0];
        prob_berserk = 0; // Los angeles no pueden ser berserk
        reprod_tries = reprod_angels; 
        newborns = angels;
    }
    else // Si es Terminal
    {
        int lilithPid = fork();

        if (lilithPid == 0) // Si es Lilith
        {
            prob_born = probs[1];
            prob_berserk = probs[2];
            reprod_tries = reprod_evitas;
            newborns = evitas;
        }
        else
        {
            // Espera a Adam, Lilith y sus respectivos pibes
            wait(NULL);
            wait(NULL);
            printResults(power_margin, max_days, evitas, angels);
            exit(0);
        }
    }
 	
 	// Corremos las simulaciones de nacimiento
	for(int day = 1; day < max_days; day++)
	{

		// Simulamos un dia y obtenemos los resultados
		tuple<string, double, int, int, bool> result = spawn_children(reprod_tries, prob_born, prob_berserk, newborns);
        string type = get<0>(result);
        double power = get<1>(result); 
        int pid = get<2>(result);
        int ppid = get<3>(result);
        bool is_berserker = get<4>(result);

        // Agrega el resultado a la lista
        newborns[day] =  newborns[day] + 1;
        newborns[day + max_days] = newborns[day + max_days] + power;

        cout << "Child Pid: " << pid << endl;
        cout << "Child Ppid: " << ppid << endl;
        cout << "Child Type: " << type << endl; 
        cout << "Child Power: " << power << endl;   

        if (is_berserker) // Si es berserker, no tiene hijos
        {
            exit(0);
        }   
	}
}