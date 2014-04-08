﻿#include "mesh.h"
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <QDebug>


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Mesh::Mesh()
{
}

Mesh::Mesh(const Mesh & m): m_tabPoint(m.m_tabPoint), m_tabNorme(m.m_tabNorme), m_tabTopologie(m.m_tabTopologie)
{}

double Mesh::getMaxZ () const
{
    double maxZ = 0.0;
    for (int i = 0 ; i < m_tabPoint.size() ; i++)
    {
        maxZ = (sqrt(m_tabPoint[i].getZ()*m_tabPoint[i].getZ())) > maxZ ? sqrt(m_tabPoint[i].getZ()*m_tabPoint[i].getZ()) : maxZ;
    }
    std::cout<< maxZ << std::endl;
    return maxZ;
}

Vector Mesh::getNormeTriangle ( Point3D A, Point3D B, Point3D C)
{
    /*Nx = UyVz - UzVy
    Ny = UzVx - UxVz
    Nz = UxVy - UyVx
*/
    Vector v = A.toVector() - B.toVector();
    Vector u = C.toVector() - B.toVector();

    return  Vector( u[1]*v[2]- u[2]*v[1],
            u[2]*v[0]- u[0]*v[2],
            u[0]*v[1]- u[1]*v[0]);
}

//https://www.opengl.org/wiki/Calculating_a_Surface_Normal
void Mesh::corrigeNormales ()
{
    m_tabNorme.clear();
    for ( int i = 0 ; i < m_tabTopologie.size() ; i +=6)
    {
        Point3D A = m_tabPoint[m_tabTopologie[i]];
        Point3D B = m_tabPoint[m_tabTopologie[i+2]];
        Point3D C = m_tabPoint[m_tabTopologie[i+4]];

        m_tabNorme.push_back(getNormeTriangle(B,A,C));
        m_tabTopologie[i+1] = m_tabNorme.size()-1;
        m_tabTopologie[i+3] = m_tabNorme.size()-1;
        m_tabTopologie[i+5] = m_tabNorme.size()-1;

    }
}

Mesh Mesh::copie () const
{
    Mesh copie;
    for (int i =0 ; i < m_tabPoint.size() ; i ++)
    {
      copie.m_tabPoint.push_back(m_tabPoint.at(i));
    }

    for (int i =0 ; i < m_tabNorme.size() ; i ++)
    {
        copie.m_tabNorme.push_back(m_tabNorme.at(i));
    }

    for (int i =0 ; i < m_tabTopologie.size() ; i ++)
    {
        copie.m_tabTopologie.push_back(m_tabTopologie.at(i));
    }

    return copie;
}

Mesh operator + (const Mesh& scene, const Mesh& ajout)
{
    Mesh ret(scene);

    int partieBasseTaillePoint = scene.m_tabPoint.size();
    int partieBasseTailleNorm = scene.m_tabNorme.size();

    for (int i = 0 ; i < ajout.m_tabPoint.size(); i ++)
    {
        ret.m_tabPoint.push_back(ajout.m_tabPoint[i]);
    }
    for (int i = 0 ; i < ajout.m_tabNorme.size(); i ++)
    {
        ret.m_tabNorme.push_back(ajout.m_tabNorme[i]);
    }
    for (int i = 0 ; i < ajout.m_tabTopologie.size(); i+=2)
    {
        ret.m_tabTopologie.push_back(ajout.m_tabTopologie[i] + partieBasseTaillePoint);
        ret.m_tabTopologie.push_back(ajout.m_tabTopologie[i+1] + partieBasseTailleNorm);
    }
}

Mesh operator + (const Mesh& scene, const QVector<Mesh>& ajout)
{
    Mesh ret(scene);

    for ( int i = 0; ajout.size() ; i ++)
    {
        ret += ajout[i];
    }
}

Mesh& Mesh::operator += (const Mesh& ajout)
{
    int partieBasseTaillePoint = m_tabPoint.size();
    int partieBasseTailleNorm = m_tabNorme.size();

    for (int i = 0 ; i < ajout.m_tabPoint.size(); i ++)
    {
        m_tabPoint.push_back(ajout.m_tabPoint[i]);
    }
    for (int i = 0 ; i < ajout.m_tabNorme.size(); i ++)
    {
        m_tabNorme.push_back(ajout.m_tabNorme[i]);
    }
    for (int i = 0 ; i < ajout.m_tabTopologie.size(); i+=2)
    {
        m_tabTopologie.push_back(ajout.m_tabTopologie[i] + partieBasseTaillePoint);
        m_tabTopologie.push_back(ajout.m_tabTopologie[i+1] + partieBasseTailleNorm);
    }

    return *this;
}

Mesh& Mesh::operator += (const QVector<Mesh>& ajout)
{
    for ( int i = 0; ajout.size() ; i ++)
    {
        (*this) += ajout[i];
    }

    return *this;
}

bool operator == (const Mesh& m1, const Mesh& m2)
{
    return (m1.m_tabPoint == m2.m_tabPoint) &&
            (m1.m_tabNorme == m2.m_tabNorme) &&
            (m1.m_tabTopologie == m2.m_tabTopologie);
}

Mesh& Mesh::operator = (const Mesh& m)
{
    m_tabPoint.clear();
    m_tabNorme.clear();
    m_tabTopologie.clear();

    m_tabPoint = m.m_tabPoint;
    m_tabNorme = m.m_tabNorme;
    m_tabTopologie = m.m_tabTopologie;

    return *this;
}

void Mesh::rotation(int composante, double angle)
{
    angle = M_PI * angle/ 180;

    double sinAngle = sin ( angle );
    double cosAngle = cos ( angle );
    switch (composante) {
    // Rotation autour de X
    case 0:
        for(int i = 0; i < m_tabPoint.size(); i ++)
        {
            Point3D d = m_tabPoint[i];
            m_tabPoint[i] = Point3D(d.getX(),
                                  cosAngle * d.getY() - sinAngle * d.getZ(),
                                  sinAngle * d.getY() + cosAngle * d.getZ());
        }

        for(int i = 0; i < m_tabNorme.size(); i ++)
        {
            Vector v = m_tabNorme[i];
            m_tabNorme[i] = Vector(
                        v[0],
                    cosAngle * v[1] - sinAngle * v[2],
                    sinAngle * v[1] - cosAngle * v[2]);
        }

        break;
        // Autour de Y
    case 1:
        for(int i = 0; i < m_tabPoint.size(); i ++)
        {
            Point3D d = m_tabPoint[i];
            m_tabPoint[i] = Point3D(cosAngle * d.getX() + sinAngle * d.getZ(),
                                  d.getY(),
                                  - sinAngle * d.getX() + cosAngle * d.getZ());
        }

        for(int i = 0; i < m_tabNorme.size(); i ++)
        {
            Vector v = m_tabNorme[i];
            m_tabNorme[i] = Vector(
                        cosAngle * v[0] + sinAngle * v[2],
                    v[1],
                    -sinAngle * v[0] - cosAngle * v[2]);
        }

        break;
        //Z
    default:
        for(int i = 0; i < m_tabPoint.size(); i ++)
        {
            Point3D d = m_tabPoint[i];
            m_tabPoint[i] = Point3D(cosAngle * d.getX()- sinAngle * d.getY(),
                                  sinAngle * d.getX()+ cosAngle * d.getY(),
                                  d.getZ());
        }

        for(int i = 0; i < m_tabNorme.size(); i ++)
        {
            Vector v = m_tabNorme[i];
            m_tabNorme[i] = Vector(
                        cosAngle * v[0] - sinAngle * v[1],
                    sinAngle * v[0] - cosAngle * v[1],
                    v[2]);
        }
        break;
    }
}

void Mesh::rotation(double thetaX, double thetaY, double thetaZ)
{
    rotation(0, thetaX);
    rotation(1, thetaY);
    rotation(2, thetaZ);
}

void Mesh::translation(double x , double y , double z)
{
    for(int i = 0; i < m_tabPoint.size(); i ++)
    {
        m_tabPoint[i] = Point3D(m_tabPoint[i].getX()+x, m_tabPoint[i].getY()+y,m_tabPoint[i].getZ()+z);
    }

    for(int i = 0; i < m_tabNorme.size(); i ++)
    {
        m_tabNorme[i] = Vector(m_tabNorme[i][0]+x, m_tabNorme[i][1]+y,m_tabNorme[i][2]+z);
    }
}

void Mesh::redimensionner(double x, double y , double z)
{
    for(int i = 0; i < m_tabPoint.size(); i ++)
    {
        m_tabPoint[i] = Point3D(m_tabPoint[i].getX()*x, m_tabPoint[i].getY()*y,m_tabPoint[i].getZ()*z);
    }

    for(int i = 0; i < m_tabNorme.size(); i ++)
    {
        m_tabNorme[i] = Vector(m_tabNorme[i][0]*x, m_tabNorme[i][1]*y,m_tabNorme[i][2]*z);
    }
}

QString Mesh::toString(){

    QString res("#Obj.toString()\no objet\n");
    for (int i = 0 ; i < m_tabPoint.size(); i++){
        res.append(QString("v %1 %2 %3\n").arg(this->m_tabPoint.at(i).getX())
                   .arg(this->m_tabPoint.at(i).getY())
                   .arg(this->m_tabPoint.at(i).getZ()));

    }
    res.append("\n\n #Normes\n");
    for (int i = 0 ; i < m_tabNorme.size(); i++){
        res.append(QString("vn %1 %2 %3\n").arg(m_tabNorme[i][0])
                .arg(m_tabNorme[i][1])
                .arg(m_tabNorme[i][2]));
    }
    res.append("\ng shape");
    res.append("\n\n #Face\n");
    //cout << "taille" << tabTopologie.size()<< endl;
    for (int i = 0 ; i < m_tabTopologie.size()  ; i+=6)
    {
        //std::cout << "i " << i << std::endl;
        QString line = QString("f ");
        line.append(QString("%1//%2 ")
                    .arg(m_tabTopologie.at(i)+1)
                    .arg(m_tabTopologie.at(i+1)+1));

        line.append( QString("%1//%2 ")
                     .arg(m_tabTopologie.at(i+2)+1)
                     .arg(m_tabTopologie.at(i+3)+1));


        line.append( QString("%1//%2\n")
                     .arg(m_tabTopologie.at(i+4)+1)
                     .arg(m_tabTopologie.at(i+5)+1));

        res.append(line);
    }
    return res;
}

void Mesh::writeObj(QString nom)
{
    // Création d'un objet QFile
    QFile file(nom);
    // On ouvre notre fichier en lecture seule et on vérifie l'ouverture
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<<"Fichier"<<nom<<"non ouvert";
        return;
    }

    // Création d'un objet QTextStream à partir de notre objet QFile
    QTextStream flux(&file);
    // On choisit le codec correspondant au jeu de caractère que l'on souhaite ; ici, UTF-8
    flux.setCodec("UTF-8");
    // Ecriture des diffèrentes lignes dans le fichier
    flux << toString() << endl;
}

Mesh Mesh::readObj(QString path)
{
    Mesh m;

    // lecture d'un objet QFile
    QFile file(path);
    printf( "\n%s has been loaded\n\n",path.toLocal8Bit().data() );
    // On ouvre notre fichier en lecture seule et on vérifie l'ouverture
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return m;




    // Création d'un objet QTextStream a  partir de notre objet QFile
    QTextStream flux(&file);

    while (!flux.atEnd())
    {
        QString line = flux.readLine().toLocal8Bit().data();
        QStringList opperation = line.split(" ");

        if (opperation.at(0) == "v")
        {
        //    qDebug() << opperation.at(0);
            Point3D p = Point3D(opperation.at(1).toDouble(),opperation.at(2).toDouble(),opperation.at(3).toDouble());
            m.m_tabPoint.push_back(p);
        }
        else if (opperation.at(0) == "vn")
        {
            Vector vn = Vector(opperation.at(1).toDouble(),opperation.at(2).toDouble(),opperation.at(3).toDouble());
            m.m_tabNorme.push_back(vn);
        }
        else if (opperation.at(0) == "f")
        {

            for (int i=1;i<4;i++)
            {
                QStringList v = opperation.at(i).split("//");

                m.m_tabTopologie.push_back(v.at(0).toInt()-1);
                m.m_tabTopologie.push_back(v.at(1).toInt()-1);
            }

        }
    }



    // On choisit le codec correspondant au jeu de caractère que l'on souhaite ; ici, UTF-8
  //  flux.setCodec("UTF-8");
    // Écriture des différentes lignes dans le fichier
    //flux << data << endl;

    return m;
}

Mesh Mesh::concatenation(Mesh partieHaute,Mesh partieBasse, double rapportPourcent)
{
    Mesh res;
    rapportPourcent = rapportPourcent > 10 ? rapportPourcent / 100 :rapportPourcent;
    double zMax= 0;
    for ( int i = 0 ; i < partieBasse.m_tabPoint.size(); i ++ )
    {
        res.m_tabPoint.push_back(partieBasse.m_tabPoint[i]);
        zMax =  partieBasse.m_tabPoint[i].getZ() > zMax ?  partieBasse.m_tabPoint[i].getZ() : zMax;
    }
    std::cout << "z max " << zMax << std::endl;
    partieHaute.translation(0,0,zMax *rapportPourcent );



    for (int i = 0 ; i < partieBasse.m_tabNorme.size(); i ++)
    {
        res.m_tabNorme.push_back(partieBasse.m_tabNorme[i]);
    }
    for (int i = 0 ; i < partieBasse.m_tabTopologie.size(); i ++)
    {
        res.m_tabTopologie.push_back(partieBasse.m_tabTopologie[i]);
    }


    for (int i = 0 ; i < partieHaute.m_tabPoint.size(); i ++)
    {
        res.m_tabPoint.push_back(partieHaute.m_tabPoint[i]);
    }
    for (int i = 0 ; i < partieHaute.m_tabNorme.size(); i ++)
    {
        res.m_tabNorme.push_back(partieHaute.m_tabNorme[i]);
    }
    int partieBasseTaillePoint = partieBasse.m_tabPoint.size();
    int partieBasseTailleNorm = partieBasse.m_tabNorme.size();
    for (int i = 0 ; i < partieHaute.m_tabTopologie.size(); i+=2)
    {
        res.m_tabTopologie.push_back(partieHaute.m_tabTopologie[i] + partieBasseTaillePoint);
        res.m_tabTopologie.push_back(partieHaute.m_tabTopologie[i+1] + partieBasseTailleNorm);
    }



    return res;
}

void Mesh::subDivideSpherePoint(int precision)
{
    for(int i = 0; i < precision ; i ++)
    {
        QVector<int> temp;

        while(!m_tabTopologie.isEmpty())
        {
            Point3D v1,v2,v3; //Point du triangle avant décomposistion
            Vector n1, n2, n3, wn1, wn2,wn3; //Norme des points (wni nouvelle norme)

            int iv1, iv2,iv3, in1,in2,in3, iw1, iw2, iw3, iwn1, iwn2, iwn3; // Index des points

            iv1 = m_tabTopologie[0];
            v1 = m_tabPoint[iv1];
            in1 = m_tabTopologie[1];
            n1 = m_tabNorme[in1];
            iv2 = m_tabTopologie[2];
            v2 = m_tabPoint[iv2];
            in2 = m_tabTopologie[3];
            n2 = m_tabNorme[in2];
            iv3 = m_tabTopologie[4];
            v3 = m_tabPoint[iv3];
            in3 = m_tabTopologie[5];
            n3 = m_tabNorme[in3];

            for(int i = 0; i < 6; i ++)
            {
                m_tabTopologie.pop_front();
            }
            Point3D w1, w2, w3; //Nouveau point

            w1 = Point3D::fromVector(Normalized(v1.toVector() + v2.toVector()));
            w2 = Point3D::fromVector(Normalized(v1.toVector() + v3.toVector()));
            w3 = Point3D::fromVector(Normalized(v2.toVector() + v3.toVector()));

            iw1 = m_tabPoint.indexOf(w1);
            iw2 = m_tabPoint.indexOf(w2);
            iw3 = m_tabPoint.indexOf(w3);

            if(iw1 == -1)
            {
                iw1 = m_tabPoint.size();
                m_tabPoint<<w1;
            }
            if(iw2 == -1)
            {
                iw2 = m_tabPoint.size();
                m_tabPoint<<w2;
            }
            if(iw3 == -1)
            {
                iw3 = m_tabPoint.size();
                m_tabPoint<<w3;
            }

            float phi, alpha;

            phi = atan(w1.getX()/w1.getY());
            alpha = acos(w1.getZ());

            wn1[0] = (cos(phi)*cos(alpha));
            wn1[1] = (cos(phi)*sin(alpha));
            wn1[2] = (sin(phi));

            phi = atan(w2.getX()/w2.getY());
            alpha = acos(w2.getZ());

            wn2[0] = (cos(phi)*cos(alpha));
            wn2[1] = (cos(phi)*sin(alpha));
            wn2[2] = (sin(phi));

            phi = atan(w3.getX()/w3.getY());
            alpha = acos(w3.getZ());

            wn3[0] = (cos(phi)*cos(alpha));
            wn3[1] = (cos(phi)*sin(alpha));
            wn3[2] = (sin(phi));

            iwn1 = m_tabNorme.indexOf(wn1);
            iwn2 = m_tabNorme.indexOf(wn2);
            iwn3 = m_tabNorme.indexOf(wn3);

            if(iwn1 == -1)
            {
                m_tabNorme<<wn1;
                iwn1 = m_tabNorme.size() - 1;
            }
            if(iwn2 == -1)
            {
                m_tabNorme<<wn2;
                iwn2 = m_tabNorme.size() - 1;
            }
            if(iwn3 == -1)
            {
                m_tabNorme<<wn3;
                iwn3 = m_tabNorme.size() - 1;
            }


            //Triangle v1, w1, w2
            temp<<iv1<<in1<<iw1<<iwn1<<iw2<<iwn2;

            //triangle v2, w1, w3
            temp<<iv2<<in2<<iw1<<iwn1<<iw3<<iwn3;

            //triangle v3, w2, w3
            temp<<iv3<<in3<<iw2<<iwn2<<iw3<<iwn3;

            //Triangle w1,w2,w3
            temp<<iw1<<iwn1<<iw2<<iwn2<<iw3<<iwn3;
        }
        m_tabTopologie = temp;
    }
}

void Mesh::normaliseMesh()
{
    this->translation(-m_tabPoint[0].getX(),- m_tabPoint[0].getY(),- m_tabPoint[0].getZ());
}
