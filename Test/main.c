#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ���������� ����: 1=����, 2=����, 3=�� */
int getEnemyHand(void) {
	return (rand() % 3) + 1;
}

const char* handName(int h) {
	if (h == 1) return "����";
	if (h == 2) return "����";
	return "��";
}

/* ���� 1���� ó��: ���� ��ȯ (1=�÷��̾� ��, -1=��, 0=��) */
int rpsResult(int p, int e) {
	if (p == e) return 0;
	if ((p == 1 && e == 3) || (p == 2 && e == 1) || (p == 3 && e == 2)) return 1;
	return -1;
}

/* ���� ü�� ��� (�Ҽ� 1�ڸ�) */
void showStatus(float playerHP, float enemyHP) {
	printf("���� �� ü��: %.1f / ���� �� ü��: %.1f\n", playerHP, enemyHP);
}

/* �� �������� ���� ���� (�÷��̾ �̱�� 1, ���� 0) */
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

	printf("\n===== �������� %d: %s ����! (�� HP=%.1f, ATK=%.1f) =====\n",
		stageNo, enemyName, enemyMaxHP, enemyATK);

	while (*pHP > 0.0f && enemyHP > 0.0f) {
		printf("\n������ ���ڽ��ϱ�? (1=����, 2=����, 3=��) �Է�: ");
		if (scanf_s("%d", &playerHand) != 1) {
			printf("�Է��� �ùٸ��� �ʽ��ϴ�. ������ �����մϴ�.\n");
			return 0;
		}
		if (playerHand < 1 || playerHand > 3) {
			printf("1~3 �߿��� �����ϼ���.\n");
			continue;
		}

		enemyHand = getEnemyHand();

		printf("���: %s  vs  ��: %s\n", handName(playerHand), handName(enemyHand));
		result = rpsResult(playerHand, enemyHand);

		if (result == 1) {
			enemyHP -= *pATK;
			if (enemyHP < 0.0f) enemyHP = 0.0f;
			printf("�̰���ϴ�! ������ %.1f ���ظ� �������ϴ�.\n", *pATK);
		}
		else if (result == -1) {
			*pHP -= enemyATK;
			if (*pHP < 0.0f) *pHP = 0.0f;
			printf("�����ϴ�... ���� %.1f ���ظ� �޾ҽ��ϴ�.\n", enemyATK);
		}
		else {
			printf("�����ϴ�. ���ذ� �����ϴ�.\n");
		}

		showStatus(*pHP, enemyHP);
	}

	if (*pHP <= 0.0f) {
		printf("\n���������ϴ�... (HP=0)\n");
		return 0; // �й�
	}

	/* �������� Ŭ���� */
	printf("\n�������� %d Ŭ����!\n", stageNo);

	/* ü�� ���� ȸ�� */
	*pHP = pMaxHP;
	if (*pHP > 5.0f) *pHP = 5.0f; // ���� �� �ִ�ü�� 5

	/* ������ ���� (0=ȸ����, 1=���ݷ� +0.4) */
	int item = rand() % 2;
	if (item == 0) {
		printf("[����] ȸ���� ȹ��! (�̹� ���� ȸ����)\n");
	}
	else {
		*pATK += 0.4f;
		printf("[����] ���ݷ� ��ȭ! ATK +0.4 �� ���� ATK=%.1f\n", *pATK);
	}

	printf("ü�� ���� ȸ��! ���� HP=%.1f (�ִ� 5.0)\n", *pHP);
	return 1; // �¸�
}

int main(void) {
	int character = 0;     // 1=ö��, 2=����
	float playerHP = 0.0f; // ���� ü��
	float playerATK = 0.0f;// ���� ���ݷ�
	float playerMaxHP = 0.0f; // ĳ���� �ִ� ü��(�������� ȸ�� ����)
	int gameOn = 1;

	/* ���� �õ� ���� (����� ĳ�������� ��� ����) */
	time_t now = time(NULL);
	unsigned int seed = (unsigned int)now;
	srand(seed);

	while (gameOn) {
		/* ĳ���� ���� */
		printf("\n=== ���� ���� �� RPG ���� ����! ===\n");
		printf("ĳ���͸� �����Ͻÿ�.\n");
		printf("ö�� = 1, ���� = 2 �� ��������: ");

		if (scanf_s("%d", &character) != 1) {
			printf("�Է��� �ùٸ��� �ʽ��ϴ�. ���α׷��� �����մϴ�.\n");
			break;
		}

		if (character == 1) {
			playerMaxHP = 3.0f;  // ö�� ������
			playerATK = 1.0f;  // ATK 1.0
			playerHP = playerMaxHP;
			printf("\n[ö�� ����] HP=%.1f, ATK=%.1f\n", playerHP, playerATK);
		}
		else if (character == 2) {
			playerMaxHP = 2.0f;  // ���� ����
			playerATK = 1.5f;  // ATK 1.5
			playerHP = playerMaxHP;
			printf("\n[���� ����] HP=%.1f, ATK=%.1f\n", playerHP, playerATK);
		}
		else {
			printf("1 �Ǵ� 2�� �����ϼ���.\n");
			continue; // ���� �ٽ�
		}

		/* �������� 1 */
		if (!playStage(1, &playerHP, &playerATK, playerMaxHP, 3.0f, 1.0f, "��1(HP3, ATK1.0)")) 
		{
			printf("ĳ���� ���ú��� �ٽ� �����մϴ�.\n");
			continue; // ĳ���� �������� ���ư�
		}

		/* �������� 2 */
		if (!playStage(2, &playerHP, &playerATK, playerMaxHP, 2.0f, 1.5f, "��2(HP2, ATK1.5)")) 
		{
			printf("ĳ���� ���ú��� �ٽ� �����մϴ�.\n");
			continue;
		}

		/* ���� */
		if (!playStage(3, &playerHP, &playerATK, playerMaxHP, 4.0f, 2.0f, "����(HP4, ATK2.0)")) 
		{
			printf("ĳ���� ���ú��� �ٽ� �����մϴ�.\n");
			continue;
		}

		/* ��� �������� Ŭ���� */
		printf("\n�������� 1 Ŭ����, �������� 2 Ŭ����, ������ �����ƽ��ϴ�!\n");
		printf("���� ��! �÷����� �ּż� �����մϴ�.\n");
		break; // ���α׷� ����
	}

	return 0;
}
