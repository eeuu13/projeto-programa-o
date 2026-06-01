#include <iostream>
#include "SVGElements.hpp"
#include "external/tinyxml2/tinyxml2.h"
#include <sstream>

using namespace std;
using namespace tinyxml2;

namespace svg
{
    vector<Point> parse_points(const char* value)
    {
        vector<Point> points;
        stringstream ss(value);
        string s;

        while (ss >> s)
        {
            int v = s.find(',');
            int x = stoi(s.substr(0, v));
            int y = stoi(s.substr(v + 1));
            points.push_back({x, y});
        }
        return points;
    }
    void a_child(XMLElement *element, vector<SVGElement *>& svg_elements)
        {
            for (XMLElement *child = element->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
            {
                if ((string)child->Name() == "ellipse")
                {
                    Color fill;
                    Point center,radius;
                    for (const XMLAttribute *attr = child->FirstAttribute(); attr != nullptr; attr = attr->Next())
                    {
                        if ((string)attr->Name() == "fill") fill = parse_color(attr->Value());
                        else if ((string)attr->Name() == "cx") center.x = attr->IntValue();
                        else if ((string)attr->Name() == "cy") center.y = attr->IntValue();
                        else if ((string)attr->Name() == "rx") radius.x = attr->IntValue();
                        else if ((string)attr->Name() == "ry") radius.y = attr->IntValue();
                    }
                    svg_elements.push_back(new Ellipse(fill, center, radius));
                }
                else if ((string)child->Name() == "circle")
                {
                    Color fill;
                    Point center;
                    int radius;
                    for (const XMLAttribute *attr = child->FirstAttribute(); attr != nullptr; attr = attr->Next())
                    {
                        if ((string)attr->Name() == "fill") fill = parse_color(attr->Value());
                        else if ((string)attr->Name() == "cx") center.x = attr->IntValue();
                        else if ((string)attr->Name() == "cy") center.y = attr->IntValue();
                        else if ((string)attr->Name() == "r") radius = attr->IntValue();
                    }
                    svg_elements.push_back(new Circle(fill, center, radius));
                }
                else if ((string)child->Name() == "polyline")
                {
                    Color stroke;
                    vector<Point> points;
                    for (const XMLAttribute *attr = child->FirstAttribute(); attr != nullptr; attr = attr->Next())
                    {
                        if ((string)attr->Name() == "stroke") stroke = parse_color(attr->Value());
                        else if ((string)attr->Name() == "points") points = parse_points(attr->Value());
                    } 
                    svg_elements.push_back(new Polyline(stroke, points));
                }
                else if ((string) child->Name() == "line")
                {
                    Color stroke;
                    Point point1, point2;
                    for (const XMLAttribute *attr = child->FirstAttribute(); attr != nullptr; attr = attr->Next())
                    {
                        if ((string) attr->Name() == "stroke") stroke = parse_color(attr->Value());
                        else if ((string) attr->Name() == "x1") point1.x = attr->IntValue();
                        else if ((string) attr->Name() == "x2") point2.x = attr->IntValue();
                        else if ((string) attr->Name() == "y1") point1.y = attr->IntValue();
                        else if ((string) attr->Name() == "y2") point2.y = attr->IntValue();
                    } 
                    svg_elements.push_back(new Line(stroke, vector<Point>{point1, point2}));
                }
                else if ((string)child->Name() == "polygon")
                {
                    Color fill;
                    vector<Point> points;
                    for (const XMLAttribute *attr = child->FirstAttribute(); attr != nullptr; attr = attr->Next())
                    {
                        if ((string)attr->Name() == "fill") fill = parse_color(attr->Value());
                        else if ((string)attr->Name() == "points") points = parse_points(attr->Value());
                    } 
                    svg_elements.push_back(new Polygon(fill, points));
                }
                else if ((string) child->Name() == "rect")
                {
                    Color fill;
                    Point origin, size;
                    for (const XMLAttribute *attr = child->FirstAttribute(); attr != nullptr; attr = attr->Next())
                    {
                        if ((string) attr->Name() == "fill") fill = parse_color(attr->Value());
                        else if ((string) attr->Name() == "x") origin.x = attr->IntValue();
                        else if ((string) attr->Name() == "y") origin.y = attr->IntValue();
                        else if ((string) attr->Name() == "width") size.x = attr->IntValue();
                        else if ((string) attr->Name() == "height") size.y = attr->IntValue();
                    } 
                    svg_elements.push_back(new Rectangle(fill, origin, size));
                }
                else if (string((string)child->Name()) == "g")
                {
                    a_child(child, svg_elements);
                }
            } 
        }
    void readSVG(const string& svg_file, Point& dimensions, vector<SVGElement *>& svg_elements)
    {
        XMLDocument doc;
        XMLError r = doc.LoadFile(svg_file.c_str());
        if (r != XML_SUCCESS)
        {
            throw runtime_error("Unable to load " + svg_file);
        }
        XMLElement *xml_elem = doc.RootElement();

        dimensions.x = xml_elem->IntAttribute("width");
        dimensions.y = xml_elem->IntAttribute("height");
        a_child(xml_elem,svg_elements);
    }
}
