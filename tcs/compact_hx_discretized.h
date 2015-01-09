#ifndef __compact_hx_dis_
#define __compact_hx_dis_

#include <limits>
#include "htf_props.h"

/* 8.3.14 twn: The goal here is to model a multi-pass cross-flow air-cooler. Model is discretized
to account for varying properties of carbon dioxide around the critical.
Design Parameters:
	* Compact HX Config: Names correspond to work by Gavic, who used EES, which references Kays and London
	* Completely define hot stream: inlet/outlet temps, mass flow and/or heat rejection
	* Ambient air temperature
	* Number of passes
	* Tube thickness
	* Fan efficiency
	* *** Model converges design to hit following targets *** *
	* Hot side pressure drop
	* Fan power
*/

using namespace std;

//config$ = 'fc_tubes_s80_38T'

enum compact_hx_configs
{
	fc_tubes_s80_38T = 1,
	fc_tubes_sCF_88_10Jb
};

bool get_compact_hx_geom(int enum_compact_hx_config, double & d_out, double & fin_pitch, double & D_h,
	double & fin_thk, double & sigma, double & alpha, double & A_fin_to_surf,
	double & s_h, double & s_v, double & fin_V_per_m);

bool get_compact_hx_f_j(int enum_compact_hx_config, double Re, double & f, double & j_H);

class compact_hx
{

public:
	struct S_hx_design_solved
	{
		double m_material_V;	//[m^3]		Total Material volume - no headers

		S_hx_design_solved()
		{
			m_material_V = numeric_limits<double>::quiet_NaN();
		}
	};

private:

	// Classes
	HTFProperties mc_air;				// Instance of HTFProperties class for ambient air

	// Remaining Air-Cooler Specs
		// Inputs
	int m_N_loops;
	int m_N_nodes;
	double m_th;			//[m]
	double m_eta_fan;		//[-]
	double m_roughness;		//[m]
		// Calculated
	double m_d_in;			//[m]
	double m_A_cs;			//[m^2]
	double m_relRough;		//[-]
	double m_Depth;			//[m]		Dimension in loop/air flow direction
	double m_W_par;			//[m]		Dimension of parallel flow paths
	double m_N_par;			//[-]		Number of parallel flow paths
	double m_N_tubes;		//[-]		Number of tubes
	double m_L_tube;		//[m]		Tube length
	double m_L_path;		//[m]		Total flow path length
	double m_A_surf_total;	//[m^2]		Total air-side surface area
	double m_UA_total;		//[W/K]		Total air-side conductance at design
	double m_V_total;		//[m^3]		Total HX volume
	double m_material_V;	//[m^3]		Total Material volume - no headers
	double m_A_surf_node;	//[m^2]

	// Design Ambient Conditions
	double m_T_amb_des;		//[K]
	double m_P_amb_des;		//[Pa]

	// Hot-side Inlet Conditions
	double m_T_hot_in_des;		//[K]
	double m_P_hot_in_des;		//[kPa]
	double m_m_dot_total;		//[kg/s] Total sCO2 mass flow into air-cooler

	// Design Performance Targets
	double m_W_dot_fan_des;		//[MW]
	double m_delta_P_des;		//[kPa]
	double m_T_hot_out_des;		//[K]
	double m_m_dot_air_des;		//[kg/s]
	double m_Q_dot_des;			//[W]

	// Calculated Performance Target
	double m_P_hot_out_des;		//[kPa]

	// HX geometry
		// Input
	int m_enum_compact_hx_config;
		// Defined from Config
	double m_d_out;		//[m]
	double m_fin_pitch;	//[1/m]
	double m_D_h;		//[m]
	double m_fin_thk;	//[m]
	double m_sigma;		//[-]
	double m_alpha;		//[1/m]
	double m_A_fin_to_surf;	//[-]
	double m_s_h;		//[m]
	double m_s_v;		//[m]
	double m_fin_V_per_m;	//[1/m]

	int m_final_outlet_index;

	// Structures
	S_hx_design_solved m_hx_design_solved;

public:	

	compact_hx();

	~compact_hx(){};

	bool design_hx(double T_amb_K, double P_amb_Pa, double T_hot_in_K, double P_hot_in_kPa, 
		double m_dot_hot_kg_s, double W_dot_fan_MW, double deltaP_kPa, double T_hot_out_K);

	void off_design_hx(double T_amb_K, double P_amb_Pa, double T_hot_in_K, double P_hot_in_kPa,
		double m_dot_hot_kg_s, double T_hot_out_K, double & W_dot_fan_MW, int & error_code);

	const S_hx_design_solved * get_hx_design_solved()
	{
		m_hx_design_solved.m_material_V = m_material_V;

		return &m_hx_design_solved;
	}

};



#endif