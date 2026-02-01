#include "servicios.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

string servicios[MAX_SERVICIOS][10];
int totalServicios = 0;

void leerServicios(){
    ifstream archivo("data/servicios.csv");
    if(!archivo.is_open()) return;
    string linea;
    totalServicios=0;
    while(getline(archivo,linea)){
        stringstream ss(linea);
        for(int i=0;i<10;i++)
            getline(ss,servicios[totalServicios][i],',');
        totalServicios++;
    }
    archivo.close();
}

void guardarServicios(){
    ofstream archivo("data/servicios.csv");
    for(int i=0;i<totalServicios;i++){
        for(int j=0;j<10;j++){
            archivo<<servicios[i][j];
            if(j<9) archivo<<",";
        }
        archivo<<"\n";
    }
    archivo.close();
}

string generarIDServicio(){
    string id = "S";
    for(int i=0;i<12;i++) id += to_string(rand()%10);
    return id;
}

void agregarServicio(){
    string idCliente, nombre, descripcion, costo, estado, fecha, tipo, duracion;

    cout<<"ID Cliente: "; cin>>idCliente; cin.ignore();
    cout<<"Nombre Servicio: "; getline(cin,nombre);
    cout<<"Descripcion: "; getline(cin,descripcion);
    cout<<"Costo: "; cin>>costo; cin.ignore();
    cout<<"Estado (Activo/Inactivo): "; getline(cin,estado);
    cout<<"Fecha Contratacion (dd/mm/yyyy): "; getline(cin,fecha);
    cout<<"Tipo de Servicio: "; getline(cin,tipo);
    cout<<"Duracion Contrato (meses): "; getline(cin,duracion);

    string idServicio = generarIDServicio();

    servicios[totalServicios][0]=idServicio;
    servicios[totalServicios][1]=idCliente;
    servicios[totalServicios][2]=nombre;
    servicios[totalServicios][3]=descripcion;
    servicios[totalServicios][4]=costo;
    servicios[totalServicios][5]=estado;
    servicios[totalServicios][6]=fecha;
    servicios[totalServicios][7]=tipo;
    servicios[totalServicios][8]=duracion;
    servicios[totalServicios][9]="";

    totalServicios++;
    guardarServicios();
    cout<<"Servicio agregado correctamente.\n";
}

void mostrarServicios(){
    leerServicios();
    cout<<"\n=== Lista de Servicios ===\n";
    cout<<setw(15)<<"ID Servicio"<<setw(15)<<"ID Cliente"<<setw(20)<<"Nombre"
        <<setw(25)<<"Descripcion"<<setw(10)<<"Costo"<<setw(10)<<"Estado"
        <<setw(15)<<"Fecha"<<setw(15)<<"Tipo"<<setw(10)<<"Duracion"<<endl;

    int ancho[]={15,15,20,25,10,10,15,15,10,0};

    for(int i=0;i<totalServicios;i++){
        for(int j=0;j<9;j++)
            cout<<setw(ancho[j])<<servicios[i][j];
        cout<<endl;
    }
}

void menuServicios(){
    int op;
    do{
        cout<<"\n=== Menu Servicios ===\n";
        cout<<"1. Agregar Servicio\n2. Mostrar Servicios\n0. Salir\nOpcion: ";
        cin>>op;
        switch(op){
            case 1: agregarServicio(); break;
            case 2: mostrarServicios(); break;
        }
    }while(op!=0);
}

