#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> // Sleep 함수를 위해 추가

// 가위바위보 선택 매크로
#define SCISSORS 1
#define ROCK 2
#define PAPER 3

// 코드 흐름
// 가위 바위 보 게임 시작!
// 캐릭터를 선택하시오. 
// 철수 = 1, 영희 = 2를 누르세요 

// 3스테이지 구성 (스테이지 1, 스테이지 2, 보스)
// 각 스테이지 클리어 시 체력 전부 회복, 아이템 회복템 or 공격력 0.4 증가템 
// 스테이지1 클리어 시 스테이지 1 클리어, 스테이지 2 클리어, 보스를 물리쳤습니다. -> 게임 끝과 함께 프로그램 종료
// 철수, 영희 체력이 0이 되면 다시 캐릭터 선택부터 시작

// 캐릭터 정보
// 철수의 체력 = ♡♡♡, 3 공격력 1
// 영희의 체력 = ♡♡, 2 공격력 1.5
// 적1 = ♡♡♡, 3 공격력 1
// 적2 = ♡♡♡, 2 공격력 1.5
// 보스= ♡♡♡♡, 공격력 2
// 게임 내 최대체력 ♡♡♡♡♡가 최대

// 게임 흐름 : 가위 바위 보를 무엇을 내었는지 표현, 가위 바위 보 한판 후 이김, 짐, 비김 표현, 현재 체력, 현재 적 체력 명시





// 함수 선언
void print_health(int health); //void가 함수 이름 앞에 오면, 해당 함수는 어떤 값도 반환하지 않는다는 의미입니다. 
void choose_item(int* health, double* attack);

int main()
{
	printf("가위 바위 보 게임 시작! \n");



        int playerCharacter = 0; // 1:철수, 2:영희
        double playerHealth = 0; //double: 자료형 중 하나로, **실수(부동 소수점 수)**를 저장할 때 사용합니다. 
        double playerAttack = 0; 
        int playerChoice = 0;

        int stage = 1;

        // 무한 루프: 게임 오버 시 다시 시작하기 위함
        while (1) {
            srand(time(NULL)); // 난수 시드 초기화

            // 캐릭터 선택
            printf("가위 바위 보 게임 시작!\n\n");
            printf("당신의 캐릭터를 선택하시오.\n");
            printf("철수는 1, 영희는 2를 누르세요 : ");
            scanf_s("%d", &playerCharacter);

            if (playerCharacter == 1) {
                printf("당신은 철수를 선택했습니다!\n");
                playerHealth = 3;
                playerAttack = 1.0;
            }
            else if (playerCharacter == 2) {
                printf("당신은 영희를 선택했습니다!\n");
                playerHealth = 2;
                playerAttack = 1.5;
            }
            else {
                printf("잘못된 선택입니다. 다시 선택해주세요.\n\n");
                continue; // 루프 처음으로 돌아감
            }

            // 3단계 게임 진행
            for (stage = 1; stage <= 3; stage++) {
                double enemyHealth;
                double enemyAttack;
                char* enemyName;

                // 스테이지별 적 설정
                if (stage == 1) {
                    enemyHealth = 3;
                    enemyAttack = 1.0;
                    enemyName = "적1";
                }
                else if (stage == 2) {
                    enemyHealth = 2;
                    enemyAttack = 1.5;
                    enemyName = "적2";
                }
                else { // stage == 3 (보스)
                    enemyHealth = 4;
                    enemyAttack = 2.0;
                    enemyName = "보스";
                }

                printf("\n\n--- 스테이지 %d: %s 와의 대결 ---\n", stage, enemyName);

                // 스테이지 진행 루프
                while (playerHealth > 0 && enemyHealth > 0) {
                    int computerChoice = (rand() % 3) + 1;

                    printf("\n현재 플레이어 체력: ");
                    print_health((int)playerHealth);
                    printf(", 현재 %s 체력: ", enemyName);
                    print_health((int)enemyHealth);

                    printf("\n무엇을 내겠습니까? (1:가위, 2:바위, 3:보) : ");
                    scanf_s("%d", &playerChoice);

                    char* playerHand;
                    char* computerHand;

                    // 선택을 문자열로 변환
                    switch (playerChoice) {
                    case SCISSORS: playerHand = "가위"; break;
                    case ROCK: playerHand = "바위"; break;
                    case PAPER: playerHand = "보"; break;
                    default: playerHand = "알 수 없음"; break;
                    }

                    switch (computerChoice) {
                    case SCISSORS: computerHand = "가위"; break;
                    case ROCK: computerHand = "바위"; break;
                    case PAPER: computerHand = "보"; break;
                    }

                    printf("플레이어: %s, %s: %s\n", playerHand, enemyName, computerHand);

                    // 승패 판정
                    if (playerChoice == computerChoice) {
                        printf("비겼습니다.\n");
                    }
                    else if ((playerChoice == SCISSORS && computerChoice == PAPER) ||
                        (playerChoice == ROCK && computerChoice == SCISSORS) ||
                        (playerChoice == PAPER && computerChoice == ROCK)) {
                        printf("플레이어가 승리했습니다!\n");
                        enemyHealth -= playerAttack;
                    }
                    else {
                        printf("플레이어가 패배했습니다.\n");
                        playerHealth -= enemyAttack;
                    }

                    Sleep(1000); // 1초 대기
                }

                // 스테이지 종료 후 결과
                if (playerHealth <= 0) {
                    printf("\n캐릭터의 체력이 모두 소진되었습니다. 게임 오버!\n");
                    break; // 게임 오버이므로 스테이지 루프 탈출
                }
                else {
                    printf("\n--- %s를 물리쳤습니다! 스테이지 %d 클리어! ---\n", enemyName, stage);

                    // 보스까지 클리어했으면 게임 종료
                    if (stage == 3) {
                        break;
                    }

                    // 스테이지 클리어 보상
                    printf("플레이어의 체력이 모두 회복되었습니다.\n");
                    if (playerCharacter == 1) playerHealth = 3;
                    else playerHealth = 2;

                    choose_item((int*)&playerHealth, &playerAttack);
                }
            }

            // 게임 오버 혹은 게임 클리어 여부 확인
            if (playerHealth <= 0) {
                printf("\n새로운 캐릭터로 다시 도전하시겠습니까? (1:예) ");
                int restart;
                scanf_s("%d", &restart);
                if (restart != 1) {
                    break; // 프로그램 종료
                }
            }
            else {
                printf("\n\n모든 적을 물리쳤습니다! 게임 클리어!\n");
                break; // 프로그램 종료
            }
        }

        printf("\n게임을 종료합니다.\n");
        return 0;
    }

    // 체력 하트 출력 함수
    void print_health(int health) {
        for (int i = 0; i < health; i++) {
            printf("♡");
        }
    }

    // 아이템 선택 함수
    void choose_item(int* health, double* attack) {
        int itemChoice;
        printf("\n보상을 선택하세요!\n");
        printf("1. 회복 아이템 (체력 +1)\n");
        printf("2. 공격력 증가 아이템 (공격력 +0.4)\n");
        printf("선택 : ");
        scanf_s("%d", &itemChoice);

        if (itemChoice == 1) {
            (*health)++;
            printf("체력이 1 증가했습니다!\n");
        }
        else if (itemChoice == 2) {
            (*attack) += 0.4;
            printf("공격력이 0.4 증가했습니다!\n");
        }
        else {
            printf("잘못된 선택입니다. 보상을 받지 못했습니다.\n");
        }
    }

