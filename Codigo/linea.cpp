#include "linea.h"

bool Linea::Existencia_Estacion(string &Nombre_Estacion)
{
    bool Existe = false;
    cout << endl << "Ingrese el nombre de la nueva estacion: ";
    cin.ignore();
    getline(cin, Nombre_Estacion);
    Nombre_Estacion += " " + Nombre;

    if (Linea_ == nullptr){
        cout << "Por el momento, la estacion que anadira es la unica en la linea." << endl;
    }
    else{
        for (int i = 0; i < Tamaño; i++) {
            if (Linea_[i].Get_Nombre() == Nombre_Estacion) {
                Existe = true;
                break;
            }
        }
    }
    return Existe;
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

int Linea::Seleccionar_Añadir()
{
    Mostrar_Estaciones();
    int Posicion = 0;
    if (Linea_ != nullptr){
        while(true){
            cout << "\nTeniendo en cuenta lo siguiente: \n.Ingrese 1 si desea que la estacion se ubique al inicio de la linea.";
            cout << "\n.Ingrese cualquier indice mostrado si desea que la nueva estacion se ubique en esa posicion.";
            cout << "\n.Ingrese el indice mayor + 1 si desea que la nueva estacion se ubique al final de la linea.";
            cout << "\nSeleeciona la ubicacion de la estacion en la linea: ";
            cin >> Posicion;
            if (Posicion < 1 || Posicion > Tamaño+1){
                cout <<"Ubicacion no valida, intente de nuevo."<< endl;
            }else break;
        }
        Posicion -=1;
    }
    return Posicion;
}

int Linea::Seleccionar_Eliminar()
{
    Mostrar_Estaciones();
    int Posicion = 0;
    while(true){
        cout << "\nSeleeciona la ubicacion de la estacion en la linea: ";
        cin >> Posicion;
        if (Posicion < 1 || Posicion > Tamaño){
            cout <<"Ubicacion no valida, intente de nuevo."<< endl;
        }else break;
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

void Linea::Mostrar_Estaciones()
{
    cout <<endl << "Estaciones presentes en la linea: " << endl;

    if (Linea_ == nullptr){
        cout <<"La linea aun no tiene estaciones, la ingresada se anadira en la posicion inicial." << endl;
    }else{
        for (int i = 0; i < Tamaño; i++){
        cout << i+1 << ". " << Linea_[i].Get_Nombre() << endl;
        }
    }
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
    Tamaño =  Tamaño_Linea;
}

Linea::Linea()
{
    Nombre = "No tiene nombre";
    Tamaño = 0;
    Linea_ = nullptr;
}

void Linea::Añadir_Estacion()
{
    string Nombre_Estacion;
    bool Existe = Existencia_Estacion(Nombre_Estacion);
    if(!Existe){
        bool Es_De_Transferencia = Verificacion_Transferencia();
        int Posicion = Seleccionar_Añadir();
        Tamaño += 1;

        Estacion *Actualizacion = new Estacion[Tamaño];
        for (int i = 0; i < Tamaño; i++) {
            if (i < Posicion) {
                Actualizacion[i] = Linea_[i];
            }else if (i == Posicion) {
                Actualizacion[i] = Estacion(Nombre_Estacion, Es_De_Transferencia);
            }else {
                Actualizacion[i] = Linea_[i - 1];
            }
        }
        delete [] Linea_;
        Linea_ = Actualizacion;
    }
    else{
        Error1_EstacionEncontrada();
    }
}

void Linea::Eliminar_Estacion()
{
    int Posicion = Seleccionar_Eliminar();
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
    else Error2_EstacionDeTransferenciaEncontrada();
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

void Linea::Error1_EstacionEncontrada()
{
    try {
        throw runtime_error("La estacion ingresada ya esta almacenada en la linea.");
    } catch (const runtime_error& ex) {
        cout << "Error: " << ex.what() << endl;
    }
}

void Linea::Error2_EstacionDeTransferenciaEncontrada()
{
    try {
        throw runtime_error("La estacion ingresada es de transferencia, no puede eliminarse.");
    } catch (const runtime_error& ex) {
        cout << "Error: " << ex.what() << endl;
    }
}
