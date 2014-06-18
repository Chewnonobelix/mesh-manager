#include "mesh.h"
#include <QFile>
#include <QTextStream>
#include <iostream>
//#include <QDebug>
#include <cmath>

#include "../../Utility/perlinnoise.h"
#include "meshfactory.h"
#include "../Advance/Terrain/terraincontinu.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace MeshBase
{
    void Mesh::smoothMesh( double deltaX)
    {
        double deltaT = sqrt(2* (deltaX* deltaX));
        QVector<Geometry::Point3D> tabPts;
        for(int i = 0 ; i < m_tabPoint.size() ; i++ )
        {
            tabPts.clear();
            //std::cout << "tourne i " << i << endl;
            Geometry::Point3D ptLocal = m_tabPoint[i];
            for (int j = 0 ; j < m_tabPoint.size(); j ++)
            {
                double dist = ptLocal.distanceXYTo(m_tabPoint[j]);
                if (tabPts.contains(m_tabPoint[j]) )
                { /* Do nothing ) */ }
                else if ( dist < deltaT*1.1 )
                    tabPts.push_back(m_tabPoint[j]);
            }

            if ( tabPts.size() > 5)
            {
                double z = 0;
                for ( int k = 0 ; k < tabPts.size() ; k ++ )
                {
                    z += tabPts[k].getZ(); //( ptLocal.getZ() + (tabPts[k].getZ()/tabPts.size()) ) / 2.0 ;
                }
                z = z/ tabPts.size();
                m_tabPoint[i].setZ(z);
            }
        }
    }

    Mesh::Mesh() : m_tabPoint(), m_tabNorme(), m_tabTopologie()
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

    Geometry::Vector Mesh::getNormeTriangle ( Geometry::Point3D A, Geometry::Point3D B, Geometry::Point3D C)
    {
        /*Nx = UyVz - UzVy
        Ny = UzVx - UxVz
        Nz = UxVy - UyVx
    */
        Geometry::Vector v = A.toVector() - B.toVector();
        Geometry::Vector u = C.toVector() - B.toVector();

        return  Geometry::Vector( u[1]*v[2]- u[2]*v[1],
                u[2]*v[0]- u[0]*v[2],
                u[0]*v[1]- u[1]*v[0]);
    }

    //https://www.opengl.org/wiki/Calculating_a_Surface_Normal
    void Mesh::corrigeNormales ()
    {
        m_tabNorme.clear();
        for ( int i = 0 ; i < m_tabTopologie.size() ; i +=6)
        {
            Geometry::Point3D A = m_tabPoint[m_tabTopologie[i]];
            Geometry::Point3D B = m_tabPoint[m_tabTopologie[i+2]];
            Geometry::Point3D C = m_tabPoint[m_tabTopologie[i+4]];

            m_tabNorme.push_back(getNormeTriangle(A,B,C));
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
                Geometry::Point3D d = m_tabPoint[i];
                m_tabPoint[i] = Geometry::Point3D(d.getX(),
                                        cosAngle * d.getY() - sinAngle * d.getZ(),
                                        sinAngle * d.getY() + cosAngle * d.getZ());
            }

            for(int i = 0; i < m_tabNorme.size(); i ++)
            {
                Geometry::Vector v = m_tabNorme[i];
                m_tabNorme[i] = Geometry::Vector(
                            v[0],
                        cosAngle * v[1] - sinAngle * v[2],
                        sinAngle * v[1] - cosAngle * v[2]);
            }

            break;
            // Autour de Y
        case 1:
            for(int i = 0; i < m_tabPoint.size(); i ++)
            {
                Geometry::Point3D d = m_tabPoint[i];
                m_tabPoint[i] = Geometry::Point3D(cosAngle * d.getX() + sinAngle * d.getZ(),
                                        d.getY(),
                                        - sinAngle * d.getX() + cosAngle * d.getZ());
            }

            for(int i = 0; i < m_tabNorme.size(); i ++)
            {
                Geometry::Vector v = m_tabNorme[i];
                m_tabNorme[i] = Geometry::Vector(
                            cosAngle * v[0] + sinAngle * v[2],
                        v[1],
                        -sinAngle * v[0] - cosAngle * v[2]);
            }

            break;
            //Z
        default:
            for(int i = 0; i < m_tabPoint.size(); i ++)
            {
                Geometry::Point3D d = m_tabPoint[i];
                m_tabPoint[i] = Geometry::Point3D(cosAngle * d.getX()- sinAngle * d.getY(),
                                        sinAngle * d.getX()+ cosAngle * d.getY(),
                                        d.getZ());
            }

            for(int i = 0; i < m_tabNorme.size(); i ++)
            {
                Geometry::Vector v = m_tabNorme[i];
                m_tabNorme[i] = Geometry::Vector(
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
            m_tabPoint[i] = Geometry::Point3D(m_tabPoint[i].getX()+x, m_tabPoint[i].getY()+y,m_tabPoint[i].getZ()+z);
        }

        for(int i = 0; i < m_tabNorme.size(); i ++)
        {
            m_tabNorme[i] = Geometry::Vector(m_tabNorme[i][0]+x, m_tabNorme[i][1]+y,m_tabNorme[i][2]+z);
        }
    }

    void Mesh::redimensionner(double x, double y , double z)
    {
        for(int i = 0; i < m_tabPoint.size(); i ++)
        {
            m_tabPoint[i] = Geometry::Point3D(m_tabPoint[i].getX()*x, m_tabPoint[i].getY()*y,m_tabPoint[i].getZ()*z);
        }

        for(int i = 0; i < m_tabNorme.size(); i ++)
        {
            m_tabNorme[i] = Geometry::Vector(m_tabNorme[i][0]*x, m_tabNorme[i][1]*y,m_tabNorme[i][2]*z);
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
            std::cout<<"Fichier "<<nom.toStdString()<<" non ouvert" << std::endl;
            return;
        }

        // Création d'un objet QTextStream à partir de notre objet QFile
        QTextStream flux(&file);
        // On choisit le codec correspondant au jeu de caractère que l'on souhaite ; ici, UTF-8
        flux.setCodec("UTF-8");
        // Ecriture des diffèrentes lignes dans le fichier
        flux << "#Obj.toString()"<< endl << " o objet" << endl;

        for (int i = 0 ; i < m_tabPoint.size(); i++){
            flux << "v " << m_tabPoint.at(i).getX() << " " << m_tabPoint.at(i).getY() << " " << m_tabPoint.at(i).getZ() << endl;
        }

        flux << endl << "#Normes" << endl;

        for (int i = 0 ; i < m_tabNorme.size(); i++){
            flux << "vn " << m_tabNorme[i][0] << " " << m_tabNorme[i][1] << " " <<m_tabNorme[i][2] << endl;
        }

        flux << endl << "g shape" << endl;
        flux << endl << "#Face" << endl;

        for (int i = 0 ; i < m_tabTopologie.size()  ; i+=6)
        {
            flux << "f " << m_tabTopologie.at(i)+1 << "//" << m_tabTopologie.at(i+1)+1;
            flux << " "  << m_tabTopologie.at(i+2)+1 << "//" << m_tabTopologie.at(i+3)+1;
            flux << " "  << m_tabTopologie.at(i+4)+1 << "//" << m_tabTopologie.at(i+5)+1 << endl;
        }

        flux <<"#fin" << endl;

        file.close();
    }


    void Mesh::writeObjNoNormals(QString nom)
    {
        // Création d'un objet QFile
        QFile file(nom);
        // On ouvre notre fichier en lecture seule et on vérifie l'ouverture
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            std::cout<<"Fichier "<<nom.toStdString()<<" non ouvert" << std::endl;
            return;
        }

        // Création d'un objet QTextStream à partir de notre objet QFile
        QTextStream flux(&file);
        // On choisit le codec correspondant au jeu de caractère que l'on souhaite ; ici, UTF-8
        flux.setCodec("UTF-8");
        // Ecriture des diffèrentes lignes dans le fichier
        flux << "#Obj.toString()"<< endl << "o shape.009" << endl;

        for (int i = 0 ; i < m_tabPoint.size(); i++){
            flux << "v " << m_tabPoint.at(i).getX() << " " << m_tabPoint.at(i).getY() << " " << m_tabPoint.at(i).getZ() << endl;
        }

        flux << endl << "#Face" << endl;
        flux << "usemtl None"<< endl;
        flux << "s 1" << endl;

        for (int i = 0 ; i < m_tabTopologie.size()  ; i+=6)
        {
            flux << "f " << m_tabTopologie.at(i)+1 ;
            flux << " "  << m_tabTopologie.at(i+2)+1 ;
            flux << " "  << m_tabTopologie.at(i+4)+1 << endl;
        }

        flux <<"#fin" << endl;

        file.close();
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
                Geometry::Point3D p = Geometry::Point3D(opperation.at(1).toDouble(),opperation.at(2).toDouble(),opperation.at(3).toDouble());
                m.m_tabPoint.push_back(p);
            }
            else if (opperation.at(0) == "vn")
            {
                Geometry::Vector vn = Geometry::Vector(opperation.at(1).toDouble(),opperation.at(2).toDouble(),opperation.at(3).toDouble());
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
                Geometry::Point3D v1,v2,v3; //Point du triangle avant décomposistion
                Geometry::Vector n1, n2, n3, wn1, wn2,wn3; //Norme des points (wni nouvelle norme)

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
                Geometry::Point3D w1, w2, w3; //Nouveau point

                w1 = Geometry::Point3D::fromVector(Normalized(v1.toVector() + v2.toVector()));
                w2 = Geometry::Point3D::fromVector(Normalized(v1.toVector() + v3.toVector()));
                w3 = Geometry::Point3D::fromVector(Normalized(v2.toVector() + v3.toVector()));

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


    Mesh Mesh::generateurTerrain ()
    {
        //Mesh terrain = Mesh::plan5points();/*
        Mesh terrain = MeshFactory::planComplexe(100);
        terrain.redimensionner(100,100,1);
        /*PerlinNoise noise;
        noise.SetAmplitude(20);
        noise.SetFrequency(00.200);
        noise.SetOctaves(1);
        noise.SetRandomSeed(128);
        noise.SetPersistence(2);*/
        /* int n = 6;
        QVector<double> tabHauteursIn;
        tabHauteursIn << 10 << 5 << 2.5 << 1.25 << 10.0/16.0 << 10.0/32.0;
        QVector<double> tabFrequencesIn;
        tabFrequencesIn << 32 << 16 << 8 << 4 << 2 << 1;

        FractalNoise noise;

        TerrainContinu t(noise);

        for (int i = 0 ; i < terrain.m_tabPoint.size(); i++)
        {
            terrain.m_tabPoint[i].setZ( t.getZ(terrain.m_tabPoint[i].getX(), terrain.m_tabPoint[i].getY()));
        }

        for (int i = 0 ; i < terrain.m_tabPoint.size(); i++)
        {
            terrain.m_tabPoint[i].setZ( noise.GetHeight(terrain.m_tabPoint[i].getX(), terrain.m_tabPoint[i].getY()));
        }


        for (int i = 0 ; i < terrain.m_tabPoint.size(); i++)
        {
            terrain.m_tabPoint[i].setZ( terrain.m_tabPoint[i].getZ()+ 0.5*( noise.GetHeight(terrain.m_tabPoint[i].getY(), terrain.m_tabPoint[i].getX())));
        }*/
        /*for (int l = 1 ; l < 5 ; l ++ )
        {
            terrain.subdivisePlan(octaves, freq, persistence, 10*l);
        }*/
        return terrain;
    }

    bool operator == (const Mesh& m1, const Mesh& m2)
    {
        return (m1.m_tabPoint == m2.m_tabPoint) &&
                (m1.m_tabNorme == m2.m_tabNorme) &&
                (m1.m_tabTopologie == m2.m_tabTopologie);
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
        return ret;
    }

    Mesh operator + (const Mesh& scene, const QVector<Mesh>& ajout)
    {
        Mesh ret(scene);

        for ( int i = 0; ajout.size() ; i ++)
        {
            ret += ajout[i];
        }
        return ret;
    }

    void Mesh::mensurationMesh(Mesh &m, double &xmmin, double &xmax, double &ymin, double &ymax)
    {

        ymin = xmmin = m.m_tabPoint[0].getY();

        xmax = ymax = 0;

        for (Geometry::Point3D p : m.m_tabPoint)

        {

            if ( ymin > p.getY())

                ymin = p.getY();

            if ( xmmin > p.getX())

                xmmin = p.getX();

            if ( ymax < p.getY())

                ymax = p.getY();

            if ( xmax < p.getX())

                xmax = p.getX();

        }

    }
}

