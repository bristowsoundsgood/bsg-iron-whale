//
// Created by Joe Bristow on 03/12/2025.
//

#ifndef EDITORCONFIG_H
#define EDITORCONFIG_H

namespace GUIDefaults
{
    static constexpr int windowWidth {600};
    static constexpr int windowHeight {430};

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

#endif //EDITORCONFIG_H
