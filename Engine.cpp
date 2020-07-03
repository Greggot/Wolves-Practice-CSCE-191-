#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "point.h"

float Angle_Between_Vect_XY(RealPoint one, RealPoint two)
{
    ///Сюда код для нахождения угла между проекциями точки и камеры на Oxy
}

float Angle_Between_Vect_Z(RealPoint one, RealPoint two)
{
    ///Сюда то же самое, только между проекциями на плоскость, образованную Z и н.в.
    ///проекции радиус вектора на Оху
}

float Camera_Angle_To_Render_X(float omega, float c_x,
                                RealPoint POINT, RealPoint CAMERA)
{
    float output = pow(POINT.x, 2)+pow(POINT.y, 2);
    output = sqrt(output);
    output = output*sin(Angle_Between_Vect_XY(POINT, CAMERA));

    //std::cout<<(c_x+output)<<std::endl;
    return c_x+output;
}
float Camera_Angle_To_Render_Y(float gamma, float c_y,
                               RealPoint POINT, RealPoint CAMERA)
{
    float output = pow(POINT.x, 2)+pow(POINT.y, 2)+pow(POINT.x, 2);
    output = sqrt(output);
    output = output*sin(Angle_Between_Vect_Z(POINT, CAMERA));
    //std::cout<<(c_x+output)<<std::endl;
    return c_y+output;
}

void Center_Update(int& center_x, int& center_y, sf::Vector2u Eng_size)
{
    center_y = Eng_size.y/2;
    center_x = Eng_size.x/2;
}

int main()//int Engine_START(point[] PointArray) -- в будущем тупо функция,
{           //Сейчас main() для тестов
    float const GTR = 0.0174533;    //Grad to Rad

    int center_x, center_y; //Rendering Center
    float omega, gamma, r;     //Keyboard Input in grad
    float x_render, y_render;

    RealPoint POINT {1, 0, 0};
    RealPoint Camera {0,0,0};

    omega = 0; float& omega_ref = omega;
    gamma = 0;  float& gamma_ref = gamma;
    r = 10;//? вообще хз какой брать
    center_x = 300; int &center_x_ref = center_x;
    center_y = 200; int &center_y_ref = center_y;

    x_render = center_x; y_render = center_y;

    sf::CircleShape center(5.f);
    center.setFillColor(sf::Color::White);
    center.setOutlineThickness(2.f);
    center.setOutlineColor(sf::Color::Black);
    center.setPosition(center_x, center_y);

    sf::CircleShape point(5.f);
    point.setFillColor(sf::Color(245,230,255,255)); //Розовенький uwu
    point.setOutlineThickness(2.f);
    point.setOutlineColor(sf::Color::Black);

    sf::RenderWindow Engine(sf::VideoMode(600, 400), "Window");
    Engine.setFramerateLimit(60);

    while (Engine.isOpen())
    {
        sf::Event event;

        while (Engine.pollEvent(event))
        {
            switch (event.type)
            {
                //Здесь прописывать события в окне, в том числе реакцию на мышь и
                //клавиатуру
                case sf::Event::Closed:
                    Engine.close();
                    break;
                case sf::Event::Resized:
                    {
                    Center_Update(center_x_ref, center_y_ref, Engine.getSize());
                    break;
                    }
                case sf::Event::KeyPressed:
                    switch(event.key.code)
                    {
                        case sf::Keyboard::Up:
                            gamma_ref--;
                            //point.setPosition(omega, gamma); -
                            //Скопировать во все остальные кнопки, чтобы тупо покатать
                            //точку по экрану
                            Camera.z = r*cos(gamma*GTR);

                            y_render = Camera_Angle_To_Render_Y(gamma,
                                                                center_y,
                                                                POINT,
                                                                Camera);
                            point.setPosition(x_render, y_render);
                            break;
                        case sf::Keyboard::Down:
                            gamma_ref++;

                            Camera.z = r*cos(gamma*GTR);

                            y_render = Camera_Angle_To_Render_Y(gamma,
                                                                center_y,
                                                                POINT,
                                                                Camera);
                            point.setPosition(x_render, y_render);
                            break;
                        case sf::Keyboard::Right:
                            omega_ref++;

                            Camera.x = r*sin(omega*GTR);
                            Camera.y = r*cos(omega*GTR);

                            x_render = Camera_Angle_To_Render_X(omega,
                                                                center_x,
                                                                POINT,
                                                                Camera);
                            point.setPosition(x_render, y_render);
                            break;
                        case sf::Keyboard::Left:
                            omega_ref--;

                            Camera.x = r*sin(omega*GTR);
                            Camera.y = r*cos(omega*GTR);

                             x_render = Camera_Angle_To_Render_X(omega,
                                                                center_x,
                                                                POINT,
                                                                Camera);
                            point.setPosition(x_render, y_render);
                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }
        }
         Engine.clear(sf::Color::White);
        //Здесь всё отрисовывать
         Engine.draw(point);

         Engine.draw(center); //Цент всегда виден, а потому рендерится последним
         Engine.display();
    }
    return 0;
}
