#include "facturas.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

string facturas[MAX_FACTURAS][CAMPOS_FACTURA];
int totalFacturas = 0;

// csv
void leerFacturas() {
    ifstream archivo("facturas.csv");
    if (!archivo.is_open()) return;

    totalFacturas = 0;
    string linea;
    while (getline(archivo, linea)) {
        int k = 0; string temp = "";
        for (char c : linea) {
            if (c == ',') { facturas[totalFacturas][k++] = temp; temp = ""; }
            else temp += c;
        }
        facturas[totalFacturas][k++] = temp;
        totalFacturas++;
        if (totalFacturas >= MAX_FACTURAS) break;
    }
    archivo.close();
}

void guardarFacturas() {
    ofstream archivo("facturas.csv");
    for (int i = 0; i < totalFacturas; i++) {
        for (int j = 0; j < CAMPOS_FACTURA; j++) {
            archivo << facturas[i][j];
            if (j != CAMPOS_FACTURA - 1) archivo << ",";
        }
        archivo << "\n";
    }
    archivo.close();
}

// crud
string generarIDFactura() {
    return "F" + to_string(1000 + totalFacturas);
}

void agregarFactura() {
    if (totalFacturas >= MAX_FACTURAS) { cout << "Limite de facturas alcanzado\n"; return; }

    cin.ignore();
    cout << "Cliente: "; getline(cin, facturas[totalFacturas][1]);
    cout << "Linea: "; getline(cin, facturas[totalFacturas][2]);
    cout << "Mes: "; getline(cin, facturas[totalFacturas][3]);
    cout << "Año: "; getline(cin, facturas[totalFacturas][4]);
    cout << "Monto: "; getline(cin, facturas[totalFacturas][5]);
    cout << "Estado (Pendiente/Facturada): "; getline(cin, facturas[totalFacturas][6]);
    cout << "Observaciones: "; getline(cin, facturas[totalFacturas][7]);

    facturas[totalFacturas][0] = generarIDFactura();

    totalFacturas++;
    guardarFacturas();
    cout << "Factura agregada correctamente.\n";
}

void mostrarFacturas() {
    if (totalFacturas == 0) { cout << "No hay facturas registradas\n"; return; }

    cout << setw(6) << "ID" << setw(12) << "Cliente" << setw(10) << "Linea"
         << setw(6) << "Mes" << setw(6) << "Año" << setw(8) << "Monto"
         << setw(12) << "Estado" << setw(20) << "Observaciones" << endl;

    for (int i = 0; i < totalFacturas; i++) {
        for (int j = 0; j < CAMPOS_FACTURA; j++)
            cout << setw( (j==7)?20:10 ) << facturas[i][j];
        cout << "\n";
    }
}

void actualizarFactura() {
    string id; cout << "ID de factura a actualizar: "; cin.ignore(); getline(cin, id);
    for (int i = 0; i < totalFacturas; i++) {
        if (facturas[i][0] == id) {
            int opcion;
            do {
                cout << "1.Cliente 2.Linea 3.Mes 4.Año 5.Monto 6.Estado 7.Observaciones 0.Salir\nOpcion: ";
                cin >> opcion; cin.ignore();
                switch(opcion){
                    case 1: cout<<"Nuevo cliente: "; getline(cin,facturas[i][1]); break;
                    case 2: cout<<"Nueva linea: "; getline(cin,facturas[i][2]); break;
                    case 3: cout<<"Nuevo mes: "; getline(cin,facturas[i][3]); break;
                    case 4: cout<<"Nuevo año: "; getline(cin,facturas[i][4]); break;
                    case 5: cout<<"Nuevo monto: "; getline(cin,facturas[i][5]); break;
                    case 6: cout<<"Nuevo estado: "; getline(cin,facturas[i][6]); break;
                    case 7: cout<<"Nueva observacion: "; getline(cin,facturas[i][7]); break;
                }
            } while(opcion != 0);
            guardarFacturas();
            cout<<"Factura actualizada\n"; return;
        }
    }
    cout<<"Factura no encontrada\n";
}

void eliminarFactura() {
    string id; cout << "ID de factura a eliminar: "; cin.ignore(); getline(cin,id);
    for (int i=0;i<totalFacturas;i++){
        if(facturas[i][0]==id){
            for(int j=i;j<totalFacturas-1;j++)
                for(int k=0;k<CAMPOS_FACTURA;k++)
                    facturas[j][k]=facturas[j+1][k];
            totalFacturas--;
            guardarFacturas();
            cout<<"Factura eliminada\n"; return;
        }
    }
    cout<<"Factura no encontrada\n";
}

void facturarMes(const string& mes, const string& anio){
    for(int i=0;i<totalFacturas;i++)
        if(facturas[i][3]==mes && facturas[i][4]==anio)
            facturas[i][6] = "Facturada";
    cout<<"Facturas del mes "<<mes<<" del año "<<anio<<" procesadas.\n";
    guardarFacturas();
}

// busquedas
void buscarFacturaPorID(){ string id; cout<<"ID: "; getline(cin,id); for(int i=0;i<totalFacturas;i++) if(facturas[i][0]==id) cout<<facturas[i][0]<<" | "<<facturas[i][1]<<" | "<<facturas[i][2]<<" | "<<facturas[i][5]<<" | "<<facturas[i][6]<<"\n";}
void buscarFacturaPorCliente(){ string c; cout<<"Cliente: "; getline(cin,c); for(int i=0;i<totalFacturas;i++) if(facturas[i][1]==c) cout<<facturas[i][0]<<" | "<<facturas[i][1]<<" | "<<facturas[i][2]<<" | "<<facturas[i][5]<<" | "<<facturas[i][6]<<"\n";}
void buscarFacturaPorLinea(){ string l; cout<<"Linea: "; getline(cin,l); for(int i=0;i<totalFacturas;i++) if(facturas[i][2]==l) cout<<facturas[i][0]<<" | "<<facturas[i][1]<<" | "<<facturas[i][2]<<" | "<<facturas[i][5]<<" | "<<facturas[i][6]<<"\n";}
void buscarFacturaPorMes(){ string m; cout<<"Mes: "; getline(cin,m); for(int i=0;i<totalFacturas;i++) if(facturas[i][3]==m) cout<<facturas[i][0]<<" | "<<facturas[i][1]<<" | "<<facturas[i][3]<<" | "<<facturas[i][5]<<" | "<<facturas[i][6]<<"\n";}
void buscarFacturaPorAnio(){ string a; cout<<"Año: "; getline(cin,a); for(int i=0;i<totalFacturas;i++) if(facturas[i][4]==a) cout<<facturas[i][0]<<" | "<<facturas[i][1]<<" | "<<facturas[i][4]<<" | "<<facturas[i][5]<<" | "<<facturas[i][6]<<"\n";}
void buscarFacturaPorMonto(){ string mo; cout<<"Monto: "; getline(cin,mo); for(int i=0;i<totalFacturas;i++) if(facturas[i][5]==mo) cout<<facturas[i][0]<<" | "<<facturas[i][1]<<" | "<<facturas[i][5]<<" | "<<facturas[i][6]<<"\n";}
void buscarFacturaPorEstado(){ string e; cout<<"Estado: "; getline(cin,e); for(int i=0;i<totalFacturas;i++) if(facturas[i][6]==e) cout<<facturas[i][0]<<" | "<<facturas[i][1]<<" | "<<facturas[i][6]<<" | "<<facturas[i][5]<<"\n";}
void buscarFacturaPorObservaciones(){ string o; cout<<"Obs: "; getline(cin,o); for(int i=0;i<totalFacturas;i++) if(facturas[i][7]==o) cout<<facturas[i][0]<<" | "<<facturas[i][1]<<" | "<<facturas[i][7]<<"\n";}
void buscarFacturaPorCualquierCampo(){ string b; cout<<"Buscar: "; getline(cin,b); for(int i=0;i<totalFacturas;i++) for(int j=0;j<CAMPOS_FACTURA;j++) if(facturas[i][j]==b) cout<<facturas[i][0]<<" | "<<facturas[i][1]<<" | "<<facturas[i][2]<<"\n";}

void buscarFactura() {
    int opcion;
    do{
        cout<<"\n Menu Busqueda Facturas \n1.ID 2.Cliente 3.Linea 4.Mes 5.Año 6.Monto 7.Estado 8.Observaciones 9.CualquierCampo 0.Salir\nOpcion: ";
        cin>>opcion; cin.ignore();
        switch(opcion){
            case 1: buscarFacturaPorID(); break;
            case 2: buscarFacturaPorCliente(); break;
            case 3: buscarFacturaPorLinea(); break;
            case 4: buscarFacturaPorMes(); break;
            case 5: buscarFacturaPorAnio(); break;
            case 6: buscarFacturaPorMonto(); break;
            case 7: buscarFacturaPorEstado(); break;
            case 8: buscarFacturaPorObservaciones(); break;
            case 9: buscarFacturaPorCualquierCampo(); break;
        }
    } while(opcion!=0);
}

// ordenamientos
void intercambiarFacturas(int a,int b){ for(int k=0;k<CAMPOS_FACTURA;k++){ string tmp=facturas[a][k]; facturas[a][k]=facturas[b][k]; facturas[b][k]=tmp; } }
void ordenarFacturasPorID(){ for(int i=0;i<totalFacturas-1;i++) for(int j=i+1;j<totalFacturas;j++) if(facturas[i][0]>facturas[j][0]) intercambiarFacturas(i,j);}
void ordenarFacturasPorCliente(){ for(int i=0;i<totalFacturas-1;i++) for(int j=i+1;j<totalFacturas;j++) if(facturas[i][1]>facturas[j][1]) intercambiarFacturas(i,j);}
void ordenarFacturasPorLinea(){ for(int i=0;i<totalFacturas-1;i++) for(int j=i+1;j<totalFacturas;j++) if(facturas[i][2]>facturas[j][2]) intercambiarFacturas(i,j);}
void ordenarFacturasPorMes(){ for(int i=0;i<totalFacturas-1;i++) for(int j=i+1;j<totalFacturas;j++) if(facturas[i][3]>facturas[j][3]) intercambiarFacturas(i,j);}
void ordenarFacturasPorMonto(){ for(int i=0;i<totalFacturas-1;i++) for(int j=i+1;j<totalFacturas;j++) if(facturas[i][5]>facturas[j][5]) intercambiarFacturas(i,j); }

// menu
void menuFacturas() {
    leerFacturas();
    int opcion;
    do {
        cout<<"\n Menu Facturas \n1.Agregar 2.Mostrar 3.Actualizar 4.Eliminar 5.Facturar Mes 6.Buscar 7.Ordenar 0.Salir\nOpcion: ";
        cin >> opcion; cin.ignore();
        switch(opcion){
            case 1: agregarFactura(); break;
            case 2: mostrarFacturas(); break;
            case 3: actualizarFactura(); break;
            case 4: eliminarFactura(); break;
            case 5: { string mes, anio; cout<<"Mes: "; getline(cin,mes); cout<<"Año: "; getline(cin,anio); facturarMes(mes,anio); break;}
            case 6: buscarFactura(); break;
            case 7: {
                int ord; 
                cout<<"Ordenar por: 1.ID 2.Cliente 3.Linea 4.Mes 5.Monto\nOpcion: "; cin>>ord; cin.ignore();
                switch(ord){
                    case 1: ordenarFacturasPorID(); break;
                    case 2: ordenarFacturasPorCliente(); break;
                    case 3: ordenarFacturasPorLinea(); break;
                    case 4: ordenarFacturasPorMes(); break;
                    case 5: ordenarFacturasPorMonto(); break;
                }
                break;
            }
        }
    } while(opcion != 0);
}

