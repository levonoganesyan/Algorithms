
#pragma once

namespace algo
{
    template<class T = int>
    struct Point2
    {
        T x, y;
    };
    template<class T = int>
    struct Point3
    {
        T x, y, z;
    };
    template<typename T>
    double distance(Point2<T> f, Point2<T> s)
    {
        double dx = f.x - s.x;
        double dy = f.y - s.y;
        return sqrt(dx * dx + dy * dy);
    }
    template<typename T>
    double distance(Point3<T> f, Point3<T> s)
    {
        double dx = f.x - s.x;
        double dy = f.y - s.y;
        double dz = f.z - s.z;
        return sqrt(dx * dx + dy * dy + dz * dz);
    }

    template<class T = int>
    struct Line2
    {
        T A, B, C;
    };
    
    template<class T>
    Line2<T> CreateLine(Point2<T> f, Point2<T> s)
    {
        Line2<T> line;
        line.A = s.y - f.y;
        line.B = f.x - s.x;
        line.C = -(line.A * s.x + line.B * s.y);
        return line;
    }

    template<class T1, typename T2>
    double DistanceToLine(Line2<T1> line, Point2<T2> point)
    {
        return line.A * point.x + line.B * point.y + line.C;
    }

}