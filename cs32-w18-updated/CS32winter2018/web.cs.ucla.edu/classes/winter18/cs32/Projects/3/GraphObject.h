#ifndef GRAPHOBJ_H_
#define GRAPHOBJ_H_

#include "GameConstants.h"
#include <set>

const int ANIMATION_POSITIONS_PER_TICK = 1;

using Direction = int;

class GraphObject
{
protected:
	GraphObject(int imageID, double startX, double startY, int dir = 0, double size = 1.0, int depth = 0)
	 : m_imageID(imageID), m_animationNumber(0), m_x(startX), m_y(startY),
	   m_destX(startX), m_destY(startY), m_direction(dir),
	   m_size(size <= 0 ? 1 : size), m_depth(depth)
	{
		getGraphObjects(m_depth).insert(this);
	}

public:
	virtual ~GraphObject()
	{
		getGraphObjects(m_depth).erase(this);
	}

    double getX() const
    {
          // If already moved but not yet animated, use new location anyway.
        return m_destX;
    }
    
    double getY() const
    {
          // If already moved but not yet animated, use new location anyway.
        return m_destY;
    }
    
    virtual void moveTo(double x, double y)
    {
        m_destX = x;
        m_destY = y;
        m_animationNumber++;
    }

    int getDirection() const
    {
        return m_direction;
    }
    
    void setDirection(int d)
    {
        while (d < 0)
            d += 360;
        
        m_direction = d % 360;
    }
    
    void setSize(double size)
    {
        m_size = size;
    }
    
    double getSize() const
    {
        return m_size;
    }

	double getRadius() const
	{
		const int RADIUS_PER_UNIT = 8;
		return RADIUS_PER_UNIT * m_size;
	}

    template<typename Func>
    static void drawAllObjects(Func plotFunc)
    {
        for (int depth = NUM_DEPTHS - 1; depth >= 0; depth--)
        {
            for (GraphObject* go : getGraphObjects(depth))
            {
                go->animate();
                plotFunc(go->m_imageID, go->m_animationNumber, go->m_x, go->m_y, go->m_direction, go->m_size);
            }
        }
    }

private:
    static const int NUM_DEPTHS = 4;
    int             m_imageID;
    unsigned int    m_animationNumber;
    double          m_x;
    double          m_y;
    double          m_destX;
    double          m_destY;
    int				m_direction;
    double          m_size;
    int             m_depth;

    void animate()
    {
        m_x = m_destX;
        m_y = m_destY;
        // moveALittle(m_x, m_destX);
        // moveALittle(m_y, m_destY);
    }
 
    void moveALittle(double& from, double& to)
    {
        static const double DISTANCE = 1.0/ANIMATION_POSITIONS_PER_TICK;
        if (to - from >= DISTANCE)
            from += DISTANCE;
        else if (from - to >= DISTANCE)
            from -= DISTANCE;
        else
            from = to;
    }

    static std::set<GraphObject*>& getGraphObjects(int depth)
    {
        static std::set<GraphObject*> m_graphObjects[NUM_DEPTHS];
        if (depth < NUM_DEPTHS)
            return m_graphObjects[depth];
        else
            return m_graphObjects[0];         // empty;
    }
    
      // Prevent copying or assigning GraphObjects
    GraphObject(const GraphObject&) = delete;
    GraphObject& operator=(const GraphObject&) = delete;
};

#endif // GRAPHOBJ_H_
