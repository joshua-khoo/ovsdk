#include "toolkit/ovtk_all.h"

using namespace OpenViBE;
using namespace OpenViBE::Kernel;
using namespace OpenViBEToolkit;

// ********************************************************************************************************************
//                                                                                                                    *
// VIM Replace string to easily add enumeration values :                                                              *
//                                                                                                                    *
// :%s/#define \([A-Za-z0-9_]\+\).*/	l_rTypeManager.registerEnumerationEntry(OV_TypeId_Stimulation, "\1", \1);/g   *
//                                                                                                                    *
// ********************************************************************************************************************

boolean OpenViBEToolkit::initialize(const IKernelContext& rKernelContext)
{
	ITypeManager& l_rTypeManager=rKernelContext.getTypeManager();

	initializeStimulationList(rKernelContext);

	// Register measurement units. See ovtk_defines.h for details.
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "?", OVTK_UNIT_Unspecified);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "-", OVTK_UNIT_Dimensionless);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "%", OVTK_UNIT_10_2_Percent);
//	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "percent", OVTK_UNIT_10_2_Percent);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "ppht", OVTK_UNIT_10_3_Parts_Per_Thousand);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "ppm", OVTK_UNIT_10_6_Parts_Per_Million);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "ppmd", OVTK_UNIT_10_9_Parts_Per_Milliard);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "ppb", OVTK_UNIT_10_12_Parts_Per_Billion);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "ppt", OVTK_UNIT_10_18_Parts_Per_Trillion);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "degree", OVTK_UNIT_Angle_Degree);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "rad", OVTK_UNIT_Angle_Radian);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "g g-1", OVTK_UNIT_Grams_Per_Gram);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "g kg-1", OVTK_UNIT_Grams_Per_Kilogram);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "mol mol-1", OVTK_UNIT_Moles_Per_Mole);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "l l-1", OVTK_UNIT_Litres_Per_Litre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "m m-3", OVTK_UNIT_Cubic_Metres_Per_Cubic_Metre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "m cm-3", OVTK_UNIT_Cubic_Metres_Per_Cubic_Centimetre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "vol %", OVTK_UNIT_Volume_Percent);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "pH", OVTK_UNIT_Ph);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "drop", OVTK_UNIT_Drop);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "rbc", OVTK_UNIT_Red_Blood_Cells);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "beat", OVTK_UNIT_Beat);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "breath", OVTK_UNIT_Breath);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "cell", OVTK_UNIT_Cell);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "cough", OVTK_UNIT_Cough);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "sigh", OVTK_UNIT_Sigh);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "%PCV", OVTK_UNIT_Percent_Of_Packed_Cell_Volume);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "m", OVTK_UNIT_Metres);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "yd", OVTK_UNIT_Yard);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "ft", OVTK_UNIT_Foot);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "in", OVTK_UNIT_Inch);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "lm-2", OVTK_UNIT_Litres_Per_Square_Metre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "m-1", OVTK_UNIT_Per_Metre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "m2", OVTK_UNIT_Square_Metres);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "in2", OVTK_UNIT_Square_Inch);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "m-2", OVTK_UNIT_Per_Square_Metre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "m3", OVTK_UNIT_Cubic_Metres);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "l", OVTK_UNIT_Litres);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "l_breath-1", OVTK_UNIT_Litres_Per_Breath);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "l_beat-1", OVTK_UNIT_Litres_Per_Beat);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "m-3", OVTK_UNIT_Per_Cubic_Metre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "l-1", OVTK_UNIT_Per_Litre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "g", OVTK_UNIT_Gram);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "lb", OVTK_UNIT_Pound);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "oz", OVTK_UNIT_Ounce);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "g-1", OVTK_UNIT_Per_Gram);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "gm", OVTK_UNIT_Gram_Metre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "g m m-2", OVTK_UNIT_Grams_Meter_Per_Square_Metre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "kg m2", OVTK_UNIT_Gram_Metre_Squared);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "kg m-2", OVTK_UNIT_Kilograms_Per_Square_Metre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "g m-3", OVTK_UNIT_Grams_Per_Cubic_Metre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "g cm-3", OVTK_UNIT_Grams_Per_Cubic_Centimetre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "g l-1", OVTK_UNIT_Grams_Per_Litre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "g cl-3", OVTK_UNIT_Grams_Per_Centilitre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "g dl-3", OVTK_UNIT_Grams_Per_Decilitre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "g ml-3", OVTK_UNIT_Grams_Per_Millilitre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "s", OVTK_UNIT_Second);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "min", OVTK_UNIT_Minute);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "h", OVTK_UNIT_Hour);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "d", OVTK_UNIT_Day);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "weeks", OVTK_UNIT_Weeks);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "mth", OVTK_UNIT_Months);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "y", OVTK_UNIT_Year);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "TOD", OVTK_UNIT_Time_Of_Day_Hh_Mm_Ss);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "DATE", OVTK_UNIT_Date_Yyyy_Mm_Dd);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "s-1", OVTK_UNIT_Per_Second);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "Hz", OVTK_UNIT_Hertz);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "min-1", OVTK_UNIT_Per_Minute);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "h-1", OVTK_UNIT_Per_Hour);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "d-1", OVTK_UNIT_Per_Day);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "week-1", OVTK_UNIT_Per_Week);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "mth-1", OVTK_UNIT_Per_Month);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "y-1", OVTK_UNIT_Per_Year);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "bpm", OVTK_UNIT_Beat_Per_Minute);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "puls min-1", OVTK_UNIT_Puls_Per_Minute);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "resp min-1", OVTK_UNIT_Respirations_Per_Minute);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "m s-1", OVTK_UNIT_Metres_Per_Second);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "l min-1 m-2", OVTK_UNIT_Litres_Per_Minute_Per_Square_Meter);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "m2 s-1", OVTK_UNIT_Square_Metres_Per_Second);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "m3 s-1", OVTK_UNIT_Cubic_Metres_Per_Second);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "m3 min-1", OVTK_UNIT_Cubic_Metres_Per_Minute);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "m3 h-1", OVTK_UNIT_Cubic_Metres_Per_Hour);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "m3 d-1", OVTK_UNIT_Cubic_Metres_Per_Day);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "l s-1", OVTK_UNIT_Litres_Per_Second);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "l min-1", OVTK_UNIT_Litres_Per_Minute);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "l h-1", OVTK_UNIT_Litres_Per_Hour);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "l d-1", OVTK_UNIT_Litres_Per_Day);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "l kg-1", OVTK_UNIT_Litres_Per_Kilogram);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "m3 kg-1", OVTK_UNIT_Cubic_Metres_Per_Kilogram);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "m Pa-1s-1", OVTK_UNIT_Meter_Per_Pascal_Second);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "l min-1 mmHG-1", OVTK_UNIT_Litre_Per_Min_Per_Millimetre_Of_Mercury);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "g s-1", OVTK_UNIT_Grams_Per_Second);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "g m-1", OVTK_UNIT_Grams_Per_Minute);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "g h-1", OVTK_UNIT_Grams_Per_Hour);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "g d-1", OVTK_UNIT_Grams_Per_Day);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "g kg-1 s-1", OVTK_UNIT_Grams_Per_Kilogram_Per_Second);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "g kg-1 m-1", OVTK_UNIT_Grams_Per_Kilogram_Per_Minute);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "g kg-1 h-1", OVTK_UNIT_Grams_Per_Kilogram_Per_Hour);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "g kg-1 d-1", OVTK_UNIT_Grams_Per_Kilogram_Per_Day);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "g l-1_s-1", OVTK_UNIT_Grams_Per_Litre_Per_Second);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "g l-1 m-1", OVTK_UNIT_Grams_Per_Litre_Per_Minute);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "g l-1 h-1", OVTK_UNIT_Grams_Per_Litre_Per_Hour);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "g l-1 d-1", OVTK_UNIT_Grams_Per_Litre_Per_Day);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "g m-1 s-1", OVTK_UNIT_Grams_Per_Meter_Per_Second);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "gm s-1", OVTK_UNIT_Gram_Metres_Per_Second);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "Ns", OVTK_UNIT_Newton_Seconds);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "N", OVTK_UNIT_Newton);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "dyn", OVTK_UNIT_Dyne);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "Pa", OVTK_UNIT_Pascal);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "mmHg", OVTK_UNIT_Millimetres_Of_Mercury);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "cm H2O", OVTK_UNIT_Centimetre_Of_Water);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "bar", OVTK_UNIT_Bar);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "J", OVTK_UNIT_Joules);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "eV", OVTK_UNIT_Electronvolts);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "W", OVTK_UNIT_Watts);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "Pa_s_m-3", OVTK_UNIT_Pascal_Second_Per_Cubic_Meter);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "Pa_s_l-1", OVTK_UNIT_Pascal_Second_Per_Litre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "dyne s cm-5", OVTK_UNIT_Dyne_Second_Per_Cm5);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "l cmH2O-1", OVTK_UNIT_Litre_Per_Centimetre_Of_Water);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "l mmHg-1", OVTK_UNIT_Litre_Per_Millimetre_Of_Mercury);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "l Pa-1", OVTK_UNIT_Litre_Per_Pascal);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "cmH2O l-1", OVTK_UNIT_Centimetre_Of_Water_Per_Litre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "mmHg l-1", OVTK_UNIT_Millimetre_Of_Mercury_Per_Litre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "Pa l-1", OVTK_UNIT_Pascal_Per_Litre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "A", OVTK_UNIT_Amperes);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "C", OVTK_UNIT_Coulombs);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "Ah", OVTK_UNIT_Amperes_Hour);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "A m-1", OVTK_UNIT_Amperes_Per_Metre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "V", OVTK_UNIT_Volts);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "Ohm", OVTK_UNIT_Ohms);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "Wm", OVTK_UNIT_Ohm_Metres);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "F", OVTK_UNIT_Farads);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "K", OVTK_UNIT_Kelvin);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "degC", OVTK_UNIT_Degree_Celcius);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "degF", OVTK_UNIT_Degree_Fahrenheit);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "K W-1", OVTK_UNIT_Kelvins_Per_Watt);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "cd", OVTK_UNIT_Candelas);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "osmole", OVTK_UNIT_Osmoles);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "mol", OVTK_UNIT_Moles);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "eq", OVTK_UNIT_Equivalent);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "osmol l-1", OVTK_UNIT_Osmoles_Per_Litre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "mol cm-3", OVTK_UNIT_Moles_Per_Cubic_Centimetre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "mol m-3", OVTK_UNIT_Moles_Per_Cubic_Metre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "mol l-1", OVTK_UNIT_Moles_Per_Litre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "mol ml-1", OVTK_UNIT_Moles_Per_Millilitre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "eq cm-3", OVTK_UNIT_Equivalents_Per_Cubic_Centimetre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "eq m-3", OVTK_UNIT_Equivalents_Per_Cubic_Metre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "eq l-1", OVTK_UNIT_Equivalents_Per_Litre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "eq ml-1", OVTK_UNIT_Equivalents_Per_Millilitre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "osmol kg-1", OVTK_UNIT_Osmoles_Per_Kilogram);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "mol kg-1", OVTK_UNIT_Moles_Per_Kilogram);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "mol s-1", OVTK_UNIT_Moles_Per_Second);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "mol min-1", OVTK_UNIT_Moles_Per_Minute);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "mol h-1", OVTK_UNIT_Moles_Per_Hour);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "mol d-1", OVTK_UNIT_Moles_Per_Day);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "eq s-1", OVTK_UNIT_Equivalents_Per_Second);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "eq min-1", OVTK_UNIT_Equivalents_Per_Minute);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "eq h-1", OVTK_UNIT_Equivalents_Per_Hour);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "eq d-1", OVTK_UNIT_Equivalents_Per_Day);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "mol kg-1 s-1", OVTK_UNIT_Moles_Per_Kilogram_Per_Second);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "mol kg-1 min-1", OVTK_UNIT_Moles_Per_Kilogram_Per_Minute);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "mol kg-1 h-1", OVTK_UNIT_Moles_Per_Kilogram_Per_Hour);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "mol kg-1 d-1", OVTK_UNIT_Moles_Per_Kilogram_Per_Day);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "eq kg-1 s-1", OVTK_UNIT_Equivalents_Per_Kilogram_Per_Second);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "eq kg-1 min-1", OVTK_UNIT_Equivalents_Per_Kilogram_Per_Minute);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "eq kg-1 h-1", OVTK_UNIT_Equivalents_Per_Kilogram_Per_Hour);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "eq kg-1 d-1", OVTK_UNIT_Equivalents_Per_Kilogram_Per_Day);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "i.u.", OVTK_UNIT_International_Unit);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "i.u. cm-3", OVTK_UNIT_International_Units_Per_Cubic_Centimetre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "i.u. m-3", OVTK_UNIT_International_Units_Per_Cubic_Meter);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "i.u. l-1", OVTK_UNIT_International_Units_Per_Litre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "i.u. ml-1", OVTK_UNIT_International_Units_Per_Millilitre);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "i.u. s-1", OVTK_UNIT_International_Units_Per_Second);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "i.u. min-1", OVTK_UNIT_International_Units_Per_Minute);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "i.u. h-1", OVTK_UNIT_International_Units_Per_Hour);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "i.u. d-1", OVTK_UNIT_International_Units_Per_Day);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "i.u. kg-1_s-1", OVTK_UNIT_International_Units_Per_Kilogram_Per_Second);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "i.u. kg-1_min-1", OVTK_UNIT_International_Units_Per_Kilogram_Per_Minute);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "i.u. kg-1_h-1", OVTK_UNIT_International_Units_Per_Kilogram_Per_Hour);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "i.u. kg-1_d-1", OVTK_UNIT_International_Units_Per_Kilogram_Per_Day);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "cmH2O l-1s-1", OVTK_UNIT_Centimetre_Of_Water_Per_Litre_Per_Second);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "l2s-1", OVTK_UNIT_Litre_Squared_Per_Second);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "cmH2O %-1", OVTK_UNIT_Centimetre_Of_Water_Per_Percent);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "dyne s m-2 cm-5", OVTK_UNIT_Dyne_Seconds_Per_Square_Meter_Per_Centimetre_To_The_Power_Of_5);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "mmHg %-1", OVTK_UNIT_Millimetres_Of_Mercury_Per_Percent);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "Pa %-1", OVTK_UNIT_Pascal_Per_Percent);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "B", OVTK_UNIT_Relative_Power_Decibel	);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "m s-2", OVTK_UNIT_Meter_Per_Second_Squared);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "rad s2-2", OVTK_UNIT_Radians_Per_Second_Squared);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "ft min-1", OVTK_UNIT_Foot_Per_Minute);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "in min-1", OVTK_UNIT_Inch_Per_Minute);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "step min-1", OVTK_UNIT_Step_Per_Minute);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "kcal", OVTK_UNIT_Kilocalories);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "rpm", OVTK_UNIT_Revolution_Per_Minute);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "V s-1", OVTK_UNIT_V_Per_S);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "m m-1", OVTK_UNIT_M_Per_M);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "km/h", OVTK_UNIT_Velocity_Kilometer_Per_Hour);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "g_s-2", OVTK_UNIT_Left_Stroke_Work_Index_Lswi);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "g_s-3", OVTK_UNIT_Indexed_Left_Cardiac_Work_Lcwi);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "mHg_s-1", OVTK_UNIT_Mhg_Per_S);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "mol l-1 mm", OVTK_UNIT_Millimol_Per_Liter_X_Millimeter);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "r.p.m", OVTK_UNIT_Rotations_Per_Minute);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "dyne*s*m*m cm-5", OVTK_UNIT_Dyne_Seconds_Square_Meter_Per_Centimetre_To_The_Power_Of_5);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "l m-2", OVTK_UNIT_Litres_Per_Square_Meter);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "T", OVTK_UNIT_Tesla);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_MeasurementUnit, "deg/s", OVTK_UNIT_Degree_Per_Second);

	//  Register measurement factors
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_Factor, "1e+24", OVTK_FACTOR_Yotta);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_Factor, "1e+21", OVTK_FACTOR_Zetta);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_Factor, "1e+18", OVTK_FACTOR_Exa);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_Factor, "1e+15", OVTK_FACTOR_Peta);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_Factor, "1e+12", OVTK_FACTOR_Tera); 
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_Factor, "1e+09", OVTK_FACTOR_Giga);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_Factor, "1e+06", OVTK_FACTOR_Mega);  
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_Factor, "1e+03", OVTK_FACTOR_Kilo);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_Factor, "1e+02", OVTK_FACTOR_Hecto);    
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_Factor, "1e+01", OVTK_FACTOR_Deca);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_Factor, "1e+00", OVTK_FACTOR_Base);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_Factor, "1e-01", OVTK_FACTOR_Deci);
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_Factor, "1e-02", OVTK_FACTOR_Centi);     
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_Factor, "1e-03", OVTK_FACTOR_Milli);   
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_Factor, "1e-06", OVTK_FACTOR_Micro);  
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_Factor, "1e-09", OVTK_FACTOR_Nano);   
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_Factor, "1e-12", OVTK_FACTOR_Pico);            
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_Factor, "1e-15", OVTK_FACTOR_Femto);  
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_Factor, "1e-18", OVTK_FACTOR_Atto);    
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_Factor, "1e-21", OVTK_FACTOR_Zepto); 
	l_rTypeManager.registerEnumerationEntry(OV_TypeId_Factor, "1e-24", OVTK_FACTOR_Yocto);

	l_rTypeManager.registerEnumerationType(OVTK_TypeId_ClassificationAlgorithm, "Classification algorithm");
	l_rTypeManager.registerEnumerationType(OVTK_TypeId_ClassificationStrategy, "Classification strategy");

	return true;
}

boolean OpenViBEToolkit::uninitialize(const IKernelContext& rKernelContext)
{
	return true;
}


