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
	std::stack<std::string::iterator> m_loopStart;
	std::string m_userCode;
	std::string m_outputString;
	std::string RawTapeString() const;
	void ParseString();
	void LoopHandler(std::string::iterator& loopPoint);
	void ProcessInstruction(std::string::iterator& instruction);
	void AdjustCell(char adjustment);
	void MoveCell(char direction);
	void JumpToEndLoop(std::string::iterator& loopPoint);
	bool m_instructionFlag = true;
};

#endif