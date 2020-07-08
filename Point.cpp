#include <cmath>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

    float const GTR = 0.0174533;
    float const RTG = 1/GTR;

/*float progress(float x, float y)
{
    float out;
    if
}*/


class Point
{
private:
    float x, y, z;
    float x_render, y_render;
    sf::CircleShape pointShape;
public:

    float Angle_to_X(float &omega)
    {
        float cam_x = cos(GTR*omega);
        float cam_y = sin(GTR*omega);

        float ch = cam_x*x+cam_y*y;
        float zn = sqrt(pow(cam_x, 2)+pow(cam_y, 2))*
                    sqrt(pow(x, 2)+pow(y, 2));

        float output;
        if(ch==0)
        output = sqrt(pow(x, 2)+pow(y, 2));
        else
        output = sqrt(pow(x, 2)+pow(y, 2))*sin(acos(ch/zn));

        if((omega>(360))||(omega<-360))
            omega=0;
        if (omega<-180)
            omega =180;
        std::cout<<x<<" "<<y<<"  "<<z<<" : "<<atan(y/x)/GTR<<std::endl;
        if((omega>180+(atan(y/x)/GTR)&&omega<360+(atan(y/x)/GTR))
        ||(omega<(atan(y/x)/GTR)&&omega>-180+(atan(y/x)/GTR)))
            output*=-1;

        return output;
    }

    float Angle_to_Y(float &gamma, float Axy_90)
    {
        float cam_xy = cos(GTR*gamma);
        float cam_z = sin(GTR*gamma);

        float ch = cam_xy*z+cam_z*Axy_90;
        float zn = sqrt(pow(cam_xy, 2)+pow(cam_z, 2))*
				sqrt(pow(z, 2)+pow(Axy_90, 2));

		float  output;
        if(ch==0)
        output = sqrt(pow(z,2)+pow(Axy_90,2));
        else
        output = sqrt(pow(z,2)+pow(Axy_90,2))*sin(acos(ch/zn));

        if((gamma>(360))||(gamma<-360))
            gamma=0;
        if (gamma<-180)
            gamma =180;
        if((gamma>180+(atan(Axy_90/z)/GTR)&&gamma<360+(atan(Axy_90/z)/GTR))
        ||(gamma<(atan(Axy_90/z)/GTR)&&gamma>-180+(atan(Axy_90/z)/GTR)))
            output*=-1;

        return output;
    }

    void setPoint (float &omega, float &gamma,
                   float center_x, float center_y) //Temp function
    {
        float omega_90 = omega-90;
        x_render = center_x + Angle_to_X(omega);
        y_render = center_y + Angle_to_Y(gamma, Angle_to_X(omega_90));
        pointShape.setPosition(x_render, y_render);
    }

    Point(float x, float y, float z, sf::CircleShape pointShape)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->pointShape = pointShape;
    }
    operator= (const Point &thing)
    {
        x = thing.x;
        y = thing.y;
        z = thing.z;
        pointShape = thing.pointShape;
    }

    float get_x()
    {
        return x;
    }
    float get_y()
    {
        return y;
    }
    float get_z()
    {
        return z;
    }
    void set_x(float x)
    {
        this->x=x;
    }
    void set_y(float y)
    {
        this->y=y;
    }
    void set_z(float z)
    {
        this->z=z;
    }

    float get_x_render()
    {
        return x_render;
    }
    float get_y_render()
    {
        return y_render;
    }

    void RenderOut()
    {
        std::cout<<x_render<<", "<<y_render<<"\n";
    }

    sf::CircleShape getShape()
    {
        return pointShape;
    }
};

struct Triangle
{
    Point* one;
    Point* two;
    Point* three;
    unsigned int order;
};

/*class cube
{
	private:
	std::vector<Point> CubePoints;
	//tringle texture[12];
	float side;
	float V;
	float S;
	public:
	cube(float side, sf::CircleShape)
	{
		float first_point;
		first_point=side/2;
		Point time(0,0,0);
		for(int i=0;i<2;i++)
		{
			for(int j=0;j<2;j++)
			{
				for(int n=0;n<2;n++)
				{
					float q=first_point*(pow(-1,i+1));
					float w=first_point*(pow(-1,j+1));
					float e=first_point*(pow(-1,n+1));
					time=Point(q,w,e);
					CubePoints.push_back(time);
				};
			};
		};
		V=side*side*side;
		S=side*side*6;
		задание треугольников
		tringle[0]={verhini[1],verhini[2],verhini[3]};
		tringle[1]={verhini[2],verhini[3],verhini[4]};
		tringle[2]={verhini[5],verhini[6],verhini[7]};
		tringle[3]={verhini[6],verhini[7],verhini[8]};
		tringle[4]={verhini[2],verhini[5],verhini[6]};
		tringle[5]={verhini[1],verhini[2],verhini[5]};
		tringle[6]={verhini[3],verhini[4],verhini[7]};
		tringle[7]={verhini[4],verhini[7],verhini[8]};
		tringle[8]={verhini[1],verhini[7],verhini[5]};
		tringle[9]={verhini[2],verhini[8],verhini[4]};
		tringle[10]={verhini[1],verhini[7],verhini[3]};
		tringle[11]={verhini[2],verhini[8],verhini[6]};

	}
	void dislocation_x(float dislocation)
	{
		for(int i=0;i<8;i++)
		{
			CubePoints[i].x+=dislocation;
		};
	}
	void dislocation_y(float dislocation)
	{
		for(int i=0;i<8;i++)
		{
			CubePoints[i].y+=dislocation;
		};
	}
	void dislocation_z(float dislocation)
	{
		for(int i=0;i<8;i++)
		{
			CubePoints[i].z+=dislocation;
		};
	}
	float get_side()
	{
		return side;
	};
	float get_V()
	{
		return V;
	};
	float get_S()
	{
		return S;
	};
	Point get_verhini(int n)
	{
		return CubePoints[n];
	};
	void show_verhini()
	{
		for(int i=0;i<8;i++)
		{
			cout<<get_verhini(i).x<<endl<<get_verhini(i).y<<endl<<get_verhini(i).z<<endl<<endl;
		};
		return;
	};
};*/
