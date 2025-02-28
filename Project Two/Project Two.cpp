#include <iostream>
#include <cstdlib>
using namespace std;

enum enQuestionLevel { Easy = 1, Mideum = 2, Hard = 3, Mix = 4 };
enum enOperationType { Add = 1, Subtract = 2, Multiplication = 3, Divide = 4, MixOp = 5 };

struct stQuestion
{
	enQuestionLevel QuestionLevel;
	enOperationType OperationType;
	int FirstNumber = 0;
	int SecondNumber = 0;
	int PlayerAnswer = 0;
	int CorrectAnswer = 0;
	bool FinalResult = true;
};

struct stQuiz
{
	stQuestion QuestionList[100];
	enQuestionLevel QuestionLevel;
	enOperationType OperationType;
	short NumberOfQuestion = 0;
	short NumberOfRightAnswer = 0;
	short NumberOfWrongAnswer = 0;
	bool IsPass = true;
};

int RandomNumber(int From, int To)
{
	int RandNum = 0;

	RandNum = rand() % (To - From + 1) + From;
	return RandNum;
}

string Tabs(short NumberOfTabs)
{
	string Tab = "";

	for (int i = 0; i < NumberOfTabs; i++)
	{
		Tab = Tab + "\t";
	}
	return Tab;
}

string Slash(short NumberOfSlash)
{
	string Slash = "";

	for (int i = 0; i < NumberOfSlash; i++)
	{
		Slash = Slash + "-";
	}
	return Slash;
}

short ReadHowManyQuestion()
{
	short HowManyQuestion = 0;

	do
	{
		cout << "Please Enter How Many Question Do You Want to Answer? ";
		cin >> HowManyQuestion;

	} while (HowManyQuestion < 1 || HowManyQuestion > 10);
	return HowManyQuestion;
}

enQuestionLevel ReadQuestionLevel()
{
	short QuestionLevel = 0;

	do
	{
		cout << "Enter Question Level : [1]:Easy , [2]:Mideum , [3]:Hard , [4]:Mix? ";
		cin >> QuestionLevel;

	} while (QuestionLevel < 1 || QuestionLevel > 4);
	return (enQuestionLevel)QuestionLevel;
}

enOperationType ReadOperationType()
{
	short OperationType = 0;

	do
	{
		cout << "Enter Operation Type : [1]:Add , [2]:Subtract , [3]:Multiplication , [4]:Divide , [5]:Mix? ";
		cin >> OperationType;

	} while (OperationType < 1 || OperationType > 5);
	return (enOperationType)OperationType;
}

string GetQuestionLevelText(enQuestionLevel QuestionLevel)
{
	string ArrQuestionLevelText[4] = { "Easy","Mideum","Multiplication","Mix" };
	return ArrQuestionLevelText[QuestionLevel - 1];
}

string GetOperationTypeText(enOperationType OperationType)
{
	string ArrOperationType[5] = { "Add","Subtract","Hard","Divide","Mix" };
	return ArrOperationType[OperationType - 1];
}

enQuestionLevel GetRandomQuestionLevel()
{
	return (enQuestionLevel)RandomNumber(1, 3);
}

enOperationType GetRandomOperationType()
{
	return (enOperationType)RandomNumber(1, 4);
}

string GetOperationTypeSymbol(enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
	{
		return "+";
	}
	case enOperationType::Subtract:
	{
		return "-";
	}
	case enOperationType::Multiplication:
	{
		return "x";
	}
	case enOperationType::Divide:
	{
		return "/";
	}
	default:
	{
		return "+";
	}
	};
}

int SimpleCalculator(int FirstNumber, int SecondNumber, enOperationType OpTye)
{
	switch (OpTye)
	{
	case enOperationType::Add:
	{
		return FirstNumber + SecondNumber;
	}
	case enOperationType::Subtract:
	{
		return FirstNumber - SecondNumber;
	}
	case enOperationType::Multiplication:
	{
		return FirstNumber * SecondNumber;
	}
	case enOperationType::Divide:
	{
		return FirstNumber / SecondNumber;
	}
	default:
	{
		return FirstNumber + SecondNumber;
	}
	};
}

stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OperationType)
{
	stQuestion Question;

	if (QuestionLevel == enQuestionLevel::Mix)
	{
		QuestionLevel = GetRandomQuestionLevel();
	}
	if (OperationType == enOperationType::MixOp)
	{
		OperationType = GetRandomOperationType();
	}

	Question.OperationType = OperationType;

	switch (QuestionLevel)
	{
	case enQuestionLevel::Easy:
	{
		Question.FirstNumber = RandomNumber(1, 10);
		Question.SecondNumber = RandomNumber(1, 10);

		Question.CorrectAnswer = SimpleCalculator(Question.FirstNumber, Question.SecondNumber, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	}
	case enQuestionLevel::Mideum:
	{
		Question.FirstNumber = RandomNumber(10, 50);
		Question.SecondNumber = RandomNumber(10, 50);

		Question.CorrectAnswer = SimpleCalculator(Question.FirstNumber, Question.SecondNumber, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	}
	case enQuestionLevel::Hard:
	{
		Question.FirstNumber = RandomNumber(50, 100);
		Question.SecondNumber = RandomNumber(50, 100);

		Question.CorrectAnswer = SimpleCalculator(Question.FirstNumber, Question.SecondNumber, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	}
	};
	return Question;
}

void GenerateQuizQuestion(stQuiz& Quiz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quiz.NumberOfQuestion; QuestionNumber++)
	{
		Quiz.QuestionList[QuestionNumber] = GenerateQuestion(Quiz.QuestionLevel, Quiz.OperationType);
	}
}

void PrintTheQuestion(stQuiz Quiz, short QuestionNumber)
{
	cout << endl;
	cout << "Question [" << QuestionNumber + 1 << "/" << Quiz.NumberOfQuestion << "]" << endl << endl;
	cout << Quiz.QuestionList[QuestionNumber].FirstNumber << endl;
	cout << Quiz.QuestionList[QuestionNumber].SecondNumber << "  ";
	cout << GetOperationTypeSymbol(Quiz.QuestionList[QuestionNumber].OperationType) << endl;
	cout << Slash(20) << endl;
}

int ReadPlayerAnswer()
{
	int PlayerAnswer = 0;
	cin >> PlayerAnswer;
	return PlayerAnswer;
}

void SetScreenColor(bool FinalResult)
{
	if (FinalResult)
	{
		system("Color 2F");
	}
	else
	{
		system("Color 4F");
		cout << "\a";
	}
}

void PrintCorrectAnswer(stQuiz Quiz, short QuestionNumber)
{
	cout << endl;

	if (Quiz.QuestionList[QuestionNumber].FinalResult)
	{
		cout << "Right Answer : -(";
	}
	else
	{
		cout << "Wrong Answer : -(" << endl;
		cout << "The Right Answer is : " << Quiz.QuestionList[QuestionNumber].CorrectAnswer << endl;
	}

	cout << endl;
	SetScreenColor(Quiz.QuestionList[QuestionNumber].FinalResult);
}

void CorrectTheQuestionAnswer(stQuiz& Quiz, short QuestionNumber)
{
	if (Quiz.QuestionList[QuestionNumber].PlayerAnswer == Quiz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quiz.NumberOfRightAnswer++;
		Quiz.QuestionList[QuestionNumber].FinalResult = true;
	}
	else
	{
		Quiz.NumberOfWrongAnswer++;
		Quiz.QuestionList[QuestionNumber].FinalResult = false;
	}
	PrintCorrectAnswer(Quiz, QuestionNumber);
}

void AskAndCorrectQuestionListAnswer(stQuiz& Quiz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quiz.NumberOfQuestion; QuestionNumber++)
	{
		PrintTheQuestion(Quiz, QuestionNumber);
		Quiz.QuestionList[QuestionNumber].PlayerAnswer = ReadPlayerAnswer();
		CorrectTheQuestionAnswer(Quiz, QuestionNumber);

	}
	Quiz.IsPass = (Quiz.NumberOfRightAnswer >= Quiz.NumberOfWrongAnswer);
}

string GetPassFailText(bool Pass)
{
	if (Pass)
	{
		return "Pass : -)";
	}
	else
	{
		return "Fail : -(";
	}
}

void PrintQuizResult(stQuiz Quiz)
{
	cout << endl;
	cout << Slash(40) << endl;
	cout << "Final Result is " << GetPassFailText(Quiz.IsPass) << endl;
	cout << Slash(40) << endl;

	cout << "Number Of Question             : " << Quiz.NumberOfQuestion << endl;
	cout << "Question Level                 : " << GetQuestionLevelText(Quiz.QuestionLevel) << endl;
	cout << "Operation Type                 : " << GetOperationTypeText(Quiz.OperationType) << endl;
	cout << "Number of Right Answer         : " << Quiz.NumberOfRightAnswer << endl;
	cout << "Number of Wrong Answer         : " << Quiz.NumberOfWrongAnswer << endl;
	cout << Slash(40) << endl;
}

void PlayMathGame()
{
	stQuiz Quiz;

	Quiz.NumberOfQuestion = ReadHowManyQuestion();
	Quiz.QuestionLevel = ReadQuestionLevel();
	Quiz.OperationType = ReadOperationType();

	GenerateQuizQuestion(Quiz);
	AskAndCorrectQuestionListAnswer(Quiz);
	PrintQuizResult(Quiz);
}

void ResetScreen()
{
	system("Color 0F");
	system("cls");
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		PlayMathGame();

		cout << "\nDo You Want to Play Again [Y/N]? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}