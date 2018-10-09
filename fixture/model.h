#ifndef __SENSORMODEL_H
#define __SENSORMODEL_H

#include <RasterGM.h>
#include <SettableEllipsoid.h>
#include <CorrelationModel.h>


class FixtureSensorModel : public csm::RasterGM, virtual public csm::SettableEllipsoid
{
public:
   FixtureSensorModel();
   ~FixtureSensorModel();

   virtual csm::ImageCoord groundToImage(
      const csm::EcefCoord& groundPt,
      double desiredPrecision = 0.001,
      double* achievedPrecision = NULL,
      csm::WarningList* warnings = NULL) const;

   virtual csm::ImageCoordCovar groundToImage(
      const csm::EcefCoordCovar& groundPt,
      double desiredPrecision = 0.001,
      double* achievedPrecision = NULL,
      csm::WarningList* warnings = NULL) const;

   virtual csm::EcefCoord imageToGround(
      const csm::ImageCoord& imagePt,
      double height,
      double desiredPrecision = 0.001,
      double* achievedPrecision = NULL,
      csm::WarningList* warnings = NULL) const;

   virtual csm::EcefCoordCovar imageToGround(
      const csm::ImageCoordCovar& imagePt,
      double height,
      double heightVariance,
      double desiredPrecision = 0.001,
      double* achievedPrecision = NULL,
      csm::WarningList* warnings = NULL) const;

   virtual csm::EcefLocus imageToProximateImagingLocus(
      const csm::ImageCoord& imagePt,
      const csm::EcefCoord& groundPt,
      double desiredPrecision = 0.001,
      double* achievedPrecision = NULL,
      csm::WarningList* warnings = NULL) const;

   virtual csm::EcefLocus imageToRemoteImagingLocus(
      const csm::ImageCoord& imagePt,
      double desiredPrecision = 0.001,
      double* achievedPrecision = NULL,
      csm::WarningList* warnings = NULL) const;
   
   virtual csm::ImageCoord getImageStart() const;

   virtual csm::ImageVector getImageSize() const;

   virtual std::pair<csm::ImageCoord, csm::ImageCoord> getValidImageRange() const;

   virtual std::pair<double, double> getValidHeightRange() const;

   virtual csm::EcefVector getIlluminationDirection(const csm::EcefCoord& groundPt) const;

   virtual double getImageTime(const csm::ImageCoord& imagePt) const;

   virtual csm::EcefCoord getSensorPosition(const csm::ImageCoord& imagePt) const;

   virtual csm::EcefCoord getSensorPosition(double time) const;

   virtual csm::EcefVector getSensorVelocity(const csm::ImageCoord& imagePt) const;

   virtual csm::EcefVector getSensorVelocity(double time) const;


   virtual csm::RasterGM::SensorPartials computeSensorPartials(
      int index,
      const csm::EcefCoord& groundPt,
      double desiredPrecision = 0.001,
      double* achievedPrecision = NULL,
      csm::WarningList* warnings = NULL) const;

   virtual csm::RasterGM::SensorPartials computeSensorPartials(
      int index,
      const csm::ImageCoord& imagePt,
      const csm::EcefCoord& groundPt,
      double desiredPrecision = 0.001,
      double* achievedPrecision = NULL,
      csm::WarningList* warnings = NULL) const;

   virtual std::vector<csm::RasterGM::SensorPartials> computeAllSensorPartials(
      const csm::EcefCoord& groundPt,
      csm::param::Set pSet = csm::param::VALID,
      double desiredPrecision = 0.001,
      double* achievedPrecision = NULL,
      csm::WarningList* warnings = NULL) const;

   virtual std::vector<csm::RasterGM::SensorPartials> computeAllSensorPartials(
      const csm::ImageCoord& imagePt,
      const csm::EcefCoord& groundPt,
      csm::param::Set pSet = csm::param::VALID,
      double desiredPrecision = 0.001,
      double* achievedPrecision = NULL,
      csm::WarningList* warnings = NULL) const;

   virtual std::vector<double> computeGroundPartials(const csm::EcefCoord& groundPt) const;

   virtual const csm::CorrelationModel& getCorrelationModel() const;

   virtual std::vector<double> getUnmodeledCrossCovariance(
      const csm::ImageCoord& pt1,
      const csm::ImageCoord& pt2) const;

   virtual csm::EcefCoord getReferencePoint() const;

   virtual void setReferencePoint(const csm::EcefCoord& groundPt);

   virtual int getNumParameters() const;

   virtual std::string getParameterName(int index) const;

   virtual std::string getParameterUnits(int index) const;
   
   virtual bool hasShareableParameters() const;

   virtual bool isParameterShareable(int index) const;

   virtual csm::SharingCriteria getParameterSharingCriteria(int index) const;

   virtual double getParameterValue(int index) const;

   virtual void setParameterValue(int index, double value);

   virtual csm::param::Type getParameterType(int index) const;

   virtual void setParameterType(int index, csm::param::Type pType);

   virtual double getParameterCovariance(
      int index1,
      int index2) const;

   virtual void setParameterCovariance(
      int index1,
      int index2,
      double covariance);

   virtual int getNumGeometricCorrectionSwitches() const;

   virtual std::string getGeometricCorrectionName(int index) const;

   virtual void setGeometricCorrectionSwitch(int index,
      bool value,
      csm::param::Type pType);

   virtual bool getGeometricCorrectionSwitch(int index) const;

   virtual std::vector<double> getCrossCovarianceMatrix(
      const csm::GeometricModel& comparisonModel,
      csm::param::Set pSet = csm::param::VALID,
      const csm::GeometricModel::GeometricModelList& otherModels = csm::GeometricModel::GeometricModelList()) const;

   virtual csm::Version getVersion() const;

   virtual std::string getModelName() const;

   virtual std::string getPedigree() const;

   virtual std::string getImageIdentifier() const;

   virtual void setImageIdentifier(
      const std::string& imageId,
      csm::WarningList* warnings = NULL);

   virtual std::string getSensorIdentifier() const;

   virtual std::string getPlatformIdentifier() const;

   virtual std::string getCollectionIdentifier() const;

   virtual std::string getTrajectoryIdentifier() const;

   virtual std::string getSensorType() const;

   virtual std::string getSensorMode() const;

   virtual std::string getReferenceDateAndTime() const;
   
   virtual std::string getModelState() const;

   virtual void replaceModelState(const std::string& argState);



private:
   // This private form of the g2i method is used to ensure thread safety.
   virtual csm::ImageCoord groundToImage(
      const csm::EcefCoord& groundPt,
      const std::vector<double> &adjustments,
      double desiredPrecision = 0.001,
      double* achievedPrecision = NULL,
      csm::WarningList* warnings = NULL) const;
};
#endif
