#include "Button.h"
#include "graphics.h"
using namespace std;

Button::Button(qColor qfill, point qcenter, unsigned int qwidth, unsigned int qheight, std::string qlabel) : Quad(qfill, qcenter, qwidth, qheight) {
    this->qlabel = qlabel;
    qoriginalFill = qfill;
    qhoverFill = {qfill.qred + 0.5, qfill.qgreen + 0.5, qfill.qblue + 0.5};
    qpressFill = {qfill.qred - 0.5, qfill.qgreen - 0.5, qfill.qblue - 0.5};
}

void Button::qdraw() const {
    Quad::qdraw();
    glColor3f(0, 0, 0);
    glRasterPos2i(qcenter.qx - (4 * qlabel.length()), qcenter.qy + 7);
    for (const char &letter : qlabel) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }
}

/* Returns true if the coordinate is inside the box */
bool Button::qisOverlapping(int qx, int qy) const {
    // TODO: Implement
    if(qgetRightX() < qx || qgetBottomY() < qy){
        return false;
    }
    // 2. when one is above the other
    if(qgetLeftX() > qx || qgetTopY() > qy){
        return false;
    }
    return true;
     // Placeholder for compilation
}

/* Change color of the box when the user is hovering over it */
void Button::qhover() {
    qsetColor(qhoverFill);
}

/* Change color of the box when the user is clicking on it */
void Button::qpressDown() {
    qsetColor(qpressFill);
}

/* Change the color back when the user is not clicking/hovering */
void Button::qrelease() {
    qsetColor(qoriginalFill);
}