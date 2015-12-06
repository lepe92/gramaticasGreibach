#include "dataStructures.h"
#include <string>
#include <sstream>

using namespace std;
int contadorNoTerminales=0;
//metodos para split de cadena
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

void MostrarGramatica(std::vector<std::string> noTerminalesNumerados, std::map<std::string,std::vector<std::string> > produccionesNumeradas){
for(int k=0; k<noTerminalesNumerados.size();k++){
    std::vector<std::string> a =produccionesNumeradas.at(noTerminalesNumerados[k]);
    for(int iV=0;iV<a.size();iV++){
        cout<<"\n"<<noTerminalesNumerados[k]<<"->"<<a[iV];
        }
    }
}

Gramar enumerarNoTerminales(Gramar FNCH, vector<string> noTerminal,vector<string> terminal){
    cout<<"\n"<<"No terminales";

    std::vector<string> noTerminalesOriginal;
    noTerminalesOriginal.push_back(FNCH.initial);
    //cout<<"\n"<<FNCH.initial;
    for(int i=0; i<noTerminal.size();i++)
        noTerminalesOriginal.push_back(noTerminal[i]);
        // cout<<FNCH.symbols.at(i).name;

//declaracion del vector de no terminales ya numerados
    std::vector<string> noTerminalesNumerados;
    for(int j=0; j<noTerminalesOriginal.size();j++){
        string Result;          // string which will contain the result
        stringstream convert;   // stream used for the conversion
        convert << contadorNoTerminales;      // insert the textual representation of 'Number' in the characters in the stream
        Result = convert.str(); // set 'Result' to the contents of the stream
        noTerminalesNumerados.push_back(Result);
        contadorNoTerminales++;
        cout<<"\n"<<noTerminalesOriginal[j]<<"->"<<noTerminalesNumerados[j];
    }

//generar nuevas producciones ya cambiados el mapeo de noTerminal a numero
    //definimos la nueva gramatica
    Gramar Greibach;
    Greibach.defineInitial(noTerminalesNumerados[0]);
    //insertar terminales
    for(int i=0;i<terminal.size();i++){ //EJEMPLO DE COMO INSERTAR ITERATIVAMENTE
        Greibach.insertTerminal(terminal[i]);
    }

    cout << "\nProducciones del simbolo inicial separadas por simbolo en la produccion: " ;
    int contadorProduccion=0;
    for(int m=0;m<noTerminalesOriginal.size();m++){
        std::vector<string> aux;

        for(int i=0;i<FNCH.getProduction(noTerminalesOriginal[m]).size();i++){
                string produccion="";
        //obtener cada produccion de la FNCH, cada produccion de los no terminales
            cout << "\n\t" <<noTerminalesOriginal[m]<<"->"<< FNCH.getProduction(noTerminalesOriginal[m]).at(i);
            std::vector<std::string> x = split(FNCH.getProduction(noTerminalesOriginal[m]).at(i), '|');
            for(int j=0;j<x.size();j++){
                //obtener cada terminal y/o no terminal de cada produccion
                cout<<"\n"<<x[j];
                int c=0, indiceNoTerminal;
                for(int iT=0;iT <noTerminalesOriginal.size();iT++){
                    if(noTerminalesOriginal[iT]==x[j]){
                    cout<<" "<<noTerminalesNumerados[iT];
                    c++;
                    indiceNoTerminal=iT;
                    }
                }
                if(c==0){
                        produccion+=x[j]+'|';
                }
                else{
                    produccion+=noTerminalesNumerados[indiceNoTerminal]+'|';
                }
                //cout<<"\n"<<noTerminalesNumerados[contadorProduccion]<<"->"<<produccion;
            }
            aux.push_back(produccion);
           // cout<<"\n"<<"fin de produccion";
            //cout<<"\n"<<noTerminalesNumerados[contadorProduccion]<<"->"<<produccion;
        }
        cout<<noTerminalesNumerados[m]<<"->"<<aux[0];
        Greibach.insertNonTerminal(noTerminalesNumerados[m],aux);
    }

//ya numerada y sustituida la gramatica
cout<<"\n"<<"Gramatica Numerada";
  std::vector<std::string> stringsOfGramar;
    stringsOfGramar= Greibach.getStringsOfGramar();
    //int i;
        for(int i=0;i<stringsOfGramar.size();i++){
            cout <<"\n" << stringsOfGramar[i];
        }
cout<<"\n";

//mapear las producciones de la gramatica
std::map<std::string,std::vector<std::string> > produccionesNumeradas;

for(int m=0;m<noTerminalesNumerados.size();m++){
        std::vector<std::string>produccioncitas;
for(int i=0;i<Greibach.getProduction(noTerminalesNumerados[m]).size();i++){
cout << "\n\t" <<noTerminalesNumerados[m]<<"->"<< Greibach.getProduction(noTerminalesNumerados[m]).at(i);
    produccioncitas.push_back(Greibach.getProduction(noTerminalesNumerados[m]).at(i));
}
produccionesNumeradas.insert(std::pair<std::string,std::vector<std::string> > (noTerminalesNumerados[m],produccioncitas));
}
//PASO 1
cout<<"\n"<<"Paso 1";
//std::vector<std::string> a =produccionesNumeradas.at("0");
//cout<<"\n"<<a[0];
//sigue paso 1, recorrer todas las producciones y ver cuando i<=j para toda Ai y sus producciones
bool siSeCambio=true;
while(siSeCambio){
        siSeCambio=false;
for(int k=0; k<noTerminalesNumerados.size();k++){
    std::vector<std::string> a =produccionesNumeradas.at(noTerminalesNumerados[k]);
    //pasar a entero la llave pare tener i
    // pasar a entero el inicial de cada produccion para tener j
    int i=0;
    stringstream convert(noTerminalesNumerados[k]);//object from the class stringstream
    convert>>i;
    //ya tenemos i, sigue obtener j
    int j=0;
    for(int iV=0;iV<a.size();iV++){
        std::vector<std::string> x = split(a[iV], '|');
       //si x[0] esta en los noterminalesnumerados
       bool estaEnNoTerminales=false;
       for(int nTI=0; nTI<noTerminalesNumerados.size();nTI++){
            if(noTerminalesNumerados[nTI]==x[0])
                estaEnNoTerminales=true;
       }
       if(estaEnNoTerminales){
        stringstream convert(x[0]);//object fr1om the class stringstream
        convert>>j;
        //cout<<"\n"<<j;
        if(i>j){
                siSeCambio=true;
            cout<<"\n"<<i<<">"<<j;
            //i=2 y j=0
            std::vector<std::string> vectorJ=produccionesNumeradas.at(noTerminalesNumerados[j]);
            std::vector<std::string> reemplazarI;
            //copiamos en reemplazarI todos los valores de producciones anteriores a iV
            for(int iV2=0;iV2<iV;iV2++){
                reemplazarI.push_back(a[iV2]);
            }
           for(int vJ=0; vJ<vectorJ.size();vJ++){
                //vectorJ[vJ];
                string temp=vectorJ[vJ];
               for(int iX=1;iX<x.size();iX++){
                    temp+=x[iX]+'|';
                }
                reemplazarI.push_back(temp);
            }
            //anadimos lo que es posterior a iV
            for(int iV2=iV+1;iV2<a.size();iV2++){
                reemplazarI.push_back(a[iV2]);
            }
           // produccionesNumeradas[noTerminalesNumerados[k]].clear();
                a=reemplazarI;
            //produccionesNumeradas.at(noTerminalesNumerados[k])=reemplazarI
        }
       }
    }//ya tenemos a reemplazada, falta sustituir en produccionesnumeradas
    produccionesNumeradas[noTerminalesNumerados[k]]=a;
}

}

//std::vector<std::string> reemplazarI= produccionesNumeradas.at("2");
//for(int i=0; i<reemplazarI.size();i++)
//    cout<<"\n"<<reemplazarI[i];
cout<<"\n\n"<<"Final del paso 1.1 i>j";
cout<<"\n"<<"Nueva gramatica";
MostrarGramatica(noTerminalesNumerados, produccionesNumeradas);



return Greibach;
}



int main()
{   //EJEMPLO DE COMO USAR LA ESTRUCTURA

    //ESTAS DOS COSAS SE TIENEN QUE CONSEGUIR POR LA INTERFAZ
    std::vector<string> nonTerminal;
    std::vector<string> terminal;


    //insertar al final del vector
    terminal.push_back ("a|");//esto es una emulacion de lo que se tiene que insertar por interfaz
    terminal.push_back ("b|");

    nonTerminal.push_back("A");
        std::vector<string> auxA;// ESTAS SON LAS PRODUCCIONES DE A
        auxA.push_back("B|S|");// LA NOTACION DE " | " ES PARA DISTINGUIR ENTRE SIMBOLOS COMO A_b (a sub b) y simbolos de A al momento de leer
        auxA.push_back("b|");
        //auxA.push_back("S|B|");
    nonTerminal.push_back("B");
        std::vector<string> auxB;// ESTAS SON LAS PRODUCCIONES DE B
        auxB.push_back("S|A|");
        auxB.push_back("a|");
        //auxB.push_back("A|S|");

    //instancia de la gramatica
    Gramar G;
    G.defineInitial("S");// EL SIMBOLO POR DEFAULT ES S PERO LO AGREGO AQUI PARA DAR UN EJEMPLO DE COMO FUNCIONA ESTA FUNCION
        std::vector<string> auxS;// ESTAS SON LAS PRODUCCIONES DE
        auxS.push_back("A|B|");
         //auxS.push_back("S|B|");

    G.insertNonTerminal(G.initial,std::vector<std::string>()); // EN ESTE PASO SE INSERTA UN NO TERMINAL, AGREGO "S" Y  UN VECTOR VACIO
    G.insertNonTerminal("A",auxA); //SE INSERTA UN NO TERMINAL Y SE LE ENVIA SUS PRODUCCIONES DIRECTAMENTE
    G.insertNonTerminal("B",auxB);
    G.symbols["S"].productions=auxS;//ASIGNO AQUI A S LAS PRODUCCIONES QUE LE CORRESPONDE

    G.state=0;//EMPTY, LEASE ESTADOS EN LA CLASE GRAMAR


    int i;
    for(i=0;i<terminal.size();i++){ //EJEMPLO DE COMO INSERTAR ITERATIVAMENTE
        G.insertTerminal(terminal[i]);
    }


//ahasta aqui se inciializa la gramatica en FNCH
cout<<"\n"<<"Gramatica FNCH";
  std::vector<std::string> stringsOfGramar;
    stringsOfGramar= G.getStringsOfGramar();
    //int i;
        for(i=0;i<stringsOfGramar.size();i++){
            cout <<"\n" << stringsOfGramar[i];
        }
cout<<"\n";
enumerarNoTerminales(G, nonTerminal,terminal);

/*
    std::cout << "\nProducciones del simbolo A separadas por simbolo en la produccion ?: " ;
    for(i=0;i<G.getProduction("A").size();i++){ // Producciones de A ?
        std::cout << "\n\t" << G.getProduction("A").at(i);
    }

    std::cout << "\nQue simbolos hay en la ultima produccion de A ?: \n" ;
    for(i=0;i<G.symbolsOfProduction(G.getProduction("A").at(1)).size();i++){ // Producciones de A ?
        std::cout << "\t" << G.symbolsOfProduction( G.getProduction("A").at(1) ).at(i);
    }

    std::cout << "\nProducciones del simbolo inicial ?: " << G.initial << " -> ";
    for(i=0;i<G.getProduction(G.initial).size();i++){ // Producciones de A ?
        std::cout << " \\ " << G.getProductionClean(G.initial).at(i);
    }//G.symbols[terminal[i]].productions=auxA;


    printf("\n\n");
*/

}
