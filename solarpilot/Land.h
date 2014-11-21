#ifndef _LAND_H_
#define _LAND_H_ 1

#include "math.h"
#include <vector>
#include "mod_base.h"
using namespace std;


struct landnode
{
	int node_id;
	Point point;
	vector<int> links;
};

class Land : public mod_base
{
	double
		_max_scaled_rad,	//_bound_type = 1
		_min_scaled_rad,	//_bound_type = 1
		_max_fixed_rad,		//_bound_type = 2
		_min_fixed_rad,		//_bound_type = 2
		_land_max_opt_max,
		_land_max_opt_min;
	
	double 
		_bound_area;	//land area inside the bounding box around the heliostat positions
	
	bool 
		_is_bounds_scaled,		//Land boundary scales with tower hight value
		_is_bounds_fixed,		//Land boundary has fixed limits (not more than | not less than)
		_is_bounds_array,		//Land boundaries is specified by points array
		_is_land_max_opt,
		_is_land_max_restrict;

	vector<Point> 
		_topo_grid;	//Grid with regularly spaced x-y points describing the topology in the z direction
	vector<Point>
		_layout_positions;	//list of heliostat positions -- used to calculate land area
	bounds_array		//--- vector<vector<double> > ----
		_inclusions,	//Vector of land inclusion maps
		_exclusions;	//Vector of exclusion maps 

 public:
	 Land (){}; 
	 ~Land (){};
	void Create( var_map &V );
	void Clean();

	void getExtents(double rval[], var_set &V);
	void getExtents(double rval[], double tht=1.);
	void getRadialExtents(double rval[2], double tht=1.);
	bounds_array *getInclusions();
	bounds_array *getExclusions();
	vector<Point> *getLayoutPositions();
	double getLandArea();
	double calcPolyLandArea();
	
	void calcLandArea();
	void setLayoutPositions(vector<Point> &layout, bool dolandcalc = true);

	bool isBoundsScaled();
	void isBoundsScaled(bool &val);
	bool isBoundsFixed();
	void isBoundsFixed(bool &val);
	bool isBoundsArray();
	void isBoundsArray(bool &val);
	
	
	//methods for containment testing
	bool InBounds(Point &H, double tht=1.0);

 } ;

#endif