#include <stdio.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

//http://www.cplusplus.com/reference/

class symbol{
    public:
        std::string name;
        bool terminal; // in case been terminal results are empty
        std::vector<std::string> productions;

};


class Gramar{


    public:
        std::map<std::string,symbol> symbols;//Map symbol name to symbol

        int state = 0; // 0 new, 1 clean, 2 chomsky, 3 greibach
        std::string initial="S";

        void defineInitial(std::string S){
            initial=S;
        }

        bool insertNonTerminal(std::string sym, std::vector<std::string> P){

            if(symbols.find(sym)==symbols.end()){
                symbol newSymbol;
                newSymbol.name=sym;
                newSymbol.terminal=false;
                newSymbol.productions=P;
                symbols.insert( std::pair<std::string,symbol>(sym,newSymbol) );
                return true;
            }
            return false;

        }

         bool insertTerminal(std::string sym){

            if(symbols.find(sym)==symbols.end()){
                symbol newSymbol;
                newSymbol.name=sym;
                newSymbol.terminal=true;
                symbols.insert( std::pair<std::string,symbol>(sym,newSymbol) );
                //newSymbol.productions=null;
                return true;
            }
            return false;
        }
        //get production for key, key is a symbol.name
        std::vector<std::string> getProduction(std::string key){
            if (symbols.find(key)!=symbols.end()){
                symbol aux= symbols[key];
                if (symbols[key].terminal){
                    return std::vector<std::string>();
                }
                return symbols[key].productions;
            }
            else return std::vector<std::string>();

        }
        //get production for key, without the symbol '|'
        std::vector<std::string> getProductionClean(std::string key){
            if (symbols.find(key)!=symbols.end()){
                symbol aux= symbols[key];
                if (symbols[key].terminal){
                    return std::vector<std::string>();
                }
                //Remove de | character
                std::vector<std::string> auxProduction =symbols[key].productions;
                int i=0,j=0;

                 for(i=0;i<auxProduction.size();i++){
                    while(j<auxProduction[i].size()){
                        if(auxProduction[i].at(j)=='|'){// constante de separacion de simbolos en un produccion
                            auxProduction[i].erase(auxProduction[i].begin()+j);
                            j=0;
                        }
                        j++;

                    }
                 }
                return auxProduction;

            }
            else return std::vector<std::string>();

        }

        std::vector<std::string> symbolsOfProduction(std::string productionString){

            //Remove de | character
            std::vector<std::string> auxProduction;
            std::string subString;
            int j=0;

            while(j<productionString.size()){
                if(productionString.at(j)=='|'){// constante de separacion de simbolos en un produccion
                    auxProduction.push_back(subString);
                    subString.clear();
                }else{
                    subString+=productionString.at(j);
                }
                j++;
             }
            return auxProduction;
        }

        std::vector<std::string> getStringsOfGramar(){
            std::map<std::string, symbol>::iterator it;
            std::vector<symbol> auxSymbol;
            std::vector<std::string> strings;
            it = symbols.begin();
            int i,j ;
            while ( it != symbols.end()){

              auxSymbol.push_back(it->second);
              it++;
            }
            for(i=0;i<auxSymbol.size();i++){
                for(j=0;j<auxSymbol[i].productions.size();j++){
                    strings.push_back( auxSymbol[i].name+"->"+auxSymbol[i].productions[j]);
                }

            }
            return strings;
        }

};


