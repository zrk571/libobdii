#include"../include/obdii_pid.h"

obdii_pid standard_pid_list[12] = {
  {SUPPORTED_PIDS_1,         "0100", 0, "Supported PIDS_1",          NULL,     NULL},
  {ENGINE_LOAD,              "0104", 0, "Engine load",              "%",      &load},
  {ENGINE_RPM,               "010C", 0, "Engine RPM",               "tr/min", &rpm},
  {ENGINE_OIL_TEMP,          "015C", 2, "Engine oil temperature",   "°C",     &engine_oil_temp},
  {TEMP_COOLANT,             "0105", 0, "Coolant temperature",      "°C",     &engine_coolant_temp},
  {TEMP_AIR_INTAKE,          "010F", 0, "Air intake temperature",   "°C" ,    &engine_intake_temp},
  {PRESSURE_FUEL_RAIL,       "010A", 0, "Fuel rail pressure",       "kPa",    NULL},
  {PRESSURE_INTAKE_MANIFOLD, "010B", 0, "Intake manifold pressure", "kPa",    NULL},
  {VEHICULE_SPEED,           "010D", 0, "Vehicule speed",           "km/h",   &speed},
  {TIMING_ADVANCE,           "010E", 0, "Timing advance",           "°",      NULL},
  {MASS_AIR_FLOW,            "0110", 0, "Mass air flow (MAF)",      "gr/s",   &maf},
  {THROTTLE_POSITION,        "0111", 0, "Throttle position",        "%",      &throttle_position}//,
//  {0,                        NULL,   NULL,                       NULL,     NULL}
};
