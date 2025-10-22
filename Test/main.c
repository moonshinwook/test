#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <locale.h>   // 콘솔에 ♥/♡ 깨짐 방지 (윈도우면 필요)




/* 가위바위보 매핑: 1=가위, 2=바위, 3=보 */
int getEnemyHand(void) {
	return (rand() % 3) + 1;
}

const char* handName(int h) {
	if (h == 1) return "가위";
	if (h == 2) return "바위";
	return "보";
}

/* 전투 1라운드 처리: 승패 반환 (1=플레이어 승, -1=패, 0=무) */
int rpsResult(int p, int e) {
	if (p == e) return 0;
	if ((p == 1 && e == 3) || (p == 2 && e == 1) || (p == 3 && e == 2)) return 1;
	return -1;
}

/* 현재 체력 출력 (소수 1자리) */


///* 하트로 체력 출력 (♥=남은 체력, 💔=반하트, ♡=빈칸) */ -> 반하트깨짐으로 밑에 코드로 대체
//void printHearts(float hp, float maxHp) {
//	if (maxHp > 5.0f) maxHp = 5.0f;
//	if (hp < 0.0f) hp = 0.0f;
//	if (hp > maxHp) hp = maxHp;
//
//	int fullHearts = (int)hp;             // 정수부분 = 완전한 ♥ 개수
//	int maxH = (int)roundf(maxHp);
//	int hasHalf = 0;
//
//	// 소수점 부분이 0.3~0.8 사이면 반하트 출력
//	if (hp - fullHearts >= 0.3f && hp - fullHearts < 0.8f)
//		hasHalf = 1;
//
//	// ♥ 출력
//	for (int i = 0; i < fullHearts; i++)
//		printf("♥");
//
//	// 💔 출력 (절반 하트)
//	if (hasHalf)
//		printf("💔");
//
//	// ♡ 출력 (빈칸)
//	for (int i = fullHearts + hasHalf; i < maxH; i++)
//		printf("♡");
//}
/* 하트 출력: ♥=채움, ◐=반, ♡=빈칸 (UTF-8 텍스트) */
void printHearts(float hp, float maxHp) {
	if (maxHp > 5.0f) maxHp = 5.0f;
	if (hp < 0.0f) hp = 0.0f;
	if (hp > maxHp) hp = maxHp;

	int full = (int)hp;
	float frac = hp - full;
	int half = (frac >= 0.3f && frac < 0.8f) ? 1 : 0;
	int maxH = (int)maxHp;

	for (int i = 0; i < full; ++i) printf("♥");
	if (half) printf("◐");              // 💔 대신 ◐ 사용 (안 깨짐)
	for (int i = full + half; i < maxH; ++i) printf("♡");
}
void drawUI(float pHP, float pMaxHP, float eHP, float eMaxHP) {
	system("cls");                  // 콘솔 지우기 (Windows)
	printf("내 체력: ");
	printHearts(pHP, pMaxHP);
	printf("  |  적 체력: ");
	printHearts(eHP, eMaxHP);
	printf("\n");                   // 상태라인 1줄만
}


/* 상태 줄 출력 */
void showStatus(float playerHP, float playerMaxHP, float enemyHP, float enemyMaxHP) {
	printf("\r 내 체력: "); // \r 화면 위로 스크롤 방지
	printHearts(playerHP, playerMaxHP);
	printf("  |  적 체력: ");
	printHearts(enemyHP, enemyMaxHP);
	printf("\n");
}


/* 한 스테이지 전투 루프 (플레이어가 이기면 1, 지면 0) */
int playStage(
	int stageNo,
	float* pHP,
	float* pATK,
	float  pMaxHP,
	float  enemyMaxHP,
	float  enemyATK,
	const char* enemyName
) {
	float enemyHP = enemyMaxHP;
	int playerHand = 0;
	int enemyHand = 0;
	int result = 0;

	printf("\n===== 스테이지 %d: %s 등장! (적 HP=%.1f, 공격력=%.1f) =====\n",
		stageNo, enemyName, enemyMaxHP, enemyATK);

	while (*pHP > 0.0f && enemyHP > 0.0f) {
		printf("\n무엇을 내겠습니까? (1=가위, 2=바위, 3=보) 입력: ");
		if (scanf_s("%d", &playerHand) != 1) {
			printf("입력이 올바르지 않습니다. 게임을 종료합니다.\n");
			return 0;
		}
		if (playerHand < 1 || playerHand > 3) {
			printf("1~3 중에서 선택하세요.\n");
			continue;
		}

		enemyHand = getEnemyHand();

		printf("당신: %s  vs  적: %s\n", handName(playerHand), handName(enemyHand));
		result = rpsResult(playerHand, enemyHand);

		if (result == 1) {
			enemyHP -= *pATK;
			if (enemyHP < 0.0f) enemyHP = 0.0f;
			printf("이겼습니다! 적에게 %.1f 피해를 입혔습니다.\n", *pATK);
		}
		else if (result == -1) {
			*pHP -= enemyATK;
			if (*pHP < 0.0f) *pHP = 0.0f;
			printf("졌습니다... 내가 %.1f 피해를 받았습니다.\n", enemyATK);
		}
		else {
			printf("비겼습니다. 피해가 없습니다.\n");
		}

		showStatus(*pHP, pMaxHP, enemyHP, enemyMaxHP);
	}

	if (*pHP <= 0.0f) {
		printf("\n쓰러졌습니다... (HP=0)\n");
		return 0; // 패배
	}

	/* 스테이지 클리어 */
	printf("\n스테이지 %d 클리어!\n", stageNo);

	/* 체력 전부 회복 */
	*pHP = pMaxHP;
	if (*pHP > 5.0f) *pHP = 5.0f; // 게임 내 최대체력 5

	/* 아이템 지급 (0=회복템, 1=공격력 +0.4) */
	int item = rand() % 2;
	if (item == 0) {
		printf("[보상] 회복템 획득! (이미 전부 회복됨)\n");
	}
	else {
		*pATK += 0.4f;
		printf("[보상] 공격력 강화! ATK +0.4 → 현재 공격력=%.1f\n", *pATK);
	}

	printf("체력 전부 회복! 현재 HP=%.1f (최대 5.0)\n", *pHP);
	return 1; // 승리
}

int main(void) {
	int character = 0;     // 1=철수, 2=영희
	float playerHP = 0.0f; // 현재 체력
	float playerATK = 0.0f;// 현재 공격력
	float playerMaxHP = 0.0f; // 캐릭터 최대 체력(스테이지 회복 기준)
	int gameOn = 1;

	/* 난수 시드 설정 (명시적 캐스팅으로 경고 방지) */
	time_t now = time(NULL);
	unsigned int seed = (unsigned int)now;
	srand(seed);

	while (gameOn) {
		/* 캐릭터 선택 */
		printf("\n=== 가위 바위 보 RPG 게임 시작! ===\n");
		printf("캐릭터를 선택하시오.\n");
		printf("철수 = 1, 영희 = 2 를 누르세요: ");

		if (scanf_s("%d", &character) != 1) {
			printf("입력이 올바르지 않습니다. 프로그램을 종료합니다.\n");
			break;
		}

		if (character == 1) {
			playerMaxHP = 3.0f;  // 철수 ♡♡♡
			playerATK = 1.0f;  // ATK 1.0
			playerHP = playerMaxHP;
			printf("\n[철수 선택] HP=♥♥♥, 공격력=1.0f\n");
		}
		else if (character == 2) {
			playerMaxHP = 2.0f;  // 영희 ♡♡
			playerATK = 1.5f;  // ATK 1.5
			playerHP = playerMaxHP;
			printf("\n[영희 선택] HP=♥♥, 공격력=1.5f\n");
		}
		else 
		{
			printf("1 또는 2를 선택하세요.\n");
			continue; // 선택 다시
		}

		/* 스테이지 1 */
		if (!playStage(1, &playerHP, &playerATK, playerMaxHP, 3.0f, 1.0f, "적1(♥♥♥, 공격력1.0)")) 
		{
			printf("캐릭터 선택부터 다시 시작합니다.\n");
			continue; // 캐릭터 선택으로 돌아감
		}

		/* 스테이지 2 */
		if (!playStage(2, &playerHP, &playerATK, playerMaxHP, 2.0f, 1.5f, "적2(♥♥, 공격력1.5)")) 
		{
			printf("캐릭터 선택부터 다시 시작합니다.\n");
			continue;
		}

		/* 보스 */
		if (!playStage(3, &playerHP, &playerATK, playerMaxHP, 4.0f, 2.0f, "보스(♥♥♥♥, 공격력2.0)")) 
		{
			printf("캐릭터 선택부터 다시 시작합니다.\n");
			continue;
		}

		/* 모든 스테이지 클리어 */
		printf("\n스테이지 1 클리어, 스테이지 2 클리어, 보스를 물리쳤습니다!\n");
		printf("게임 끝! 플레이해 주셔서 감사합니다.\n");
		break; // 프로그램 종료
	}

	return 0;
}
