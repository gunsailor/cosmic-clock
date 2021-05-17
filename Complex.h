#ifndef __COMPLEX_H
#define __COMPLEX_H


class Complex{

	public:
		Complex();
		Complex(double a, double b, bool cartesian = true);
		int add(Complex a, Complex b);
		int subs(Complex a, Complex b);
		int mul(Complex a, Complex b);
		int conjug(Complex a);
		int power(Complex a, int m);
		int rotate(Complex a, double phi);
		int radius_change(Complex a, double i);
		double getPosX()
		{
			return a;
		}
		double getPosY()
		{
			return b;
		}
	private:
		double a;
		double b;
		double cos;
		double sin;
		double theta;
		double radius;

};
#endif
