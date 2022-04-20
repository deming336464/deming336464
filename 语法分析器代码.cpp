#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
void A();  //  A -> V:=E
void E();  //  E -> TE'
void T();  //  T -> FT'
void E1(); //  E'-> +TE'|-TE'|null
void T1(); //  T'-> *FT'|/FT'|null
void F();  //  F -> V|(E)
void V();  //  V -> a|b|c|d|e...|z

char s[50],n='1';   //s[50]用于存放输入的赋值表达式
char Table[50][3];  //产生中间代码所需的符号表
int SIGN,sym;   //sym为s[50]中当前读入符号的下标
int list_n=0;   //符号表的下标
/*消除左递归及回溯
A -> V:=E
E -> TE'
E'-> +TE'|-TE'|null
T -> FT'
T'-> *FT'|/FT'|null
F -> V|(E)
V -> a|b|c|d|e...|z
*/
void A()  //  A -> V:=E
{
	V();
	if(s[sym]==':'&&s[sym+1]=='=') //判断赋值号是否有拼写错误
	{
		sym+=2;
		E();
		printf("%s:=%s",Table[list_n-2],Table[list_n-1]);
		printf("     (:=,%s,-,%s)\n",Table[list_n-1],Table[list_n-2]);
	}
	else
	{
		printf("The assignment Symbol spelling mistakes!\n"); //赋值号拼写错误
		SIGN=1;
		
	}
}
void V()  // V -> a|b|c|d|e...|z
{
	if(islower(s[sym]))
	{
		Table[list_n][0] = s[sym];              //把读取的小写字母存入符号表，便于分析是生成中间代码
		Table[list_n][1] = '\0';
		list_n++;
		sym++;
	}
	else
	{
		printf("Operand Errors!\n");      //运算对象错误
		SIGN=1;
		
	}
}
void E()     //E -> TE'
{
	if(SIGN==0)
	{
		T();
		E1();
	}
}
void T()   // T -> FT'
{
	if(SIGN==0)
	{
		F();
		T1();
	}
}
void E1()               //E'-> +TE'|-TE'|null
{
	int p;
	if(SIGN==0)
	{
		if(s[sym]=='+'||s[sym]=='-')
		{
			p=sym;                  //用p记录出现'+'或'-'时sym的值
			sym++;
			T();
			char ch[3];
			ch[0] = 'T';
			ch[1] = n;
            ch[2] = '\0';
            if(s[p] == '+')
            {
                printf("%s:=%s+%s",ch,Table[list_n-2],Table[list_n-1]);                //输出三地址代码
				printf("     (+,%s,%s,%s)\n", Table[list_n-2],Table[list_n-1],ch);             //输出四元式
			}
			else
			{
				printf("%s:=%s-%s",ch,Table[list_n-2],Table[list_n-1]);               //输出三地址代码
				printf("     (-,%s,%s,%s)\n", Table[list_n-2],Table[list_n-1],ch);        //输出四元式
			}
			strcpy(Table[list_n-2],ch);           //将当前结果归结式放在符号表中
			list_n--;
			n++;
			E1();
        }
	}
}
void T1()  //  T'-> *FT'|/FT'|null
{
    int p;
	if(SIGN==0)
	{
		if(s[sym] == '*'||s[sym]=='/')
		{
			p=sym;
            sym++;
			F();
			char ch[3];
			ch[0] = 'T';
            ch[1] = n;
			ch[2] = '\0';
			if(s[p] == '*')
            {
				printf("%s:=%s*%s",ch,Table[list_n-2],Table[list_n-1]);   //输出三地址代码
				printf("     (*,%s,%s,%s)\n", Table[list_n-2],Table[list_n-1],ch);//输出四元式
			}
			else
			{
				printf("%s:=%s/%s",ch,Table[list_n-2],Table[list_n-1]);   //输出三地址代码
				printf("     (/,%s,%s,%s)\n", Table[list_n-2],Table[list_n-1],ch);//输出四元式
			}
            strcpy(Table[list_n-2],ch);      //将当前结果归结式放在符号表中
			list_n--;
			n++;
			T1();
		}
	}
}
void F()    //F -> V|(E)
{
	if(SIGN==0)
	{
		if(s[sym]=='(')
		{
			sym++;
			E();
			if(s[sym]==')')
                sym++;
			else
			{
                printf("ERROR!\n");
				SIGN=1;
               
			}
		}
        else if(islower(s[sym]))  //判断s[sym]是否是小写字母
			V();
		else
		{
			printf("ERROR!\n");
            SIGN=1;
			
		}
	}
}
int main()
{
		SIGN = 0;  //SIGN用于指示赋值表达式是否出现错误
		sym=0;
		scanf("%s",&s);
		if( s[0] == '\0')  //没有输入的情况直接退出
			return 0;
		A();
		if(s[sym]!='\0'&&SIGN==0)
		{
			printf("ERROR!\n");
			
		}
	return 0;
}
