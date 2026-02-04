//
// Created by Joe on 09/11/2025.
//

#include <cmath>
#include <juce_audio_basics/juce_audio_basics.h>
#include "GainDSP.h"

/* Decibels are non-linear. A 20dB increase is 100 times the pressure than a 10dB increase.
 * Therefore, decibels must be converted to linear units to scale sample amplitudes appropriately.
 * E.g., a 6dB increase doubles the amplitude, so it corresponds to a 2.0x coefficient.
 */
float GainDSP::dBToLinearCoefficient(const float dB) noexcept
{
    return static_cast<float>(pow(10, (dB / 20)));
}

void GainDSP::processBlock(juce::AudioBuffer<float>& buffer, const int blockSize) const noexcept
{
    const float multiplier { dBToLinearCoefficient(m_gainDB) };

    for (int sample = 0; sample < blockSize; ++sample)
    {
        const float dryL { buffer.getSample(0, sample) };
        const float dryR { buffer.getSample(1, sample) };

        // Scale each sample's amplitude according to linear units
        const float outL { dryL * multiplier };
        const float outR { dryR * multiplier };

        buffer.setSample(0, sample, outL);
        buffer.setSample(1, sample, outR);
    }
}