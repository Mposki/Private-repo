#ifndef SPRAWDZPISANIE_H
#define SPRAWDZPISANIE_H
#define GET_VARIABLE_NAME(Variable) (#Variable)
#include <regex>
#include <string>

class Pismo
{
public:
    std::regex litery;
    std::regex peselR;
    std::regex dataR;

    Pismo(){
        this->litery = std::regex("((([A-Z]|[Ą,Ć,Ę,Ł,Ń,Ó,Ś,Ź,Ż]){2,})|([A-Z]|[Ą,Ć,Ę,Ł,Ń,Ó,Ś,Ź,Ż])([a-z]|[ą,ć,ę,ł,ń,ó,ś,ź,ż]){1,})$");
        this->peselR = std::regex("[0-9]{2}((0[1-9])|(1[0-2]))((0[1-9])|(1[0-9])|(2[0-9])|(3[0-1]))[0-9]{5}$");
        this->dataR = std::regex("([1-9]|(0[1-9])|(1[0-9])|(2[0-9])|(3[0-1]))\-([1-9]|(0[1-9])|(1[0-2]))\-[0-9]{4}$");
    }

    template<class T, class F> void sprawdz(T ciag, F wybor){
        if(wybor == 0){
            if(std::regex_match(ciag, this->peselR)) { return; }
            else { throw "Brak dopasowania wzorca peselu!"; }
        }
        else if(wybor == 1){
            if(std::regex_match(ciag, this->litery)){ return; }
            else { throw "Brak dopasowania wzorca nazwy własnej!"; }
        }
        else if(wybor == 2){
            if(std::regex_match(ciag, this->dataR)){ return; }
            else { throw "Brak dopasowania wzorca daty!"; }
        }
        else { throw "Brak dopasowania wzorca!"; }
    }
};


#endif // SPRAWDZPISANIE_H
