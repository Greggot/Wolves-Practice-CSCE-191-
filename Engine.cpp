#include "Figure.cpp"
#include <vector>

class Engine
{
private:
    double scale = 1;
    unsigned long long speed = 4;
    unsigned long long activeFigure = 0;

    double getDistance(Point one, double omega, double gamma)
    {
        double cam_x = 500*cos(omega*GTR);
        double cam_y = 500*sin(omega*GTR);
        double cam_z = 500*sin(gamma*GTR);

        double x = cam_x - one.get_x();
        double y = cam_y - one.get_y();
        double z = cam_z - one.get_z();

        return sqrt(pow(x, 2)+pow(y, 2)+pow(z, 2));
    }

    std::vector<unsigned long long> FigureSort(std::vector<std::vector<Point>> PointS, unsigned long long figuresNumber, double omega, double gamma)
    {
        size_t SIZE = PointS.size();
        unsigned long long SIZE_ = static_cast<unsigned long long>(SIZE);
        std::vector<unsigned long long> sizes;
        for(unsigned long long i  = 0; i<SIZE_; i++)
        {

            unsigned long long temp_ = static_cast<unsigned long long>(SIZE);

            sizes.push_back(temp_);
        }
        std::vector<double> Distance;
        std::vector<unsigned long long> Out;
        for(unsigned long long i = 0; i<figuresNumber; i++)
            Out.push_back(i);

        for(unsigned long long i = 0; i<figuresNumber; i++)
            Distance.push_back(getDistance(PointS[i][sizes[i]], omega, gamma));

        for(unsigned long long i = 0; i<figuresNumber; i++)
        {
            for(unsigned long long j = 0; j<figuresNumber; j++)
            {
                if(Distance[i]>Distance[j])
                       {
                           double temp = Distance[i];
                           Distance[i] = Distance[j];
                           Distance[j] = temp;

                           unsigned long long Itemp = Out[i];
                           Out[i] = Out[j];
                           Out[j] = Itemp;
                       }
            }
        }
        if(gamma>-180&&gamma<0)
            std::reverse(Out.begin(), Out.end());
        return Out;
    }

    double getDistanceXY(Point one, double omega)
    {
        double cam_x = 500*cos(omega*GTR);
        double cam_y = 500*sin(omega*GTR);

        double x = cam_x - one.get_x();
        double y = cam_y - one.get_y();

        return sqrt(pow(x, 2)+pow(y, 2));
    }

    std::vector<unsigned long long> PolygoneSort(std::vector<Polygone> Poly, double omega, double gamma)
    {
        std::vector<double> Distance;
        std::vector<unsigned long long> Out;
        for(unsigned long long i = 0; i<Poly.size(); i++)
        {
            Distance.push_back(getDistance(Poly[i].get_distanceTest(), omega, gamma));
            Out.push_back(i);

        }

        for(unsigned long long i = 0; i<Distance.size(); i++)
        {
            for(unsigned long long j = 0; j<Distance.size(); j++)
            {
                if(Distance[i]>Distance[j])
                {
                    double temp = Distance[i];
                    Distance[i] = Distance[j];
                    Distance[j] = temp;

                    unsigned long long Itemp = Out[i];
                    Out[i] = Out[j];
                    Out[j] = Itemp;
                }
            }
        }
        for(unsigned long long i = 0; i<Distance.size(); i++)
        {
            Distance[Out[i]] = Poly[Out[i]].get_distanceTest().get_z();
        }
        if(gamma<90)
        {
            std::reverse(Out.begin(), Out.end());
            std::reverse(Distance.begin(), Distance.end());
        }
        if(gamma>=-180&&gamma<-90)
        {
            std::reverse(Out.begin(), Out.end());
            std::reverse(Distance.begin(), Distance.end());
        }

        return Out;
    }
public:
    Engine(unsigned int win_width, unsigned int win_height, std::vector<std::vector<Point>> PointS, std::vector<std::vector<Polygone>> POLYGONES, unsigned long long figuresNumber)
    {
        unsigned long long center_x, center_y;
        double omega, gamma;

        omega = 0; double& omega_ref = omega;
        gamma = 0;  double& gamma_ref = gamma;

        center_x = win_width/2;
        center_y = win_height/2;

        sf::RenderWindow Engine(sf::VideoMode(win_width, win_height), "3D presentation");

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

        for(unsigned long long i = 0; i<Axys.size(); i++)
            Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);

        for(unsigned long long i = 0; i<POLYGONES.size(); i++)
            PolygoneSort(POLYGONES[i], omega, gamma);

        std::vector<unsigned long long> Order = FigureSort(PointS, POLYGONES.size(), omega, gamma);
        std::vector<std::vector<unsigned long long>> Order_two;

        for(unsigned long long i = 0; i<POLYGONES.size(); i++)
        {
            for(unsigned long long j = 0; j<POLYGONES[i].size(); j++)
                POLYGONES[i][j].setPolygon(omega_ref, gamma_ref,
                                                         center_x, center_y,
                                                         scale, PointS[i]);

            Order_two.push_back(PolygoneSort(POLYGONES[i], omega, gamma));
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
                                for(unsigned long long i = 0; i<Axys.size(); i++)
                                    Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                for(unsigned long long i = 0; i<figuresNumber; i++)
                                {
                                    for(unsigned long long j = 0; j<PointS[i].size(); j++)
                                        PointS[i][j].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                    for(unsigned long long j = 0; j<POLYGONES[i].size(); j++)
                                        POLYGONES[i][j].setPolygon(omega_ref, gamma_ref, center_x, center_y,
                                                                                 scale, PointS[i]);
                                }
                                break;
                            case sf::Keyboard::E:
                                if(scale>0.4)
                                    scale-=0.2;
                                for(unsigned long long i = 0; i<Axys.size(); i++)
                                    Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                for(unsigned long long i = 0; i<figuresNumber; i++)
                                {
                                    for(unsigned long long j = 0; j<PointS[i].size(); j++)
                                        PointS[i][j].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                    for(unsigned long long j = 0; j<POLYGONES[i].size(); j++)
                                        POLYGONES[i][j].setPolygon(omega_ref, gamma_ref, center_x, center_y,
                                                                                 scale, PointS[i]);
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
                                std::cout<<gamma<<", "<<omega<<"\n";
                                for(unsigned long long i = 0; i<Axys.size(); i++)
                                    Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                for(unsigned long long i = 0; i<figuresNumber; i++)
                                {
                                    for(unsigned long long j = 0; j<PointS[i].size(); j++)
                                        PointS[i][j].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                    for(unsigned long long j = 0; j<POLYGONES[i].size(); j++)
                                        POLYGONES[i][j].setPolygon(omega_ref, gamma_ref, center_x, center_y,
                                                                                 scale, PointS[i]);
                                }
                                break;
                            case sf::Keyboard::Down:
                                gamma_ref+=speed;
                                for(unsigned long long i = 0; i<Axys.size(); i++)
                                    Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                for(unsigned long long i = 0; i<figuresNumber; i++)
                                {
                                    for(unsigned long long j = 0; j<PointS[i].size(); j++)
                                        PointS[i][j].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                    for(unsigned long long j = 0; j<POLYGONES[i].size(); j++)
                                        POLYGONES[i][j].setPolygon(omega_ref, gamma_ref, center_x, center_y,
                                                                                 scale, PointS[i]);
                                }
                                break;
                            case sf::Keyboard::Right:
                                omega_ref+=speed;

                                for(unsigned long long i = 0; i<Axys.size(); i++)
                                    Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);

                                for(unsigned long long i = 0; i<figuresNumber; i++)
                                {
                                    for(unsigned long long j = 0; j<PointS[i].size(); j++)
                                        PointS[i][j].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                    for(unsigned long long j = 0; j<POLYGONES[i].size(); j++)
                                        POLYGONES[i][j].setPolygon(omega_ref, gamma_ref, center_x, center_y,
                                                                                 scale, PointS[i]);
                                }

                                break;
                            case sf::Keyboard::Left:
                                omega_ref-=speed;
                                for(unsigned long long i = 0; i<Axys.size(); i++)
                                    Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                for(unsigned long long i = 0; i<figuresNumber; i++)
                                {
                                    for(unsigned long long j = 0; j<PointS[i].size(); j++)
                                        PointS[i][j].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                    for(unsigned long long j = 0; j<POLYGONES[i].size(); j++)
                                        POLYGONES[i][j].setPolygon(omega_ref, gamma_ref, center_x, center_y,
                                                                                 scale, PointS[i]);
                                }
                                break;
                            case sf::Keyboard::F:
                                activeFigure++;
                                if(activeFigure==figuresNumber)
                                    activeFigure = 0;
                                break;

                            case sf::Keyboard::Space:

                                for(unsigned long long j = 0; j<PointS[activeFigure].size(); j++)
                                        PointS[activeFigure][j].set_z(PointS[activeFigure][j].get_z()+speed*5);
                                for(unsigned long long j = 0; j<POLYGONES[activeFigure].size(); j++)
                                        POLYGONES[activeFigure][j].setPolygon(omega_ref, gamma_ref,
                                                                                 center_x, center_y,
                                                                                 scale, PointS[activeFigure]);
                                break;
                            case sf::Keyboard::LControl:
                                for(unsigned long long j = 0; j<PointS[activeFigure].size(); j++)
                                        PointS[activeFigure][j].set_z(PointS[activeFigure][j].get_z()-speed*5);
                                for(unsigned long long j = 0; j<POLYGONES[activeFigure].size(); j++)
                                        POLYGONES[activeFigure][j].setPolygon(omega_ref, gamma_ref,
                                                                                 center_x, center_y,
                                                                                 scale, PointS[activeFigure]);
                                break;
                            case sf::Keyboard::W:
                                for(unsigned long long j = 0; j<PointS[activeFigure].size(); j++)
                                        PointS[activeFigure][j].set_x(PointS[activeFigure][j].get_x()+speed*5);
                                for(unsigned long long j = 0; j<POLYGONES[activeFigure].size(); j++)
                                        POLYGONES[activeFigure][j].setPolygon(omega_ref, gamma_ref,
                                                                                 center_x, center_y,
                                                                                 scale, PointS[activeFigure]);
                                break;
                            case sf::Keyboard::S:
                                for(unsigned long long j = 0; j<PointS[activeFigure].size(); j++)
                                        PointS[activeFigure][j].set_x(PointS[activeFigure][j].get_x()-speed*5);
                               for(unsigned long long j = 0; j<POLYGONES[activeFigure].size(); j++)
                                        POLYGONES[activeFigure][j].setPolygon(omega_ref, gamma_ref,
                                                                                 center_x, center_y,
                                                                                 scale, PointS[activeFigure]);

                                break;
                            case sf::Keyboard::D:
                                for(unsigned long long j = 0; j<PointS[activeFigure].size(); j++)
                                        PointS[activeFigure][j].set_y(PointS[activeFigure][j].get_y()-speed*5);
                                for(unsigned long long j = 0; j<POLYGONES[activeFigure].size(); j++)
                                        POLYGONES[activeFigure][j].setPolygon(omega_ref, gamma_ref,
                                                                                 center_x, center_y,
                                                                                 scale, PointS[activeFigure]);
                                break;
                            case sf::Keyboard::A:
                                for(unsigned long long j = 0; j<PointS[activeFigure].size(); j++)
                                        PointS[activeFigure][j].set_y(PointS[activeFigure][j].get_y()+speed*5);
                                for(unsigned long long j = 0; j<POLYGONES[activeFigure].size(); j++)
                                        POLYGONES[activeFigure][j].setPolygon(omega_ref, gamma_ref,
                                                                                 center_x, center_y,
                                                                                 scale, PointS[activeFigure]);

                                break;
                            default:
                                break;
                        }
                }
            }

            Order = FigureSort(PointS, figuresNumber, omega, gamma);
            Order_two.clear();
            for(unsigned long long i = 0; i<POLYGONES.size(); i++)
                Order_two.push_back(PolygoneSort(POLYGONES[i], omega, gamma));

            Engine.clear(sf::Color::White);

            for(unsigned long long i = 0; i<POLYGONES.size(); i++)
            {
                for(unsigned long long j = 0; j<POLYGONES[Order[i]].size(); j++)
                    Engine.draw(POLYGONES[Order[i]][Order_two[Order[i]][j]].getTriangle(PointS[Order[i]]));
            }

           for(unsigned long long i = 0; i<PointS.size(); i++)
            {
                for(unsigned long long j = 0; j<PointS[Order[i]].size(); j++)
                {
                    Engine.draw(PointS[Order[i]][j].getShape());
                }
            }

            for(unsigned long long i = 0; i<Axys.size(); i++)
                Engine.draw(Axys[i].getShape());

            Engine.display();
            }
    }

    Engine(unsigned int win_width, unsigned int win_height, std::vector<std::vector<Point>> PointS, unsigned long long figuresNumber)
    {
        unsigned long long center_x, center_y;
        double omega, gamma;

        omega = 0; double& omega_ref = omega;
        gamma = 0;  double& gamma_ref = gamma;

        center_x = win_width/2;
        center_y = win_height/2;

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

        for(unsigned long long i = 0; i<Axys.size(); i++)
            Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);


        std::vector<unsigned long long> Order = FigureSort(PointS, figuresNumber, omega, gamma);

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
                                for(unsigned long long i = 0; i<Axys.size(); i++)
                                    Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                for(unsigned long long i = 0; i<figuresNumber; i++)
                                {
                                    for(unsigned long long j = 0; j<PointS[i].size(); j++)
                                        PointS[i][j].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                }
                                break;
                            case sf::Keyboard::E:
                                if(scale>0.4)
                                    scale-=0.2;
                                for(unsigned long long i = 0; i<Axys.size(); i++)
                                    Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                for(unsigned long long i = 0; i<figuresNumber; i++)
                                {
                                    for(unsigned long long j = 0; j<PointS[i].size(); j++)
                                        PointS[i][j].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
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
                                std::cout<<gamma<<", "<<omega<<"\n";
                                for(unsigned long long i = 0; i<Axys.size(); i++)
                                    Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                for(unsigned long long i = 0; i<figuresNumber; i++)
                                {
                                    for(unsigned long long j = 0; j<PointS[i].size(); j++)
                                        PointS[i][j].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                }
                                break;
                            case sf::Keyboard::Down:
                                gamma_ref+=speed;
                                for(unsigned long long i = 0; i<Axys.size(); i++)
                                    Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                for(unsigned long long i = 0; i<figuresNumber; i++)
                                {
                                    for(unsigned long long j = 0; j<PointS[i].size(); j++)
                                        PointS[i][j].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                }
                                break;
                            case sf::Keyboard::Right:
                                omega_ref+=speed;

                                for(unsigned long long i = 0; i<Axys.size(); i++)
                                    Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);

                                for(unsigned long long i = 0; i<figuresNumber; i++)
                                {
                                    for(unsigned long long j = 0; j<PointS[i].size(); j++)
                                        PointS[i][j].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                }

                                break;
                            case sf::Keyboard::Left:
                                omega_ref-=speed;
                                for(unsigned long long i = 0; i<Axys.size(); i++)
                                    Axys[i].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);
                                for(unsigned long long i = 0; i<figuresNumber; i++)
                                {
                                    for(unsigned long long j = 0; j<PointS[i].size(); j++)
                                        PointS[i][j].setPoint(omega_ref, gamma_ref, center_x, center_y, scale);

                                }
                                break;
                            case sf::Keyboard::F:
                                activeFigure++;
                                if(activeFigure==figuresNumber)
                                    activeFigure = 0;
                                break;

                            case sf::Keyboard::Space:

                                for(unsigned long long j = 0; j<PointS[activeFigure].size(); j++)
                                        PointS[activeFigure][j].set_z(PointS[activeFigure][j].get_z()+speed*5);

                                break;
                            case sf::Keyboard::LControl:
                                for(unsigned long long j = 0; j<PointS[activeFigure].size(); j++)
                                        PointS[activeFigure][j].set_z(PointS[activeFigure][j].get_z()-speed*5);
                                break;
                            case sf::Keyboard::W:
                                for(unsigned long long j = 0; j<PointS[activeFigure].size(); j++)
                                        PointS[activeFigure][j].set_x(PointS[activeFigure][j].get_x()+speed*5);
                                break;
                            case sf::Keyboard::S:
                                for(unsigned long long j = 0; j<PointS[activeFigure].size(); j++)
                                        PointS[activeFigure][j].set_x(PointS[activeFigure][j].get_x()-speed*5);

                                break;
                            case sf::Keyboard::D:
                                for(unsigned long long j = 0; j<PointS[activeFigure].size(); j++)
                                        PointS[activeFigure][j].set_y(PointS[activeFigure][j].get_y()-speed*5);
                                break;
                            case sf::Keyboard::A:
                                for(unsigned long long j = 0; j<PointS[activeFigure].size(); j++)
                                        PointS[activeFigure][j].set_y(PointS[activeFigure][j].get_y()+speed*5);
                                break;
                            default:
                                break;
                        }
                }
            }

            Order = FigureSort(PointS, figuresNumber, omega, gamma);
            for(unsigned long long i = 0; i<PointS.size(); i++)
            {
                for(unsigned long long j = 0; j<PointS[Order[i]].size(); j++)
                {
                    Engine.draw(PointS[Order[i]][j].getShape());
                }
            }

            for(unsigned long long i = 0; i<Axys.size(); i++)
                Engine.draw(Axys[i].getShape());

            Engine.display();
            }
    }
};

