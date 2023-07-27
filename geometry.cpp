#include "geometry.hpp"

Vector::Vector() {}
Vector::Vector(int64_t indx, int64_t indy) : x_(indx), y_(indy) {}

int64_t Vector::operator*(Vector second) const {
  int64_t result;
  result = x_ * second.x_ + y_ * second.y_;
  return result;
}

int64_t Vector::operator^(Vector second) const {
  int64_t result;
  result = x_ * second.y_ - y_ * second.x_;
  return result;
}

Vector operator+(Vector first, Vector second) {
  Vector result;
  result.x_ = first.x_ + second.x_;
  result.y_ = first.y_ + second.y_;
  return result;
}

Vector operator-(Vector first, Vector second) {
  Vector result;
  result.x_ = first.x_ - second.x_;
  result.y_ = first.y_ - second.y_;
  return result;
}

Vector& Vector::operator+=(Vector second) {
  x_ = x_ + second.x_;
  y_ = y_ + second.y_;
  return *this;
}

Vector& Vector::operator-=(Vector second) {
  x_ = x_ - second.x_;
  y_ = y_ - second.y_;
  return *this;
}

Vector operator*(Vector first, int64_t digit) {
  Vector result;
  result.x_ = first.x_ * digit;
  result.y_ = first.y_ * digit;
  return result;
}

Vector operator*(int64_t digit, Vector first) {
  Vector result;
  result.x_ = first.x_ * digit;
  result.y_ = first.y_ * digit;
  return result;
}

Vector& Vector::operator-() {
  x_ *= (-1);
  y_ *= (-1);
  return *this;
}

int64_t Vector::GetX() const { return x_; }
int64_t Vector::GetY() const { return y_; }

Point::Point() {}
Point::Point(int64_t indx, int64_t indy) : x_(indx), y_(indy) {}
int64_t Point::GetX() const { return x_; }
int64_t Point::GetY() const { return y_; }
Vector operator-(const Point& k_first, const Point& k_second) {
  int64_t one;
  int64_t two;
  one = k_first.GetX() - k_second.GetX();
  two = k_first.GetY() - k_second.GetY();
  Vector result(one, two);
  return result;
}
bool Point::ContainsPoint(const Point& k_second) const {
  return ((x_ == k_second.x_) && (y_ == k_second.y_));
}
size_t Point::Distance(const Point& k_second) const {
  return (x_ - k_second.GetX()) * (x_ - k_second.GetX()) +
         (y_ - k_second.GetY()) * (y_ - k_second.GetY());
}
bool Point::CrossSegment(const Segment& k_second) const {
  return k_second.ContainsPoint(*this);
}
void Point::Move(const Vector& arr) {
  x_ += arr.GetX();
  y_ += arr.GetY();
}
IShape* Point::Clone() const { return new Point(*this); }

Segment::Segment() {}
Segment::Segment(Point inda, Point indb) : a_(inda), b_(indb) {}
Point Segment::GetA() const { return a_; }
Point Segment::GetB() const { return b_; }
bool Segment::ContainsPoint(const Point& k_second) const {
  Vector left;
  Vector right;
  left = k_second - a_;
  right = b_ - k_second;
  return ((left ^ right) == 0 && (left * right) >= 0);
}
bool Segment::CrossSegment(const Segment& k_second) const {
  if (ContainsPoint(k_second.a_) || ContainsPoint(k_second.b_)) {
    return true;
  }
  if (k_second.ContainsPoint(a_) || k_second.ContainsPoint(b_)) {
    return true;
  }

  if (((b_ - a_) ^ (k_second.b_ - k_second.a_)) == 0) {
    return !(true);
  }

  return (((b_ - a_) ^ (k_second.a_ - a_)) * ((b_ - a_) ^ (k_second.b_ - a_)) <=
              0 &&
          ((k_second.b_ - k_second.a_) ^ (a_ - k_second.a_)) *
                  ((k_second.b_ - k_second.a_) ^ (b_ - k_second.a_)) <=
              0);
}
void Segment::Move(const Vector& arr) {
  a_.Move(arr);
  b_.Move(arr);
}
IShape* Segment::Clone() const { return new Segment(*this); }

Line::Line() {}
Line::Line(Point inda, Point indb) : a_(inda), b_(indb) {}

int64_t Line::GetA() const { return (a_.GetY() - b_.GetY()) / noda_; }
int64_t Line::GetB() const { return (-a_.GetX() + b_.GetX()) / noda_; }
int64_t Line::GetC() const {
  return (a_.GetX() * b_.GetY() - b_.GetX() * a_.GetY()) / noda_;
}
bool Line::ContainsPoint(const Point& k_second) const {
  return (((k_second - a_) ^ (k_second - b_)) == 0);
}
bool Line::CrossSegment(const Segment& k_second) const {
  if (ContainsPoint(k_second.GetA()) || ContainsPoint(k_second.GetB())) {
    return true;
  }
  if (k_second.ContainsPoint(a_) || k_second.ContainsPoint(b_)) {
    return true;
  }
  return (((b_ - a_) ^ (k_second.GetA() - a_)) *
              ((b_ - a_) ^ (k_second.GetB() - a_)) <=
          0);
}

void Line::Move(const Vector& arr) {
  a_.Move(arr);
  b_.Move(arr);
  noda_ = Noda(a_.GetY() - b_.GetY(),
               Noda(a_.GetX() - b_.GetX(),
                    a_.GetX() * b_.GetY() - b_.GetX() * a_.GetY()));
}
IShape* Line::Clone() const { return new Line(*this); }

Ray::Ray() {}
Ray::Ray(Point inda, Point indb) : a_(inda), b_(indb) {}
Point Ray::GetA() const { return a_; }
Vector Ray::GetVector() const { return b_ - a_; }
bool Ray::ContainsPoint(const Point& k_second) const {
  Vector vect;
  vect = b_ - a_;
  Vector add;
  add = k_second - a_;
  return ((vect ^ add) == 0 && (vect * add) >= 0);
}
bool Ray::CrossSegment(const Segment& k_second) const {
  if (ContainsPoint(k_second.GetA()) || ContainsPoint(k_second.GetB())) {
    return true;
  }
  if (k_second.ContainsPoint(a_) || k_second.ContainsPoint(b_)) {
    return true;
  }
  Line add(a_, b_);
  bool thefirst = add.CrossSegment(k_second);
  int64_t kofa = k_second.GetB().GetY() - k_second.GetA().GetY();
  int64_t kofb = k_second.GetB().GetX() - k_second.GetA().GetX();
  int64_t kofc = k_second.GetA().GetY() * k_second.GetB().GetX() -
                 k_second.GetA().GetX() * k_second.GetB().GetY();
  int64_t kofv = b_.GetX() - a_.GetX();
  int64_t kofw = b_.GetY() - a_.GetY();
  int64_t temp = (-kofa * a_.GetX() - kofb * a_.GetY() - kofc) *
                 (kofa * kofv + kofb * kofw);

  return (thefirst && temp > 0);
}

void Ray::Move(const Vector& arr) {
  a_.Move(arr);
  b_.Move(arr);
}

IShape* Ray::Clone() const { return new Ray(*this); }

Circle::Circle() {}
Circle::Circle(Point centre, size_t radius)
    : centre_(centre), radius_(radius) {}
Point Circle::GetCentre() const { return centre_; }
size_t Circle::GetRadius() const { return radius_; }
bool Circle::ContainsPoint(const Point& k_second) const {
  return (centre_.Distance(k_second) <= radius_ * radius_);
}

bool Circle::CrossSegment(const Segment& k_second) const {
  if (((k_second.GetA().Distance(centre_)) < radius_ * radius_) &&
      ((k_second.GetB().Distance(centre_)) < radius_ * radius_)) {
    return false;
  }
  Vector abvector;
  abvector = k_second.GetA() - k_second.GetB();
  Vector aovector;
  aovector = centre_ - k_second.GetA();
  if ((abvector ^ aovector) * (abvector ^ aovector) <=
      static_cast<int64_t>(radius_ * radius_ *
                           k_second.GetB().Distance(k_second.GetA()))) {
    return true;
  }
  return (((k_second.GetA().Distance(centre_)) <= radius_ * radius_) &&
              ((k_second.GetB().Distance(centre_)) >= radius_ * radius_) ||
          ((k_second.GetB().Distance(centre_)) <= radius_ * radius_) &&
              ((k_second.GetA().Distance(centre_)) >= radius_ * radius_));
}
void Circle::Move(const Vector& arr) { centre_.Move(arr); }
IShape* Circle::Clone() const { return new Circle(*this); }
