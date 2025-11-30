//
// Created by Joe on 09/11/2025.
//

#pragma once
#ifndef BSGDELAY_GAINDSP_H
#define BSGDELAY_GAINDSP_H

class GainDSP
{
public:
    static float dBToLinearCoefficient(float dB) noexcept;
    void processBlock(float* block, int blockSize) const noexcept;

    // Getters / Setters
    [[nodiscard]] float getGainDB() const { return m_gainDB; }
    void setGainDB(const float newGainDB) { m_gainDB = newGainDB; }
private:
    float m_gainDB {};
};


#endif //BSGDELAY_GAINDSP_H