#ifndef BRAINFUCKINTERPRETER_INCLUDED
#define BRAINFUCKINTERPRETER_INCLUDED
#include <string>
#include <stack>

class BrainfuckInterpreter
{
public:
	BrainfuckInterpreter();

	std::string Parse(bool output = true);
	std::string ToString() const;
	void UserCodeInput(const std::string code);
private:
	static const size_t TapeLength = 30000;
	char m_tape[TapeLength];
	char* m_tapePointer;
	std::stack<char*> m_loopStart;
	std::string m_userCode;
	std::string m_outputString;
	std::string RawTapeString() const;
	void ParseString();
	void LoopHandler(char& loopPoint);
	void ProcessInstruction(char& instruction);
	void AdjustCell(char adjustment);
	void MoveCell(char direction);
};

#endif