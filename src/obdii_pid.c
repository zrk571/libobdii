#include"../include/obdii_pid.h"

obdii_pid standard_pid_list[12] = {
  {SUPPORTED_PIDS,           "0100","Supported PIDS",            NULL,     4, NULL},
  {ENGINE_LOAD,              "0104", "Engine load",              "%",      1, NULL},
  {ENGINE_RPM,               "010C", "Engine RPM",               "tr/min", 2, NULL},
  {ENGINE_UPTIME,            "011F", "Engine uptime",            "sec",    2, NULL},
  {TEMP_COOLANT,             "0105", "Coolant temperature",      "°C",     1, NULL},
  {TEMP_AIR_INTAKE,          "010F", "Air intake temperature",   "°C" ,    1, NULL},
  {PRESSURE_FUEL_RAIL,       "010A", "Fuel rail pressure",       "kPa",    1, NULL},
  {PRESSURE_INTAKE_MANIFOLD, "010B", "Intake manifold pressure", "kPa",    1, NULL},
  {VEHICULE_SPEED,           "010D", "Vehicule speed",           "km/h",   1, NULL},
  {TIMING_ADVANCE,           "010E", "Timing advance",           "°",      1, NULL},
  {MASS_AIR_FLOW,            "0110", "Mass air flow (MAF)",      "gr/s",   2, NULL},
  {THROTTLE_POSITION,        "0111", "Throttle position",        "%",      1, NULL},
  {0,                        NULL,   NULL,                       NULL,     0, NULL}
};
