//
// Created by Joe Bristow on 04/12/2025.
//

#include "DefaultSkin.h"

juce::Typeface::Ptr Text::Fonts::getTypeface()
{
    return juce::Typeface::createSystemTypefaceFor(BinaryData::IBMPlexSans_ttf, BinaryData::IBMPlexSans_ttfSize);
}

juce::Font Text::Fonts::getFont(const float height)
{
    return juce::Font(getTypeface()).withHeight(height);
}

MainLookAndFeel::MainLookAndFeel()
{
    setDefaultSansSerifTypeface(Text::Fonts::getTypeface());
    setColour(juce::GroupComponent::ColourIds::outlineColourId, Colours::GroupComponent::outline);
    setDefaultLookAndFeel(this);
}

MainLookAndFeel::~MainLookAndFeel()
{
    setDefaultLookAndFeel(nullptr);
}

MainLookAndFeel& MainLookAndFeel::instance()
{
    static MainLookAndFeel INSTANCE;
    return INSTANCE;
}

RotaryDialLookAndFeel::RotaryDialLookAndFeel()
{
    setColour(juce::Slider::rotarySliderFillColourId, Colours::Dial::dialFill);
}

RotaryDialLookAndFeel& RotaryDialLookAndFeel::instance()
{
    static RotaryDialLookAndFeel INSTANCE;
    return INSTANCE;
}

void RotaryDialLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
{
    // 1. Draw Circle for Knob
    const juce::Rectangle<float> bounds = juce::Rectangle<int>(x, y, width, width).toFloat();
    const juce::Rectangle<float> dialRect = bounds.reduced(10.0f, 10.0f);

    juce::Path path = juce::Path();
    path.addEllipse(dialRect);
    dropShadow.drawForPath(g, path);
    g.setColour(Colours::Dial::outline);
    g.fillEllipse(dialRect);

    const juce::Rectangle<float> innerRect = dialRect.reduced(2.0f, 2.0f);
    const juce::ColourGradient gradient = juce::ColourGradient(Colours::Dial::gradientTop, 0.0f, innerRect.getY(), Colours::Dial::gradientBottom, 0.0f, innerRect.getBottom(), false);
    g.setGradientFill(gradient);
    g.fillEllipse(innerRect);

    auto centre = bounds.getCentre();
    auto radius = bounds.getWidth() / 2.0f;
    auto lineWidth = 3.0f;
    auto arcRadius = radius - lineWidth / 2.0f;

    juce::Path backgroundArc;
    backgroundArc.addCentredArc(centre.x, centre.y, arcRadius, arcRadius, 0.0f, rotaryStartAngle, rotaryEndAngle, true);

    auto strokeType = juce::PathStrokeType(lineWidth, juce::PathStrokeType::curved, juce::PathStrokeType::rounded);

    g.setColour(Colours::Dial::trackBackground);
    g.strokePath(backgroundArc, strokeType);

    auto dialRadius = innerRect.getHeight() / 2.0f - lineWidth;
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    juce::Point<float> dialStart(centre.x + 10.0f * std::sin(toAngle), centre.y - 10.0f * std::cos(toAngle));
    juce::Point<float> dialEnd(centre.x + dialRadius * std::sin(toAngle), centre.y - dialRadius * std::cos(toAngle));

    juce::Path dialPath;
    dialPath.startNewSubPath(dialStart);
    dialPath.lineTo(dialEnd);
    g.setColour(Colours::Dial::trackBackground);
    g.strokePath(dialPath, strokeType);

    if (slider.isEnabled())
    {
        juce::Path valueArc;
        valueArc.addCentredArc(centre.x, centre.y, arcRadius, arcRadius, 0.0f, rotaryStartAngle, toAngle, true);
        g.setColour(Colours::Dial::dialFill);
        g.strokePath(valueArc, strokeType);
    }
}







