#pragma once
#include <JuceHeader.h>

#define LIBRARY_NAME "Kasm"

class PatchConverter
{
public:
    String outputFolderPath;

    bool setLayerTitle = true;

#if 1
    String libraryName = LIBRARY_NAME;
#else
    String libraryName;
#endif

public:
    PatchConverter();
    int processFiles(const StringArray& filePaths);

protected:
    void test();

    void getCategoryAndPrefix(String, String&, String&);

    void processFile(File, int& fileCount);
    XmlElement* processPresetFile(File inFile, String& newPatchNameOrErrorMessage);

    void saveUnifyPatch(File inFile, String patchName, XmlElement* patchXml);

private:
    File outputFolder;
    std::unique_ptr<XmlElement> unifyPatchXml_Diva;
    std::unique_ptr<XmlElement> unifyPatchXml_Zebra2;
    std::unique_ptr<XmlElement> unifyPatchXml_ZebraHZ;
    std::unique_ptr<XmlElement> unifyPatchXml_Zebralette;
    std::unique_ptr<XmlElement> unifyPatchXml_Zebralette3;
    std::unique_ptr<XmlElement> unifyPatchXml_Spire;
    std::unique_ptr<XmlElement> unifyPatchXml_Vital;
    std::unique_ptr<XmlElement> unifyPatchXml_Serum;
    std::unique_ptr<XmlElement> unifyPatchXml_Twin3;
    std::unique_ptr<XmlElement> unifyPatchXml_Pigments;
    std::unique_ptr<XmlElement> unifyPatchXml_Kontakt;
    std::unique_ptr<XmlElement> unifyPatchXml_Omnisphere_Multi;
    std::unique_ptr<XmlElement> unifyPatchXml_Omnisphere_Patch;
    std::unique_ptr<XmlElement> unifyPatchXml_Battalion_Patch;
    std::unique_ptr<XmlElement> unifyPatchXml_Lion_Patch;
    std::unique_ptr<XmlElement> unifyPatchXml_MassiveX_Patch;
    std::unique_ptr<XmlElement> unifyPatchXml_DecentSampler_Patch;
    std::unique_ptr<XmlElement> unifyPatchXml_HALion7_Patch;
    std::unique_ptr<XmlElement> unifyPatchXml_UVIWorkstation;
    std::unique_ptr<XmlElement> unifyPatchXml_ReasonRack;
    std::unique_ptr<XmlElement> unifyPatchXml_SurgeXT;
    std::unique_ptr<XmlElement> unifyPatchXml_Sylenth1;
    std::unique_ptr<XmlElement> unifyPatchXml_Softube_Modular;
    std::unique_ptr<XmlElement> unifyPatchXml_Arturia_AcidV;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PatchConverter)
};
