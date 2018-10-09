#include "plugin.h"

#include "model.h"

#include <cstdlib>
#include <string>

#include <csm.h>
#include <Error.h>
#include <Plugin.h>
#include <Warning.h>
#include <Version.h>

#ifdef _WIN32
# define DIR_DELIMITER_STR "\\"
#else
# define DIR_DELIMITER_STR  "/"
#endif


// Declaration of static variables
const std::string PluginFixture::_PLUGIN_NAME = "PluginFixture";
const std::string PluginFixture::_MANUFACTURER_NAME = "Fakers";
const std::string PluginFixture::_RELEASE_DATE = "20170425";
const int         PluginFixture::_N_SENSOR_MODELS = 1;
const int         PluginFixture::_NUM_ISD_KEYWORDS = 0;
const std::string PluginFixture::_ISD_KEYWORD[] = {};

const int         PluginFixture::_NUM_STATE_KEYWORDS = 0;
const std::string PluginFixture::_STATE_KEYWORD[] = {};


// Static Instance of itself
const PluginFixture PluginFixture::m_registeredPlugin;

PluginFixture::PluginFixture() {
}


PluginFixture::~PluginFixture() {
}


std::string PluginFixture::getPluginName() const {
  return _PLUGIN_NAME;
}


std::string PluginFixture::getManufacturer() const {
  return _MANUFACTURER_NAME;
}


std::string PluginFixture::getReleaseDate() const {
  return _RELEASE_DATE;
}


csm::Version PluginFixture::getCsmVersion() const {
  return CURRENT_CSM_VERSION;
}


size_t PluginFixture::getNumModels() const {
  return _N_SENSOR_MODELS;
}


std::string PluginFixture::getModelName(size_t modelIndex) const {
  return "FixtureSensorModel";
}


std::string PluginFixture::getModelFamily(size_t modelIndex) const {
  return CSM_RASTER_FAMILY;
}


csm::Version PluginFixture::getModelVersion(const std::string &modelName) const {
  return csm::Version(1, 0, 0);
}


bool PluginFixture::canModelBeConstructedFromState(const std::string &modelName,
                                                const std::string &modelState,
                                                csm::WarningList *warnings) const {
  bool constructible = true;
  if (modelName == "False") {
    constructible = false;
  }
  return constructible;
}


bool PluginFixture::canModelBeConstructedFromISD(const csm::Isd &imageSupportData,
                                              const std::string &modelName,
                                              csm::WarningList *warnings) const {
  return canISDBeConvertedToModelState(imageSupportData, modelName, warnings);
}


csm::Model *PluginFixture::constructModelFromState(const std::string& modelState,
                                                csm::WarningList *warnings) const {
    csm::Model *sensor_model = 0;

    // Instantiate the model
    FixtureSensorModel* mdsensor_model = new FixtureSensorModel();
 
sensor_model = mdsensor_model;
return sensor_model;
}


csm::Model *PluginFixture::constructModelFromISD(const csm::Isd &imageSupportData,
                                              const std::string &modelName,
                                              csm::WarningList *warnings) const {
                                            
  if (modelName == "False") {
    std::string errorMessage;
    throw csm::Error(csm::Error::SENSOR_MODEL_NOT_CONSTRUCTIBLE,
                  "IntentionalError",
                  "PluginFixture::constructModelFromISD()");
  }

  FixtureSensorModel *sensorModel = new FixtureSensorModel();
  return sensorModel;
}


std::string PluginFixture::getModelNameFromModelState(const std::string &modelState,
                                                   csm::WarningList *warnings) const {

  if (modelState == "False"){
    throw csm::Error(csm::Error::INVALID_SENSOR_MODEL_STATE,
                  "IntentionalError",
                  "PluginFixture::constructModelFromISD()");
  }
  return "FixtureSensorModel";
}


bool PluginFixture::canISDBeConvertedToModelState(const csm::Isd &imageSupportData,
                                               const std::string &modelName,
                                               csm::WarningList *warnings) const {
  bool convertible = true;
  if (modelName == "False"){
    convertible = false;
  }
  
  return convertible;
}


std::string PluginFixture::convertISDToModelState(const csm::Isd &imageSupportData,
                                               const std::string &modelName,
                                               csm::WarningList *warnings) const {
  csm::Model* sensor_model = constructModelFromISD(
                             imageSupportData, modelName);

  return sensor_model->getModelState();
}
