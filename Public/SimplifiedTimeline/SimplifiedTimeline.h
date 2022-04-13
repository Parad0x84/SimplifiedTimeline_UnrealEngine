// This is lighter version of marketplace content which is named as SimplifiedTimeline.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SimplifiedTimeline.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSimplifiedTimelineUpdate, float , Value, float, CurrentTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSimplifiedTimelineFinished);


UCLASS()
class YOURPROJECTNAME_API USimplifiedTimeline : public UObject
{
	GENERATED_BODY()

public:
	USimplifiedTimeline();

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
		FOnSimplifiedTimelineUpdate TimelineUpdate;
	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
		FOnSimplifiedTimelineFinished TimelineFinished;

protected:
	void TimelineTick();

	UPROPERTY()
		UCurveFloat* CurrentCurve;

	UPROPERTY()
		float CurrentTime;
	UPROPERTY()
		float MinTime;
	UPROPERTY()
		float MaxTime;
	UPROPERTY()
		float MinValue;
	UPROPERTY()
		float MaxValue;
	UPROPERTY()
		float PlayRate;

	UPROPERTY()
		bool bDirection;
	UPROPERTY()
		bool bIsPlaying;
	UPROPERTY()
		bool bDoOnce;

	UPROPERTY()
	FTimerHandle TimelineHandle;
	
public:
	/**     Plays selected Simplified Timeline
	 *      It returns the success state of playing timeline
	 *
	 *      It will fail and return false, if selected curve is not valid,
	 *      Curve length is 0 or currently playing and StopIfPlaying is false
	 *
	 *      @param IsForward         Whether curve plays forward or backward
	 *      @param StopIfPlaying     If curve is currently playing, should it stop and re-run
	 *      @param ResetCurrentTime  Whether reset current time or not
	 */
	UFUNCTION(BlueprintCallable, Category = "Simplified Timeline")
		bool Play(bool IsForward, bool StopIfPlaying, bool ResetCurrentTime);
	/**     Stops selected Simplified Timeline     */
	UFUNCTION(BlueprintCallable, Category = "Simplified Timeline")
		void Stop();

	
	
	/**     Gets current time of selected Simplified Timeline     */
	UFUNCTION(BlueprintCallable, Category = "Simplified Timeline")
		float GetCurrentTime() const;
	/**     Sets current time of selected Simplified Timeline     */
	UFUNCTION(BlueprintCallable, Category = "Simplified Timeline")
		bool SetCurrentTime(float NewTime);

	
	
	/**     Gets curve of selected Simplified Timeline     */
	UFUNCTION(BlueprintCallable, Category = "Simplified Timeline")
		UCurveFloat* GetCurve() const;
	/**     Sets the curve of selected Simplified Timeline
	 *      It returns the success state of setting new curve
	 *     
	 *      It will fail and return false, if selected curve is not valid or Timeline is currently running
	 */
	UFUNCTION(BlueprintCallable, Category = "Simplified Timeline")
		bool SetCurve(UCurveFloat* Curve);

	
	
	/**     Gets time range of selected Simplified Timeline as Vector2D
	 *      X is minimum time and Y is maximum time
	 *      
	 *      It will return Zero-Vector(0.0, 0.0), if curve is not valid
	 */
	UFUNCTION(BlueprintCallable, Category = "Simplified Timeline")
		FVector2D GetTimeRange() const;
	/**     Gets value range of selected Simplified Timeline as Vector2D
	 *      X is minimum value and Y is maximum value
	 *      
	 *      It will return Zero-Vector(0.0, 0.0), if curve is not valid
	 */
	UFUNCTION(BlueprintCallable, Category = "Simplified Timeline")
		FVector2D GetValueRange() const;

	
	
	/**     Gets play rate of selected Simplified Timeline     */
	UFUNCTION(BlueprintCallable, Category = "Simplified Timeline")
		float GetPlayRate() const;
	/**     Sets play rate of selected Simplified Timeline
	 *
	 *      If new rate equal or smaller than 0, it will fail and return false
	 */
	UFUNCTION(BlueprintCallable, Category = "Simplified Timeline")
		bool SetPlayRate(float NewRate);



	/**     Gets direction of selected Simplified Timeline     */
	UFUNCTION(BlueprintCallable, Category = "Simplified Timeline")
		bool GetDirection() const;
	/**     Sets direction of selected Simplified Timeline     */
	UFUNCTION(BlueprintCallable, Category = "Simplified Timeline")
		void SetDirection(bool NewDirection);
};
