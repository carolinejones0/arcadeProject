#ifndef GRAPHICSEXAMPLES_RECT_H
#define GRAPHICSEXAMPLES_RECT_H

#include "shape.h"

class Rect : public Shape {
private:
    dimensions size;
    std::string sColor;
public:
    /* Constructors */
    Rect();
    explicit Rect(dimensions size);
    explicit Rect(color fill);
    explicit Rect(point2D center);
    Rect(color fill, point2D center);
    Rect(double red, double green, double blue, double alpha);
    Rect(double x, double y);
    Rect(double red, double green, double blue, double alpha, double x, double y);
    Rect(color fill, double x, double y);
    Rect(double red, double green, double blue, double alpha, point2D center);
    Rect(color fill, dimensions size);
    Rect(point2D center, dimensions size);
    Rect(color fill, point2D center, dimensions size);
    Rect(double red, double green, double blue, double alpha, dimensions size);
    Rect(double x, double y, dimensions size);
    Rect(double red, double green, double blue, double alpha, double x, double y, dimensions size);
    Rect(color fill, double x, double y, dimensions size);
    Rect(double red, double green, double blue, double alpha, point2D center, dimensions size);

    /* Destructor */
    virtual ~Rect() = default;

    /* Getters */
    dimensions getSize() const;
    double getWidth() const;
    double getHeight() const;
    double getLeftX() const override;
    double getRightX() const override;
    double getTopY() const override;
    double getBottomY() const override;
    std::string getSColor() const;

    /* Setters */
    void setSize(dimensions size);
    void setSColor(std::string sColor);
    void setSize(double width, double height);
    void setWidth(double width);
    void setHeight(double height);
    void changeSize(double deltaWidth, double deltaHeight);
    void changeWidth(double delta);
    void changeHeight(double delta);

    /* Check if two Rect objects are overlapping */
    bool isOverlapping(std::vector<Rect> r) const;

    /* Draw */
    void draw() const override;

    bool isOverlapping(Rect r) const;
};


#endif //GRAPHICSEXAMPLES_RECT_H
