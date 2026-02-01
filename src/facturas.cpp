#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include "facturas.h"
#include "clientes.h"
#include "servicios.h"

using namespace std;

string facturas[100][9];
int totalFacturas = 0;

extern string clientes[100][10];
extern int totalClientes;

void leerFacturas() {
    ifstream archivo("facturas.csv");
    if(!archivo.is_open()) return;
    string linea;
    totalFacturas=0;
    while(getline(archivo,linea)){
        stringstream ss(linea);
        for(int i=0;i<9;i++){
            getline(ss,facturas[totalFacturas][i],',');
        }
        totalFacturas++;
    }
    archivo.close();
}

void guardarFacturas() {
    ofstream archivo("facturas.csv");
    for(int i=0;i<totalFacturas;i++){
        for(int j=0;j<9;j++){
            archivo<<facturas[i][j];
            if(j<8) archivo<<",";
        }
        archivo<<"\n";
    }
    archivo.close();
}

string generarIDFactura() {
    string id="F";
    for(int i=0;i<12;i++){
        id += to_string(rand()%10);
    }
    return id;
}

void facturarMes(string mes){
    leerFacturas();
    for(int i=0;i<totalClientes;i++){
        if(clientes[i][8]=="Activo"){
            string serviciosCliente="";
            double montoTotal=0;

            for(int j=0;j<100;j++){ // ajusta según totalServicios si quieres
                // aquí normalmente sumarías servicios activos
            }

            if(clientes[i][6]=="Plan Básico") montoTotal+=10;
            else if(clientes[i][6]=="Plan Estándar") montoTotal+=20;
            else if(clientes[i][6]=="Plan Premium") montoTotal+=30;
            else if(clientes[i][6]=="Plan Oro") montoTotal+=40;
            else if(clientes[i][6]=="Plan Platino") montoTotal+=50;

            string idFactura = generarIDFactura();
            facturas[totalFacturas][0]=idFactura;
            facturas[totalFacturas][1]=clientes[i][0];
            facturas[totalFacturas][2]=clientes[i][1];
            facturas[totalFacturas][3]=clientes[i][2];
            facturas[totalFacturas][4]=clientes[i][6];
            facturas[totalFacturas][5]=to_string(montoTotal);
            facturas[totalFacturas][6]=serviciosCliente;
            facturas[totalFacturas][7]=mes;
            facturas[totalFacturas][8]="Pendiente";

            totalFacturas++;
        }
    }
    guardarFacturas();
    cout<<"Facturacion mensual completada para "<<totalClientes<<" clientes.\n";
}

void mostrarFacturas(){
    leerFacturas();
    cout<<"\n=== Lista de Facturas ===\n";
    cout<<setw(15)<<"ID"<<setw(15)<<"Nombre"<<setw(15)<<"Apellido"<<setw(15)<<"Plan"
        <<setw(10)<<"Monto"<<setw(40)<<"Servicios"<<setw(12)<<"Mes"<<setw(12)<<"Estado"<<endl;
    for(int i=0;i<totalFacturas;i++){
        cout<<setw(15)<<facturas[i][0]<<setw(15)<<facturas[i][2]<<setw(15)<<facturas[i][3]
            <<setw(15)<<facturas[i][4]<<setw(10)<<facturas[i][5]<<setw(40)<<facturas[i][6]
            <<setw(12)<<facturas[i][7]<<setw(12)<<facturas[i][8]<<endl;
    }
}

void actualizarEstadoFactura(){
    leerFacturas();
    string id;
    cout<<"Ingrese ID de factura a actualizar: "; cin>>id;
    for(int i=0;i<totalFacturas;i++){
        if(facturas[i][0]==id){
            cout<<"Estado actual: "<<facturas[i][8]<<"\n";
            cout<<"Ingrese nuevo estado (Pendiente/Pagado): ";
            cin>>facturas[i][8];
            guardarFacturas();
            cout<<"Factura actualizada.\n";
            return;
        }
    }
    cout<<"Factura no encontrada.\n";
}

void menuFacturas(){
    int op;
    do{
        cout<<"\n=== Menu Facturas ===\n";
        cout<<"1. Facturar mes\n";
        cout<<"2. Mostrar facturas\n";
        cout<<"3. Actualizar estado factura\n";
        cout<<"0. Salir\n";
        cout<<"Opcion: "; cin>>op;
        switch(op){
            case 1: {
                string mes;
                cout<<"Mes a facturar: ";
                cin>>mes;
                facturarMes(mes);
                break;
            }
            case 2: mostrarFacturas(); break;
            case 3: actualizarEstadoFactura(); break;
        }
    }while(op!=0);
}

