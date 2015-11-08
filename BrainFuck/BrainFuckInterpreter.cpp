#include "BrainfuckInterpreter.h"
#include <iostream>

using namespace ::std;

BrainfuckInterpreter::BrainfuckInterpreter() :
m_tapePointer(m_tape),
m_userCode(""),
m_outputString("")
{}

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
	for (char& strPos : m_userCode)
	{
		ProcessInstruction(strPos);
	}
}

void BrainfuckInterpreter::ProcessInstruction(char& instructionPointer)
{
	switch (instructionPointer)
	{
	case '+':
	case '-':
		AdjustCell(instructionPointer);
		break;
	case '>':
	case '<':
		MoveCell(instructionPointer);
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

void BrainfuckInterpreter::LoopHandler(char& loopPoint)
{
	if (loopPoint == '[')
		m_loopStart.push(&loopPoint);
	else
	{
		if (!m_loopStart.empty() && *m_tapePointer == 0)
			m_loopStart.pop();
		else if (!m_loopStart.empty())
			loopPoint = *m_loopStart.top();
	}
}
