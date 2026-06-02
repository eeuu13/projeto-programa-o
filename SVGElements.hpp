//! @file shape.hpp
#ifndef __svg_SVGElements_hpp__
#define __svg_SVGElements_hpp__

#include "Color.hpp"
#include "Point.hpp"
#include "PNGImage.hpp"
using namespace std;

namespace svg
{
    class SVGElement
    {

    public:
        SVGElement();
        virtual ~SVGElement();
        virtual void draw(PNGImage &img) const = 0;
        virtual void translate(const int &x,const int &y) =0;
        virtual void rotate(const int &v,Point transform_origin)=0;
        virtual void scale(const int &v,Point transform_origin)=0;

    };

    // Declaration of namespace functions
    // readSVG -> implement it in readSVG.cpp
    // convert -> already given (DO NOT CHANGE) in convert.cpp

    void readSVG(const std::string &svg_file,
                 Point &dimensions,
                 std::vector<SVGElement *> &svg_elements);
    void convert(const std::string &svg_file,
                 const std::string &png_file);

    class Ellipse : public SVGElement
    {
    public:
        Ellipse(const Color &fill, const Point &center, const Point &radius);
        void draw(PNGImage &img) const override;
        void translate(const int &x,const int &y) override;
        void rotate(const int &v,Point transform_origin) override;
        void scale(const int &v,Point transform_origin) override;

    private:
        Color fill;
        Point center;
        Point radius;
    };

    class Circle : public Ellipse
    {
    public:
        Circle(const Color &fill, const Point &center, const int &radius);
    };
    
    class Polyline: public SVGElement
    {
    public:
        Polyline(const Color &stroke,const vector<Point> &points);
        void draw(PNGImage &img) const override;
        void translate(const int &x,const int &y) override;
        void rotate(const int &v,Point transform_origin) override;
        void scale(const int &v,Point transform_origin) override;
    private:
        Color stroke;
        vector<Point> points;
    };

    class Line : public Polyline{
    public:
        Line(const Color &stroke,const vector<Point> &points);

    };

    class Polygon : public SVGElement
    {
    public:
        Polygon(const Color &fill,const vector<Point> &points);
        void  draw (PNGImage &img) const override;
        void translate(const int &x,const int &y) override;
        void rotate(const int &v,Point transform_origin) override;
        void scale(const int &v,Point transform_origin) override;
    private:
        Color fill;
        vector<Point> points;
    };

    class Rectangle : public Polygon
    {
    public:
        Rectangle(const Color &fill,const Point &origin, const Point &sizes);
    };
    
}
#endif
