//
// Created by Joe Bristow on 04/02/2026.
//

#include "StereoWidthDSP.h"

void StereoWidthDSP::processBlock(juce::AudioBuffer<float>& buffer, const int blockSize) const noexcept
{
    const float coefficient { m_stereoWidth * 0.5f };

    for (int i = 0; i < blockSize; ++i)
    {
        const float dryL { buffer.getSample(0, i) };
        const float dryR { buffer.getSample(1, i) };

        const float mid { dryL + dryR * 0.5f };
        const float side { (dryR - dryL) * coefficient };

        const float outL { mid - side };
        const float outR { mid + side };

        buffer.setSample(0, i, outL);
        buffer.setSample(1, i, outR);
    }
}
