#ifndef SHAPE_H
#define SHAPE_H

#include <math.h> // This allows you to use sqrt and pow functions
#include <string>

const double PI = 3.14159265358979323846;

struct dimensions {
    double width;
    double height;

    /* Constructors */
    dimensions();
    dimensions(double w, double h);

    /* Overloaded Operator */
    friend std::ostream& operator << (std::ostream& outs, const dimensions &d);
};

struct color {


    double red;
    double green;
    double blue;
    double alpha; // Opacity (0 is transparent, 1 is solid)

    /* Constructors */
    color();
    color(double r, double g, double b);
    color(double r, double g, double b, double a);

    /* Overloaded Operator */
    friend std::ostream& operator << (std::ostream& outs, const color &c);
};

struct point2D {
    double x;
    double y;

    /* Constructors */
    point2D();
    point2D(double x, double y);

    /* Overloaded Operator */
    friend std::ostream& operator << (std::ostream& outs, const point2D &p);
};

class Shape {
protected:
    color fill;
    point2D center;
    std::string sColor;
    double xVelocity;
    double yVelocity;
    bool collided;

public:
    /* Constructors */
    Shape();
    explicit Shape(color fill);
    explicit Shape(point2D center);
    Shape(color fill, point2D center);
    Shape(double red, double green, double blue, double alpha);
    Shape(double x, double y);
    Shape(double red, double green, double blue, double alpha, double x, double y);
    Shape(color fill, double x, double y);
    Shape(double red, double green, double blue, double alpha, point2D center);

    /* Destructor */
    virtual ~Shape() = default;

    /* Getters */
    color getColor() const;
    double getRed() const;
    double getGreen() const;
    double getBlue() const;
    double getOpacity() const;
    point2D getCenter() const;
    double getCenterX() const;
    double getCenterY() const;
    std::string getSColor() const;
    virtual double getLeftX() const = 0;
    virtual double getRightX() const = 0;
    double getXVelocity() const;
    double getYVelocity() const;
    bool getCollided() const;
    virtual double getTopY() const = 0;
    virtual double getBottomY() const = 0;

    /* Setters */
    void setColor(color c);
    void setColor(double r, double g, double b, double a);
    void setRed(double r);
    void setGreen(double g);
    void setBlue(double b);
    void setOpacity(double a);
    void setCenter(point2D center);
    void setSColor(std::string sColor);
    void setCenter(double x, double y);
    void setCenterX(double x);
    void setCenterY(double y);
    void setXVelocity(double xVel);
    void setYVelocity(double yVel);
    void setVelocity(double xVel, double yVel);
    void setCollided(bool b);
    virtual void move(double deltaX, double deltaY);
    virtual void moveX(double deltaX);
    virtual void moveY(double deltaY);
    void bounceX();
    void bounceY();
    bool isOverlapping(const Shape &s) const;
    virtual void draw() const = 0;
};

#endif //SHAPE_H
