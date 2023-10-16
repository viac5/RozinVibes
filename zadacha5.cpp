#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include<windows.h>

using namespace std;

const double Mu = 398600.4418; //(мю)гравитационный параметр Земли
const double R = 6378;  //радиус Земли
const double g = 9.8;// ускорение свободного падения

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

	cout << "Введите количество перелетов: ";
	double N;
	double r12 = 0, r22 = 0;
	cin >> N;
	cout << "//все перелёты осуществляются с Земли, поэтому r1 и r2 увеличены на радиус Земли(R = 6378)"<<endl;
	for (int i = 0; i < N; i++)
	{
		cout << "Перелет номер: " << i + 1<<endl;
		cout << "Введите радиус орбиты с которой осуществляется перелет: ";
		double r1;
		cin >> r1;
		if (r1 <= 0) {
			cout << "Невозможный радиус орбиты, введите заново: ";
			cin >> r1;
		}
		
		cout << "Введите радиус орбиты  на которую осуществляется перелет: ";
		double r2;
		cin >> r2;
		if (r2 <= 0) {
			cout << "Невозможный радиус орбиты, введите заново";
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

	cout << "Введите количество космических аппаратов: ";
	double N1;
	cin >> N1;

	for (int i = 0; i < N1; i++)
	{
		cout << "КА номер: " << i + 1<<endl;
		cout << "Введите массу заправленного аппарата: ";
		double M;
		cin >> M;

		cout << "Введите массу топлива: ";
		double m;
		cin >> m;

		cout << "Введите удельный импульс тяги двигательной установки: ";
		double I;
		cin >> I;

		double delVSC = I * g * log(M / (M - m));//уравнение Циалковского
		vector<double> newStr = { M, m, I, delVSC};
		KA.push_back(newStr);
	}
	sort(KA.begin(), KA.end(), Uslov2);

	////////////////////////////////////

	for (int i = 0; i < Per.size(); i++)
	{
		cout << "-__________________________________________________________________________________-"<<endl;
		cout<<"Перелет номер: "<<i+1 << "                 r1 =" << Per[i][0] << "   r2=" << Per[i][1] << "   delVE=" << Per[i][2]<<endl;
		cout << "-__________________________________________________________________________________-" <<endl;
		for (int j = 0; j < KA.size(); j++)
		{
			if ((abs(Per[i][2] < KA[j][3]))&& (KA[j][0] > KA[j][1])) { cout << "Космический аппарат номер: " << j + 1 << "     M= " << KA[j][0] << "   m= " << KA[j][1] << "   I= " << KA[j][2] << "   delVSC= " << KA[j][3] << "   Перелет возможен" << endl; }
		}
		for (int j = 0; j < KA.size(); j++)
		{
			if ((abs(Per[i][2] >= KA[j][3]))||(KA[j][0]<=KA[j][1])) { cout << "Космический аппарат номер: " << j + 1 << "     M= " << KA[j][0] << "   m= " << KA[j][1] << "   I= " << KA[j][2] << "   delVSC= " << KA[j][3] << "   Перелет невозможен" << endl; }
		}
	}
	///////////////////////////////////
	for (int i = 0; i < 10; i++)
	{
		cout << endl<<"Хотите ли вы удалить КА? (Да/Нет)";
		string Otv = "";
		cin >> Otv;
		double otv = 0;
		if (Otv == "Да" || Otv == "ДА" || Otv == "да" || Otv == "дА") {
			cout <<endl<< endl;
			cout << "____________________________________________________________________________________" << endl;
			for (int j = 0; j < KA.size(); j++)
			{
				cout << "Космический аппарат номер: " << j + 1 << "     M= " << KA[j][0] << "   m= " << KA[j][1] << "   I= " << KA[j][2] << "   delVSC= " << KA[j][3] << endl;
			}
			cout << "____________________________________________________________________________________" << endl<<endl;
			cout << "Какой аппарат вы хотите удалить?" << endl;
			cin >> otv;
			KA.erase(KA.begin() + (otv-1));
			cout << endl;
			for (int i = 0; i < Per.size(); i++)
			{
				cout << "-__________________________________________________________________________________-" << endl;
				cout << "Перелет номер: " << i + 1 << "                 r1 =" << Per[i][0] << "   r2=" << Per[i][1] << "   delVE=" << Per[i][2] << endl;
				cout << "-__________________________________________________________________________________-" << endl;
				for (int j = 0; j < KA.size(); j++)
				{
					if ((abs(Per[i][2] < KA[j][3])) && (KA[j][0] > KA[j][1])) { cout << "Космический аппарат номер: " << j + 1 << "     M= " << KA[j][0] << "   m= " << KA[j][1] << "   I= " << KA[j][2] << "   delVSC= " << KA[j][3] << "   Перелет возможен" << endl; }
				}
				for (int j = 0; j < KA.size(); j++)
				{
					if ((abs(Per[i][2] >= KA[j][3])) || (KA[j][0] <= KA[j][1])) { cout << "Космический аппарат номер: " << j + 1 << "     M= " << KA[j][0] << "   m= " << KA[j][1] << "   I= " << KA[j][2] << "   delVSC= " << KA[j][3] << "   Перелет невозможен" << endl; }
				}
			}
		}
		else {
			cout << "Отлично! данные полетов и КА доступны вам в файле res.txt";
			break;
		}
	}

	for (int i = 0; i < Per.size(); i++)
	{
		out << "-__________________________________________________________________________________-" << endl;
		out << "Перелет номер: " << i + 1 << "                 r1 =" << Per[i][0] << "   r2=" << Per[i][1] << "   delVE=" << Per[i][2] << endl;
		out << "-__________________________________________________________________________________-" << endl;
		for (int j = 0; j < KA.size(); j++)
		{
			if ((abs(Per[i][2] < KA[j][3])) && (KA[j][0] > KA[j][1])) { out << "Космический аппарат номер: " << j + 1 << "     M= " << KA[j][0] << "   m= " << KA[j][1] << "   I= " << KA[j][2] << "   delVSC= " << KA[j][3] << "   Перелет возможен" << endl; }
		}
		for (int j = 0; j < KA.size(); j++)
		{
			if ((abs(Per[i][2] >= KA[j][3])) || (KA[j][0] <= KA[j][1])) { out << "Космический аппарат номер: " << j + 1 << "     M= " << KA[j][0] << "   m= " << KA[j][1] << "   I= " << KA[j][2] << "   delVSC= " << KA[j][3] << "   Перелет невозможен" << endl; }
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