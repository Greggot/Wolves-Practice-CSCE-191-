#include "Point.cpp"
#include <vector>

float scale = 10;
float speed = 4;

void Center_Update(int& center_x, int& center_y,
                    sf::Vector2u Eng_size, sf::CircleShape &CenterPoint)
{
    center_y = Eng_size.y/2;
    center_x = Eng_size.x/2;
    CenterPoint.setPosition(center_x, center_y);
}

int main() //StartEngine()
{
    int center_x, center_y; //Rendering Center
    float omega, gamma;     //Keyboard Input in grad

    omega = 0; float& omega_ref = omega;
    gamma = 0;  float& gamma_ref = gamma;
    center_x = 400; int &center_x_ref = center_x;
    center_y = 300; int &center_y_ref = center_y;

    sf::RenderWindow Engine(sf::VideoMode(800, 600), "Window");

    sf::CircleShape center(3.f);
    center.setFillColor(sf::Color::White);
    center.setOutlineThickness(1.f);
    center.setOutlineColor(sf::Color::Black);
    center.setPosition(center_x, center_y);
    sf::CircleShape &center_ref = center;

    sf::CircleShape point_shape(5.f);
    point_shape.setFillColor(sf::Color(245,230,255,255));
    point_shape.setOutlineThickness(2.f);
    point_shape.setOutlineColor(sf::Color::Black);

    sf::CircleShape X(3.f);
    X.setFillColor(sf::Color::Red);
    sf::CircleShape Y(3.f);
    Y.setFillColor(sf::Color::Green);
    sf::CircleShape Z(3.f);
    Z.setFillColor(sf::Color::Blue);

    Point X_axys(100, 0, 0, X);
    Point Y_axys(0, 100, 0, Y);
    Point Z_axys(0, 0, 100, Z);

    X_axys.setPoint(omega_ref, gamma_ref, center_x, center_y);
    Y_axys.setPoint(omega_ref, gamma_ref, center_x, center_y);
    Z_axys.setPoint(omega_ref, gamma_ref, center_x, center_y);

    Point Center(0,0,0, center);

    Point thing(100, 20, 0, point_shape);
    Point thing2(-10, 20, 50, point_shape);
    Point thing3(100, -20, 0, point_shape);

    std::vector<Point> PointVector;
    PointVector.push_back(Center);
    PointVector.push_back(thing);
    PointVector.push_back(thing2);
    PointVector.push_back(thing3);

    for(int i = 0; i<PointVector.capacity(); i++)
        PointVector[i].setPoint(omega_ref, gamma_ref, center_x, center_y);

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
                    Center_Update(center_x_ref, center_y_ref,
                                   Engine.getSize(), center_ref);
                    break;
                    }
                case sf::Event::KeyPressed:
                    switch(event.key.code)
                    {
                        case sf::Keyboard::W:
                            speed++;
                            break;
                        case sf::Keyboard::S:
                            if(speed>2)
                                speed--;
                            break;
                        case sf::Keyboard::Up:
                            gamma_ref-=speed;
                            std::cout<<gamma<<", "<<omega<<"\n";
                            X_axys.setPoint(omega_ref, gamma_ref, center_x, center_y);
                            Y_axys.setPoint(omega_ref, gamma_ref, center_x, center_y);
                            Z_axys.setPoint(omega_ref, gamma_ref, center_x, center_y);

                            for(int i = 0; i<PointVector.size(); i++)
                                PointVector[i].setPoint(omega_ref, gamma_ref, center_x, center_y);

                            break;
                        case sf::Keyboard::Down:
                            gamma_ref+=speed;
                            std::cout<<gamma<<", "<<omega<<"\n";
                            X_axys.setPoint(omega_ref, gamma_ref, center_x, center_y);
                            Y_axys.setPoint(omega_ref, gamma_ref, center_x, center_y);
                            Z_axys.setPoint(omega_ref, gamma_ref, center_x, center_y);
                            for(int i = 0; i<PointVector.size(); i++)
                                PointVector[i].setPoint(omega_ref, gamma_ref, center_x, center_y);

                            break;
                        case sf::Keyboard::Right:
                            omega_ref+=speed;
                            std::cout<<gamma<<", "<<omega<<"\n";
                            X_axys.setPoint(omega_ref, gamma_ref, center_x, center_y);
                            Y_axys.setPoint(omega_ref, gamma_ref, center_x, center_y);
                            Z_axys.setPoint(omega_ref, gamma_ref, center_x, center_y);
                            for(int i = 0; i<PointVector.size(); i++)
                                PointVector[i].setPoint(omega_ref, gamma_ref, center_x, center_y);

                            break;
                        case sf::Keyboard::Left:
                            omega_ref-=speed;
                            std::cout<<gamma<<", "<<omega<<"\n";
                            X_axys.setPoint(omega_ref, gamma_ref, center_x, center_y);
                            Y_axys.setPoint(omega_ref, gamma_ref, center_x, center_y);
                            Z_axys.setPoint(omega_ref, gamma_ref, center_x, center_y);
                            for(int i = 0; i<PointVector.size(); i++)
                                PointVector[i].setPoint(omega_ref, gamma_ref, center_x, center_y);

                            break;
                        default:
                            break;
                    }
            }
        }
        Engine.clear(sf::Color::White);

        for(int i = 0; i<PointVector.size(); i++)
            Engine.draw(PointVector[i].getShape());

        Engine.draw(X_axys.getShape());
        Engine.draw(Y_axys.getShape());
        Engine.draw(Z_axys.getShape());

        Engine.display();
        }
    return 0;
}
