#include "Red_Metro.h"
#include <cstdlib>



int main()
{
    Red_Metro Metro;
    cout << "Bienvenido a la red metro." << endl;
    int Opcion;
    bool Corre = true;
    while (Corre){
        cout << "Operaciones disponibles para realizar: " << endl;
        cout << "\n1. Anadir linea.";
        cout << "\n2. Eliminar linea.";
        cout << "\n3. Anadir estacion.";
        cout << "\n4. Eliminar estacion.";
        cout << "\n5. Conocer la cantidad de lineas en la red.";
        cout << "\n6. Conocer la cantidad de estaciones en una linea.";
        cout << "\n7. Conocer la cantidad de estaciones en la red.";
        cout << "\n8. Calcular el tiempo de llegada de una estacion a otra.";
        cout << "\n9. Saber si una estacion especifica pertenece a una linea.";
        cout << "\n10. Limpiar la consola.";
        cout << "\nCualquier otro caracter para salir.";

        cout << "\n\nIngrese una opcion: "; cin >> Opcion;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(Opcion){
        case 1:
            Metro.Añadir_Linea();
                break;
        case 2:
            Metro.Eliminar_Linea();
            break;
        case 3:
            Metro.Añadir_Estacion();
                break;
        case 4:
            Metro.Eliminar_Estacion();
            break;
        case 5:
            cout << Metro.Get_Tamaño() << endl;
                break;
        case 6:
            Metro.Cantidad_Estaciones_Linea();
            break;
        case 7:
            Metro.Cantidad_Estaciones_Red_Metro();
            break;
        case 8:
            Metro.Calcular_Tiempo_Estaciones();
            break;
        case 9:
            Metro.Estacion_Pertenece_A_Linea_Especifica();
            break;
        case 10:
            system("cls");
            break;
        default:
            cout << "Saliendo del programa." << endl;
            Corre = false;
            break;
        }
        cout << endl;
    }
}
