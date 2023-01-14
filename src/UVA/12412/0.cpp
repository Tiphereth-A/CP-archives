#include <algorithm>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#define REP1(i, l, r) for (int i = (l); i < (r); ++i)
#define REP2(i, l, r) for (int i = (l); i <= (r); ++i)
#define INF 0x3f3f3f3f
#define EPS 1e-5
using namespace std;
struct Student {
  string SID, Name;
  int CID;
  int Ch, Ma, En, Pr, TotScore;
  double AveScore;
  int Rank, InputID;
  static int Cnt;
} stu[1000];
map<string, int> sidTable;
int Student::Cnt = 1;
bool CmpScore(const Student &a, const Student &b) {
  return a.TotScore > b.TotScore;
}
bool CmpInputID(const Student &a, const Student &b) {
  return a.InputID < b.InputID;
}
void PrintMenu() {
  printf(
    "Welcome to Student Performance Management System (SPMS).\n\n"
    "1 - Add\n"
    "2 - Remove\n"
    "3 - Query\n"
    "4 - Show ranking\n"
    "5 - Show Statistics\n"
    "0 - Exit\n\n");
}
void Add() {
  printf(
    "Please enter the SID, CID, name and four scores. Enter 0 to finish.\n");
  string sid, name;
  int cid, ch, ma, en, pr;
  while (cin >> sid) {
    if (sid == "0") return;
    cin >> cid >> name >> ch >> ma >> en >> pr;
    if (sidTable[sid] != 0) {
      printf(
        "Duplicated SID.\n"
        "Please enter the SID, CID, name and four scores. Enter 0 to "
        "finish.\n");
      continue;
    }
    Student *now = &stu[Student::Cnt];
    sidTable[sid] = Student::Cnt;
    now->SID = sid;
    now->Name = name;
    now->CID = cid;
    now->Ch = ch;
    now->Ma = ma;
    now->En = en;
    now->Pr = pr;
    now->TotScore = ch + ma + en + pr;
    now->AveScore = (double)now->TotScore / 4.0 + EPS;
    now->InputID = Student::Cnt++;
    printf(
      "Please enter the SID, CID, name and four scores. Enter 0 to finish.\n");
  }
}
void Remove() {
  printf("Please enter SID or name. Enter 0 to finish.\n");
  string p;
  while (cin >> p) {
    if (p == "0") break;
    int cnt = 0;
    REP2(i, 1, Student::Cnt) {
      if (stu[i].Name == p || stu[i].SID == p) {
        ++cnt;
        Student *now = &stu[i];
        sidTable[now->SID] = 0;
        now->SID = "";
        now->Name = "";
        now->CID = 0;
        now->TotScore = -1;
        now->InputID = INF;
      }
    }
    printf(
      "%d student(s) removed.\n"
      "Please enter SID or name. Enter 0 to finish.\n",
      cnt);
  }
}
void Query() {
  printf("Please enter SID or name. Enter 0 to finish.\n");
  sort(stu + 1, stu + Student::Cnt, CmpScore);
  REP1(i, 1, Student::Cnt)
  stu[i].Rank = (stu[i - 1].TotScore == stu[i].TotScore) ? stu[i - 1].Rank : i;
  sort(stu + 1, stu + Student::Cnt, CmpInputID);
  string p;
  while (cin >> p) {
    if (p == "0") return;
    REP1(i, 1, Student::Cnt) {
      if (stu[i].Name == p || stu[i].SID == p) {
        Student *now = &stu[i];
        cout << now->Rank << " " << now->SID << " " << now->CID << " "
             << now->Name << " " << now->Ch << " " << now->Ma << " " << now->En
             << " " << now->Pr << " " << now->TotScore << " " << fixed
             << setprecision(2) << now->AveScore << endl;
      }
    }
    printf("Please enter SID or name. Enter 0 to finish.\n");
  }
}
void ShowRanking() {
  printf("Showing the ranklist hurts students' self-esteem. Don't do that.\n");
}
void ShowStatistics() {
  printf("Please enter class ID, 0 for the whole statistics.\n");
  int cid, StuCnt = 0;
  cin >> cid;
  int chCnt = 0, maCnt = 0, enCnt = 0, prCnt = 0;
  int pass0 = 0, pass1 = 0, pass2 = 0, pass3 = 0, pass4 = 0;
  double chTot = 0, maTot = 0, enTot = 0, prTot = 0;
  if (cid == 0) {
    REP1(i, 1, Student::Cnt) {
      int passCnt = 0;
      Student *now = &stu[i];
      if (now->CID) {
        ++StuCnt;
        if (now->Ch >= 60) {
          ++chCnt;
          ++passCnt;
        }
        chTot += now->Ch;
        if (now->Ma >= 60) {
          ++maCnt;
          ++passCnt;
        }
        maTot += now->Ma;
        if (now->En >= 60) {
          ++enCnt;
          ++passCnt;
        }
        enTot += now->En;
        if (now->Pr >= 60) {
          ++prCnt;
          ++passCnt;
        }
        prTot += now->Pr;
        if (passCnt == 0) pass0++;
        if (passCnt >= 1) pass1++;
        if (passCnt >= 2) pass2++;
        if (passCnt >= 3) pass3++;
        if (passCnt >= 4) pass4++;
      }
    }
    printf(
      "Chinese\n"
      "Average Score: %.2f\n"
      "Number of passed students: %d\n"
      "Number of failed students: %d\n\n"
      "Mathematics\n"
      "Average Score: %.2f\n"
      "Number of passed students: %d\n"
      "Number of failed students: %d\n\n"
      "English\n"
      "Average Score: %.2f\n"
      "Number of passed students: %d\n"
      "Number of failed students: %d\n\n"
      "Programming\n"
      "Average Score: %.2f\n"
      "Number of passed students: %d\n"
      "Number of failed students: %d\n\n"
      "Overall:\n"
      "Number of students who passed all subjects: %d\n"
      "Number of students who passed 3 or more subjects: %d\n"
      "Number of students who passed 2 or more subjects: %d\n"
      "Number of students who passed 1 or more subjects: %d\n"
      "Number of students who failed all subjects: %d\n\n",
      chTot / (double)StuCnt + EPS,
      chCnt,
      StuCnt - chCnt,
      maTot / (double)StuCnt + EPS,
      maCnt,
      StuCnt - maCnt,
      enTot / (double)StuCnt + EPS,
      enCnt,
      StuCnt - enCnt,
      prTot / (double)StuCnt + EPS,
      prCnt,
      StuCnt - prCnt,
      pass4,
      pass3,
      pass2,
      pass1,
      pass0);
  } else {
    REP1(i, 1, Student::Cnt) {
      int passCnt = 0;
      Student *now = &stu[i];
      if (now->CID == cid) {
        ++StuCnt;
        if (now->Ch >= 60) {
          ++chCnt;
          ++passCnt;
        }
        chTot += now->Ch;
        if (now->Ma >= 60) {
          ++maCnt;
          ++passCnt;
        }
        maTot += now->Ma;
        if (now->En >= 60) {
          ++enCnt;
          ++passCnt;
        }
        enTot += now->En;
        if (now->Pr >= 60) {
          ++prCnt;
          ++passCnt;
        }
        prTot += now->Pr;
        if (passCnt == 0) pass0++;
        if (passCnt >= 1) pass1++;
        if (passCnt >= 2) pass2++;
        if (passCnt >= 3) pass3++;
        if (passCnt >= 4) pass4++;
      }
    }
    printf(
      "Chinese\n"
      "Average Score: %.2f\n"
      "Number of passed students: %d\n"
      "Number of failed students: %d\n\n"
      "Mathematics\n"
      "Average Score: %.2f\n"
      "Number of passed students: %d\n"
      "Number of failed students: %d\n\n"
      "English\n"
      "Average Score: %.2f\n"
      "Number of passed students: %d\n"
      "Number of failed students: %d\n\n"
      "Programming\n"
      "Average Score: %.2f\n"
      "Number of passed students: %d\n"
      "Number of failed students: %d\n\n"
      "Overall:\n"
      "Number of students who passed all subjects: %d\n"
      "Number of students who passed 3 or more subjects: %d\n"
      "Number of students who passed 2 or more subjects: %d\n"
      "Number of students who passed 1 or more subjects: %d\n"
      "Number of students who failed all subjects: %d\n\n",
      chTot / (double)StuCnt + EPS,
      chCnt,
      StuCnt - chCnt,
      maTot / (double)StuCnt + EPS,
      maCnt,
      StuCnt - maCnt,
      enTot / (double)StuCnt + EPS,
      enCnt,
      StuCnt - enCnt,
      prTot / (double)StuCnt + EPS,
      prCnt,
      StuCnt - prCnt,
      pass4,
      pass3,
      pass2,
      pass1,
      pass0);
  }
}
int main() {
  int p;
  PrintMenu();
  while (cin >> p) {
    switch (p) {
      case 1: Add(); break;
      case 2: Remove(); break;
      case 3: Query(); break;
      case 4: ShowRanking(); break;
      case 5: ShowStatistics(); break;
      case 0: exit(0); break;
    }
    PrintMenu();
  }
  return 0;
}
