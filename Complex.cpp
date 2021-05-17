#include<iostream>
#include<cmath>
#include<string>
#include"Complex.h"

Complex::Complex()
{
}
Complex::Complex(double c, double d, bool cartesian)
{
	if(cartesian)
	{
		this->a = c;
		this->b = d;
		this->radius = sqrt(pow(a,2)+pow(b,2));
		this->cos = a / this->radius;
		this->sin = b / this->radius;
		this->theta = atan2l(this->sin, this->cos);
	}else{
		theta = c;
		radius = d;
		cos = cosl(c);
		sin = sinl(c);
		a = radius * cos;
		b = radius * sin;	
	}
}

int Complex::add(Complex a, Complex b)
{
	this->radius = sqrt(pow(a.a + b.a, 2) + pow(a.b + b.b, 2));
	this->cos = (a.a + b.a) / this->radius;
	this->sin = (a.b + b.b) / this->radius;
	this->theta = atan2l(this->sin, this->cos);
	this->a = this->radius * this->cos;
	this->b = this->radius * this->sin;

	return EXIT_SUCCESS;
}

int Complex::subs(Complex a, Complex b)
{
	this->radius = sqrt(pow(a.a - b.a, 2) + pow(a.b - b.b, 2));
	this->cos = (a.a - b.a) / this->radius;
	this->sin = (a.b - b.b) / this->radius;
	this->theta = atan2l(this->sin, this->cos);
	this->a = this->radius * this->cos;
	this->b = this->radius * this->sin;

	return EXIT_SUCCESS;
}

int Complex::mul(Complex a, Complex b)
{
	this->cos = (a.cos * b.cos - a.sin * b.sin);
	this->sin = (a.sin * b.cos + b.sin * a.cos);
	this->radius = a.radius * b.radius;
	this->theta = a.theta + b.theta;
	this->a = this->radius * this->cos;
	this->b = this->radius * this->sin;

	return EXIT_SUCCESS;
}

int Complex::conjug(Complex a)
{
	this->cos = a.cos;
	this->sin = - a.sin;
	this->theta = - a.theta;
	this->b = -a.b;
	this->a = a.a;
	this->radius = a.radius;

	return EXIT_SUCCESS;
}

int Complex::power(Complex a, int m)
{
	this->theta = m * a.theta;
	this->cos = cosl(m * a.theta);
	this->sin = sinl(m * a.theta);
	this->radius = pow(a.radius, m);
	this->a = this->radius * this->cos;
	this->b = this->radius * this->sin;

	return EXIT_SUCCESS;
}

int Complex::rotate(Complex a, double phi)
{
	Complex d;
	d.theta = phi;
	d.radius = 1.0L;
	d.cos = cosl(phi);
	d.sin = sinl(phi);
	d.a = d.cos;
	d.b = d.sin;
	subs((*this), a);
	mul(d, (*this));
	add(a, (*this));

	return EXIT_SUCCESS;
}

int Complex::radius_change(Complex a, double i)
{
	this->a = this->a + (this->a - a.a) / i;
	this->b = this->b + (this->b - a.b) / i;
	this->radius = sqrt(pow(this->a,2)+pow(this->b,2));
	this->cos = this->a / this->radius;
	this->sin = this->b / this->radius;
	this->theta = atan2l(this->sin, this->cos);
	return EXIT_SUCCESS;
}
