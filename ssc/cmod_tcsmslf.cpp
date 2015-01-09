#include "core.h"
#include "tckernel.h"
#include "common.h"

static var_info _cm_vtab_tcsmslf[] = {
/*	EXAMPLE LINES FOR INPUTS
    { SSC_INPUT,        SSC_NUMBER,      "XXXXXXXXXXXXXX",    "Label",                                                                               "",              "",            "sca",            "*",                       "",                      "" },
    { SSC_INPUT,        SSC_NUMBER,      "INTINTINTINT",      "Label",                                                                               "",              "",            "parasitic",      "*",                       "INTEGER",               "" },
    { SSC_INPUT,        SSC_ARRAY,       "XXXXXXXXXXX",       "Number indicating the receiver type",                                                 "",              "",            "hce",            "*",                       "",                      "" },
    { SSC_INPUT,        SSC_MATRIX,      "XXXXXXXXXXX",       "Label",                                                                               "",              "",            "tes",            "*",                       "",                      "" },
*/

//    VARTYPE           DATATYPE          NAME                 LABEL                                                                                 UNITS            META            GROUP            REQUIRED_IF                 CONSTRAINTS             UI_HINTS
    { SSC_INPUT,        SSC_STRING,      "file_name",         "local weather file path",                                                             "",              "",            "Weather",        "*",                       "LOCAL_FILE",            "" },
    { SSC_INPUT,        SSC_NUMBER,      "track_mode",        "Tracking mode",                                                                       "",              "",            "Weather",        "*",                       "",                      "" },
    { SSC_INPUT,        SSC_NUMBER,      "tilt",              "Tilt angle of surface/axis",                                                          "",              "",            "Weather",        "*",                       "",                      "" },
    { SSC_INPUT,        SSC_NUMBER,      "azimuth",           "Azimuth angle of surface/axis",                                                       "",              "",            "Weather",        "*",                       "",                      "" },
	{ SSC_INPUT, SSC_NUMBER, "system_capacity", "Nameplate capacity", "kW", "", "mslf", "*", "", "" },

    // TOU
    { SSC_INPUT,        SSC_MATRIX,      "weekday_schedule",  "12x24 Time of Use Values for week days",                                              "",             "",             "tou_translator", "*",                       "",                      "" }, 
    { SSC_INPUT,        SSC_MATRIX,      "weekend_schedule",  "12x24 Time of Use Values for week end days",                                          "",             "",             "tou_translator", "*",                       "",                      "" }, 

	// Type 262 (solar field collector) parameters
	{ SSC_INPUT,	SSC_NUMBER, "nMod", "Number of collector modules in a loop", "", "", "controller", "*", "INTEGER", "" },
	{ SSC_INPUT,	SSC_NUMBER, "nRecVar", "Number of receiver variantions", "", "", "controller", "?=4", "INTEGER", "" },
	{ SSC_INPUT,	SSC_NUMBER, "nLoops", "Number of loops in the field", "", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "eta_pump", "HTF pump efficiency", "", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "HDR_rough", "Header pipe roughness", "m", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "theta_stow", "stow angle", "deg", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "theta_dep", "deploy angle", "deg", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "FieldConfig", "Number of subfield headers", "", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "T_startup", "The required temperature of the system before the power block can be switched on", "C", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "pb_rated_cap", "Rated plant capacity", "MWe", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "m_dot_htfmin", "Minimum loop HTF flow rate", "kg/s", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "m_dot_htfmax", "Maximum loop HTF flow rate", "kg/s", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "T_loop_in_des", "Design loop inlet temperature", "C", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "T_loop_out", "Target loop outlet temperature", "C", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "Fluid", "Field HTF fluid number", "", "", "controller", "*", "INTEGER", "" },
	{ SSC_INPUT, SSC_NUMBER, "T_field_ini", "Initial field temperature", "C", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_MATRIX, "HTF_data", "Fluid property data", "", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "T_fp", "Freeze protection temperature (heat trace activation temperature)", "C", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "I_bn_des", "Solar irradiation at design", "W/m2", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "V_hdr_max", "Maximum HTF velocity in the header at design", "m/s", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "V_hdr_min", "Minimum HTF velocity in the header at design", "m/s", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "Pipe_hl_coef", "Loss coefficient from the header, 	runner pipe, 	and non-HCE piping", "W/m2-K", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "SCA_drives_elec", "Tracking power, 	in Watts per SCA drive", "W/module", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "fthrok", "Flag to allow partial defocusing of the collectors", "", "", "controller", "*", "INTEGER", "" },
	{ SSC_INPUT, SSC_NUMBER, "fthrctrl", "Defocusing strategy", "", "", "controller", "*", "INTEGER", "" },
	{ SSC_INPUT, SSC_NUMBER, "ColAz", "Collector azimuth angle", "deg", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "solar_mult", "Solar multiple", "", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "mc_bal_hot", "The heat capacity of the balance of plant on the hot side", "kWht/K-MWt", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "mc_bal_cold", "The heat capacity of the balance of plant on the cold side", "kWht/K-MWt", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "mc_bal_sca", "Non-HTF heat capacity associated with each SCA - per meter basis", "Wht/K-m", "", "controller", "*", "", "" },

	{ SSC_INPUT, SSC_NUMBER, "opt_model", "The optical model (1=Solar position ; 2=Collector incidence table ; 3 = IAM polys)", "", "", "controller", "*", "INTEGER", "" },
	{ SSC_INPUT, SSC_NUMBER, "A_aperture", "Reflective aperture area of the collector", "m2", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "reflectivity", "Solar-weighted mirror reflectivity value ", "", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "TrackingError", "Tracking error derate", "", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "GeomEffects", "Geometry effects derate", "", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "Dirt_mirror", "User-defined dirt on mirror derate", "", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "Error", "User-defined general optical error derate ", "", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "L_mod", "The length of the collector module", "m", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_ARRAY, "IAM_T_coefs", "Incidence angle modifier coefficients - transversal plane", "", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_ARRAY, "IAM_L_coefs", "Incidence angle modifier coefficients - longitudinal plane", "", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_MATRIX, "OpticalTable", "Values of the optical efficiency table", "", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "rec_model", "Receiver model type (1=Polynomial ; 2=Evac tube)", "", "", "controller", "*", "INTEGER", "" },
	{ SSC_INPUT, SSC_ARRAY, "HCE_FieldFrac", "The fraction of the field occupied by this HCE type ", "", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_ARRAY, "D_abs_in", "The inner absorber tube diameter", "m", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_ARRAY, "D_abs_out", "The outer absorber tube diameter", "m", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_ARRAY, "D_glass_in", "The inner glass envelope diameter ", "m", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_ARRAY, "D_glass_out", "The outer glass envelope diameter ", "m", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_ARRAY, "D_plug", "The diameter of the absorber flow plug (optional) ", "m", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_ARRAY, "Flow_type", "The flow type through the absorber", "", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_ARRAY, "Rough", "Roughness of the internal surface ", "m", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_ARRAY, "alpha_env", "Envelope absorptance ", "", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_MATRIX, "epsilon_abs_1", "Absorber emittance - HCE variation 1", "", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_MATRIX, "epsilon_abs_2", "Absorber emittance - HCE variation 2", "", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_MATRIX, "epsilon_abs_3", "Absorber emittance - HCE variation 3", "", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_MATRIX, "epsilon_abs_4", "Absorber emittance - HCE variation 4", "", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_ARRAY, "alpha_abs", "Absorber absorptance ", "", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_ARRAY, "Tau_envelope", "Envelope transmittance", "", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_ARRAY, "epsilon_glass", "Glass envelope emissivity", "", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_ARRAY, "GlazingIntactIn", "The glazing intact flag {1=true, 	else=false}", "", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_ARRAY, "P_a", "Annulus gas pressure", "torr", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_ARRAY, "AnnulusGas", "Annulus gas type (1=air, 	26=Ar, 	27=H2)", "", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_ARRAY, "AbsorberMaterial", "Absorber material type", "", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_ARRAY, "Shadowing", "Receiver bellows shadowing loss factor", "", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_ARRAY, "dirt_env", "Loss due to dirt on the receiver envelope", "", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_ARRAY, "Design_loss", "Receiver heat loss at design", "W/m", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "L_mod_spacing", "Piping distance between sequential modules in a loop", "m", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "L_crossover", "Length of crossover piping in a loop", "m", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_ARRAY, "HL_T_coefs", "HTF temperature-dependent heat loss coefficients", "W/m-K", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_ARRAY, "HL_w_coefs", "Wind-speed-dependent heat loss coefficients", "W/m-(m/s)", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "DP_nominal", "Pressure drop across a single collector assembly at design", "bar", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_ARRAY, "DP_coefs", "Pressure drop mass flow based part-load curve", "", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "rec_htf_vol", "Volume of HTF in a single collector unit per unit aperture area", "L/m2-ap", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "T_amb_sf_des", "Ambient design-point temperature for the solar field", "C", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "V_wind_des", "Design-point wind velocity", "m/s", "", "controller", "*", "", "" },

	// Type 262 inputs
	{ SSC_INPUT, SSC_NUMBER, "I_b", "Direct normal incident solar irradiation", "kJ/m2-hr", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "T_db", "Dry bulb air temperature", "C", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "V_wind", "Ambient windspeed ", "m/s", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "P_amb", "Ambient pressure", "atm", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "T_dp", "The dewpoint temperature", "C", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "T_cold_in", "HTF return temperature", "C", "", "controller", "*", "", "" },
// not used
//	{ SSC_INPUT, SSC_NUMBER, "m_dot_in", "HTF mass flow rate at the inlet ", "kg/hr", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "defocus", "Defocus control ", "", "", "controller", "*", "", "" },
	// connected to weather file
//	{ SSC_INPUT, SSC_NUMBER, "SolarAz", "Solar azimuth angle ", "deg", "", "controller", "*", "", "" },
//	{ SSC_INPUT, SSC_NUMBER, "SolarZen", "Solar zenith angle", "deg", "", "controller", "*", "", "" },
//	{ SSC_INPUT, SSC_NUMBER, "latitude", "Site latitude read from weather file", "deg", "", "controller", "*", "", "" },
//	{ SSC_INPUT, SSC_NUMBER, "longitude", "Site longitude read from weather file", "deg", "", "controller", "*", "", "" },
//	{ SSC_INPUT, SSC_NUMBER, "timezone", "Time zone", "hr", "", "controller", "*", "", "" },






	

	//   controller (type 251) inputs
	//   VARTYPE            DATATYPE          NAME                LABEL                                                             UNITS           META            GROUP            REQUIRED_IF                CONSTRAINTS              UI_HINTS
	{ SSC_INPUT, SSC_NUMBER, "T_pb_out_init", "Fluid temperature from the power block", "C", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_NUMBER, "field_fluid", "Label", "", "", "controller", "*", "", "" },
	{ SSC_INPUT, SSC_MATRIX, "field_fl_props", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "store_fluid", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "tshours", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "is_hx", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "dt_hot", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "dt_cold", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "hx_config", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "q_max_aux", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "T_set_aux", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "V_tank_hot_ini", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "T_tank_hot_ini", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "T_tank_cold_ini", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "vol_tank", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "h_tank", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "h_tank_min", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "u_tank", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "tank_pairs", 			"Label", 			"", 			"", 			"controller", 			"*", 			"INTEGER", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "cold_tank_Thtr", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "hot_tank_Thtr", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "tank_max_heat", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "T_field_in_des", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "T_field_out_des", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "q_pb_design", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "W_pb_design", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "cycle_max_frac", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "cycle_cutoff_frac", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "solarm", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "pb_pump_coef", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "tes_pump_coef", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "pb_fixed_par", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_ARRAY, "bop_array", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_ARRAY, "aux_array", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT,        SSC_NUMBER,      "tes_temp", 			        "Label", 			                                                         "", 			            "", 			            "controller", 			   "*", 			                      "", 			                     "" },
	{ SSC_INPUT, SSC_NUMBER, "fossil_mode", 			"Label", 			"", 			"", 			"controller", 			"*", 			"INTEGER", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "fthr_ok", 			"Label", 			"", 			"", 			"controller", 			"*", 			"INTEGER", 			"" },
	{ SSC_INPUT,        SSC_NUMBER,      "nSCA", 			             "Label", 			                                                         "", 			            "", 			            "controller", 			   "*", 			                      "", 			                     "" },
	//{ SSC_INPUT,        SSC_NUMBER,      "I_bn_des", 			         "Label", 			                                                         "", 			            "", 			            "controller", 			   "*", 			                      "", 			                     "" },
	{ SSC_INPUT, SSC_NUMBER, "fc_on", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "q_sby_frac", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "t_standby_reset", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "sf_type", 			"Solar field type, 1 = trough, 2 = tower", 			"-", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "tes_type", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_ARRAY, "tslogic_a", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_ARRAY, "tslogic_b", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_ARRAY, "tslogic_c", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_ARRAY, "ffrac", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "tc_fill", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "tc_void", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "t_dis_out_min", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "t_ch_out_max", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "nodes", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "f_tc_cold", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	// controller (type 251)  initial conditions
	{ SSC_INPUT, SSC_NUMBER, "I_bn", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "T_amb", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "m_dot_field", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "m_dot_htf_ref", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "T_field_out", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "T_pb_out_init", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "m_pb_demand", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "q_startup", 			"Label", 			"", 			"", 			"controller", 			"*", 			"", 			"" },




	//   powerblock (type 224) inputs
	//   VARTYPE            DATATYPE          NAME                LABEL                                                             UNITS           META            GROUP            REQUIRED_IF                CONSTRAINTS              UI_HINTS
	{ SSC_INPUT, SSC_NUMBER, "P_ref", 			"Label", 			"", 			"", 			"powerblock", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "eta_ref", 			"Label", 			"", 			"", 			"powerblock", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "T_htf_hot_ref", 			"Label", 			"", 			"", 			"powerblock", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "T_htf_cold_ref", 			"Label", 			"", 			"", 			"powerblock", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "dT_cw_ref", 			"Label", 			"", 			"", 			"powerblock", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "T_amb_des", 			"Label", 			"", 			"", 			"powerblock", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "HTF", 			"Label", 			"", 			"", 			"powerblock", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "q_sby_frac", 			"Label", 			"", 			"", 			"powerblock", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "P_boil", 			"Label", 			"", 			"", 			"powerblock", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "CT", 			"Label", 			"", 			"", 			"powerblock", 			"*", 			"INTEGER", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "startup_time", 			"Label", 			"", 			"", 			"powerblock", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "startup_frac", 			"Label", 			"", 			"", 			"powerblock", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "tech_type", 			"Label", 			"", 			"", 			"powerblock", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "T_approach", 			"Label", 			"", 			"", 			"powerblock", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "T_ITD_des", 			"Label", 			"", 			"", 			"powerblock", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "P_cond_ratio", 			"Label", 			"", 			"", 			"powerblock", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "pb_bd_frac", 			"Label", 			"", 			"", 			"powerblock", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "P_cond_min", 			"Label", 			"", 			"", 			"powerblock", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "n_pl_inc", 			"Label", 			"", 			"", 			"powerblock", 			"*", 			"INTEGER", 			"" },
	{ SSC_INPUT, SSC_ARRAY, "F_wc", 			"Label", 			"", 			"", 			"powerblock", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "mode", 			"Label", 			"", 			"", 			"powerblock", 			"*", 			"", 			"" },
	// powerblock (type 224) initial conditions
	{ SSC_INPUT, SSC_NUMBER, "T_wb", 			"Label", 			"", 			"", 			"powerblock", 			"*", 			"", 			"" },
	//	{ SSC_INPUT,        SSC_NUMBER,      "T_db", 			             "Label", 			                                                         "", 			            "", 			            "powerblock", 			   "*", 			                      "", 			                     "" },
	//	{ SSC_INPUT,        SSC_NUMBER,      "P_amb", 			            "Label", 			                                                         "", 			            "", 			            "powerblock", 			   "*", 			                      "", 			                     "" },
	{ SSC_INPUT, SSC_NUMBER, "rh", 			"Label", 			"", 			"", 			"powerblock", 			"*", 			"", 			"" },
//	{ SSC_INPUT, SSC_NUMBER, "T_htf_hot", 			"Label", 			"", 			"", 			"powerblock", 			"*", 			"", 			"" },
//	{ SSC_INPUT, SSC_NUMBER, "m_dot_htf_init", 			"Label", 			"", 			"", 			"powerblock", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "demand_var", 			"Label", 			"", 			"", 			"powerblock", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "standby_control", 			"Label", 			"", 			"", 			"powerblock", 			"*", 			"", 			"" },
	//{ SSC_INPUT,        SSC_NUMBER,      "TOU", 			              "Label", 			                                                         "", 			            "", 			            "powerblock", 			   "*", 			                      "", 			                     "" },

	//  enet calculator
	{ SSC_INPUT, SSC_NUMBER, "eta_lhv", 			"Label", 			"", 			"", 			"enet", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "eta_tes_htr", 			"Label", 			"", 			"", 			"enet", 			"*", 			"", 			"" },
	{ SSC_INPUT, SSC_NUMBER, "fp_mode", 			"Label", 			"", 			"", 			"enet", 			"*", 			"", 			"" },


	// OUTPUTS
	// The names of the output variables should match the parameter names for the TCS units in order to signal to the TCS kernel to store the values by timestep

	//weather file reader
	{ SSC_OUTPUT, SSC_ARRAY, "beam", "Beam normal irradiance", "W/m2", "", "weather", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "hour", "Hour of Year", "", "", "weather", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "pres", "Pressure", "mbar", "", "weather", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "wspd", "Wind Speed", "m/s", "", "weather", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "solazi", "Solar Azimuth", "deg", "", "weather", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "solzen", "Solar Zenith", "deg", "", "weather", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "tdry", "Dry bulb temperature", "C", "", "weather", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "twet", "Wet bulb temperature", "C", "", "weather", "*", "LENGTH=8760", "" },
	
    // VARTYPE          DATATYPE          NAME                 LABEL                                                                                 UNITS           META            GROUP            REQUIRED_IF                 CONSTRAINTS             UI_HINTS
	// Type 262 outputs
	{ SSC_OUTPUT, SSC_ARRAY, "T_sys_h", "Solar field HTF outlet temperature", "C", "", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "m_dot_avail", "HTF mass flow rate from the field", "kg/hr", "", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "q_avail", "Thermal power produced by the field", "MWt", "", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "DP_tot", "Total HTF pressure drop", "bar", "", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "W_dot_pump", "Required solar field pumping power", "MWe","", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "E_fp_tot", "Freeze protection energy", "MW","", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "T_sys_c", "Collector inlet temperature", "C","", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "eta_optical", "Collector total optical efficiency", "none","", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "EqOptEff", "Total solar field optical efficiency - including receiver optical losses", "none","", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "sf_def", "The fraction of the solar field that's on focus", "none","", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "m_dot_htf_tot", "The actual flow rate through the field..", "kg/hr","", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "E_bal_startup", "Startup energy consumed", "MWt","", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "q_inc_sf_tot", "Total power incident on the field", "MWt","", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "q_abs_tot", "Total absorbed energy", "MWt","", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "q_loss_tot", "Total receiver thermal and optical losses", "MWt","", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "m_dot_htf", "Flow rate in a single loop", "kg/s","", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "q_loss_spec_tot", "Field-average receiver thermal losses (convection and radiation)", "W/m","", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "track_par_tot", "Parasitic electric power consumed by the tracking drives", "MWe","", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "Pipe_hl", "Pipe heat loss in the hot header and the hot runner", "MWt","", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "q_dump", "Dumped thermal energy", "MWt","", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "phi_t", "Solar incidence angle in the collector transversal plane", "deg","", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "theta_L", "Solar incidence angle in the collector longitudinal plane", "deg","", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "t_loop_outlet", "HTF temperature immediately subsequent to the loop outlet", "C","", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "c_htf_ave", "Average solar field specific heat", "J/kg-K","", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "q_field_delivered", "Total solar field thermal power delivered", "MWt","", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "eta_thermal", "Solar field thermal efficiency (power out/ANI)", "none","", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "E_loop_accum", "Accumulated internal energy change rate in the loops ONLY", "MWht","", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "E_hdr_accum", "Accumulated internal energy change rate in the headers/SGS", "MWht","", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "E_tot_accum", "Total accumulated internal energy change rate", "MWht","", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "E_field", "Accumulated internal energy in the entire solar field", "MWht","", "mslf", "*", "LENGTH=8760", "" },
//	{ SSC_OUTPUT, SSC_STRING, "piping_summary", "String containing description of field piping design", "none","", "mslf", "*", "LENGTH=8760", "" },
// sum calcs
	{ SSC_OUTPUT, SSC_ARRAY, "P_cycle", "Gross electricity generation (or usage) by the plant", "MW", "", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "W_net", "Net electricity generation (or usage) by the plant", "MW", "", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "W_par_tot", "Total electrical parasitic consumption by all plant subsystems", "MW", "", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "Fuel_usage", "Total fossil fuel usage by all plant subsystems", "MMBTU", "", "mslf", "*", "LENGTH=8760", "" },
	{ SSC_OUTPUT, SSC_ARRAY, "Q_fp_tot", "Total freeze protection thermal energy requirement", "MW", "", "mslf", "*", "LENGTH=8760", "" },

	{ SSC_OUTPUT, SSC_ARRAY, "q_aux_fuel", "Heat content of fuel required to provided aux heat", "MMBTU", "", "Outputs", "*", "LENGTH=8760", "" },


	{ SSC_OUTPUT, SSC_ARRAY, "hourly_energy", "Net electricity generation (or usage) by the plant", "kWh", "", "Outputs", "*", "LENGTH=8760", "" },

	// monthly values
	{ SSC_OUTPUT, SSC_ARRAY, "monthly_energy", "Monthly Energy", "kWh", "", "mslf", "*", "LENGTH=12", "" },


	// single values
	{ SSC_OUTPUT, SSC_NUMBER, "annual_energy",        "Annual Energy",                                "kWh", "", "mslf", "*", "", "" },
	{ SSC_OUTPUT, SSC_NUMBER, "annual_W_cycle_gross", "Electrical source - Power cycle gross output", "kWh", "", "mslf", "*", "", "" },
	//{ SSC_OUTPUT,       SSC_NUMBER,      "system_use_lifetime_output",  "Use lifetime output",                                                       "0/1",          "",            "Linear Fresnel", "*",                       "INTEGER",               "" },

	{ SSC_OUTPUT, SSC_NUMBER, "conversion_factor", "Gross to Net Conversion Factor", "%", "", "Calculated", "*", "", "" },
	{ SSC_OUTPUT, SSC_NUMBER, "capacity_factor", "Capacity factor", "", "", "", "*", "", "" },
	{ SSC_OUTPUT, SSC_NUMBER, "kwh_per_kw", "First year kWh/kW", "", "", "", "*", "", "" },
	{ SSC_OUTPUT, SSC_NUMBER, "system_heat_rate", "System heat rate", "MMBtu/MWh", "", "", "*", "", "" },
	{ SSC_OUTPUT, SSC_NUMBER, "annual_fuel_usage", "Annual fuel usage", "kWh", "", "", "*", "", "" },


    var_info_invalid };

class cm_tcsmslf : public tcKernel
{
public:

	cm_tcsmslf(tcstypeprovider *prov)
	:tcKernel(prov)
	{
		add_var_info( _cm_vtab_tcsmslf );
		add_var_info(vtab_adjustment_factors);

		// debugging
		//set_store_all_parameters(true);
		//set_store_array_matrix_data(true);
		//set_store_all_parameters(true); // default is 'false' = only store TCS parameters that match the SSC_OUTPUT variables above
	}

	void exec( ) throw( general_error )
	{
		bool debug_mode = false; //(__DEBUG__ == 1);  // When compiled in VS debug mode, this will use the trnsys weather file; otherwise, it will attempt to open the file with name that was passed in
		//Add weather file reader unit
		int weather = 0;
		if(debug_mode) weather = add_unit("trnsys_weatherreader", "TRNSYS weather reader");
		else weather = add_unit("weatherreader", "TCS weather reader");

		if(debug_mode)
		{
			set_unit_value( weather, "file_name", "C:/svn_NREL/main/ssc/tcs/typelib/TRNSYS_weather_outputs/tucson_trnsys_weather.out" );
			set_unit_value( weather, "i_hour", "TIME" );
			set_unit_value( weather, "i_month", "month" );
			set_unit_value( weather, "i_day", "day" );
			set_unit_value( weather, "i_global", "GlobalHorizontal" );
			set_unit_value( weather, "i_beam", "DNI" );
			set_unit_value( weather, "i_diff", "DiffuseHorizontal" );
			set_unit_value( weather, "i_tdry", "T_dry" );
			set_unit_value( weather, "i_twet", "T_wet" );
			set_unit_value( weather, "i_tdew", "T_dew" );
			set_unit_value( weather, "i_wspd", "WindSpeed" );
			set_unit_value( weather, "i_wdir", "WindDir" );
			set_unit_value( weather, "i_rhum", "RelHum" );
			set_unit_value( weather, "i_pres", "AtmPres" );
			set_unit_value( weather, "i_snow", "SnowCover" );
			set_unit_value( weather, "i_albedo", "GroundAlbedo" );
			set_unit_value( weather, "i_poa", "POA" );
			set_unit_value( weather, "i_solazi", "Azimuth" );
			set_unit_value( weather, "i_solzen", "Zenith" );
			set_unit_value( weather, "i_lat", "Latitude" );
			set_unit_value( weather, "i_lon", "Longitude" );
			set_unit_value( weather, "i_shift", "Shift" );
		}
		else
		{
			//Set weather parameters
			set_unit_value_ssc_string( weather, "file_name" );
			set_unit_value_ssc_double( weather, "track_mode" );
			set_unit_value_ssc_double( weather, "tilt" );
			set_unit_value_ssc_double( weather, "azimuth" );
		}
		
		// Add tou translator
		int	tou_translator = add_unit("tou_translator", "Time of Use Translator");
		//Add the solar field collector unit
		int solarfield = add_unit("sam_mw_lf_type262", "type 262 solarfield");
		//Add controller unit
		int controller = add_unit("sam_mw_trough_type251", "type 251 controller");
		//Add direct powerblock unit
		int powerblock = add_unit("sam_mw_pt_type224", "type 224 powerblock");
		//Add unit to that summarizes energy output
		int enet = add_unit("sam_mw_csp_SumCalcs","type csp_SumCalcs enet calculator");

		// Now set solar field collector unit parameters
		set_unit_value_ssc_double(solarfield, "nMod" ); // nMod);
		set_unit_value_ssc_double(solarfield, "nRecVar" ); // 4);
		set_unit_value_ssc_double(solarfield, "nLoops" ); // nLoops);
		set_unit_value_ssc_double(solarfield, "eta_pump" ); // 0.85);
		set_unit_value_ssc_double(solarfield, "HDR_rough" ); // 4.57E-05);
		set_unit_value_ssc_double(solarfield, "theta_stow" ); // 170);
		set_unit_value_ssc_double(solarfield, "theta_dep" ); // 10);
		set_unit_value_ssc_double(solarfield, "FieldConfig" ); // 2);
		set_unit_value_ssc_double(solarfield, "T_startup" ); // T_startup);
		set_unit_value_ssc_double(solarfield, "pb_rated_cap" ); // E_gross);
		set_unit_value_ssc_double(solarfield, "m_dot_htfmin" ); // m_dot_min);
		set_unit_value_ssc_double(solarfield, "m_dot_htfmax" ); // m_dot_max);
		set_unit_value_ssc_double(solarfield, "T_loop_in_des" ); // T_cold_des);
		set_unit_value_ssc_double(solarfield, "T_loop_out" ); // T_hot_des);
		set_unit_value_ssc_double(solarfield, "Fluid" ); // field_fluid);
		set_unit_value_ssc_double(solarfield, "T_field_ini" ); // T_startup);
		set_unit_value_ssc_double(solarfield, "T_fp" ); // T_cold_fp);
		set_unit_value_ssc_double(solarfield, "I_bn_des" ); // I_bn_des);
		set_unit_value_ssc_double(solarfield, "V_hdr_max" ); // 3);
		set_unit_value_ssc_double(solarfield, "V_hdr_min" ); // 2);
		set_unit_value_ssc_double(solarfield, "Pipe_hl_coef" ); // 0.45);
		set_unit_value_ssc_double(solarfield, "SCA_drives_elec" ); // 125);
		set_unit_value_ssc_double(solarfield, "fthrok" ); // 1);
		set_unit_value_ssc_double(solarfield, "fthrctrl" ); // 2);
		set_unit_value_ssc_double(solarfield, "ColAz" ); // ColAz);
		set_unit_value_ssc_double(solarfield, "solar_mult" ); // SM);
		set_unit_value_ssc_double(solarfield, "mc_bal_hot" ); // 0.2);
		set_unit_value_ssc_double(solarfield, "mc_bal_cold" ); // 0.2);
		set_unit_value_ssc_double(solarfield, "mc_bal_sca" ); // 4.5);

		set_unit_value_ssc_double(solarfield, "opt_model" ); // opt_model);
		set_unit_value_ssc_double(solarfield, "A_aperture" ); // A_aperture);
		set_unit_value_ssc_double(solarfield, "reflectivity" ); // reflectivity);
		set_unit_value_ssc_double(solarfield, "TrackingError" ); // TrackingError);
		set_unit_value_ssc_double(solarfield, "GeomEffects" ); // GeomEffects);
		set_unit_value_ssc_double(solarfield, "Dirt_mirror" ); // Dirt_mirror);
		set_unit_value_ssc_double(solarfield, "Error" ); // Error);
		set_unit_value_ssc_double(solarfield, "L_mod" ); // L_mod);
		set_unit_value_ssc_array(solarfield, "IAM_T_coefs" ); // [0.9896, 0.044, -0.0721, -0.2327, 0.]);
		set_unit_value_ssc_array(solarfield, "IAM_L_coefs" ); // [1.0031, -0.2259, 0.5368, -1.6434, 0.7222]);
		set_unit_value_ssc_matrix(solarfield, "OpticalTable");

		set_unit_value_ssc_double(solarfield, "rec_model" ); // rec_model);
		set_unit_value_ssc_array(solarfield, "HCE_FieldFrac" ); // HCE_FieldFrac);
		set_unit_value_ssc_array(solarfield, "D_abs_in" ); // [0.066, 0.066, 0.066, 0.066]);
		set_unit_value_ssc_array(solarfield, "D_abs_out" ); // [0.07, 0.07, 0.07, 0.07]);
		set_unit_value_ssc_array(solarfield, "D_glass_in" ); // [0.115, 0.115, 0.115, 0.115]);
		set_unit_value_ssc_array(solarfield, "D_glass_out" ); // [0.12, 0.12, 0.12, 0.12]);
		set_unit_value_ssc_array(solarfield, "D_plug" ); // [0, 0, 0, 0]);
		set_unit_value_ssc_array(solarfield, "Flow_type" ); // [1, 1, 1, 1]);
		set_unit_value_ssc_array(solarfield, "Rough" ); // [4.50E-05, 4.50E-05, 4.50E-05, 4.50E-05]);
		set_unit_value_ssc_array(solarfield, "alpha_env" ); // [0.02, 0.02, 0, 0]);
		set_unit_value_ssc_matrix_transpose(solarfield, "epsilon_abs_1"); // [[100, 150, 200, 250, 300, 350, 400, 450, 500], [0.064, 0.0665, 0.07, 0.0745, 0.08, 0.0865, 0.094, 0.1025, 0.112]]);
		set_unit_value_ssc_matrix_transpose(solarfield, "epsilon_abs_2"); // [[0], [0.65]]);
		set_unit_value_ssc_matrix_transpose(solarfield, "epsilon_abs_3"); // [[0], [0.65]]);
		set_unit_value_ssc_matrix_transpose(solarfield, "epsilon_abs_4"); // [[0], [0]]);
		set_unit_value_ssc_array(solarfield, "alpha_abs" ); // alpha_abs);
		set_unit_value_ssc_array(solarfield, "Tau_envelope" ); // Tau_envelope);
		set_unit_value_ssc_array(solarfield, "epsilon_glass" ); // [0.86, 0.86, 1, 0]);
		set_unit_value_ssc_array(solarfield, "GlazingIntactIn" ); // [1, 1, 0, 1]);
		set_unit_value_ssc_array(solarfield, "P_a" ); // [0.0001, 750, 750, 0]);
		set_unit_value_ssc_array(solarfield, "AnnulusGas" ); // [27, 1, 1, 27]);
		set_unit_value_ssc_array(solarfield, "AbsorberMaterial" ); // [1, 1, 1, 1]);
		set_unit_value_ssc_array(solarfield, "Shadowing" ); // [0.96, 0.96, 0.96, 0.963]);
		set_unit_value_ssc_array(solarfield, "dirt_env" ); // [0.98, 0.98, 1, 0.98]);
		set_unit_value_ssc_array(solarfield, "Design_loss" ); // Design_loss);
		set_unit_value_ssc_double(solarfield, "L_mod_spacing" ); // 1);
		set_unit_value_ssc_double(solarfield, "L_crossover" ); // 15);
		set_unit_value_ssc_array(solarfield, "HL_T_coefs" ); // HL_T_coefs);
		set_unit_value_ssc_array(solarfield, "HL_w_coefs" ); // HL_w_coefs);
		set_unit_value_ssc_double(solarfield, "DP_nominal" ); // 2.5);
		set_unit_value_ssc_array(solarfield, "DP_coefs" ); // [0., 1., 0., 0.]);
		set_unit_value_ssc_double(solarfield, "rec_htf_vol" ); // 1);
		set_unit_value_ssc_double(solarfield, "T_amb_sf_des" ); // T_amb_des);
		set_unit_value_ssc_double(solarfield, "V_wind_des" ); // V_wind_des);


		//Set the initial values
//		set_unit_value_ssc_double(solarfield, "I_b" ); // 0.);
//		set_unit_value_ssc_double(solarfield, "T_db" ); // 15.);
//		set_unit_value_ssc_double(solarfield, "V_wind" ); // 1.5);
//		set_unit_value_ssc_double(solarfield, "P_amb" ); // 1.);
//		set_unit_value_ssc_double(solarfield, "T_dp" ); // 10.);
		set_unit_value_ssc_double(solarfield, "T_cold_in"); // 293.);
// m_dot_in
		set_unit_value_ssc_double(solarfield, "defocus"); // 1.);
//		set_unit_value_ssc_double(solarfield, "SolarAz"); // 0.);
// SolarZen
// latitude
// longitude
// timezone


		

		//Set controller parameters type 251
		set_unit_value_ssc_double(controller, "field_fluid" ); // field_fluid);
		set_unit_value_ssc_matrix(controller, "field_fl_props" ); // [0]);
		set_unit_value_ssc_double(controller, "store_fluid" ); // tes_fluid);
		set_unit_value_ssc_double(controller, "tshours" ); // TES_hrs);
		set_unit_value_ssc_double(controller, "is_hx" ); // is_hx);
		set_unit_value_ssc_double(controller, "dt_hot" ); // hx_dt_hot);
		set_unit_value_ssc_double(controller, "dt_cold" ); // hx_dt_cold);
		set_unit_value_ssc_double(controller, "hx_config" ); // 2);
		set_unit_value_ssc_double(controller, "q_max_aux" ); // Qsf);
		set_unit_value_ssc_double(controller, "lhv_eff", as_double("eta_lhv"));			// 9.17.14 twn: input lhv here to calculate fuel usage
		set_unit_value_ssc_double(controller, "T_set_aux" ); // T_hot_des);
		set_unit_value_ssc_double(controller, "V_tank_hot_ini" ); // TES_init_vol);
		set_unit_value_ssc_double(controller, "T_tank_hot_ini" ); // T_hot_des);
		set_unit_value_ssc_double(controller, "T_tank_cold_ini" ); // T_cold_des);
		set_unit_value_ssc_double(controller, "vol_tank" ); // TES_tank_vol);
		set_unit_value_ssc_double(controller, "h_tank" ); // 20);
		set_unit_value_ssc_double(controller, "h_tank_min" ); // 1);
		set_unit_value_ssc_double(controller, "u_tank" ); // 0.4);
		set_unit_value_ssc_double(controller, "tank_pairs" ); // 1);
		// cold_tank_Thtr = T_cold_des - 30 = T_loop_in_des - 30
		// set_unit_value_ssc_double(controller, "cold_tank_Thtr"); // T_cold_fp);
		set_unit_value(controller, "cold_tank_Thtr", (as_double("T_loop_in_des") - 30.0) );
		// hot_tank_Thtr = T_hot_des - 100 = T_loop_out - 100
		//set_unit_value_ssc_double(controller, "hot_tank_Thtr"); // T_hot_fp);
		set_unit_value(controller, "hot_tank_Thtr", (as_double("T_loop_out") - 100.0));
		// Q_TES_htr = 1.5*TES_tank_vol/1000.;
		//set_unit_value_ssc_double(controller, "tank_max_heat"); // Q_TES_htr);
		set_unit_value(controller, "tank_max_heat", (1.5 * as_double("vol_Tank") / 1000.0));
		set_unit_value_ssc_double(controller, "T_field_in_des"); // T_cold_des);
		set_unit_value_ssc_double(controller, "T_field_out_des" ); // T_hot_des);
		set_unit_value_ssc_double(controller, "q_pb_design" ); // Q_cycle_des);
		set_unit_value_ssc_double(controller, "W_pb_design" ); // E_gross);
		set_unit_value_ssc_double(controller, "cycle_max_frac" ); // 1.05);
		set_unit_value_ssc_double(controller, "cycle_cutoff_frac" ); // 0.25);
		set_unit_value_ssc_double(controller, "solarm" ); // SM);
		set_unit_value_ssc_double(controller, "pb_pump_coef" ); // 0.55);
		set_unit_value_ssc_double(controller, "tes_pump_coef" ); // 0.15);
		set_unit_value_ssc_double(controller, "pb_fixed_par" ); // 0.0055);
		set_unit_value_ssc_array(controller, "bop_array" ); // [0, 1, 0.483, 0.517, 0]);
		set_unit_value_ssc_array(controller, "aux_array" ); // [0.02273, 1, 0.483, 0.517, 0]);
		// tes_temp = T_sf_ave
		set_unit_value_ssc_double(controller, "T_startup" ); // T_sf_ave);
		//set_unit_value(controller, "T_startup", as_double("tes_temp"));
		set_unit_value_ssc_double(controller, "fossil_mode" ); // 1);
		set_unit_value_ssc_double(controller, "fthr_ok" ); // 1);
		set_unit_value_ssc_double(controller, "nSCA" ); // nMod);
		set_unit_value_ssc_double(controller, "I_bn_des" ); // I_bn_des);
		set_unit_value_ssc_double(controller, "fc_on" ); // 0);
		set_unit_value_ssc_double(controller, "q_sby_frac" ); // 0.2);
		set_unit_value_ssc_double(controller, "t_standby_reset" ); // 2);
		set_unit_value_ssc_double(controller, "tes_type" ); // 1);
		set_unit_value_ssc_array(controller, "tslogic_a" ); // [0, 0, 0, 0, 0, 0, 0, 0, 0]);
		set_unit_value_ssc_array(controller, "tslogic_b" ); // [0, 0, 0, 0, 0, 0, 0, 0, 0]);
		set_unit_value_ssc_array(controller, "tslogic_c" ); // [1.05, 1, 1, 1, 1, 1, 1, 1, 1]);
		set_unit_value_ssc_array(controller, "ffrac" ); // [0, 0, 0, 0, 0, 0, 0, 0, 0]);
		set_unit_value_ssc_double(controller, "tc_fill" ); // 7);
		set_unit_value_ssc_double(controller, "tc_void" ); // 0.25);
		set_unit_value_ssc_double(controller, "t_dis_out_min" ); // 500);
		set_unit_value_ssc_double(controller, "t_ch_out_max" ); // 500);
		set_unit_value_ssc_double(controller, "nodes" ); // 2000);
		set_unit_value_ssc_double(controller, "f_tc_cold" ); // 2);



		set_unit_value_ssc_matrix(tou_translator, "weekday_schedule");
		set_unit_value_ssc_matrix(tou_translator, "weekend_schedule");




		//Set initial values
		set_unit_value_ssc_double(controller, "I_bn" ); // 0.);
		set_unit_value_ssc_double(controller, "T_amb" ); // 15.);
		set_unit_value_ssc_double(controller, "m_dot_field" ); // 0.);
	//	set_unit_value_ssc_double(controller, "m_dot_htf_ref" ); // 0.);
		// T_hot_des=T_loop_out
		//set_unit_value_ssc_double(controller, "T_field_out" ); // T_hot_des);
		set_unit_value(controller, "T_field_out", as_double("T_loop_out"));
		// T_cold_des=T_loop_in_des
		//set_unit_value_ssc_double(controller, "T_pb_out_init"); // T_cold_des);
		set_unit_value(controller, "T_pb_out", as_double("T_loop_in_des"));
		set_unit_value_ssc_double(controller, "m_pb_demand"); // 100000.);
		set_unit_value_ssc_double(controller, "q_startup" ); // 0.);


		//Set the parameters for the power block type 224
		set_unit_value_ssc_double(powerblock, "P_ref" ); // E_gross);
		set_unit_value_ssc_double(powerblock, "eta_ref" ); // eta_cycle_des);
		set_unit_value_ssc_double(powerblock, "T_htf_hot_ref" ); // T_hot_des);
		set_unit_value_ssc_double(powerblock, "T_htf_cold_ref" ); // T_cold_des);
		set_unit_value_ssc_double(powerblock, "dT_cw_ref" ); // 10);
		set_unit_value_ssc_double(powerblock, "T_amb_des" ); // 20);
		set_unit_value_ssc_double(powerblock, "HTF" ); // field_fluid);
		set_unit_value_ssc_double(powerblock, "q_sby_frac" ); // 0.2);
		set_unit_value_ssc_double(powerblock, "P_boil" ); // 100);
		set_unit_value_ssc_double(powerblock, "CT" ); // 1);
		set_unit_value_ssc_double(powerblock, "startup_time" ); // 0.5);
		set_unit_value_ssc_double(powerblock, "startup_frac" ); // 0.2);
		set_unit_value_ssc_double(powerblock, "tech_type" ); // 2);
		set_unit_value_ssc_double(powerblock, "T_approach" ); // 5);
		set_unit_value_ssc_double(powerblock, "T_ITD_des" ); // 16);
		set_unit_value_ssc_double(powerblock, "P_cond_ratio" ); // 1.0028);
		set_unit_value_ssc_double(powerblock, "pb_bd_frac" ); // 0.02);
		set_unit_value_ssc_double(powerblock, "P_cond_min" ); // 1.25);
		set_unit_value_ssc_double(powerblock, "n_pl_inc" ); // 2);
		set_unit_value_ssc_array(powerblock, "F_wc" ); // [0, 0, 0, 0, 0, 0, 0, 0, 0]);

		set_unit_value_ssc_double(powerblock, "mode", 2);	//Always set to 2 for type 251
		//Set initial values
		set_unit_value_ssc_double(powerblock, "T_wb" ); // 10.);
		set_unit_value_ssc_double(powerblock, "T_db" ); // 15.);
		set_unit_value_ssc_double(powerblock, "P_amb" ); // 1.);
		set_unit_value_ssc_double(powerblock, "rh" ); // 0.25);
//		set_unit_value_ssc_double(powerblock, "T_htf_hot" ); // T_hot_des);
//		set_unit_value(controller, "T_htf_hot", as_double("T_loop_out"));
//		set_unit_value_ssc_double(powerblock, "m_dot_htf_init"); // 0.);
		set_unit_value_ssc_double(powerblock, "demand_var" ); // E_gross);
		set_unit_value_ssc_double(powerblock, "standby_control" ); // 0);

		//Connect the enet calculator to the parasitic values
		set_unit_value_ssc_double(enet, "eta_lhv" ); // 0.9);
		set_unit_value_ssc_double(enet, "eta_tes_htr" ); // 0.98);
		set_unit_value_ssc_double(enet, "fp_mode" ); // freeze_prot_mode);


		//Set the connections
		bool bConnected = connect(weather, "beam", solarfield, "I_b",0);
		bConnected &= connect(weather, "tdry", solarfield, "T_db");
		bConnected &= connect(weather, "wspd", solarfield, "V_wind");
		bConnected &= connect(weather, "pres", solarfield, "P_amb");
		bConnected &= connect(weather, "tdew", solarfield, "T_dp");
		bConnected &= connect(weather, "solazi", solarfield, "SolarAz");
		bConnected &= connect(weather, "solzen", solarfield, "SolarZen");
		bConnected &= connect(weather, "lat", solarfield, "latitude");
		bConnected &= connect(weather, "lon", solarfield, "longitude");
		bConnected &= connect(weather, "tz", solarfield, "timezone");
		if (!bConnected)
			throw exec_error("tcsmslf", util::format("there was a problem connecting outputs of weather to inputs of solarfield for the simulation."));





		bConnected &= connect(tou_translator, "tou_value", controller, "TOUPeriod");
		if (!bConnected)
			throw exec_error("tcsmslf", util::format("there was a problem connecting outputs of tou to inputs of controller for the simulation."));

		//Connect weather reader to controller
		bConnected &= connect(weather, "beam", controller, "I_bn");
		bConnected &= connect(weather, "tdry", controller, "T_amb");
		bConnected &= connect(solarfield, "m_dot_avail", controller, "m_dot_field");
		bConnected &= connect(powerblock, "m_dot_htf_ref", controller, "m_dot_htf_ref");
		bConnected &= connect(solarfield, "T_sys_h", controller, "T_field_out");
		bConnected &= connect(powerblock, "T_htf_cold", controller, "T_pb_out");
		bConnected &= connect(powerblock, "m_dot_demand", controller, "m_pb_demand");
		bConnected &= connect(solarfield, "E_bal_startup", controller, "q_startup");
		if (!bConnected)
			throw exec_error("tcsmslf", util::format("there was a problem connecting outputs of some units to inputs of controller for the simulation."));


		bConnected &= connect(controller, "defocus", solarfield, "defocus");
		bConnected &= connect(controller, "T_field_in", solarfield, "T_cold_in");
		if (!bConnected)
			throw exec_error("tcsmslf", util::format("there was a problem connecting outputs of controller to inputs of solarfield for the simulation."));

		//Connect inputs
		bConnected &= connect(weather, "twet", powerblock, "T_wb");
		bConnected &= connect(weather, "tdry", powerblock, "T_db");
		bConnected &= connect(weather, "pres", powerblock, "P_amb");
		bConnected &= connect(weather, "rhum", powerblock, "rh");

		bConnected &= connect(controller, "T_pb_in", powerblock, "T_htf_hot");
//		bConnected &= connect(controller, "T_pb_in", powerblock, "T_htf_hot_ref");
		bConnected &= connect(controller, "m_dot_pb", powerblock, "m_dot_htf");
		bConnected &= connect(controller, "m_dot_pb", powerblock, "demand_var");
		bConnected &= connect(controller, "standby_control", powerblock, "standby_control");
		bConnected &= connect(controller, "TOU", powerblock, "TOU");

		bConnected &= connect(powerblock, "P_cycle", enet, "W_cycle_gross");
		bConnected &= connect(powerblock, "W_cool_par", enet, "W_par_heatrej");
		bConnected &= connect(solarfield, "W_dot_pump", enet, "W_par_sf_pump");
		bConnected &= connect(controller, "htf_pump_power", enet, "W_par_tes_pump");
		bConnected &= connect(controller, "bop_par", enet, "W_par_BOP");
		bConnected &= connect(controller, "fixed_par", enet, "W_par_fixed");
		bConnected &= connect(solarfield, "track_par_tot", enet, "W_par_tracking");
		bConnected &= connect(controller, "aux_par", enet, "W_par_aux_boiler");
		bConnected &= connect(controller, "tank_fp_par", enet, "Q_par_tes_fp");
		bConnected &= connect(solarfield, "E_fp_tot", enet, "Q_par_sf_fp");
		bConnected &= connect(controller, "q_aux_heat", enet, "Q_aux_backup");
	

		// check if all connections worked
		if ( !bConnected )
			throw exec_error( "tcsmslf", util::format("there was a problem connecting outputs of one unit to inputs of another for the simulation.") );

		// Run simulation
		size_t hours = 8760;
//		int error = simulate(3600, hours * 3600, 3600, 30);
		int error = simulate(3600, hours * 3600, 3600);
		if (0 > error)
			throw exec_error( "tcsmslf", util::format("there was a problem simulating in the TCS molten salt linear fresnel model. Error %d", error) );

		// get the outputs
		if (!set_all_output_arrays() )
			throw exec_error( "tcsmslf", util::format("there was a problem returning the results from the simulation.") );

		//1.7.15, twn: Need to calculated the conversion factor before the performance adjustments are applied to "hourly energy"
		accumulate_annual("hourly_energy", "annual_energy"); // already in kWh
		accumulate_annual("P_cycle", "annual_W_cycle_gross", 1000); // convert from MWh to kWh
		// Calculated outputs
		ssc_number_t ae = as_number("annual_energy");
		ssc_number_t pg = as_number("annual_W_cycle_gross");
		ssc_number_t convfactor = (pg != 0) ? 100 * ae / pg : 0;
		assign("conversion_factor", convfactor);

		// performance adjustement factors
		adjustment_factors haf(this);
		if (!haf.setup())
			throw exec_error("tcsmslf", "failed to setup adjustment factors: " + haf.error());
		
		size_t count;
		ssc_number_t *p_hourly_energy = as_array("hourly_energy", &count);
		// set hourly energy = tcs output Enet
		
		//ssc_number_t *hourly_energy = as_array("W_net", &count);//MWh
		if (count != 8760)
			throw exec_error("tcsmslf", "hourly_energy count incorrect (should be 8760): " + count);

		// apply performance adjustments and convert from MWh to kWh 
		for (size_t i = 0; i < count; i++)
			p_hourly_energy[i] = p_hourly_energy[i] * (ssc_number_t)(haf(i));	// already in kWh


		accumulate_annual("hourly_energy", "annual_energy"); // already in kWh
		accumulate_monthly("hourly_energy", "monthly_energy"); // already in kWh


		double fuel_usage_mmbtu = 0;
		ssc_number_t *hourly_fuel = as_array("q_aux_fuel", &count);//MWh
		if (count != 8760)
			throw exec_error("tcslinear_fresnel", "q_aux_fuel count incorrect (should be 8760): " + count);
		for (size_t i = 0; i < count; i++)
			fuel_usage_mmbtu += hourly_fuel[i];
		assign("system_heat_rate", 3.413); // samsim tcstrough_physical
		// www.unitjuggler.com/convert-energy-from-MMBtu-to-kWh.html
		assign("annual_fuel_usage", var_data((ssc_number_t)(fuel_usage_mmbtu * 293.297)));

		double kWhperkW = 0.0;
		double nameplate = as_double("system_capacity");
		double annual_energy = 0.0;
		for (int i = 0; i < 8760; i++)
			annual_energy += p_hourly_energy[i];
		if (nameplate > 0) kWhperkW = annual_energy / nameplate;
		assign("capacity_factor", var_data((ssc_number_t)(kWhperkW / 87.6)));
		assign("kwh_per_kw", var_data((ssc_number_t)kWhperkW));
	}

};

DEFINE_TCS_MODULE_ENTRY( tcsmslf, "CSP model using the molten salt linear fresnel TCS types.", 4 )