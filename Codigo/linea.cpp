#include "linea.h"

bool Linea::Validacion_Error1(string &Nombre_Estacion)
{
    bool Existe = false;
    string Nombre;
    cout << endl << "Ingrese el nombre de la nueva estacion: ";
    getline(cin, Nombre_Estacion);

    if(!Validacion_Linea_Vacia(0)) {

        for (int i = 0; i < Tamaño; i++) {
            Nombre = Linea_[i].Get_Nombre();
            if (Linea_[i].Get_Transferencia() == true){
                Nombre = Nombre.substr(0, Nombre.size() - 2);
            }
            if (Nombre == Nombre_Estacion) {
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
        break;
        case 2:
            delete[] Linea_;
            Linea_ = nullptr;
        break;
        }
    }
    return Validacion;
}

bool Linea::Validacion_Posiciones_Extremas(int &Posicion)
{
    bool Validacion = false;
    int Posicion_AñadirTiempo = Posicion;

    if (Posicion == 0 or Posicion == Tamaño-1){
        cout << "La estacion se ubica en un extremo, por lo tanto el tiempo asociado sera 0 minutos." << endl;
        Validacion = true;
        Validacion_Solo_Dos_Estaciones();
        if (Tamaño > 2){
            if (Posicion == Tamaño-1){
                Posicion_AñadirTiempo -=1;
            }
            Modificar_TiempoEstaciones(Posicion_AñadirTiempo);
        }
    }

    return Validacion;
}

void Linea::Validacion_Solo_Dos_Estaciones()
{
    int Tiempo;

    if (Tamaño == 2){
        cout << "\nAl solo ser dos estaciones, el tiempo estara asociado a la estacion que ya se encontraba en la linea.";
        cout << "\nIngrese el tiempo para la estacion " << Linea_[0].Get_Nombre() <<": ";
        cin >> Tiempo;
        Linea_[0].Set_Tiempo(Tiempo);
    }
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
        while (true){
        Mostrar_Estaciones();
        cout << "\nTeniendo en cuenta lo siguiente: \n.Ingrese 1 si desea que la estacion se ubique al inicio de la linea.";
        cout << "\n.Ingrese cualquier indice mostrado si desea que la nueva estacion se ubique en esa posicion.";
        cout << "\n.Ingrese el indice mayor + 1 si desea que la nueva estacion se ubique al final de la linea.";
        cout << "\nSelecciona la ubicacion de la estacion en la linea: ";
        cin >> Posicion;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (Posicion < 1 || Posicion > Tamaño+1){
            Validacion = true;
            Error4_PosicionInvalida();
            }
        else break;
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

void Linea::Modificar_TiempoEstaciones(int &Posicion_Cambio)
{
    int Nuevo_Tiempo;

    cout << "Ingrese el nuevo tiempo asociado a la estacion " <<Linea_[Posicion_Cambio].Get_Nombre() << " ya que esta no es un extremo: ";
    cin >> Nuevo_Tiempo;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Linea_[Posicion_Cambio].Set_Tiempo(Nuevo_Tiempo);
}

void Linea::Modificar_TiempoEstacionesEliminar(int &Posicion_Cambio)
{
    if (Posicion_Cambio == 0 || Posicion_Cambio == Tamaño-1){
        if (Posicion_Cambio == 0){
            Linea_[Posicion_Cambio+1].Set_Tiempo(0);
            Linea_[Posicion_Cambio+2].Set_Tiempo_Eliminar(Linea_[Posicion_Cambio+1].Get_Tiempo());
        }
        if (Posicion_Cambio == Tamaño-1){
            Linea_[Posicion_Cambio-1].Set_Tiempo(0);
            Linea_[Posicion_Cambio-2].Set_Tiempo_Eliminar(Linea_[Posicion_Cambio+1].Get_Tiempo());
        }
    }else{
        Linea_[Posicion_Cambio-1].Set_Tiempo_Eliminar(Linea_[Posicion_Cambio].Get_Tiempo());
        Linea_[Posicion_Cambio+1].Set_Tiempo_Eliminar(Linea_[Posicion_Cambio+1].Get_Tiempo());
    }
}

void Linea::Mostrar_Estaciones_Linea()
{
    cout << endl << "\nEstaciones de transferencia presentes en la linea: "<< endl;
    int Cont = 1;
    for (int i = 0; i < Tamaño; i++){
        if (Linea_[i].Get_Transferencia() == true){
            cout << Cont <<". " << Linea_[i].Get_Nombre()  << endl;
        }
    }
}

Linea::Linea(string Nombre_Linea, int Tamaño_Linea)
{
    Nombre = Nombre_Linea;

    if (Tamaño_Linea > 0) {
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

void Linea::Añadir_Estacion(bool &Termina_Proceso, bool &Es_De_Transferencia, int& Posicion_Estacion)
{
    string Nombre_Estacion;
    if(!Validacion_Error1(Nombre_Estacion)){
        if(!Validacion_Error3(Es_De_Transferencia)){
            Validacion_Error4_Añadir(Posicion_Estacion);
                Tamaño += 1;
                Estacion *Actualizacion = new Estacion[Tamaño];
                for (int i = 0; i < Tamaño; i++) {
                    if (i < Posicion_Estacion) {
                        Actualizacion[i] = Linea_[i];
                    }else if (i == Posicion_Estacion) {
                        if(Validacion_Posiciones_Extremas(Posicion_Estacion)){
                            Actualizacion[i] = Estacion(Nombre_Estacion, Es_De_Transferencia,0 );
                        }else{
                        Actualizacion[i] = Estacion(Nombre_Estacion, Es_De_Transferencia);
                        }
                    }else {
                        Actualizacion[i] = Linea_[i - 1];
                    }
                }
                delete [] Linea_;
                Linea_ = Actualizacion;
                Termina_Proceso = true;
        }
    }
}

void Linea::Añadir_Estacion(bool Transferencia, string &Nombre_Estacion_Conexion)
{
    int Posicion_Estacion;
    Validacion_Error4_Añadir(Posicion_Estacion);
    Tamaño += 1;
    Estacion *Actualizacion = new Estacion[Tamaño];
    for (int i = 0; i < Tamaño; i++) {
        if (i < Posicion_Estacion) {
        Actualizacion[i] = Linea_[i];
        }else if (i == Posicion_Estacion) {
        if(Validacion_Posiciones_Extremas(Posicion_Estacion)){
                Actualizacion[i] = Estacion(Nombre_Estacion_Conexion, Transferencia,0 );
        }else{
                Actualizacion[i] = Estacion(Nombre_Estacion_Conexion, Transferencia);
        }
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
    Validacion_Error4_Eliminar(Posicion);
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

int Linea::Cantidad_Estaciones_Transferencia()
{
    int Contador = 0;
    for (int i = 0; i < Tamaño; i++){
        if (Linea_[i].Get_Transferencia() == true){
            Contador++;
        }
    }
    return Contador;
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
        throw runtime_error("La posicion ingresada es invalida. Intete de nuevo.");
    } catch (const runtime_error& ex) {
        cout << "Error: " << ex.what() << endl;
    }
}


