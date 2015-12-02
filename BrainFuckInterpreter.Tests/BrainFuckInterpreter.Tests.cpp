#include "BrainfuckInterpreter.h"
#include <gtest/gtest.h>

using namespace ::testing;

class Brainfuck : public ::testing::Test
{
public:
	BrainfuckInterpreter reader;
};

TEST_F(Brainfuck, Interpreter_initialises_with_empty_output)
{
	ASSERT_EQ("", reader.Parse());
}

TEST_F(Brainfuck, Interpreter_input_totals_9_output_is_TAB)
{
	reader.UserCodeInput("+++++++++");
	ASSERT_EQ("\t", reader.Parse()) << "Output is NOT a TAB char";
}

TEST_F(Brainfuck, Interpreter_input_is_10_minus_1_Outputs_TAB)
{
	reader.UserCodeInput("++++++++++-");
	ASSERT_EQ("\t", reader.Parse()) << "Forgot to take-away 1?";
}

TEST_F(Brainfuck, Interpreter_adds_9_to_TWO_cells_Output_is_TABTAB)
{
	reader.UserCodeInput("+++++++++>+++++++++");
	ASSERT_EQ("\t\t", reader.Parse()) << "Output is NOT TABTAB";
}

TEST_F(Brainfuck, Interpreter_adds_11_to_first_cell_9_to_second_subtracts_2_from_first_Output_is_TABTAB)
{
	reader.UserCodeInput("+++++ +++++ +>+++++ ++++<--");
	ASSERT_EQ("\t\t", reader.Parse()) << "NOT TABTAB < skip/remove wrong?";
}

TEST_F(Brainfuck, Basic_loop_adds_5_to_second_cell_twice_Output_is_NEWLINE)
{
	reader.UserCodeInput("++[>+++++<-]");
	ASSERT_EQ("\n", reader.Parse()) << "Output is NOT NEWLINE";
}

TEST_F(Brainfuck, Basic_nested_loop_populates_three_cells_Output_is_TAB_and_NEWLINE)
{
	reader.UserCodeInput("++[>+++++[>+<-]<-]>+++++++++");
	ASSERT_EQ("\t\n", reader.Parse()) << "Output is NOT TABNEWLINE!";
}

TEST_F(Brainfuck, Tapecell_rollover_behavior_Cell_1_minus_1_Output_is_CHAR255)
{
	// NOTE: I didn't know what output to expect (Extended ASCII or not)
	reader.UserCodeInput("-");
	ASSERT_EQ("\xFF", reader.Parse()) << "Output is NOT '\xFF'";
}

TEST_F(Brainfuck, Skip_to_end_of_tape_then_skip_forward_to_cell_2_Output_is_TAB)
{
	reader.UserCodeInput("<>>+++++++++");
	ASSERT_EQ("\t", reader.Parse()) << "Tape skipping failed: Cell 2 is NOT TAB";
}

TEST_F(Brainfuck, Subtract_one_from_last_pointer_skipping_backwards_Output_is_CHAR255)
{
	reader.UserCodeInput("<-");
	ASSERT_EQ("\xFF", reader.Parse()) << "Output is NOT '\xFF'";
}

TEST_F(Brainfuck, Using_output_instruction_to_build_string)
{
	reader.UserCodeInput("+++++ +++[>++++<-]>.+.+.+.");
	reader.Parse(false);
	ASSERT_EQ(" !\"#", reader.ToString()) << "Output is NOT ' !\"#'";
}

TEST_F(Brainfuck, Code_input_is_Wiki_Hello_World_example)
{
	reader.UserCodeInput("++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.");
	reader.Parse(false);
	ASSERT_EQ("Hello World!", reader.ToString()) << "Output is NOT Hello World!";
}

TEST_F(Brainfuck, Email_address_copy_at_copy_dot_sh)
{
	reader.UserCodeInput("--[----->+<]>---.++++++++++++.+.+++++++++.+[-->+<]>+++.++[-->+++<]>.++++++++++++.+.+++++++++.-[-->+++++<]>++.[--->++<]>-.-----------.");
	reader.Parse(false);
	ASSERT_EQ("copy@copy.sh", reader.ToString()) << "Output is NOT copy@copy.sh!";
}

TEST_F(Brainfuck, Working_up_to_complex_Hello_World_example)
{
	reader.UserCodeInput(">++++++++[<+++++++++>-]<.>>+>+>++>[-]+<[>[->+<<++++>]<<]>.+++++++..+++.>>+++++++.<<<[[-]<[-]>]<+++++++++++++++.");
	reader.Parse();
	ASSERT_EQ("Hello W", reader.ToString()) << "Output is NOT 'Hello W'";
}

/*
TEST_F(Brainfuck, Complex_Hello_World_Esolang_example)
{
reader.UserCodeInput(">++++++++[<+++++++++>-]<.>>+>+>++>[-]+<[>[->+<<++++>]<<]>.+++++++..+++.>>+++++++.<<<[[-]<[-]>]<+++++++++++++++.>>.+++.------.--------.>>+.>++++.");
reader.Parse(false);
ASSERT_EQ("Hdw!", reader.Parse());
ASSERT_EQ("Hello World!", reader.ToString()) << "Complex Hello World FAILED!";
}
*/