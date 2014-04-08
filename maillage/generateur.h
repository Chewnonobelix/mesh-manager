#ifndef GENERATEUR_H
#define GENERATEUR_H

#include "mesh.h"

class Generateur
{
public:
    Generateur();
    /**
     * @brief generateurAlumette Génère une alummette
     * @return
     */
    static Mesh generateurAlumette ();

    static Mesh generateurAlumette (int i);
    /**
     * @brief generateurColonne Génère une colonne de hauteur 1.
     * @return
     */
    static Mesh generateurColonne ();
    /**
     * @brief generateurDalle Génère une dalle à partir d'un cube
     * @param taille
     * @return
     */
    static Mesh generateurDalle (double taille);
    /**
     * @brief generateurBaseColonnes Génère une base rectangulaire avec des colones de chaque coté
     * @param taille
     * @return
     */
    static Mesh generateurBaseColonnes (double taille);
    /**
     * @brief generateurToitTore génère un toit avec
     * @param taille
     * @param hauteur
     * @return
     */
    static Mesh generateurToitTore ( double taille, double hauteur);


    /**
     * @brief generateurCoque Dessine une coqe de taille t, de largeur taille/5
     * Avec des alumettes ^^
     * @return
     */
    static Mesh generateurCoque (double taille);

    /**
     * @brief planGouteEau retourne un plan 1 * 1 déformé par une goutte d'eau
     * @param precision
     * @return
     */
    static Mesh planGouteEau ( double precision );

    /**
      Non fonctionnel
     * @brief cylindreComplexe dessine un cylindre complexe;
     * @param longueur
     * @param rayon
     * @param precision
     * @return
     */
    static Mesh cylindreComplexe (double longueur, double rayon, double precision);

    /**
     * @brief maisonSimple dessine une maison simple de taille t
     * @param taille
     * @return
     */
    static Mesh maisonSimple ( double taille);

    /**
     * @brief retourne un toit simple de taille 1*1*1
     * @return
     */
    static Mesh toitSimpleFez ();

    /**
     * @brief Génère le temple Grec :)
     * @param taille du temple
     * @return
     */
    static Mesh generateurTemple ( double taille );

    /**
     * @brief Génère un pentraedre de taille 1*1*1
     * @return
     */
    static Mesh pentaedrePyramidal ();

    /**
     * @brief génère un plan ondulé pour immiter les tuiles
     * @return
     */
    static Mesh generateurPlanOnduleeTuile();

    /**
     * @brief génération du signe du gémeaux (schéma simple)
     * @param taille
     * @return
     */
    static Mesh generateurGemeau();

    static Mesh generateurColoneStyle();	
};

#endif // GENERATEUR_H
