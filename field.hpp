/*
 * field.hpp
 *
 * Contains game field information
 */

#ifndef _FIELD_HPP_
#define _FIELD_HPP_

class Field {
public:
	//Exposed Constants
	static const int defaultXSize = 51;
	static const int defaultYSize = 21;
	static const int defaultXScale = 2;

	//Constructors
	Field();
	Field(int, int);
	Field(int, int, int);

	//Getters
	int getXSize() const;
	int getYSize() const;
	int getXScale() const;

	//Setters
	void setXSize(int);
	void setYSize(int);
	void setXScale(int);

private:
	int xSize;
	int ySize;
	int xScale;
};

#endif
