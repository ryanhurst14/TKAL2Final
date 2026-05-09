#include "TKAL2GameMode.h"
#include "Player/TKAL2PlayerController.h"

ATKAL2GameMode::ATKAL2GameMode()
{
	PlayerControllerClass = ATKAL2PlayerController::StaticClass();
}
