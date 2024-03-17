#include "CritterHandler.h"
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

void PlayGame();

// ���α׷��� ���۵Ǵ� ���� srand�� ����� �ؼ� ���۵� ���� seed���� �ٲپ� �ָ� �ȴ�.
int main(void) {
	fastio;
	srand((unsigned)time(NULL));
	PlayGame();
	return 0;
}

void PlayGame() {
	CritterHandler* survival_game = new CritterHandler();

	survival_game->ShowTopInfo();
	survival_game->ShowWorld();
	survival_game->ShowBottomInfo();
	survival_game->InitSetting();

	while (1) {
		survival_game->HunterAction();
		if (survival_game->GameOver()) {
			survival_game->FinalMsg();
			return;
		}
		survival_game->ClearScreen();
		survival_game->TigerAction();
		survival_game->RabbitAction();
		survival_game->GrassAction();
		survival_game->ShowTopInfo();
		survival_game->ShowWorld();
		survival_game->ShowBottomInfo();
		survival_game->InitSetting();
	}
}