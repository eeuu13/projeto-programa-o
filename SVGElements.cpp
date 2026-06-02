#include "SVGElements.hpp"
#include <iostream>
namespace svg
{
    // These must be defined!
    SVGElement::SVGElement() :id_(""){}
    SVGElement::~SVGElement() {}

    // Ellipse (initial code provided)
    Ellipse::Ellipse(const Color &fill,
                     const Point &center,
                     const Point &radius,
                     const string &id)
        : fill(fill), center(center), radius(radius),SVGElement(id)
    {
    }
    void Ellipse::draw(PNGImage &img) const
    {
        img.draw_ellipse(center, radius, fill);
    }
    void Ellipse::translate(const int &x,const int &y){
        center=center.translate({x,y});
    }
    void Ellipse::rotate(const int &v,Point transform_origin){
        center=center.rotate(transform_origin,v);
    }
    void Ellipse::scale(const int &v,Point transform_origin){
        radius.y*=v;
        radius.x*=v;
        center=center.scale(transform_origin,v);

    }

    // @todo provide the implementation of SVGElement derived classes
    // HERE -->
    Circle::Circle(const Color &fill,
                     const Point &center,
                     const int &radius,
                     const string &id)
        : Ellipse(fill,center,{radius,radius},id)

    {
    }
    Polyline::Polyline(const Color &stroke,
                       const vector<Point> &points
                       ,const string &id)
        : stroke(stroke), points(points),SVGElement(id)
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

    void Polyline::rotate(const int &v,Point transform_origin){
        for (unsigned long i=0;i<points.size();i++){
            points[i]=points[i].rotate(transform_origin,v);
        }
    }

    void Polyline::scale(const int &v,Point transform_origin){
        for (unsigned long i=0;i<points.size();i++){
            points[i]=points[i].scale(transform_origin,v);
        }
    }

    Line::Line(const Color &stroke,
            const vector<Point> &points,
            const string &id)
        : Polyline(stroke,points,id)
    { 
    }
    Polygon::Polygon(const Color &fill,
                     const vector<Point> &points,
                     const string &id)
        : fill(fill), points(points),SVGElement(id)
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

    void Polygon::rotate(const int &v,Point transform_origin){
        for (unsigned long i=0;i<points.size();i++){
            points[i]=points[i].rotate(transform_origin,v);
        }
    }

    void Polygon::scale(const int &v,Point transform_origin){
        for (unsigned long i=0;i<points.size();i++){
            points[i]=points[i].scale(transform_origin,v);
        }
    }

    Rectangle::Rectangle(const Color &fill,
                         const Point &origin,
                         const Point &sizes,
                         const string &id)
        : Polygon(fill,{origin,
            {origin.x+sizes.x-1,origin.y},
            {origin.x+sizes.x-1,origin.y+sizes.y-1},
            {origin.x,origin.y+sizes.y-1}},
            id)
    {
    }
    

}
