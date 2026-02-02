#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <iomanip>
#include "clientes.h"

using namespace std;

string clientes[MAX_CLIENTES][CAMPOS_CLIENTE];
int totalClientes = 0;

string generarIDUnico() {
    string id;
    bool existe;
    do {
        id = "";
        for(int i=0;i<13;i++) id += to_string(rand()%10);
        existe = false;
        for(int j=0;j<totalClientes;j++){
            if(clientes[j][0]==id){ existe=true; break; }
        }
    } while(existe);
    return id;
}

bool existeCedula(const string& cedula){
    for(int i=0;i<totalClientes;i++)
        if(clientes[i][3]==cedula) return true;
    return false;
}

bool existeTelefono(const string& tel){
    for(int i=0;i<totalClientes;i++)
        if(clientes[i][4]==tel) return true;
    return false;
}

bool validarCedula(const string& cedula){
    return cedula.length()==10;
}

bool validarTelefono(const string& tel){
    return tel.length()==10;
}

bool validarCorreo(const string& correo){
    if(correo.length()<10) return false;
    string fin = correo.substr(correo.length()-10);
    return fin=="@gmail.com";
}

//  Lectura y guardado
void leerClientes(){
    ifstream archivo("clientes.csv");
    if(!archivo.is_open()) return;
    totalClientes=0;
    string linea;
    while(getline(archivo,linea)){
        int k=0;
        string temp="";
        for(char c:linea){
            if(c==','){ clientes[totalClientes][k++]=temp; temp=""; }
            else temp+=c;
        }
        clientes[totalClientes][k++]=temp;
        totalClientes++;
        if(totalClientes>=MAX_CLIENTES) break;
    }
    archivo.close();
}

void guardarClientes(){
    ofstream archivo("clientes.csv");
    for(int i=0;i<totalClientes;i++){
        for(int j=0;j<CAMPOS_CLIENTE;j++){
            archivo << clientes[i][j];
            if(j != CAMPOS_CLIENTE-1) archivo << ",";
        }
        archivo << "\n";
    }
    archivo.close();
}

// Crud 
void agregarCliente(){
    if(totalClientes>=MAX_CLIENTES){ cout<<"Limite de clientes alcanzado\n"; return; }
    clientes[totalClientes][0] = generarIDUnico();
    cin.ignore();

    cout<<"Nombre: "; getline(cin,clientes[totalClientes][1]);
    cout<<"Apellido: "; getline(cin,clientes[totalClientes][2]);

    string ced;
    do{
        cout<<"Cedula (10 digitos, unica): "; getline(cin,ced);
        if(!validarCedula(ced) || existeCedula(ced)) cout<<"Cedula invalida o repetida\n";
    }while(!validarCedula(ced) || existeCedula(ced));
    clientes[totalClientes][3]=ced;

    string tel;
    do{
        cout<<"Telefono (10 digitos, unico): "; getline(cin,tel);
        if(!validarTelefono(tel) || existeTelefono(tel)) cout<<"Telefono invalido o repetido\n";
    }while(!validarTelefono(tel) || existeTelefono(tel));
    clientes[totalClientes][4]=tel;

    string correo;
    do{
        cout<<"Correo (@gmail.com): "; getline(cin,correo);
        if(!validarCorreo(correo)) cout<<"Correo invalido\n";
    }while(!validarCorreo(correo));
    clientes[totalClientes][5]=correo;

    cout<<"Direccion: "; getline(cin,clientes[totalClientes][6]);

    string planes[6] = {"Basico","Estandar","Premium","Familiar","Corporativo","VIP"};
    int opcion;
    do{
        cout<<"Planes:\n";
        for(int i=0;i<6;i++) cout<<i+1<<". "<<planes[i]<<"\n";
        cout<<"Elige plan: "; cin>>opcion; cin.ignore();
    }while(opcion<1 || opcion>6);
    clientes[totalClientes][7]=planes[opcion-1];
    clientes[totalClientes][8]="Activo";

    totalClientes++;
    guardarClientes();
    cout<<"Cliente agregado correctamente\n";
}

void mostrarClientes(){
    if(totalClientes==0){ cout<<"No hay clientes registrados\n"; return; }
    cout << left 
         << setw(15) << "ID" 
         << setw(15) << "Nombre" 
         << setw(15) << "Apellido" 
         << setw(12) << "Cedula" 
         << setw(12) << "Telefono" 
         << setw(25) << "Correo" 
         << setw(25) << "Direccion" 
         << setw(15) << "Plan" 
         << setw(10) << "Estado" << "\n";
    cout << string(144,'-') << "\n";
    for(int i=0;i<totalClientes;i++){
        cout << left
             << setw(15) << clientes[i][0]
             << setw(15) << clientes[i][1]
             << setw(15) << clientes[i][2]
             << setw(12) << clientes[i][3]
             << setw(12) << clientes[i][4]
             << setw(25) << clientes[i][5]
             << setw(25) << clientes[i][6]
             << setw(15) << clientes[i][7]
             << setw(10) << clientes[i][8] << "\n";
    }
}

void actualizarCliente(){
    string ced;
    cin.ignore();
    cout<<"Cedula del cliente a actualizar: "; getline(cin,ced);
    for(int i=0;i<totalClientes;i++){
        if(clientes[i][3]==ced){
            int opcion;
            do{
                cout<<"1.Nombre 2.Apellido 3.Telefono 4.Correo 5.Direccion 6.Plan 7.Estado 0.Salir\nOpcion: ";
                cin>>opcion; cin.ignore();
                switch(opcion){
                    case 1: cout<<"Nuevo nombre: "; getline(cin,clientes[i][1]); break;
                    case 2: cout<<"Nuevo apellido: "; getline(cin,clientes[i][2]); break;
                    case 3:{
                        string tel;
                        do{ cout<<"Nuevo telefono: "; getline(cin,tel);
                            if(!validarTelefono(tel) || existeTelefono(tel)) cout<<"Telefono invalido o repetido\n";
                        }while(!validarTelefono(tel) || existeTelefono(tel));
                        clientes[i][4]=tel;
                        break;
                    }
                    case 4:{
                        string correo;
                        do{ cout<<"Nuevo correo: "; getline(cin,correo);
                            if(!validarCorreo(correo)) cout<<"Correo invalido\n";
                        }while(!validarCorreo(correo));
                        clientes[i][5]=correo;
                        break;
                    }
                    case 5: cout<<"Nueva direccion: "; getline(cin,clientes[i][6]); break;
                    case 6:{
                        string planes[6] = {"Basico","Estandar","Premium","Familiar","Corporativo","VIP"};
                        int opc;
                        do{
                            for(int k=0;k<6;k++) cout<<k+1<<". "<<planes[k]<<"\n";
                            cout<<"Nuevo plan: "; cin>>opc; cin.ignore();
                        }while(opc<1 || opc>6);
                        clientes[i][7]=planes[opc-1];
                        break;
                    }
                    case 7: cout<<"Nuevo estado: "; getline(cin,clientes[i][8]); break;
                }
            }while(opcion!=0);
            guardarClientes();
            cout<<"Cliente actualizado correctamente\n";
            return;
        }
    }
    cout<<"Cliente no encontrado\n";
}

void eliminarCliente(){
    string ced;
    cin.ignore();
    cout<<"Cedula del cliente a eliminar: "; getline(cin,ced);
    for(int i=0;i<totalClientes;i++){
        if(clientes[i][3]==ced){
            for(int j=i;j<totalClientes-1;j++)
                for(int k=0;k<CAMPOS_CLIENTE;k++)
                    clientes[j][k]=clientes[j+1][k];
            totalClientes--;
            guardarClientes();
            cout<<"Cliente eliminado\n";
            return;
        }
    }
    cout<<"Cliente no encontrado\n";
}

// Ordenamiento 
void intercambiarClientes(int a,int b){
    for(int k=0;k<CAMPOS_CLIENTE;k++){
        string tmp=clientes[a][k];
        clientes[a][k]=clientes[b][k];
        clientes[b][k]=tmp;
    }
}

void ordenarClientesPorID(){ for(int i=0;i<totalClientes-1;i++) for(int j=i+1;j<totalClientes;j++) if(clientes[i][0]>clientes[j][0]) intercambiarClientes(i,j);}
void ordenarClientesPorNombre(){ for(int i=0;i<totalClientes-1;i++) for(int j=i+1;j<totalClientes;j++) if(clientes[i][1]>clientes[j][1]) intercambiarClientes(i,j);}
void ordenarClientesPorApellido(){ for(int i=0;i<totalClientes-1;i++) for(int j=i+1;j<totalClientes;j++) if(clientes[i][2]>clientes[j][2]) intercambiarClientes(i,j);}
void ordenarClientesPorPlan(){ for(int i=0;i<totalClientes-1;i++) for(int j=i+1;j<totalClientes;j++) if(clientes[i][7]>clientes[j][7]) intercambiarClientes(i,j);}
void ordenarClientesPorEstado(){ for(int i=0;i<totalClientes-1;i++) for(int j=i+1;j<totalClientes;j++) if(clientes[i][8]>clientes[j][8]) intercambiarClientes(i,j);}

// Busqueda
void buscarCliente(){
    int opcion;
    do{
        cout<<"1.ID 2.Nombre 3.Apellido 4.Cedula 5.Telefono 6.Correo 7.Direccion 8.Plan 9.Estado 0.Salir\nOpcion: ";
        cin>>opcion; cin.ignore();
        switch(opcion){
            case 1:{ string id; cout<<"Ingrese ID: "; getline(cin,id);
                for(int i=0;i<totalClientes;i++) if(clientes[i][0]==id) cout<<clientes[i][1]<<" "<<clientes[i][2]<<" | Plan: "<<clientes[i][7]<<"\n"; break;}
            case 2:{ string nom; cout<<"Ingrese nombre: "; getline(cin,nom);
                for(int i=0;i<totalClientes;i++) if(clientes[i][1]==nom) cout<<clientes[i][0]<<" | "<<clientes[i][1]<<" "<<clientes[i][2]<<"\n"; break;}
            case 3:{ string ape; cout<<"Ingrese apellido: "; getline(cin,ape);
                for(int i=0;i<totalClientes;i++) if(clientes[i][2]==ape) cout<<clientes[i][0]<<" | "<<clientes[i][1]<<" "<<clientes[i][2]<<"\n"; break;}
            case 4:{ string ced; cout<<"Ingrese cedula: "; getline(cin,ced);
                for(int i=0;i<totalClientes;i++) if(clientes[i][3]==ced) cout<<clientes[i][0]<<" | "<<clientes[i][1]<<" "<<clientes[i][2]<<"\n"; break;}
            case 5:{ string tel; cout<<"Ingrese telefono: "; getline(cin,tel);
                for(int i=0;i<totalClientes;i++) if(clientes[i][4]==tel) cout<<clientes[i][0]<<" | "<<clientes[i][1]<<" "<<clientes[i][2]<<"\n"; break;}
            case 6:{ string corr; cout<<"Ingrese correo: "; getline(cin,corr);
                for(int i=0;i<totalClientes;i++) if(clientes[i][5]==corr) cout<<clientes[i][0]<<" | "<<clientes[i][1]<<"\n"; break;}
            case 7:{ string dir; cout<<"Ingrese direccion: "; getline(cin,dir);
                for(int i=0;i<totalClientes;i++) if(clientes[i][6]==dir) cout<<clientes[i][0]<<" | "<<clientes[i][1]<<"\n"; break;}
            case 8:{ string plan; cout<<"Ingrese plan: "; getline(cin,plan);
                for(int i=0;i<totalClientes;i++) if(clientes[i][7]==plan) cout<<clientes[i][0]<<" | "<<clientes[i][1]<<"\n"; break;}
            case 9:{ string est; cout<<"Ingrese estado: "; getline(cin,est);
                for(int i=0;i<totalClientes;i++) if(clientes[i][8]==est) cout<<clientes[i][0]<<" | "<<clientes[i][1]<<"\n"; break;}
        }
    }while(opcion!=0);
}

// Menu
void menuClientes(){
    leerClientes();
    int opcion;
    do{
        cout<<"1.Agregar\n2.Mostrar\n3.Buscar\n4.Actualizar\n5.Eliminar\n6.Ordenar\n0.Salir\nOpcion: ";
        cin>>opcion; cin.ignore();
        switch(opcion){
            case 1: agregarCliente(); break;
            case 2: mostrarClientes(); break;
            case 3: buscarCliente(); break;
            case 4: actualizarCliente(); break;
            case 5: eliminarCliente(); break;
            case 6:{
                int ord;
                cout<<"Ordenar por: 1.ID 2.Nombre 3.Apellido 4.Plan 5.Estado\nOpcion: "; cin>>ord; cin.ignore();
                switch(ord){
                    case 1: ordenarClientesPorID(); break;
                    case 2: ordenarClientesPorNombre(); break;
                    case 3: ordenarClientesPorApellido(); break;
                    case 4: ordenarClientesPorPlan(); break;
                    case 5: ordenarClientesPorEstado(); break;
                }
                break;
            }
        }
    }while(opcion!=0);
}

