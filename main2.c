#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> // Sleep �Լ��� ���� �߰�

// ���������� ���� ��ũ��
#define SCISSORS 1
#define ROCK 2
#define PAPER 3

// �Լ� ����
void print_health(int health);
void play_stage(int stage, double* playerHealth, double* playerAttack);

int main() {
    int playerCharacter = 0; // 1:ö��, 2:����
    double playerHealth = 0;
    double playerAttack = 0;

    // ���� ����: ���� ���� �� �ٽ� �����ϱ� ����
    while (1) {
        srand(time(NULL)); // ���� �õ� �ʱ�ȭ

        // ĳ���� ����
        printf("���� ���� �� ���� ����!\n\n");
        printf("����� ĳ���͸� �����Ͻÿ�.\n");
        printf("ö���� 1, ����� 2�� �������� : ");
        scanf_s("%d", &playerCharacter);

        if (playerCharacter == 1) {
            printf("����� ö���� �����߽��ϴ�!\n");
            playerHealth = 3;
            playerAttack = 1.0;
        }
        else if (playerCharacter == 2) {
            printf("����� ���� �����߽��ϴ�!\n");
            playerHealth = 2;
            playerAttack = 1.5;
        }
        else {
            printf("�߸��� �����Դϴ�. �ٽ� �������ּ���.\n\n");
            continue; // ���� ó������ ���ư�
        }

        // 3�ܰ� ���� ����
        int stage;
        for (stage = 1; stage <= 3; stage++) {
            play_stage(stage, &playerHealth, &playerAttack);

            // �÷��̾� ü���� 0�� �Ǹ� ���� ����
            if (playerHealth <= 0) {
                printf("\nĳ������ ü���� ��� �����Ǿ����ϴ�. ���� ����!\n");
                break;
            }
        }

        // ���� ���� Ȥ�� ���� Ŭ���� ���� Ȯ��
        if (playerHealth <= 0) {
            printf("\n���ο� ĳ���ͷ� �ٽ� �����Ͻðڽ��ϱ�? (1:��, �ٸ� Ű:����) ");
            int restart;
            scanf_s("%d", &restart);
            if (restart != 1) {
                break; // ���α׷� ����
            }
        }
        else {
            printf("\n\n��� ���� �����ƽ��ϴ�! ���� Ŭ����!\n");
            break; // ���α׷� ����
        }
    }

    printf("\n������ �����մϴ�.\n");
    return 0;
}

// ü�� ��Ʈ ��� �Լ�
void print_health(int health) {
    int maxHealth = 5;
    if (health > maxHealth) health = maxHealth;
    for (int i = 0; i < health; i++) {
        printf("��");
    }
    for (int i = health; i < maxHealth; i++) {
        printf("��");
    }
}

// �� �������� ���� �Լ�
void play_stage(int stage, double* playerHealth, double* playerAttack) {
    double enemyHealth;
    double enemyAttack;
    char* enemyName;

    // ���������� �� ����
    if (stage == 1) {
        enemyHealth = 3;
        enemyAttack = 1.0;
        enemyName = "��1";
    }
    else if (stage == 2) {
        enemyHealth = 2;
        enemyAttack = 1.5;
        enemyName = "��2";
    }
    else { // stage == 3 (����)
        enemyHealth = 4;
        enemyAttack = 2.0;
        enemyName = "����";
    }

    printf("\n\n--- �������� %d: %s ���� ��� ---\n", stage, enemyName);

    // �������� ���� ����
    while (*playerHealth > 0 && enemyHealth > 0) {
        int playerChoice;
        int computerChoice = (rand() % 3) + 1;

        printf("\n���� �÷��̾� ü��: ");
        print_health((int)*playerHealth);
        printf(", ���� %s ü��: ", enemyName);
        print_health((int)enemyHealth);

        printf("\n������ ���ڽ��ϱ�? (1:����, 2:����, 3:��) : ");
        scanf_s("%d", &playerChoice);

        char* playerHand;
        char* computerHand;

        // ������ ���ڿ��� ��ȯ
        switch (playerChoice) {
        case SCISSORS: playerHand = "����"; break;
        case ROCK: playerHand = "����"; break;
        case PAPER: playerHand = "��"; break;
        default: playerHand = "�� �� ����"; break;
        }

        switch (computerChoice) {
        case SCISSORS: computerHand = "����"; break;
        case ROCK: computerHand = "����"; break;
        case PAPER: computerHand = "��"; break;
        }

        printf("�÷��̾�: %s, %s: %s\n", playerHand, enemyName, computerHand);

        // ���� ����
        if (playerChoice == computerChoice) {
            printf("�����ϴ�.\n");
        }
        else if ((playerChoice == SCISSORS && computerChoice == PAPER) ||
            (playerChoice == ROCK && computerChoice == SCISSORS) ||
            (playerChoice == PAPER && computerChoice == ROCK)) {
            printf("�÷��̾ �¸��߽��ϴ�!\n");
            enemyHealth -= *playerAttack;
        }
        else {
            printf("�÷��̾ �й��߽��ϴ�.\n");
            *playerHealth -= enemyAttack;
        }

        Sleep(1000); // 1�� ���
    }

    // �������� ���� �� ���
    if (*playerHealth > 0) {
        printf("\n--- %s�� �����ƽ��ϴ�! �������� %d Ŭ����! ---\n", enemyName, stage);
    }
}
