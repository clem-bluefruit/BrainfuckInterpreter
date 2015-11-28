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


string BrainfuckInterpreter::Parse(bool output)
{
	ParseString();
	return (output ? RawTapeString() : "");
}

void BrainfuckInterpreter::UserCodeInput(const string code)
{
	m_userCode = code;
}

string BrainfuckInterpreter::RawTapeString() const
{
	string tempString;
	for (const char& c : m_tape)
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
		if (!m_instructionFlag)
			break;
		AdjustCell(*instructionPointer);
		break;
	case '>':
	case '<':
		if (!m_instructionFlag)
			break;
		MoveCell(*instructionPointer);
		break;
	case '[':
	case ']':
		LoopHandler(instructionPointer);
		break;
	case '.':
		if (!m_instructionFlag)
			break;
		if (*m_tapePointer >= ' ')
			m_outputString += *m_tapePointer;
		break;
	default:
		break;
	}
}

void BrainfuckInterpreter::AdjustCell(char adjustment)
{
	(*m_tapePointer) = (adjustment == '+' ? *m_tapePointer + 1 : *m_tapePointer - 1);
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
		if (m_tapePointer == 0)
			m_instructionFlag == false;
		m_loopStart.push(loopPoint);
	}
	else
	{
		if (!m_loopStart.empty() && *m_tapePointer == 0)
			m_loopStart.pop();
		else if (m_loopStart.size() == 1 && !m_instructionFlag)
			m_instructionFlag ^= m_instructionFlag;
		else if (!m_loopStart.empty() && m_instructionFlag)
			loopPoint = m_loopStart.top();
	}
}