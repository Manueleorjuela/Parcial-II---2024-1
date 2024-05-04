#include "linea.h"

bool Linea::Validacion_Error1(string &Nombre_Estacion_Conexion, string &Nombre_Estacion)
{
    bool Existe = false;
    cout << endl << "Ingrese el nombre de la nueva estacion: ";
    getline(cin, Nombre_Estacion);

    Nombre_Estacion_Conexion = Nombre_Estacion;
    Nombre_Estacion += " " + Nombre;

    if(!Validacion_Linea_Vacia(0)) {
        for (int i = 0; i < Tamaño; i++) {
            if (Linea_[i].Get_Nombre() == Nombre_Estacion) {
                Existe = true;
                Error1_EstacionRepetida();
                break;
            }
        }
    }
    return Existe;
}

bool Linea::Validacion_Linea_Vacia(int Case)
{
    bool Validacion = false;
    if (Linea_ == nullptr || Tamaño == 0){
        Validacion = true;
        switch (Case){
        case 0:
            cout << "Por el momento, la estacion que anadira es la unica en la linea." << endl;
            break;
        case 1:
            cout << "La estacion sera ubicada en la posicion inicial." << endl;
        break;
        case 2:
            delete[] Linea_;
            Linea_ = nullptr;
        break;
        }
    }
    return Validacion;
}

bool Linea::Validacion_Error3(bool &Transferencia)
{
    int Opcion;
    bool Validacion = false;

    cout << endl << "De acuerdo a lo siguiente:" << endl;
    cout << "Ingrese 1 para indicar que la estacion es de transferencia." << endl;
    cout << "Ingrese 0 para indicar que la estacion no es de transferencia." << endl;
    cout << "Ingrese una opcion: ";
    cin >> Opcion;
    if (Opcion != 0 && Opcion != 1) {
        Error3_RequerimientoTransferenciaInvalido();
        Validacion = true;
    }else{
        Transferencia = static_cast<bool>(Opcion);
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return Validacion;
}

bool Linea::Validacion_Error4_Añadir(int &Posicion)
{
    bool Validacion = false;
    if (Validacion_Linea_Vacia(1)){
        Posicion = 1;
    }else{
        Mostrar_Estaciones();
        cout << "\nTeniendo en cuenta lo siguiente: \n.Ingrese 1 si desea que la estacion se ubique al inicio de la linea.";
        cout << "\n.Ingrese cualquier indice mostrado si desea que la nueva estacion se ubique en esa posicion.";
        cout << "\n.Ingrese el indice mayor + 1 si desea que la nueva estacion se ubique al final de la linea.";
        cout << "\nSeleeciona la ubicacion de la estacion en la linea: ";
        cin >> Posicion;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (Posicion < 1 || Posicion > Tamaño+1){
            Validacion = true;
        Error4_PosicionInvalida();
        }
    }
    Posicion -=1;
    return Validacion;
}

bool Linea::Validacion_Error4_Eliminar(int &Posicion)
{
    bool Validacion = false;
    Mostrar_Estaciones();
    cout << "\nSeleccione la ubicacion de la estacion en la linea: ";
    cin >> Posicion;
    if (Posicion < 1 || Posicion > Tamaño) {
        Validacion = true;
        Error4_PosicionInvalida();
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Posicion -= 1;
    return Validacion;
}

bool Linea::Validacion_Error2(int &Posicion)
{
    bool Validacion = false;
    if (Linea_[Posicion].Get_Transferencia() == true){
        Error2_EstacionDeTransferenciaEncontrada();
        Validacion = true;
    }
    return Validacion;
}

void Linea::Mostrar_Estaciones()
{
    cout <<endl << "Estaciones presentes en la linea: " << endl;
    for (int i = 0; i < Tamaño; i++){
        cout << i+1 << ". " << Linea_[i].Get_Nombre() << endl;
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
    Linea_Conectada = false;

}

Linea::Linea()
{
    Nombre = "No tiene nombre";
    Tamaño = 0;
    Linea_ = nullptr;
}

void Linea::Añadir_Estacion(string &Nombre_Estacion_Conexion, bool &Es_De_Transferencia, int& Posicion_Estacion)
{
    string Nombre_Estacion;
    if(!Validacion_Error1(Nombre_Estacion_Conexion, Nombre_Estacion)){
        if(!Validacion_Error3(Es_De_Transferencia)){
        if (!Validacion_Error4_Añadir(Posicion_Estacion)){
                Tamaño += 1;
                Estacion *Actualizacion = new Estacion[Tamaño];
                for (int i = 0; i < Tamaño; i++) {
                    if (i < Posicion_Estacion) {
                        Actualizacion[i] = Linea_[i];
                    }else if (i == Posicion_Estacion) {
                        Actualizacion[i] = Estacion(Nombre_Estacion, Es_De_Transferencia);
                    }else {
                        Actualizacion[i] = Linea_[i - 1];
                    }
                }
                delete [] Linea_;
                Linea_ = Actualizacion;
            }
        }
    }
}

void Linea::Añadir_Estacion(bool Transferencia, string &Nombre_Estacion_Conexion)
{
    int Posicion_Estacion = Tamaño;
    Nombre_Estacion_Conexion += " " + Nombre;
    Tamaño += 1;
    Estacion *Actualizacion = new Estacion[Tamaño];
    for (int i = 0; i < Tamaño; i++) {
        if (i < Posicion_Estacion) {
        Actualizacion[i] = Linea_[i];
        }else if (i == Posicion_Estacion) {
        Actualizacion[i] = Estacion(Nombre_Estacion_Conexion, Transferencia);
        }else {
        Actualizacion[i] = Linea_[i - 1];
        }
    }
    delete [] Linea_;
    Linea_ = Actualizacion;
}

void Linea::Eliminar_Estacion()
{
    int Posicion;
    if(!Validacion_Error4_Eliminar(Posicion)){
        if(!Validacion_Error2(Posicion)){
            Tamaño -=1;
            if(!Validacion_Linea_Vacia(2)){
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
        }
    }
}

void Linea::Eliminar_Estacion(int &Posicion_Estacion)
{
    Tamaño -=1;
    if(!Validacion_Linea_Vacia(2)){
        Estacion *Actualizacion = new Estacion[Tamaño];
        for (int i = 0; i < Tamaño; i++){
            if (i < Posicion_Estacion){
            Actualizacion[i] = Linea_[i];
            }else if(i >= Posicion_Estacion){
            Actualizacion[i] = Linea_[i+1];
            }
        }
        delete [] Linea_;
        Linea_ = Actualizacion;
    }
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

bool Linea::Get_LineaConectada()
{
    return Linea_Conectada;
}

void Linea::Set_LineaConectada(bool Cambio)
{
    Linea_Conectada = Cambio;
}

Linea::~Linea()
{
    delete[] Linea_;
}

void Linea::Error1_EstacionRepetida()
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

void Linea::Error3_RequerimientoTransferenciaInvalido()
{
    try {
        throw runtime_error("Condicion ingresada invalida.");
    } catch (const runtime_error& ex) {
        cout << "Error: " << ex.what() << endl;
    }
}

void Linea::Error4_PosicionInvalida()
{
    try {
        throw runtime_error("La posicion ingresada es invalida.");
    } catch (const runtime_error& ex) {
        cout << "Error: " << ex.what() << endl;
    }
}


