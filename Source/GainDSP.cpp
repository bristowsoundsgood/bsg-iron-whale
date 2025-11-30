//
// Created by Joe on 09/11/2025.
//

#include "GainDSP.h"
#include <cmath>

/* Decibels are non-linear. A 20dB increase is 100 times the pressure than a 10dB increase.
 * Therefore, decibels must be converted to linear units to scale sample amplitudes appropriately.
 * E.g., a 6dB increase doubles the amplitude, so it corresponds to a 2.0x coefficient.
 */
float GainDSP::dBToLinearCoefficient(const float dB) noexcept
{
    return static_cast<float>(pow(10, (dB / 20)));
}


void GainDSP::processBlock(float* block, const int blockSize) const noexcept
{
    const float multiplier = dBToLinearCoefficient(m_gainDB);

    // Scale each sample's amplitude according to linear units
    for (int sample = 0; sample < blockSize; ++sample)
    {
        block[sample] *= multiplier;
    }
}