#include "model.h"

#include <iomanip>
#include <iostream>
#include <sstream>

#include <Error.h>
#include <Version.h>

using namespace std;

FixtureSensorModel::FixtureSensorModel() {

}


FixtureSensorModel::~FixtureSensorModel() {}

csm::ImageCoord FixtureSensorModel::groundToImage(const csm::EcefCoord &groundPt,
                              double desiredPrecision,
                              double *achievedPrecision,
                              csm::WarningList *warnings) const {

   csm::ImageCoord imagecoord = csm::ImageCoord(0,0);
   
   // Check that the pixel is actually in the image
   if ((groundPt.x < 0) || (groundPt.y < 0)) {
      csm::ImageCoord imagecoord = csm::ImageCoord(-1,-1);
      throw csm::Warning(
         csm::Warning::IMAGE_COORD_OUT_OF_BOUNDS,
         "The image coordinate is out of bounds of the image size.",
         "UsgsAstroLsSensorModel::groundToImage");
   };
  return imagecoord;
}

csm::ImageCoord FixtureSensorModel::groundToImage(
    const csm::EcefCoord&      groundPt,
    const std::vector<double>& adjustments,
    double                     desired_precision,
    double*                    achieved_precision,
    csm::WarningList*          warnings ) const {

  return csm::ImageCoord(0, 0);
}


csm::ImageCoordCovar FixtureSensorModel::groundToImage(const csm::EcefCoordCovar &groundPt,
                                   double desiredPrecision,
                                   double *achievedPrecision,
                                   csm::WarningList *warnings) const {

    throw csm::Error(csm::Error::UNSUPPORTED_FUNCTION,
      "Unsupported function",
      "FixtureSensorModel::groundToImage");
}


csm::EcefCoord FixtureSensorModel::imageToGround(const csm::ImageCoord &imagePt,
                                                 double height,
                                                 double desiredPrecision,
                                                 double *achievedPrecision,
                                                 csm::WarningList *warnings) const {

  return csm::EcefCoord(0, 0, 0);
}


csm::EcefCoordCovar FixtureSensorModel::imageToGround(const csm::ImageCoordCovar &imagePt, double height,
                                  double heightVariance, double desiredPrecision,
                                  double *achievedPrecision,
                                  csm::WarningList *warnings) const {
    throw csm::Error(csm::Error::UNSUPPORTED_FUNCTION,
      "Unsupported function",
      "FixtureSensorModel::imageToGround");
}


csm::EcefLocus FixtureSensorModel::imageToProximateImagingLocus(const csm::ImageCoord &imagePt,
                                                                const csm::EcefCoord &groundPt,
                                                                double desiredPrecision,
                                                                double *achievedPrecision,
                                                                csm::WarningList *warnings) const {
  // Ignore the ground point?
  return imageToRemoteImagingLocus(imagePt);
}


csm::EcefLocus FixtureSensorModel::imageToRemoteImagingLocus(const csm::ImageCoord &imagePt,
                                                             double desiredPrecision,
                                                             double *achievedPrecision,
                                                             csm::WarningList *warnings) const {

  return csm::EcefLocus(0,0,0,0,0,0);
}


csm::ImageCoord FixtureSensorModel::getImageStart() const {
  return csm::ImageCoord();
}


csm::ImageVector FixtureSensorModel::getImageSize() const {
  return csm::ImageVector();
}


std::pair<csm::ImageCoord, csm::ImageCoord> FixtureSensorModel::getValidImageRange() const {
    csm::ImageCoord min_pt(0, 0);
    csm::ImageCoord max_pt(1,1);
    return std::pair<csm::ImageCoord, csm::ImageCoord>(min_pt, max_pt);
}


std::pair<double, double> FixtureSensorModel::getValidHeightRange() const {
    return std::pair<double, double>(0, 1);
}


csm::EcefVector FixtureSensorModel::getIlluminationDirection(const csm::EcefCoord &groundPt) const {
  // ground (body-fixed) - sun (body-fixed) gives us the illumination direction.
  return csm::EcefVector(0,0,0);
}


double FixtureSensorModel::getImageTime(const csm::ImageCoord &imagePt) const {

  // check if the image point is in range
  if (imagePt.samp >= 0 &&
      imagePt.samp <= 1 &&
      imagePt.line >= 0 &&
      imagePt.line <= 1) {
    return 0;
  }
  else {
    throw csm::Error(csm::Error::BOUNDS,
                     "Image Coordinate out of Bounds",
                     "FixtureSensorModel::getImageTime");
  }
}


csm::EcefCoord FixtureSensorModel::getSensorPosition(const csm::ImageCoord &imagePt) const {

  // check if the image point is in range
  if (imagePt.samp >= 0 &&
      imagePt.samp <= 1 &&
      imagePt.line >= 0 &&
      imagePt.line <= 1) {
    return csm::EcefCoord();
  }
  else {
    throw csm::Error(csm::Error::BOUNDS,
                     "Image Coordinate out of Bounds",
                     "FixtureSensorModel::getSensorPosition");
  }
}

csm::EcefCoord FixtureSensorModel::getSensorPosition(double time) const {
    if (time == 0){
        return csm::EcefCoord();
    } else {
        std::string aMessage = "Valid image time is 0.0";
        throw csm::Error(csm::Error::BOUNDS,
                         aMessage,
                         "FixtureSensorModel::getSensorPosition");
    }
}


csm::EcefVector FixtureSensorModel::getSensorVelocity(const csm::ImageCoord &imagePt) const {
  // Make sure the passed coordinate is with the image dimensions.
  if (imagePt.samp < 0.0 || imagePt.samp > 1 ||
      imagePt.line < 0.0 || imagePt.line > 1) {
    throw csm::Error(csm::Error::BOUNDS, "Image coordinate out of bounds.",
                     "FixtureSensorModel::getSensorVelocity");
  }

  // Since this is a frame, just return the sensor velocity the ISD gave us.
  return csm::EcefVector(0,0,0);
}


csm::EcefVector FixtureSensorModel::getSensorVelocity(double time) const {
    if (time == 0){
        return csm::EcefVector(0,0,0);
    } else {
        std::string aMessage = "Valid image time is 0.0";
        throw csm::Error(csm::Error::BOUNDS,
                         aMessage,
                         "FixtureSensorModel::getSensorVelocity");
    }
}


csm::RasterGM::SensorPartials FixtureSensorModel::computeSensorPartials(int index,
                                           const csm::EcefCoord &groundPt,
                                           double desiredPrecision,
                                           double *achievedPrecision,
                                           csm::WarningList *warnings) const {

    csm::ImageCoord img_pt = groundToImage(groundPt, desiredPrecision, achievedPrecision);

    return computeSensorPartials(index, img_pt, groundPt, desiredPrecision, achievedPrecision);
}

csm::RasterGM::SensorPartials FixtureSensorModel::computeSensorPartials(int index,
                                          const csm::ImageCoord &imagePt,
                                          const csm::EcefCoord &groundPt,
                                          double desiredPrecision,
                                          double *achievedPrecision,
                                          csm::WarningList *warnings) const {

  csm::RasterGM::SensorPartials partials;
  partials.first = 0;
  partials.second = 0;

  return partials;

}

std::vector<csm::RasterGM::SensorPartials> FixtureSensorModel::computeAllSensorPartials(
    const csm::ImageCoord& imagePt,
    const csm::EcefCoord& groundPt,
    csm::param::Set pset,
    double desiredPrecision,
    double *achievedPrecision,
    csm::WarningList *warnings) const
    {
        std::vector<csm::RasterGM::SensorPartials> partials;
        for (int i=0;i<3;i++){
            csm::RasterGM::SensorPartials partial;
            partial.first = 0;
            partial.second = 0;
            partials.push_back(partial);
        }
        return partials;
    }

std::vector<csm::RasterGM::SensorPartials> FixtureSensorModel::computeAllSensorPartials(
    const csm::EcefCoord& groundPt,
    csm::param::Set pset,
    double desiredPrecision,
    double *achievedPrecision,
    csm::WarningList *warnings) const
    {
        csm::ImageCoord imagePt = groundToImage(groundPt,
                                    desiredPrecision, achievedPrecision, warnings);
        return computeAllSensorPartials(imagePt, groundPt,
                                    pset, desiredPrecision, achievedPrecision, warnings);
    }

std::vector<double> FixtureSensorModel::computeGroundPartials(const csm::EcefCoord &groundPt) const {
    std::vector<double> partials(6, 0.0);
    return partials;
}


const csm::CorrelationModel& FixtureSensorModel::getCorrelationModel() const {
    return csm::NoCorrelationModel();
}


std::vector<double> FixtureSensorModel::getUnmodeledCrossCovariance(const csm::ImageCoord &pt1,
                                                const csm::ImageCoord &pt2) const {

    throw csm::Error(csm::Error::UNSUPPORTED_FUNCTION,
      "Unsupported function",
      "FixtureSensorModel::getUnmodeledCrossCovariance");
}


csm::Version FixtureSensorModel::getVersion() const {
    return csm::Version(0,1,0);
}


std::string FixtureSensorModel::getModelName() const {
    return "FixtureSensorModel";
}


std::string FixtureSensorModel::getPedigree() const {
  throw csm::Error(csm::Error::UNSUPPORTED_FUNCTION,
                   "Unsupported function",
                   "FixtureSensorModel::getPedigree");
}


std::string FixtureSensorModel::getImageIdentifier() const {
  throw csm::Error(csm::Error::UNSUPPORTED_FUNCTION,
                   "Unsupported function",
                   "FixtureSensorModel::getImageIdentifier");
}


void FixtureSensorModel::setImageIdentifier(const std::string& imageId,
                                            csm::WarningList* warnings) {
  throw csm::Error(csm::Error::UNSUPPORTED_FUNCTION,
                   "Unsupported function",
                   "FixtureSensorModel::setImageIdentifier");
}


std::string FixtureSensorModel::getSensorIdentifier() const {
  throw csm::Error(csm::Error::UNSUPPORTED_FUNCTION,
                   "Unsupported function",
                   "FixtureSensorModel::getSensorIdentifier");
}


std::string FixtureSensorModel::getPlatformIdentifier() const {
  throw csm::Error(csm::Error::UNSUPPORTED_FUNCTION,
                   "Unsupported function",
                   "FixtureSensorModel::getPlatformIdentifier");
}


std::string FixtureSensorModel::getCollectionIdentifier() const {
  throw csm::Error(csm::Error::UNSUPPORTED_FUNCTION,
                   "Unsupported function",
                   "FixtureSensorModel::getCollectionIdentifier");
}


std::string FixtureSensorModel::getTrajectoryIdentifier() const {
  throw csm::Error(csm::Error::UNSUPPORTED_FUNCTION,
                   "Unsupported function",
                   "FixtureSensorModel::getTrajectoryIdentifier");
}


std::string FixtureSensorModel::getSensorType() const {
    return CSM_SENSOR_TYPE_EO;
}


std::string FixtureSensorModel::getSensorMode() const {
    return CSM_SENSOR_MODE_FRAME;
}


std::string FixtureSensorModel::getReferenceDateAndTime() const {
  throw csm::Error(csm::Error::UNSUPPORTED_FUNCTION,
                   "Unsupported function",
                   "FixtureSensorModel::getReferenceDateAndTime");
}


std::string FixtureSensorModel::getModelState() const {
    std::string state = "STATE";
    return state;
}


void FixtureSensorModel::replaceModelState(const std::string& modelState) {

}


csm::EcefCoord FixtureSensorModel::getReferencePoint() const {
  throw csm::Error(csm::Error::UNSUPPORTED_FUNCTION,
                   "Unsupported function",
                   "FixtureSensorModel::getReferencePoint");
}


void FixtureSensorModel::setReferencePoint(const csm::EcefCoord &groundPt) {
  throw csm::Error(csm::Error::UNSUPPORTED_FUNCTION,
                   "Unsupported function",
                   "FixtureSensorModel::setReferencePoint");
}


int FixtureSensorModel::getNumParameters() const {
  return 6;
}


std::string FixtureSensorModel::getParameterName(int index) const {
  return "Name";
}


std::string FixtureSensorModel::getParameterUnits(int index) const {
  if (index < 3) {
    return "m";
  }
  else {
    return "radians";
  }
}


bool FixtureSensorModel::hasShareableParameters() const {
  throw csm::Error(csm::Error::UNSUPPORTED_FUNCTION,
                   "Unsupported function",
                   "FixtureSensorModel::hasShareableParameters");
}


bool FixtureSensorModel::isParameterShareable(int index) const {
  throw csm::Error(csm::Error::UNSUPPORTED_FUNCTION,
                   "Unsupported function",
                   "FixtureSensorModel::isParameterShareable");
}


csm::SharingCriteria FixtureSensorModel::getParameterSharingCriteria(int index) const {
  throw csm::Error(csm::Error::UNSUPPORTED_FUNCTION,
                   "Unsupported function",
                   "FixtureSensorModel::getParameterSharingCriteria");
}


double FixtureSensorModel::getParameterValue(int index) const {
  return 0;
}


void FixtureSensorModel::setParameterValue(int index, double value) {
}


csm::param::Type FixtureSensorModel::getParameterType(int index) const {
  return csm::param::REAL;
}


void FixtureSensorModel::setParameterType(int index, csm::param::Type pType) {
}


double FixtureSensorModel::getParameterCovariance(int index1, int index2) const {
  throw csm::Error(csm::Error::UNSUPPORTED_FUNCTION,
                   "Unsupported function",
                   "FixtureSensorModel::getParameterCovariance");
}


void FixtureSensorModel::setParameterCovariance(int index1, int index2, double covariance) {
  throw csm::Error(csm::Error::UNSUPPORTED_FUNCTION,
                   "Unsupported function",
                   "FixtureSensorModel::setParameterCovariance");
}


int FixtureSensorModel::getNumGeometricCorrectionSwitches() const {
  throw csm::Error(csm::Error::UNSUPPORTED_FUNCTION,
                   "Unsupported function",
                   "FixtureSensorModel::getNumGeometricCorrectionSwitches");
}


std::string FixtureSensorModel::getGeometricCorrectionName(int index) const {
  throw csm::Error(csm::Error::UNSUPPORTED_FUNCTION,
                   "Unsupported function",
                   "FixtureSensorModel::getGeometricCorrectionName");
}


void FixtureSensorModel::setGeometricCorrectionSwitch(int index,
                                                      bool value,
                                                      csm::param::Type pType) {
  throw csm::Error(csm::Error::UNSUPPORTED_FUNCTION,
                   "Unsupported function",
                   "FixtureSensorModel::setGeometricCorrectionSwitch");
}


bool FixtureSensorModel::getGeometricCorrectionSwitch(int index) const {
  throw csm::Error(csm::Error::UNSUPPORTED_FUNCTION,
                   "Unsupported function",
                   "FixtureSensorModel::getGeometricCorrectionSwitch");
}


std::vector<double> FixtureSensorModel::getCrossCovarianceMatrix(
    const GeometricModel &comparisonModel,
    csm::param::Set pSet,
    const GeometricModelList &otherModels) const {
  throw csm::Error(csm::Error::UNSUPPORTED_FUNCTION,
                   "Unsupported function",
                   "FixtureSensorModel::getCrossCovarianceMatrix");
}