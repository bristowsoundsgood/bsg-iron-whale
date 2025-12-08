//
// Created by Joe Bristow on 03/12/2025.
//

#ifndef DEFAULTSKIN_H
#define DEFAULTSKIN_H

#include <juce_gui_basics/juce_gui_basics.h>

namespace Text
{
    static constexpr float fontSize {11.0f};
}

namespace Dimensions
{
    static constexpr int windowWidth {650};
    static constexpr int windowHeight {450};

    static constexpr int sliderWidth {70};
    static constexpr int sliderHeight {110};
    static constexpr int sliderTextBoxWidth {70};
    static constexpr int sliderTextBoxHeight {16};
    static constexpr bool sliderTextBoxReadOnly {false};

    static constexpr int labelHeight {25};

    static constexpr int marginTop {25};
    static constexpr int marginSide {20};
    static constexpr int dialBufferY {20};

    static constexpr int groupWidth {100};
    static constexpr int groupHeight {windowHeight - (marginTop * 2)};
}

namespace Colours
{
    const juce::Colour background {23, 29, 37};
    const juce::Colour header {40, 40, 40};

    namespace Dial
    {
        const juce::Colour dialFill {208, 87, 46};
    }
}

class RotaryDialLookAndFeel : public juce::LookAndFeel_V4
{
public:
    static RotaryDialLookAndFeel& instance();

    // void drawRotarySlider(juce::Graphics&, int x, int y, int width, int height,
    //    float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider&) override;

private:
    RotaryDialLookAndFeel();
    // juce::Typeface::Ptr m_customTypeface {juce::Typeface::createSystemTypefaceFor(BinaryData::)}
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RotaryDialLookAndFeel)
};

#endif //DEFAULTSKIN_H
