//
// Created by Joe Bristow on 04/02/2026.
//

#ifndef STEREOWIDTHDSP_H
#define STEREOWIDTHDSP_H

#include <juce_audio_basics/juce_audio_basics.h>

class StereoWidthDSP {
public:
    void processBlock(juce::AudioBuffer<float>& buffer, int blockSize) const noexcept;
    void setWidth(const float stereoWidth) { m_stereoWidth = stereoWidth; }
private:
    float m_stereoWidth { };
};

#endif //STEREOWIDTHDSP_H
