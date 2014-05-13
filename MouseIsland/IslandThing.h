#ifndef ISLANDTHING_H
#define ISLANDTHING_H

class IslandThing
{
public:

    IslandThing();
    ~IslandThing();

    int getX();
    int getY();
    void setX(int);
    void setY(int);

    bool getShown();
    void setShown(bool);

    int getDisplayChar();
    void setDisplayChar(int);

private:

    int x,y;
    bool isShown;
    int displayChar;
};

#endif // ISLANDTHING_H
