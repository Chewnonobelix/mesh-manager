#ifndef MESHFACTORY_H
#define MESHFACTORY_H

#include "mesh.h"

class MeshFactory
{
public:
    MeshFactory();
    /**
     * @brief tetraheder
     * @param hauteur
     * @return Nouveau tetrahédre
     */
    static Mesh tetrahedre(double);

    /**
     * @brief poufCube
     * @param grande face
     * @param petite face
     * @return nouveau pouf cubique
     */
    static Mesh poufCube(double, double);
    /**
     * @brief fez
     * @param petite face
     * @param grande face
     * @param hauteur
     * @param precision
     * @return
     */
    static Mesh fez(double ,double , double , int );

    /**
      Cube taille 1
     * @brief cube
     * @param size
     * @return
     */
    static Mesh cube(int size);

    /** Power cube par quentin (  créer à partir d'un cylindre )
     * @brief cube
     * @return
     */
    static Mesh cube();

    /** Classic cube par Maelyss
     * @brief cube
     * @return
     */
    static Mesh cube(double sizeX, double sizeY, double sizeZ);

    /**
     //TODO Quentin
     * @brief cylinder Créer un cylindre de longueur l et de rayon r
     * @param longueur l
     * @param rayon r
     * @param precision nombre de points sur le rayon
     * @return cylinder
     */
    static Mesh cylindre(double longueur, double rayon, int precision);

    /**
     * @brief cylindreRainures : retourne un cylindre avec des encoches
     * @param longueur
     * @param rayon
     * @param precision
     * @return
     */
    static Mesh cylindreComplexe(double longueur, double rayon, int precision);


    /** Cone taille 1
     * @brief cone
     * @return
     */
    static Mesh cone();

    /**
      Tore
     * @brief tore
     * @return
     */
    static Mesh tore(double rayon, double rTube,int precision);

    /**
     * @brief demiTore
     * @param rayon
     * @param rTube
     * @param precision
     * @return
     */
    static Mesh demiTore(double rayon, double rTube,int precision);

    /**
      Sphère
     * @brief sphereTore créer une sphère à  partir d'un tore
     * @return
     */
    static Mesh sphereTore(int);

    /**
     * @brief cubeComplexe
     * @param precision
     * @param longueur
     * @param largeur
     * @return
     */
    static Mesh cubeComplexe ( int precision, double taille);

    /**
     * @brief sphere
     * @return
     */
    static Mesh sphere(int = 1);

    /**
     * @brief planComplexe Créer un plan 2D 1*1
     * @param precision = nb itèrations
     * @return
     */
    static Mesh planComplexe ( int precision);

    /**
     * @brief rectangleComplexe
     * @param precision
     * @param longueur
     * @param largeur
     * @return
     */
    static Mesh rectangleComplexe ( int precision, double longueur, double largeur);

    static Mesh cylindre();

};

#endif // MESHFACTORY_H
