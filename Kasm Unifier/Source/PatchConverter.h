#pragma once
#include <JuceHeader.h>

class PatchConverter
{
public:
    String outputFolderPath;

    bool setLayerTitle = true;

#if 1
    String libraryName = "Kasm u-he Kasm";
#else
    String libraryName;
#endif

public:
    PatchConverter();
    int processFiles(const StringArray& filePaths);

protected:
    void test();

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
    std::unique_ptr<XmlElement> unifyPatchXml_Twin3;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PatchConverter)
};
