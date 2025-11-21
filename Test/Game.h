#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> // printf 함수 사용을 위한 헤더
#include <time.h> // 컴퓨터 난수 설정을 위한 헤더

typedef enum CharacterType {
	WARRIOR_TYPE = 1,
	THIEF_TYPE = 2,
	UNDEFINED_TYPE
}CharacterType;


// 전사 스탯
typedef struct WARRIOR {
	int hp;
	int atk;
	int def;
	int condition;
}WARRIOR;

// 도적 스탯
typedef struct THIEF {
	int hp;
	int atk;
	int poison;
	int ctr;
	int condition;
}THIEF;

// 적 스탯
typedef struct ENEMY {
	int hp;
	int atk;
	int def;
	int condition;
}ENEMY;

// 상태이상 열거형
typedef enum DEBUFF {
	POISON,
	BURNE,
	DARK
}DEBUFF;