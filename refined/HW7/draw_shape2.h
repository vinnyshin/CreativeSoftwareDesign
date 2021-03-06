#include <iostream>
#include <vector>

using namespace std;

class Canvas
{
public:
    Canvas(size_t row, size_t col);
    ~Canvas();

    // canvas 크기를 row * col 로 변경한다. 그려진 내용은 보존한다.
    void Resize(size_t row, size_t col);

    // (x, y) 위치에 문자를 그린다. 범위 밖의 x, y는 무시한다.
    bool Draw(int x, int y, char brush);

    // 그려진 내용을 모두 지운다. (‘.’으로 초기화)
    void Clear();

private:
    // 그려진 모양을 저장할 수 있도록 데이터멤버를 정의 (resize 가능에 주의)
    friend ostream &operator<<(ostream &os, const Canvas &c);
    vector<vector<char> > map_;
    size_t row_, col_;
};

class Shape
{
public:
    Shape();
    virtual ~Shape() {};
    virtual void Draw(Canvas *canvas) const = 0;

    string type() const { return type_; }
    int x() const { return x_; }
    int y() const { return y_; }
    int h() const { return h_; }
    int w() const { return w_; }
    char brush() const { return brush_; }

protected:
    string type_;
    int x_, y_, h_, w_;
    char brush_;
    // 도형의 공통 속성 정의
};

class Rectangle : public Shape
{
public:
    Rectangle() { type_ = "rect"; }
    virtual ~Rectangle() {}
    virtual void Draw(Canvas *canvas) const;

private:
    friend istream &operator>>(istream &is, Rectangle &r);
};

class UpTriangle : public Shape
{
public:
    UpTriangle() { type_ = "tri_up"; }
    virtual ~UpTriangle() {}
    virtual void Draw(Canvas *canvas) const;

private:
    friend istream &operator>>(istream &is, UpTriangle &t);
};

class DownTriangle : public Shape
{
public:
    DownTriangle() { type_ = "try_down"; }
    virtual ~DownTriangle() {}
    virtual void Draw(Canvas *canvas) const;

private:
    friend istream &operator>>(istream &is, DownTriangle &d);
};

class Diamond : public Shape
{
public:
    Diamond() { type_ = "diamond"; }
    virtual ~Diamond() {}
    virtual void Draw(Canvas *canvas) const;

private:
    friend istream &operator>>(istream &is, Diamond &dm);
};

istream &operator>>(istream &is, Rectangle &r);
istream &operator>>(istream &is, UpTriangle &t);
istream &operator>>(istream &is, DownTriangle &d);
istream &operator>>(istream &is, Diamond &dm);

ostream &operator<<(ostream &os, const Canvas &c);