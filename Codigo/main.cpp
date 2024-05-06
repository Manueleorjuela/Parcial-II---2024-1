#include "Red_Metro.h"
#include <cstdlib>



int main()
{
    Red_Metro Metro;

    int Opcion;
    bool Corre = true;
    while (Corre){
        cout << "Ingrese una opcion: "; cin >> Opcion;
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
            Corre = false;
            break;
        case 7:
            system("cls");
            break;
        }
        cout << endl;
    }
}
