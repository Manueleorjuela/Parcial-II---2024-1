#include "linea.h"

string Linea::Existencia_Estacion()
{
    string Nombre_Estacion;
    bool Existe = true;


    while (Existe) {
        cout << "Ingrese el nombre de la nueva estacion: ";
        getline(cin, Nombre_Estacion);

        if (Tamaño == 0){
            break;
        }else{
            for (int i = 0; i < Tamaño; i++) {
                if (Linea_[i].Get_Nombre() == Nombre_Estacion) {
                    cout << "La estacion ya existe en la linea, pruebe con otro." << endl;
                    break;

                }else Existe = false;
        }
        if (!Existe) break;
        }
    }

    return Nombre_Estacion;
}

bool Linea::Verificacion_Transferencia()
{
    int Transferencia;
    while (true) {
        cout << endl << "De acuerdo a lo siguiente:" << endl;
        cout << "Ingrese 1 para indicar que la estacion es de transferencia." << endl;
        cout << "Ingrese 0 para indicar que la estacion no es de transferencia." << endl;
        cout << "Ingrese una opcion: ";
        if (!(cin >> Transferencia)) {
            cout << "Entrada invalida. Por favor, ingrese un valor numerico (0 o 1)." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (Transferencia == 0 || Transferencia == 1) {
            break;
        } else {
            cout << "Opcion invalida. Por favor, ingrese 0 o 1." << endl;
        }
    }
    return static_cast<bool>(Transferencia);
}

int Linea::Mostrar_Estaciones()
{
    int Posicion;
    cout <<endl << "Estaciones presentes en la linea: " << endl;

    if (Tamaño == 0){
        cout << "La linea no tiene estaciones por el momento." << endl;
        Posicion = 1;

    }else{
        for (int i = 0; i < Tamaño; i++){
            cout << i+1 << ". " << Linea_[i].Get_Nombre() << endl;
    }
        while (true){
            cout << "Seleccione la posicion en la cual quiere realizar los cambios: ";
            cin >> Posicion;
            if (Posicion < 1 || Posicion > Tamaño){
                cout <<endl<<"Ubicacion no valida, intente de nuevo."<< endl;
            }else break;
        }
    }

    Posicion -=1;
    return Posicion;
}

bool Linea::Verificacion_Estacion_Transferencia(int Posicion)
{

    bool Transferencia = false;
    Transferencia =  (Linea_[Posicion].Get_Transferencia() == true);
    return Transferencia;
}

Linea::Linea(string Nombre_Linea, int Tamaño_Linea)
{
    Nombre = Nombre_Linea;
    if (Tamaño_Linea > 0) {
        Tamaño = Tamaño_Linea;
        Linea_ = new Estacion[Tamaño];
    } else {
        Linea_ = nullptr;
    }
}

Linea::Linea()
{

}

void Linea::Añadir_Estacion()
{
    string Nombre_Estacion = Existencia_Estacion();
    Nombre_Estacion += " " + Nombre;
    bool Es_De_Transferencia = Verificacion_Transferencia();
    int Posicion = Mostrar_Estaciones();
    //int Tiempo_Anterior;
    //int Tiempo_Posterior;


    Tamaño += 1;
    Estacion *Actualizacion = new Estacion[Tamaño];

    for (int i = 0; i < Tamaño; i++) {
        if (i < Posicion) {
            Actualizacion[i] = Linea_[i];
        } else if (i == Posicion) {
            Actualizacion[i] = Estacion(Nombre_Estacion, Es_De_Transferencia);
        } else {
            Actualizacion[i] = Linea_[i - 1];
        }
    }
    delete [] Linea_;
    Linea_ = Actualizacion;
}

void Linea::Eliminar_Estacion()
{
    int Posicion = Mostrar_Estaciones();
    bool Es_De_Transferencia = Verificacion_Estacion_Transferencia(Posicion);

    if (!Es_De_Transferencia){
        Tamaño -=1;
        Estacion *Actualizacion = new Estacion[Tamaño];

        for (int i = 0; i < Tamaño; i++){
            if (i < Posicion){
                Actualizacion[i] = Linea_[i];
            }else if(i >= Posicion){
                Actualizacion[i] = Linea_[i+1];
            }
        }
        delete [] Linea_;
        Linea_ = Actualizacion;
    }
    else cout << endl << "No se puede eliminar la estacion" << endl;
}


int Linea::GetTamaño()
{
    return Tamaño;
}

string Linea::Get_Nombre()
{
    return Nombre;
}

Estacion *Linea::Get_Linea()
{
    return Linea_;
}

Linea::~Linea()
{
    delete[] Linea_;
}

