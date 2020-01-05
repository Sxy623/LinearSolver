#ifndef ROW_H
#define ROW_H

class Row {
public:
    Row();

    Row(int size, double *data);

    double &operator[](int index);

    double operator[](int index) const;

    void addRow(Row &another, double ratio);

    void multi(double ratio);

    void printPolynomial();

private:
    int size;
    double *data;
};

#endif