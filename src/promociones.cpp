#include "promociones.h"
#include <iostream>
#include <fstream>
#include <string>      
#include <iomanip>

using namespace std;

// Definición de variables globales
string promociones[MAX_PROMOCIONES][CAMPOS_PROMOCION];
int totalPromociones = 0;


string generarIDPromocion() {
    string id;
    bool existe;
    do {
        id = "P";
        for(int i=0;i<6;i++) id += to_string(rand()%10);
        existe = false;
        for(int j=0;j<totalPromociones;j++){
            if(promociones[j][0]==id){ existe=true; break; }
        }
    } while(existe);
    return id;
}


void leerPromociones(){
    ifstream archivo("promociones.csv");
    if(!archivo.is_open()) return;
    totalPromociones=0;
    string linea;
    while(getline(archivo,linea)){
        int k=0; string temp="";
        for(char c:linea){
            if(c==','){ promociones[totalPromociones][k++]=temp; temp=""; }
            else temp+=c;
        }
        promociones[totalPromociones][k++]=temp;
        totalPromociones++;
        if(totalPromociones>=MAX_PROMOCIONES) break;
    }
    archivo.close();
}

void guardarPromociones(){
    ofstream archivo("promociones.csv");
    for(int i=0;i<totalPromociones;i++){
        for(int j=0;j<CAMPOS_PROMOCION;j++){
            archivo << promociones[i][j];
            if(j!=CAMPOS_PROMOCION-1) archivo << ",";
        }
        archivo << "\n";
    }
    archivo.close();
}


void agregarPromocion(){
    if(totalPromociones>=MAX_PROMOCIONES){ cout<<"Limite de promociones alcanzado\n"; return; }
    promociones[totalPromociones][0] = generarIDPromocion();
    cin.ignore();
    cout << "Nombre de la promocion: "; getline(cin,promociones[totalPromociones][1]);
    cout << "Descuento (%): "; getline(cin,promociones[totalPromociones][2]);
    cout << "Fecha inicio (dd/mm/yyyy): "; getline(cin,promociones[totalPromociones][3]);
    cout << "Fecha fin (dd/mm/yyyy): "; getline(cin,promociones[totalPromociones][4]);
    promociones[totalPromociones][5] = "Activa";

    totalPromociones++;
    guardarPromociones();
    cout << "Promocion agregada correctamente\n";
}

void mostrarPromociones(){
    if(totalPromociones==0){ cout<<"No hay promociones registradas\n"; return; }
    cout << left
         << setw(10) << "ID"
         << setw(25) << "Nombre"
         << setw(12) << "Descuento"
         << setw(15) << "Inicio"
         << setw(15) << "Fin"
         << setw(10) << "Estado" << "\n";
    cout << string(87,'-') << "\n";
    for(int i=0;i<totalPromociones;i++){
        cout << left
             << setw(10) << promociones[i][0]
             << setw(25) << promociones[i][1]
             << setw(12) << promociones[i][2]
             << setw(15) << promociones[i][3]
             << setw(15) << promociones[i][4]
             << setw(10) << promociones[i][5] << "\n";
    }
}

void actualizarPromocion(){
    string id;
    cin.ignore();
    cout << "ID de la promocion a actualizar: "; getline(cin,id);
    for(int i=0;i<totalPromociones;i++){
        if(promociones[i][0]==id){
            int opcion;
            do{
                cout<<"1.Nombre 2.Descuento 3.Fecha Inicio 4.Fecha Fin 5.Estado 0.Salir\nOpcion: ";
                cin>>opcion; cin.ignore();
                switch(opcion){
                    case 1: cout<<"Nuevo nombre: "; getline(cin,promociones[i][1]); break;
                    case 2: cout<<"Nuevo descuento: "; getline(cin,promociones[i][2]); break;
                    case 3: cout<<"Nueva fecha inicio: "; getline(cin,promociones[i][3]); break;
                    case 4: cout<<"Nueva fecha fin: "; getline(cin,promociones[i][4]); break;
                    case 5: cout<<"Nuevo estado: "; getline(cin,promociones[i][5]); break;
                }
            }while(opcion!=0);
            guardarPromociones();
            cout<<"Promocion actualizada correctamente\n";
            return;
        }
    }
    cout<<"Promocion no encontrada\n";
}

void eliminarPromocion(){
    string id;
    cin.ignore();
    cout << "ID de la promocion a eliminar: "; getline(cin,id);
    for(int i=0;i<totalPromociones;i++){
        if(promociones[i][0]==id){
            for(int j=i;j<totalPromociones-1;j++)
                for(int k=0;k<CAMPOS_PROMOCION;k++)
                    promociones[j][k] = promociones[j+1][k];
            totalPromociones--;
            guardarPromociones();
            cout<<"Promocion eliminada\n";
            return;
        }
    }
    cout<<"Promocion no encontrada\n";
}


void buscarPromocion(){
    int opcion;
    do{
        cout<<"1.ID 2.Nombre 3.Descripcion 4.Estado 0.Salir\nOpcion: ";
        cin>>opcion; cin.ignore();
        switch(opcion){
            case 1:{ string id; cout<<"Ingrese ID: "; getline(cin,id);
                for(int i=0;i<totalPromociones;i++) if(promociones[i][0]==id) cout<<promociones[i][1]<<" | Descuento: "<<promociones[i][2]<<"\n"; break;}
            case 2:{ string nom; cout<<"Ingrese nombre: "; getline(cin,nom);
                for(int i=0;i<totalPromociones;i++) if(promociones[i][1]==nom) cout<<promociones[i][0]<<" | "<<promociones[i][1]<<" | "<<promociones[i][2]<<"\n"; break;}
            case 4:{ string est; cout<<"Ingrese estado: "; getline(cin,est);
                for(int i=0;i<totalPromociones;i++) if(promociones[i][5]==est) cout<<promociones[i][0]<<" | "<<promociones[i][1]<<"\n"; break;}
        }
    }while(opcion!=0);
}


void intercambiarPromociones(int a,int b){ for(int k=0;k<CAMPOS_PROMOCION;k++){ string tmp=promociones[a][k]; promociones[a][k]=promociones[b][k]; promociones[b][k]=tmp;} }
void ordenarPromocionesPorID(){ for(int i=0;i<totalPromociones-1;i++) for(int j=i+1;j<totalPromociones;j++) if(promociones[i][0]>promociones[j][0]) intercambiarPromociones(i,j);}
void ordenarPromocionesPorNombre(){ for(int i=0;i<totalPromociones-1;i++) for(int j=i+1;j<totalPromociones;j++) if(promociones[i][1]>promociones[j][1]) intercambiarPromociones(i,j);}


void menuPromociones(){
    leerPromociones();
    int opcion;
    do{
        cout<<"\n Menu Promociones \n1.Agregar 2.Mostrar 3.Buscar 4.Actualizar 5.Eliminar 6.Ordenar 0.Salir\nOpcion: ";
        cin>>opcion; cin.ignore();
        switch(opcion){
            case 1: agregarPromocion(); break;
            case 2: mostrarPromociones(); break;
            case 3: buscarPromocion(); break;
            case 4: actualizarPromocion(); break;
            case 5: eliminarPromocion(); break;
            case 6:{
                int ord;
                cout<<"Ordenar por: 1.ID 2.Nombre\nOpcion: "; cin>>ord; cin.ignore();
                switch(ord){
                    case 1: ordenarPromocionesPorID(); break;
                    case 2: ordenarPromocionesPorNombre(); break;
                }
                break;
            }
        }
    }while(opcion!=0);
}

