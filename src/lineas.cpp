#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

const int MAX_LINEAS = 100;
const int CAMPOS = 9;
string lineas[MAX_LINEAS][CAMPOS];
int totalLineas = 0;


string generarIDLinea() {
    string id = "L";
    for (int i = 0; i < 12; i++)
        id += to_string(rand() % 10);
    return id;
}


bool validarNumeroLinea(const string& num){
    return num.length()==10;
}


void leerLineas() {
    ifstream archivo("lineas.csv");
    if (!archivo.is_open()) return;

    totalLineas = 0;
    string linea;
    while (getline(archivo, linea)) {
        int k = 0; string temp = "";
        for (char c : linea) {
            if (c == ',') { lineas[totalLineas][k++] = temp; temp = ""; }
            else temp += c;
        }
        lineas[totalLineas][k++] = temp;
        totalLineas++;
        if (totalLineas >= MAX_LINEAS) break;
    }
    archivo.close();
}


void guardarLineas() {
    ofstream archivo("lineas.csv");
    for (int i = 0; i < totalLineas; i++) {
        for (int j = 0; j < CAMPOS; j++) {
            archivo << lineas[i][j];
            if (j != CAMPOS - 1) archivo << ",";
        }
        archivo << "\n";
    }
    archivo.close();
}


void agregarLinea() {
    if (totalLineas >= MAX_LINEAS) { cout << "Limite de lineas alcanzado\n"; return; }

    cin.ignore();
    lineas[totalLineas][0] = generarIDLinea();

    cout << "Cliente asociado: "; getline(cin, lineas[totalLineas][1]);

    string numero;
    do{
        cout << "Numero de linea (10 digitos): "; getline(cin, numero);
        if(!validarNumeroLinea(numero)) cout << "Numero invalido\n";
    } while(!validarNumeroLinea(numero));
    lineas[totalLineas][2] = numero;

    cout << "Plan: "; getline(cin, lineas[totalLineas][3]);
    cout << "Estado (Activo/Inactivo): "; getline(cin, lineas[totalLineas][4]);
    cout << "Tipo (Prepago/Postpago): "; getline(cin, lineas[totalLineas][5]);
    cout << "Fecha de activacion (dd/mm/yyyy): "; getline(cin, lineas[totalLineas][6]);
    cout << "Observaciones: "; getline(cin, lineas[totalLineas][7]);
    lineas[totalLineas][8] = "";

    totalLineas++;
    guardarLineas();
    cout << "Linea agregada correctamente.\n";
}


void mostrarLineas() {
    if (totalLineas == 0) { cout << "No hay lineas registradas\n"; return; }

    cout << setw(15) << "ID" << setw(20) << "Cliente" << setw(15) << "Numero"
         << setw(15) << "Plan" << setw(10) << "Estado" << setw(15) << "Tipo"
         << setw(15) << "Fecha" << setw(25) << "Observaciones" << endl;

    for (int i = 0; i < totalLineas; i++) {
        for (int j = 0; j < CAMPOS; j++) {
            int ancho;
            switch(j){ case 0: ancho=15; break; case 1: ancho=20; break; case 2: ancho=15; break; 
                       case 3: ancho=15; break; case 4: ancho=10; break; case 5: ancho=15; break; 
                       case 6: ancho=15; break; default: ancho=25;}
            cout << setw(ancho) << lineas[i][j];
        }
        cout << endl;
    }
}


void actualizarLinea() {
    string id; cout << "ID de linea a actualizar: "; cin.ignore(); getline(cin, id);

    for (int i = 0; i < totalLineas; i++) {
        if (lineas[i][0] == id) {
            int opcion;
            do {
                cout << "\n Actualizar Linea \n";
                cout << "1. Cliente\n2. Numero\n3. Plan\n4. Estado\n5. Tipo\n6. Fecha\n7. Observaciones\n0. Salir\n";
                cout << "Opcion: "; cin >> opcion; cin.ignore();
                switch (opcion){
                    case 1: cout << "Nuevo cliente: "; getline(cin, lineas[i][1]); break;
                    case 2: {
                        string numero;
                        do{
                            cout << "Nuevo numero: "; getline(cin, numero);
                            if(!validarNumeroLinea(numero)) cout << "Numero invalido\n";
                        } while(!validarNumeroLinea(numero));
                        lineas[i][2] = numero;
                        break;
                    }
                    case 3: cout << "Nuevo plan: "; getline(cin, lineas[i][3]); break;
                    case 4: cout << "Nuevo estado: "; getline(cin, lineas[i][4]); break;
                    case 5: cout << "Nuevo tipo: "; getline(cin, lineas[i][5]); break;
                    case 6: cout << "Nueva fecha: "; getline(cin, lineas[i][6]); break;
                    case 7: cout << "Nuevas observaciones: "; getline(cin, lineas[i][7]); break;
                    case 0: cout << "Actualizacion finalizada\n"; break;
                    default: cout << "Opcion invalida\n";
                }
            } while (opcion != 0);
            guardarLineas();
            return;
        }
    }
    cout << "Linea no encontrada\n";
}


void eliminarLinea() {
    string id; cout << "ID de linea a eliminar: "; cin.ignore(); getline(cin, id);

    for (int i = 0; i < totalLineas; i++) {
        if (lineas[i][0] == id) {
            for (int j = i; j < totalLineas - 1; j++)
                for (int k = 0; k < CAMPOS; k++)
                    lineas[j][k] = lineas[j+1][k];
            totalLineas--;
            guardarLineas();
            cout << "Linea eliminada\n"; return;
        }
    }
    cout << "Linea no encontrada\n";
}


void buscarLineaPorID() { string id; cout << "Ingrese ID: "; cin.ignore(); getline(cin,id); bool f=false; for(int i=0;i<totalLineas;i++){ if(lineas[i][0]==id){ cout<<lineas[i][0]<<" | "<<lineas[i][1]<<" | "<<lineas[i][2]<<" | "<<lineas[i][3]<<"\n"; f=true; } } if(!f) cout<<"No se encontro.\n";}
void buscarLineaPorCliente() { string c; cout << "Ingrese Cliente: "; cin.ignore(); getline(cin,c); bool f=false; for(int i=0;i<totalLineas;i++){ if(lineas[i][1]==c){ cout<<lineas[i][0]<<" | "<<lineas[i][1]<<" | "<<lineas[i][2]<<"\n"; f=true;} } if(!f) cout<<"No se encontro.\n";}
void buscarLineaPorNumero() { string n; cout << "Ingrese Numero: "; cin.ignore(); getline(cin,n); bool f=false; for(int i=0;i<totalLineas;i++){ if(lineas[i][2]==n){ cout<<lineas[i][0]<<" | "<<lineas[i][1]<<" | "<<lineas[i][2]<<"\n"; f=true;} } if(!f) cout<<"No se encontro.\n";}
void buscarLineaPorPlan() { string p; cout << "Ingrese Plan: "; cin.ignore(); getline(cin,p); bool f=false; for(int i=0;i<totalLineas;i++){ if(lineas[i][3]==p){ cout<<lineas[i][0]<<" | "<<lineas[i][1]<<" | "<<lineas[i][3]<<"\n"; f=true;} } if(!f) cout<<"No se encontro.\n";}
void buscarLineaPorEstado() { string e; cout << "Ingrese Estado: "; cin.ignore(); getline(cin,e); bool f=false; for(int i=0;i<totalLineas;i++){ if(lineas[i][4]==e){ cout<<lineas[i][0]<<" | "<<lineas[i][1]<<" | "<<lineas[i][4]<<"\n"; f=true;} } if(!f) cout<<"No se encontro.\n";}
void buscarLineaPorTipo() { string t; cout << "Ingrese Tipo (Prepago/Postpago): "; cin.ignore(); getline(cin,t); bool f=false; for(int i=0;i<totalLineas;i++){ if(lineas[i][5]==t){ cout<<lineas[i][0]<<" | "<<lineas[i][1]<<" | "<<lineas[i][5]<<"\n"; f=true;} } if(!f) cout<<"No se encontro.\n";}
void buscarLineaPorFecha() { string fch; cout << "Ingrese Fecha (dd/mm/yyyy): "; cin.ignore(); getline(cin,fch); bool f=false; for(int i=0;i<totalLineas;i++){ if(lineas[i][6]==fch){ cout<<lineas[i][0]<<" | "<<lineas[i][1]<<" | "<<lineas[i][6]<<"\n"; f=true;} } if(!f) cout<<"No se encontro.\n";}


void intercambiarFilasLinea(int a, int b){ for(int k=0;k<CAMPOS;k++){ string t=lineas[a][k]; lineas[a][k]=lineas[b][k]; lineas[b][k]=t;}}
void ordenarLineasPorID(){ for(int i=0;i<totalLineas-1;i++) for(int j=i+1;j<totalLineas;j++) if(lineas[i][0]>lineas[j][0]) intercambiarFilasLinea(i,j); guardarLineas();}
void ordenarLineasPorNumero(){ for(int i=0;i<totalLineas-1;i++) for(int j=i+1;j<totalLineas;j++) if(lineas[i][2]>lineas[j][2]) intercambiarFilasLinea(i,j); guardarLineas();}
void ordenarLineasPorPlan(){ for(int i=0;i<totalLineas-1;i++) for(int j=i+1;j<totalLineas;j++) if(lineas[i][3]>lineas[j][3]) intercambiarFilasLinea(i,j); guardarLineas();}
void ordenarLineasPorEstado(){ for(int i=0;i<totalLineas-1;i++) for(int j=i+1;j<totalLineas;j++) if(lineas[i][4]>lineas[j][4]) intercambiarFilasLinea(i,j); guardarLineas();}
void ordenarLineasPorFecha(){ for(int i=0;i<totalLineas-1;i++) for(int j=i+1;j<totalLineas;j++) if(lineas[i][6]>lineas[j][6]) intercambiarFilasLinea(i,j); guardarLineas();}


void menuLineas() {
    leerLineas();
    int opcion;
    do {
        cout<<"\n=== Menu Lineas ===\n1.Agregar 2.Mostrar 3.Actualizar 4.Eliminar 5.Buscar 6.Ordenar 0.Volver\nOpcion: ";
        cin>>opcion;
        switch(opcion){
            case 1: agregarLinea(); break;
            case 2: mostrarLineas(); break;
            case 3: actualizarLinea(); break;
            case 4: eliminarLinea(); break;
            case 5: {
                int b; 
                cout<<"Buscar por: 1.ID 2.Cliente 3.Numero 4.Plan 5.Estado 6.Tipo 7.Fecha\nOpcion: "; cin>>b;
                switch(b){
                    case 1: buscarLineaPorID(); break;
                    case 2: buscarLineaPorCliente(); break;
                    case 3: buscarLineaPorNumero(); break;
                    case 4: buscarLineaPorPlan(); break;
                    case 5: buscarLineaPorEstado(); break;
                    case 6: buscarLineaPorTipo(); break;
                    case 7: buscarLineaPorFecha(); break;
                } 
                break; 
            }
            case 6: {
                int o; 
                cout<<"Ordenar por: 1.ID 2.Numero 3.Plan 4.Estado 5.Fecha\nOpcion: "; cin>>o;
                switch(o){
                    case 1: ordenarLineasPorID(); break;
                    case 2: ordenarLineasPorNumero(); break;
                    case 3: ordenarLineasPorPlan(); break;
                    case 4: ordenarLineasPorEstado(); break;
                    case 5: ordenarLineasPorFecha(); break;
                } 
                break; 
            }
            case 0: break;
            default: cout<<"Opcion invalida\n";
        }
    } while(opcion!=0);
}

