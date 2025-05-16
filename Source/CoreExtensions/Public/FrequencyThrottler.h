#pragma once

#include <Containers/Deque.h>
#include <CoreMinimal.h>

class COREEXTENSIONS_API FFrequencyThrottler
{
public:
    FFrequencyThrottler() = default;
    FFrequencyThrottler( int max_events, float time_window );

    void Reset( int max_events, float time_window );
    bool RecordEvent();
    int GetEventCount() const;
    int GetMaxEvents() const;
    float GetTimeWindow() const;
    float GetTimeBetweenFirstAndLastEvents() const;

private:
    TDeque< float > Events;
    int MaxEvents;
    float TimeWindow;
};

FORCEINLINE int FFrequencyThrottler::GetEventCount() const
{
    return Events.Num();
}

FORCEINLINE int FFrequencyThrottler::GetMaxEvents() const
{
    return MaxEvents;
}

FORCEINLINE float FFrequencyThrottler::GetTimeWindow() const
{
    return TimeWindow;
}

FORCEINLINE float FFrequencyThrottler::GetTimeBetweenFirstAndLastEvents() const
{
    return Events.Last() - Events.First();
}