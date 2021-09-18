//**********CECI EST UNE PETITE PILE D'OUTILS POUR EGAYER UN PEU LA CONSOLE, REALISE PAR URZAIZ CODING*********//
/*Les fonctionnalites :
    -une alternative à std::cin pour gérer les erreurs de saisie des users, gérer l'entrer des nombres flottants
    en utilisant ',' comme dans le système francophone.

    -un système de gestion des couleurs en console.

    -une alternative à cout pour afficher les accents et autres caractères latins en console win 32 "conOut"

    -des fonctions pour encadrer, souligner, déplacer texte et curseur en console, effacer la console.
    ...
    Bonne utilisation
*/





#ifndef MYWINCONLIB_H_INCLUDED
#define MYWINCONLIB_H_INCLUDED
#include <windows.h>
#include <sstream>
#include <algorithm>
#include <limits>
#include <string>

typedef unsigned short int shint;
typedef unsigned long int lint;
typedef long double Ldouble;
namespace urzaiz {
    class Couleur{
    public:
        enum colorReference {NOIR,BLEUFONCE,VERT,BLEUGRIS,MARRON,POURPRE,KAKI,GRISCLAIR,GRIS,BLEU,VERTFLUO,
                                TURQUOISE,ROUGE,ROSEFLUO,JAUNEFLUO,BLANC};
        void setText(colorReference color){
            m_text = color;
        }
        void setFond(colorReference color){
            m_fond = color;
        }
        Couleur (colorReference coulFond = NOIR, colorReference coulTexte = BLANC);
        void applyGlobal() const;
        void applyLocal() const;
        void reset();
    private:
        colorReference getFond() const{
            return m_fond;
        }
        colorReference getText() const{
            return m_text;
        }
        colorReference getGlobalFond() const{
            return m_globalFond;
        }
        colorReference getGlobalText() const{
            return m_globalText;
        }
        const char toHex16Color(colorReference coul) const;
        colorReference m_globalFond;
        colorReference m_globalText;
        colorReference m_fond;
        colorReference m_text;
    };

    struct coord{
        shint a;
        shint b;
        coord();
        coord(shint x, shint y):a(x),b(y){}
        coord(const _COORD& win32COORD);
        coord & operator =(const _COORD& win32COORD);
        coord operator + (const coord& vecteur);
        coord & operator +=(const coord& vecteur);
    };

    class Output {
    public:
        Output (const Output&) = delete;
        Output & operator =(const Output&) = delete;
        static const Output& getOutput(){
            return m_sortie;
        }
        static char endLine;
    private:
        Output(){};
        static Output m_sortie;
    };

    class Input{
    public:
        Input (const Input&) = delete;
        Input& operator =(const Input&) = delete;
        static Input& getInput(){
            return m_entree;
        }
        coord getErrorPos() const {
            return m_errorPos;
        }
        std::string getErrorMessage() const {
            return m_messageErreur;
        }
        void setMessageErreur(std::string const& message);
        void setPositionErreur(const coord& pos);
    private:
        Input();
        static Input m_entree;
        coord m_errorPos;
        std::string m_messageErreur;
    };

    extern urzaiz::Input& conIn;
    extern const urzaiz::Output& conOut;
    void AllerA(shint x, shint y);
    void AllerA(const coord& pos);
    void AllerA(const COORD& pos);
    struct coord cursorPos();
    void souligner(const std::string& chaine = "", const coord& debut = coord(),const char symbole = '*');
    void encadrer(const std::string& chaine, const coord& debut);
    void encadrer(const std::string& chaine, shint x, shint y);
    void encadrer(const std::string& chaine, const COORD& debut);
    void centrer(const std::string& chaine, shint ligne);
    void soulignerEtCentrer(const std::string& chaine = "", shint ligne = 0, const char symbole = '*');
    void encadrerEtCentrer(const std::string& chaine, shint ligne);
    void cls();
    void translation(const std::string& chaine, const coord& vecteur);
    void pause(const std::string& message);
    template<typename T>
    void vider_tampon();
    template <typename T>
    void saisieSecurisee(const coord& _errorPos,const std::string& _message,std::string const& _chaineModele,T& _value);
}
template <typename T>
const urzaiz::Output& operator <<(const urzaiz::Output& sortie, const T& entree);
template <>
const urzaiz::Output& operator << <std::string>(const urzaiz::Output& sortie, const std::string& entree);
const urzaiz::Output& operator <<(const urzaiz::Output& sortie, const char * entree);
template <typename T>
const urzaiz::Input& operator >>(const urzaiz::Input& entree, T& _content);
template <>
const urzaiz::Input& operator >> <int> (const urzaiz::Input& entree, int& _content);
template <>
const urzaiz::Input& operator >> <short> (const urzaiz::Input& entree, short& _content);
template <>
const urzaiz::Input& operator >> <UINT> (const urzaiz::Input& entree, UINT& _content);
template <>
const urzaiz::Input& operator >> <shint> (const urzaiz::Input& entree, shint& _content);
template <>
const urzaiz::Input& operator >> <lint> (const urzaiz::Input& entree, lint& _content);
template <>
const urzaiz::Input& operator >> <long int> (const urzaiz::Input& entree, long int& _content);
template <>
const urzaiz::Input& operator >> <float> (const urzaiz::Input& entree, float& _content);
template <>
const urzaiz::Input& operator >> <double> (const urzaiz::Input& entree, double& _content);
template <>
const urzaiz::Input& operator >> <Ldouble> (const urzaiz::Input& entree, Ldouble& _content);
typedef struct urzaiz::coord Coordinates;
#ifndef INCLUDING_IN_CPP
#include "template.tpp"
#endif // INCLUDING_IN_CPP
#endif // MYWINCONLIB_H_INCLUDED
