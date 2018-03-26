#ifndef XY_H_INCLUDED
#define XY_H_INCLUDED

/** \brief A two dimensional point.
 *
 * A struct to hold the coordinates of a two dimensional point.
 * It has two integer variables: x and y.
**/
struct xy {

    int x; /**< The x coordinate of the point. */
    int y; /**< The y coordinate of the point. */


    /**
     * Copies coordinates from the right hand side point.
    **/
    xy& operator= (const xy& rhs){
        x = rhs.x;
        y = rhs.y;
        return *this;
    }

    /**
     * Compares the coordinates of two xy points.
     * Two xy points are equal if both of their corresponding coordinates are equal.
    **/
    bool operator==(const xy& rhs) const{
        return (x == rhs.x) && (y == rhs.y);
    }

    /**
     * If any of the coordinates is not equal to the corresponding
     * coordinate of the other point two points are not equal.
    **/
    bool operator!=(const xy& rhs) const{
        return !(*this == rhs);
    }
};

#endif // XY_H_INCLUDED
