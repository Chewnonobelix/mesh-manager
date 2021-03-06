#include "terraindiscret.h"

#include"../../Base/meshfactory.h"
#include <iostream>
#include <QImage>
#include <QColor>
#include <QRgb>

using namespace MeshAdvance;

TerrainDiscret::TerrainDiscret(): mTailleTerrain(0), mDeltaXY(0)
{
}


TerrainDiscret::TerrainDiscret ( QVector<PairBruitDistance> pairsIn,int taille , double deltaXY, double deltaZ ):
    mTailleTerrain(taille), mDeltaXY(deltaXY), mDeltaZ(deltaZ)
{
    mTabElevation.reserve((mTailleTerrain+1)*(mTailleTerrain+1));

    for ( int i = 0 ; i <= mTailleTerrain ; i ++)
    {
        double x = (double)i * mDeltaXY;
        for (int j = 0 ; j <= mTailleTerrain ; j++)
        {
            double y = (double)j * mDeltaXY;
            double z = 0;
            for (int k = 0 ; k < pairsIn.size() ; k ++)
            {
                z += deltaZ * pairsIn[k].getZ(x,y);
            }
            mTabElevation.push_back(z);
        }
    }
}


TerrainDiscret::TerrainDiscret (TerrainContinu terrainIn,int taille, double deltaXY , double deltaZ):
    mTailleTerrain(taille), mDeltaXY(deltaXY), mDeltaZ(deltaZ)
{
    mTabElevation.reserve((mTailleTerrain+1)*(mTailleTerrain+1));
    for ( int i = 0 ; i <= mTailleTerrain ; i ++)
    {
        double x = (double)i * mDeltaXY;
        for (int j = 0 ; j <= mTailleTerrain ; j++)
        {
            double y = (double)j * mDeltaXY;
            mTabElevation.push_back(terrainIn.getZ(x,y) * mDeltaZ);
        }
    }
}

double TerrainDiscret::getZ(int x, int y)
{
    double res = 0;
    if ( (x + y*( mTailleTerrain+1 )) > mTabElevation.size()-1)
        std::cout<<"err"<<std::endl;
    else
    {
        res = mTabElevation[x + y*( mTailleTerrain+1)];
    }
    return res;
}

QVector<Triangle3D> TerrainDiscret::getTabTriangle()
{
    QVector<Triangle3D>  tab;
    tab.reserve(2*(mTailleTerrain*mTailleTerrain));

    for (int i = 0 ; i < mTailleTerrain; i++ )
    {
        for (int j = 0 ; j < mTailleTerrain; j++ )
        {
            Geometry::Point3D A,B,C,D;
            A = Geometry::Point3D(j*mDeltaXY,i*mDeltaXY,getZ(i,j));
            B = Geometry::Point3D(j*mDeltaXY,(i+1)*mDeltaXY,getZ((i+1),j));
            C = Geometry::Point3D((j+1)*mDeltaXY,(i+1)*mDeltaXY,getZ((i+1),(j+1)));
            D = Geometry::Point3D((j+1)*mDeltaXY,i*mDeltaXY,getZ(i,(j+1)));

            Triangle3D ta (A,B,D);
            Triangle3D tb (B,C,D);
            tab << ta << tb;
        }
    }

    return tab;
}


double TerrainDiscret::getZ(int x)
{
    if ( x < mTabElevation.size())
        return mTabElevation[x];
    else
    {
        std::cerr << "ERR - Depassement de capacité TerrainDiscret::getZ(int)" << std::endl;
        return 0.0;
    }
}


MeshBase::Mesh TerrainDiscret::getMesh()
{
    mMesh = MeshBase::MeshFactory::planComplexe(mTailleTerrain);

    mMesh.redimensionner(mTailleTerrain*mDeltaXY, mTailleTerrain*mDeltaXY,mDeltaZ);
    for ( int i = 0 ; i < mMesh.m_tabPoint.size() ; i++ )
    {
        double z = getZ(i);
        mMesh.m_tabPoint[i].setZ(z);
    }
    return mMesh;
}


QVector<double> TerrainDiscret::getTabElevation() const
{
    return mTabElevation;
}

void TerrainDiscret::setTabElevation(const QVector<double> &value)
{
    mTabElevation = value;
}
bool TerrainDiscret::contient ( double x, double y, QPair<Geometry::Point3D ,Geometry::Point3D > pairIn)
{
    bool ret = false;
    if( x >= pairIn.first.getX() && x <= pairIn.second.getX())
        if ( y >= pairIn.first.getY() && y <= pairIn.second.getY())
            ret = true;

    return ret;
}


/**
 * @brief TerrainDiscret : constructeur avec multi ensembles
 * @param fonctionIn
 */
TerrainDiscret::TerrainDiscret(QVector<QPair<QPair<Geometry::Point3D ,Geometry::Point3D >, TerrainContinu  > > fonctionIn, int nbPoints, double deltaXY, double deltaZ) :
    TabEnembles( fonctionIn), mTailleTerrain(nbPoints), mDeltaXY(deltaXY), mDeltaZ(deltaZ)
{
    mTabElevation.reserve((1+mTailleTerrain)*(1+mTailleTerrain));
    for ( int i = 0 ; i <= mTailleTerrain ; i ++)
    {
        double x = (double)i * mDeltaXY;
        for (int j = 0 ; j <= mTailleTerrain ; j++)
        {
            double y = (double)j * mDeltaXY;
            mTabElevation.push_back(0.0);
            for (int k = 0 ; k < TabEnembles.size() ; k ++ )
            {
                if ( contient ( x, y,TabEnembles[k].first))
                    mTabElevation[mTabElevation.size()-1] += mDeltaZ * TabEnembles[k].second.getZ(x,y);
            }
        }
    }
}



TerrainDiscret::TerrainDiscret ( QString cheminNomDeFichier, double deltaXY, double deltaZ ):
    mDeltaXY(deltaXY), mDeltaZ(deltaZ)
{
    QImage image(cheminNomDeFichier);

    int largeur = image.width();
    int hauteur = image.height();

    mTailleTerrain = largeur -1 ;
    mTabElevation.reserve( hauteur * largeur);

    for (int i = 0 ; i < hauteur ; i ++ )
    {
        for (int j = 0 ; j < largeur ; j ++)
        {
            QRgb pixel = image.pixel(j, i);
            mTabElevation.push_back(qGray(pixel)*deltaZ);
        }
    }
    std::cout << "fini" << mTabElevation.size() << std::endl;
}


void TerrainDiscret::coupeSommets ( double hauteurMax, double facteur )
{

    double hauteurReel = hauteurMax * mDeltaZ;

    for ( int i = 0 ; i < mTabElevation.size() ; i ++ )
    {
        if ( mTabElevation[i] > hauteurReel )
            mTabElevation[i] = hauteurReel - mTabElevation[i]/facteur;
    }
}


void  TerrainDiscret::coupeCreux ( double hauteurMin, double facteur)
{
    double hauteurReel = hauteurMin * mDeltaZ;
    for ( int i = 0 ; i < mTabElevation.size() ; i ++ )
    {
        if ( mTabElevation[i] < hauteurReel )
            mTabElevation[i] = hauteurReel + mTabElevation[i]/facteur;
    }
}


