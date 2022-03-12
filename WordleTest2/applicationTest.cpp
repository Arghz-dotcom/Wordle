#include "pch.h"
#include "CppUnitTest.h"
#include "../PatternCompute.cpp"
#include "../GameState.cpp"
#include "../Loader.cpp"
#include "../application.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WordleTest2
{
	/*
	V: vert, matching same location
	J: jaune, matching another location
	G: gris, not matching
	*/

	TEST_CLASS(applicationTest)
	{
	public:
		TEST_METHOD(TestComputePattern1)
		{
			string truth = "ABCDE";
			string word = "AXXXX";
			PatternCompute patternCompute;
			string pattern = patternCompute.PatternToStringOfSquares(ComputePattern(word, truth), (int)word.size());
			Assert::AreEqual((string)"VGGGG", pattern); // 🟩⬛⬛⬛⬛ one good
		}

		TEST_METHOD(TestComputePattern2)
		{
			string truth = "ABCDE";
			string word = "XAXXX";
			PatternCompute patternCompute;
			string pattern = patternCompute.PatternToStringOfSquares(ComputePattern(word, truth), (int)word.size());
			Assert::AreEqual((string)"GJGGG", pattern); // ⬛🟨⬛⬛⬛ one misplaced
		}

		TEST_METHOD(TestComputePattern3)
		{
			string truth = "ABCDE";
			string word = "AEXXX";
			PatternCompute patternCompute;
			string pattern = patternCompute.PatternToStringOfSquares(ComputePattern(word, truth), (int)word.size());
			Assert::AreEqual((string)"VJGGG", pattern); // 🟩🟨⬛⬛⬛ one good one misplaced
		}

		TEST_METHOD(TestComputePattern4)
		{
			string truth = "ABCDE";
			string word = "AAXXX";
			PatternCompute patternCompute;
			string pattern = patternCompute.PatternToStringOfSquares(ComputePattern(word, truth), (int)word.size());
			Assert::AreEqual((string)"VGGGG", pattern); // 🟩⬛⬛⬛⬛ one good once
		}

		TEST_METHOD(TestComputePattern5)
		{
			string truth = "ABCDE";
			string word = "XAAXX";
			PatternCompute patternCompute;
			string pattern = patternCompute.PatternToStringOfSquares(ComputePattern(word, truth), (int)word.size());
			Assert::AreEqual((string)"GJGGG", pattern); // ⬛🟨⬛⬛⬛ double misplacement of the same letter
		}

		TEST_METHOD(TestComputePattern6)
		{
			string truth = "AABCD";
			string word = "AXAXX";
			PatternCompute patternCompute;
			string pattern = patternCompute.PatternToStringOfSquares(ComputePattern(word, truth), (int)word.size());
			Assert::AreEqual((string)"VGJGG", pattern); // 🟩⬛🟨⬛⬛ same letter twice one good, a second copy misplaced
		}

		TEST_METHOD(TestComputePattern7)
		{
			string truth = "AABCD";
			string word = "AAXXX";
			PatternCompute patternCompute;
			string pattern = patternCompute.PatternToStringOfSquares(ComputePattern(word, truth), (int)word.size());
			Assert::AreEqual((string)"VVGGG", pattern); // 🟩🟩⬛⬛⬛
		}

		TEST_METHOD(TestComputePattern8)
		{
			string truth = "AABCD";
			PatternCompute patternCompute;
			string word = "AAXXA";
			string pattern = patternCompute.PatternToStringOfSquares(ComputePattern(word, truth), (int)word.size());
			Assert::AreEqual((string)"VVGGG", pattern); // 🟩🟩⬛⬛⬛
		}

		TEST_METHOD(TestComputePattern9)
		{
			string truth = "AAACD";
			string word = "AAXXA";
			PatternCompute patternCompute;
			string pattern = patternCompute.PatternToStringOfSquares(ComputePattern(word, truth), (int)word.size());
			Assert::AreEqual((string)"VVGGJ", pattern); // 🟩🟩⬛⬛🟨 there is a third copy somewhere
		}
		
	};
}
