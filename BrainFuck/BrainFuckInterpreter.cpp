#include "BrainfuckInterpreter.h"

using namespace ::std;

BrainfuckInterpreter::BrainfuckInterpreter() :
	m_tapePointer(m_tape),
	m_userCode(""),
	m_outputString("")
{
	for (size_t i = 0; i < TapeLength; i++)
	{
		m_tape[i] = 0;
	}
}

string BrainfuckInterpreter::Parse()
{
	ParseString();
	return RawTapeString();
}

void BrainfuckInterpreter::UserCodeInput(const string code)
{
	m_userCode = code;
}

string BrainfuckInterpreter::RawTapeString() const
{
	string tempString;
	for (const char c : m_tape)
	{
		if (c != 0)
			tempString += c;
	}
	return tempString;
}

string BrainfuckInterpreter::ToString() const
{
	return m_outputString;
}

void BrainfuckInterpreter::ParseString()
{
	for (auto strPos = m_userCode.begin(); strPos != m_userCode.end(); ++strPos)
	{
		ProcessInstruction(strPos);
	}
}

void BrainfuckInterpreter::ProcessInstruction(string::iterator& instructionPointer)
{
	switch (*instructionPointer)
	{
	case '+':
	case '-':
		AdjustCell(*instructionPointer);
		break;
	case '>':
	case '<':
		MoveCell(*instructionPointer);
		break;
	case '[':
	case ']':
		LoopHandler(instructionPointer);
		break;
	case '.':
		if (*m_tapePointer >= ' ')
			m_outputString += *m_tapePointer;
		break;
	default:
		break;
	}
}

void BrainfuckInterpreter::AdjustCell(char adjustment)
{
	if (adjustment == '+')
		*m_tapePointer += 1;
	else
		*m_tapePointer -= 1;
}

void BrainfuckInterpreter::MoveCell(char direction)
{
	char* tapeEnd = (m_tape + (sizeof(m_tape) - 1));
	if (direction == '>')
		m_tapePointer = (m_tapePointer != tapeEnd ? m_tapePointer + 1 : m_tape);
	else
		m_tapePointer = (m_tapePointer != m_tape ? m_tapePointer - 1 : tapeEnd);
}

void BrainfuckInterpreter::LoopHandler(string::iterator& loopPoint)
{
	if (*loopPoint == '[')
	{
		*m_tapePointer == 0 ? JumpToEndLoop(loopPoint) : m_loopStart.push(loopPoint);
		return;
	}
	else
	{
		if (!m_loopStart.empty() && *m_tapePointer == 0)
		{
			m_loopStart.pop();
			return;
		}
	}
	loopPoint = m_loopStart.top();
}

void BrainfuckInterpreter::JumpToEndLoop(std::string::iterator& loopPoint)
{
	size_t loopStackSize = m_loopStart.size();
	m_loopStart.push(loopPoint);
	for (auto loopClose = loopPoint; loopClose != m_userCode.end(); loopClose++)
	{
		if (*loopClose == '[')
			m_loopStart.push(loopClose);
		if (*loopClose == ']')
			m_loopStart.pop();

		if (m_loopStart.size() == loopStackSize)
		{
			loopPoint = loopClose;
			return;
		}
	}
}