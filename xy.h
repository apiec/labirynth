#ifndef XY_H_INCLUDED
#define XY_H_INCLUDED

struct xy {

    int x, y;

    xy& operator= (const xy& rhs){
        x = rhs.x;
        y = rhs.y;
        return *this;
    }
    bool operator==(const xy& rhs) const{
        return (x == rhs.x) && (y == rhs.y);
    }
    bool operator!=(const xy& rhs) const{
        return !(*this == rhs);
    }
};

#endif // XY_H_INCLUDED
