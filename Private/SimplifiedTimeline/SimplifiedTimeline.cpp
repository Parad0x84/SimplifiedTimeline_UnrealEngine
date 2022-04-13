// This is lighter version of marketplace content which is named as SimplifiedTimeline.


#include "SimplifiedTimeline/SimplifiedTimeline.h"

USimplifiedTimeline::USimplifiedTimeline()
{
	bDoOnce = bIsPlaying = bDirection = false;
	CurrentTime = MinTime = MaxTime = MinValue = MaxValue = 0.0f;
	PlayRate = 1.0f;
}




void USimplifiedTimeline::TimelineTick()
{
	if(bIsPlaying)
	{
		if(bDirection? CurrentTime < MaxTime : CurrentTime > MinTime)
		{
			TimelineUpdate.Broadcast(CurrentCurve->GetFloatValue(CurrentTime), CurrentTime);
			
			CurrentTime = FMath::Clamp(CurrentTime + (bDirection? 1.0f : -1.0f) * GetWorld()->GetDeltaSeconds() * PlayRate, MinTime, MaxTime);
			
			GetWorld()->GetTimerManager().SetTimerForNextTick(this, &USimplifiedTimeline::TimelineTick);
		}
		else if(bDoOnce)
		{
			bIsPlaying = false;

			TimelineUpdate.Broadcast(CurrentCurve->GetFloatValue(CurrentTime), CurrentTime);

			TimelineFinished.Broadcast();
		}
	}
}





bool USimplifiedTimeline::Play(bool IsForward, bool StopIfPlaying, bool ResetCurrentTime)
{
	/*                    SETUP START                    */
	if(!IsValid(CurrentCurve) || (GetTimeRange().Y - GetTimeRange().X <= 0.0f) || (bIsPlaying && !StopIfPlaying) || !TimelineUpdate.IsBound())
		return false;

	if(bDirection == IsForward && StopIfPlaying && !ResetCurrentTime)

	bIsPlaying = false;
	
	bDirection = IsForward? true : false;

	if(ResetCurrentTime)
		CurrentTime = IsForward? GetTimeRange().X : GetTimeRange().Y;

	bDoOnce = true;
	/*                     SETUP END                     */

	bIsPlaying = true;
	
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &USimplifiedTimeline::TimelineTick);
	
	return true;
}


void USimplifiedTimeline::Stop()
{
	bIsPlaying = false;
}




/*               GETTER & SETTER START               */
float USimplifiedTimeline::GetCurrentTime() const
{
	return CurrentTime;
}

bool USimplifiedTimeline::SetCurrentTime(float NewTime)
{
	if(IsValid(CurrentCurve) && MinTime <= NewTime && NewTime <= MaxTime)
	{
		CurrentTime = NewTime;
		return true;
	}

	return false;
}

UCurveFloat* USimplifiedTimeline::GetCurve() const
{
	return CurrentCurve;
}

bool USimplifiedTimeline::SetCurve(UCurveFloat* Curve)
{
	if(bIsPlaying || !IsValid(Curve))
		return false;

	CurrentCurve = Curve;

	CurrentCurve->GetTimeRange(MinTime, MaxTime);
	CurrentCurve->GetValueRange(MinValue, MaxValue);

	return true;
}

FVector2D USimplifiedTimeline::GetTimeRange() const
{
	return FVector2D(MinTime, MaxTime);
}

FVector2D USimplifiedTimeline::GetValueRange() const
{
	return FVector2D(MinValue, MaxValue);
}

float USimplifiedTimeline::GetPlayRate() const
{
	return PlayRate;
}

bool USimplifiedTimeline::SetPlayRate(float NewRate)
{
	if(NewRate <= 0.0f)
		return false;

	PlayRate = NewRate;
	
	return true;
}

bool USimplifiedTimeline::GetDirection() const
{
	return bDirection;
}

void USimplifiedTimeline::SetDirection(bool NewDirection)
{
	bDirection = NewDirection;
}
/*                GETTER & SETTER END                 */



