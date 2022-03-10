//
// Created by robbe on 3-3-2022.
//

#ifndef CAR_SIMULATOR_CAR_H
#define CAR_SIMULATOR_CAR_H

class Car{
private:
    int distance;
public:
    Car (int distance);
    virtual ~Car();

    int getDistance() const;
    void setDistance(int distance);
};


#endif //CAR_SIMULATOR_CAR_H
