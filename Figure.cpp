#include "Polygone.cpp"
#include <vector>
#include <cmath>
///-------CUBE------------------------------------------------------------
class Cube
{
private:
    int PointNumber;
    int PointBound;

    double diffAngle;
    double S; double V;
    double FigureHeight;
    double Radius;

    sf::Color FigureColor;

    std::vector<Polygone> Polygons;

    Point cent;
public:
    std::vector<Point> POINTS;
    std::vector<Point> createPoints()
    {
        for(double i = 0; i<360; i+=diffAngle)
        {
            double x = cent.get_x()+Radius*cos((i+45)*GTR);
            double y = cent.get_y()+Radius*sin((i+45)*GTR);
            double z = cent.get_z()-(FigureHeight/2);

            if(i>180)
            {
                if(FigureColor.r<240)
                    FigureColor.r+=15;
                if(FigureColor.g<240)
                    FigureColor.g+=15;
                if(FigureColor.b<240)
                    FigureColor.b+=15;
            }
            else
            {
                if(FigureColor.r>15)
                    FigureColor.r-=15;
                if(FigureColor.g>15)
                    FigureColor.g-=15;
                if(FigureColor.b>15)
                    FigureColor.b-=15;
            }
            Point temp_neg (x,y,z, FigureColor);
            POINTS.push_back(temp_neg);
        }
        for(double i = 0; i<360; i+=diffAngle)
        {
            double x = cent.get_x()+Radius*cos((i+45)*GTR);
            double y = cent.get_y()+Radius*sin((i+45)*GTR);
            double z = cent.get_z()+(FigureHeight/2);

            if(i>180)
            {
                if(FigureColor.r<240)
                    FigureColor.r+=15;
                if(FigureColor.g<240)
                    FigureColor.g+=15;
                if(FigureColor.b<240)
                    FigureColor.b+=15;
            }
            else
            {
                if(FigureColor.r>15)
                    FigureColor.r-=15;
                if(FigureColor.g>15)
                    FigureColor.g-=15;
                if(FigureColor.b>15)
                    FigureColor.b-=15;
            }
            Point temp_pos (x,y,z, FigureColor);
            POINTS.push_back(temp_pos);
        }
        Point Bottom(cent.get_x(), cent.get_y(), cent.get_z()-FigureHeight/2, FigureColor);
        Point Upper(cent.get_x(), cent.get_y(), cent.get_z()+FigureHeight/2, FigureColor);
        POINTS.push_back(Bottom);
        POINTS.push_back(Upper);
        POINTS.push_back(cent);

        return POINTS;
    }

    std::vector<Polygone> createPolygons() //We push index of POINTS to use it via render-engine
    {
        for(int i=0; i<PointBound; i++)
        {
            Polygone temp_one;
            Polygone temp_two;
            if(i!=3)
            {
                temp_one = Polygone(i+PointBound, i+1, i, POINTS);
                temp_two = Polygone(i+PointBound, i+1, i+PointBound+1, POINTS);
            }
            else
            {
                temp_one = Polygone(i+PointBound, 0, i+1, POINTS);
                temp_two = Polygone(i+PointBound, 0, i, POINTS);
            }
            Polygons.push_back(temp_one);
            Polygons.push_back(temp_two);
        }
        for(int i=0; i<PointBound; i++)
        {
            Polygone temp_bottom;
            if(i!=3)
                temp_bottom = Polygone(i, i+1, (PointBound*2), POINTS);
            else
                temp_bottom = Polygone(i, 0, (PointBound*2), POINTS);
            Polygons.push_back(temp_bottom);
        }
        for(int i=0; i<PointBound; i++)
        {
            Polygone temp_bottom;
            if(i!=3)
                temp_bottom = Polygone(i+PointBound, i+1+PointBound, (PointBound*2)+1, POINTS);
            else
                temp_bottom = Polygone(i+PointBound, PointBound, (PointBound*2)+1, POINTS);
            Polygons.push_back(temp_bottom);
        }

        return Polygons;
    }
    std::vector<Polygone> getTriangle()
    {
            return Polygons;
    }
    std::vector<Point> getPOINTS()
    {
        return POINTS;
    }

    Cube(double BasicLine, Point cent, sf::Color FigureColor)
    {
        this->FigureColor = FigureColor;
        this->cent = cent;
        FigureHeight = BasicLine;
        Radius=FigureHeight*sqrt(2)/2;
        PointNumber = 8;
        PointBound = 4;
        diffAngle = 90;
        POINTS = createPoints();
        Polygons = createPolygons();
        S = pow(BasicLine, 2)*6;
        V = pow(BasicLine, 3);
    }

    Cube(double BasicLine, Point cent, sf::CircleShape PointShape)
    {
        this->cent = cent;
        FigureHeight = Radius = BasicLine;
        PointNumber = 8;
        diffAngle = 90;
        POINTS=createPoints();
        Polygons = createPolygons();
        for(unsigned long long i = 0; i<POINTS.size()-3; i++)
            POINTS[i].setShape(PointShape);
        S = pow(BasicLine, 2)*6;
        V =BasicLine*BasicLine*BasicLine;
    }

    int getPointBound()
    {
        return PointBound;
    }
    int getPointNumber()
    {
        return PointNumber;
    }
    double getS()
    {
        return S;
    }
    double getV()
    {
        return V;
    }
};
///---------PRISM-CYLINDER---------------------------------------------------
class Prism_Cylinder
{
private:
    int PointNumber;
    int PointBound;
    double S; double V;

    sf::Color FigureColor;

    double diffAngle;
    double FigureHeight;
    double Radius;

    Point cent;

    std::vector<Polygone> Polygons;
public:
    std::vector<Point> POINTS;
    Point getCenter()
    {
        return cent;
    }
    std::vector<Point> createPoints()
    {
        for(double i = 0; i<360; i+=diffAngle)
        {
            double x = cent.get_x()+Radius*cos((i+45)*GTR);
            double y = cent.get_y()+Radius*sin((i+45)*GTR);
            double z = cent.get_z()-(FigureHeight/2);

            if(i>180)
            {
                if(FigureColor.r<240)
                    FigureColor.r+=15;
                if(FigureColor.g<240)
                    FigureColor.g+=15;
                if(FigureColor.b<240)
                    FigureColor.b+=15;
            }
            else
            {
                if(FigureColor.r>15)
                    FigureColor.r-=15;
                if(FigureColor.g>15)
                    FigureColor.g-=15;
                if(FigureColor.b>15)
                    FigureColor.b-=15;
            }
            Point temp_neg (x,y,z, FigureColor);
            POINTS.push_back(temp_neg);
        }
        for(double i = 0; i<360; i+=diffAngle)
        {
            double x = cent.get_x()+Radius*cos((i+45)*GTR);
            double y = cent.get_y()+Radius*sin((i+45)*GTR);
            double z = cent.get_z()+(FigureHeight/2);

            if(i>180)
            {
                if(FigureColor.r<240)
                    FigureColor.r+=15;
                if(FigureColor.g<240)
                    FigureColor.g+=15;
                if(FigureColor.b<240)
                    FigureColor.b+=15;
            }
            else
            {
                if(FigureColor.r>15)
                    FigureColor.r-=15;
                if(FigureColor.g>15)
                    FigureColor.g-=15;
                if(FigureColor.b>15)
                    FigureColor.b-=15;
            }
            Point temp_pos (x,y,z, FigureColor);
            POINTS.push_back(temp_pos);
        }
        Point Bottom(cent.get_x(), cent.get_y(), cent.get_z()-FigureHeight/2, FigureColor);
        Point Upper(cent.get_x(), cent.get_y(), cent.get_z()+FigureHeight/2, FigureColor);
        POINTS.push_back(Bottom);
        POINTS.push_back(Upper);

        POINTS.push_back(cent);

        return POINTS;
    }

    std::vector<Polygone> createPolygons() //We push index of POINTS to use it via render-engine
    {
        for(int i=0; i<PointBound; i++)
        {
            Polygone temp_one;
            Polygone temp_two;
            if(i!=PointBound-1)
            {
                temp_one = Polygone(i+1, i, i+PointBound, POINTS);
                temp_two = Polygone(i+1, i+PointBound, i+1+PointBound, POINTS);
            }
            else
            {
                temp_one = Polygone(0, i, i+PointBound, POINTS);
                temp_two = Polygone(0, PointBound, i+PointBound, POINTS);
            }
            Polygons.push_back(temp_one);
            Polygons.push_back(temp_two);
        }
        for(int i = 0; i<PointBound; i++)
        {
            Polygone temp_one;
            if(i!=PointBound-1)
                temp_one = Polygone(PointNumber, i, i+1, POINTS);
            else
                temp_one = Polygone(PointNumber, i, 0, POINTS);
            Polygons.push_back(temp_one);
        }
        for(int i = 0; i<PointBound; i++)
        {
            Polygone temp_two;
            if(i!=PointBound-1)
                temp_two = Polygone(PointNumber+1, i+PointBound, i+1+PointBound, POINTS);
            else
                temp_two = Polygone(PointNumber+1, i+PointBound, PointBound, POINTS);
            Polygons.push_back(temp_two);
        }
        return Polygons;
    }

    std::vector<Polygone> getTriangle()
    {
        return Polygons;
    }
    std::vector<Point> getPOINTS()
    {
        return POINTS;
    }

    Prism_Cylinder(double FigureHeight, double Radius, int PointNumber,
                    Point cent, sf::Color FigureColor)
    {
        this->FigureColor = FigureColor;
        this->FigureHeight = FigureHeight;
        this->Radius = Radius;
        this->PointNumber = PointNumber;
        this->cent = cent;
        PointBound = PointNumber/2;
        diffAngle = 360/PointBound;
        S = 2*M_PI*(pow(Radius, 2)+Radius*FigureHeight);
        V = M_PI*pow(Radius, 2)*FigureHeight;

        POINTS = createPoints();
        Polygons = createPolygons();
    }

    Prism_Cylinder(double BasicLine, double R, int number, Point cent, sf::CircleShape PointShape)
    {
        this->cent = cent;
        FigureHeight = BasicLine;
        Radius = R;
        PointNumber = number;
        diffAngle = 720/number;
        POINTS=createPoints();
        for(unsigned long long i = 0; i<POINTS.size()-3; i++)
        POINTS[i].setShape(PointShape);
        S = 2*M_PI*(pow(Radius, 2)+Radius*FigureHeight);
        V = M_PI*pow(Radius, 2)*FigureHeight;
    }
    double getS()
    {
        return S;
    }
    double getV()
    {
        return V;
    }
};
///-----------PYRAMID-CONE-----------------------------------------------------------
class Pyramid_Cone
{
private:
    int PointNumber;

    double diffAngle;
    double FigureHeight;
    double Radius;
    double S; double V;

    sf::Color FigureColor;

    std::vector<Polygone> Polygons;
    Point cent;
public:
    std::vector<Point> POINTS;
    Point getCenter()
    {
        return cent;
    }
    std::vector<Point> createPoints()
    {

        Point S (cent.get_x(), cent.get_y(), cent.get_z()+FigureHeight/2, FigureColor);
        POINTS.push_back(S);
        Point antiS (cent.get_x(), cent.get_y(), cent.get_z()-FigureHeight/2, FigureColor);
        POINTS.push_back(antiS);


        for(double i = 0; i<360; i+=diffAngle)
        {
            double x = cent.get_x()+Radius*cos((i+45)*GTR);
            double y = cent.get_y()+Radius*sin((i+45)*GTR);
            double z = cent.get_z()-(FigureHeight/2);
            if(i<180)
            {
                if(FigureColor.r<245)
                    FigureColor.r+=10;
                if(FigureColor.g<245)
                    FigureColor.g+=10;
                if(FigureColor.b<245)
                    FigureColor.b+=10;
            }
            else
            {
                if(FigureColor.r>245)
                    FigureColor.r-=10;
                if(FigureColor.g>245)
                    FigureColor.g-=10;
                if(FigureColor.b>245)
                    FigureColor.b-=10;
            }
            Point temp_neg (x,y,z, FigureColor);
            POINTS.push_back(temp_neg);
        }
        POINTS.push_back(cent);
        return POINTS;
    }

    std::vector<Polygone> createPolygons()    //We push index of POINTS to use it via render-engine
    {
        for (int i = 2; i<=PointNumber; i++)
        {
            Polygone temp;
            if(i!=PointNumber)
                temp = Polygone(0,i,i+1, POINTS);
            else
                temp = Polygone(0,PointNumber,2, POINTS);
            Polygons.push_back(temp);
        }
        for (int i = 2; i<=PointNumber; i++)
        {
            Polygone antiTemp;
            if(i!=PointNumber)
                antiTemp = Polygone(1,i,(i+1), POINTS);
            else
                antiTemp = Polygone(1,PointNumber,2, POINTS);
            Polygons.push_back(antiTemp);
        }
        return Polygons;
    }

    std::vector<Polygone> getTriangle()
    {
        return Polygons;
    }
    std::vector<Point> getPOINTS()
    {
        return POINTS;
    }

    Pyramid_Cone(double FigureHeight, double Radius, int PointNumber,
                  Point cent, sf::Color FigureColor)
    {
        double L = sqrt(pow(Radius, 2)+pow(FigureHeight, 2));
        this->FigureHeight = FigureHeight;
        this->Radius = Radius;
        this->PointNumber = PointNumber;
        this->FigureColor = FigureColor;
        this->cent = cent;
        diffAngle = 360/(PointNumber-1);
        POINTS = createPoints();
        Polygons = createPolygons();
        S = M_PI*Radius*(Radius+L);
        V = (1.f/3.f)*M_PI*pow(Radius, 2)*FigureHeight;
    }

    Pyramid_Cone(double BasicLine, double R, int number, Point cent, sf::CircleShape PointShape)
    {
        double L = sqrt(pow(Radius, 2)+pow(FigureHeight, 2));
        this->cent = cent;
        FigureHeight = BasicLine;
        Radius = R;
        PointNumber = number;
        diffAngle = 360/(number-1);
        POINTS=createPoints();
        for(unsigned long long i = 0; i<POINTS.size(); i++)
            POINTS[i].setShape(PointShape);
        S = M_PI*Radius*(Radius+L);
        V = (1.f/3.f)*M_PI*pow(Radius, 2)*FigureHeight;
    }
    double getS()
    {
        return S;
    }
    double getV()
    {
        return V;
    }
};

///------SPHERE------------------------------------------------------
class Sphere
{
private:
    unsigned long long PointNumber;
    unsigned long long PointPack;
    double Radius;
    double diffAngle;
    double S; double V;

    std::vector<Polygone> Polygons;
    std::vector<Point> POINTS;

    sf::Color FigureColor;

    Point cent;
public:
    std::vector<Point> createPoints(Point cent)
    {
        Point Upper (cent.get_x(), cent.get_y(), cent.get_z()+Radius, FigureColor);
        Point Bottom (cent.get_x(), cent.get_y(), cent.get_z()-Radius, FigureColor);
        POINTS.push_back(Upper);
        Point temp;
        for(double j =90-diffAngle; j>=-90+diffAngle; j-=diffAngle)
        {
            double z = cent.get_z()+Radius*sin(j*GTR);
            double Radius_xy = Radius*cos(j*GTR);
            for(double i = 0; i<360;i+=diffAngle)
            {

                double x = cent.get_x()+Radius_xy*cos(i*GTR);
                double y = cent.get_y()+Radius_xy*sin(i*GTR);

                temp = Point(x,y,z);
                POINTS.push_back(temp);
            }
        }
        for(unsigned long long i = 0; i<POINTS.size(); i++)
        {
               if(i%PointPack==0)
                {
                if(FigureColor.r<235)
                    FigureColor.r+=20;
                if(FigureColor.g<235)
                    FigureColor.g+=20;
                if(FigureColor.b<235)
                    FigureColor.b+=20;

                if(FigureColor.r>235)
                    FigureColor.r-=20;
                if(FigureColor.g>235)
                    FigureColor.g-=20;
                if(FigureColor.b>235)
                    FigureColor.b-=20;
                }
            POINTS[i].setColor(FigureColor);
        }


        POINTS.push_back(Bottom);
        POINTS.push_back(cent);


        return POINTS;
    }

    std::vector<Polygone> createPolygons()    //We push index of POINTS to use it via render-engine
    {
       std::cout<<PointPack<<std::endl;
       for(unsigned long long i = 1; i<=PointPack; i++)
       {
           Polygone temp;
           if(i!=PointPack)
                temp = Polygone(0, i, i+1, POINTS);
            else
                temp = Polygone(0, i, 1, POINTS);
            Polygons.push_back(temp);
       }

       for(unsigned long long k = 0;k<((PointNumber-2)/(PointPack))-1; k++)
       {
           for(unsigned long long i = k*PointPack+1; i<=k*PointPack+PointPack; i++)
           {
               Polygone temp_one;
               Polygone temp_two;
               if(i!=k*PointPack+PointPack)
               {
                   temp_one = Polygone (i, i+PointPack, i+1+PointPack, POINTS);
                   temp_two = Polygone(i, i+1+PointPack, i+1, POINTS);
               }
               else
               {
                   temp_one = Polygone (i, i+PointPack, k*PointPack+1+PointPack, POINTS);
                   temp_two = Polygone(i, k*PointPack+1+PointPack, k*PointPack+1, POINTS);
               }
                Polygons.push_back(temp_one);
                Polygons.push_back(temp_two);
           }
       }

       for(unsigned long long i = PointNumber-PointPack-1; i<=PointNumber-2; i++)
       {
           Polygone temp;
           if(i!=PointNumber-2)
                temp = Polygone(PointNumber-1, i, i+1, POINTS);
            else
                temp = Polygone(PointNumber-1,PointNumber-2,PointNumber-PointPack-1,  POINTS);
            Polygons.push_back(temp);
       }

        return Polygons;
    }

    std::vector<Polygone> getTriangle()
    {
        return Polygons;
    }
    std::vector<Point> getPOINTS()
    {
        return POINTS;
    }

    Sphere (double Radius, double diffAngle, Point cent,
                sf::Color FigureColor)
        {
        S = 4*M_PI*Radius*Radius;
        V = M_PI*Radius*Radius*Radius;
            this->Radius = Radius;
            this->cent = cent;
            this->diffAngle = diffAngle;
            this->FigureColor = FigureColor;
            PointPack = 360/diffAngle;
            PointNumber = 2+((PointPack/2)-1)*PointPack;
            POINTS=createPoints(cent);
            Polygons=createPolygons();

        }
        Sphere (double Radius, double diffAngle, Point cent, sf::CircleShape PointShape)
        {
            S = 4*M_PI*pow(Radius, 2);
            V = M_PI*pow(Radius, 3);
            this->Radius = Radius;
            this->cent = cent;
            this->diffAngle = diffAngle;
            PointPack = 360/diffAngle;
            PointNumber = 2+((PointPack/2)-1)*PointPack;
            POINTS=createPoints(cent);
            for(unsigned long long i = 0; i<PointNumber; i++)
            POINTS[i].setShape(PointShape);

        }
        double getS()
        {
            return S;
        }
        double getV()
        {
            return V;
        }
};
///-----------PARALLELEPIPED---------------------------------------------------------

class Parallelepiped
{
private:
    int PointNumber;
    int PointBound;
    double S; double V;

    double diffAngle;
    double FigureHeight;
    double wight;
    double flong;

    sf::Color FigureColor;

    std::vector<Polygone> Polygons;

    Point cent;
public:
    std::vector<Point> POINTS;
    std::vector<Point> createPoints()
    {
        for(double i = 0; i<360; i+=diffAngle)
        {
            double x = cent.get_x()+wight*cos((i+45)*GTR);
            double y = cent.get_y()+flong*sin((i+45)*GTR);
            double z = cent.get_z()-(FigureHeight/2);

            if(i>180)
            {
                if(FigureColor.r<240)
                    FigureColor.r+=15;
                if(FigureColor.g<240)
                    FigureColor.g+=15;
                if(FigureColor.b<240)
                    FigureColor.b+=15;
            }
            else
            {
                if(FigureColor.r>15)
                    FigureColor.r-=15;
                if(FigureColor.g>15)
                    FigureColor.g-=15;
                if(FigureColor.b>15)
                    FigureColor.b-=15;
            }
            Point temp_neg (x,y,z, FigureColor);
            POINTS.push_back(temp_neg);
        }
        for(double i = 0; i<360; i+=diffAngle)
        {
            double x = cent.get_x()+wight*cos((i+45)*GTR);
            double y = cent.get_y()+flong*sin((i+45)*GTR);
            double z = cent.get_z()+(FigureHeight/2);

            if(i>180)
            {
                if(FigureColor.r<240)
                    FigureColor.r+=15;
                if(FigureColor.g<240)
                    FigureColor.g+=15;
                if(FigureColor.b<240)
                    FigureColor.b+=15;
            }
            else
            {
                if(FigureColor.r>15)
                    FigureColor.r-=15;
                if(FigureColor.g>15)
                    FigureColor.g-=15;
                if(FigureColor.b>15)
                    FigureColor.b-=15;
            }
            Point temp_pos (x,y,z, FigureColor);
            POINTS.push_back(temp_pos);
        }
        Point Bottom(cent.get_x(), cent.get_y(), cent.get_z()-FigureHeight/2, FigureColor);
        Point Upper(cent.get_x(), cent.get_y(), cent.get_z()+FigureHeight/2, FigureColor);
        POINTS.push_back(Bottom);
        POINTS.push_back(Upper);
        POINTS.push_back(cent);

        return POINTS;
    }

    std::vector<Polygone> createPolygons() //We push index of POINTS to use it via render-engine
    {
        for(int i=0; i<PointBound; i++)
        {
            Polygone temp_one;
            Polygone temp_two;
            if(i!=3)
            {
                temp_one = Polygone(i+PointBound, i+1, i, POINTS);
                temp_two = Polygone(i+PointBound, i+1, i+PointBound+1, POINTS);
            }
            else
            {
                temp_one = Polygone(i+PointBound, 0, i+1, POINTS);
                temp_two = Polygone(i+PointBound, 0, i, POINTS);
            }
            Polygons.push_back(temp_one);
            Polygons.push_back(temp_two);
        }
        for(int i=0; i<PointBound; i++)
        {
            Polygone temp_bottom;
            if(i!=3)
                temp_bottom = Polygone(i, i+1, (PointBound*2), POINTS);
            else
                temp_bottom = Polygone(i, 0, (PointBound*2), POINTS);
            Polygons.push_back(temp_bottom);
        }
        for(int i=0; i<PointBound; i++)
        {
            Polygone temp_bottom;
            if(i!=3)
                temp_bottom = Polygone(i+PointBound, i+1+PointBound, (PointBound*2)+1, POINTS);
            else
                temp_bottom = Polygone(i+PointBound, PointBound, (PointBound*2)+1, POINTS);
            Polygons.push_back(temp_bottom);
        }

        return Polygons;
    }
    std::vector<Polygone> getTriangle()
    {
            return Polygons;
    }
    std::vector<Point> getPOINTS()
    {
        return POINTS;
    }

    Parallelepiped(double BasicLine,double wight,double flong, Point cent, sf::Color FigureColor)
    {
        this->FigureColor = FigureColor;
        this->cent = cent;
        FigureHeight = BasicLine;
        this->wight = wight;
        this->flong = flong;
        PointNumber = 8;
        PointBound = 4;
        diffAngle = 90;
        POINTS = createPoints();
        Polygons = createPolygons();
        S = FigureHeight*wight*2+FigureHeight*flong*2+flong*wight*2;
        V = FigureHeight*wight*flong;
    }
    Parallelepiped(double BasicLine,double wight,double flong, Point cent, sf::CircleShape PointShape)
    {
        this->cent = cent;
        FigureHeight = BasicLine;
        this->wight = wight;
        this->flong = flong;
        PointNumber = 8;
        PointBound = 4;
        diffAngle = 90;
        POINTS = createPoints();
        for(unsigned long long i = 0; i<POINTS.size()-3; i++)
        POINTS[i].setShape(PointShape);
        S = FigureHeight*wight*2+FigureHeight*flong*2+flong*wight*2;
        V = FigureHeight*wight*flong;
    }

    int getPointBound()
    {
        return PointBound;
    }
    int getPointNumber()
    {
        return PointNumber;
    }
    double getS()
    {
        return S;
    }
    double getV()
    {
        return V;
    }
};
