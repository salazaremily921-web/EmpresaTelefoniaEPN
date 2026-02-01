#include "lineas.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

string lineas[100][10];
int totalLineas = 0;

void leerLineas(){
    ifstream archivo("data/lineas.csv");
    if(!archivo.is_open()) return;
    string linea;
    totalLineas = 0;
    while(getline(archivo, linea)){
        stringstream ss(linea);
        for(int i=0;i<10;i++)
            getline(ss, lineas[totalLineas][i], ',');
        totalLineas++;
    }
    archivo.close();
}

void guardarLineas(){
    ofstream archivo("data/lineas.csv");
    for(int i=0;i<totalLineas;i++){
        for(int j=0;j<10;j++){
            archivo<<lineas[i][j];
            if(j<9) archivo<<",";
        }
        archivo<<"\n";
    }
    archivo.close();
}

string generarIDLinea(){
    string id = "L";
    for(int i=0;i<12;i++) id += to_string(rand()%10);
    return id;
}

void agregarLinea(){
    string idCliente, numero, operador, plan, estado, fecha, tipo, uso, observaciones;

    cout<<"ID Cliente: "; cin>>idCliente;
    cout<<"Numero de telefono (10 digitos): "; cin>>numero; cin.ignore();
    cout<<"Operador: "; getline(cin, operador);
    cout<<"Plan Contratado: "; getline(cin, plan);
    cout<<"Estado (Activo/Inactivo/Suspendido): "; getline(cin, estado);
    cout<<"Fecha Activacion (dd/mm/yyyy): "; getline(cin, fecha);
    cout<<"Tipo de Linea (Prepago/Postpago): "; getline(cin, tipo);
    cout<<"Uso Mensual (minutos/MB/SMS): "; getline(cin, uso);
    cout<<"Observaciones: "; getline(cin, observaciones);

    string idLinea = generarIDLinea();

    lineas[totalLineas][0] = idLinea;
    lineas[totalLineas][1] = idCliente;
    lineas[totalLineas][2] = numero;
    lineas[totalLineas][3] = operador;
    lineas[totalLineas][4] = plan;
    lineas[totalLineas][5] = estado;
    lineas[totalLineas][6] = fecha;
    lineas[totalLineas][7] = tipo;
    lineas[totalLineas][8] = uso;
    lineas[totalLineas][9] = observaciones;

    totalLineas++;
    guardarLineas();
    cout<<"Linea agregada correctamente.\n";
}

void mostrarLineas(){
    leerLineas();
    cout<<"\n=== Lista de Lineas ===\n";
    cout<<setw(15)<<"ID Linea"<<setw(15)<<"ID Cliente"<<setw(15)<<"Numero"
        <<setw(15)<<"Operador"<<setw(15)<<"Plan"<<setw(12)<<"Estado"
        <<setw(15)<<"Fecha"<<setw(15)<<"Tipo"<<setw(20)<<"Uso Mensual"
        <<setw(25)<<"Observaciones"<<endl;

    int ancho[]={15,15,15,15,15,12,15,15,20,25};

    for(int i=0;i<totalLineas;i++){
        for(int j=0;j<10;j++)
            cout<<setw(ancho[j])<<lineas[i][j];
        cout<<endl;
    }
}

void buscarLineasCliente(){
    string idCliente;
    cout<<"ID Cliente a buscar lineas: "; cin>>idCliente;
    leerLineas();

    cout<<"\n=== Lineas del Cliente ===\n";
    for(int i=0;i<totalLineas;i++){
        if(lineas[i][1]==idCliente){
            cout<<"ID Linea: "<<lineas[i][0]<<" | Numero: "<<lineas[i][2]
                <<" | Plan: "<<lineas[i][4]<<" | Estado: "<<lineas[i][5]
                <<" | Observaciones: "<<lineas[i][9]<<endl;
        }
    }
}

void menuLineas(){
    int op;
    do{
        cout<<"\n=== Menu Lineas Celular ===\n";
        cout<<"1. Agregar linea\n2. Mostrar lineas\n3. Buscar lineas por cliente\n0. Salir\nOpcion: ";
        cin>>op;
        switch(op){
            case 1: agregarLinea(); break;
            case 2: mostrarLineas(); break;
            case 3: buscarLineasCliente(); break;
        }
    }while(op!=0);
}

