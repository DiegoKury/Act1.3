/*Este programa recibe información de fechas de un archivo de texto, la convierte en un vector de clase Infor,
la ordena de más antiguo a reciente, y solicita dos fechas para imprimir todas las fechas dentro de esos dos
valores.

Escrito por: 
-Diego Kury Rivera A00227097

Con ayuda de:
-Julián Madrid
-Luis Ángel

Creado el 15 de septiembre de 2021
Última modificación: 22 de septiembre de 2021*/

#include "Infor.hpp"
#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <vector>
using namespace std;

//Declaración de funciones
void merge(int, int, int, int);
void mergeSort(int, int, int);
time_t getDate(string);

/*Esta fue probablemente la parte donde más batallé en el código, principalmente
 * porque no sabía como usar este formato al utilizar un vector de clases. Al
 * final logré hacerlo con bastante ayuda*/
void merge(vector<Infor> &values, int low, int m, int high){
    vector<Infor> temp;
  
    int i{low}, j{m + 1};
  
    while (i <= m && j <= high) {
    if (values[i] <= values[j]){
        temp.push_back(values[i]);
        i++;
    } else {
        temp.push_back(values[j]);
        j++;
    }
  }

    while (i <= m) {
        temp.push_back(values[i]);
        i++;
  }
  
    while (j <= high) {
      temp.push_back(values[j]);
      j++;
  }
  
    for(int i{low}; i <= high; i++)
        values[i] = temp[i-low];
}

/*Parte sencilla del algoritmo de merge*/
void mergeSort(vector<Infor> &values, int low, int high) { 
    if (low >= high) {
        return;
  }
    int m = low + (high - low) / 2;
    mergeSort(values, low, m);
    mergeSort(values, m + 1, high);
    merge(values, low, m, high);
}

/*Esta función es crucial para conseguir los valores utilizados en la búsqueda binaria*/
time_t getDate(string fecha){ 
    /*Para no complicarme mucho volví a declarar el vector de meses en la función, aunque
 * probablemente se pudo haber evitado*/
    vector<string> meses = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    struct tm dateStruct;
    
    /*Personalmente prefiero declarar las funciones y darles valor al mismo tiempo,
     * haciendo uso de las {}, pero no lo hice en algunas del main por miedo a un
     * error, sin embargo he leído que declarar las variables con un {} vacío al lado
     * aunque todavía no se les de valor es la manera óptima de hacerlo*/
    string mes{fecha.substr(0,fecha.find(" "))};
    int dia{stoi(fecha.substr(3,fecha.find(" ")))};
    int horas{stoi(fecha.substr(6,fecha.find(":")))};
    int minutos{stoi(fecha.substr(10,fecha.find(":")))};
    int segundos{stoi(fecha.substr(13,fecha.find(":")))};

    dateStruct.tm_sec = segundos;
    dateStruct.tm_min = minutos;
    dateStruct.tm_hour = horas;
    dateStruct.tm_mday = dia;
    
    //Estas fueron las comparaciones que me hicieron crear nuevas sobrecargas
    for (size_t i{0} ; i < 12 ; i++){
        if (meses[i] == mes)
            dateStruct.tm_mon = i;
    }
    dateStruct.tm_year = 2021 - 1900;
    
    //Se utilizará este valor para la función de búsqueda binaria
    return mktime(&dateStruct);
}

//Lo mismo hecho en la tarea pasada
int binarySearch(vector<Infor> &values, int n, time_t k) {
    int low{0};
    int high{n - 1};
    while (low <= high) {
    int m{low + (high - low) / 2};
        if (values[m] == k) 
            return m;
        else if (values[m] > k) 
            high = m - 1;
        else 
            low = m + 1;
    }
    //Return en caso de no conseguir m
    return -1;
}

int main() {
    //Declaración de vector de clase Infor
    vector<Infor> infTotal;
    
    /*Esta fue la manera en la que creé cada variable Infor, anteriormente
     * tenía el while dentro de mi función pero corría con problemas para
     * iniciarla así que decidí ponerlo en el main y poner la función 
     * dentro del constructor*/
    string nomArch{"bitacora.txt"};
    ifstream archivo(nomArch.c_str());
    string linea{};
    while (getline(archivo, linea))
        infTotal.push_back(Infor(linea));
    
    mergeSort(infTotal, 0, infTotal.size() - 1);
    
    int fechai{}, fechaf{};
    string fecha{};
    cout << "Fecha Inicial: " << endl;
    getline(cin, fecha); 
    fechai = getDate(fecha);
    /*A esto me refería previamente, en otro caso lo hubiera escrito de esta manera:
     * int fechai{getDate(fecha);
     * si hay algún beneficio de una sobre la otra me gustaría oírlo en los comentarios
     * de mi calificación*/

    cout << "Fecha Final: " << endl;
    getline(cin, fecha); 
    fechaf = getDate(fecha);
    
    int ipos{}, fpos{};
    ipos = binarySearch(infTotal, infTotal.size(), fechai);
    fpos = binarySearch(infTotal, infTotal.size(), fechaf);
    
    ofstream archivorden ("ponmecien.txt");
    for (int i{ipos} ; i <= fpos ; i++) {
        infTotal[i].print(archivorden);
        cout << endl;
    } 
    
    archivorden.close();
    return 0;
}
/*Eso sería todo en cuanto al código, para finalizar quisiera comentar que inicialmente
 * batallé mucho con esta materia, lo cual es evidente viendo las calificaciones de mis
 * dos primeras actividades. Esto no es por mi falta de conocimiento del lenguaje, siento
 * que puede ver que tengo un buen entendimiento de cómo funciona el lenguaje basado en
 * objetos y el uso de funciones y variables en C++, sin embargo batallé mucho con los
 * conceptos de búsqueda y de organización, además para ser 100% honesto no le presté
 * tanta atención a la clase como debía. Por esta razón, para llenar los hoyos que no 
 * podía entender en mi código necesité una gran cantidad de ayuda de mis buenos amigos
 * que están en esta clase, lo cual me ayudó a entender lo que me faltaba y cómo podía
 * traducir mi conocimiento a mi código. La mayoría de los cambios radicales que mencioné
 * previamente fue debido a su ayuda, y buenas partes de lo realizado fue gracias a ellos
 * también. Quería mencionar esto en caso de que vea similitudes en los códigos, para que
 * sepa que estoy abierto al hecho de que necesité una buena cantidad de apoyo para
 * la actividad, y que sepa que a partir de este parcial me esforzaré el triple para que
 * sepa que me interesan los conceptos y que quiero aprender.
 * 
 * Diego Kury Rivera A00227097*/

