# SimplifiedTimeline_UnrealEngine

A simple to use timeline class for unreal engine. 
<br/>It can be used in any class or it can be a component for actors.

<br/>

It solves 2 problem with Unreals timelines:<br/>
 1-) You can't duplicate or create timelines at runtime.<br/>
 2-) You can't use timelines in widgets, etc<br/><br/><br/>


<h2>Installation</h2>
 1-) Paste source files to Your projects source folder<br/>
  For .h files: ProjectRoot/Source/ProjectName/Public/SimplifiedTimeline<br/>
  For .cpp files: ProjectRoot/Source/ProjectName/Private/SimplifiedTimeline<br/><br/>
 2-) Change API name with your projects API name in .h files<br/>
  For example let's say your projects name is "SomeName"<br/>
  You should replace this one<br/><br/>
  
    UCLASS()
    class YOURPROJECTNAME_API USimplifiedTimeline : public UObject

  To this one<br/>
  
    UCLASS()
    class SOMENAME_API USimplifiedTimeline : public UObject
