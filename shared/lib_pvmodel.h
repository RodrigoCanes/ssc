#ifndef __pvmodulemodel_h
#define __pvmodulemodel_h

#include <string>

class pvcelltemp_t;
class pvpower_t;

class pvinput_t
{
public:
	pvinput_t();
	pvinput_t( double ib, double id, double ig, 
		double ta, double td, double ws, double wd, double patm,
		double zen, double inc, 
		double elv, double tlt, double azi,
		double hrday );

	double Ibeam; // beam irradiance, W/m2
	double Idiff; // sky diffuse irradiance, W/m2
	double Ignd; // ground reflected irradiance, W/m2
	double Tdry; // dry bulb temp, C
	double Tdew; // dew point temp, C
	double Wspd; // wind speed, m/s
	double Wdir; // wind direction, deg +from north
	double Patm; // atmospheric pressure, millibar
	double Zenith; // zenith angle, deg
	double IncAng; // incidence angle on surface, deg
	double Elev; // site elevation, m
	double Tilt; // surface tilt angle, deg +from horizontal
	double Azimuth; // surface azimuth angle, deg +from north (E=90,S=180)
	double HourOfDay; // hour of the day 0=12am, 23=11pm
};

class pvoutput_t
{
public:
	pvoutput_t();
	pvoutput_t( double p, double v,
		double c, double e, 
		double voc, double isc, double t );

	double Power; // output power, Watts
	double Voltage; // operating voltage, V
	double Current; // operating current, A
	double Efficiency; // operating efficiency, fraction (0..1)
	double Voc_oper; // open circuit voltage at operating condition, V
	double Isc_oper; // short circuit current at operating condition, A
	double CellTemp; // cell temperature, 'C
};

class pvmodule_t; // forward decl

class pvcelltemp_t
{
protected:
	std::string m_err;
public:
	
	virtual bool operator() ( pvinput_t &input, pvmodule_t &module, double opvoltage, double &Tcell ) = 0;
	std::string error();
};

class pvmodule_t
{
protected:
	std::string m_err;
public:

	virtual double AreaRef() = 0;
	virtual double VmpRef() = 0;
	virtual double ImpRef() = 0;
	virtual double VocRef() = 0;
	virtual double IscRef() = 0;

	virtual bool operator() ( pvinput_t &input, double TcellC, double opvoltage, pvoutput_t &output ) = 0;
	std::string error();
};



class spe_module_t : public pvmodule_t
{
public:
	double Area; // m2
	double Gamma; // temp coefficient %/'C
	int Reference; // specification of reference condition.  valid values: 0..4
	double fd; // diffuse fraction
	double Eff[5]; // as fractions
	double Rad[5]; // W/m2

	spe_module_t( );	
	static double eff_interpolate( double irrad, double rad[5], double eff[5] );
	
	double WattsStc() { return Eff[Reference] * Rad[Reference] * Area; }

	virtual double AreaRef() { return Area; }
	virtual double VmpRef() { return 30; }
	virtual double ImpRef() { return WattsStc()/VmpRef(); }
	virtual double VocRef() { return 36; }
	virtual double IscRef() { return ImpRef()*1.3; }
	virtual bool operator() ( pvinput_t &input, double TcellC, double opvoltage, pvoutput_t &output);
};


#endif