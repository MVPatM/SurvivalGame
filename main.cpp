#include "CritterHandler.h"
#define fastio ios_base::sync_with_stdio(0), cin.tie(0);

void PlayGame();

// 프로그램이 시작되는 곳에 srand를 사용을 해서 시작될 때만 seed값을 바꾸어 주면 된다.
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