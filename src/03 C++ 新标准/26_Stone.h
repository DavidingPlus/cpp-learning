#ifndef _STONE_H_
#define _STONE_H_

class Stone {
private:
    double _length;
    double _width;
    double _height;
    double _weight;

public:
    Stone() = default;
    Stone(const double &length, const double &width, const double &height, const double &weight) : _length(length), _width(width), _height(height), _weight(weight) {}

    // copy-asgn
    Stone &operator=(const Stone &sto) {
        if (this != &sto) {
            _length = sto.getLen();
            _width = sto.getWei();
            _height = sto.getHei();
            _weight = sto.getWei();
        }
        return *this;
    }

    // copy-ctor
    Stone(const Stone &sto) { *this = sto; }

    double getLen() const { return _length; }
    double getWid() const { return _width; }
    double getHei() const { return _height; }
    double getWei() const { return _weight; }

    void setLen(const double &length) { _length = length; }
    void setWid(const double &width) { _width = width; }
    void setHei(const double &height) { _height = height; }
    void setWei(const double &weight) { _weight = weight; }
};

#endif
