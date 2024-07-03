#pragma once
#include "PatchConverter.h"
#include "BinaryData.h"

static struct
{
    String word;
    String prefix;
    String category;
}
wordPrefixCategory[] =
{
    { "Other:Templates", "TEMPLATE", "Template"},
    { "Seq+Arp:Bass", "BPM BASS", "BPM Bass" },
    { "Seq+Arp:Plucks", "BPM PLUCK", "BPM Pluck"},
    { "Seq+Arp:Melodic", "BPM SEQ", "BPM Sequence" },
    { "Drums:Percussion", "PERC", "Percussion" },

    { "Drums", "DRUM", "Drum" },
    { "Guitars", "GTR", "Guitar" },
    { "Bass", "BASS", "Bass" },
    { "Brass", "BRASS", "Brass" },
    { "Hits", "HIT", "Hit" },
    { "Mallets", "PERC", "Percussion" },
    { "Plucks", "PLUCK", "Pluck" },
    { "Strings", "STRING", "String" },

    { "FX", "FX", "FX" },
    { "Pads", "PAD", "Pad" },
    { "Leads", "LEAD", "Lead" },
    { "Keys", "KEY", "Keyboard" },
};

PatchConverter::PatchConverter()
{
    unifyPatchXml_Diva = parseXML(BinaryData::One_Diva_Layer_xml);
    unifyPatchXml_Zebra2 = parseXML(BinaryData::One_Zebra2_Layer_xml);
    unifyPatchXml_ZebraHZ = parseXML(BinaryData::One_ZebraHZ_Layer_xml);
    unifyPatchXml_Zebralette = parseXML(BinaryData::One_Zebralette_Layer_xml);
    unifyPatchXml_Zebralette3 = parseXML(BinaryData::One_Zebralette3_Layer_xml);
    unifyPatchXml_Spire = parseXML(BinaryData::One_Spire_Layer_xml);
    unifyPatchXml_Twin3 = parseXML(BinaryData::One_Twin3_Layer_xml);
    unifyPatchXml_Pigments = parseXML(BinaryData::One_Pigments_Layer_xml);
    unifyPatchXml_Kontakt = parseXML(BinaryData::One_Kontakt_Layer_xml);
    unifyPatchXml_Omnisphere_Multi = parseXML(BinaryData::One_Omnisphere_Multi_Layer_xml);
    unifyPatchXml_Omnisphere_Patch = parseXML(BinaryData::One_Omnisphere_Patch_Layer_xml);

    //test();
}


void PatchConverter::test()
{
#if 0
    auto layerXml = unifyPatchXml->getChildByName("Layer");
    auto instXml = layerXml->getChildByName("Instrument");
    auto stateInfoString = instXml->getStringAttribute("stateInformation");

    MemoryBlock mb;
    bool b64ok = mb.fromBase64Encoding(stateInfoString);

    auto vst3stateXml = AudioProcessor::getXmlFromBinary(mb.getData(), mb.getSize());

    //File outFile("~/unify-batch~/test.xml");
    //vst3stateXml->writeTo(outFile);

    auto icDataString = vst3stateXml->getChildByName("IComponent")->getAllSubText();
    b64ok = mb.fromBase64Encoding(icDataString);
    File icDataFile("~/unify-batch\\Zebralette3 Unifier\\Assets\\ic.txt");
    icDataFile.replaceWithData(mb.getData(), mb.getSize());

    auto ecDataString = vst3stateXml->getChildByName("IEditController")->getAllSubText();
    b64ok = mb.fromBase64Encoding(ecDataString);
    File ecDataFile("~/unify-batch\\Zebralette3 Unifier\\Assets\\ec.txt");
    ecDataFile.replaceWithData(mb.getData(), mb.getSize());
#endif

#if 0
    MemoryBlock mb;
    File unifyPatchFile("~/unify-batch/Presets/Unify\\Unified - PA Derailer\\Patches\\ATMO - Gazer.unify");
    unifyPatchFile.loadFileAsData(mb);
    auto patchXml = AudioProcessor::getXmlFromBinary(mb.getData(), mb.getSize());

    auto layerXml = patchXml->getChildByName("Layer");
    auto instXml = layerXml->getChildByName("Instrument");
    auto stateInfoString = instXml->getStringAttribute("stateInformation");
    bool b64ok = mb.fromBase64Encoding(stateInfoString);
    auto vst3stateXml = AudioProcessor::getXmlFromBinary(mb.getData(), mb.getSize());
    auto icXml = vst3stateXml->getChildByName("IComponent");
    auto icDataString = icXml->getAllSubText();
    mb.setSize(0);
    b64ok = mb.fromBase64Encoding(icDataString);
    auto presetXml = AudioProcessor::getXmlFromBinary(mb.getData(), mb.getSize());
    DBG(presetXml->toString());
#endif
}

int PatchConverter::processFiles(const StringArray& filePaths)
{
    if (outputFolderPath.isNotEmpty())
    {
        outputFolder = File(outputFolderPath);
        outputFolder.createDirectory();
    }

    int fileCount = 0;
    for (auto filePath : filePaths)
    {
        File file(filePath);
        processFile(file, fileCount);
    }
    return fileCount;
}

void PatchConverter::processFile(File file, int& fileCount)
{
    DBG(file.getFileName());

    if (file.isDirectory())
    {
        for (DirectoryEntry entry : RangedDirectoryIterator(file, false, "*", File::findFilesAndDirectories))
            processFile(entry.getFile(), fileCount);
    }
    else if (file.getFileExtension() != ".unify")
    {
        String newPatchNameOrErrorMessage;
        std::unique_ptr<XmlElement> patchXml(processPresetFile(file, newPatchNameOrErrorMessage));
        if (patchXml)
            saveUnifyPatch(file, newPatchNameOrErrorMessage, patchXml.get());
        else {
            // AlertWindow::showMessageBox(MessageBoxIconType::WarningIcon, "Conversion error",file.getFileName() + ": " + newPatchNameOrErrorMessage);
        }

        fileCount++;
    }
}

String base64_encode(String str) {
    return (new MemoryBlock(str.toUTF8(), static_cast<size_t>(str.length())))->toBase64Encoding();
}

XmlElement* PatchConverter::processPresetFile(File inFile, String& newPatchNameOrErrorMessage)
{
#if 0
    return nullptr;
#else
    String presetName = inFile.getFileNameWithoutExtension();
    String presetExtension = inFile.getFileExtension();

    // load preset file as text and parse the metadata
    String presetStr = inFile.loadFileAsString();
    String author = presetStr.fromFirstOccurrenceOf("Author:\n'", false, false).upToFirstOccurrenceOf("'", false, false);
    String comment = presetStr.fromFirstOccurrenceOf("Usage:\n'", false, false).upToFirstOccurrenceOf("'", false, false);
    String tags = presetStr.fromFirstOccurrenceOf("Categories:\n'", false, false).upToFirstOccurrenceOf("'", false, false);
    String prefix = "UNKNOWN";
    String category = "UNKNOWN";
    for (auto& wpc : wordPrefixCategory)
    {
        if (tags.containsIgnoreCase(wpc.word))
        {
            prefix = wpc.prefix;
            category = wpc.category;
            break;
        }
    }

    if (prefix.indexOf("UNKNOWN") == 0) {
        newPatchNameOrErrorMessage = "KASM - " + presetName;
    } else {
        newPatchNameOrErrorMessage = prefix + " - " + presetName;
    }

    // load preset file as data and convert to base64
    MemoryBlock mb;
    inFile.loadFileAsData(mb);
    auto b64state = mb.toBase64Encoding();

    // assemble a VST3PluginState XML structure, with this base64 state-string
    std::unique_ptr<XmlElement> vst3stateXml(new XmlElement("VST3PluginState"));
    auto iComponentXml = new XmlElement("IComponent");
    vst3stateXml->addChildElement(iComponentXml);
    iComponentXml->addTextElement(b64state);
    //auto eComponentXml = new XmlElement("IEditController");
    //vst3stateXml->addChildElement(eComponentXml);
    //eComponentXml->addTextElement(b64state);

    // now base64 encode that entire XML string, as new binary state
    AudioProcessor::copyXmlToBinary(*vst3stateXml, mb);
    b64state = mb.toBase64Encoding();

    // assemble new Unify patch XML
    XmlElement* patchXml;

    // determine which Unify base VST3 patch we'll amend
    String patchFile = inFile.loadFileAsString();
    String commentString;

    if (patchFile.indexOf("#AM=Diva") >= 0) {
        patchXml = new XmlElement(*unifyPatchXml_Diva);
        commentString = "Factory presets by u-he converted for Unify (Kasm)";
    } else if (patchFile.indexOf("#AM=ZebraHZ") >= 0) {
        patchXml = new XmlElement(*unifyPatchXml_ZebraHZ);
        commentString = "Factory presets by u-he converted for Unify (Kasm)";
    } else if (patchFile.indexOf("#AM=Zebra2") >= 0) {
        patchXml = new XmlElement(*unifyPatchXml_Zebra2);
        commentString = "Factory presets by u-he converted for Unify (Kasm)";
    } else if (patchFile.indexOf("#AM=Zebralette3") >= 0) {
        patchXml = new XmlElement(*unifyPatchXml_Zebralette3);
        commentString = "Factory presets by u-he converted for Unify (Kasm)";
    } else if (patchFile.indexOf("#AM=Zebralette") >= 0) {
        patchXml = new XmlElement(*unifyPatchXml_Zebralette);
        commentString = "Factory presets by u-he converted for Unify (Kasm)";
    } else if (patchFile.indexOf("\"anticlick\"") >= 0) {
        patchXml = new XmlElement(*unifyPatchXml_Spire);
        commentString = "Factory presets by Reveal Studios Spire converted for Unify (Kasm)";
    } else if (patchFile.indexOf("FT3") >= 0) {
        patchXml = new XmlElement(*unifyPatchXml_Twin3);
        commentString = "Factory presets by FabFilter converted for Unify (Kasm)";
    } else if (patchFile.indexOf("serial") >= 0) {
        patchXml = new XmlElement(*unifyPatchXml_Pigments);
        commentString = "Factory presets by Arturia converted for Unify (Kasm)";
    } else if (presetExtension.indexOf("nki") >= 0) {
        patchXml = new XmlElement(*unifyPatchXml_Kontakt);
        commentString = "Factory presets by Native Instruments converted for Unify (Kasm)";
    } else if (presetExtension.indexOf("mlt_omn") >= 0) {
        patchXml = new XmlElement(*unifyPatchXml_Omnisphere_Multi);
        commentString = "Factory presets by Omnishpere for Unify (Kasm)";
    } else if (presetExtension.indexOf("prt_omn") >= 0) {
        patchXml = new XmlElement(*unifyPatchXml_Omnisphere_Patch);
        commentString = "Factory presets by Omnishpere converted for Unify (Kasm)";
    } else {
        return NULL;
    }

    auto layerXml = patchXml->getChildByName("Layer");
    layerXml->setAttribute("layerTitle", newPatchNameOrErrorMessage);
    auto instXml = layerXml->getChildByName("Instrument");
    instXml->setAttribute("stateInformation", b64state);
    auto pmXml = patchXml->getChildByName("PresetMetadata");
    pmXml->setAttribute("name", newPatchNameOrErrorMessage);
    pmXml->setAttribute("author", author.isEmpty() ? "Kasm" : author);
    pmXml->setAttribute("category", category);
    pmXml->setAttribute("tags", tags);
    pmXml->setAttribute("comment", commentString);
    if (libraryName.isNotEmpty()) pmXml->setAttribute("library", libraryName);

    return patchXml;
#endif
}

void PatchConverter::saveUnifyPatch(File inFile, String patchName, XmlElement* patchXml)
{
    MemoryBlock outBlock;
    AudioProcessor::copyXmlToBinary(*patchXml, outBlock);

    if (outputFolderPath.isNotEmpty())
    {
        // Save to output folder
        File outFile = File(outputFolderPath).getChildFile(patchName + ".unify");
        outFile.create();
        outFile.replaceWithData(outBlock.getData(), outBlock.getSize());
    }
}
