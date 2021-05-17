#ifndef __QUATERNION_H
#define __QUATERNION_H

class Quaternion{
	public:
		Quaternion(double right_ascension, double declination, double radius = 1.0L);
		// performs spherical transformations
		int rotate();
		// tansforms equatorial coordinates to cartesian coodinates
		int polar2cartesian();
		int polar2cartesian_axis(double axis, double theta);
		// tansforms cartesian coordinates to equatorial coodinates
		int cartesian2polar(int equatorial);
		// create a transformation vector
		int create_rotate_vector(double axis, double theta, int a);
		double getRightAscension()
		{
			return spherical_coordinates[0];
		}
		double getDeclination()
		{
			return spherical_coordinates[1];
		}

		void getVector(double v[4])
		{
			for(int i = 0; i < 4; i++)
				v[i] = vec[i];
		}
	private:
		double radius;
		double vec[4];
		double cvec[4];
		double spherical_coordinates[2];

};


#endif
