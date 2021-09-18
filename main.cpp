#include <iostream>
#include <sstream>
#include <limits>
#define INCLUDING_IN_CPP
#include "MyWinconLib.h"

//********constantes et attributs statiques******//

char urzaiz::Output::endLine = '\n';
urzaiz::Output urzaiz::Output::m_sortie;
urzaiz::Input urzaiz::Input::m_entree;
const urzaiz::Output& urzaiz::conOut(urzaiz::Output::getOutput());
urzaiz::Input&  urzaiz::conIn(urzaiz::Input::getInput());
//********fin constantes et attributs statiques*********//


/*fonctions membres des classes du namespace*/



//*******classe couleur debut*******//

urzaiz::Couleur::Couleur (colorReference coulFond, colorReference coulTexte):
    m_fond(coulFond), m_text(coulTexte)
{
    m_globalFond = NOIR;
    m_globalText = BLANC;
}
void urzaiz::Couleur::applyGlobal() const{
    std::stringstream ss;
    ss<<"color "<<this->toHex16Color(this->getGlobalFond())<<this->toHex16Color(this->getGlobalText());
    std::string command = ss.str();
    system(command.c_str());
}
void urzaiz::Couleur::applyLocal() const{
    HANDLE mansortie = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(mansortie,this->getFond()*16 + this->getText());
}
void urzaiz::Couleur::reset(){
    this->setFond(urzaiz::Couleur::NOIR);
    this->setText(urzaiz::Couleur::BLANC);
    this->applyLocal();
}
const char urzaiz::Couleur::toHex16Color(urzaiz::Couleur::colorReference couleur) const{
    if(couleur >= 0 && couleur <= 9){
        return (char) (48 + (couleur));
    }
    return (char) (55 + (couleur));
}
//*******classe couleur fin*******//


//*******classe coord debut*******//

urzaiz::coord::coord(){
    this->a = 0;
    this->b = 0;
}
urzaiz::coord::coord(const _COORD& pos){
    this->a = pos.X;
    this->b = pos.Y;
}
urzaiz::coord& urzaiz::coord::operator=( const _COORD& win32COORD){
    this->a = win32COORD.X;
    this->b = win32COORD.Y;
    return * this;
}
urzaiz::coord urzaiz::coord::operator + (const urzaiz::coord& vecteur){
    Coordinates retour;
    retour.a = this->a + vecteur.a;
    retour.b = this->b + vecteur.b;
    return retour;
}
urzaiz::coord & urzaiz::coord::operator +=(const urzaiz::coord& vecteur){
    this->a += vecteur.a;
    this->b += vecteur.b;
    return * this;
}
//*******classe coord fin*******//


//*******classe output debut*******//

const urzaiz::Output& operator <<(const urzaiz::Output& sortie, const char * entree){
        std::string chaine(entree);
        return sortie << chaine;
}
//*******classe output fin*******//



//*******classe input debut*******//

urzaiz::Input::Input(): m_errorPos(urzaiz::cursorPos()),m_messageErreur("Saisie incorrecte ...")
{
}
void urzaiz::Input::setMessageErreur(std::string const& message){
    this->m_messageErreur = message;
}
void urzaiz::Input::setPositionErreur(const coord& pos){
    this->m_errorPos = pos;
}
//*******classe input fin*******//


//*******fonctions du namespace debut*******//


void urzaiz::AllerA(shint x, shint y){
    COORD position = {x,y};
    HANDLE mansortie = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(mansortie,position);
}
void urzaiz::AllerA(const Coordinates& pos){
    COORD position = {pos.a,pos.b};
    HANDLE mansortie = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(mansortie,position);
}
void urzaiz::AllerA(const COORD& pos){
    HANDLE mansortie = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(mansortie,pos);
}
Coordinates urzaiz::cursorPos(){
    HANDLE mansortie = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(mansortie,&csbi);
    return csbi.dwCursorPosition;
}
void urzaiz::souligner(const std::string& chaine, const Coordinates& debut,const char symbole){
    std::string ligne;
    for (shint i(0); i<chaine.size(); i++){
        ligne+=symbole;
    }
    urzaiz::AllerA(debut);
    urzaiz::conOut << chaine <<urzaiz::Output::endLine;
    urzaiz::AllerA(debut.a,debut.b + 1);
    urzaiz::conOut << ligne;
}
void urzaiz::encadrer(const std::string& chaine, const Coordinates& debut){
    shint x = debut.a;
    shint y = debut.b;
    debut.a == 0? x+=1:x;
    debut.b == 0? y+=1:y;
    urzaiz::AllerA(x-1,y-1);
    for(shint i(0);i < chaine.size()+2; i++){
        urzaiz::conOut << '*';
    }
    urzaiz::AllerA(x-2,y);
    urzaiz::conOut << '*';
    urzaiz::AllerA(x-1,y+1);
    for(shint i(0);i< chaine.size()+2; i++){
        urzaiz::conOut << '*';
    }
    urzaiz::AllerA(x+chaine.size() + 1,y);
    urzaiz::conOut << '*';
    urzaiz::AllerA(x,y);
    urzaiz::conOut << chaine;
}
void urzaiz::encadrer(const std::string& chaine, const COORD& debut){
    shint x = debut.X;
    shint y = debut.Y;
    debut.X == 0? x+=1:x;
    debut.Y == 0? y+=1:y;
    urzaiz::AllerA(x-1,y-1);
    for(shint i(0);i < chaine.size()+2; i++){
        urzaiz::conOut << '*';
    }
    urzaiz::AllerA(x-2,y);
    urzaiz::conOut << '*';
    urzaiz::AllerA(x-1,y++);
    for(shint i(0);i< chaine.size()+2; i++){
        urzaiz::conOut << '*';
    }
    urzaiz::AllerA(x+chaine.size() + 1,y);
    urzaiz::conOut << '*';
}
void urzaiz::encadrer(const std::string& chaine, shint x, shint y){
    x == 0? x++:x=x;
    y == 0? y++:y=y;
    urzaiz::AllerA(x-1,y-1);
    for(shint i(0);i < chaine.size()+2; i++){
        urzaiz::conOut << '*';
    }
    urzaiz::AllerA(x-2,y);
    urzaiz::conOut << '*';
    urzaiz::AllerA(x-1,y++);
    for(shint i(0);i< chaine.size()+2; i++){
        urzaiz::conOut << '*';
    }
    urzaiz::AllerA(x+chaine.size() + 1,y);
    urzaiz::conOut << '*';
    urzaiz::AllerA(x,y);
    urzaiz::conOut << chaine;
}
void urzaiz::encadrerEtCentrer(const std::string& chaine,shint ligne){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE mansortie = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(mansortie,&csbi);
    shint centre(0);
    centre = (csbi.dwSize.X - chaine.size()) / 2;
    Coordinates debut (centre - 1, ligne);
    urzaiz::encadrer(chaine,debut);
}
void urzaiz::soulignerEtCentrer(const std::string& chaine,shint ligne,const char symbole){
    urzaiz::centrer(chaine,ligne);
    std::string ligneC;
    Coordinates pos = urzaiz::cursorPos();
    pos.a = pos.a - chaine.size();
    pos.b = pos.b + 1;
    urzaiz::AllerA(pos);
    for(int i (0); i<chaine.size(); i++){
        ligneC += symbole;
    }
    urzaiz::conOut << ligneC;
}
void urzaiz::centrer(const std::string& chaine, shint ligne){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE mansortie = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(mansortie,&csbi);
    COORD taille = csbi.dwSize;
    shint x = (shint) (taille.X - chaine.size())/2;
    urzaiz::AllerA(x,ligne);
    urzaiz::conOut << chaine;
}
void urzaiz::cls(){
    HANDLE mansortie = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD consoleSize;
    DWORD writtenChars;
    COORD debut = {0,0};
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(!GetConsoleScreenBufferInfo(mansortie,&csbi)){
        std::cerr << "Error on access console"<<std::endl;
        return;
    }
    consoleSize = csbi.dwSize.X * csbi.dwSize.Y;
    if(!FillConsoleOutputCharacterA(mansortie,(TCHAR) ' ',consoleSize,debut,&writtenChars)){
        std::cerr << "Error while clearing screen"<<std::endl;
        return;
    }
    if(!FillConsoleOutputAttribute(mansortie,csbi.wAttributes,consoleSize,debut,&writtenChars)){
        std::cerr << "Error while attempting to set attributes" <<std::endl;
        return;
    }
    if(!SetConsoleCursorPosition(mansortie,debut)){
        std::cerr << "Error while positioning the cursor" <<std::endl;
    }
}
void urzaiz::translation(const std::string& chaine, const coord& vecteur){
    urzaiz::AllerA(urzaiz::cursorPos() + vecteur);
}
void urzaiz::pause(const std::string& message){
    urzaiz::conOut << message;
    std::cin.seekg(0,std::ios::end);
    if (std::cin.fail()){
        std::cin.ignore();
    }
    else{
        std::cin.ignore();
        std::cin.ignore();
    }
}
//*******fonctions du namespace fin*******//
