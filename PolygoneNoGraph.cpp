#include <iostream>
#include "PointNoGraph.cpp"
class Polygone
{
private:
    int one, two, three;
    Point distanceTest;
    double distance;
public:
    Polygone (){}
    Polygone(int one, int two, int three, std::vector<Point> P)
             {
                double x = (P[one].get_x()+P[two].get_x())/2;
                double y = (P[one].get_y()+P[two].get_y())/2;
                double z = (P[one].get_z()+P[three].get_z())/2;
                Point temp(x,y,z);
                distanceTest = temp;
                this->one = one;
                this->two = two;
                this->three = three;
             }
    void setPolygon(double &omega, double &gamma,
                    double center_x, double center_y, double scale,
                    std::vector<Point> P)
    {
        double cam_x = scale*cos(GTR*omega);
        double cam_y = scale*sin(GTR*omega);
        double cam_z = scale*sin(GTR*gamma);

        double x = cam_x - distanceTest.get_x();
        double y = cam_y - distanceTest.get_y();
        double z = cam_z - distanceTest.get_z();

        distance = pow(x,2)+pow(y,2)+pow(z,2);
    }
	 Point get_distanceTest()
    {
        return distanceTest;
    }
    void Out()
    {
        std::cout<<"["<<one<<", "<<two<<", "<<three<<"]\n";
    }

    double get_distance()
    {
        return distance;
    }

};
