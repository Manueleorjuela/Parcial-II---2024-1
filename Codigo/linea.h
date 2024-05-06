#ifndef LINEA_H
#define LINEA_H
#include "estacion.h"

class Linea
{
private:

    string Nombre;
    int Tamaño;
    Estacion *Linea_;
    bool Linea_Conectada;

    //Validar
    bool Validacion_Error1(string &Nombre_Estacion);
    bool Validacion_Error2(int &Posicion_Estacion);
    bool Validacion_Error3(bool &Transferencia);
    bool Validacion_Error4_Añadir(int &Posicion);
    bool Validacion_Error4_Eliminar(int &Posicion);
    bool Validacion_Linea_Vacia(int Case);
    bool Validacion_Posiciones_Extremas(int &Posicion);
    void Validacion_Solo_Dos_Estaciones();

    //Funciones de manejo
    void Mostrar_Estaciones();
    void Modificar_TiempoEstaciones(int &Posicion_Cambio);
    void Modificar_TiempoEstacionesEliminar(int &Posicion_Cambio);

    //Errores

    void Error1_EstacionRepetida();
    void Error2_EstacionDeTransferenciaEncontrada();
    void Error3_RequerimientoTransferenciaInvalido();
    void Error4_PosicionInvalida();

public:

    Linea();
    Linea(string Nombre_Linea, int Tamaño_Linea);
        ~Linea();

    //Operaciones con estaciones
    void Añadir_Estacion(bool &Termina_Proceso, bool &Transferencia, int& Posicion_Estacion);
    void Añadir_Estacion(bool Transferencia, string &Nombre_Estacion_Conexion);

    void Eliminar_Estacion();
    void Eliminar_Estacion(int &Posicion_Estacion);

    int Cantidad_Estaciones_Transferencia();
    void Mostrar_Estaciones_Linea();

    int GetTamaño();
    string Get_Nombre();
    Estacion *Get_Linea();
    bool Get_LineaConectada();


    void Set_LineaConectada(bool Cambio);
    void Set_Transferencia(bool Cambio);

};

#endif // LINEA_H
