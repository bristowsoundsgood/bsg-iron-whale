//
// Created by Joe Bristow on 03/12/2025.
//

#ifndef DEFAULTSKIN_H
#define DEFAULTSKIN_H

#include <juce_gui_basics/juce_gui_basics.h>
#include "BinaryData.h"

namespace Dimensions
{
    static constexpr int windowWidth {650};
    static constexpr int windowHeight {450};

    static constexpr int sliderWidth {70};
    static constexpr int sliderHeight {110};
    static constexpr int sliderTextBoxWidth {70};
    static constexpr int sliderTextBoxHeight {16};
    static constexpr bool sliderTextBoxReadOnly {false};

    static constexpr int btnWidth {30};
    static constexpr int btnHeight {30};

    static constexpr int labelHeight {25};

    static constexpr int marginTop {25};
    static constexpr int marginSide {20};
    static constexpr int dialBufferY {20};

    static constexpr int groupWidth {100};
    static constexpr int groupHeight {windowHeight - (marginTop * 2)};
}

namespace Text
{
    static constexpr float fontSize {16.0f};

    class Fonts
    {
    public:
        static juce::Typeface::Ptr getTypeface();
        static juce::Font getFont(float height = fontSize);
        Fonts() = delete; // No need to create any instance of this class. Only need to access getFont().
    };
}

namespace Colours
{
    const juce::Colour background {23, 29, 37};
    const juce::Colour header {40, 40, 40};

    namespace Dial
    {
        const juce::Colour outline {23, 29, 37};
        const juce::Colour gradientTop {33, 39, 47};
        const juce::Colour gradientBottom {28, 34, 42};
        const juce::Colour trackBackground {250, 239, 235};
        const juce::Colour dialTick {100, 100, 100};
        const juce::Colour dialFill {208, 117, 84};
        const juce::Colour dropShadow {195, 190, 185};
    }

    namespace GroupComponent
    {
        const juce::Colour label {};
        const juce::Colour outline {250, 239, 235};
    }
}

class MainLookAndFeel : public juce::LookAndFeel_V4
{
public:
    static MainLookAndFeel& instance();
private:
    MainLookAndFeel();
    ~MainLookAndFeel() override;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainLookAndFeel)
};

class RotaryDialLookAndFeel : public juce::LookAndFeel_V4
{
public:
    static RotaryDialLookAndFeel& instance();

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
        float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;
private:
    RotaryDialLookAndFeel();
    juce::DropShadow dropShadow {Colours::Dial::dropShadow, 6, {0, 3}};
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RotaryDialLookAndFeel)
};

#endif //DEFAULTSKIN_H
