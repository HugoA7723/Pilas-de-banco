#include "Banco.h"

int main()
{
    TPersona * cabecera = NULL; //Cabecera de la lista
    TPersona * preferente = NULL; //Lista de clientes preferentes
    TPersona * no_preferente = NULL; //Lista de clientes no preferentes
    TPersona * tramite = NULL; //Lista de clientes con un tramite en especifico
    int o, e, t, i;
    char n[50];

    printf("Programa para administrar una pila de clientes de un banco.\n");

    while(o != 6)
    {
        printf("Selecciona la opcion a realizar:\n1: Agregar cliente\n2: Eliminar cliente\n3: Mostrar clientes\n4: Filtrar clientes con un tramite en especifico\n5: Filtrar clientes preferntes y no preferentes\n6: Salir\n");
        scanf("%d", &o);

        switch (o)
        {
            case 1: //Agregar cliente
                printf("Ingresa el nombre del cliente:  \n");
                getchar();
                fgets(n, sizeof(n), stdin);
                printf("Ingresa el estado del cliente: 1 si es preferente, 0 si no lo es:  \n");
                scanf("%d", &e);
                if(e != 1 && e != 0)
                {
                    printf("Estado invalido, vuelve a ingresar el cliente y porfavor ingresa 1 si es preferente, 0 si no lo es\n");
                    break;
                }
                printf("Ingresa el numero de tramite del cliente:  \n");
                scanf("%d", &t);
                printf("Ingresa el identificador del cliente:  \n");
                scanf("%d", &i);
                printf("Cliente ingresado correctamente con los datos siguientes:\n");

                Agrega_cliente(n, e, t, i, &cabecera);
                printf("Nombre: %sEstado: %s\nTramite: %d\nIdentificador: %d\n\n", n, (e == 1) ? "Preferente" : "No prefernte", t, i);
                break;
            case 2: //Eliminar cliente
                if(cabecera == NULL)
                {
                    printf("No hay clientes en la pila\n");
                    break;
                }
                printf("Ingresa el identificador del cliente a eliminar:  \n");
                scanf("%d", &i);
                Elimina_cliente(i, &cabecera);
                printf("Cliente con identificador %d eliminado correctamente\n", i);
                break;

            case 3: //Mostrar clientes
                if(cabecera == NULL)
                {
                    printf("No hay clientes en la pila\n");
                    break;
                }
                Imprime_clientes(cabecera);
                break;
            case 4: //Mostrar clientes con un tramite en especifico
                if(cabecera == NULL)
                {
                    printf("No hay clientes en la pila\n");
                    break;
                }
                printf("Ingresa el numero de tramite a filtrar:  \n");
                scanf("%d", &t);
                Filtra_tramite(cabecera, &tramite, t);
                tramite = NULL; //Reiniciar la lista para evitar problemas
                break;
            case 5:
                if(cabecera == NULL)
                {
                    printf("No hay clientes en la pila\n");
                    break;
                }
                Filtra_estado(cabecera, &preferente, &no_preferente);
                preferente = NULL; //Reiniciar la lista para evitar problemas
                no_preferente = NULL; //Reiniciar la lista para evitar problemas
                break;
            case 6: //Salir
                printf("Saliendo del programa...\n");
                exit(1);
                break;
            default:
                printf("Opcion invalida, por favor ingresa un numero del 1 al 6\n");
                break;
        }
    }
}

void Agrega_cliente(char n[], int e, int t, int i, TPersona **c)
{
    TPersona * nuevo = Crea_nodo(n, e, t, i);
    if(*c == NULL)
    {
        *c = nuevo;
        return;
    }
    if(e == 1) //Si es preferente
    {
        Inserta_inicio(c, nuevo);
    }
    else //Si no es preferente
    {
        Inserta_final(c, nuevo);
    }
}

TPersona * Crea_nodo(char n[], int e, int t, int i)
{
    TPersona * nuevo = (TPersona *)malloc(sizeof(TPersona));
    if(nuevo == NULL)
    {
        printf("Error al asignar memoria\n");
        exit(1);
    }

    strcpy(nuevo-> n, n);
    nuevo -> e  = e;
    nuevo -> t = t;
    nuevo -> i = i;
    nuevo -> sig = NULL;
    return nuevo;
}

void Inserta_inicio(TPersona **c, TPersona * nuevo)
{
    if(*c == NULL)
    {
        *c = nuevo;
    }
    else
    {
        nuevo-> sig = *c;
        (*c)-> ant = nuevo;
        *c = nuevo;
    }
}

void Inserta_final(TPersona **c, TPersona * nuevo)
{
    TPersona * aux = *c;
    if(*c == NULL)
    {
        *c = nuevo;
        nuevo -> ant = NULL;
        nuevo -> sig = NULL; 
    }
    else
    {
        while(aux->sig != NULL)
        {
            aux = aux->sig;
        }
        aux->sig = nuevo;
        nuevo->ant = aux;
        nuevo->sig = NULL; 
    }
}

void Elimina_cliente(int i, TPersona **c)
{
    TPersona * aux = *c;
    while(aux != NULL && aux -> i != i)
    {
        aux = aux -> sig;
    }
    if(aux == NULL)
    {
        printf("No se encontro el cliente con identificador %d\n", i);
        return;
    }
    if(aux -> ant != NULL)
    {
        aux -> ant -> sig = aux -> sig;
    }
    else
    {
        *c = aux -> sig;
    }
    if(aux -> sig != NULL)
    {
        aux -> sig -> ant = aux -> ant;
    }
    free(aux);
}

void Imprime_clientes(TPersona * c)
{
    TPersona * aux = c;
    printf("Clientes en la fila:\n");
    while(aux != NULL)
    {
        printf("Nombre: %sEstado: %s\nTramite: %d\nIdentificador: %d\n\n", aux -> n, (aux -> e == 1) ? "Preferente" : "No prefernte", aux -> t, aux -> i);
        aux = aux -> sig;
    }
}

void Filtra_estado(TPersona * c, TPersona ** preferente, TPersona ** no_preferente)
{
    TPersona * aux = c;
    while(aux != NULL)
    {
        if(aux -> e == 1)
        {
            Inserta_final(preferente, Crea_nodo(aux -> n, aux -> e, aux -> t, aux -> i));
        }
        else
        {
            Inserta_final(no_preferente, Crea_nodo(aux -> n, aux -> e, aux -> t, aux -> i));
        }
        aux = aux -> sig;
    }

    printf("Lista de clientes preferentes:\n");
    Imprime_clientes(*preferente);
    printf("Lista de clientes no preferentes:\n");
    Imprime_clientes(*no_preferente);
}

void Filtra_tramite(TPersona * c, TPersona ** tramite, int t)
{
    TPersona * aux = c;
    int encontrado = 0;
    while(aux != NULL)
    {
        if(aux -> t == t)
        {
            Inserta_final(tramite, Crea_nodo(aux -> n, aux -> e, aux -> t, aux -> i));
            encontrado = 1;
        }
        aux = aux -> sig;
    }

    if(encontrado) 
    {
        printf("Lista de clientes con tramite %d:\n", t);
        Imprime_clientes(*tramite);
    } 
    else 
    {
        printf("No se encontro ningun cliente con tramite %d.\n", t);
    }
}

// Hecho unicamente por: Hugo Alberto Alba Medina y con ayuda de Copilot
// Ultimos cambios realizados: 27 de septiembre de 2025
