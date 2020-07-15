#include <iostream>
#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>


    double const GTR = 0.0174533;


/*double progress(double x, double y)
{
    double out;
    if
}*/


class Point
{
private:
    double x, y, z;
    double x_render, y_render;
    sf::CircleShape pointShape;
    sf::Color PointColor;
public:
    Point(){}
     Point(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    double Angle_to_X(double &omega)
    {
        double sign = 1;
        double cam_x = cos(GTR*omega);
        double cam_y = sin(GTR*omega);

        double ch = cam_x*x+cam_y*y;
        double zn = sqrt(pow(cam_x, 2)+pow(cam_y, 2))*
                    sqrt(pow(x, 2)+pow(y, 2));
        if(x<0)
            sign*=-1;

        double output;
        if(ch==0.l)
        output = sqrt(pow(x, 2)+pow(y, 2))*sign;
        else
        output = sqrt(pow(x, 2)+pow(y, 2))*sin(acos(ch/zn))*sign;

        if (omega>180)
            omega-=360;
        if (omega<-180)
            omega-=-360;
        //std::cout<<x<<" "<<y<<"  "<<z<<" : "<<atan(y/x)/GTR<<std::endl;
        if((omega>180+(atan(y/x)/GTR)&&omega<360+(atan(y/x)/GTR))
        ||(omega<(atan(y/x)/GTR)&&omega>-180+(atan(y/x)/GTR)))
            output*=-1;

        return output;
    }

    double Angle_to_Y(double &gamma, double Axy_90)
    {
        double sign = 1;
        double cam_xy = cos(GTR*gamma);
        double cam_z = sin(GTR*gamma);

        double ch = cam_xy*z+cam_z*Axy_90;
        double zn = sqrt(pow(cam_xy, 2)+pow(cam_z, 2))*
				sqrt(pow(z, 2)+pow(Axy_90, 2));

        if(z<0)
            sign*=-1;

        double  output;
        if(ch==0)
        output = sqrt(pow(z,2)+pow(Axy_90,2))*sign;
        else
        output = sqrt(pow(z,2)+pow(Axy_90,2))*sin(acos(ch/zn))*sign;

        if (gamma>180)
            gamma-=360;
        if (gamma<-180)
            gamma-=-360;

        if((gamma>180+(atan(Axy_90/z)/GTR)&&gamma<360+(atan(Axy_90/z)/GTR))
        ||(gamma<(atan(Axy_90/z)/GTR)&&gamma>-180+(atan(Axy_90/z)/GTR)))
            output*=-1;
        return output;
    }

    void setPoint (double &omega, double &gamma,
                   double center_x, double center_y, double scale) //Temp function
    {
        double omega_90 = omega-90;
        x_render = center_x + Angle_to_X(omega)*scale;
        y_render = center_y + Angle_to_Y(gamma, Angle_to_X(omega_90))*scale;
        pointShape.setPosition(x_render, y_render);
    }


    Point(double x, double y, double z, sf::CircleShape pointShape)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->pointShape = pointShape;
     }
     Point(double x, double y, double z, sf::Color PointColor)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->PointColor = PointColor;
    }


    double get_x()
    {
        return x;
    }
    double get_y()
    {
        return y;
    }
    double get_z()
    {
        return z;
    }
    void set_x(double x)
    {
        this->x=x;
    }
    void set_y(double y)
    {
        this->y=y;
    }
    void set_z(double z)
    {
        this->z=z;
    }

    double get_x_render()
    {
        return x_render;
    }
    double get_y_render()
    {
        return y_render;
    }

    sf::Color getColor()
    {
        return PointColor;
    }

    void setColor(sf::Color PointColor)
    {
        this->PointColor = PointColor;
    }

    void RenderOut()
    {
        std::cout<<x_render<<", "<<y_render<<"\n";
    }

    sf::CircleShape getShape()
    {
        return pointShape;
    }
    void setShape(sf::CircleShape pointShape)
    {
        this->pointShape = pointShape;
    }

    void Out()
    {
        std::cout<<"("<<x<<", "<<y<<", "<<z<<")"<<std::endl;
    }
};

struct Triangle
{
    unsigned int index[3];
    Point TestDistancePoint;
    unsigned int distance;
};

