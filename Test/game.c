#include "Game.h"


void SelectCharacter(CharacterType* character)
{
	int input = 0;
	while (1)
	{

		printf("==================================\n");
		printf("      로그라이크 모험게임\n");
		printf("==================================\n");
		printf(" 전사 체력 ♥♥♥(30) 공격력 10 방어력(5)\n\n");
		printf(" 도적 체력 ♥♥(20) 공격력 15 회피력: 20%\n\n");
		printf("전사 = 1, 도적 = 2를 누르세요 : \n"); // 숫자 1입력 시 전사, 2입력 시 도적


		if (scanf("%d", &input) == 1)
		{
			*character = WARRIOR_TYPE;
			break;
		}
		else if (input == 1)
		{
			*character = THIEF_TYPE;
			break;
		}
		else
		{
			printf("잘못된 입력입니다. 1 또는 2를 입력해주세요.\n");
		}
	}
}

void Battlestat(WARRIOR* warrior, THIEF* thief, ENEMY* Enemy1, ENEMY* Enemy2, ENEMY* Boss)
{
	warrior->hp = 30;
	warrior->atk = 10;
	warrior->def = 5;
	warrior->condition = 0;

	thief->hp = 20;
	thief->atk = 15;
	thief->poison = 3;
	thief->ctr = 5;
	thief->condition = 5;

	Enemy1->hp = 30;
	Enemy1->atk = 10;
	Enemy1->def = 5;
	Enemy1->condition = 0;

	Enemy2->hp = 20;
	Enemy2->atk = 14;
	Enemy2->def = 0;
	Enemy2->condition = 0;

	Boss->hp = 40;
	Boss->atk = 20;
	Boss->def = 5;
	Boss->condition = 0;
}

void BattleHealth(CharacterType* character, WARRIOR* warrior, THIEF* thief, ENEMY* Enemy1, ENEMY* Enemy2, ENEMY* Boss)
{
	// 현재 체력 명시 코드
		//if (playerchoice > 0 && playerchoice <= 3 && Enemychoice > 0 && Enemychoice <= 3)
	{
		if (*character == WARRIOR_TYPE) {
			if (warrior->hp == 30)
				printf("나의 체력 : ♥♥♥\n");
			else if (warrior->hp > 20 && warrior->hp < 30)
				printf("나의 체력 : ♥♥◐\n");
			else if (warrior->hp == 20)
				printf("나의 체력 : ♥♥♡\n");
			else if (warrior->hp > 10 && warrior->hp < 20)
				printf("나의 체력 : ♥◐♡\n");
			else if (warrior->hp == 10)
				printf("나의 체력 : ♥♡♡\n");
			else if (warrior->hp > 0 && warrior->hp < 10)
				printf("나의 체력 : ◐♡♡\n");
			else if (warrior->hp <= 0)
				printf("나의 체력 : ♡♡♡\n");
		}

		if (*character == THIEF_TYPE) {
			if (thief->hp == 20)
				printf("나의 체력 : ♥♥\n");
			else if (thief->hp > 10 && thief->hp < 20)
				printf("나의 체력 : ♥◐\n");
			else if (thief->hp == 10)
				printf("나의 체력 : ♥♡\n");
			else if (thief->hp > 0 && thief->hp < 10)
				printf("나의 체력 : ◐♡\n");
			else if (thief->hp <= 0)
				printf("나의 체력 : ♡♡\n");
		}

		if (Enemy1->hp == 30)
			printf("산적1의 체력 : ♥♥♥\n");
		else if (Enemy1->hp > 20 && Enemy1->hp < 30)
			printf("산적1의 체력 : ♥♥◐\n");
		else if (Enemy1->hp == 20)
			printf("산적1의 체력 : ♥♥♡\n");
		else if (Enemy1->hp > 10 && Enemy1->hp < 20)
			printf("산적1의 체력 : ♥◐♡\n");
		else if (Enemy1->hp == 10)
			printf("산적1의 체력 : ♥♡♡\n");
		else if (Enemy1->hp > 0 && Enemy1->hp < 10)
			printf("산적1의 체력 : ◐♡♡\n");
		else if (Enemy1->hp <= 0)
			printf("산적1의 체력 : ♡♡♡\n");
	}

}

void StartBattle(CharacterType* character, WARRIOR* warrior, THIEF* thief, ENEMY* Enemy1, ENEMY* Enemy2, ENEMY* Boss)
{
	int playerchoice = 0; // 플레이어 선택사항
	//srand(time(NULL)); // 난수 생성기 초기화 srand(time(NULL));를 매 턴에서 호출하면 같은 초 안에 입력하면 같은 난수가 나올 수 있습니다. 게임 시작 전에 한 번만 호출
	int Enemychoice = 0; // 적 선택사항

	printf("스테이지 1 시작!\n");
	printf("산적1이 나타났다!\n\n");
	printf("산적1 체력 ♥♥♥(%d) 공격력(%d) 방어력(%d)\n", Enemy1->hp, Enemy1->atk, Enemy1->def);
	printf("적의 선택 사항 : 공격 = 1, 방어 = 2, 회피 = 3\n\n");
	// 전투를 위한 while 루프
	while (warrior->hp > 0 && Enemy1->hp > 0) {
		// stage 1  적1 체력 ♥♥♥ 공격력 10


		// 전사, 도적 선택에 맞춰 행동 선택사항 출력코드 
		if (*character == WARRIOR_TYPE) {
			printf("공격(1) 강한 공격(2) 방어(3) 중 해당 숫자를 입력하세요 : ");
			scanf("%d", &playerchoice);
		}
		else if (*character == THIEF_TYPE)
		{
			printf("공격(1) 독칼 공격(2) 회피(3) 중 해당 숫자를 입력하세요 :  ");
			scanf("%d", &playerchoice);
		}

		//적 난수 생성
		int Enemychoice = rand() % 3 + 1; // 1~3 사이의 난수 생성 (1 = 공격, 2 = 방어, 3 = 회피)
		printf("적의 선택: %d\n", Enemychoice);

		// 적 회피 구현 코드
		char EnemyMiss = 'a' + (rand() % 5);
		// 도적 회피 구현 코드
		char THIEFMiss = 'a' + (rand() % 5);

		// 플레이어 공격, 강한 공격, 독칼, 방어, 회피 vs 적의 공격, 방어, 회피에 대한 계산 
			//전사
			//공격 강한 공격 방어 1 2 3

			//도적
			//공격 독칼공격 회피반격 1 2 3

			//산적1
			//공격 방어 회피 1 2 3

			//전사일 때
		{
			//1 vs 1 비김
			if (character == WARRIOR_TYPE && playerchoice == 1 && Enemychoice == 1) {
				printf("\n서로 공격하여 비겼습니다.\n");
			}
			else if (character == WARRIOR_TYPE && playerchoice == 1 && Enemychoice == 2)
			{
				//1 vs 2 산적1방어력 - 전사 공격력
				printf("\n공격하였습니다.\n");

				Enemy1->hp = Enemy1->hp + Enemy1->def - warrior->atk;
			}
			else if (character == WARRIOR_TYPE && playerchoice == 1 && Enemychoice == 3)
			{
				//1 vs 3 회피 c가 나온 경우 회피
				if (EnemyMiss == 'c') {
					printf("a ~ e 중 나온 알파벳 : %c\n", EnemyMiss);
					printf("\n산적1은 회피하였습니다,\n");
				}
				//1 vs 3 회피 c외에 나온 경우 공격력 그대로
				else if (EnemyMiss != 'c') {
					printf("a ~ e 중 나온 알파벳 : %c\n", EnemyMiss);
					printf("\n산적1은 회피에 실패했습니다,\n");
					Enemy1->hp = Enemy1->hp - warrior->atk;
				}
			}
			//2 vs 1 강한 공격 데미지, 산적1공격 데미지
			else if (character == WARRIOR_TYPE && playerchoice == 2 && Enemychoice == 1) {
				printf("\n산적1의 공격을 뚫고 강하게 공격하였습니다.\n");
				Enemy1->hp = Enemy1->hp - warrior->atk * 1.5;
			}
			//2 vs 2 강한 공격 - 산적1 방어력
			else if (character == WARRIOR_TYPE && playerchoice == 2 && Enemychoice == 2)
			{
				printf("\n공격하였습니다.\n");
				Enemy1->hp = Enemy1->hp + Enemy1->def - warrior->atk * 1.5;
			}
			else if (character == WARRIOR_TYPE && playerchoice == 2 && Enemychoice == 3)
			{
				//2 vs 3 회피 c가 나온 경우 회피
				if (EnemyMiss == 'c') {
					printf("a ~ e 중 나온 알파벳 : %c\n", EnemyMiss);
					printf("\n산적1은 회피하였습니다,\n");
				}
				//2 vs 3 회피 c외에 나온 경우 강한공격력 그대로
				else if (EnemyMiss != 'c') {
					printf("a ~ e 중 나온 알파벳 : %c\n", EnemyMiss);
					printf("\n산적1은 회피에 실패했습니다,\n");
					Enemy1->hp = Enemy1->hp - warrior->atk * 1.5;
				}
			}
			//3 vs 1 전사 방어력 - 산적 1 공격력
			else if (character == WARRIOR_TYPE && playerchoice == 3 && Enemychoice == 1) {
				printf("\n산적1의 공격을 뚫고 강하게 공격하였습니다.\n");
				warrior->hp = warrior->hp - Enemy1->atk;
			}

			//3 vs 2 방어 방어 둘다 쫄아있다
			else if (character == WARRIOR_TYPE && playerchoice == 3 && Enemychoice == 2)
			{
				printf("\n둘 다 방어만 하면서 쫄았다.\n");
			}
			//3 vs 3 아무 일도 일어나지 않았다
			else if (character == WARRIOR_TYPE && playerchoice == 3 && Enemychoice == 3)
			{
				printf("\n아무 일도 일어나지 않았다.\n");
			}
		}

		if (character == THIEF_TYPE)
		{
			//1 vs 1 비김
			if (character == THIEF_TYPE && playerchoice == 1 && Enemychoice == 1) {
				printf("\n서로 공격하여 비겼습니다.\n");
			}
			else if (character == THIEF_TYPE && playerchoice == 1 && Enemychoice == 2)
			{
				//1 vs 2 산적1방어력 - 도적 공격력
				printf("\n공격하였습니다.\n");
				Enemy1->hp = Enemy1->hp + Enemy1->def - thief->atk;
			}
			else if (character == THIEF_TYPE && playerchoice == 1 && Enemychoice == 3)
			{
				//1 vs 3 회피 c가 나온 경우 회피
				if (EnemyMiss == 'c') {
					printf("a ~ e 중 나온 알파벳 : %c\n", EnemyMiss);
					printf("\n산적1은 회피하였습니다,\n");
				}
				//1 vs 3 회피 c외에 나온 경우 공격력 그대로
				else if (EnemyMiss != 'c') {
					printf("a ~ e 중 나온 알파벳 : %c\n", EnemyMiss);
					printf("\n산적1은 회피에 실패했습니다,\n");
					Enemy1->hp = Enemy1->hp - thief->atk;
				}
			}
			//2 vs 1 상태이상 중독, 산적1공격 데미지
			else if (character == THIEF_TYPE && playerchoice == 2 && Enemychoice == 1) {
				printf("\n독칼로 공격합니다.\n");
				printf("산적1에게 독칼공격을 받았습니다.\n");
				Enemy1->hp = Enemy1->hp - thief->poison;
				thief->hp = thief->hp - Enemy1->atk;
			}
			//2 vs 2 상태이상 중독
			else if (character == THIEF_TYPE && playerchoice == 2 && Enemychoice == 2)
			{
				printf("\n적의 빈틈에 독칼로 공격했습니다.\n");
				Enemy1->hp = Enemy1->hp - thief->poison;
			}
			else if (character == THIEF_TYPE && playerchoice == 2 && Enemychoice == 3)
			{
				//2 vs 3 회피 c가 나온 경우 회피
				if (THIEFMiss == 'c') {
					printf("a ~ e 중 나온 알파벳 : %c\n", THIEFMiss);
					printf("\n산적1은 회피하였습니다,\n");
				}
				//2 vs 3 회피 c외에 나온 경우 강한공격력 그대로
				else if (THIEFMiss != 'c') {
					printf("a ~ e 중 나온 알파벳 : %c\n", THIEFMiss);
					printf("\n산적1은 회피에 실패했습니다,\n");
					printf("산적 1은 독칼 공격을 받았습니다.\n");
					Enemy1->hp = Enemy1->hp - thief->poison;
				}
			}

			else if (character == THIEF_TYPE && playerchoice == 3 && Enemychoice == 1) {
				char THIEFMiss = 'a' + (rand() % 5);
				//3 vs 1 회피 c가 나온 경우 회피
				if (THIEFMiss == 'c') {
					printf("a ~ e 중 나온 알파벳 : %c\n", THIEFMiss);
					printf("\n도적은 회피하고 반격하였습니다,\n");
					Enemy1->hp = Enemy1->hp - thief->ctr;
				}
				//3 vs 1 회피 c외에 나온 경우 강한공격력 그대로
				else if (THIEFMiss != 'c') {
					printf("a ~ e 중 나온 알파벳 : %c\n", THIEFMiss);
					printf("\n도적은 회피에 실패했습니다,\n");
					thief->hp = thief->hp - Enemy1->atk;
				}
			}
			//3 vs 2 회피 방어 둘다 쫄아있다
			else if (character == THIEF_TYPE && playerchoice == 3 && Enemychoice == 2)
			{
				printf("아무 일도 일어나지 않았다.\n");
			}
			//3 vs 3 회피 회피 아무 일도 일어나지 않았다
			else if (character == THIEF_TYPE && playerchoice == 3 && Enemychoice == 3)
			{
				printf("서로 회피하고 난리다.\n");
			}
		}
	}
}

//void Conditon()
//{
//
//}

// 스테이지 클리어 보상 
void stageReward(CharacterType* character, WARRIOR* warrior, THIEF* thief, ENEMY* Enemy1, ENEMY* Enemy2, ENEMY* Boss)
{
	if (Enemy1->hp <= 0 && warrior->hp > 0 || Enemy1->hp <= 0 && thief->hp > 0)
	{
		int stagereward = 0;
		printf("스테이지 보상을 고르세요. \n");
		printf("1. 공격력 +4	2. 체력 회복 \n");
		scanf("%d", &stagereward);
		if (stagereward == 1)
		{
			warrior->atk = warrior->atk + 4;
			thief->atk = thief->atk + 4;
			if (character == warrior) {
				printf("공격력이 (%d)이(가) 되었습니다.\n", warrior->atk);
			}
			else if (character == thief) {
				printf("공격력이 (%d)이(가) 되었습니다.\n", thief->atk);
			}
		}
		else if (stagereward == 2)
		{
			warrior->hp = 30;
			thief->hp = 20;
			if (character == WARRIOR_TYPE) {
				printf("체력이 전부 회복되었습니다.\n", warrior->hp);
			}
			else if (character == THIEF_TYPE) {
				printf("공격력이 (%d)이(가) 되었습니다.\n", thief->hp);
			}
		}
		else
		{
			printf("잘못된 입력입니다. 다시 입력하세요.\n");
		}
	}
}