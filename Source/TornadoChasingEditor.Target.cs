using UnrealBuildTool;
using System.Collections.Generic;

public class TornadoChasingEditorTarget : TargetRules
{
    public TornadoChasingEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        ExtraModuleNames.Add("TornadoChasing");
    }
}