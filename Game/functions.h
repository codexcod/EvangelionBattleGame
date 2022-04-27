#ifndef FUNCTIONS_INCLUDED_H
#define FUNCTIONS_INCLUDED_H

using namespace std;

// Los detalles de esta funcion NO son relevantes para el TP!! Pero los aclaro 
//por las dudas
// Esta funcion pide size * sizeof(atomic<float>) bytes dinámicamente
// Este espacio permite reservar suficiendte memoria para un ARREGLO de size 
//enteros atomicos. Nos devuelve un puntero (un tipo similar a las referencias)
// al comienzo de este espacio contiguo de memoria.
// Nota: sizeof es una funcion que nos dice el tamaño de un tipo, en este caso
// atomic float.
void* share_mem(int size);

// ************** //

// Esta funcion simula el proceso de nacimiento de evitas y angeles. Toma como parametros la probabilidad
// de nacimiento, la probabilidad de que el nacimiento sea berserker, y las reproducciones a realizar.
tuple<string, double, int, int, bool> spawn_children(int reprod, float prob_born, float prob_berserker, atomic<float>* newborns);

// Función que muestra en pantalla los resultados de la simulación
void printResults(float power_margin, int max_days, atomic<float>* evitas, atomic<float>* angels);


#endif
