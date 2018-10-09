#ifndef PluginFixture_h
#define PluginFixture_h

#include <string>

#include <Plugin.h>
#include <Version.h>


class PluginFixture : public csm::Plugin {

  public:
    PluginFixture();
    ~PluginFixture();

    virtual std::string getPluginName() const;
    virtual std::string getManufacturer() const;
    virtual std::string getReleaseDate() const;
    virtual csm::Version getCsmVersion() const;
    virtual size_t getNumModels() const;
    virtual std::string getModelName(size_t modelIndex) const;
    virtual std::string getModelFamily(size_t modelIndex) const;
    virtual csm::Version getModelVersion(const std::string &modelName) const;
    virtual bool canModelBeConstructedFromState(const std::string &modelName,
                                                const std::string &modelState,
                                                csm::WarningList *warnings = NULL) const;
    virtual bool canModelBeConstructedFromISD(const csm::Isd &imageSupportData,
                                              const std::string &modelName,
                                              csm::WarningList *warnings = NULL) const;
    virtual csm::Model *constructModelFromState(const std::string &modelState,
                                                csm::WarningList *warnings = NULL) const;
    virtual csm::Model *constructModelFromISD(const csm::Isd &imageSupportData,
                                              const std::string &modelName,
                                              csm::WarningList *warnings = NULL) const;
    virtual std::string getModelNameFromModelState(const std::string &modelState,
                                                   csm::WarningList *warnings = NULL) const;
    virtual bool canISDBeConvertedToModelState(const csm::Isd &imageSupportData,
                                               const std::string &modelName,
                                               csm::WarningList *warnings = NULL) const;
    virtual std::string convertISDToModelState(const csm::Isd &imageSupportData,
                                               const std::string &modelName,
                                               csm::WarningList *warnings = NULL) const;

    // TODO when implementing, add any other necessary members.

private:
    static const PluginFixture m_registeredPlugin;
    static const std::string _PLUGIN_NAME;
    static const std::string _MANUFACTURER_NAME;
    static const std::string _RELEASE_DATE;
    static const int         _N_SENSOR_MODELS;
    static const int         _NUM_ISD_KEYWORDS;
    static const std::string _ISD_KEYWORD[];
    static const int         _NUM_STATE_KEYWORDS;
    static const std::string _STATE_KEYWORD[];
};

#endif
