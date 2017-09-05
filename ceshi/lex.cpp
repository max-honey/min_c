#include"title.h"
using namespace std;
char *line[10];
string str[10];
int flag = 1, flag1 = 1;
double digit, sum1 = 0;
char prog[10000], token[10];
char ch;
int syn, p, m = 0, n, row, sum = 0;
char *rwtab[9] = { "real","string","int","while","if","else","out","in","main" };

void scan()
{
	int i = 0;
	for (n = 0; n<10; n++) token[n] = NULL;
	ch = prog[p++];
	while (ch == ' ' || ch == '\n')
	{
		ch = prog[p];
		p++;
	}
	if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z'))  //可能是标示符或者变量名 
	{
		m = 0;
		while ((ch >= '0'&&ch <= '9') || (ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z'))
		{
			token[m++] = ch;
			ch = prog[p++];
			if (m >= 8)
				break;
		}
		token[m++] = '\0';
		p--;
		syn = 32;
		for (n = 0; n<9; n++)  //将识别出来的字符和已定义的标示符作比较， 
			if (strcmp(token, rwtab[n]) == 0)
			{
				syn = n + 1;
				break;
			}
	}
	else if ((ch >= '0'&&ch <= '9'))  //数字 
	{
		m = 0;
		flag = 1;
		sum = 0;
		sum1 = 0;	//最终数字				
		int conter = 0;//计算小数点之后的层数
		while ((ch >= '0'&&ch <= '9') || ch == '.')
		{
			if (ch == '.') {
				token[m++] = ch;
				ch = prog[p++];
				flag = 0;

				continue;
			}
			if (flag != 1) {//如果前面有逗号则为实数，需计算小数部分sum2。
				conter++;
				int num = ch - '0';
				sum1 += pow(0.1, conter)*num;
				token[m++] = ch;//计算小数部分
				ch = prog[p++];

			}
			else {//如果没有逗号只需计算整数部分
				sum = sum * 10 + ch - '0';
				token[m++] = ch;
				ch = prog[p++];

			}
		}
		if (flag != 1)sum1 = sum1 + sum;//如果有小数点，则计算最终实数

		p--;
		if (flag == 1)
			syn = 33;
		else
			syn = 34;
		if (sum > 32767)
			syn = -1;
		else if (sum1 > 32767)
			syn = -1;
	}
	else switch (ch)   //其他字符 
	{
	case'<':m = 0; token[m++] = ch;
		ch = prog[p++];
		if (ch == '=')
		{
			syn = 23;
			token[m++] = ch;
		}
		else if (ch == '>')
		{
			syn = 35;
			token[m++] = ch;
		}
		else
		{
			syn = 22;
			p--;
		}
		break;
	case'>':m = 0; token[m++] = ch;
		ch = prog[p++];
		if (ch == '=')
		{
			syn = 21;
			token[m++] = ch;
		}
		else
		{
			syn = 20;
			p--;
		}
		break;
	case'=':m = 0;
		token[m++] = ch;
		ch = prog[p++];
		if (ch == '=')
		{
			syn = 37;

		}
		else if (ch == ':')
		{
			syn = 38;
			token[m++] = ch;
		}
		else
		{
			syn = 13;
			p--;
		}
		break;
	case'*':syn = 9; token[0] = ch; break;
	case'/':
		m = 0;
		token[m++] = ch;
		ch = prog[p++];
		if (ch == '/')
		{
			syn = 48;

			token[m++] = ch;
			while (ch != '\n')
			{
				ch = prog[p++];
				token[m++] = ch;

			}
		}
		else
		{
			syn = 10;
			p--;
		}
		break;
	case'%':syn = 47; token[0] = ch; break;
	case'+':m = 0;
		token[m++] = ch;
		ch = prog[p++];
		if (ch == '+')
		{
			syn = 43;
			token[m++] = ch;
		}
		else
		{
			syn = 10;
			p--;

		}
		break;
	case'-':m = 0;
		token[m++] = ch;
		ch = prog[p++];
		if (ch == '-')
		{
			syn = 44;
			token[m++] = ch;
		}
		else
		{
			syn = 12;
			p--;

		}
		break;
	case'{':syn = 17; token[0] = ch; break;
	case'}':syn = 18; token[0] = ch; break;
	case';':syn = 25; token[0] = ch; break;
	case'(':syn = 15; token[0] = ch; break;
	case')':syn = 16; token[0] = ch; break;
	case'#':syn = 36; token[0] = ch; break;
	case'\\':
		m = 0; token[m++] = ch;
		ch = prog[p++];
		if (ch == '\\')
		{
			syn = 45;
			token[m++] = ch;
		}
		else if (ch == '\t')
		{
			syn = 27;
			token[m++] = ch;
		}
		else if (ch == '\n')
		{
			syn = 46;
			token[m++] = ch;
		}
		else if (ch == '\0')
		{
			syn = 28;
			token[m++] = ch;
		}
		else {
			syn = 29;
			p--;

		}
		break;
	case',':syn = 24; token[0] = ch; break;
	case'\n':syn = -2; break;
	case'$':syn = 14; token[0] = ch; break;
	case'\"':syn = 30; token[0] = ch; break;
	case'\'':syn = 26; token[0] = ch; break;
	case'\t':syn = 27; token[0] = ch; break;
	case'!':syn = 39; token[0] = ch; break;
	case':':syn = 49; token[0] = ch; break;
	case'&':m = 0; token[m++] = ch;
		ch = prog[p++];
		if (ch == '&')
		{
			syn = 40;
			token[m++] = ch;
		}
		else
		{
			syn = -1;
		}
		break;
	case'|':m = 0;
		token[m++] = ch;
		ch = prog[p++];
		if (ch == '|')
		{
			syn = 41;
			token[m++] = ch;
		}
		else
		{
			syn = -1;
		}
		break;
	default: syn = 0; break;
	}
}

void lex()
{
	int i = 0;
	//char *ch0;
	string ch0;
	p = 0;
	row = 1;
	cout << "Please input string:" << endl;
	do
	{
		cin.get(ch);
		prog[p++] = ch;
	} while (ch != '@');
	p = 0;
	do
	{
		syn = 0;
		scan();
		ch0 = token;
		if (ch0 != ";") {
			str[i] = token;
			str[i++].append("\0");
		}
		else {
			str[i] = ";";
			grammer();
			for (int j = 0; j < 10; j++)str[j] = "";
			i = 0;
		}
		if(syn==-1)cout << "Error in row " << row << "!" << endl;
		if(syn==-2)row = row++;
	} while (syn != 0);
}