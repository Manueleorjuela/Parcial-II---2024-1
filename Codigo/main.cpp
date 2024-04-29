#include "Red_Metro.h"

int main()
{
    Red_Metro Metro;

    for (int i = 0; i < 2; i++){
        Metro.Añadir_Linea();
    }

    Metro.Mostrar_Lineas();


    Metro.Eliminar_Linea();
    Metro.Eliminar_Linea();
    Metro.Eliminar_Linea();

}
