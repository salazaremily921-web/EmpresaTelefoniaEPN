#include "servicios.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;

string servicios[MAX_SERVICIOS][CAMPOS_SERVICIO];
int totalServicios = 0;

void leerServicios(){
    ifstream archivo("servicios.csv");
    if(!archivo.is_open()) return;

    totalServicios = 0;
    string linea;
    while(getline(archivo,linea)){
        int k = 0;
        string temp = "";
        for(char c : linea){
            if(c == ','){
                servicios[totalServicios][k++] = temp;
                temp = "";
            }else{
                temp += c;
            }
        }
        servicios[totalServicios][k] = temp;
        totalServicios++;
        if(totalServicios >= MAX_SERVICIOS) break;
    }
    archivo.close();
}

void guardarServicios(){
    ofstream archivo("servicios.csv");
    for(int i=0;i<totalServicios;i++){
        for(int j=0;j<CAMPOS_SERVICIO;j++){
            archivo << servicios[i][j];
            if(j < CAMPOS_SERVICIO-1) archivo << ",";
        }
        archivo << endl;
    }
    archivo.close();
}

string generarIdServicio(){
    string id = "";
    for(int i=0;i<8;i++) id += to_string(rand()%10);
    return id;
}

bool validarCosto(string c){
    for(char ch : c)
        if(!isdigit(ch) && ch!='.') return false;
    return !c.empty();
}

bool validarEstado(string e){
    return e=="Activo" || e=="Inactivo";
}

void agregarServicio(){
    if(totalServicios >= MAX_SERVICIOS){
        cout<<"Limite alcanzado\n";
        return;
    }

    servicios[totalServicios][0] = generarIdServicio();
    cin.ignore();

    cout<<"Nombre del servicio: ";
    getline(cin, servicios[totalServicios][1]);

    string costo;
    do{
        cout<<"Costo: ";
        getline(cin, costo);
    }while(!validarCosto(costo));
    servicios[totalServicios][2] = costo;

    cout<<"Plan asociado: ";
    getline(cin, servicios[totalServicios][3]);

    string estado;
    do{
        cout<<"Estado (Activo/Inactivo): ";
        getline(cin, estado);
    }while(!validarEstado(estado));
    servicios[totalServicios][4] = estado;

    cout<<"Observaciones: ";
    getline(cin, servicios[totalServicios][5]);

    totalServicios++;
    guardarServicios();
    cout<<"Servicio agregado\n";
}

void mostrarServicios(){
    if(totalServicios == 0){
        cout<<"No hay servicios\n";
        return;
    }

    for(int i=0;i<totalServicios;i++){
        cout<<"Id           : "<<servicios[i][0]<<endl;
        cout<<"Nombre       : "<<servicios[i][1]<<endl;
        cout<<"Costo        : "<<servicios[i][2]<<endl;
        cout<<"Plan         : "<<servicios[i][3]<<endl;
        cout<<"Estado       : "<<servicios[i][4]<<endl;
        cout<<"Observacion  : "<<servicios[i][5]<<endl;
    }
}

void actualizarServicio(){
    string id;
    cin.ignore();
    cout<<"Id del servicio: ";
    getline(cin,id);

    for(int i=0;i<totalServicios;i++){
        if(servicios[i][0]==id){
            int op;
            do{
                cout<<"\n1.Nombre\n2.Costo\n3.Plan\n4.Estado\n5.Observaciones\n0.Salir\nOpcion: ";
                cin>>op;
                cin.ignore();
                if(op==1) getline(cin, servicios[i][1]);
                if(op==2){
                    string c;
                    do{ getline(cin,c); }while(!validarCosto(c));
                    servicios[i][2]=c;
                }
                if(op==3) getline(cin, servicios[i][3]);
                if(op==4){
                    string e;
                    do{ getline(cin,e); }while(!validarEstado(e));
                    servicios[i][4]=e;
                }
                if(op==5) getline(cin, servicios[i][5]);
            }while(op!=0);
            guardarServicios();
            cout<<"Servicio actualizado\n";
            return;
        }
    }
    cout<<"Servicio no encontrado\n";
}

void eliminarServicio(){
    string id;
    cin.ignore();
    cout<<"Id del servicio: ";
    getline(cin,id);

    for(int i=0;i<totalServicios;i++){
        if(servicios[i][0]==id){
            for(int j=i;j<totalServicios-1;j++)
                for(int k=0;k<CAMPOS_SERVICIO;k++)
                    servicios[j][k]=servicios[j+1][k];
            totalServicios--;
            guardarServicios();
            cout<<"Servicio eliminado\n";
            return;
        }
    }
    cout<<"Servicio no encontrado\n";
}

void menuServicios(){
    leerServicios();
    int opcion;
    do{
        cout<<"\nMenu Servicios\n";
        cout<<"1.Agregar\n";
        cout<<"2.Mostrar\n";
        cout<<"3.Actualizar\n";
        cout<<"4.Eliminar\n";
        cout<<"0.Salir\n";
        cout<<"Opcion: ";
        cin>>opcion;

        if(opcion==1) agregarServicio();
        if(opcion==2) mostrarServicios();
        if(opcion==3) actualizarServicio();
        if(opcion==4) eliminarServicio();

    }while(opcion!=0);
}

