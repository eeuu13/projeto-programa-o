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
    Point parse_single(string value)
    {
        Point point;
        stringstream ss(value);
        string s;
        ss >> s;
        point.x = stoi(s);
        ss >> s;
        point.y = stoi(s);
        return point;
    }

    void apply_transform(string transform, SVGElement* &element, vector<SVGElement *>& svg_elements,Point transform_origin)
    {
        int v = transform.find('(');
        if (v==9) // Translate
        {
            Point ponto = parse_single(transform.substr(v + 1, transform.size() - v - 1));
            element->translate(ponto.x,ponto.y);
        }
        else if (v == 6) // Rotate
        {
            int rot = stoi(transform.substr(v + 1, transform.size() - v - 1));
            element->rotate(rot,transform_origin);
        }
        else if (v == 5) // Scale
        {
            int scale = stoi(transform.substr(v + 1, transform.size() - v - 1));
            element->scale(scale,transform_origin);
        }
        
    }
    void a_child(XMLElement *element, vector<SVGElement *>& svg_elements, vector<pair<string,Point>> prev_transforms={})
        {
            for (XMLElement *child = element->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
            {
                if ((string)child->Name() == "ellipse")
                {
                    Color fill;
                    Point center, radius, transform_origin = {0, 0};
                    string trans = " ";
                    string id= " ";
                    for (const XMLAttribute *attr = child->FirstAttribute(); attr != nullptr; attr = attr->Next())
                    {
                        if ((string)attr->Name() == "fill") fill = parse_color(attr->Value());
                        else if ((string)attr->Name() == "cx") center.x = attr->IntValue();
                        else if ((string)attr->Name() == "cy") center.y = attr->IntValue();
                        else if ((string)attr->Name() == "rx") radius.x = attr->IntValue();
                        else if ((string)attr->Name() == "ry") radius.y = attr->IntValue();
                        else if ((string) attr->Name() == "transform-origin") transform_origin = parse_single(attr->Value());
                        else if ((string) attr->Name() == "transform") trans = attr->Value();
                        else if ((string) attr->Name() == "id") id = attr->Value();
                    }
                    SVGElement* object = new Ellipse(fill, center, radius,id);
                    apply_transform(trans, object, svg_elements,transform_origin);
                    for (int i=prev_transforms.size()-1;i>=0;i--){
                        pair<string,Point> prev_trans=prev_transforms[i];
                        apply_transform(prev_trans.first,object,svg_elements,prev_trans.second);
                    }
                    svg_elements.push_back(object);
                }
                else if ((string)child->Name() == "circle")
                {
                    Color fill;
                    Point center, transform_origin = {0, 0};
                    int radius;
                    string trans = " ";
                    string id= " ";
                    for (const XMLAttribute *attr = child->FirstAttribute(); attr != nullptr; attr = attr->Next())
                    {
                        if ((string)attr->Name() == "fill") fill = parse_color(attr->Value());
                        else if ((string)attr->Name() == "cx") center.x = attr->IntValue();
                        else if ((string)attr->Name() == "cy") center.y = attr->IntValue();
                        else if ((string)attr->Name() == "r") radius = attr->IntValue();
                        else if ((string) attr->Name() == "transform-origin") transform_origin = parse_single(attr->Value());
                        else if ((string) attr->Name() == "transform") trans = attr->Value();
                        else if ((string) attr->Name() == "id") id = attr->Value();
                    }
                    SVGElement* object = new Circle(fill, center, radius,id);
                    apply_transform(trans, object, svg_elements,transform_origin);
                    for (int i=prev_transforms.size()-1;i>=0;i--){
                        pair<string,Point> prev_trans=prev_transforms[i];
                        apply_transform(prev_trans.first,object,svg_elements,prev_trans.second);
                    }
                    svg_elements.push_back(object);
                }
                else if ((string)child->Name() == "polyline")
                {
                    Color stroke;
                    vector<Point> points;
                    Point transform_origin = {0, 0};
                    string trans = " ";
                    string id = " ";
                    for (const XMLAttribute *attr = child->FirstAttribute(); attr != nullptr; attr = attr->Next())
                    {
                        if ((string) attr->Name() == "stroke") stroke = parse_color(attr->Value());
                        else if ((string)attr->Name() == "points") points = parse_points(attr->Value());
                        else if ((string) attr->Name() == "transform-origin") transform_origin = parse_single(attr->Value());
                        else if ((string) attr->Name() == "transform") trans = attr->Value();
                        else if ((string) attr->Name() == "id") id = attr->Value();
                    } 
                    SVGElement* object = new Polyline(stroke, points,id);
                    apply_transform(trans, object, svg_elements,transform_origin);
                    for (int i=prev_transforms.size()-1;i>=0;i--){
                        pair<string,Point> prev_trans=prev_transforms[i];
                        apply_transform(prev_trans.first,object,svg_elements,prev_trans.second);
                    }
                    svg_elements.push_back(object);
                }
                else if ((string) child->Name() == "line")
                {
                    Color stroke;
                    Point point1, point2, transform_origin = {0, 0};
                    string trans = " ";
                    string id = " ";
                    for (const XMLAttribute *attr = child->FirstAttribute(); attr != nullptr; attr = attr->Next())
                    {
                        if ((string) attr->Name() == "stroke") stroke = parse_color(attr->Value());
                        else if ((string) attr->Name() == "x1") point1.x = attr->IntValue();
                        else if ((string) attr->Name() == "x2") point2.x = attr->IntValue();
                        else if ((string) attr->Name() == "y1") point1.y = attr->IntValue();
                        else if ((string) attr->Name() == "y2") point2.y = attr->IntValue();
                        else if ((string) attr->Name() == "transform-origin") transform_origin = parse_single(attr->Value());
                        else if ((string) attr->Name() == "transform") trans = attr->Value();
                        else if ((string) attr->Name() == "id") id = attr->Value();
                    } 
                    SVGElement* object = new Line(stroke, vector<Point>{point1, point2},id);
                    apply_transform(trans, object, svg_elements,transform_origin);
                    for (int i=prev_transforms.size()-1;i>=0;i--){
                        pair<string,Point> prev_trans=prev_transforms[i];
                        apply_transform(prev_trans.first,object,svg_elements,prev_trans.second);
                    }
                    svg_elements.push_back(object);
                }
                else if ((string)child->Name() == "polygon")
                {
                    Color fill;
                    vector<Point> points;
                    Point transform_origin = {0, 0};
                    string trans = " ";
                    string id = " ";
                    for (const XMLAttribute *attr = child->FirstAttribute(); attr != nullptr; attr = attr->Next())
                    {
                        if ((string)attr->Name() == "fill") fill = parse_color(attr->Value());
                        else if ((string)attr->Name() == "points") points = parse_points(attr->Value());
                        else if ((string) attr->Name() == "transform-origin") transform_origin = parse_single(attr->Value());
                        else if ((string) attr->Name() == "transform") trans = attr->Value();
                        else if ((string) attr->Name() == "id") id = attr->Value();
                    } 
                    SVGElement* object = new Polygon(fill, points,id);
                    apply_transform(trans, object, svg_elements,transform_origin);
                    for (int i=prev_transforms.size()-1;i>=0;i--){
                        pair<string,Point> prev_trans=prev_transforms[i];
                        apply_transform(prev_trans.first,object,svg_elements,prev_trans.second);
                    }
                    svg_elements.push_back(object);
                }
                else if ((string) child->Name() == "rect")
                {
                    Color fill;
                    Point origin, size, transform_origin = {0, 0};
                    string trans = " ";
                    string id = " ";
                    for (const XMLAttribute *attr = child->FirstAttribute(); attr != nullptr; attr = attr->Next())
                    {
                        if ((string) attr->Name() == "fill") fill = parse_color(attr->Value());
                        else if ((string) attr->Name() == "x") origin.x = attr->IntValue();
                        else if ((string) attr->Name() == "y") origin.y = attr->IntValue();
                        else if ((string) attr->Name() == "width") size.x = attr->IntValue();
                        else if ((string) attr->Name() == "height") size.y = attr->IntValue();
                        else if ((string) attr->Name() == "transform-origin") transform_origin = parse_single(attr->Value());
                        else if ((string) attr->Name() == "transform") trans = attr->Value();
                        else if ((string) attr->Name() == "id") id = attr->Value();
                    } 
                    SVGElement* object = new Rectangle(fill, origin, size,id);
                    apply_transform(trans, object, svg_elements,transform_origin);
                    for (int i=prev_transforms.size()-1;i>=0;i--){
                        pair<string,Point> prev_trans=prev_transforms[i];
                        apply_transform(prev_trans.first,object,svg_elements,prev_trans.second);
                    }
                    svg_elements.push_back(object);
                }
                else if (string(child->Name()) == "g")
                {
                    vector<pair<string,Point>> transforms={};
                    for (pair<string,Point> s:prev_transforms){
                        transforms.push_back(s);
                    }
                    pair<string,Point> last={" ",{0,0}};
                    for (const XMLAttribute *attr = child->FirstAttribute(); attr != nullptr; attr = attr->Next())
                    {
                        if ((string) attr->Name() == "transform-origin") last.second = parse_single(attr->Value());
                        else if ((string) attr->Name() == "transform") last.first = attr->Value();
                    }
                    transforms.push_back(last);
                    a_child(child, svg_elements,transforms);
                }
                else if (string(child->Name()) == "use"){
                    Point transform_origin = {0, 0};
                    string trans = " ";
                    string href= " ";
                    string id= " ";
                    for (const XMLAttribute *attr = child->FirstAttribute(); attr != nullptr; attr = attr->Next())
                    {
                        if ((string) attr->Name() == "transform-origin") transform_origin = parse_single(attr->Value());
                        else if ((string) attr->Name() == "transform") trans = attr->Value();
                        else if ((string) attr->Name() == "href") href = attr->Value();
                    }
                    href=href.substr(1,href.size()-1);
                    for (SVGElement* element:svg_elements){
                        if (element->get_id()==href){
                            auto new_element= new SVGElement element;//////////////////////////////////////////////////////////////////////
                            new_element = 
                        }
                    }
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
        a_child(xml_elem, svg_elements);
    }
}
