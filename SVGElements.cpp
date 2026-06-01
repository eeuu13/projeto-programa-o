#include "SVGElements.hpp"

namespace svg
{
    // These must be defined!
    SVGElement::SVGElement() {}
    SVGElement::~SVGElement() {}

    // Ellipse (initial code provided)
    Ellipse::Ellipse(const Color &fill,
                     const Point &center,
                     const Point &radius)
        : fill(fill), center(center), radius(radius)
    {
    }
    void Ellipse::draw(PNGImage &img) const
    {
        img.draw_ellipse(center, radius, fill);
    }

    // @todo provide the implementation of SVGElement derived classes
    // HERE -->
    Circle::Circle(const Color &fill,
                     const Point &center,
                     const int &radius)
        : Ellipse(fill,center,{radius,radius})

    {
    }
    Polyline::Polyline(const Color &stroke,
                       const vector<Point> &points)
        : stroke(stroke), points(points)
    {
    }
    void Polyline::draw(PNGImage &img) const
    {
        for (unsigned long i=0;i<points.size()-1;i++){
            img.draw_line(points[i],points[i+1],stroke);
        }
    }
    Line::Line(const Color &stroke,
            const vector<Point> &points)
        : Polyline(stroke,points)
    { 
    }
    Polygon::Polygon(const Color &fill,
                     const vector<Point> &points)
        : fill(fill), points(points)
    {
    }
    void Polygon::draw(PNGImage &img) const
    {
        img.draw_polygon(points,fill);
    }
    Rectangle::Rectangle(const Color &fill,
                        const vector<Point> &points)
        : Polygon(fill,points)
    {
    }
    

}
