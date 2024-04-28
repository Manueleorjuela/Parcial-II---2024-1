#include "estacion.h"


Estacion::Estacion(string Nombre_Estacion, bool Es_No_De_Transferencia)
{
    Nombre = Nombre_Estacion;
    Transferencia = Es_No_De_Transferencia;
}

Estacion::Estacion()
{

}

string Estacion::Get_Nombre()
{
    return Nombre;
}

bool Estacion::Get_Transferencia()
{
    return Transferencia;
}

int Estacion::Get_Tiempo_Anterior()
{
    return Tiempo_Anterior;
}

int Estacion::Get_Tiempo_Posterior()
{
    return Tiempo_Posterior;
}

void Estacion::Set_Tiempo_Anterior(int Nuevo_Tiempo)
{
    Tiempo_Anterior = Nuevo_Tiempo;
}

void Estacion::Set_Tiempo_Posterior(int Nuevo_Tiempo)
{
    Tiempo_Posterior = Nuevo_Tiempo;
}





