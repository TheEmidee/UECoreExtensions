#include "Math/MovingAverage.h"

FMovingAverage::FMovingAverage() :
    FMovingAverage( 0, 0 )
{
}

FMovingAverage::FMovingAverage( const int required_sample_count, const float sample_rate_seconds ) :
    SampleCount( 0 ),
    SampleAccumulator( 0 ),
    SampleStartTime( 0 ),
    SampleRateSeconds( sample_rate_seconds ),
    SampleSize( required_sample_count ),
    SampleAverage( 0 ),
    NextSampleIndex( 0 )
{
    Samples.Reserve( SampleSize );
}

void FMovingAverage::AddSample( const double current_time, const float value )
{
    if ( SampleSize == 0 )
    {
        return;
    }

    if ( SampleStartTime == 0 )
    {
        SampleStartTime = current_time;
    }

    ++SampleCount;
    SampleAccumulator += value;

    if ( current_time - SampleStartTime > SampleRateSeconds )
    {
        const float accumulator_average = SampleAccumulator / SampleCount;

        if ( Samples.Num() == SampleSize )
        {
            Samples[ NextSampleIndex ] = accumulator_average;
        }
        else
        {
            Samples.Add( accumulator_average );
        }

        NextSampleIndex = ( NextSampleIndex + 1 ) % SampleSize;
        ensure( NextSampleIndex >= 0 && NextSampleIndex < SampleSize );

        auto sum = 0.0f;
        for ( const auto sample : Samples )
        {
            sum += sample;
        }

        SampleAverage = sum / Samples.Num();

        SampleAccumulator = SampleCount = 0;
        SampleStartTime = current_time;
    }
}
