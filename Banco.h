#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct nodo
{
    struct nodo * sig;
    struct nodo * ant;
    char n[50];
    int e; //Estado 1 si es preferente, 0 si no lo es
    int t; //Tramite
    int i; //Identificador
}TPersona;

void Agrega_cliente(char n[], int e, int t, int i, TPersona **c);
TPersona * Crea_nodo(char n[], int e, int t, int i);
void Inserta_inicio(TPersona **c, TPersona * nuevo);
void Inserta_final(TPersona **c, TPersona * nuevo);
void Elimina_cliente(int i, TPersona **c);
void Imprime_clientes(TPersona * c);
void Filtra_estado(TPersona * c, TPersona ** preferente, TPersona ** no_preferente);
void Filtra_tramite(TPersona * c, TPersona ** tramite, int t);