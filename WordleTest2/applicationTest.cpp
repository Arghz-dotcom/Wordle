#include "pch.h"
#include "CppUnitTest.h"
#include "../application.cpp"
#include "../GameState.cpp"
#include "../Loader.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WordleTest2
{
	TEST_CLASS(applicationTest)
	{
	public:
		TEST_METHOD(TestComputePattern1)
		{
			string truth = "ABCDE";
			string word = "AXXXX";
			string pattern = PatternToStringOfSquares(ComputePattern(word, truth), word.size());
			Assert::AreEqual((string)"VGGGG", pattern); // 🟩⬛⬛⬛⬛ one good
		}

		TEST_METHOD(TestComputePattern2)
		{
			string truth = "ABCDE";
			string word = "XAXXX";
			string pattern = PatternToStringOfSquares(ComputePattern(word, truth), word.size());
			Assert::AreEqual((string)"GJGGG", pattern); // ⬛🟨⬛⬛⬛ one misplaced
		}

		TEST_METHOD(TestComputePattern3)
		{
			string truth = "ABCDE";
			string word = "AEXXX";
			string pattern = PatternToStringOfSquares(ComputePattern(word, truth), word.size());
			Assert::AreEqual((string)"VJGGG", pattern); // 🟩🟨⬛⬛⬛ one good one misplaced
		}

		TEST_METHOD(TestComputePattern4)
		{
			string truth = "ABCDE";
			string word = "AAXXX";
			string pattern = PatternToStringOfSquares(ComputePattern(word, truth), word.size());
			Assert::AreEqual((string)"VGGGG", pattern); // 🟩⬛⬛⬛⬛ one good once
		}

		TEST_METHOD(TestComputePattern5)
		{
			string truth = "ABCDE";
			string word = "XAAXX";
			string pattern = PatternToStringOfSquares(ComputePattern(word, truth), word.size());
			Assert::AreEqual((string)"GJGGG", pattern); // ⬛🟨⬛⬛⬛ double misplacement of the same letter
		}

		TEST_METHOD(TestComputePattern6)
		{
			string truth = "AABCD";
			string word = "AXAXX";
			string pattern = PatternToStringOfSquares(ComputePattern(word, truth), word.size());
			Assert::AreEqual((string)"VGJGG", pattern); // 🟩⬛🟨⬛⬛ same letter twice one good, a second copy misplaced
		}

		TEST_METHOD(TestComputePattern7)
		{
			string truth = "AABCD";
			string word = "AAXXX";
			string pattern = PatternToStringOfSquares(ComputePattern(word, truth), word.size());
			Assert::AreEqual((string)"VVGGG", pattern); // 🟩🟩⬛⬛⬛
		}

		TEST_METHOD(TestComputePattern8)
		{
			string truth = "AABCD";
			string word = "AAXXA";
			string pattern = PatternToStringOfSquares(ComputePattern(word, truth), word.size());
			Assert::AreEqual((string)"VVGGG", pattern); // 🟩🟩⬛⬛⬛
		}

		TEST_METHOD(TestComputePattern9)
		{
			string truth = "AAACD";
			string word = "AAXXA";
			string pattern = PatternToStringOfSquares(ComputePattern(word, truth), word.size());
			Assert::AreEqual((string)"VVGGJ", pattern); // 🟩🟩⬛⬛🟨 there is a third copy somewhere
		}
		
	};
}
