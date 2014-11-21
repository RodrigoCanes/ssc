#include "core.h"
#include "lib_weatherfile.h"
#include "lib_util.h"

// solarpilot header files
#include "AutoPilot_API.h"
#include "SolarField.h"
#include "IOUtil.h"


static var_info _cm_vtab_solarpilot[] = {
/*   VARTYPE           DATATYPE         NAME                         LABEL                                          UNITS     META        GROUP          REQUIRED_IF         CONSTRAINTS         UI_HINTS*/

	/*
	{ SSC_INPUT,        SSC_NUMBER,      "optimize",                  "Enable constrained optimization",            "0/1",    "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "range_tht_min",             "Tower height, minimum",                      "m",      "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "range_tht_max",             "Tower height, maximum",                      "m",      "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "range_rec_aspect_min",      "Receiver aspect ratio, minimum",             "",       "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "range_rec_aspect_max",      "Receiver aspect ratio, maximum",             "",       "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "range_rec_height_min",      "Receiver height, minimum",                   "m",      "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "range_rec_height_max",      "Receiver height, maximum",                   "m",      "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "flux_max",                  "Maximum flux",                               "kW/m2",  "",         "SolarPILOT",   "*",                "",                "" },
	*/

	{ SSC_INPUT,        SSC_STRING,      "solar_resource_file",       "Solar weather data file",                    "",       "",         "SolarPILOT",   "*",                "LOCAL_FILE",      "" },

	{ SSC_INPUT,        SSC_NUMBER,      "helio_width",               "Heliostat width",                            "m",      "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "helio_height",              "Heliostat height",                           "m",      "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "helio_optical_error",       "Optical error",                              "rad",    "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "helio_active_fraction",     "Active fraction of reflective area",         "frac",   "",         "SolarPILOT",   "*",                "",                "" },
    { SSC_INPUT,        SSC_NUMBER,      "dens_mirror",               "Ratio of reflective area to profile",        "frac",   "",         "SolarPILOT",   "*",                "",                "" },
    { SSC_INPUT,        SSC_NUMBER,      "helio_reflectance",         "Mirror reflectance",                         "frac",   "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "rec_absorptance",           "Absorptance",                                "frac",   "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "rec_height",                "Receiver height",                            "m",      "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "rec_aspect",                "Receiver aspect ratio (H/W)",                "frac",   "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "rec_hl_perm2",              "Receiver design heat loss",                  "kW/m2",  "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "q_design",                  "Receiver thermal design power",              "MW",     "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "dni_des",                   "Design-point DNI",                           "W/m2",   "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "land_max",                  "Max heliostat-dist-to-tower-height ratio",   "",       "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "land_min",                  "Min heliostat-dist-to-tower-height ratio",   "",       "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "h_tower",                   "Tower height",                               "m",      "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "c_atm_0",					  "Attenuation coefficient 0",                  "",       "",         "SolarPILOT",   "?=0.006789",       "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "c_atm_1",					  "Attenuation coefficient 1",                  "",       "",         "SolarPILOT",   "?=0.1046",         "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "c_atm_2",					  "Attenuation coefficient 2",                  "",       "",         "SolarPILOT",   "?=-0.0107",        "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "c_atm_3",					  "Attenuation coefficient 3",                  "",       "",         "SolarPILOT",   "?=0.002845",       "",                "" },
	
	{ SSC_INPUT,        SSC_NUMBER,      "n_facet_x",                 "Number of heliostat facets - X",             "",       "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "n_facet_y",                 "Number of heliostat facets - Y",             "",       "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "focus_type",                "Heliostat focus method",                     "",       "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "cant_type",                 "Heliostat cant method",                      "",       "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "n_flux_days",               "No. days in flux map lookup",                "",       "",         "SolarPILOT",   "?=8",              "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "delta_flux_hrs",            "Hourly frequency in flux map lookup",        "",       "",         "SolarPILOT",   "?=1",              "",                "" },

	{ SSC_INPUT,        SSC_NUMBER,      "calc_fluxmaps",             "Include fluxmap calculations",               "",       "",         "SolarPILOT",   "?=1",              "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "tower_fixed_cost",          "Tower fixed cost",                           "$",      "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "tower_exp",                 "Tower cost scaling exponent",                "",       "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "rec_ref_cost",              "Receiver reference cost",                    "$",      "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "rec_ref_area",              "Receiver reference area for cost scale",     "",       "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "rec_cost_exp",              "Receiver cost scaling exponent",             "",       "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "site_spec_cost",            "Site improvement cost",                      "$/m2",   "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "heliostat_spec_cost",       "Heliostat field cost",                       "$/m2",   "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "plant_spec_cost",           "Power cycle and BOS cost",                   "$/kWe",  "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "tes_spec_cost",             "Thermal energy storage cost",                "$/kWht", "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "land_spec_cost",            "Total land area cost",                       "$/acre", "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "contingency_rate",          "Contingency for cost overrun",               "%",      "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "sales_tax_rate",            "Sales tax rate",                             "%",      "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_INPUT,        SSC_NUMBER,      "sales_tax_frac",            "Percent of cost to which sales tax applies", "%",      "",         "SolarPILOT",   "*",                "",                "" },

    { SSC_INPUT,        SSC_NUMBER,      "is_optimize",               "Do SolarPILOT optimization",                 "",       "",         "SolarPILOT",   "?=0",              "",                "" },
    { SSC_INPUT,        SSC_NUMBER,      "flux_max",                  "Maximum allowable flux",                     "",       "",         "SolarPILOT",   "?=1000",           "",                "" },
    { SSC_INPUT,        SSC_NUMBER,      "opt_init_step",             "Optimization initial step size",             "",       "",         "SolarPILOT",   "?=0.05",           "",                "" },
    { SSC_INPUT,        SSC_NUMBER,      "opt_max_iter",              "Max. number iteration steps",                "",       "",         "SolarPILOT",   "?=200",            "",                "" },
    { SSC_INPUT,        SSC_NUMBER,      "opt_conv_tol",              "Optimization convergence tol",               "",       "",         "SolarPILOT",   "?=0.001",          "",                "" },
    { SSC_INPUT,        SSC_NUMBER,      "opt_algorithm",             "Optimization algorithm",                     "",       "",         "SolarPILOT",   "?=0",              "",                "" },


	/* outputs */
	{ SSC_OUTPUT,       SSC_ARRAY,       "opteff_zeniths",            "Optical efficiency table zenith angles",     "deg",    "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_OUTPUT,       SSC_ARRAY,       "opteff_azimuths",           "Optical efficiency table azimuth angles",    "deg",    "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_OUTPUT,       SSC_ARRAY,       "opteff_table",              "Optical efficiency (azi x zen)",             "frac",   "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_OUTPUT,       SSC_MATRIX,      "flux_table",                "Flux intensity table (flux(X) x (flux(y) x position)",  "frac", "", "SolarPILOT",  "*",                "",                "" },
	{ SSC_OUTPUT,       SSC_MATRIX,      "heliostat_positions",       "Heliostat positions (x,y)",                  "m",      "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_OUTPUT,       SSC_NUMBER,      "number_heliostats",         "Number of heliostats",                       "",        "",        "SolarPILOT",   "*",                "",                "" },
	{ SSC_OUTPUT,       SSC_NUMBER,      "base_land_area",            "Land area occupied by heliostats",           "acre",   "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_OUTPUT,       SSC_NUMBER,      "h_tower_opt",               "Optimized tower height",                     "m",      "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_OUTPUT,       SSC_NUMBER,      "rec_height_opt",            "Optimized receiver height",                  "m",      "",         "SolarPILOT",   "*",                "",                "" },
	{ SSC_OUTPUT,       SSC_NUMBER,      "rec_aspect_opt",            "Optimized receiver aspect ratio",            "-",      "",         "SolarPILOT",   "*",                "",                "" },
    	
	var_info_invalid };

static bool solarpilot_callback( simulation_info *siminfo, void *data );
static bool optimize_callback( simulation_info *siminfo, void *data );

#ifdef _MSC_VER
#define mysnprintf _snprintf
#else
#define mysnprintf snprintf
#endif

class cm_solarpilot : public compute_module
{
public:
	
	cm_solarpilot()
	{
		add_var_info( _cm_vtab_solarpilot );
	}

	void exec( ) throw( general_error )
	{
		AutoPilot_S sapi;

		sp_optimize opt;
		sp_ambient amb;
		sp_cost cost;
		sp_heliostats helios;
		sp_receivers recs;
		sp_layout layout;
	
		var_set V;
		ioutil::parseDefinitionArray(V);
	
		// define stuff and load default values
		opt.LoadDefaults(V);
		amb.LoadDefaults(V);
		cost.LoadDefaults(V);
		helios.resize(1);
		helios.front().LoadDefaults(V);
		recs.resize(1);
		recs.front().LoadDefaults(V);
		layout.LoadDefaults(V);

		// read inputs from SSC module
		
		bool isopt = as_boolean( "is_optimize" );
        if(isopt){
		    opt.flux_max = as_double("flux_max");
            opt.max_step = as_double("opt_init_step");
            opt.max_iter = as_integer("opt_max_iter");
            opt.converge_tol = as_double("opt_conv_tol");
            opt.method = as_integer("opt_algorithm");
            opt.is_optimize_bound = false;
        }
		/*
        opt.is_optimize_rec_aspect = isopt;
		opt.is_optimize_bound = isopt;
		opt.is_optimize_rec_height = isopt;
		opt.is_optimize_tht = isopt;
		opt.is_range_constr_aspect = isopt;
		opt.is_range_constr_bound = isopt;
		opt.is_range_constr_rech = isopt;
		opt.is_range_constr_tht = isopt;
		opt.range_tht[0] = as_double("range_tht_min");
		opt.range_tht[1] = as_double("range_tht_max");
		opt.range_rec_aspect[0] = as_double("range_rec_aspect_min");
		opt.range_rec_aspect[1] = as_double("range_rec_aspect_max");
		opt.range_rec_height[0] = as_double("range_rec_height_min");
		opt.range_rec_height[1] = as_double("range_rec_height_max");
		*/

		helios.front().width = as_double("helio_width");
		helios.front().height = as_double("helio_height");
		helios.front().optical_error = as_double("helio_optical_error"); 
		helios.front().active_fraction = as_double("helio_active_fraction") * as_double("dens_mirror");
		helios.front().reflectance = as_double("helio_reflectance");
		helios.front().npanels_h = as_integer("n_facet_y");
		helios.front().npanels_w = as_integer("n_facet_x");
		int cmap[5];
		cmap[0] = sp_heliostat::CANT_TYPE::FLAT;
		cmap[1] = sp_heliostat::CANT_TYPE::AT_SLANT;
		cmap[2] = sp_heliostat::CANT_TYPE::AT_DAY_HOUR;
		cmap[3] = sp_heliostat::CANT_TYPE::AT_DAY_HOUR;
		cmap[4] = sp_heliostat::CANT_TYPE::AT_DAY_HOUR;
		int cant_type = as_integer("cant_type");
		helios.front().cant_type = cmap[ cant_type ];
		if( cant_type == 2 ){
			helios.front().cant_settings.point_day = 81;  //spring equinox
			helios.front().cant_settings.point_hour = 12.;
		}
		else if( cant_type == 3 ){
			helios.front().cant_settings.point_day = 172;  //Summer solstice
			helios.front().cant_settings.point_hour = 12.;
		}
		else if( cant_type == 4){
			helios.front().cant_settings.point_day = 355;  //Winter solstice
			helios.front().cant_settings.point_hour = 12.;
		}

		int fmap[2];
		fmap[0] = sp_heliostat::FOCUS_TYPE::FLAT;
		fmap[1] = sp_heliostat::FOCUS_TYPE::AT_SLANT;
		helios.front().focus_type = fmap[ as_integer("focus_type") ];


		recs.front().absorptance = as_double("rec_absorptance");
		recs.front().height = as_double("rec_height");
		recs.front().aspect = as_double("rec_aspect");
		recs.front().q_hl_perm2 = as_double("rec_hl_perm2");
		
		layout.q_design = as_double("q_design");
		layout.dni_design = as_double("dni_des");
		layout.land_max = as_double("land_max");
		layout.land_min = as_double("land_min");
		layout.h_tower = as_double("h_tower");
		
		cost.tower_fixed_cost = as_double("tower_fixed_cost");
		cost.tower_exp = as_double("tower_exp");
		cost.rec_ref_cost = as_double("rec_ref_cost");
		cost.rec_ref_area = as_double("rec_ref_area");
		cost.rec_cost_exp = as_double("rec_cost_exp");
		cost.site_spec_cost = as_double("site_spec_cost");
		cost.heliostat_spec_cost = as_double("heliostat_spec_cost");
		cost.plant_spec_cost = as_double("plant_spec_cost");
		cost.tes_spec_cost = as_double("tes_spec_cost");
		cost.land_spec_cost = as_double("land_spec_cost");
		cost.contingency_rate = as_double("contingency_rate");
		cost.sales_tax_rate = as_double("sales_tax_rate");
		cost.sales_tax_rate = as_double("sales_tax_frac");
		
	
		//set up the weather data for simulation
		const char *wffile = as_string("solar_resource_file" );
		if ( !wffile ) throw exec_error( "solarpilot", "no weather file specified" );
		weatherfile wf( wffile );
		if ( !wf.ok() || wf.type() == weatherfile::INVALID ) throw exec_error("solarpilot", wf.error_message());

		
		amb.site_latitude = wf.lat;
		amb.site_longitude = wf.lon;
		amb.site_time_zone = wf.tz;
		amb.atten_model = sp_ambient::ATTEN_MODEL::USER_DEFINED;
		amb.user_atten_coefs.clear();
		amb.user_atten_coefs.push_back( as_double("c_atm_0") );
		amb.user_atten_coefs.push_back( as_double("c_atm_1") );
		amb.user_atten_coefs.push_back( as_double("c_atm_2") );
		amb.user_atten_coefs.push_back( as_double("c_atm_3") );

		vector<string> wfdata;
		wfdata.reserve( 8760 );
		char buf[1024];
		for( int i=0;i<8760;i++ )
		{
			if( !wf.read() )
				throw exec_error("solarpilot", "could not read data line " + util::to_string(i+1) + " of 8760 in weather file");

			mysnprintf(buf, 1023, "%d,%d,%d,%.2lf,%.1lf,%.1lf,%.1lf", wf.day, wf.hour, wf.month, wf.dn, wf.tdry, wf.pres/1000., wf.wspd);
			wfdata.push_back( std::string(buf) );
		}

		sapi.SetDetailCallback( solarpilot_callback, (void*)this);
		sapi.SetSummaryCallbackStatus(false);

		sapi.GenerateDesignPointSimulations( amb, V, wfdata );
	
        if(isopt){
            log("Optimizing...", SSC_WARNING, 0.);
            sapi.SetSummaryCallback( optimize_callback, (void*)this);
		    sapi.Setup(amb, cost, layout, helios, recs, true);
            
            if(! sapi.Optimize(opt, recs, layout) )
                return;

            sapi.SetSummaryCallbackStatus(false);
            sapi.PreSimCallbackUpdate();
            
        }
        else{
		    sapi.Setup(amb, cost, layout, helios, recs);
        }


        //assign("h_tower_opt", 222.222);
        assign("h_tower_opt", layout.h_tower);
        assign("rec_height_opt", recs.front().height);
        assign("rec_aspect_opt", recs.front().aspect);

        if(! sapi.CreateLayout() )
            return;
		
		//Collect the heliostat position data
		if( layout.heliostat_positions.size() > 0 )
		{
			ssc_number_t *hpos = allocate( "heliostat_positions", layout.heliostat_positions.size(), 2 );
			for(size_t i=0; i<layout.heliostat_positions.size(); i++){
				hpos[ i*2     ] = (float)layout.heliostat_positions.at(i).location.x;
				hpos[ i*2 + 1 ] = (float)layout.heliostat_positions.at(i).location.y;
			}
		}
		else
			throw exec_error("solarpilot", "failed to generate a heliostat field layout");

		//return the number of heliostats
		assign("number_heliostats", layout.heliostat_positions.size() ); 
		
		//return the land area
		assign("base_land_area", layout.land_area );

		//check if flux map calculations are desired
		if( as_boolean("calc_fluxmaps") ){

			sapi.SetDetailCallbackStatus(false);
			sapi.SetSummaryCallbackStatus(true);
			sapi.SetSummaryCallback( solarpilot_callback, (void*)this);
		
			//	sapi.Optimize(opt, recs, layout);
	
			//sp_optical_table opttab;
			sp_flux_table fluxtab;
			fluxtab.is_user_spacing = true;
			fluxtab.n_flux_days = as_integer("n_flux_days");
			fluxtab.delta_flux_hrs = as_integer("delta_flux_hrs");
		
			int nflux_x = 12, nflux_y = 1;
			if(! sapi.CalculateFluxMaps(fluxtab, nflux_x, nflux_y, true) )
                return;  //simulation failed or was cancelled.
            
			//collect the optical efficiency data and sun positions
			if ( fluxtab.zeniths.size() > 0 && fluxtab.azimuths.size() > 0
				&& fluxtab.efficiency.size() > 0 )
			{
				ssc_number_t *zeniths = allocate( "opteff_zeniths", fluxtab.zeniths.size() );
				for( size_t i=0;i<fluxtab.zeniths.size();i++ )
					zeniths[i] = (float)fluxtab.zeniths[i];

				ssc_number_t *azimuths = allocate( "opteff_azimuths", fluxtab.azimuths.size() );
				for( size_t i=0;i<fluxtab.azimuths.size();i++ )
					azimuths[i] = (float)fluxtab.azimuths[i];

				size_t nvals = fluxtab.efficiency.size();
				ssc_number_t *opteff = allocate( "opteff_table", nvals );
				for( size_t i=0;i<nvals;i++ )
					opteff[ i ] = (float)fluxtab.efficiency[i];
			}
			else
				throw exec_error("solarpilot", "failed to calculate a correct optical efficiency table");
		
			//collect the flux map data
			block_t<double> *flux_data = &fluxtab.flux_surfaces.front().flux_data;  //there should be only one flux stack for SAM
			if( flux_data->ncols() > 0 && flux_data->nlayers() > 0 ){
			
				ssc_number_t *fluxdata = allocate( "flux_table", nflux_y * flux_data->nlayers(), nflux_x );
			
				int cur_row=0;
			
				for( size_t i=0; i<flux_data->nlayers(); i++){
					for( int j=0; j<nflux_y; j++){
						for( int k=0; k<nflux_x; k++){
							fluxdata[cur_row * nflux_x + k] = (float)flux_data->at(j, k, i);
						}
						cur_row++;
					}
				}
			}
			else
				throw exec_error("solarpilot", "failed to calculate a correct flux map table");

		}
		else{
			//fluxmaps not required, so declare required variables and fill with zeros
			ssc_number_t *zeniths = allocate( "opteff_zeniths", 1 );
			ssc_number_t *azimuths = allocate( "opteff_azimuths", 1 );
			ssc_number_t *opteff = allocate( "opteff_table", 1 );
			ssc_number_t *fluxdata = allocate( "flux_table", 1, 1 );
		}

	}
};

static bool solarpilot_callback( simulation_info *siminfo, void *data )
{
	cm_solarpilot *cm = static_cast<cm_solarpilot*>( data );
	if ( !cm ) return false;
	float simprogress = (float)siminfo->getCurrentSimulation()/(float)(max(siminfo->getTotalSimulationCount(),1));

	return cm->update( *siminfo->getSimulationNotices(),
		simprogress*100.0f );

}

static bool optimize_callback( simulation_info *siminfo, void *data )
{
    cm_solarpilot *cm = static_cast<cm_solarpilot*>( data );
    if(! cm) return false;
    
    std::string notices = *siminfo->getSimulationNotices();
    cm->log( notices, SSC_WARNING, 0. );

}

DEFINE_MODULE_ENTRY( solarpilot, "SolarPILOT - CSP tower solar field layout tool.", 0 )