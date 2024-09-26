#include "EquationGenerate.h"
#include "Calculate.h"
int main(int argc, char* argv[]) {
	if (argc != 3 && argc != 5) {
		cout << "������󣬳������" << endl;
		return -1;
	}
	bool opt[4] = { 0 };//�ֱ����Ƿ���-n,-r,-e,-a
	for (int i = 1; i < argc; i += 2)
	{
		if (strcmp(argv[i], "-n") == 0)
			opt[0] = 1;
		else if (strcmp(argv[i], "-r") == 0)
			opt[1] = 1;
		else if (strcmp(argv[i], "-e") == 0)
			opt[2] = 1;
		else if (strcmp(argv[i], "-a") == 0)
			opt[3] = 1;
	}
	if (opt[0]) {
		countLimit = strtol(argv[2], NULL, 0);
		if (countLimit <= 0) {
			cout << "Ҫ��������Ŀ�������󣬳������" << endl;
			return 1;
		}
		if (opt[1]) {
			numLimit = strtol(argv[4], NULL, 0);
			if (numLimit <= 0) {
				cout << "Ҫ���������ݷ�Χ���󣬳������" << endl;
				return 2;
			}
		}
		else
			numLimit = 10;//Ĭ��Ϊ10
		//srand(time(NULL));//���������
		srand(100);
		ofstream fileExample("Exercises.txt");
		ofstream fileAnswer("Answers.txt");
		int count = 1;
		unordered_set<string> vis;//��¼�ظ���ʽ
		while (count <= countLimit) {
			Node ans = getRandomEquation(vis);
			if (ans.checkeq == "") continue;
			fileExample << count << ".  " << ans.eq << "=" << endl;
			fileAnswer << count << ".  " << ans.fr.write() << endl;
			count++;
		}
		vis.clear();
		fileExample.close();
		fileAnswer.close();
		cout << "��ʽ���ɳɹ�" << endl;
	}
	else if (opt[2] && opt[3])
	{
		if (strcmp(argv[1], "-a") == 0)
			swap(argv[2], argv[4]);
		ifstream fileExample(argv[2]);
		ifstream fileAnswer(argv[4]);
		if (fileExample.fail() || fileAnswer.fail()) {
			cout << "�ļ�·������" << endl;
			return 3;
		}
		try {
			checkexample(fileExample, fileAnswer);
			cout << "�𰸱Ƚ����" << endl;
		}
		catch (const char* msg) { // ����������׼�쳣
			cout << msg << endl;
		}
		fileExample.close();
		fileAnswer.close();
	}
	else {
		cout << "�������������ȷ���������" << endl;
	}
	return 0;
}
