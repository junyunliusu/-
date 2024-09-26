#include "pch.h"
#include "CppUnitTest.h"
#include "C:/Users/ACER/Desktop/gthreeup/ruanjian/main/main.cpp"
#include "C:/Users/ACER/Desktop/gthreeup/ruanjian/main/Fraction.h"
#include "C:/Users/ACER/Desktop/gthreeup/ruanjian/main/Calculate.h"
#include "C:/Users/ACER/Desktop/gthreeup/ruanjian/main/EquationGenerate.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{
	TEST_CLASS(UnitTest2)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			char* argv[5] = { "main.exe","-n","10000","-r","100"};
			Assert::AreEqual(main(5,argv), 0);
		}

		TEST_METHOD(TestMethod2)
		{
			char* argv[3] = { "main.exe","-n","10000" };
			Assert::AreEqual(main(3, argv), 0);
		}
		TEST_METHOD(TestMethod3)
		{
			char* argv[3] = { "main.exe","-n","-10000" };
			Assert::AreEqual(main(3, argv), 1);
		}

		TEST_METHOD(TestMethod4)
		{
			char* argv[5] = { "main.exe","-e","10000","-a","100" };
			Assert::AreEqual(main(5, argv), 3);
		}

		TEST_METHOD(TestMethod5)
		{
			char* argv[4] = { "main.exe","-e","10000","-a" };
			Assert::AreEqual(main(4, argv), -1);
		}

		TEST_METHOD(TestMethod6)
		{
			char* argv[5] = { "main.exe","-e","Exercises.txt","-a","Answers.txt"};
			Assert::AreEqual(main(5, argv), 0);
		}

		TEST_METHOD(TestMethod7)
		{
			Assert::AreEqual(getPriority("+"), 1);
			Assert::AreEqual(getPriority("-"), 1);
			Assert::AreEqual(getPriority("*"), 2);
			Assert::AreEqual(getPriority("¡Â"), 2);
			Assert::AreEqual(getPriority("#"), 0);
		}

		TEST_METHOD(TestMethod8)
		{
			string eq = "1.  3'5/7+(1*6'2/3-6)=";
			string str = "1.  4'8/21";
			Assert::IsTrue(str.compare(calculate(eq)));
		}

		TEST_METHOD(TestMethod9)
		{
			Fraction x(100,10), y(-50,10);
			string op1 = "+";
			string op2 = "-";
			string op3 = "*";
			string op4 = "¡Â";
			string ans = "15";
			Assert::IsTrue(ans.compare(autoCal(x, op1, y).write()));
			ans = "5";
			Assert::IsTrue(ans.compare(autoCal(x, op2, y).write()));
			ans = "50";
			Assert::IsTrue(ans.compare(autoCal(x, op3, y).write()));
			ans = "2";
			Assert::IsTrue(ans.compare(autoCal(x, op4, y).write()));

		}

		TEST_METHOD(TestMethod10)
		{
			string eq = "1'1/10";
			string str = "101/10";
			Assert::IsTrue(str.compare(stringToFraction(eq).write()));
		}

	};
}
