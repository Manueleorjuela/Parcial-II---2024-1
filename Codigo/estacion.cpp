#include "estacion.h"


void Estacion::Inicializar_Tiempo()
{
    cout << "\nIngrese el tiempo aproximado que toma llegar a esta estacion (EN MINUTOS): ";
    cin >> Tiempo;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

Estacion::Estacion(string Nombre_Estacion, bool Es_No_De_Transferencia)
{
    Nombre = Nombre_Estacion;
    Transferencia = Es_No_De_Transferencia;
    Inicializar_Tiempo();
}

Estacion::Estacion(string Nombre_Estacion, bool Es_No_De_Transferencia, int Tiempo_)
{
    Nombre = Nombre_Estacion;
    Transferencia = Es_No_De_Transferencia;
    Tiempo = Tiempo_;
}

Estacion::Estacion()
{
    Nombre = "No tiene nombre";
    Transferencia = false;
    Tiempo = 0;
}

string Estacion::Get_Nombre()
{
    return Nombre;
}

bool Estacion::Get_Transferencia()
{
    return Transferencia;
}

int Estacion::Get_Tiempo()
{
    return Tiempo;
}


void Estacion::Set_Tiempo(int Nuevo_Tiempo)
{
    Tiempo = Nuevo_Tiempo;
}

void Estacion::Set_Tiempo_Eliminar(int Nuevo_Tiempo)
{
    Tiempo += Nuevo_Tiempo;
}

void Estacion::Set_Transfrencia(bool Cambio)
{
    Transferencia = Cambio;
}

void Estacion::Set_Nombre(string Nuevo_Nombre)
{
    Nombre = Nuevo_Nombre;
}

