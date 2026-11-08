#include "Game/TornadoChasingGameMode.h"
#include "Characters/ChaseCharacter.h"

ATornadoChasingGameMode::ATornadoChasingGameMode()
{
    DefaultPawnClass = AChaseCharacter::StaticClass();
}
