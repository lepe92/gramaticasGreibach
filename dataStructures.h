#include <stdio.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>

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



};
