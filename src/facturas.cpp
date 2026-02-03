#include "facturas.h"
#include "clientes.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

string facturas[MAX_FACTURAS][CAMPOS_FACTURA];
int totalFacturas = 0;

string obtenerMontoPorPlan(string plan){
    if(plan=="Basico") return "10";
    if(plan=="Estandar") return "20";
    if(plan=="Premium") return "30";
    if(plan=="Familiar") return "40";
    if(plan=="Corporativo") return "50";
    if(plan=="VIP") return "70";
    return "0";
}

string generarIdFactura(){
    return "F" + to_string(1000 + totalFacturas + 1);
}

void leerFacturas(){
    ifstream archivo("facturas.csv");
    if(!archivo.is_open()) return;

    totalFacturas = 0;
    string linea;
    while(getline(archivo,linea)){
        int k = 0;
        string temp = "";
        for(char c : linea){
            if(c==','){
                facturas[totalFacturas][k++] = temp;
                temp = "";
            }else{
                temp += c;
            }
        }
        facturas[totalFacturas][k] = temp;
        totalFacturas++;
        if(totalFacturas >= MAX_FACTURAS) break;
    }
    archivo.close();
}

void guardarFacturas(){
    ofstream archivo("facturas.csv");
    for(int i=0;i<totalFacturas;i++){
        for(int j=0;j<CAMPOS_FACTURA;j++){
            archivo << facturas[i][j];
            if(j<CAMPOS_FACTURA-1) archivo << ",";
        }
        archivo << endl;
    }
    archivo.close();
}

void generarFacturaMensual(){
    leerClientes();

    if(totalClientes == 0){
        cout<<"No hay clientes registrados\n";
        return;
    }

    string mes, anio;
    cin.ignore();
    cout<<"Mes: "; getline(cin, mes);
    cout<<"Anio: "; getline(cin, anio);

    for(int i=0;i<totalClientes;i++){
        facturas[totalFacturas][0] = generarIdFactura();
        facturas[totalFacturas][1] = clientes[i][0];
        facturas[totalFacturas][2] = clientes[i][1] + " " + clientes[i][2];
        facturas[totalFacturas][3] = clientes[i][7];
        facturas[totalFacturas][4] = mes;
        facturas[totalFacturas][5] = anio;
        facturas[totalFacturas][6] = obtenerMontoPorPlan(clientes[i][7]);
        facturas[totalFacturas][7] = "Pendiente";
        totalFacturas++;
    }

    guardarFacturas();
    cout<<"Facturacion mensual generada correctamente\n";
}

void mostrarFacturas(){
    if(totalFacturas == 0){
        cout<<"No hay facturas registradas\n";
        return;
    }

    for(int i=0;i<totalFacturas;i++){
        cout<<"Id Factura : "<<facturas[i][0]<<endl;
        cout<<"Cliente    : "<<facturas[i][2]<<endl;
        cout<<"Plan       : "<<facturas[i][3]<<endl;
        cout<<"Mes        : "<<facturas[i][4]<<endl;
        cout<<"Anio       : "<<facturas[i][5]<<endl;
        cout<<"Monto      : $"<<facturas[i][6]<<endl;
        cout<<"Estado     : "<<facturas[i][7]<<endl;
    }
}

void eliminarFactura(){
    string id;
    cin.ignore();
    cout<<"Ingrese Id de factura a eliminar: ";
    getline(cin, id);

    for(int i=0;i<totalFacturas;i++){
        if(facturas[i][0] == id){
            for(int j=i;j<totalFacturas-1;j++){
                for(int k=0;k<CAMPOS_FACTURA;k++){
                    facturas[j][k] = facturas[j+1][k];
                }
            }
            totalFacturas--;
            guardarFacturas();
            cout<<"Factura eliminada correctamente\n";
            return;
        }
    }
    cout<<"Factura no encontrada\n";
}

void menuFacturas(){
    leerFacturas();
    int opcion;
    do{
        cout<<"\nMenu Facturas\n";
        cout<<"1. Agregar facturacion mensual\n";
        cout<<"2. Mostrar facturas\n";
        cout<<"3. Eliminar factura\n";
        cout<<"0. Salir\n";
        cout<<"Opcion: ";
        cin>>opcion;

        switch(opcion){
            case 1: generarFacturaMensual(); break;
            case 2: mostrarFacturas(); break;
            case 3: eliminarFactura(); break;
        }
    }while(opcion != 0);
}
void mostrarFacturasCliente(string cedula) {
    bool encontrado = false;

    for(int i=0;i<totalFacturas;i++){
        if(facturas[i][1] == cedula){
            cout << "\nFactura\n";
            cout << "Mes: " << facturas[i][4] << "\n";
            cout << "Anio: " << facturas[i][5] << "\n";
            cout << "Monto: $" << facturas[i][6] << "\n";
            cout << "Estado: " << facturas[i][7] << "\n";
            encontrado = true;
        }
    }

    if(!encontrado)
        cout << "No existen facturas registradas\n";
}

