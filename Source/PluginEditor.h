/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.3.0

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_B239480082FFF0E4__
#define __JUCE_HEADER_B239480082FFF0E4__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class BasicDelayAudioProcessorEditor  : public AudioProcessorEditor,
                                        public Timer,
                                        public SliderListener
{
public:
    //==============================================================================
    BasicDelayAudioProcessorEditor (BasicDelayAudioProcessor& p);
    ~BasicDelayAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void timerCallback();
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    BasicDelayAudioProcessor& processor ;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Slider> sliderFeedback;
    ScopedPointer<Slider> sliderDelayTime;
    ScopedPointer<Label> labelDelayTime;
    ScopedPointer<Label> labelFeedback;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicDelayAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_B239480082FFF0E4__
