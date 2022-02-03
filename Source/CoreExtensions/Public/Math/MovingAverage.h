#pragma once

#include <CoreMinimal.h>

struct COREEXTENSIONS_API FMovingAverage
{
    FMovingAverage();
    FMovingAverage( int required_sample_count, float sample_rate_seconds );

    bool HasEnoughSamples() const;
    void Reset();
    void Reset( int required_sample_count, float sample_rate_seconds );
    float GetAverage() const;
    void SetAverage( float average );
    int GetSampleCount() const;
    void AddSample( double current_time, float value );

private:
    int SampleCount;
    float SampleAccumulator;
    double SampleStartTime;
    float SampleRateSeconds;
    int32 SampleSize;
    float SampleAverage;
    TArray< float > Samples;
    int NextSampleIndex;
};

FORCEINLINE bool FMovingAverage::HasEnoughSamples() const
{
    return SampleCount != 0 && Samples.Num() == SampleSize;
}

FORCEINLINE void FMovingAverage::Reset( const int required_sample_count, const float sample_rate_seconds )
{
    *this = FMovingAverage( required_sample_count, sample_rate_seconds );
}

FORCEINLINE void FMovingAverage::Reset()
{
    *this = FMovingAverage( SampleSize, SampleRateSeconds );
}

FORCEINLINE float FMovingAverage::GetAverage() const
{
    return SampleAverage;
}

FORCEINLINE void FMovingAverage::SetAverage( float average )
{
    SampleAverage = average;
}

FORCEINLINE int FMovingAverage::GetSampleCount() const
{
    return Samples.Num();
}