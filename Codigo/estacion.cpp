#include "estacion.h"


Estacion::Estacion(string Nombre_Estacion, bool Es_No_De_Transferencia, int Tiempo_Anterior_, int Tiempo_Siguiente_)
{
    Nombre = Nombre_Estacion;
    Transferencia = Es_No_De_Transferencia;
    Tiempo_Anterior = Tiempo_Anterior_;
    Tiempo_Siguiente = Tiempo_Siguiente_;
}

Estacion::Estacion()
{
    Nombre = "No tiene nombre";
    Transferencia = false;
    Tiempo_Anterior = 0;
    Tiempo_Siguiente = 0;
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

int Estacion::Get_Tiempo_Siguiente()
{
    return Tiempo_Siguiente;
}

void Estacion::Set_Tiempo_Anterior(int Nuevo_Tiempo)
{
    Tiempo_Anterior = Nuevo_Tiempo;
}

void Estacion::Set_Tiempo_Siguiente(int Nuevo_Tiempo)
{
    Tiempo_Siguiente = Nuevo_Tiempo;
}

void Estacion::Set_Transfrencia(bool Cambio)
{
    Transferencia = Cambio;
}

void Estacion::Set_Nombre(string Nuevo_Nombre)
{
    Nombre = Nuevo_Nombre;
}

