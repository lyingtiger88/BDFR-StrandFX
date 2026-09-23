// -----------------------------------------------------------------------------
// BDFR-StrandFX platform profile layer.
//
// Provides runtime-selectable performance/quality presets for Mobile, Console,
// and PC. The profile layer intentionally targets settings that can be changed
// at runtime in the current TressFX 4.1 sample. UE5 DeviceProfile integration
// can map to the same profile API later.
// -----------------------------------------------------------------------------

#pragma once

#include "TressFXSettings.h"

enum class BDFRPlatformProfile : int
{
    Mobile = 0,
    Console = 1,
    PC = 2
};

enum class BDFROITPreference : int
{
    ShortCut = 0,
    PPLL = 1
};

struct BDFRPlatformProfileSettings
{
    const char* name;
    const char* description;

    BDFROITPreference oitPreference;

    bool enableHairLOD;
    bool enableShadowLOD;
    bool enableSDFGeneration;
    bool enableCollisionResponse;
    bool enableAsyncCompute;
    bool useDepthApproximation;

    int localConstraintIterations;
    int lengthConstraintIterations;

    float lodStartDistance;
    float lodEndDistance;
    float lodPercent;
    float lodWidthMultiplier;

    float shadowLODStartDistance;
    float shadowLODEndDistance;
    float shadowLODPercent;
    float shadowLODWidthMultiplier;
};

inline BDFRPlatformProfileSettings GetBDFRPlatformProfileSettings(BDFRPlatformProfile profile)
{
    switch (profile)
    {
    case BDFRPlatformProfile::Mobile:
        return {
            "Mobile",
            "Reduced strand/shadow cost; SDF collision disabled by default.",
            BDFROITPreference::ShortCut,
            true, true,
            false, false,
            false, true,
            1, 1,
            1.5f, 7.5f, 0.18f, 3.0f,
            1.0f, 6.0f, 0.10f, 3.5f
        };

    case BDFRPlatformProfile::Console:
        return {
            "Console",
            "Balanced strand quality, simulation, collision, and shadows.",
            BDFROITPreference::ShortCut,
            true, true,
            true, true,
            true, true,
            2, 2,
            3.0f, 15.0f, 0.45f, 2.0f,
            3.0f, 12.0f, 0.35f, 2.25f
        };

    case BDFRPlatformProfile::PC:
    default:
        return {
            "PC",
            "Highest-quality default with PPLL, SDF collision, and full simulation budget.",
            BDFROITPreference::PPLL,
            true, true,
            true, true,
            true, false,
            3, 3,
            6.0f, 25.0f, 0.70f, 1.5f,
            5.0f, 20.0f, 0.60f, 1.5f
        };
    }
}

inline void ApplyBDFRPlatformProfile(
    const BDFRPlatformProfileSettings& profile,
    TressFXSimulationSettings& simulation,
    TressFXRenderingSettings& rendering)
{
    simulation.m_localConstraintsIterations = profile.localConstraintIterations;
    simulation.m_lengthConstraintsIterations = profile.lengthConstraintIterations;

    rendering.m_EnableHairLOD = profile.enableHairLOD;
    rendering.m_LODStartDistance = profile.lodStartDistance;
    rendering.m_LODEndDistance = profile.lodEndDistance;
    rendering.m_LODPercent = profile.lodPercent;
    rendering.m_LODWidthMultiplier = profile.lodWidthMultiplier;

    rendering.m_EnableShadowLOD = profile.enableShadowLOD;
    rendering.m_ShadowLODStartDistance = profile.shadowLODStartDistance;
    rendering.m_ShadowLODEndDistance = profile.shadowLODEndDistance;
    rendering.m_ShadowLODPercent = profile.shadowLODPercent;
    rendering.m_ShadowLODWidthMultiplier = profile.shadowLODWidthMultiplier;
}
