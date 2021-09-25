#ifndef INFOR_HPP
#define INFOR_HPP
#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <vector>
using namespace std;

class Infor {
    //Consideré hacer las variables públicas pero no terminó siendo un problema
    private: 
        struct tm dateStruct;
        time_t valor;
        string mes;
        string dia;
        string horas;
        string minutos;
        string segundos;
        string ip;
        string mensaje;
        vector<string> meses{"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    public:
        Infor(string);
        void print(ofstream&);
        bool operator ==(const Infor&);
        bool operator ==(const time_t&);
        bool operator !=(const Infor&);
        bool operator >(const Infor&);
        bool operator <(const Infor&);
        bool operator >(const time_t&);
        bool operator <=(const Infor&);
        ~Infor();

};

#endif // INFOR_HPP
