# Geometry
В данном проекте реализован набор классов для решения геометрических задач на плоскости. Все координаты предполагаются целочисленными.

## Класс Vector 
Для вектора на плоскости реализованы следующие методы и перегружены соответствующие операторы:
 * Конструктор по умолчанию (создает нулевой вектор)
 * Конструктор от двух целочисленных переменных (создает вектор с соответствующими координатами)
 * Оператор * для скалярного произведения
 * Оператор ^ для векторного произведения
 * Операторы сложения/разности с другим вектором, соответственно операторы += и -=
 * Оператор умножения на число (допустимы как умножение вектора на число, так и числа на вектор), реализован оператор *=
 * Унарный оператор минус для получения вектора в противоположном направлении
 * Методы GetX() и GetY() для получения соответствующих координат

 ## Набор классов - фигур, которые наследуются от абстрактного класса IShape для работы с двумерными примитивами:

 * Point или точка (создается из двух координат типа int64_t)
 * Segment или отрезок (создается из двух Point)
 * Line или прямая (создается из двух Point)
 * Ray или луч (создается из двух Point)
 * Circle или окружность (создается из Point и радиуса типа size_t)


В каждом классе реализованы геттеры:
 * Point: GetX, GetY (координаты)
 * Segment: GetA, GetB (начало, конец отрезка)
 * Line: GetA, GetB, GetC, где a, b, c - это коэффициенты уравнения прямой ax + by + c с точностью до множителя (то есть 10x + 20y + 30 это тоже самое что 5x + 10y + 15)
 * Ray: GetA - точка начала и GetVector - направляющий вектор
 * Circle: GetCentre и GetRadius

В базовом классе реализованы следующие методы:
 * void Move(const Vector&) - сдвиг фигуры на соответствующий вектор
 * bool ContainsPoint(const Point&) - проверка, содержит ли фигура точку
 * bool CrossSegment(const Segment&) - проверка, пересекает ли отрезок фигуру
 * IShape* Clone() - вернуть указатель на копию фигуры

В производных классах необходимо реализовать эти методы.
