#include "Game.h"

// 프로젝트 
// 로그라이크 모험 게임 

// 플레이어와 게임 상태를 관리하는 구조체
// const static 사용해보기 




// main함수 
int main() {
	char RestartChoice = 0;
	CharacterType* character;
	WARRIOR warrior;
	THIEF thief;
	ENEMY Enemy1;
	ENEMY Enemy2;
	ENEMY Boss;
	

	// 게임 재시작을 위한 while 루프
	srand(time(NULL)); // 난수 생성기 초기화 srand(time(NULL));를 매 턴에서 호출하면 같은 초 안에 입력하면 같은 난수가 나올 수 있습니다. 게임 시작 전에 한 번만 호출
	while (1) {
		SelectCharacter(&character);
		Battlestat(&warrior, &thief, &Enemy1, &Enemy2, &Boss);
		BattleHealth(&character, &warrior, &thief, &Enemy1, &Enemy2, &Boss);
		StartBattle(&character, &warrior, &thief, &Enemy1, &Enemy2, &Boss);
		stageReward(&character, &warrior, &thief, &Enemy1, &Enemy2, &Boss);


		printf("게임을 다시 시작하시겠습니까? : (Y / N)  ");
		scanf(" %c", &RestartChoice);

		// 입력 버퍼 비우기 (다음 입력에 영향 없도록)
		int c;
		while ((c = getchar()) != '\n' && c != EOF); // EOF -> 파일의 끝 표시: 프로그램이 파일을 순차적으로 읽어나갈 때 더 이상 읽을 데이터가 없다는 것을 알려주는 역할


		// 'y'나 'Y'가 아니면 루프 종료
		if (RestartChoice != 'y' && RestartChoice != 'Y') { // != 같지 않다. y, Y가 아니면 게임을 끝내겠다.
			break;
		}
	}

	printf("\n게임을 종료합니다. 감사합니다!\n");
	return 0;
}

// 3 스테이지 구성 (스테이지 1, 스테이지 2, 보스)
// 배경 : 깊은 숲 속
// 각 스테이지 클리어 시 체력 전부 회복 공격력 0.4 증가템,  
// 스테이지1 클리어 시 스테이지 1 클리어, 스테이지 2 클리어, 보스를 물리쳤습니다. -> 게임 끝과 함께 프로그램 종료
// 전사, 도적 체력이 0이 되면 다시 캐릭터 선택부터 시작

// 캐릭터 정보
// 전사의 체력 = ♥♥♥, 30 공격력 10 방어력 5
// 도적의 체력 = ♥♥, 20 공격력 15 독데미지 3 반격데미지 5
// 산적1 = ♥♥♥, 30 공격력 10
// 산적2 = ♥♥, 20 공격력 14
// 산적 보스 = ♥♥♥♥, 40 공격력 20 방어력 5 , 체력 20 이하일 때 페이즈 2 : 방어력 7.5로 up  
// 게임 내 최대체력 ♥♥♥♥가 최대
// 체력 표시 ♥, 데미지를 입은 체력 ♡, 반 체력 ◐ 

// 게임 흐름 
// 공격: 공격력만큼 데미지를 준다
// 강한 공격: 1.5배만큼 데미지를 준다, 강한 공격은 충전 필요 3턴에 한번 사용 가능 
// 독칼 공격:  공격력의 절반데미지 + 중독 부여 매턴 시작 시 1.5씩 데미지를 준다. 
// 회피: 공격을 피할 확률 12.5% 확률
// 방어력만큼 방어 후 데미지 입음.
// 스테이지 끝날 시 보상  1. 공격력 증가템 or 2. 체력 회복 요소(full 회복)
// 게임오버 playerHealthpoint = 0이면 다시 게임 캐릭터 선택으로 돌아감.
// 게임종료 = Esc or p 버튼
// 공격 vs 방어일때 방어 선택자 데미지 = 방어력 - 공격력
// 회피율 플레이어 20%
// 회피율 적 10%  

// 추가 요소 
// 스테이지 클리어 후 경로 2가지 중 하나 택일 왼쪽 = 1, 오른쪽 = 2 을 누르세요
// 중독데미지는 최대 1중첩, 3턴 동안 유지 
// 스테이지 클리어 후 체력 풀회복, 아이템 선택창 만들기(아이템 공격력 증가 or 방어력 증가)    

// 체력에 대한 표현을 변수로 대체하여 표현 ex) healthpoint == 30 -> 30을 변수로 대체


// 로그라이크 모험 게임 Version 1. 0. 0. 10/28 
// 함수 선언 void StartBattle(); void Characterchoice();, Characterchoice함수 관련 오류 발생. 스테이지 1구성 중에 중단

// 로그라이크 모험 게임 Version 1. 0. 1. 11/05  
// Characterchoice함수 -> StartCharacterchoice로 수정, 기존 Characterchoice 변수 -> Character로 변경
// 0x00007FFCCDB4C5A6(ucrtbased.dll)에(test2.exe의) 처리되지 않은 예외가 있습니다. 0xC0000005: 0x00007FF6D99811D1 위치를 기록하는 동안 액세스 위반이 발생
// 캐릭터 선택 1을 누를 시 무한 반복 발생 -> CharacterPtr -> Character로 수정하여 해결, 2를 누를 시 플레이어 선택사항에 따라서 컴퓨터와 대전
// 체력 계산 후 현재 체력 명시 코드 필요, 플레이어 현재체력 출력 코드 필요

// 로그라이크 모험 게임 Version 1. 0. 2. 11/06 
// 기존 캐릭터 선택 if문 -> enum(열거형) 수정. 수정에 따라 Startbattle함수에서 selectCharactert에 따른 characterchoice 받아야함.

// 로그라이크 모험 게임 Version 1. 0. 3. 11/10 
// 열거형 포인터 기존 Chracter -> selectcharacter로 변수 조정, Startbattle while반복문 무한 반복문 탈출용 break; 추가
// 체력 계산 및 현재 체력 코드 필요. 
// SetplayerStat(selectCharacter, *baseHPptr, *baseATKptr, *baseDEFptr); 에서 역참조값을 대입하는 경우 주소를 받는 것이 아닌 값을 받는 행위이다.
// 즉, 주소를 받아야 하는데 값을 받았기 때문에(ptr은 포인터가 가리키는 실제 정수값임) NULL 또는 잘못된 주소로 처리되고, 역참조 시 크래시 발생.
//  SetplayerStat(selectCharacter, baseHPptr, baseATKptr, baseDEFptr); 로 수정하여 버그 해결
// selectCharacter를 1 또는 2 선택사항에 대한 입력값이 무시되어 플레이어 선택사항을 건너뛰는 문제 발생. -> selectCharacter = input으로 하여 해결. input = 0 이후 *selectCharacter = input하면
// NULL 포인터가 되어 읽기 액세스 위반 발생 
// 캐릭터선택에 따라 행동사항을 다르게 하기 위한 입력값 인식에 문제 발생으로 무한루프 발생 -> void함수에서 input을 main으로 옮긴 후 해결, void에서 지역변수의 개념으로 인식하여 매함수마다 넣어줘야함
// 그래서 input은 전역변수로 선언

// 로그라이크 모험 게임 Version 1. 0. 4. 11/11 
// 체력 명시 코드 작성, 30 -15-15 인데 0으로 인식 x 
// Restartchoice 앞에 %c에 입력 시 주소 연산자 & 추가하여 버그 해결
// 배열 함수 활용하여 도적일 경우 3번 사항에 회피 발생 코드 추가
// 회피 시 반격데미지 5 추가를 위해 int baseCTRptr 및 포인터 선언
// + *baseDEFptr, + Enemy.def 로 방어력까지 고려하여 체력 계산  
// 도적 독칼 공격에 대한 POISON 선언 및 변수 대입
// 전사 선택사항과 도적 선택사항, 산적1의 선택사항에 따른 결과 표시 및 체력 계산 코드 변동
// StageReward 함수 선언 -> 스테이지 클리어에 대한 보상 공격력 4 업 or 전체 체력 회복 추후에 추가 예정
// 독칼 공격 및 적의 회피 후 체력 계산 코드 출력 이후 현재 체력이 나타나지 않는 현상 발생. 

// 로그라이크 모험 게임 Version 1. 0. 5. 11/13 
//  전사, 도적일 때의 경우의 수에 맞게 Startbattle함수의 공격 판정 코드 선언

// 로그라이크 모험 게임 Version 1. 0. 5. 11/17
// 스테이지 보상 함수 선언
// bool함수로 상태이상 독 구현 코드 선언, 아직 수정 필요.
// 중독이 도적이 2번 공격에 성공했을 때 구현되도록 수정 필요.

// 로그라이크 모험 게임 Version 1. 0. 5. 11/24
// 헤더파일 구조체, 열거형으로 캐릭터 스탯 정보 선언
// 버그 발생 -> 함수 인수 대조
//