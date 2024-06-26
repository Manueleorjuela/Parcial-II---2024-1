#ifndef LINEA_H
#define LINEA_H
#include "estacion.h"
#include <chrono>
#include <ctime>

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

    //Funciones de manejo
    void Mostrar_Estaciones();
    void Inicializar_Tiempos(int& Posicion);
    void Eliminar_Tiempos(int& Posicion);
    int Ingresar_Cambio_Tiempo(int Case);

    void Calcular_Tiempo_Caso(int &Posicion_Inicio, int &Posicion_Llegada, int &Tiempo);;
    void Operar_Tiempo(int& Hora, int& Minuto, int& Tiempo);

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

    void Estacion_Especifica_Pertenece_Linea();
    void Calcular_Tiempo_Entre_Estaciones();

    int GetTamaño();
    string Get_Nombre();
    Estacion *Get_Linea();
    bool Get_LineaConectada();


    void Set_LineaConectada(bool Cambio);
    void Set_Transferencia(bool Cambio);

};

#endif // LINEA_H
