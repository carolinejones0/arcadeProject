#ifndef GRAPHICS_STARTER_BUTTON_H
#define GRAPHICS_STARTER_BUTTON_H

#include "Quad.h"
#include <string>

class Button : public Quad {
private:
    std::string qlabel;
    qColor qoriginalFill, qhoverFill, qpressFill;

public:
    Button(qColor qfill, point qcenter, unsigned int qwidth, unsigned int qheight, std::string qlabel);
    /* Uses OpenGL to draw the box with the label on top */
    virtual void qdraw() const override;

    /* Returns true if the coordinate is inside the box */
    bool qisOverlapping(int qx, int qy) const;

    /* Change color of the Button when the user is hovering over it */
    void qhover();

    /* Change color of the Button when the user is clicking on it */
    void qpressDown();

    /* Change the color back when the user is not clicking/hovering */
    void qrelease();
};


#endif //GRAPHICS_STARTER_BUTTON_H
