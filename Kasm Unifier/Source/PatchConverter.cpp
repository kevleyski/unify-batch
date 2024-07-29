#pragma once
#include "PatchConverter.h"
#include "BinaryData.h"
#include "MyVstUtils.h"

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
    unifyPatchXml_Vital = parseXML(BinaryData::One_Vital_Layer_xml);
    unifyPatchXml_Serum = parseXML(BinaryData::One_Serum_Layer_xml);
    unifyPatchXml_Spire = parseXML(BinaryData::One_Spire_Layer_xml);
    unifyPatchXml_Twin3 = parseXML(BinaryData::One_Twin3_Layer_xml);
    unifyPatchXml_Pigments = parseXML(BinaryData::One_Pigments_Layer_xml);
    unifyPatchXml_Kontakt = parseXML(BinaryData::One_Kontakt_Layer_xml);
    unifyPatchXml_Omnisphere_Multi = parseXML(BinaryData::One_Omnisphere_Multi_Layer_xml);
    unifyPatchXml_Omnisphere_Patch = parseXML(BinaryData::One_Omnisphere_Patch_Layer_xml);
    unifyPatchXml_Battalion_Patch = parseXML(BinaryData::One_Battalion_Layer_xml);
    unifyPatchXml_Lion_Patch = parseXML(BinaryData::One_Lion_Layer_xml);
    unifyPatchXml_MassiveX_Patch = parseXML(BinaryData::One_Massive_X_Layer_xml);
    unifyPatchXml_DecentSampler_Patch = parseXML(BinaryData::One_Decent_Sampler_Layer_xml);
    unifyPatchXml_HALion7_Patch = parseXML(BinaryData::One_HALion7_Layer_xml);
    unifyPatchXml_UVIWorkstation = parseXML(BinaryData::One_UVIWorkstation_Layer_xml);
    unifyPatchXml_ReasonRack = parseXML(BinaryData::One_Reason_Rack_Layer_xml);
    unifyPatchXml_SurgeXT = parseXML(BinaryData::One_SurgeXT_Layer_xml);
    unifyPatchXml_Sylenth1 = parseXML(BinaryData::One_Sylenth1_Layer_xml);
    unifyPatchXml_Softube_Modular = parseXML(BinaryData::One_Softube_Modular_Layer_xml);
    unifyPatchXml_Arturia_AcidV = parseXML(BinaryData::One_Arturia_Acid_V_Layer_xml);
    unifyPatchXml_CherryVoltage_Modular = parseXML(BinaryData::One_Voltage_Modular_Layer_xml);
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

static char first16bytes[] = "VstW\x00\x00\x00\x08\x00\x00\x00\x01\x00\x00\x00\x00";
static String tuningJson(",\"tuning\":{\"default\":true,\"mapping_name\":\"\",\"reference_midi_note\":0.0,\"scale\":[0.0,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0],\"scale_start_midi_note\":60,\"tuning_name\":\"\"}");

String base64_encode(String str) {
    return (new MemoryBlock(str.toUTF8(), static_cast<size_t>(str.length())))->toBase64Encoding();
}

XmlElement* PatchConverter::processPresetFile(File inFile, String& newPatchNameOrErrorMessage)
{
    String presetName = inFile.getFileNameWithoutExtension();
    String presetExtension = inFile.getFileExtension();

    String prefix = "";
    String category = "";
    String author = "";
    String tags = "";

    // TODO: handle fxb (banks of fxp patch files)

    // TODO: parse JSON for metadata e.g. Vital
	if (0) {
		    // load patch JSON and tack on the "tuning" tags at the end
	    String patchJson = inFile.loadFileAsString().trimEnd().dropLastCharacters(1) + tuningJson + "}";

	    // parse out some metadata
	    var json = JSON::parse(patchJson);
	    String presetAuthor = json.getProperty("author", "Vital Audio").toString();
	    String presetComments = json.getProperty("comments", "").toString();
	    String presetName = json.getProperty("preset_name", inFile.getFileNameWithoutExtension()).toString();
	    String presetStyle = json.getProperty("preset_style", "").toString();
	    getCategoryAndPrefix(presetStyle, category, prefix);
	    newPatchNameOrErrorMessage = prefix + " - " + presetName;

	    // put patch JSON into a MemoryBlock
	    MemoryBlock mb(patchJson.getCharPointer(), patchJson.getNumBytesAsUTF8());

	    // wrap in a VST "FBCh" chunk in mb
	    MyVstConv vstConv;
	    vstConv.setChunkData(patchJson.getCharPointer(), patchJson.getNumBytesAsUTF8(), true);
	    vstConv.saveToFXBFile(mb, true);

	    // prepend Vital's 16-byte binary header and convert to base64
	    MemoryBlock mb2(first16bytes, 16);
	    mb2.setSize(16 + mb.getSize());
	    mb2.copyFrom(mb.getData(), 16, mb.getSize());
	    String b64state = mb2.toBase64Encoding();
	} else {

	    // load preset file as text and parse the metadata
	    String presetStr = inFile.loadFileAsString();
	    author = presetStr.fromFirstOccurrenceOf("Author:\n'", false, false).upToFirstOccurrenceOf("'", false, false);
	    String comment = presetStr.fromFirstOccurrenceOf("Usage:\n'", false, false).upToFirstOccurrenceOf("'", false, false);
	    tags = presetStr.fromFirstOccurrenceOf("Categories:\n'", false, false).upToFirstOccurrenceOf("'", false, false);
	    for (auto& wpc : wordPrefixCategory)
	    {
	        if (tags.containsIgnoreCase(wpc.word))
	        {
	            prefix = wpc.prefix;
	            category = wpc.category;
	            break;
	        }
	    }
	}

    if (prefix.isEmpty()) prefix = "UNKNOWN";
    if (category.isEmpty()) category = "UNKNOWN";
    if (author.isEmpty()) author = "Kev";
    if (tags.isEmpty()) tags = "Kasm";

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

    if (presetExtension.indexOf("h2p") >= 0) {
        // u-he
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
        } else {
            patchXml = new XmlElement(*unifyPatchXml_Zebralette);
            commentString = "Factory presets by u-he converted for Unify (Kasm)";
        }
    } else if (presetExtension.indexOf("vital") >= 0) {
        // Vital Synth
        patchXml = new XmlElement(*unifyPatchXml_Vital);
        commentString = "Factory presets by Vital converted for Unify (Kasm)";
    } else if (presetExtension.indexOf("fxp") >= 0) {
        if (patchFile.indexOf("CcnK") >= 0) {
            if (1 /* TODO */) {
                // Lennar Digital Sylenth1 synth
                patchXml = new XmlElement(*unifyPatchXml_Sylenth1);
                commentString = "Factory presets by Lennar Digital for Unify (Kasm)";
            } else {
                // SurgeXT
                patchXml = new XmlElement(*unifyPatchXml_SurgeXT);
                commentString = "Factory presets by SurgeXT Team converted for Unify (Kasm)";
            }
        } else {
            // Xfer Serum Synth
            patchXml = new XmlElement(*unifyPatchXml_Serum);
            commentString = "Factory presets by Xfer converted for Unify (Kasm)";
        }
    } else if (patchFile.indexOf("\"anticlick\"") >= 0) {
        // Lennar Digital Spire Synth
        patchXml = new XmlElement(*unifyPatchXml_Spire);
        commentString = "Factory presets by Reveal Studios Spire converted for Unify (Kasm)";
    } else if (patchFile.indexOf("FT3") >= 0) {
        // FabFilter Twin 3
        patchXml = new XmlElement(*unifyPatchXml_Twin3);
        commentString = "Factory presets by FabFilter converted for Unify (Kasm)";
    } else if (patchFile.indexOf("serial") >= 0) {
        // Arturia Instrument Patches
        if (patchFile.indexOf("Distortion_PostEQ_ParamEq_Cutoff4") >= 0) {
            // Arturia Acid V Synth
            patchXml = new XmlElement(*unifyPatchXml_Arturia_AcidV);
            commentString = "Factory presets by Arturia converted for Unify (Kasm)";
        } else {
            // Arturia Pigments Synth
            patchXml = new XmlElement(*unifyPatchXml_Pigments);
            commentString = "Factory presets by Arturia converted for Unify (Kasm)";
        }
    } else if (presetExtension.indexOf("nki") >= 0) {
        // Native Instrument
        patchXml = new XmlElement(*unifyPatchXml_Kontakt);
        commentString = "Factory presets by Native Instruments converted for Unify (Kasm)";
    } else if (presetExtension.indexOf("mlt_omn") >= 0) {
        // Spectronics Omnishere (multi)
        patchXml = new XmlElement(*unifyPatchXml_Omnisphere_Multi);
        commentString = "Factory presets by Omnishpere for Unify (Kasm)";
    } else if (presetExtension.indexOf("prt_omn") >= 0) {
        // Spectronics Omnishere (part/patch)
        patchXml = new XmlElement(*unifyPatchXml_Omnisphere_Patch);
        commentString = "Factory presets by Omnishpere converted for Unify (Kasm)";
    } else if (presetExtension.indexOf("uap") >= 0) {
        // Unfiltered Audio
        if (patchFile.indexOf("drum1distortenv1") >= 0) {
            patchXml = new XmlElement(*unifyPatchXml_Battalion_Patch);
            commentString = "Factory presets by Unfiltered Audio Battalion converted for Unify (Kasm)";
        } else {
            patchXml = new XmlElement(*unifyPatchXml_Lion_Patch);
            commentString = "Factory presets by Unfiltered Audio LION converted for Unify (Kasm)";
        }
    } else if (presetExtension.indexOf("nksf") >= 0) {
        // Native Instruments Massive X Synth
        patchXml = new XmlElement(*unifyPatchXml_MassiveX_Patch);
        commentString = "Factory presets by Native Instruments for Unify (Kasm)";
    } else if (presetExtension.indexOf("dspreset") >= 0) {
        // Decent Sampler
        patchXml = new XmlElement(*unifyPatchXml_DecentSampler_Patch);
        commentString = "Factory presets by Native Instruments for Unify (Kasm)";
    } else if (presetExtension.indexOf("vstprest") >= 0) {
        // Steinberg HALion7
        patchXml = new XmlElement(*unifyPatchXml_HALion7_Patch);
        commentString = "Factory presets by Steinberg for Unify (Kasm)";
    } else if (presetExtension.indexOf("uviws") >= 0) {
        // UVI Workstation
        patchXml = new XmlElement(*unifyPatchXml_UVIWorkstation);
        commentString = "Factory presets by UVI for Unify (Kasm)";
    } else if (presetExtension.indexOf("spt") >= 0) {
        // UVI Workstation
        patchXml = new XmlElement(*unifyPatchXml_Softube_Modular);
        commentString = "Factory presets by Softube for Unify (Kasm)";
    } else if (presetExtension.indexOf("voltagepreset") >= 0) {
        // UVI Workstation
        patchXml = new XmlElement(*unifyPatchXml_CherryVoltage_Modular);
        commentString = "Factory presets by Cherry Audio for Unify (Kasm)";
    } else {
        // Not yet supported
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

static struct { String presetStyle, category, prefix; } categoryTable[] =
{
    // Not yet used. If you want better categories than are encoded in Vital's "preset_style" attribute,
    // you'll need to analyze all the attribute values actually used in your preset collection and define
    // appropriate Unify category/prefix strings for each of them here. The following are example entries
    // used for a completely different plug-in.

    { "Arpegs", "Arpeggio", "BPM ARP" },
    { "Sequences", "Sequence", "BPM SEQ" },
    { "Textures", "Texture", "TEXT" },
    { "Basses", "Bass", "BASS" },
    { "Bells", "Bell", "BELL" },
    { "Chords", "Chord", "CHORD" },
    { "Effects", "SFX", "SFX" },
    { "Keys", "Keyboard", "KEY" },
    { "Leads", "Lead", "LEAD" },
    { "Organ", "Organ", "ORGAN" },
    { "Pads", "Pad", "PAD" },
    { "Hits", "Drum", "DRUM" },
};

void PatchConverter::getCategoryAndPrefix(String presetStyle, String& category, String& prefix)
{
    // Activate this code only after you have prepared a complete categoryTable[] above.
#if 0
    for (auto& cte : categoryTable)
    {
        if (cte.presetStyle == presetStyle)
        {
            category = cte.category;
            prefix = cte.prefix;
            return;
        }
    }
#endif

    category = presetStyle;
    prefix = presetStyle.isEmpty() ? "UNKNOWN" : presetStyle.toUpperCase();
}
