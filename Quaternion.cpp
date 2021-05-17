#include<iostream>
#include<cmath>
#include<string>
#include"Quaternion.h"

Quaternion::Quaternion(double right_ascension, double declination, double radius)
{
	for(int i = 0; i < 4; i++)
	{
		vec[i]  = 0.0L;
		cvec[i] = 0.0L;
	}
	this->radius = radius;
	this->spherical_coordinates[0] = right_ascension;
	this->spherical_coordinates[1] = declination;
	polar2cartesian();
}

int Quaternion::create_rotate_vector(double axis, double theta, int a)
{
	if(a)
		polar2cartesian_axis(axis, 0.0L);
	else
		polar2cartesian_axis(0.0L, axis);
	this->cvec[0] = cos( theta / 2.0L);
	for(int i = 1; i < 4; i++)
		this->cvec[i] = sin( theta / 2.0L) * this->cvec[i];

	return EXIT_SUCCESS;
}

int Quaternion::rotate()
{
	double signs[4][4] = {{1.0L, -1.0L, -1.0L, -1.0L},
				{1.0L, 1.0L, -1.0L, 1.0L},
				{1.0L, 1.0L, 1.0L, -1.0L},
				{1.0L, -1.0L, 1.0L, 1.0L}};
	int values[4][4] = 	{{0, 1, 2, 3},
				{1, 0, 3, 2},
				{2, 3, 0, 1},
				{3, 2, 1, 0}};

	double quaterniontmp[4] = {0.0L};

	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			quaterniontmp[i] +=  this->cvec[values[i][j]] * this->vec[j] * signs[i][j];
	
	for(int i = 1; i < 4; i++)
		this->cvec[i] = -this->cvec[i];

	for(int i = 0; i < 4; i++)
	{
		this->vec[i] = 0.0L;
		for(int j = 0; j < 4; j++)
			this->vec[i] += quaterniontmp[values[i][j]] * this->cvec[j] * signs[i][j];
	}

	return EXIT_SUCCESS;
}

int Quaternion::polar2cartesian_axis(double axis, double theta)
{
	this->cvec[0] = 0.0L;
	this->cvec[1] = cos(axis)*cos(theta);
	this->cvec[2] = sin(axis)*cos(theta);
	this->cvec[3] = sin(theta);

	return EXIT_SUCCESS;
}

int Quaternion::polar2cartesian()
{
	this->vec[0] = radius;
	this->vec[1] = radius * cos(this->spherical_coordinates[0])*cos(this->spherical_coordinates[1]);
	this->vec[2] = radius * sin(this->spherical_coordinates[0])*cos(this->spherical_coordinates[1]);
	this->vec[3] = radius * sin(this->spherical_coordinates[1]);

	return EXIT_SUCCESS;
}

int Quaternion::cartesian2polar(int equatorial)
{
	double r = 0.0L;
	r = sqrt(pow(this->vec[1], 2) + pow(this->vec[2],2) + pow(this->vec[3],2));
	this->spherical_coordinates[1] = acos(this->vec[3] / r);
	this->spherical_coordinates[0] = atan2(this->vec[2], this->vec[1]);
	if(equatorial)
		this->spherical_coordinates[1] = M_PI / 2.0L - this->spherical_coordinates[1];

	return EXIT_SUCCESS;
}

