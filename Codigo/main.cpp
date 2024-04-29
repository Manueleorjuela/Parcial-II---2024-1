#include "Red_Metro.h"

int main()
{
    Red_Metro Metro;
    cout <<  Metro.Get_Tamaño() << endl;

    Metro.Añadir_Linea();
    Metro.Mostrar_Lineas();
    cout <<  Metro.Get_Tamaño() << endl;

    Metro.Eliminar_Linea();
    Metro.Mostrar_Lineas();
    cout <<  Metro.Get_Tamaño() << endl;
}
