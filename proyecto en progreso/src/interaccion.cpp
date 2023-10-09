#include "../include/metodos.h"


void ejecutarOpcion(const Opciones& opc) {
    int eleccion = opc.eleccion;
    const vector<int>& vectorPerfil = opc.vectorPerfil;
    const vector<int>& vectorEntrada = opc.vectorEntrada;
    const ifstream& archivoTexto = opc.archivoTexto;
    const string& f = opc.f;
    const string& t = opc.t;
    const string& i = opc.i;
    const string& o = opc.o;
    const ifstream& archivoSalida = opc.archivoSalida;
    const string rutaOut = opc.rutaOut;
    const string comandoPrepararDatos = opc.comandoPrepararDatos;
    const string comandoCrearIndice = opc.comandoCrearIndice;

    if (find(vectorPerfil.begin(), vectorPerfil.end(), eleccion) != vectorPerfil.end()) {
        switch (eleccion) {
            case 1:
                cout << "La suma de su vector v es: " << accumulate(vectorEntrada.begin(), vectorEntrada.end(), 0) << endl << endl;
                break;
            case 2:
                cout << "El promedio de su vector v es: " <<
                static_cast<double>(accumulate(vectorEntrada.begin(), vectorEntrada.end(), 0)) / vectorEntrada.size() << endl << endl;
                break;
            case 3:
                cout << "La moda de su vector v es: " << calcularModa(vectorEntrada) << endl << endl;
                break;
            case 4:
                cout << "Tiene " << vectorEntrada.size() << " elementos en su vector\n" << endl;
                break;
            case 5:
                if (archivoTexto.is_open()) {
                    cout << "El archivo ya existe!!\n" << endl;
                } else { 
                    crearArchivo(f);
                }
                break;
            case 6:
                if (!archivoTexto.is_open()) {
                    cout << "El archivo NO existe!!\n" << endl;
                } else {
                    agregarLineaArchivo(f, t);
                }
                break;
            case 7:
                if(archivoSalida.is_open()){
                    cout << "El archivo ya existe!!\n" << endl;
                } else {
                    procesarArchivo(i, o);
                }
                break;
            case 8:
                if (fs::is_directory(rutaOut)) {
                    fs::directory_iterator it(rutaOut);
                    if (it == fs::directory_iterator()) {
                        system(comandoPrepararDatos.c_str());
                    } else {
                        cout << "No puede sobreescribir en la carpeta!!." << endl;
                    }
                } else {
                    cout << "La ruta no es una carpeta válida. Revise su archivo .env!!" << endl;
                }
                break;
            case 9:
                if (fs::is_directory(rutaOut)) {
                    fs::directory_iterator it(rutaOut);
                    if ((it == fs::directory_iterator())) {
                        // Si la carpeta esta vacia, es porque no ha seleccionado la opcion 8 previamente
                        cout << "Debe ejecutar la opcion 8 primero!!" << endl;
                    } else {
                        system(comandoCrearIndice.c_str());
                    }
                } else {
                    cout << "La ruta no es una carpeta válida. Revise su archivo .env!!" << endl;
                }
                break;
        }
    } else {
        cout << "No tiene permiso para escoger la opcion " << eleccion << endl << endl;
    }
}

int obtenerEleccion() {
    int eleccion;
    cout << "Ingrese su eleccion: ";
    cin >> eleccion;
    cout << endl;
    return eleccion;
}

int calcularModa(const vector<int>& numeros) {
    vector<int> numerosOrdenados = numeros;
    sort(numerosOrdenados.begin(), numerosOrdenados.end());
    int moda = 0;
    int maxFrecuencia = 0;
    int currentFrecuencia = 1;

    for (size_t i = 1; i < numerosOrdenados.size(); i++) {
        if (numerosOrdenados[i] == numerosOrdenados[i - 1]) {
            currentFrecuencia++;
        } else {
            currentFrecuencia = 1;
        }

        if (currentFrecuencia > maxFrecuencia) {
            maxFrecuencia = currentFrecuencia;
            moda = numerosOrdenados[i];
        }
    }
    return moda;
}