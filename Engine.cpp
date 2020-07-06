#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "point.h"

float const GTR = 0.0174533;    //Grad to Rad
float const RTG = 1/GTR;
float speed =4;


float Angle_to_X(float &omega, float x, float y)
{

	float cum_x = cos(GTR*omega);
	float cum_y = sin(GTR*omega);

	float ch = cum_x*x+cum_y*y;

	float zn = sqrt(pow(cum_x, 2)+pow(cum_y, 2))*
				sqrt(pow(x, 2)+pow(y, 2));
	float output = sqrt(pow(x, 2)+pow(y, 2))*sin(acos(ch/zn));

	if(omega>(360+(atan(y/x)/GTR))||(omega<-360+(atan(y/x)/GTR)))
        omega=(atan(y/x)/GTR);
    if((omega>180+(atan(y/x)/GTR)&&omega<360+(atan(y/x)/GTR))
       ||(omega<(atan(y/x)/GTR)&&omega>-180+(atan(y/x)/GTR)))
        output*=-1;
	return output;
}

float sign = 1;

float Angle_to_Y(float &gamma, float &omega, float x, float y, float z, float Axy_90)
{

    float cum_xy = cos(GTR*gamma);
	float cum_z = sin(GTR*gamma);

    float ch = cum_xy*z+cum_z*Axy_90;

	float zn = sqrt(pow(cum_xy, 2)+pow(cum_z, 2))*
				sqrt(pow(z, 2)+pow(Axy_90, 2));

    float output = sqrt(pow(z,2)+pow(Axy_90,2))*sin(acos(ch/zn))*sign;

    if(gamma>(360+(atan(Axy_90/z)*RTG))||(gamma<-360+(atan(Axy_90/z)*RTG)))
        gamma=(atan(Axy_90/z)*RTG);
    if((gamma>180+(atan(Axy_90/z)*RTG)&&gamma<360+(atan(Axy_90/z)*RTG))
       ||(gamma<(atan(Axy_90/z)*RTG)&&gamma>-180+(atan(Axy_90/z)*RTG)))
        output*=-1;

    return output;
}

void Center_Update(int& center_x, int& center_y, sf::Vector2u Eng_size)
{
    center_y = Eng_size.y/2;
    center_x = Eng_size.x/2;
}

int main()
{
    float x_render; float y_render;
    float Axy_90;
    float scale = 10;
    RealPoint POINT {10, -10, 10};
    int center_x, center_y; //Rendering Center
    float omega, gamma;     //Keyboard Input in grad

    omega = 0; float& omega_ref = omega;
    gamma = 1;  float& gamma_ref = gamma;
    center_x = 300; int &center_x_ref = center_x;
    center_y = 200; int &center_y_ref = center_y;

    sf::RenderWindow Engine(sf::VideoMode(600, 400), "Window");
    sf::Vector2u Eng_size = Engine.getSize();

    sf::CircleShape center(5.f);
    center.setFillColor(sf::Color::White);
    center.setOutlineThickness(2.f);
    center.setOutlineColor(sf::Color::Black);
    center.setPosition(center_x, center_y);

    sf::CircleShape point(5.f);
    point.setFillColor(sf::Color(245,230,255,255));
    point.setOutlineThickness(2.f);
    point.setOutlineColor(sf::Color::Black);

    Axy_90 = Angle_to_X(omega, POINT.x*scale, POINT.y*scale);
    y_render = Eng_size.y/2 + Angle_to_Y(gamma_ref, omega_ref,POINT.x*scale,
                                        POINT.y*scale, POINT.z*scale, Axy_90);
    x_render = Eng_size.x/2 - Angle_to_X(omega_ref, POINT.x*scale, POINT.y*scale);
    point.setPosition(x_render, y_render);

    Engine.setFramerateLimit(60);

    while (Engine.isOpen())
    {
        sf::Event event;

        while (Engine.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    Engine.close();
                    break;
                case sf::Event::Resized:
                    {
                    Center_Update(center_x_ref, center_y_ref, Engine.getSize());
                    center.setPosition(center_x, center_y);
                    break;
                    }
                case sf::Event::KeyPressed:
                    switch(event.key.code)
                    {
                        case sf::Keyboard::Q:
                            scale++;
                            Axy_90 = Angle_to_X(omega, POINT.x*scale, POINT.y*scale);
                            y_render = Eng_size.y/2 + Angle_to_Y(gamma_ref, omega_ref,POINT.x*scale,
                                        POINT.y*scale, POINT.z*scale, Axy_90);
                            x_render = Eng_size.x/2 - Angle_to_X(omega_ref, POINT.x*scale, POINT.y*scale);
                            point.setPosition(x_render, y_render);
                            break;
                        case sf::Keyboard::W:
                            if(scale>2)
                            {
                                scale--;
                                Axy_90 = Angle_to_X(omega, POINT.x*scale, POINT.y*scale);
                                y_render = Eng_size.y/2 + Angle_to_Y(gamma_ref, omega_ref,POINT.x*scale,
                                        POINT.y*scale, POINT.z*scale, Axy_90);
                                x_render = Eng_size.x/2 - Angle_to_X(omega_ref, POINT.x*scale, POINT.y*scale);
                                point.setPosition(x_render, y_render);
                            }
                            break;
                        case sf::Keyboard::Up:
                            gamma_ref-=speed;
                            Axy_90 = Angle_to_X(omega, POINT.x, POINT.y);
                            y_render = Eng_size.y/2 + Angle_to_Y(gamma_ref, omega_ref,
                                                                POINT.x*scale,
                                                                POINT.y*scale,
                                                                POINT.z*scale,
                                                                 Axy_90);

                            point.setPosition(x_render, y_render);
                            break;
                        case sf::Keyboard::Down:
                            gamma_ref+=speed;
                            Axy_90 = Angle_to_X(omega, POINT.x, POINT.y);
                            y_render = Eng_size.y/2 + Angle_to_Y(gamma_ref, omega_ref,
                                                                 POINT.x*scale,
                                                                 POINT.y*scale,
                                                                 POINT.z*scale,
                                                                  Axy_90);

                            point.setPosition(x_render, y_render);
                            break;
                        case sf::Keyboard::Right:
                            omega_ref+=speed;
                            x_render = Eng_size.x/2 - Angle_to_X(omega_ref, POINT.x*scale,
                                                                  POINT.y*scale);

                            point.setPosition(x_render, y_render);
                            break;
                        case sf::Keyboard::Left:
                            omega_ref-=speed;
                            x_render = Eng_size.x/2 - Angle_to_X(omega_ref, POINT.x*scale,
                                                                 POINT.y*scale);

                            point.setPosition(x_render, y_render);
                            break;
                        default:
                            break;
                    }
            }
        }
         Engine.clear(sf::Color::White);

        sf::Vertex line[] ={
            sf::Vertex(sf::Vector2f(center_x, center_y)),
            sf::Vertex(sf::Vector2f(x_render, y_render))
        };
        Engine.draw(line, 2, sf::Lines)

        Engine.draw(center);
        Engine.draw(point);
        Engine.display();
        }
    return 0;
}
