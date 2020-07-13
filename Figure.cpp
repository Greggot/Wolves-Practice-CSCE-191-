#include "Point.cpp"
#include <vector>
#include <cmath>

///-----POLYGONE--------------------------------------------------------
class Polygone
{
private:
    int one, two, three;
    Point distanceTest;
    sf::VertexArray triangle;
    float distance;
public:
    Polygone (){}
    Polygone(int one, int two, int three, std::vector<Point> P)
             {
                float x = (P[one].get_x()+P[two].get_x())/2;
                float y = (P[one].get_y()+P[two].get_y())/2;
                float z = (P[one].get_z()+P[three].get_z())/2;
                Point temp(x,y,z);
                distanceTest = temp;
                this->one = one;
                this->two = two;
                this->three = three;
                triangle = sf::VertexArray(sf::Triangles, 3);
                triangle[0].color = P[one].getColor();
                triangle[1].color = P[two].getColor();
                triangle[2].color = P[three].getColor();
             }
    void setPolygon(float &omega, float &gamma,
                    float center_x, float center_y, float scale,
                    std::vector<Point> P)
    {
        float cam_x = scale*cos(GTR*omega);
        float cam_y = scale*sin(GTR*omega);
        float cam_z = scale*sin(GTR*gamma);

        float x = cam_x - distanceTest.get_x();
        float y = cam_y - distanceTest.get_y();
        float z = cam_z - distanceTest.get_z();

        distance = pow(x,2)+pow(y,2)+pow(z,2);

        P[one].setPoint(omega, gamma, center_x, center_y, scale);
        P[two].setPoint(omega, gamma, center_x, center_y, scale);
        P[three].setPoint(omega, gamma, center_x, center_y, scale);

        triangle[0].position = sf::Vector2f(P[one].get_x_render(), P[one].get_y_render());
        triangle[1].position = sf::Vector2f(P[two].get_x_render(), P[two].get_y_render());
        triangle[2].position = sf::Vector2f(P[three].get_x_render(), P[three].get_y_render());
    }
	 Point get_distanceTest()
    {
        return distanceTest;
    }
    void Out()
    {
        std::cout<<"["<<one<<", "<<two<<", "<<three<<"]\n";
    }

    float get_distance()
    {
        return distance;
    }

    sf::VertexArray getTriangle(std::vector<Point> P)
    {
        return triangle;
    }
    float getTwo()
    {
        return two;
    }
};
///-------CUBE------------------------------------------------------------
class Cube
{
private:
    int PointNumber;
    int PointBound;

    float diffAngle;
    float FigureHeight;
    float Radius;

    sf::Color FigureColor;

    std::vector<Polygone> Polygons;

    Point cent;
public:
    std::vector<Point> POINTS;
    std::vector<Point> createPoints()
    {
        for(float i = 0; i<360; i+=diffAngle)
        {
            float x = cent.get_x()+Radius*cos((i+45)*GTR);
            float y = cent.get_y()+Radius*sin((i+45)*GTR);
            float z = cent.get_z()-(FigureHeight/2);

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
        for(float i = 0; i<360; i+=diffAngle)
        {
            float x = cent.get_x()+Radius*cos((i+45)*GTR);
            float y = cent.get_y()+Radius*sin((i+45)*GTR);
            float z = cent.get_z()+(FigureHeight/2);

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

    Cube(float BasicLine, Point cent, sf::Color FigureColor)
    {
        this->FigureColor = FigureColor;
        this->cent = cent;
        FigureHeight = BasicLine;
        Radius = FigureHeight*sqrt(2)/2;
        PointNumber = 8;
        PointBound = 4;
        diffAngle = 90;
        POINTS = createPoints();
        Polygons = createPolygons();
    }

    Cube(float BasicLine, Point cent, sf::CircleShape PointShape)
    {
        this->cent = cent;
        FigureHeight = Radius = BasicLine;
        PointNumber = 8;
        diffAngle = 90;
        POINTS=createPoints();
        Polygons = createPolygons();
        for(int i = 0; i<POINTS.capacity(); i++)
            POINTS[i].setShape(PointShape);
    }

    int getPointBound()
    {
        return PointBound;
    }
    int getPointNumber()
    {
        return PointNumber;
    }
};
///---------PRISM-CYLINDER---------------------------------------------------
class Prism_Cylinder
{
private:
    int PointNumber;
    int PointBound;

    sf::Color FigureColor;

    float diffAngle;
    float FigureHeight;
    float Radius;

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
        for(float i = 0; i<360; i+=diffAngle)
        {
            float x = cent.get_x()+Radius*cos((i+45)*GTR);
            float y = cent.get_y()+Radius*sin((i+45)*GTR);
            float z = cent.get_z()-(FigureHeight/2);

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
        for(float i = 0; i<360; i+=diffAngle)
        {
            float x = cent.get_x()+Radius*cos((i+45)*GTR);
            float y = cent.get_y()+Radius*sin((i+45)*GTR);
            float z = cent.get_z()+(FigureHeight/2);

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

    Prism_Cylinder(float FigureHeight, float Radius, int PointNumber,
                    Point cent, sf::Color FigureColor)
    {
        this->FigureColor = FigureColor;
        this->FigureHeight = FigureHeight;
        this->Radius = Radius;
        this->PointNumber = PointNumber;
        this->cent = cent;
        PointBound = PointNumber/2;
        diffAngle = 360/PointBound;

        POINTS = createPoints();
        Polygons = createPolygons();
    }

    Prism_Cylinder(float BasicLine, float R, int number, Point cent, sf::CircleShape PointShape)
    {
        this->cent = cent;
        FigureHeight = BasicLine;
        Radius = R;
        PointNumber = number;
        diffAngle = 720/number;
        POINTS=createPoints();
        for(int i = 0; i<POINTS.capacity(); i++)
            POINTS[i].setShape(PointShape);
    }
};
///-----------PYRAMID-CONE-----------------------------------------------------------
class Pyramid_Cone
{
private:
    int PointNumber;

    float diffAngle;
    float FigureHeight;
    float Radius;

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
        int ind = 0;
        Point S (cent.get_x(), cent.get_y(), cent.get_z()+FigureHeight/2, FigureColor);
        POINTS.push_back(S);
        Point antiS (cent.get_x(), cent.get_y(), cent.get_z()-FigureHeight/2, FigureColor);
        POINTS.push_back(antiS);


        for(float i = 0; i<360; i+=diffAngle)
        {
            float x = cent.get_x()+Radius*cos((i+45)*GTR);
            float y = cent.get_y()+Radius*sin((i+45)*GTR);
            float z = cent.get_z()-(FigureHeight/2);
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

    Pyramid_Cone(float FigureHeight, float Radius, int PointNumber, Point cent)
    {
        this->FigureHeight = FigureHeight;
        this->Radius = Radius;
        this->PointNumber = PointNumber;
        this->cent = cent;
        diffAngle = 360/(PointNumber-1);
        POINTS=createPoints();
    }
    Pyramid_Cone(float FigureHeight, float Radius, int PointNumber,
                  Point cent, sf::Color FigureColor)
    {
        this->FigureHeight = FigureHeight;
        this->Radius = Radius;
        this->PointNumber = PointNumber;
        this->FigureColor = FigureColor;
        this->cent = cent;
        diffAngle = 360/(PointNumber-1);
        POINTS = createPoints();
        Polygons = createPolygons();
    }

    Pyramid_Cone(float BasicLine, float R, int number, Point cent, sf::CircleShape PointShape)
    {
        this->cent = cent;
        FigureHeight = BasicLine;
        Radius = R;
        PointNumber = number;
        diffAngle = 360/(number-1);
        POINTS=createPoints();
        for(int i = 0; i<POINTS.capacity(); i++)
            POINTS[i].setShape(PointShape);
    }
};
///------SPHERE------------------------------------------------------
class Sphere
{
private:
    int PointNumber;
    int PointPack;
    float Radius;
    float diffAngle;

    std::vector<Polygone> Polygons;
    std::vector<Point> POINTS;

    sf::Color FigureColor;

    Point cent;
public:
    std::vector<Point> createPoints(Point cent)
    {
        int col=0;
        Point Upper (cent.get_x(), cent.get_y(), cent.get_z()+Radius, FigureColor);
        Point Bottom (cent.get_x(), cent.get_y(), cent.get_z()-Radius, FigureColor);
        POINTS.push_back(Upper);
        std::cout<<"\n\n\n\n\n\n\n";
        Point temp;
        for(int j =90-diffAngle; j>=-90+diffAngle; j-=diffAngle)
        {
            float z = cent.get_z()+Radius*sin(j*GTR);
            float Radius_xy = Radius*cos(j*GTR);
            for(float i = 0; i<360;i+=diffAngle)
            {

                float x = cent.get_x()+Radius_xy*cos(i*GTR);
                float y = cent.get_y()+Radius_xy*sin(i*GTR);

                temp = Point(x,y,z);
                POINTS.push_back(temp);
            }
        }
        for(int i = 0; i<POINTS.size(); i++)
        {
               if(i%PointPack==0)
                {
                if(FigureColor.r<245)
                    FigureColor.r+=20;
                if(FigureColor.g<245)
                    FigureColor.g+=20;
                if(FigureColor.b<245)
                    FigureColor.b+=20;

                if(FigureColor.r>245)
                    FigureColor.r-=20;
                if(FigureColor.g>245)
                    FigureColor.g-=20;
                if(FigureColor.b>245)
                    FigureColor.b-=20;
                }
            POINTS[i].setColor(FigureColor);
            std::cout<<i;
            POINTS[i].colorOut();
        }


        POINTS.push_back(Bottom);
        POINTS.push_back(cent);
        std::cout<<"\n\n\n\n\n\n\n";
        for(int i = 0; i<POINTS.size(); i++)
        {
            std::cout<<i;
            POINTS[i].Out();
        }


        return POINTS;
    }

    std::vector<Polygone> createPolygons()    //We push index of POINTS to use it via render-engine
    {
       std::cout<<PointPack<<std::endl;
       for(int i = 1; i<=PointPack; i++)
       {
           Polygone temp;
           if(i!=PointPack)
                temp = Polygone(0, i, i+1, POINTS);
            else
                temp = Polygone(0, i, 1, POINTS);
            Polygons.push_back(temp);
       }

       for(int k = 0;k<((PointNumber-2)/(PointPack))-1; k++)
       {
           std::cout<<"\n\n"<<k<<"\n\n";
           for(int i = k*PointPack+1; i<=k*PointPack+PointPack; i++)
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
               temp_one.Out();
               temp_two.Out();
                Polygons.push_back(temp_one);
                Polygons.push_back(temp_two);
           }
       }

       for(int i = PointNumber-PointPack-1; i<=PointNumber-2; i++)
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

    Sphere (float Radius, float diffAngle, Point cent, sf::CircleShape PointShape,
            sf::Color FigureColor)
    {
        this->Radius = Radius;
        this->cent = cent;
        this->diffAngle = diffAngle;
        this->FigureColor = FigureColor;
        PointPack = 360/diffAngle;
        PointNumber = 2+((PointPack/2)-1)*PointPack;
        POINTS=createPoints(cent);
        for(int i = 0; i<POINTS.capacity(); i++)
        POINTS[i].setShape(PointShape);
        Polygons=createPolygons();
    }
};

/* for(int i=1;i<PointPack+1;i++)
        {
           // std::cout<<PointPack<<"||"<<PointNumber<<std::endl;
            Polygone temp;
            if(i==PointPack)
            {
                temp = Polygone(0,1,PointPack, POINTS);
                Polygons.push_back(temp);
            }
            else
            {
            temp = Polygone(0,i,i+1, POINTS);
            Polygons.push_back(temp);
            }

        }
        for(int j=PointPack+1;j<PointNumber-PointPack-1;j+=PointPack)
            {
                for(int i=j;i<j+PointPack;i++)
                {
                    Polygone temp_one,temp_two;
                    if(i!=j+PointPack-1)
                    {
                        temp_one = Polygone(i,i+1,i+PointPack, POINTS);
                        temp_two = Polygone(i+1,i+PointPack,i+PointPack+1, POINTS);
                    }
                    else
                    {
                        temp_one = Polygone(i,i-PointPack+1,i+PointPack, POINTS);
                        temp_two = Polygone(i-PointPack+1,i+PointPack-PointPack+1,i+PointPack, POINTS);
                    }
                    Polygons.push_back(temp_one);
                    Polygons.push_back(temp_two);
                   // temp_one.Out();
                   // temp_two.Out();
                }
            }
        for(int i=PointNumber-1;i>PointNumber-PointPack-1;i--)
        {
            Polygone temp;
            if(i==PointNumber-PointPack)
            {
                temp = Polygone(PointNumber,PointNumber-PointPack,i+PointPack-1, POINTS);
                Polygons.push_back(temp);
            }
            else
            {
            temp = Polygone(PointNumber,i,i-1, POINTS);
            Polygons.push_back(temp);
            }

        }*/
