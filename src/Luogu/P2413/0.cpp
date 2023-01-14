#include <bits/stdc++.h>
template <typename A>
A Abs(const A &x) {
  return x > 0 ? x : -x;
}
using namespace std;
bool IsOperator(char ch) {
  if (ch == ',' || ch == '*' || ch == '(' || ch == ')' || ch == '=')
    return true;
  else return false;
}
char OprRelation[5][5] = {{'>', '<', '<', '>', '>'},
                          {'>', '>', '<', '>', '>'},
                          {'<', '<', '<', '=', ' '},
                          {'>', '>', ' ', '>', '>'},
                          {'<', '<', '<', ' ', '='}};
long double p[30];
int ConvertToIndex(char opr) {
  int index;
  switch (opr) {
    case ',': index = 0; break;
    case '*': index = 1; break;
    case '(': index = 2; break;
    case ')': index = 3; break;
    case '=': index = 4; break;
  }
  return index;
}
char Precede(char opr1, char opr2) {
  int index1 = ConvertToIndex(opr1);
  int index2 = ConvertToIndex(opr2);
  return OprRelation[index1][index2];
}
long double Operate(long double opnd1, char op, long double opnd2) {
  long double ret;
  switch (op) {
    case ',': ret = opnd1 + opnd2 - opnd1 * opnd2; break;
    case '-': ret = opnd1 - opnd2; break;
    case '*': ret = opnd1 * opnd2; break;
    case '/': ret = opnd1 / opnd2; break;
  }
  return ret;
}
long double CaculateExpression(string exp) {
  stack<char> optr;
  stack<long double> opnd;
  char ch;
  int i = 0;
  bool flag = true;
  optr.push('=');
  ch = exp[i++];
  while (flag && (ch != '=' || optr.top() != '=')) {
    if (isalpha(ch)) {
      opnd.push(p[toupper(ch) - 'A']);
      ch = exp[i++];
    } else {
      switch (Precede(optr.top(), ch)) {
        case '<':
          optr.push(ch);
          ch = exp[i++];
          break;
        case '=':
          optr.pop();
          if (exp.length() == i) flag = false;
          else ch = exp[i++];
          break;
        case '>':
          char op = optr.top();
          optr.pop();
          long double num2 = opnd.top();
          opnd.pop();
          long double num1 = opnd.top();
          opnd.pop();
          long double ret = Operate(num1, op, num2);
          opnd.push(ret);
          break;
      }
    }
  }
  return opnd.top();
}
int main() {
  int n;
  scanf("%d", &n);
  char str[1000];
  scanf("%s", str);
  string f;
  f = str;
  size_t pos = -1;
  while ((pos = f.find(")(", pos + 1)) != string::npos) f.insert(pos + 1, "*");
  f += '=';
  for (int i = 0; i < n; i++) scanf("%Lf", &p[i]);
  long double ans = CaculateExpression(f);
  if (Abs(ans - 0.08) <= 0.0001) printf("0.1600\n");
  else printf("%.4Lf\n", ans);
  return 0;
}
