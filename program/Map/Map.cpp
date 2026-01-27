#include "Map.h"
#include "../System/TextView/TextView.h"
#include "../System/KeyInput/KeyInput.h"
#include<iostream>
#include <string>


/**
 * @brief Render the current floor's map information (header and selectable options).
 *
 * Builds display text for the current floor's "Up" and "Down" scene types, writes a header
 * and the composed stage line to the global TextView, then triggers rendering and resets the view.
 */
void Map::DrawInfo(/* Player�Ə�����*/)
{

	// �`�悷��e�L�X�g
	std::string drawText = "";

	// ���E�����̃X�e�[�W��
	std::string upStr = ReturnStr(m_floorTable[m_currentFloor].Up);
	std::string downStr = ReturnStr(m_floorTable[m_currentFloor].Down);


	//������: $$$
	//
	//player1 hp : 7 / 15
	//player2 hp : 22 / 40
	//player3 hp : 10 / 10

	// �e�L�X�g�C���X�^���X�擾
	auto& text = TextView::Instance();

	text.AddText("���̃X�e�[�W\n");

	std::string stageText = std::to_string(SELECT_UP) + " " + upStr + " | " +
		std::to_string(SELECT_DOWN) + " " + downStr;
	text.AddText(stageText + "\n");

	text.TextRender();
	text.ResetText();
}

/**
 * @brief Present an interactive menu to choose between the current floor's Up and Down options.
 *
 * Displays the Up and Down option strings for the current floor, allows navigation with the UP/DOWN keys
 * and confirmation with ENTER, then advances the current floor and returns the chosen scene type.
 *
 * @return SceneType The scene type corresponding to the selected option; the map's current floor index is incremented.
 */
SceneType Map::SelectScene()
{
	// ���̓C���X�^���X�擾
	auto& input = KeyInput::Instance();
	// �e�L�X�g�C���X�^���X�擾
	auto& text = TextView::Instance();

	int cursor = 0; // 0: UP, 1: DOWN
	bool selected = false;

	while (!selected)
	{
		// ���͍X�V
		input.Update();

		// �J�[�\���ړ�
		if (input.ChechKey(KeyInput::UP))   cursor = 0;
		if (input.ChechKey(KeyInput::DOWN)) cursor = 1;

		// ����
		if (input.ChechKey(KeyInput::ENTER)) {
			selected = true;
			break; // ���[�v�𔲂���
		}

		std::string upStr = ReturnStr(m_floorTable[m_currentFloor].Up);
		std::string downStr = ReturnStr(m_floorTable[m_currentFloor].Down);

		text.ResetText(); // �`��O�Ɉ�x���Z�b�g
		text.AddText("���̃X�e�[�W��I�����Ă��������F\n");

		// �I�𒆂̕��ɃJ�[�\����\��
		std::string display = (cursor == 0 ? "> " : "  ") + upStr + "\n" +
			(cursor == 1 ? "> " : "  ") + downStr + "\n";

		text.AddText(display);
		text.TextRender();
	}

	// �I�����ꂽ�V�[����Ԃ�
	// ���͂����鐔���ƃC���f�b�N�X�����킹��
	return ReturnScene(cursor);
}

/**
 * Selects the next scene type from the current floor's Up/Down option and advances the current floor.
 *
 * Advances the map's current floor index by one as a side effect.
 *
 * @param select Choice index: `0` selects the floor's Up scene, any other value selects the Down scene.
 * @return SceneType The scene type corresponding to the selected option.
 */
SceneType Map::ReturnScene(int select)
{
    const auto& floor = m_floorTable[m_currentFloor];
    
    SceneType type = (select == 0) ? floor.Up : floor.Down;

    // �K�w��i�߂�
    m_currentFloor++;
    return type;
}

/**
 * @brief Return the display label for a SceneType.
 *
 * @param type The scene type to convert into a display string.
 * @return std::string The label corresponding to `type`:
 * - `SceneType::BATTLE` -> "�퓬"
 * - `SceneType::SHOP`   -> "�V���b�v"
 * - `SceneType::EVENT`  -> "�C�x���g"
 * - `SceneType::BOSS`   -> "�{�X"
 * - default              -> "�����ȃV�[��"
 */
std::string Map::ReturnStr(SceneType type)
{

	std::string nextStr = "�����ȃV�[��";

	switch (type)
	{
	case SceneType::BATTLE:
		nextStr = "�퓬";
		return nextStr;

	case SceneType::SHOP:
		nextStr = "�V���b�v";
		return nextStr;

	case SceneType::EVENT:
		nextStr = "�C�x���g";
		return nextStr;

	case SceneType::BOSS:
		nextStr = "�{�X";
		return nextStr;

	default:
		return nextStr;
	}
}