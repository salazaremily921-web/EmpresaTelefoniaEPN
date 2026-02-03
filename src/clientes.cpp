#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <ctime>
#include "clientes.h"

using namespace std;

string clientes[MAX_CLIENTES][CAMPOS_CLIENTE];
int totalClientes = 0;

string generarIDUnico(){
    string id;
    bool existe;
    do{
        id="";
        for(int i=0;i<13;i++) id+=to_string(rand()%10);
        existe=false;
        for(int j=0;j<totalClientes;j++)
            if(clientes[j][0]==id) existe=true;
    }while(existe);
    return id;
}

bool validarCedula(string c){ return c.length()==10; }
bool validarTelefono(string t){ return t.length()==10; }
bool validarCorreo(string c){
    if(c.length()<10) return false;
    return c.substr(c.length()-10)=="@gmail.com";
}

bool existeCedula(string c){
    for(int i=0;i<totalClientes;i++)
        if(clientes[i][3]==c) return true;
    return false;
}

bool existeTelefono(string t){
    for(int i=0;i<totalClientes;i++)
        if(clientes[i][4]==t) return true;
    return false;
}

void leerClientes(){
    ifstream archivo("clientes.csv");
    if(!archivo.is_open()) return;
    totalClientes=0;
    string linea;
    while(getline(archivo,linea)){
        int k=0;
        string temp="";
        for(char c:linea){
            if(c==','){
                clientes[totalClientes][k++]=temp;
                temp="";
            }else temp+=c;
        }
        clientes[totalClientes][k]=temp;
        totalClientes++;
    }
    archivo.close();
}

void guardarClientes(){
    ofstream archivo("clientes.csv");
    for(int i=0;i<totalClientes;i++){
        for(int j=0;j<CAMPOS_CLIENTE;j++){
            archivo<<clientes[i][j];
            if(j<CAMPOS_CLIENTE-1) archivo<<",";
        }
        archivo<<"\n";
    }
    archivo.close();
}

void agregarCliente(){
    if(totalClientes>=MAX_CLIENTES){
        cout<<"Limite alcanzado\n";
        return;
    }

    clientes[totalClientes][0]=generarIDUnico();
    cin.ignore();

    cout<<"Nombre: ";
    getline(cin,clientes[totalClientes][1]);

    cout<<"Apellido: ";
    getline(cin,clientes[totalClientes][2]);

    string ced;
    do{
        cout<<"Cedula: ";
        getline(cin,ced);
    }while(!validarCedula(ced)||existeCedula(ced));
    clientes[totalClientes][3]=ced;

    string tel;
    do{
        cout<<"Telefono: ";
        getline(cin,tel);
    }while(!validarTelefono(tel)||existeTelefono(tel));
    clientes[totalClientes][4]=tel;

    string cor;
    do{
        cout<<"Correo: ";
        getline(cin,cor);
    }while(!validarCorreo(cor));
    clientes[totalClientes][5]=cor;

    cout<<"Direccion: ";
    getline(cin,clientes[totalClientes][6]);

    string planes[6]={"Basico","Estandar","Premium","Familiar","Corporativo","Vip"};
    int op;
    do{
        cout<<"Planes\n";
        for(int i=0;i<6;i++) cout<<i+1<<" "<<planes[i]<<"\n";
        cout<<"Opcion: ";
        cin>>op;
        cin.ignore();
    }while(op<1||op>6);

    clientes[totalClientes][7]=planes[op-1];
    clientes[totalClientes][8]="Activo";

    totalClientes++;
    guardarClientes();
    cout<<"Cliente agregado\n";
}

void mostrarClientes(){
    if(totalClientes==0){
        cout<<"No hay clientes\n";
        return;
    }

    for(int i=0;i<totalClientes;i++){
        cout<<"Id        : "<<clientes[i][0]<<"\n";
        cout<<"Nombre    : "<<clientes[i][1]<<" "<<clientes[i][2]<<"\n";
        cout<<"Cedula    : "<<clientes[i][3]<<"\n";
        cout<<"Telefono  : "<<clientes[i][4]<<"\n";
        cout<<"Correo    : "<<clientes[i][5]<<"\n";
        cout<<"Direccion : "<<clientes[i][6]<<"\n";
        cout<<"Plan      : "<<clientes[i][7]<<"\n";
        cout<<"Estado    : "<<clientes[i][8]<<"\n";
    }
}

void actualizarCliente(){
    string ced;
    cin.ignore();
    cout<<"Cedula: ";
    getline(cin,ced);

    for(int i=0;i<totalClientes;i++){
        if(clientes[i][3]==ced){
            int op;
            do{
                cout<<"\n1.Nombre\n2.Apellido\n3.Telefono\n4.Correo\n5.Direccion\n6.Plan\n7.Estado\n0.Salir\nOpcion: ";
                cin>>op;
                cin.ignore();

                if(op==1) getline(cin,clientes[i][1]);
                if(op==2) getline(cin,clientes[i][2]);
                if(op==3){
                    string t;
                    do{ getline(cin,t); }while(!validarTelefono(t)||existeTelefono(t));
                    clientes[i][4]=t;
                }
                if(op==4){
                    string c;
                    do{ getline(cin,c); }while(!validarCorreo(c));
                    clientes[i][5]=c;
                }
                if(op==5) getline(cin,clientes[i][6]);
                if(op==6){
                    string planes[6]={"Basico","Estandar","Premium","Familiar","Corporativo","Vip"};
                    int p;
                    do{
                        for(int k=0;k<6;k++) cout<<k+1<<" "<<planes[k]<<"\n";
                        cout<<"Opcion: ";
                        cin>>p;
                        cin.ignore();
                    }while(p<1||p>6);
                    clientes[i][7]=planes[p-1];
                }
                if(op==7) getline(cin,clientes[i][8]);
            }while(op!=0);

            guardarClientes();
            cout<<"Cliente actualizado\n";
            return;
        }
    }
    cout<<"Cliente no encontrado\n";
}

void eliminarCliente(){
    string ced;
    cin.ignore();
    cout<<"Cedula: ";
    getline(cin,ced);

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

int buscarClientePorCedula(string cedula){
    for(int i=0;i<totalClientes;i++)
        if(clientes[i][3]==cedula) return i;
    return -1;
}

void mostrarDatosCliente(int pos){
    cout<<"\nDatos del cliente\n";
    cout<<"Nombre   : "<<clientes[pos][1]<<" "<<clientes[pos][2]<<"\n";
    cout<<"Cedula   : "<<clientes[pos][3]<<"\n";
    cout<<"Telefono : "<<clientes[pos][4]<<"\n";
    cout<<"Plan     : "<<clientes[pos][7]<<"\n";
    cout<<"Estado   : "<<clientes[pos][8]<<"\n";
}

void menuClientes(){
    leerClientes();
    int op;
    do{
        cout<<"\nMenu Clientes\n";
        cout<<"1.Agregar\n";
        cout<<"2.Mostrar\n";
        cout<<"3.Actualizar\n";
        cout<<"4.Eliminar\n";
        cout<<"0.Salir\n";
        cout<<"Opcion: ";
        cin>>op;

        if(op==1) agregarCliente();
        if(op==2) mostrarClientes();
        if(op==3) actualizarCliente();
        if(op==4) eliminarCliente();

    }while(op!=0);
}

