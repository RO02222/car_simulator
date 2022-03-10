//
// Created by robbe on 10-3-2022.
//

#ifndef CAR_SIMULATOR_CARGEN_H
#define CAR_SIMULATOR_CARGEN_H
class Road;

class CarGen {
    private:
        int frequency;
        Road* road;
    public:
        CarGen (Road* road,int frequency);
        virtual ~CarGen();

    int getFrequency() const;

    void setFrequency(int frequency);

    Road *getRoad() const;

    void setRoad(Road *road);
};


#endif //CAR_SIMULATOR_CARGEN_H
