#include "dataStructures.h"

using namespace std;

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
        auxA.push_back("a|");
        auxA.push_back("a|A|");// LA NOTACION DE " | " ES PARA DISTINGUIR ENTRE SIMBOLOS COMO A_b (a sub b) y simbolos de A al momento de leer
        auxA.push_back("a|A|B|b|");
    nonTerminal.push_back("B|");
        std::vector<string> auxB;// ESTAS SON LAS PRODUCCIONES DE B
        auxB.push_back("b|");
        auxB.push_back("b|B|");

    //instancia de la gramatica
    Gramar G;
    G.defineInitial("S");// EL SIMBOLO POR DEFAULT ES S PERO LO AGREGO AQUI PARA DAR UN EJEMPLO DE COMO FUNCIONA ESTA FUNCION
        std::vector<string> auxS;// ESTAS SON LAS PRODUCCIONES DE
        auxS.push_back("@|");//Arroba es epsilon namas por que se me antojo
        auxS.push_back("A|B");

    G.insertNonTerminal(G.initial,std::vector<std::string>()); // EN ESTE PASO SE INSERTA UN NO TERMINAL, AGREGO "S" Y  UN VECTOR VACIO
    G.insertNonTerminal("A",auxA); //SE INSERTA UN NO TERMINAL Y SE LE ENVIA SUS PRODUCCIONES DIRECTAMENTE
    G.insertNonTerminal("B",auxB);
    G.symbols["S"].productions=auxS;//ASIGNO AQUI A S LAS PRODUCCIONES QUE LE CORRESPONDE

    G.state=0;//EMPTY, LEASE ESTADOS EN LA CLASE GRAMAR


    int i;
    for(i=0;i<terminal.size();i++){ //EJEMPLO DE COMO INSERTAR ITERATIVAMENTE
        G.insertTerminal(terminal[i]);
    }



    std::cout << "Que hay en auxA [0]?: " << auxA.at(1);// PREGUNTAR POR UN VECTOR
    std::cout << "\nQue hay en auxA [0][2]?: " << auxA.at(1).at(2);// Cual es su segundo caracter?
    std::cout << "\nProducciones del simbolo A ?: " << G.getProduction(G.initial).size();
    for(i=0;i<G.getProduction("A").size();i++){ // Producciones de A ?
        std::cout << "\n\t" << G.getProductionClean("A").at(i);
    }

    std::cout << "\nProducciones del simbolo A separadas por simbolo en la produccion ?: " ;
    for(i=0;i<G.getProduction("A").size();i++){ // Producciones de A ?
        std::cout << "\n\t" << G.getProduction("A").at(i);
    }

    std::cout << "\nQue simbolos hay en la ultima produccion de A ?: \n" ;
    for(i=0;i<G.symbolsOfProduction(G.getProduction("A").at(2)).size();i++){ // Producciones de A ?
        std::cout << "\t" << G.symbolsOfProduction( G.getProduction("A").at(2) ).at(i);
    }

    std::cout << "\nProducciones del simbolo inicial ?: " << G.initial << " -> ";
    for(i=0;i<G.getProduction(G.initial).size();i++){ // Producciones de A ?
        std::cout << " \\ " << G.getProductionClean(G.initial).at(i);
    }//G.symbols[terminal[i]].productions=auxA;


    printf("\n\n");


}
