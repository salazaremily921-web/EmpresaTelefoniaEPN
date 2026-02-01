#include "promociones.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

string promociones[100][10];
int totalPromociones = 0;

void leerPromociones(){
    ifstream archivo("data/promociones.csv");
    if(!archivo.is_open()) return;
    string linea;
    totalPromociones=0;
    while(getline(archivo,linea)){
        stringstream ss(linea);
        for(int i=0;i<10;i++)
            getline(ss,promociones[totalPromociones][i],',');
        totalPromociones++;
    }
    archivo.close();
}

void guardarPromociones(){
    ofstream archivo("data/promociones.csv");
    for(int i=0;i<totalPromociones;i++){
        for(int j=0;j<10;j++){
            archivo<<promociones[i][j];
            if(j<9) archivo<<",";
        }
        archivo<<"\n";
    }
    archivo.close();
}

string generarIDPromocion(){
    string id="P";
    for(int i=0;i<12;i++) id+=to_string(rand()%10);
    return id;
}

void agregarPromocion(){
    string nombre, descripcion, descuento, fechaInicio, fechaFin, plan, tipo, estado, observaciones;

    cin.ignore();
    cout<<"Nombre Promocion: "; getline(cin,nombre);
    cout<<"Descripcion: "; getline(cin,descripcion);
    cout<<"Descuento (%): "; cin>>descuento;
    cout<<"Fecha Inicio (dd/mm/yyyy): "; cin>>fechaInicio;
    cout<<"Fecha Fin (dd/mm/yyyy): "; cin>>fechaFin;
    cin.ignore();
    cout<<"Plan Asociado: "; getline(cin,plan);
    cout<<"Tipo (Temporal/Permanente/Especial): "; getline(cin,tipo);
    cout<<"Estado (Activa/Inactiva): "; getline(cin,estado);
    cout<<"Observaciones: "; getline(cin,observaciones);

    string idProm = generarIDPromocion();

    promociones[totalPromociones][0]=idProm;
    promociones[totalPromociones][1]=nombre;
    promociones[totalPromociones][2]=descripcion;
    promociones[totalPromociones][3]=descuento;
    promociones[totalPromociones][4]=fechaInicio;
    promociones[totalPromociones][5]=fechaFin;
    promociones[totalPromociones][6]=plan;
    promociones[totalPromociones][7]=tipo;
    promociones[totalPromociones][8]=estado;
    promociones[totalPromociones][9]=observaciones;

    totalPromociones++;
    guardarPromociones();
    cout<<"Promocion agregada correctamente.\n";
}

void mostrarPromociones(){
    leerPromociones();
    cout<<"\n=== Lista de Promociones ===\n";
    int ancho[]={15,20,25,10,15,15,15,15,12,25};
    cout<<setw(15)<<"ID Promocion"<<setw(20)<<"Nombre"<<setw(25)<<"Descripcion"
        <<setw(10)<<"Descuento"<<setw(15)<<"Inicio"<<setw(15)<<"Fin"
        <<setw(15)<<"Plan"<<setw(15)<<"Tipo"<<setw(12)<<"Estado"<<setw(25)<<"Observaciones"<<endl;

    for(int i=0;i<totalPromociones;i++){
        for(int j=0;j<10;j++) cout<<setw(ancho[j])<<promociones[i][j];
        cout<<endl;
    }
}

void buscarPromocionPlan(){
    string plan;
    cin.ignore();
    cout<<"Plan a buscar promociones: "; getline(cin,plan);
    leerPromociones();

    cout<<"\n=== Promociones del Plan ===\n";
    for(int i=0;i<totalPromociones;i++){
        if(promociones[i][6]==plan){
            cout<<"ID: "<<promociones[i][0]<<" | Nombre: "<<promociones[i][1]
                <<" | Descuento: "<<promociones[i][3]<<"% | Estado: "<<promociones[i][8]<<endl;
        }
    }
}

void menuPromociones(){
    int op;
    do{
        cout<<"\n=== Menu Promociones ===\n";
        cout<<"1. Agregar promocion\n2. Mostrar promociones\n3. Buscar promociones por plan\n0. Salir\nOpcion: ";
        cin>>op;
        switch(op){
            case 1: agregarPromocion(); break;
            case 2: mostrarPromociones(); break;
            case 3: buscarPromocionPlan(); break;
        }
    }while(op!=0);
}

