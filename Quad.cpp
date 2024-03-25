#include "Quad.h"
#include "graphics.h"
#include "shape.h"

Quad::Quad() {
    qfill = {0, 0, 0};
    qcenter = {0, 0};
    qwidth = 50;
    qheight = 50;
}

Quad::Quad(qColor qfill, point qcenter, unsigned int qwidth, unsigned int qheight) {
    this->qfill = qfill;
    this->qcenter = qcenter;
    this->qwidth = qwidth;
    this->qheight = qheight;
}

int Quad::qgetCenterX() const {
    return qcenter.qx;
}

int Quad::qgetLeftX() const {
    return qcenter.qx - (qwidth / 2);
}

int Quad::qgetRightX() const {
    return qcenter.qx + (qwidth / 2);
}

int Quad::qgetCenterY() const {
    return qcenter.qy;
}

int Quad::qgetTopY() const {
    return qcenter.qy - (qheight / 2);
}

int Quad::qgetBottomY() const {
    return qcenter.qy + (qheight / 2);
}

point Quad::qgetCenter() const {
    return qcenter;
}

double Quad::qgetRed() const {
    return qfill.qred;
}

double Quad::qgetGreen() const {
    return qfill.qgreen;
}

double Quad::qgetBlue() const {
    return qfill.qblue;
}

qColor Quad::qgetFill() const {
    return qfill;
}

unsigned int Quad::qgetWidth() const {
    return qwidth;
}

unsigned int Quad::qgetHeight() const {
    return qheight;
}

double Quad::qgetXVelocity() const {
    return xVelocity;
}

double Quad::qgetYVelocity() const {
    return yVelocity;
}

bool Quad::qgetCollided() const {
    return collided;
}

void Quad::qsetCenter(int x, int y) {
    qcenter = {x,y};
}

void Quad::qsetCenterX(int x) {
    qcenter.qx = x;
}

void Quad::qsetCenterY(int y) {
    qcenter.qy = y;
}

void Quad::qsetColor(double qred, double qgreen, double qblue) {
    qfill = {qred, qgreen, qblue};
}

void Quad::qsetColor(qColor qfill) {
    this->qfill = qfill;
}

void Quad::qmove(int qdeltaX, int qdeltaY) {
    qcenter.qx += qdeltaX;
    qcenter.qy += qdeltaY;
}

void Quad::qsetXVelocity(int xVel) {
    xVelocity = xVel;
}

void Quad::qsetYVelocity(int yVel) {
    yVelocity = yVel;
}

void Quad::qsetVelocity(int xVel, int yVel) {
    xVelocity = xVel;
    yVelocity = yVel;
}

void Quad::qsetCollided(bool b) {
    collided = b;
}
void Quad::qresize(unsigned int qwidth, unsigned int qheight) {
    this->qwidth = qwidth;
    this->qheight = qheight;
}
void Quad::bounceX() {
    xVelocity *= -1;
}

void Quad::bounceY() {
    yVelocity *= -1;
}

bool Quad::qisOverlapping(const Quad &s) const {
    if (qgetRightX()<s.qgetLeftX() || s.qgetRightX()<qgetLeftX()) {
        return false;
    }
    else if (qgetBottomY()<s.qgetTopY() || s.qgetBottomY()<qgetTopY()) {
        return false;
    }
    else {
        return true;
    }
}

void Quad::qdraw() const {
    // TODO: Implement

    glBegin(GL_QUADS);
    glColor3f(qgetRed(), qgetGreen(), qgetBlue());
    glVertex2i(qgetLeftX(), qgetBottomY());
    glVertex2i(qgetLeftX(), qgetTopY());
    glVertex2i(qgetRightX(), qgetTopY());
    glVertex2i(qgetRightX(), qgetBottomY());
    glEnd();
}

