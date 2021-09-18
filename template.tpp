#ifndef MY_TEMPLATE
#define MY_TEMPLATE

template<typename T>
const urzaiz::Output& operator <<(const urzaiz::Output& sortie, const T& entree){
        std::cout << entree;
        return sortie;
}
template<>
const urzaiz::Output& operator << <std::string>(const urzaiz::Output& sortie, const std::string& entree){
        char * chaineConv = new char[entree.size()+1];
        chaineConv[entree.size()] = '\0';
        CharToOemBuffA(entree.c_str(),chaineConv,entree.size());
        std::cout << chaineConv;
        delete [] chaineConv;
        return sortie;
}
template<typename T>
void urzaiz::vider_tampon(){
     std::cin.clear();
    std::cin.seekg(0, std::ios::end);
    if (!std::cin.fail()){                          //tampon non vide, le vider
        std::cin.ignore(std::numeric_limits<T>::max()); //vidage il est deja a l'etat valide
    }
    else {
        std::cin.clear ();
    }
}
template <typename T>
void urzaiz::saisieSecurisee(const coord& _errorPos,const std::string& _message,std::string const& _chaineModele,T& _value){
    Coordinates posit;
    std::string chaineMask ("");
    std::string temp;
    for (int i = 0; i<99; i++){
        chaineMask += " ";
    }
    while (true){
        getline (std::cin, temp);
        if (std::cin.eof() || std::cin.bad ()){                       //fin du flux rencontre ou alors cin invalide de maniere premeturee
            std::cerr << "Une erreur interne est survenue ..."<<std::endl;       // si l'erreur est une fin de flux prematuree
            if (std::cin.eof()){
                break;
            }
            vider_tampon<T>();
            continue;
        }
        else if (std::cin.fail() || (temp.find_first_not_of(_chaineModele) != std::string::npos)){
            urzaiz::AllerA(0,_errorPos.b+1);
            posit = urzaiz::cursorPos();
            urzaiz::conOut << chaineMask;
            urzaiz::AllerA(posit.a,posit.b);
            urzaiz::conOut << _message;
            urzaiz::vider_tampon<T>();
            urzaiz::AllerA(_errorPos);
            urzaiz::conOut << chaineMask;
            urzaiz::AllerA(_errorPos);
            continue;
        }
        vider_tampon<T>();   // pour pouvoir le confier a un autre flux
        std::stringstream flux(temp);
        auto totalSlash {std::count(std::begin(temp),std::end(temp),'/')};
        auto totalVirgule {std::count(std::begin(temp),std::end(temp),',')};
        auto iterateurSlash {std::find(std::begin(temp),std::end(temp),'/')}; //iterateurSlash pointe sur le slash
        if (totalSlash > 1 || totalVirgule > 1 || iterateurSlash == std::begin(temp)){  //c pas la peine de continuer ce n'est pas un nombre
            urzaiz::AllerA(0,_errorPos.b+1);
            posit =urzaiz::cursorPos();
            urzaiz::conOut << chaineMask;
            urzaiz::AllerA(posit);
            urzaiz::conOut<<_message;
            urzaiz::AllerA(_errorPos);
            urzaiz::conOut << chaineMask;
            urzaiz::AllerA(_errorPos);
            continue;
        }
        else if(totalSlash == 1) {
            std::string miniChaine1 {std::begin(temp),iterateurSlash};
            std::string miniChaine2 {++iterateurSlash,std::end(temp)};
            double reelTempo1{}, reelTempo2{};
            std::stringstream flux2 (miniChaine1);
            flux2 >> reelTempo1;
            std::stringstream flux3(miniChaine2);
            flux3 >> reelTempo2;
            if (flux2.fail() || flux3.fail()){
                urzaiz::AllerA(0,_errorPos.b+1);
                posit =urzaiz::cursorPos();
                urzaiz::conOut << chaineMask;
                urzaiz::AllerA(posit);
                urzaiz::conOut<<_message;
                urzaiz::AllerA(_errorPos);
                urzaiz::conOut << chaineMask;
                urzaiz::AllerA(_errorPos);
                continue;
            }
            _value = (T) (reelTempo1/reelTempo2);
            break;
        }
        else if (totalVirgule == 1){
            auto iterateurVirgule {std::find(std::begin(temp),std::end(temp),',')};
            *iterateurVirgule = '.';
        }
        flux >>_value;
        if (flux.fail()){
            urzaiz::AllerA(0,_errorPos.b+1);
            posit =urzaiz::cursorPos();
            urzaiz::conOut << chaineMask;
            urzaiz::AllerA(posit);
            urzaiz::conOut<<_message;
            urzaiz::AllerA(_errorPos);
            urzaiz::conOut << chaineMask;
            urzaiz::AllerA(_errorPos);
            continue;
        }
        else {
            break;
        }
    }
}
template <typename T>
const urzaiz::Input& operator >>(const urzaiz::Input& entree, T& _content){
    std::cin >> _content;
    return entree;
}
template <>
const urzaiz::Input& operator >> <int> (const urzaiz::Input& entree, int& _content){
    urzaiz::saisieSecurisee<>(entree.getErrorPos(),entree.getErrorMessage(),std::string("-0123456789"),_content);
    return entree;
}
template <>
const urzaiz::Input& operator >> <short> (const urzaiz::Input& entree, short& _content){
    urzaiz::saisieSecurisee<>(entree.getErrorPos(),entree.getErrorMessage(),std::string("-0123456789"),_content);
    return entree;
}
template <>
const urzaiz::Input& operator >> <long int> (const urzaiz::Input& entree, long int& _content){
    urzaiz::saisieSecurisee<>(entree.getErrorPos(),entree.getErrorMessage(),std::string("-0123456789"),_content);
    return entree;
}
template <>
const urzaiz::Input& operator >> <UINT> (const urzaiz::Input& entree, UINT& _content){
    urzaiz::saisieSecurisee<>(entree.getErrorPos(),entree.getErrorMessage(),std::string("0123456789"),_content);
    return entree;
}
template <>
const urzaiz::Input& operator >> <shint> (const urzaiz::Input& entree, shint& _content){
    urzaiz::saisieSecurisee<>(entree.getErrorPos(),entree.getErrorMessage(),std::string("0123456789"),_content);
    return entree;
}
template <>
const urzaiz::Input& operator >> <lint> (const urzaiz::Input& entree, lint& _content){
    urzaiz::saisieSecurisee<>(entree.getErrorPos(),entree.getErrorMessage(),std::string("0123456789"),_content);
    return entree;
}
template <>
const urzaiz::Input& operator >> <float> (const urzaiz::Input& entree, float& _content){
    urzaiz::saisieSecurisee<>(entree.getErrorPos(),entree.getErrorMessage(),std::string("-./eE0123456789"),_content);
    return entree;
}
template <>
const urzaiz::Input& operator >> <double> (const urzaiz::Input& entree, double& _content){
    urzaiz::saisieSecurisee<>(entree.getErrorPos(),entree.getErrorMessage(),std::string("-./eE0123456789"),_content);
    return entree;
}
template<>
const urzaiz::Input& operator >> <Ldouble> (const urzaiz::Input& entree, Ldouble& _content){
    urzaiz::saisieSecurisee<>(entree.getErrorPos(),entree.getErrorMessage(),std::string("-./eE0123456789"),_content);
    return entree;
}
#endif // MY_TEMPLATE
