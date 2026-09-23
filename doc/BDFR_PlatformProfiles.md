# BDFR-StrandFX Platform Profiles

BDFR-StrandFX adds a runtime-selectable platform profile layer on top of the TressFX 4.1 baseline.

The current selector is available in the sample UI as:

- Mobile
- Console
- PC

The goal is to keep a single hair/fur asset and switch the runtime budget according to the target device. The same profile API is intended to map to Unreal Engine Device Profiles when the UE5 plugin layer is added.

## Current behavior

| Setting | Mobile | Console | PC |
|---|---:|---:|---:|
| Transparency method | ShortCut | ShortCut | PPLL |
| Hair LOD | Enabled | Enabled | Enabled |
| Shadow LOD | Enabled | Enabled | Enabled |
| SDF generation | Disabled | Enabled | Enabled |
| SDF collision response | Disabled | Enabled | Enabled |
| Async compute | Disabled | Disabled | Disabled |
| Shadow depth approximation | Enabled | Enabled | Disabled |
| Local constraint iterations | 1 | 2 | 3 |
| Length constraint iterations | 1 | 2 | 3 |
| Final hair density at far LOD | 18% | 45% | 70% |
| Final shadow density at far LOD | 10% | 35% | 60% |

## Mobile

The Mobile profile is deliberately conservative. It keeps strand rendering functional while aggressively reducing distant strand and shadow density. Dynamic SDF generation and SDF collision response are disabled by default because they are relatively expensive for a mobile GPU.

This is not yet a card-based mobile renderer. A future UE5 integration can map this profile to a hybrid or card fallback while preserving the same public profile API.

## Console

The Console profile keeps SDF collision and full-rate simulation, but uses ShortCut transparency and stronger LOD reduction than the PC profile.

This profile is intended to become the default starting point for fixed-spec consoles after profiling on target hardware.

## PC

The PC profile selects PPLL transparency, retains SDF collision, uses the highest simulation iteration budget of the three presets, and uses less aggressive hair and shadow reduction.

## Runtime selection

The sample exposes a Platform Profile combo box. Selecting a profile immediately updates:

- transparency/OIT method
- hair LOD parameters
- shadow LOD parameters
- simulation constraint iterations
- SDF generation
- collision response
- shadow depth approximation

The selected profile is also re-applied when a scene is loaded.

## Important implementation note

The legacy TressFX async-compute path currently waits for compute completion in the same frame, so BDFR profiles leave it disabled until the resource scheduling path is modernized.

## Planned UE5 mapping

The UE5 plugin layer can map these profiles to:

- Unreal Device Profiles
- Project Settings
- per-platform defaults
- runtime scalability settings
- automatic hardware detection
- future strand / hybrid / card rendering backends

The current core API is defined in:

`src/BDFRPlatformProfile.h`
