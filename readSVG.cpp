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
        
        // TODO complete code -->
        for (XMLElement *child = xml_elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
        {
            if (child->Name() == "ellipse")
            {
                Color fill;
                Point center,radius;
                for (const XMLAttribute *attr = child->FirstAttribute(); attr != nullptr; attr = attr->Next())
                {
                    if (attr->Name() == "fill") fill = parse_color(attr->Value());
                    else if (attr->Name() == "cx") center.x = attr->IntValue();
                    else if (attr->Name() == "cy") center.y = attr->IntValue();
                    else if (attr->Name() == "rx") radius.x = attr->IntValue();
                    else if (attr->Name() == "ry") radius.y = attr->IntValue();
                }
                svg_elements.push_back(new Ellipse(fill, center, radius));
            }
            else if (child->Name() == "circle")
            {
                Color fill;
                Point center;
                int radius;
                for (const XMLAttribute *attr = child->FirstAttribute(); attr != nullptr; attr = attr->Next())
                {
                    if (attr->Name() == "fill") fill = parse_color(attr->Value());
                    else if (attr->Name() == "cx") center.x = attr->IntValue();
                    else if (attr->Name() == "cy") center.y = attr->IntValue();
                    else if (attr->Name() == "r") radius = attr->IntValue();
                }
                svg_elements.push_back(new Circle(fill, center, radius));
            }
            else if (child->Name() == "polyline")
            {
                Color stroke;
                vector<Point> points;
                for (const XMLAttribute *attr = child->FirstAttribute(); attr != nullptr; attr = attr->Next())
                {
                    if (attr->Name() == "stroke") stroke = parse_color(attr->Value());
                    else if (attr->Name() == "points") points = parse_points(attr->Value());
                } 
                svg_elements.push_back(new Polyline(stroke, points));
            }
            else if (child->Name() == "line")
            {
                Color stroke;
                vector<Point> points;
                for (const XMLAttribute *attr = child->FirstAttribute(); attr != nullptr; attr = attr->Next())
                {
                    if (attr->Name() == "stroke") stroke = parse_color(attr->Value());
                    else if (attr->Name() == "points") points = parse_points(attr->Value());
                } 
                svg_elements.push_back(new Line(stroke, points));
            }
            else if (child->Name() == "polygon")
            {
                Color fill;
                vector<Point> points;
                for (const XMLAttribute *attr = child->FirstAttribute(); attr != nullptr; attr = attr->Next())
                {
                    if (attr->Name() == "fill") fill = parse_color(attr->Value());
                    else if (attr->Name() == "points") points = parse_points(attr->Value());
                } 
                svg_elements.push_back(new Polygon(fill, points));
            }
            else if (child->Name() == "rect")
            {
                Color fill;
                vector<Point> points;
                for (const XMLAttribute *attr = child->FirstAttribute(); attr != nullptr; attr = attr->Next())
                {
                    if (attr->Name() == "fill") fill = parse_color(attr->Value());
                    else if (attr->Name() == "points") points = parse_points(attr->Value());
                } 
                svg_elements.push_back(new Rectangle(fill, points));
            }
        }   
    }
}
