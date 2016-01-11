
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <regex>	//c++ 正则表达式

using namespace std;
const char alpha[26]="abcdefghijklmnopqrstuvwxyz";
typedef unordered_map<string,int> Dictionary;
typedef vector<string> vec_string;
typedef set<string> s_str;
char lower(char ch); //大写转小写
vec_string words(string & str);
s_str edit1(const string & word);
s_str edit2(s_str & s,Dictionary & dict);
void correct(string & word,Dictionary & dict);
int main()
{
	string str;
	string word;
	regex pattern("[a-z]+");
	vec_string vs;
	Dictionary dict;
	ifstream fin("big.txt");
	if(!fin)
	{
		cout<<" can not open file"<<endl;
		return -1;
	}
	while(getline(fin,str))
	{
		if(!str.empty())
		{
			vs = words(str);
			for(int i = 0;i<vs.size();i++)
			{
				dict[vs[i]] += 1;
			}
			vs.clear();
		}
	}
	cout<<"Please input a word"<<endl;
	while(1)
	{
		cin>>word;
		correct(word,dict);
	}
	return 0;
}

char lower(char ch)
{
	if(ch >= 'A' && ch <= 'Z')
		return ch + 32;
	else
		return ch;
}

vec_string words(string & str)
{
	vec_string vs;
	transform(str.begin(),str.end(),str.begin(),lower);
	regex pattern("[a-z]+");
	smatch mat;
	string::const_iterator start = str.begin();
    string::const_iterator end = str.end();
	//regex_match()只有在整个字符串匹配正则表达式时才返回 true, 
	//而 regex_search()在子串匹配就返回 true.
	while(regex_search(start,end,mat,pattern))
	{
		/*std::wsmatch 是一个由若干个 std::wssub_match 对象构成的数组. 
		而 std::wssub_match 派生自 pair.由std::wssub_match::first保存
		子串的起始位置指针(其实说是迭代器比较准确一点).由std::wssub_match::second
		保存子串的结束位置 +1 的指针(STL的通用原则,半开区间).所以
		[std::wssub_match::first,std::wssub_match::second) 就是子串的全部内容.
		*/
		string msg(mat[0].first,mat[0].second);
		vs.push_back(msg);
		start = mat[0].second;
	}
	return vs;
}

//编辑距离为1
s_str edit1(const string & word)
{
	s_str sub_str;
	//删除一个字符
	for(int i = 0;i<word.length();i++)
	{
		string temp = word;
		temp.erase(i,1);
		sub_str.insert(temp);
	}
	//交换相邻两个字符
	for(int i = 0;i<word.length()-1;i++)
	{
		string temp=word;
		char tempchar;
		tempchar = temp[i];
		temp[i] = temp[i+1];
		temp[i+1] = tempchar;
		sub_str.insert(temp);
	}
	//替换一个字符
	for(int i = 0;i<word.length();i++)
	{
		for(int j = 0;j<26;j++)
		{
			string temp = word;
			temp[i] = alpha[j];
			sub_str.insert(temp);
		}
		
	}
	//插入一个字符
	for(int i = 0;i<word.length();i++)
	{
		for(int j = 0;j<26;j++)
		{
			string temp = word;
			temp.insert(i,1,alpha[j]);
			sub_str.insert(temp);
		}
	}

	return sub_str;
}

//编辑距离为2
s_str edit2(s_str & s,Dictionary & dict)
{
	s_str edit2_substr;
	s_str substr;
	for(s_str::iterator it = s.begin();it != s.end();it++)
	{
		substr = edit1(*it);
		for(s_str::iterator index = substr.begin();index != substr.end();index++)
		{
			if(dict[*index] > 0)
				edit2_substr.insert(*index);
		}
	}
	return edit2_substr;
}

void correct(string & word,Dictionary & dict)
{
	if(dict[word] > 0)
		cout<<word<<endl;
	else
	{
		s_str s = edit1(word);
		s_str s1;
		s_str::iterator it;
		for(it = s.begin();it != s.end();it++)
		{
			if(dict[*it] > 0)
				s1.insert(*it);
		}
		if(s1.size()>0)
		{
			//找出dict[]最大值
			struct node
			{
				int max;
				string sss;
			};
			node right;
			s_str::iterator in;
			for(in = s1.begin(),right.sss=*in,right.max=dict[*in];in != s1.end();in++)
			{
				if(dict[*in] > right.max)
				{
					right.max=dict[*in];
					right.sss = *in;
				}
			}
			cout<<right.sss<<endl;
		}
		else
		{
			s_str edit2_substr;
			edit2_substr = edit2(s,dict);
			if(edit2_substr.size()>0)
			{
			struct node
			{
				int max;
				string sss;
			};
			node x;
			s_str::iterator xx;
			for(xx = edit2_substr.begin(),x.sss=*xx,x.max=dict[*xx];xx != edit2_substr.end();xx++)
			{
				if(dict[*xx] > x.max)
				{
					x.max=dict[*xx];
					x.sss = *xx;
				}
			}
			cout<<x.sss<<endl;
		}
		else
			cout<<word<<endl;
		}
	}
}
