#include "pch.h"
#include "Node.h"

Node::Node(Point2D p) : point(p) {}
Point2D Node::getPoint() { return point; }
void Node::setPoint(Point2D p) { point = p; }
std::string Node::toString() {
    return "(" + std::to_string(point.x) + ";" + std::to_string(point.y) + ")";
}
