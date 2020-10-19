#pragma once
#include <cmath>
#include <iostream>
#include <vector>

class WrongShape : public std::exception {};

bool areSame(const double &a, const double &b) {
  const double EPS = 1e-6;

  return abs(a - b) < EPS;
}

double angle2rad(const double &angle) { return angle * M_PI / 180.; }

/** Point **/
struct Point {
  double x;
  double y;

  Point() : x(0.), y(0.) {}

  Point(const double &x_, const double y_) : x(x_), y(y_) {}

  Point &operator=(const Point &other) {
    if (this != &other) {
      this->x = other.x;
      this->y = other.y;
    }
    return *this;
  }

  bool operator==(const Point &other) const {
    return areSame(this->x, other.x) and areSame(this->y, other.y);
  }

  bool operator!=(const Point &other) const { return !(*this == other); }

  double dist_to(const Point &other) const {
    return sqrt((this->x - other.x) * (this->x - other.x)
                    + (this->y - other.y) * (this->y - other.y));
  }

  Point operator-=(const Point &other) {
    this->x -= other.x;
    this->y -= other.y;
    return *this;
  }

  Point operator+=(const Point &other) {
    this->x += other.x;
    this->y += other.y;
    return *this;
  }

  Point operator-(const Point &other) const {
    Point new_point(*this);

    new_point -= other;
    return new_point;
  }

  Point operator+(const Point &other) const {
    Point new_point(*this);

    new_point += other;
    return new_point;
  }

  Point operator*(const double coefficient) const {
    Point new_point;
    new_point.x = this->x * coefficient;
    new_point.y = this->y * coefficient;
    return new_point;
  }

  Point operator/(const double coefficient) const {
    Point new_point;
    new_point.x = this->x / coefficient;
    new_point.y = this->y / coefficient;
    return new_point;
  }

  void rotate(const Point &center, const double &angle) {
    Point new_point;

    new_point.x = (this->x - center.x) * cos(angle2rad(angle))
        - (this->y - center.y) * sin(angle2rad(angle));
    new_point.y = (this->y - center.y) * cos(angle2rad(angle))
        + (this->x - center.x) * sin(angle2rad(angle));
    *this = new_point;
  }
};

std::ostream &operator<<(std::ostream &output, const Point &point) {
  output << "x: " << point.x << " y: " << point.y << std::endl;

  return output;
}
/** Point **/

/** Line **/
class Line {
  /* y = k * x + b */
  /* 0 * x = b */
  double k;
  double b;

 public:
  Line() : k(0), b(0) {}

  Line(const double &k_, const double &b_) : k(k_), b(b_) {}

  Line(const Point &a, const Point &b) : k((b.y - a.y) / (b.x - a.x)) {
    if (isinf(this->k))
      this->b = a.x;
    else
      this->b = a.y - k * a.x;
  }

  Line(const Point &a, const double &k_) : k(k_), b(a.y - k_ * a.x) {
    if (isinf(this->k))
      this->b = a.x;
  }

  Line(const Line &a_b, const Point &point, const double &alpha) :
      k((a_b.k + tan(alpha)) / (1.0 - a_b.k * tan(alpha))) {
    if (isinf(this->k))
      this->b = point.x;
    else
      this->b = point.y - this->k * point.x;
  }

  bool operator==(const Line &other) const {
    if (isinf(this->k) and isinf(other.k))
      return areSame(this->b, other.b);
    else
      return areSame(this->k, other.k) and areSame(this->b, other.b);
  }

  bool operator!=(const Line &other) const { return !(*this == other); }

  double get_k() const { return this->k; }

  double get_b() const { return this->b; }

  double angleBetween(const Line &other) const {
    return atan((other.k - this->k) / (1 + other.k * this->k));
  }

  Point cross_point(const Line &other) const {
    if (isinf(this->k))
      return Point(this->b, this->b * other.k + other.b);
    else if (isinf(other.k))
      return Point(other.b, other.b * this->k + this->b);
    else
      return Point((other.b - this->b) / (this->k - other.k),
                   (this->k * other.b - this->b * other.k) / (this->k - other.k)
      );
  }
};

std::ostream &operator<<(std::ostream &output, const Line &line) {
  output << "Line params K: " << line.get_k();
  output << " B: " << line.get_b() << std::endl;

  return output;
}

Point projection(const Point &point, const Line &line) {
  double line_k = line.get_k();
  if (areSame(line_k, 0.0))
    return Point(point.x, 0.0);
  else if (isinf(line_k))
    return Point(0.0, point.y);
  else {
    Line proj_line(point, -1.0 / line_k);

    return line.cross_point(proj_line);
  }
}
/** Line **/

/** Shape **/
class Shape {
 public:
  virtual double perimeter() const { return 0.; }

  virtual double area() const { return 0.; }

  virtual bool operator==(const Shape &other) const { return true; }

  virtual bool operator!=(const Shape &other) const {
    return !(*this == other);
  }

  virtual void rotate(const Point &center, const double &angle) {}

  virtual void reflex(const Point &center) {}

  virtual void reflex(const Line &axis) {}

  virtual void scale(const Point &center, const double &coefficient) {}
};
/** Shape **/

/** Polygon **/
class Polygon : public Shape {
 protected:
  std::vector<Point> points;
 public:
  explicit Polygon(const size_t &size) : points(size) {
    if (size < 3)
      throw WrongShape();
  }

  Polygon(const std::initializer_list<Point> &points_arr) : points(points_arr) {
    if (this->points.size() < 3)
      throw WrongShape();
  }

  explicit Polygon(const std::vector<Point> &points_vec) : points(points_vec) {
    if (this->points.size() < 3)
      throw WrongShape();
  }

  size_t verticesCount() const { return this->points.size(); }

  std::vector<Point> getVertices() const { return this->points; }

  bool operator==(const Polygon &other) const {
    if (this->points.size() != other.points.size())
      return false;

    for (auto &pnt: other.points) {
      bool is_equal = false;
      for (auto &cur_pnt: this->points)
        is_equal |= (pnt == cur_pnt);
      if (!is_equal)
        return false;
    }

    return true;
  }

  bool operator!=(const Polygon &other) const { return !(*this == other); }

  Point center_of_mass() const {
    Point center;
    size_t size = this->points.size();

    for (auto &point: points)
      center += point / size;

    return center;
  }

  void rotate(const Point &center, const double &angle) override {
    for (auto &point: this->points)
      point.rotate(center, angle);
  }

  void scale(const Point &center, const double &coefficient) override {
    for (auto &point: this->points)
      point = (point - center) * coefficient;
  }

  void reflex(const Point &center) override { this->rotate(center, 180); };

  void reflex(const Line &axis) override {
    Point center = this->center_of_mass();
    Point project = projection(center, axis);
    this->rotate(project, 180);
  };

  double perimeter() const override {
    double perimeter = 0.0;
    size_t size = this->points.size();

    for (size_t i = 0; i < size; ++i)
      perimeter += this->points[i].dist_to(this->points[(i + 1) % size]);

    return perimeter;
  }

  double area() const override {
    // https://ru.wikipedia.org/wiki/Формула_площади_Гаусса
    double area = 0.0;
    size_t size = this->points.size();

    for (size_t i = 0; i < size; ++i) {
      double x_1 = points[i].x;
      double x_2 = points[(i + 1) % size].x;
      double y_1 = points[i].y;
      double y_2 = points[(i + 1) % size].y;

      area += (x_1 * y_2 - x_2 * y_1) / 2;
    }
    return abs(area);
  };
};

std::ostream &operator<<(std::ostream &output, const Polygon &poly) {
  auto arr_p = poly.getVertices();

  for (size_t i = 0; i < arr_p.size(); ++i)
    output << "Point " << i + 1 << ": " << arr_p[i];

  return output;
}
/** Polygon **/

/** Ellipse **/
class Ellipse : public Shape {
 protected:
  Point f1;
  Point f2;
  double a;
  double b;
  double c;
 public:
  Ellipse(const Point &a_, const Point &b_, const double &dists)
      : f1(a_),
        f2(b_),
        a(dists / 2.),
        b(sqrt(pow(dists / 2., 2) - pow(a_.dist_to(b_) / 2., 2))),
        c(a_.dist_to(b_) / 2.) {}

  std::pair<Point, Point> focuses() const {
    return std::make_pair(this->f1, this->f2);
  }

  double eccentricity() const { return this->c / this->a; }

  Point center() const { return (this->f1 + this->f2) / 2.; }

  double perimeter() const override {
    double h = pow((this->a - this->b), 2) / pow((this->a + this->b), 2);
    double ramanujan_factor = 1 + 3. * h / (10. + sqrt(4. - 3 * h));

    double perimeter = M_PI * (this->a + this->b) * ramanujan_factor;
    return perimeter;
  }

  double area() const override { return M_PI * this->a * this->b; }
};
/** Ellipse **/

/** Circle **/
class Circle : public Ellipse {
 public:
  Circle(Point &a, const double &radius) : Ellipse(a, a, 2. * radius) {}

  double radius() const { return this->a; }
};
/** Circle **/

/** Triangle **/
class Triangle : public Polygon {
 public:
  Triangle(const Point &a, const Point &b, const Point &c)
      : Polygon({a, b, c}) {}

  Circle inscribedCircle() const {
    Line a_b = Line(this->points[0], this->points[1]);
    Line b_c = Line(this->points[1], this->points[2]);
    Line c_a = Line(this->points[2], this->points[0]);

    Line bisector_a = Line(a_b, this->points[1], a_b.angleBetween(b_c) / 2.);
    Line bisector_b = Line(b_c, this->points[2], b_c.angleBetween(c_a) / 2.);

    Point ins_center = bisector_a.cross_point(bisector_b);
    Circle ins_circle(ins_center,
                      ins_center.dist_to(projection(ins_center, c_a)));
    return ins_circle;
  }

  Circle circumscribedCircle() const {
    Point center_a_b((this->points[0] + this->points[1]) / 2.);
    Point center_b_c((this->points[1] + this->points[2]) / 2.);
    Line a_b(this->points[0], this->points[1]);
    Line b_c(this->points[1], this->points[2]);

    Line bisection_a_b(center_a_b, -1.0 / a_b.get_k());
    Line bisection_b_c(center_b_c, -1.0 / b_c.get_k());

    Point cum_center(bisection_a_b.cross_point(bisection_b_c));
    Circle cum_circle(cum_center, cum_center.dist_to(this->points[2]));
    return cum_circle;
  }

  Point centroid() { return this->center_of_mass(); }

  Point orthocenter() {
    Point a(this->points[0]);
    Point b(this->points[1]);
    Line b_c = Line(b, this->points[2]);
    Line c_a = Line(this->points[2], a);

    Line height_a_h(a, projection(a, b_c));
    Line height_b_h(b, projection(b, c_a));

    Point ort_center = height_a_h.cross_point(height_b_h);
    return ort_center;
  }

  Line EulerLine() {
    Point centroid = this->center_of_mass();
    Point ort_center = this->orthocenter();

    Line euler_line(centroid, ort_center);
    return euler_line;
  }

  Circle ninePointsCircle() {
    Point ort_center = this->orthocenter();
    Circle ins_circle = this->circumscribedCircle();
    Point nine_center = (ort_center + ins_circle.center()) / 2.;

    Circle nine_point_circle(nine_center, ins_circle.radius() / 2.);
    return nine_point_circle;
  }
};
/** Triangle **/

/** Rectangle **/
class Rectangle : public Polygon {
 public:
  Rectangle(const Point &a_, const Point &b_, const double &ratio)
      : Polygon(4) {
    double a_b = a_.dist_to(b_);
    double b_c = ratio * a_b;
    double rad_alpha = atan((a_.x - b_.x) / (a_.y - b_.y));

    this->points = {a_, b_,
                    b_ + Point((cos(rad_alpha) * b_c), sin(rad_alpha) * b_c),
                    a_ + Point((cos(rad_alpha) * b_c), sin(rad_alpha) * b_c)
    };
  }

  Point center() const { return this->center_of_mass(); }

  std::pair<Line, Line> diagonals() const {
    Line a_c(this->points[0], this->points[2]);
    Line b_d(this->points[1], this->points[3]);

    return std::make_pair(a_c, b_d);
  }
};
/** Rectangle **/

/** Square **/
class Square : public Rectangle {
 public:
  Square(const Point &a, const Point &b) : Rectangle({a, b, 1}) {}

  Circle circumscribedCircle() {
    double radius = this->points[0].dist_to(this->points[2]) / 2.;
    Point center = this->center();

    Circle cum_circle(center, radius);
    return cum_circle;
  }

  Circle inscribedCircle() {
    double radius = this->points[0].dist_to(this->points[1]) / 2.;
    Point center = this->center();

    Circle ins_circle(center, radius);
    return ins_circle;
  }
};
/** Square **/