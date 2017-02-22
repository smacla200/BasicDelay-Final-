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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
BasicDelayAudioProcessorEditor::BasicDelayAudioProcessorEditor (BasicDelayAudioProcessor& p)
    : AudioProcessorEditor(p), processor(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (sliderFeedback = new Slider ("feedback "));
    sliderFeedback->setRange (0, 0.95, 0);
    sliderFeedback->setSliderStyle (Slider::LinearHorizontal);
    sliderFeedback->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    sliderFeedback->addListener (this);

    addAndMakeVisible (sliderDelayTime = new Slider ("delay time"));
    sliderDelayTime->setRange (0.01, 1, 0);
    sliderDelayTime->setSliderStyle (Slider::LinearHorizontal);
    sliderDelayTime->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    sliderDelayTime->addListener (this);

    addAndMakeVisible (labelDelayTime = new Label ("new label",
                                                   TRANS("Delay time (seconds)\n")));
    labelDelayTime->setFont (Font (15.00f, Font::plain));
    labelDelayTime->setJustificationType (Justification::centredLeft);
    labelDelayTime->setEditable (false, false, false);
    labelDelayTime->setColour (TextEditor::textColourId, Colours::black);
    labelDelayTime->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (labelFeedback = new Label ("new label",
                                                  TRANS("Feedback (0-0.95)")));
    labelFeedback->setFont (Font (15.00f, Font::plain));
    labelFeedback->setJustificationType (Justification::centredLeft);
    labelFeedback->setEditable (false, false, false);
    labelFeedback->setColour (TextEditor::textColourId, Colours::black);
    labelFeedback->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    startTimer(200);//starts timer with interval of 200mS
    //[/Constructor]
}

BasicDelayAudioProcessorEditor::~BasicDelayAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    sliderFeedback = nullptr;
    sliderDelayTime = nullptr;
    labelDelayTime = nullptr;
    labelFeedback = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void BasicDelayAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void BasicDelayAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    sliderFeedback->setBounds (48, 216, 272, 24);
    sliderDelayTime->setBounds (48, 88, 272, 24);
    labelDelayTime->setBounds (40, 56, 150, 24);
    labelFeedback->setBounds (40, 168, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void BasicDelayAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == sliderDelayTime)
    {
        //[UserSliderCode_sliderDelayTime] -- add your slider handling code here..
        processor.setParameterNotifyingHost(BasicDelayAudioProcessor::kDelayTimeParam,
                                            (float)sliderDelayTime->getValue());
        //[/UserSliderCode_sliderDelayTime]
    }
    else if (sliderThatWasMoved == sliderFeedback)
    {
        //[UserSliderCode_sliderFeedback] -- add your slider handling code here..
        processor.setParameterNotifyingHost(BasicDelayAudioProcessor::kFeedbackParam,
                                            (float)sliderFeedback->getValue());
        //[/UserSliderCode_sliderFeedback]
    }
}
    //[MiscUserCode] You can add your own definitions of your custom methods or any other code
    //here...
    void BasicDelayAudioProcessorEditor::timerCallback()
    {
        sliderDelayTime->setValue(processor.delayTime, dontSendNotification);
        sliderFeedback->setValue(processor.feedback, dontSendNotification);
        //exchange any data you want between UI elements and the Plugin processor
    }
    //[/MiscUserCode]




//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="BasicDelayAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="BasicDelayAudioProcessor&amp; p" variableInitialisers="AudioProcessorEditor(p), processor(p)&#10;"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="feedback " id="edbe6c7a52e1751b" memberName="sliderFeedback"
          virtualName="" explicitFocusOrder="0" pos="48 216 272 24" min="0"
          max="0.94999999999999995559" int="0" style="LinearHorizontal"
          textBoxPos="TextBoxLeft" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="delay time" id="df0ff6ce906c3edd" memberName="sliderDelayTime"
          virtualName="" explicitFocusOrder="0" pos="48 88 272 24" min="0.010000000000000000208"
          max="1" int="0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <LABEL name="new label" id="3ba2108ad06a6df1" memberName="labelDelayTime"
         virtualName="" explicitFocusOrder="0" pos="40 56 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Delay time (seconds)&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="9984e32610b7d467" memberName="labelFeedback"
         virtualName="" explicitFocusOrder="0" pos="40 168 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Feedback (0-0.95)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
