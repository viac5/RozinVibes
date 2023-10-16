#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include<windows.h>

using namespace std;

const double Mu = 398600.4418; //(��)�������������� �������� �����
const double R = 6378;  //������ �����
const double g = 9.8;// ��������� ���������� �������

bool Uslov1(const vector<double>& row1, const vector<double>& row2) {
	return row1[2] > row2[2];
}
bool Uslov2(const vector<double>& row1, const vector<double>& row2) {
	return row1[0] > row2[0];
}


double VozmozhPereleta()
{   
	ofstream out;
	out.open("res.txt");

	vector<vector<double>> Per;
	vector<vector<double>> KA;

	cout << "������� ���������� ���������: ";
	double N;
	double r12 = 0, r22 = 0;
	cin >> N;
	cout << "//��� ������� �������������� � �����, ������� r1 � r2 ��������� �� ������ �����(R = 6378)"<<endl;
	for (int i = 0; i < N; i++)
	{
		cout << "������� �����: " << i + 1<<endl;
		cout << "������� ������ ������ � ������� �������������� �������: ";
		double r1;
		cin >> r1;
		if (r1 <= 0) {
			cout << "����������� ������ ������, ������� ������: ";
			cin >> r1;
		}
		
		cout << "������� ������ ������  �� ������� �������������� �������: ";
		double r2;
		cin >> r2;
		if (r2 <= 0) {
			cout << "����������� ������ ������, ������� ������";
			cin >> r2;
		}
		r12 = r1 + R;
		r22 = r2 + R;

		double delV1 = pow((Mu / r12), 0.5) * (pow(((2 * r22) / (r12 + r22)), 0.5) - 1);
		double delV2 = pow((Mu / r22), 0.5) * (1 - pow(((2 * r12) / (r12 + r22)), 0.5));
		double delVE = (abs(delV1) + abs(delV2))*1000;
		vector<double> newStr = { r12, r22, delVE };
		Per.push_back(newStr);
	}

	sort(Per.begin(), Per.end(), Uslov1);

	/////////////////////////////

	cout << "������� ���������� ����������� ���������: ";
	double N1;
	cin >> N1;

	for (int i = 0; i < N1; i++)
	{
		cout << "�� �����: " << i + 1<<endl;
		cout << "������� ����� ������������� ��������: ";
		double M;
		cin >> M;

		cout << "������� ����� �������: ";
		double m;
		cin >> m;

		cout << "������� �������� ������� ���� ������������ ���������: ";
		double I;
		cin >> I;

		double delVSC = I * g * log(M / (M - m));//��������� ������������
		vector<double> newStr = { M, m, I, delVSC};
		KA.push_back(newStr);
	}
	sort(KA.begin(), KA.end(), Uslov2);

	////////////////////////////////////

	for (int i = 0; i < Per.size(); i++)
	{
		cout << "-__________________________________________________________________________________-"<<endl;
		cout<<"������� �����: "<<i+1 << "                 r1 =" << Per[i][0] << "   r2=" << Per[i][1] << "   delVE=" << Per[i][2]<<endl;
		cout << "-__________________________________________________________________________________-" <<endl;
		for (int j = 0; j < KA.size(); j++)
		{
			if ((abs(Per[i][2] < KA[j][3]))&& (KA[j][0] > KA[j][1])) { cout << "����������� ������� �����: " << j + 1 << "     M= " << KA[j][0] << "   m= " << KA[j][1] << "   I= " << KA[j][2] << "   delVSC= " << KA[j][3] << "   ������� ��������" << endl; }
		}
		for (int j = 0; j < KA.size(); j++)
		{
			if ((abs(Per[i][2] >= KA[j][3]))||(KA[j][0]<=KA[j][1])) { cout << "����������� ������� �����: " << j + 1 << "     M= " << KA[j][0] << "   m= " << KA[j][1] << "   I= " << KA[j][2] << "   delVSC= " << KA[j][3] << "   ������� ����������" << endl; }
		}
	}
	///////////////////////////////////
	for (int i = 0; i < 10; i++)
	{
		cout << endl<<"������ �� �� ������� ��? (��/���)";
		string Otv = "";
		cin >> Otv;
		double otv = 0;
		if (Otv == "��" || Otv == "��" || Otv == "��" || Otv == "��") {
			cout <<endl<< endl;
			cout << "____________________________________________________________________________________" << endl;
			for (int j = 0; j < KA.size(); j++)
			{
				cout << "����������� ������� �����: " << j + 1 << "     M= " << KA[j][0] << "   m= " << KA[j][1] << "   I= " << KA[j][2] << "   delVSC= " << KA[j][3] << endl;
			}
			cout << "____________________________________________________________________________________" << endl<<endl;
			cout << "����� ������� �� ������ �������?" << endl;
			cin >> otv;
			KA.erase(KA.begin() + (otv-1));
			cout << endl;
			for (int i = 0; i < Per.size(); i++)
			{
				cout << "-__________________________________________________________________________________-" << endl;
				cout << "������� �����: " << i + 1 << "                 r1 =" << Per[i][0] << "   r2=" << Per[i][1] << "   delVE=" << Per[i][2] << endl;
				cout << "-__________________________________________________________________________________-" << endl;
				for (int j = 0; j < KA.size(); j++)
				{
					if ((abs(Per[i][2] < KA[j][3])) && (KA[j][0] > KA[j][1])) { cout << "����������� ������� �����: " << j + 1 << "     M= " << KA[j][0] << "   m= " << KA[j][1] << "   I= " << KA[j][2] << "   delVSC= " << KA[j][3] << "   ������� ��������" << endl; }
				}
				for (int j = 0; j < KA.size(); j++)
				{
					if ((abs(Per[i][2] >= KA[j][3])) || (KA[j][0] <= KA[j][1])) { cout << "����������� ������� �����: " << j + 1 << "     M= " << KA[j][0] << "   m= " << KA[j][1] << "   I= " << KA[j][2] << "   delVSC= " << KA[j][3] << "   ������� ����������" << endl; }
				}
			}
		}
		else {
			cout << "�������! ������ ������� � �� �������� ��� � ����� res.txt";
			break;
		}
	}

	for (int i = 0; i < Per.size(); i++)
	{
		out << "-__________________________________________________________________________________-" << endl;
		out << "������� �����: " << i + 1 << "                 r1 =" << Per[i][0] << "   r2=" << Per[i][1] << "   delVE=" << Per[i][2] << endl;
		out << "-__________________________________________________________________________________-" << endl;
		for (int j = 0; j < KA.size(); j++)
		{
			if ((abs(Per[i][2] < KA[j][3])) && (KA[j][0] > KA[j][1])) { out << "����������� ������� �����: " << j + 1 << "     M= " << KA[j][0] << "   m= " << KA[j][1] << "   I= " << KA[j][2] << "   delVSC= " << KA[j][3] << "   ������� ��������" << endl; }
		}
		for (int j = 0; j < KA.size(); j++)
		{
			if ((abs(Per[i][2] >= KA[j][3])) || (KA[j][0] <= KA[j][1])) { out << "����������� ������� �����: " << j + 1 << "     M= " << KA[j][0] << "   m= " << KA[j][1] << "   I= " << KA[j][2] << "   delVSC= " << KA[j][3] << "   ������� ����������" << endl; }
		}
	}


	out.close();
	return 0;

}


int main() {
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);

	VozmozhPereleta();

	return 0;
}