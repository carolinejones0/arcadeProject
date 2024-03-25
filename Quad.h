#ifndef CONFETTIFY_QUAD_H
#define CONFETTIFY_QUAD_H
#include "graphics.h"
#include "shape.h"

struct qColor {
    double qred;
    double qgreen;
    double qblue;
};

struct point {
    int qx;
    int qy;
};

class Quad {
protected:
    qColor qfill;
    point qcenter;
    unsigned int qwidth;
    unsigned int qheight;
    double xVelocity;
    double yVelocity;
    bool collided;

public:
    Quad();
    Quad(qColor qfill, point qcenter, unsigned int qwidth, unsigned int qheight);

    int qgetCenterX() const;
    int qgetLeftX() const;
    int qgetRightX() const;
    int qgetCenterY() const;
    int qgetTopY() const;
    int qgetBottomY() const;
    point qgetCenter() const;

    double qgetXVelocity() const;
    double qgetYVelocity() const;
    bool qgetCollided() const;

    double qgetRed() const;
    double qgetGreen() const;
    double qgetBlue() const;
    qColor qgetFill() const;

    unsigned int qgetWidth() const;
    unsigned int qgetHeight() const;

    void qsetColor(double qred, double qgreen, double qblue);
    void qsetColor(qColor qfill);
    void qmove(int qdeltaX, int qdeltaY);
    void qresize(unsigned int qwidth, unsigned int qheight);
    void qsetCenter(int x, int y);
    void qsetCenterX(int x);
    void qsetCenterY(int y);
    void qsetVelocity(int x, int y);
    void qsetYVelocity(int y);
    void qsetXVelocity(int x);
    void qsetCollided(bool c);

    void bounceX();
    void bounceY();

    bool qisOverlapping(const Quad &s) const;

    virtual void qdraw() const;
};

#endif //CONFETTIFY_QUAD_H
