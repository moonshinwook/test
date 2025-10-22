#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> // Sleep �Լ��� ���� �߰�

// ���������� ���� ��ũ��
#define SCISSORS 1
#define ROCK 2
#define PAPER 3

// �ڵ� �帧
// ���� ���� �� ���� ����!
// ĳ���͸� �����Ͻÿ�. 
// ö�� = 1, ���� = 2�� �������� 

// 3�������� ���� (�������� 1, �������� 2, ����)
// �� �������� Ŭ���� �� ü�� ���� ȸ��, ������ ȸ���� or ���ݷ� 0.4 ������ 
// ��������1 Ŭ���� �� �������� 1 Ŭ����, �������� 2 Ŭ����, ������ �����ƽ��ϴ�. -> ���� ���� �Բ� ���α׷� ����
// ö��, ���� ü���� 0�� �Ǹ� �ٽ� ĳ���� ���ú��� ����

// ĳ���� ����
// ö���� ü�� = ������, 3 ���ݷ� 1
// ������ ü�� = ����, 2 ���ݷ� 1.5
// ��1 = ������, 3 ���ݷ� 1
// ��2 = ������, 2 ���ݷ� 1.5
// ����= ��������, ���ݷ� 2
// ���� �� �ִ�ü�� ������������ �ִ�

// ���� �帧 : ���� ���� ���� ������ �������� ǥ��, ���� ���� �� ���� �� �̱�, ��, ��� ǥ��, ���� ü��, ���� �� ü�� ���





// �Լ� ����
void print_health(int health); //void�� �Լ� �̸� �տ� ����, �ش� �Լ��� � ���� ��ȯ���� �ʴ´ٴ� �ǹ��Դϴ�. 
void choose_item(int* health, double* attack);

int main()
{
	printf("���� ���� �� ���� ����! \n");



        int playerCharacter = 0; // 1:ö��, 2:����
        double playerHealth = 0; //double: �ڷ��� �� �ϳ���, **�Ǽ�(�ε� �Ҽ��� ��)**�� ������ �� ����մϴ�. 
        double playerAttack = 0; 
        int playerChoice = 0;

        int stage = 1;

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
            for (stage = 1; stage <= 3; stage++) {
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
                while (playerHealth > 0 && enemyHealth > 0) {
                    int computerChoice = (rand() % 3) + 1;

                    printf("\n���� �÷��̾� ü��: ");
                    print_health((int)playerHealth);
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
                        enemyHealth -= playerAttack;
                    }
                    else {
                        printf("�÷��̾ �й��߽��ϴ�.\n");
                        playerHealth -= enemyAttack;
                    }

                    Sleep(1000); // 1�� ���
                }

                // �������� ���� �� ���
                if (playerHealth <= 0) {
                    printf("\nĳ������ ü���� ��� �����Ǿ����ϴ�. ���� ����!\n");
                    break; // ���� �����̹Ƿ� �������� ���� Ż��
                }
                else {
                    printf("\n--- %s�� �����ƽ��ϴ�! �������� %d Ŭ����! ---\n", enemyName, stage);

                    // �������� Ŭ���������� ���� ����
                    if (stage == 3) {
                        break;
                    }

                    // �������� Ŭ���� ����
                    printf("�÷��̾��� ü���� ��� ȸ���Ǿ����ϴ�.\n");
                    if (playerCharacter == 1) playerHealth = 3;
                    else playerHealth = 2;

                    choose_item((int*)&playerHealth, &playerAttack);
                }
            }

            // ���� ���� Ȥ�� ���� Ŭ���� ���� Ȯ��
            if (playerHealth <= 0) {
                printf("\n���ο� ĳ���ͷ� �ٽ� �����Ͻðڽ��ϱ�? (1:��) ");
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
        for (int i = 0; i < health; i++) {
            printf("��");
        }
    }

    // ������ ���� �Լ�
    void choose_item(int* health, double* attack) {
        int itemChoice;
        printf("\n������ �����ϼ���!\n");
        printf("1. ȸ�� ������ (ü�� +1)\n");
        printf("2. ���ݷ� ���� ������ (���ݷ� +0.4)\n");
        printf("���� : ");
        scanf_s("%d", &itemChoice);

        if (itemChoice == 1) {
            (*health)++;
            printf("ü���� 1 �����߽��ϴ�!\n");
        }
        else if (itemChoice == 2) {
            (*attack) += 0.4;
            printf("���ݷ��� 0.4 �����߽��ϴ�!\n");
        }
        else {
            printf("�߸��� �����Դϴ�. ������ ���� ���߽��ϴ�.\n");
        }
    }

