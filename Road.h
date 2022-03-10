//
// Created by robbe on 3-3-2022.
//

#ifndef CAR_SIMULATOR_ROAD_H
#define CAR_SIMULATOR_ROAD_H
#include <vector>
#include <iostream>

class Road;
class Light;
class Car;

class Road{
private:
    std::string name;
    int length;
    std::vector<Light*> lights;
    std::vector<Car*> cars;
public:
    Road(const std::string &name, int length);
    virtual ~Road();

    const std::string &getName() const;
    void setName(const std::string &name);

    int getLength() const;
    void setLength(int length);

    const std::vector<Light *> &getLights() const;
    void setLights(const std::vector<Light *> &lights);
    void addLights(int position, int cycle);

    const std::vector<Car *> &getCars() const;
    void setCars(const std::vector<Car *> &cars);
    void addCars(int distance);

};

#endif //CAR_SIMULATOR_ROAD_H
