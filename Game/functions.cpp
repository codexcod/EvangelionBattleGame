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


using namespace std;


tuple<string, double, int, int, bool> spawn_children(int reprod, float prob_born, float prob_berserker, atomic<float>* newborns)
{
    tuple<string,double, int, int, bool> result;
	string type = prob_berserker > 0 ? "Evita" : "Angel";
	bool is_berserker = false;

	int child_pid = -1;

	for (int i = 0; i < reprod; i++) 
	{
        child_pid = -1;
		
		// Seteamos los valores de la distribución según cada especie
		float u = (type == "Evita") ? 20 : 25;
		float std = (type == "Evita") ? 5 : 10;

		// Inicializamos un generador con distribucion uniforme en el intervalo (0,1)
		// La semilla es aleatoria, pero puede ser util fijarla para facilitar las pruebas	
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		default_random_engine generator (seed);
		uniform_real_distribution<double> distribution(0.0,1.0);

		// Inicializamos un generador con distribucion normal
		normal_distribution<double> ap_distribution(u,std);

		if (distribution(generator) >= prob_born) // Si nace
		{
			child_pid = fork();

			if (child_pid == 0) {

				// Si es evita y tiene de hijo un berserker
				if (type == "Evita" && distribution(generator) >= prob_berserker)
				{
					is_berserker = true;
					result = make_tuple(type, fabsf(ap_distribution(generator)*2), getpid(), getppid(), is_berserker);
					return result;
				}	

				result = make_tuple(type, fabsf(ap_distribution(generator)), getpid(), getppid(), is_berserker);
				return result;
			}
		}
	}

	if (child_pid > 0)
    {
        for(int x = 0; x < reprod; x++)
        {
            wait(NULL); // Espera a hijos
        }
        exit(0);
    }
	
    return result;
}


void* share_mem(int size)
{
	// Vamos a pedir size * sizeof(atomic<int>) para reservar suficiendte memoria 
	// para un vector sizeof nos dice el tamaño del tipo atomic int.
    void * mem;
    if( MAP_FAILED == (mem = (atomic<float>*)mmap(NULL, sizeof(atomic<float>)*size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0) ) )
    {
        perror( "mmap failed" );
        exit( EXIT_FAILURE );
    }
    return mem;
}

void printResults(float power_margin, int max_days, atomic<float>* evitas, atomic<float>* angels)
{
	printf("Fin de la Simulación:\n");

	for(int i = 1; i < max_days; i++)
    {   
		
		angels[i] = angels[i] + angels[i - 1];
        angels[i + max_days] = angels[i + max_days] + angels[i - 1 + max_days];
        evitas[i] = evitas[i] + evitas[i - 1];
        evitas[i + max_days] = evitas[i + max_days] + evitas[i - 1 + max_days];

        cout << "Days Simulated: "<< i << endl;
        cout << "Angels: " << angels[i] - angels[i - 1] << endl;
        cout << "Angels Total Power: "<< angels[i + max_days] << endl;
        cout << "Evitas: "<<evitas[i] - evitas[i - 1] << endl;
        cout << "Evitas Total Power: "<<evitas[i + max_days]  << endl;

		// Chequea que si hubo un empate de poderes
        if( fabsf(angels[i + max_days] - evitas[i + max_days]) < power_margin )
        {
			printf("There was a match between evitas and angels power ;) in\n");

            cout << "Day: " << i << endl;
            cout << "Angels: " << angels[i] << endl;
			cout << "Angels Total Power: " << angels[i + max_days] << endl;
			cout << "Evitas: " << evitas[i] << endl;
			cout << "Evitas Total Power: " << evitas[i + max_days] << endl;

            return;        
        }
    }                      

    cout << "There was not a match between evitas and angels power ;(" << endl;
}

