#include "FrequencyThrottler.h"

FFrequencyThrottler::FFrequencyThrottler( const int max_events, const float time_window ) :
    MaxEvents( max_events ),
    TimeWindow( time_window )
{
}

void FFrequencyThrottler::Reset( const int max_events, const float time_window )
{
    *this = FFrequencyThrottler( max_events, time_window );
}

bool FFrequencyThrottler::RecordEvent()
{
    const auto current_time = FPlatformTime::Seconds();

    while ( !Events.IsEmpty() )
    {
        const auto elapsed = current_time - Events.First();

        if ( elapsed > TimeWindow )
        {
            Events.PopFirst();
        }
        else
        {
            break;
        }
    }

    if ( GetEventCount() >= MaxEvents )
    {
        return false;
    }

    Events.PushLast( current_time );
    return true;
}