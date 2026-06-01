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
    void Ellipse::translate(const int &x,const int &y){
        center=center.translate({x,y});
    }
    void Ellipse::rotate(const int &v){
        Point transform_origin={0,0};//TO DO: change into the input
        center=center.rotate(transform_origin,v);
    }
    void Ellipse::scale(const int &v){
        Point transform_origin={0,0};//TO DO: change into the input
        radius.y*=v;
        radius.x*=v;
        center=center.scale(transform_origin,v);

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
    void Polyline::translate(const int &x, const int &y){
        for (unsigned long i=0;i<points.size();i++){
            points[i]=points[i].translate({x,y});
        }
    }

    void Polyline::rotate(const int &v){
        Point transform_origin={0,0};//TO DO: change into the input
        for (unsigned long i=0;i<points.size();i++){
            points[i]=points[i].rotate(transform_origin,v);
        }
    }

    void Polyline::scale(const int &v){
        Point transform_origin={0,0};//TO DO: change into the input
        for (unsigned long i=0;i<points.size();i++){
            points[i]=points[i].scale(transform_origin,v);
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

    void Polygon::translate(const int &x, const int &y){
        for (unsigned long i=0;i<points.size();i++){
            points[i]=points[i].translate({x,y});
        }
    }

    void Polygon::rotate(const int &v){
        Point transform_origin={0,0};//TO DO: change into the input
        for (unsigned long i=0;i<points.size();i++){
            points[i]=points[i].rotate(transform_origin,v);
        }
    }

    void Polygon::scale(const int &v){
        Point transform_origin={0,0};//TO DO: change into the input
        for (unsigned long i=0;i<points.size();i++){
            points[i]=points[i].scale(transform_origin,v);
        }
    }

    Rectangle::Rectangle(const Color &fill,
                        const vector<Point> &points)
        : Polygon(fill,points)
    {
    }
    

}
