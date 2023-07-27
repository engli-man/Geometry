#include <cmath>
#include <iostream>
#include <numeric>
class Vector {
 public:
  Vector();
  Vector(int64_t indx, int64_t indy);
  int64_t operator*(Vector second) const;
  int64_t operator^(Vector second) const;
  friend Vector operator+(Vector first, Vector second);
  friend Vector operator-(Vector first, Vector second);
  Vector& operator+=(Vector second);
  Vector& operator-=(Vector second);
  friend Vector operator*(Vector first, int64_t digit);
  friend Vector operator*(int64_t digit, Vector first);
  Vector& operator-();
  int64_t GetX() const;
  int64_t GetY() const;

 private:
  int64_t x_ = 0;
  int64_t y_ = 0;
};

class Point;
class Segment;

class IShape {
 public:
  virtual bool ContainsPoint(const Point& k_second) const = 0;
  virtual bool CrossSegment(const Segment& k_second) const = 0;
  virtual void Move(const Vector& arr) = 0;
  virtual IShape* Clone() const = 0;
  virtual ~IShape() = default;
};

class Point : public IShape {
 public:
  Point();
  Point(int64_t indx, int64_t indy);
  int64_t GetX() const;
  int64_t GetY() const;

  bool ContainsPoint(const Point& k_second) const;
  size_t Distance(const Point& k_second) const;
  friend Vector operator-(const Point& k_first, const Point& k_second);

  bool CrossSegment(const Segment& k_second) const;

  void Move(const Vector& arr);
  IShape* Clone() const;

 private:
  int64_t x_ = 0;
  int64_t y_ = 0;
};

class Segment : public IShape {
 public:
  Segment();
  Segment(Point inda, Point indb);
  Point GetA() const;
  Point GetB() const;
  bool ContainsPoint(const Point& k_second) const;
  bool CrossSegment(const Segment& k_second) const;

  void Move(const Vector& arr);
  IShape* Clone() const;

 private:
  Point a_;
  Point b_;
};

static int64_t Noda(int64_t arr, int64_t brr) { return std::gcd(arr, brr); }

class Line : public IShape {
 public:
  Line();
  Line(Point inda, Point indb);
  int64_t GetA() const;
  int64_t GetB() const;
  int64_t GetC() const;
  bool ContainsPoint(const Point& k_second) const;
  bool CrossSegment(const Segment& k_second) const;
  void Move(const Vector& arr);
  IShape* Clone() const;

 private:
  Point a_;
  Point b_;
  int64_t noda_ = Noda(a_.GetY() - b_.GetY(),
                       Noda(a_.GetX() - b_.GetX(),
                            a_.GetX() * b_.GetY() - b_.GetX() * a_.GetY()));
};

class Ray : public IShape {
 public:
  Ray();
  Ray(Point inda, Point indb);
  Point GetA() const;
  Vector GetVector() const;
  bool ContainsPoint(const Point& k_second) const;
  bool CrossSegment(const Segment& k_second) const;
  void Move(const Vector& arr);
  IShape* Clone() const;

 private:
  Point a_;
  Point b_;
};

class Circle : public IShape {
 public:
  Circle();
  Circle(Point centre, size_t radius);
  Point GetCentre() const;
  size_t GetRadius() const;
  bool ContainsPoint(const Point& k_second) const;
  bool CrossSegment(const Segment& k_second) const;
  void Move(const Vector& arr);
  IShape* Clone() const;

 private:
  Point centre_;
  size_t radius_;
};
