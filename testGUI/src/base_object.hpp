#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

namespace Flyy
{
    // using PositionUnit = long long int;
    typedef long long int PositionUnit;
    #define P_UNIT_TO_METER 10000

    struct Position
    {
        PositionUnit x;
        PositionUnit y;
        
        Position(int px = 0, int py = 0);
        Position& operator=(const Position& p);
    };

    struct Rectangle
    {
        Position p;
        PositionUnit w;
        PositionUnit h;

        Rectangle();
        Rectangle(PositionUnit w, PositionUnit h, Position position);
    };


    class BaseObject
    {
    protected:
        Rectangle m_rect;

    public:
        BaseObject();
        BaseObject(Rectangle rect);
        BaseObject(int w, int h, Position position);
        virtual ~BaseObject();
    };
}

#endif //_OBJECTS_HPP_
