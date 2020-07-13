#include "Figure.cpp"
#include <vector>

float scale = 1;
int speed = 4;
int activeFigure = 0;

float getDistance(Point one, float omega, float gamma)
{
    float cam_x = 500*cos(omega*GTR);
    float cam_y = 500*sin(omega*GTR);
    float cam_z = 500*sin(gamma*GTR);

    float x = cam_x - one.get_x();
    float y = cam_y - one.get_y();
    float z = cam_z - one.get_z();

    return sqrt(pow(x, 2)+pow(y, 2)+pow(z, 2));
}

std::vector<int> FigureSort(std::vector<std::vector<Point>> POINTS,
                                int figuresNumber, float omega, float gamma)
{
    std::vector<float> Distance;
    std::vector<int> Out;
    for(int i = 0; i<figuresNumber; i++)
        Out.push_back(i);

    for(int i = 0; i<figuresNumber; i++)
        Distance.push_back(getDistance(POINTS[i][POINTS[i].capacity()-1], omega, gamma));
    int temp;
    for(int i = 0; i<figuresNumber; i++)
    {
        for(int j = 0; j<figuresNumber; j++)
        {
            if(Distance[i]>Distance[j])
                   {
                       float temp = Distance[i];
                       Distance[i] = Distance[j];
                       Distance[j] = temp;

                       int Itemp = Out[i];
                       Out[i] = Out[j];
                       Out[j] = Itemp;
                   }
        }
    }
    if(gamma>-180&&gamma<0)
        reverse(Out.begin(), Out.end());
    return Out;
}

std::vector<int> PoligoneSort(std::vector<Polygone> POLYGONES,
                                float omega, float gamma)
{
    int size_pol=POLYGONES.capacity();
    std::vector<float> Distance;
    std::vector<int> Out;
    for(int i = 0; i<size_pol; i++)
        Out.push_back(i);

    for(int i = 0; i<size_pol; i++)
        Distance.push_back(getDistance(POLYGONES[i].get_distanceTest(), omega, gamma));
    int temp;

    for(int i = 0; i<size_pol; i++)
    {
        for(int j = 0; j<size_pol; j++)
        {
            if(Distance[i]>Distance[j])
                   {
                       float temp = Distance[i];
                       Distance[i] = Distance[j];
                       Distance[j] = temp;

                       int Itemp = Out[i];
                       Out[i] = Out[j];
                       Out[j] = Itemp;

                   }
        }
    }
   // for(int i = 0; i<size_pol; i++)
    //      std::cout<<Out[i]<<std::endl;
    if(gamma<0)
        reverse(Out.begin(), Out.end());
    return Out;
}

int main()  //StartPointEngine(int win_width, int win_height,
            //                 std::vector<std::vector<Point>> POINTS,
            //                 std::vector<std::vector<Polygone>> POLYGONS,
            //                 int capacity)
{
    int center_x, center_y; //Rendering Center
    float omega, gamma;     //Keyboard Input in grad

    omega = 0; float& omega_ref = omega;
    gamma = 0;  float& gamma_ref = gamma;

    int win_width = 1200; int win_height = 800;
    center_x = win_width/2; int &center_x_ref = center_x;
    center_y = win_height/2; int &center_y_ref = center_y;

    sf::RenderWindow Engine(sf::VideoMode(win_width, win_height), "Window");

    sf::CircleShape X(3.f);
    X.setFillColor(sf::Color::Red);
    sf::CircleShape Y(3.f);
    Y.setFillColor(sf::Color::Green);
    sf::CircleShape Z(3.f);
    Z.setFillColor(sf::Color::Blue);

    Point X_axys(100, 0, 0, X);
    Point Y_axys(0, 100, 0, Y);
    Point Z_axys(0, 0, 100, Z);

    std::vector <Point> Axys;
    Axys.push_back(X_axys);
    Axys.push_back(Y_axys);
    Axys.push_back(Z_axys);

    for(int i = 0; i<Axys.capacity(); i++)
        Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);

    Point Center(125,200,0);
    Point CubeCenter(-150,200,0);
    Point ConeCenter(130, 50,0);
    Point SphereCenter(0,0,0);

    Cube CUBE(100.f, CubeCenter, sf::Color(69, 228, 255, 255));
    std::vector<Point> PointVector_one = CUBE.getPOINTS();
    std::vector<Polygone> Polygones_one = CUBE.getTriangle();

    Prism_Cylinder Prism (170.f, 100.f, 10, Center, sf::Color(168, 235, 150, 255));
    std::vector<Point> PointVector_two = Prism.getPOINTS();
    std::vector<Polygone> Polygones_two = Prism.getTriangle();

    Pyramid_Cone CONE (170.f, 100.f, 9, ConeCenter, sf::Color(250, 90, 125, 255));
    std::vector<Point> PointVector_three = CONE.getPOINTS();
    std::vector<Polygone> Polygones_three = CONE.getTriangle();

    sf::CircleShape point_shape (3.f);
    point_shape.setFillColor(sf::Color(65, 105, 225, 255));
    point_shape.setOutlineThickness(1.5f);
    point_shape.setOutlineColor(sf::Color::Black);

    Sphere Round (200.f, 30.f, SphereCenter, point_shape, sf::Color(69, 228, 255, 255));
    std::vector<Point> PointVector_four = Round.getPOINTS();
    std::vector<Polygone> Polygones_four = Round.getTriangle();

    std::vector<std::vector<Point>> POINTS;
    std::vector<std::vector<Polygone>> POLYGONES;
    int figuresNumber = 0;

    POINTS.push_back(PointVector_two);
    POLYGONES.push_back(Polygones_two);
    figuresNumber++;

    POINTS.push_back(PointVector_one);
    POLYGONES.push_back(Polygones_one);
    figuresNumber++;

    POINTS.push_back(PointVector_three);
    POLYGONES.push_back(Polygones_three);
    figuresNumber++;

    POINTS.push_back(PointVector_four);
    POLYGONES.push_back(Polygones_four);
    figuresNumber++;

    std::vector<int> Order = FigureSort(POINTS, figuresNumber, omega, gamma);
	std::vector<std::vector<int>> izmini_nazvanie;

    for(int i = 0; i<POLYGONES.size(); i++)
    {
        for(int j = 0; j<POLYGONES[i].size(); j++)
            POLYGONES[i][j].setPolygon(omega_ref, gamma_ref,
                                                     center_x, center_y,
                                                     scale, POINTS[i]);
    }


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
                case sf::Event::KeyPressed:
                    switch(event.key.code)
                    {
                        case sf::Keyboard::Q:
                            scale+=0.2;
                            for(int i = 0; i<Axys.capacity(); i++)
                                Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                            for(int i = 0; i<figuresNumber; i++)
                            {
                                for(int j = 0; j<POINTS[i].capacity(); j++)
                                    POINTS[i][j].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                for(int j = 0; j<POLYGONES[i].capacity(); j++)
                                    POLYGONES[i][j].setPolygon(omega_ref, gamma_ref, center_x, center_y,
                                                                             scale, POINTS[i]);
                            }
                            break;
                        case sf::Keyboard::E:
                            if(speed>0.4)
                                scale-=0.2;
                            for(int i = 0; i<Axys.capacity(); i++)
                                Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                            for(int i = 0; i<figuresNumber; i++)
                            {
                                for(int j = 0; j<POINTS[i].capacity(); j++)
                                    POINTS[i][j].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                for(int j = 0; j<POLYGONES[i].capacity(); j++)
                                    POLYGONES[i][j].setPolygon(omega_ref, gamma_ref, center_x, center_y,
                                                                             scale, POINTS[i]);
                            }
                            break;
                        case sf::Keyboard::LShift:
                            speed++;
                            break;
                        case sf::Keyboard::LAlt:
                            if(speed>1)
                                speed--;
                            break;
                        case sf::Keyboard::Up:
                            gamma_ref-=speed;
                            //std::cout<<gamma<<", "<<omega<<"\n";
                            for(int i = 0; i<Axys.capacity(); i++)
                                Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                            for(int i = 0; i<figuresNumber; i++)
                            {
                                for(int j = 0; j<POINTS[i].capacity(); j++)
                                    POINTS[i][j].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                for(int j = 0; j<POLYGONES[i].capacity(); j++)
                                    POLYGONES[i][j].setPolygon(omega_ref, gamma_ref, center_x, center_y,
                                                                             scale, POINTS[i]);
                            }
                            break;
                        case sf::Keyboard::Down:
                            gamma_ref+=speed;
                            //std::cout<<gamma<<", "<<omega<<"\n";
                            for(int i = 0; i<Axys.capacity(); i++)
                                Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                            for(int i = 0; i<figuresNumber; i++)
                            {
                                for(int j = 0; j<POINTS[i].capacity(); j++)
                                    POINTS[i][j].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                for(int j = 0; j<POLYGONES[i].capacity(); j++)
                                    POLYGONES[i][j].setPolygon(omega_ref, gamma_ref, center_x, center_y,
                                                                             scale, POINTS[i]);
                            }
                            break;
                        case sf::Keyboard::Right:
                            omega_ref+=speed;
                            //std::cout<<gamma<<", "<<omega<<"\n";
                            for(int i = 0; i<Axys.capacity(); i++)
                                Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);

                            for(int i = 0; i<figuresNumber; i++)
                            {
                                for(int j = 0; j<POINTS[i].capacity(); j++)
                                    POINTS[i][j].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                for(int j = 0; j<POLYGONES[i].capacity(); j++)
                                    POLYGONES[i][j].setPolygon(omega_ref, gamma_ref, center_x, center_y,
                                                                             scale, POINTS[i]);
                            }

                            break;
                        case sf::Keyboard::Left:
                            omega_ref-=speed;
                           // std::cout<<gamma<<", "<<omega<<"\n";
                            for(int i = 0; i<Axys.capacity(); i++)
                                Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                            for(int i = 0; i<figuresNumber; i++)
                            {
                                for(int j = 0; j<POINTS[i].capacity(); j++)
                                    POINTS[i][j].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                for(int j = 0; j<POLYGONES[i].capacity(); j++)
                                    POLYGONES[i][j].setPolygon(omega_ref, gamma_ref, center_x, center_y,
                                                                             scale, POINTS[i]);
                            }
                            break;
                        case sf::Keyboard::F:
                            activeFigure++;
                            if(activeFigure==figuresNumber)
                                activeFigure = 0;
                            break;

                        case sf::Keyboard::Space:

                            for(int j = 0; j<POINTS[activeFigure].capacity(); j++)
                                    POINTS[activeFigure][j].set_z(POINTS[activeFigure][j].get_z()+speed*5);
                            for(int j = 0; j<POLYGONES[activeFigure].capacity(); j++)
                                    POLYGONES[activeFigure][j].setPolygon(omega_ref, gamma_ref,
                                                                             center_x, center_y,
                                                                             scale, POINTS[activeFigure]);
                            break;
                        case sf::Keyboard::LControl:
                            for(int j = 0; j<POINTS[activeFigure].capacity(); j++)
                                    POINTS[activeFigure][j].set_z(POINTS[activeFigure][j].get_z()-speed*5);
                            for(int j = 0; j<POLYGONES[activeFigure].capacity(); j++)
                                    POLYGONES[activeFigure][j].setPolygon(omega_ref, gamma_ref,
                                                                             center_x, center_y,
                                                                             scale, POINTS[activeFigure]);
                            break;
                        case sf::Keyboard::W:
                            for(int j = 0; j<POINTS[activeFigure].capacity(); j++)
                                    POINTS[activeFigure][j].set_x(POINTS[activeFigure][j].get_x()+speed*5);
                            for(int j = 0; j<POLYGONES[activeFigure].capacity(); j++)
                                    POLYGONES[activeFigure][j].setPolygon(omega_ref, gamma_ref,
                                                                             center_x, center_y,
                                                                             scale, POINTS[activeFigure]);
                            break;
                        case sf::Keyboard::S:
                            for(int j = 0; j<POINTS[activeFigure].capacity(); j++)
                                    POINTS[activeFigure][j].set_x(POINTS[activeFigure][j].get_x()-speed*5);
                           for(int j = 0; j<POLYGONES[activeFigure].capacity(); j++)
                                    POLYGONES[activeFigure][j].setPolygon(omega_ref, gamma_ref,
                                                                             center_x, center_y,
                                                                             scale, POINTS[activeFigure]);

                            break;
                        case sf::Keyboard::D:
                            for(int j = 0; j<POINTS[activeFigure].capacity(); j++)
                                    POINTS[activeFigure][j].set_y(POINTS[activeFigure][j].get_y()-speed*5);
                            for(int j = 0; j<POLYGONES[activeFigure].capacity(); j++)
                                    POLYGONES[activeFigure][j].setPolygon(omega_ref, gamma_ref,
                                                                             center_x, center_y,
                                                                             scale, POINTS[activeFigure]);
                            break;
                        case sf::Keyboard::A:
                            for(int j = 0; j<POINTS[activeFigure].capacity(); j++)
                                    POINTS[activeFigure][j].set_y(POINTS[activeFigure][j].get_y()+speed*5);
                            for(int j = 0; j<POLYGONES[activeFigure].capacity(); j++)
                                    POLYGONES[activeFigure][j].setPolygon(omega_ref, gamma_ref,
                                                                             center_x, center_y,
                                                                             scale, POINTS[activeFigure]);

                            break;
                        case sf::Keyboard::R:
                            Order = FigureSort(POINTS, figuresNumber, omega, gamma);
                            break;
                        default:
                            break;
                    }
            }
        }

        Order = FigureSort(POINTS, figuresNumber, omega, gamma);


        Engine.clear(sf::Color::White);

        /*for(int i = 0; i<POINTS.size(); i++)
        {
            for(int j = 0; j<POINTS[Order[i]].size(); j++)
            {
                Engine.draw(POINTS[Order[i]][j].getShape());
            }
        }*/

        for(int i = 0; i<POLYGONES.size(); i++)
        {
            for(int j = 0; j<POLYGONES[Order[i]].size(); j++)
                Engine.draw(POLYGONES[Order[i]][j].getTriangle(POINTS[Order[i]]));
        }

        for(int i=0;i<3;i++)
        {
        izmini_nazvanie.push_back(PoligoneSort(POLYGONES[i],omega,gamma));
        //std::cout<<"xyi";
        }

        for(int i = 0; i<Axys.capacity(); i++)
            Engine.draw(Axys[i].getShape());

        Engine.display();
        }
    return 0;
}
