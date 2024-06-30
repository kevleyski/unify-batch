#include "MainComponent.h"
#include <stdlib.h>
#include <time.h>

const String DEFAULT_UNIFY_PATCHES_FOLDER_PATH = "/Library/Audio/Presets/PlugInGuru/Unify";

MainComponent::MainComponent()
{
    message = "Select Unify patch folder to generate, then drag plugin presets (.h2p files) or folders of patches here...";

	// Output path
	outputPathLabel.setJustificationType(Justification::topLeft);
	outputPathLabel.setText("(click folder below to change)", dontSendNotification);
	addAndMakeVisible(outputPathLabel);

	outputFolderPathLabel.setText("Output Folder:", dontSendNotification);
	outputFolderPathLabel.setJustificationType(Justification::right);
    outputFolderPath.setButtonText(DEFAULT_UNIFY_PATCHES_FOLDER_PATH);

	outputFolderPathLabel.attachToComponent(&outputFolderPath, true);
	addAndMakeVisible(outputFolderPath);
	outputFolderPath.onClick = [this]()
	{
		FileChooser chooser("Select output folder");
		if (chooser.browseForDirectory())
		{
			String path = chooser.getResult().getFullPathName();
            if (path.length() == 0) {
                path = DEFAULT_UNIFY_PATCHES_FOLDER_PATH;
            }
			outputFolderPath.setButtonText(path);
			patchConverter.outputFolderPath = path;
		}
	};

    setSize(800, 230);
}

void MainComponent::resized()
{
    auto bounds = getLocalBounds().reduced(40, 20);
	bounds.removeFromTop(80);		// space for message (and a gap below)

	bounds.removeFromLeft(120);		// space for labels
	bounds.removeFromRight(20);		// balance space on right

	bounds.removeFromTop(30);
	outputPathLabel.setBounds(bounds.removeFromTop(26));
	auto row = bounds.removeFromTop(24);
	outputFolderPath.setBounds(row);
}

void MainComponent::paint(Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

	auto messageBox = getLocalBounds().reduced(40, 20).removeFromTop(60);

	g.setFont(Font(16.0f));
	g.setColour(Colours::white);
	g.drawText(message, messageBox, Justification::centred);
}

bool MainComponent::isInterestedInFileDrag(const StringArray&)
{
    return true;
}

void MainComponent::filesDropped(const StringArray& filePaths, int, int)
{
	if (patchConverter.outputFolderPath.isEmpty())
	{
        patchConverter.outputFolderPath = DEFAULT_UNIFY_PATCHES_FOLDER_PATH;
	}

    int fileCount = patchConverter.processFiles(filePaths);
    message = String(fileCount) + " files processed.";

	repaint();
}
