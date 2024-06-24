#include <iostream>
#include <memory>
#include <cmath>

class Figure {
protected:
    int sides;
    bool valid;
    Figure(int sides) : sides(sides), valid(true) {}

public:
    virtual ~Figure() = default;

    virtual void print_info() const = 0;
    virtual bool isValid() const = 0;

    int getSides() const {
        return sides;
    }

    virtual void validate() = 0;
};

class Triangle : public Figure {
protected:
    double a, b, c;
    double A, B, C;

    Triangle(double a, double b, double c, double A, double B, double C)
        : Figure(3), a(a), b(b), c(c), A(A), B(B), C(C) {
        validate();
    }

public:
    static std::unique_ptr<Triangle> create(double a, double b, double c, double A, double B, double C) {
        return std::unique_ptr<Triangle>(new Triangle(a, b, c, A, B, C));
    }

    void validate() override {
        if (std::abs(A + B + C - 180) > 1e-5) {
            valid = false;
        }
    }

    bool isValid() const override {
        return valid;
    }

    void print_info() const override {
        std::cout << "Треугольник:\n" << (isValid() ? "Правильная" : "Неправильная") << "\n"
            << "Количество сторон: " << sides << "\n"
            << "Стороны: a=" << a << " b=" << b << " c=" << c << "\n"
            << "Углы: A=" << A << " B=" << B << " C=" << C << std::endl;
    }
};

class RightTriangle : public Triangle {
    RightTriangle(double a, double b, double c, double A, double B)
        : Triangle(a, b, c, A, B, 90) {
        validate();
    }

public:
    static std::unique_ptr<RightTriangle> create(double a, double b, double c, double A, double B) {
        return std::unique_ptr<RightTriangle>(new RightTriangle(a, b, c, A, B));
    }

    void validate() override {
        if (std::abs(C - 90) > 1e-5 || std::abs(A + B - 90) > 1e-5) {
            valid = false;
        }
    }
};

class IsoscelesTriangle : public Triangle {
    IsoscelesTriangle(double a, double b, double A, double B)
        : Triangle(a, b, a, A, B, A) {
        validate();
    }

public:
    static std::unique_ptr<IsoscelesTriangle> create(double a, double b, double A, double B) {
        return std::unique_ptr<IsoscelesTriangle>(new IsoscelesTriangle(a, b, A, B));
    }

    void validate() override {
        if (a != c || std::abs(A - C) > 1e-5) {
            valid = false;
        }
    }
};

class EquilateralTriangle : public Triangle {
    EquilateralTriangle(double side)
        : Triangle(side, side, side, 60, 60, 60) {
        validate();
    }

public:
    static std::unique_ptr<EquilateralTriangle> create(double side) {
        return std::unique_ptr<EquilateralTriangle>(new EquilateralTriangle(side));
    }

    void validate() override {
        if (a != b || b != c || std::abs(A - 60) > 1e-5 || std::abs(B - 60) > 1e-5 || std::abs(C - 60) > 1e-5) {
            valid = false;
        }
    }
};

class Quadrilateral : public Figure {
protected:
    double a, b, c, d;
    double A, B, C, D;

    Quadrilateral(double a, double b, double c, double d, double A, double B, double C, double D)
        : Figure(4), a(a), b(b), c(c), d(d), A(A), B(B), C(C), D(D) {
        validate();
    }

public:
    static std::unique_ptr<Quadrilateral> create(double a, double b, double c, double d, double A, double B, double C, double D) {
        return std::unique_ptr<Quadrilateral>(new Quadrilateral(a, b, c, d, A, B, C, D));
    }

    void validate() override {
        if (std::abs(A + B + C + D - 360) > 1e-5) {
            valid = false;
        }
    }

    bool isValid() const override {
        return valid;
    }

    void print_info() const override {
        std::cout << "Четырёхугольник:\n" << (isValid() ? "Правильная" : "Неправильная") << "\n"
            << "Количество сторон: " << sides << "\n"
            << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << "\n"
            << "Углы: A=" << A << " B=" << B << " C=" << C << " D=" << D << std::endl;
    }
};

class Rectangle : public Quadrilateral {
    Rectangle(double a, double b)
        : Quadrilateral(a, b, a, b, 90, 90, 90, 90) {
        validate();
    }

public:
    static std::unique_ptr<Rectangle> create(double a, double b) {
        return std::unique_ptr<Rectangle>(new Rectangle(a, b));
    }

    void validate() override {
        if (a != c || b != d || std::abs(A - 90) > 1e-5 || std::abs(B - 90) > 1e-5 || std::abs(C - 90) > 1e-5 || std::abs(D - 90) > 1e-5) {
            valid = false;
        }
    }
};

class Square : public Quadrilateral {
    Square(double side)
        : Quadrilateral(side, side, side, side, 90, 90, 90, 90) {
        validate();
    }

public:
    static std::unique_ptr<Square> create(double side) {
        return std::unique_ptr<Square>(new Square(side));
    }

    void validate() override {
        if (a != b || b != c || c != d || std::abs(A - 90) > 1e-5 || std::abs(B - 90) > 1e-5 || std::abs(C - 90) > 1e-5 || std::abs(D - 90) > 1e-5) {
            valid = false;
        }
    }
};

class Parallelogram : public Quadrilateral {
    Parallelogram(double a, double b, double A, double B)
        : Quadrilateral(a, b, a, b, A, B, A, B) {
        validate();
    }

public:
    static std::unique_ptr<Parallelogram> create(double a, double b, double A, double B) {
        return std::unique_ptr<Parallelogram>(new Parallelogram(a, b, A, B));
    }

    void validate() override {
        if (a != c || b != d || std::abs(A - C) > 1e-5 || std::abs(B - D) > 1e-5) {
            valid = false;
        }
    }
};

class Rhombus : public Quadrilateral {
    Rhombus(double side, double A, double B)
        : Quadrilateral(side, side, side, side, A, B, A, B) {
        validate();
    }

public:
    static std::unique_ptr<Rhombus> create(double side, double A, double B) {
        return std::unique_ptr<Rhombus>(new Rhombus(side, A, B));
    }

    void validate() override {
        if (a != b || b != c || c != d || std::abs(A - C) > 1e-5 || std::abs(B - D) > 1e-5) {
            valid = false;
        }
    }
};

void print_info(Figure* figure) {
    figure->print_info();
}

int main() {
    setlocale(LC_ALL, "");
    auto triangle = Triangle::create(10, 20, 30, 50, 60, 70);
    auto rightTriangleInvalid = RightTriangle::create(10, 20, 30, 50, 60);
    auto rightTriangleValid = RightTriangle::create(10, 20, 30, 50, 40);
    auto isoscelesTriangle = IsoscelesTriangle::create(10, 20, 50, 60);
    auto equilateralTriangle = EquilateralTriangle::create(30);
    auto quadrilateral = Quadrilateral::create(10, 20, 30, 40, 50, 60, 70, 80);
    auto rectangle = Rectangle::create(10, 20);
    auto square = Square::create(20);
    auto parallelogram = Parallelogram::create(20, 30, 30, 40);
    auto rhombus = Rhombus::create(30, 30, 40);

    std::cout << "Информация о фигурах:" << std::endl;
    print_info(triangle.get());
    print_info(rightTriangleInvalid.get());
    print_info(rightTriangleValid.get());
    print_info(isoscelesTriangle.get());
    print_info(equilateralTriangle.get());
    print_info(quadrilateral.get());
    print_info(rectangle.get());
    print_info(square.get());
    print_info(parallelogram.get());
    print_info(rhombus.get());

    return 0;
}