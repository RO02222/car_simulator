//
// Created by robbe on 3-3-2022.
//

#ifndef CAR_SIMULATOR_LIGHT_H
#define CAR_SIMULATOR_LIGHT_H


class Light{
private:
    int position;
    int cycle;
public:
    Light(int position, int cycle);
    virtual ~Light();

    int getPosition() const;
    void setPosition(int position);

    int getCycle() const;
    void setCycle(int cycle);
};



#endif //CAR_SIMULATOR_LIGHT_H
