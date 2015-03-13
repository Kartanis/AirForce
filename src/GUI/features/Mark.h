#ifndef OBJECT_H
#define OBJECT_H

class Mark
{
private:

public:
    int x;
    int y;
    int angle;

    Mark();
    void setPositionDirection(int, int, int);
    virtual void display();



};

#endif // OBJECT_H

