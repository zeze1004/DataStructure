#include <iostream>
#include <stack>
#include <vector>

using namespace std;
  
// n개의 원판을 from에서 to로 이동시키자 (temp 기둥을 이용할 수 있음)
void hanoi(int n, char from, char temp, char to) {

   // stack을 이용하자
   stack<vector<int>> s; // [ n, type, from, temp, to ]
   vector<int> poped;

   // 4번째 원판을 A에 B를 거쳐 C로 : 4 0 A B C => 0 이면 n번째 원판
   // 4개 원판들을 A에 B를 거쳐 C로 : 4 1 A B C => 1 이면 n개의 원판들


   // 맨 처음에, 스택에 이 명령을 넣는다.
   // 명령: n from temp to
   s.push({ n, 1, (int)from, (int)temp, (int)to });                       //배열로 명령어를 넣어준다.

   // 반복: stack이 비어있지 않는 한
   while (s.size() != 0) {

      // 스택 맨 위를 읽는다(가져온다).
      poped = s.top(); // 4 0 A B C
      s.pop();

      // 1. 만약: 1개의 원판을 이동하는 명령이라면
      if (poped[1] == 0) {
         // 이동내용을 출력한다.
         cout << poped[0] << ": " << (char)poped[2] << "->" << (char)poped[4] << '\n';
      } else {
         // 1층짜리 원판이면, 이동내용을 출력한다.
         if (poped[0] == 1) {
            cout << poped[0] << ": " << (char)poped[2] << "->" << (char)poped[4] << '\n';
         } else {
            // 2. 그게 아니라면:

            //// 명령(n a b c : n개를 a에서 b를 거쳐 c에 이동)을 세 단계로 나누고 스텍은 반대로 넣어야한다.
            // 스택에 [n-1개 b a c] 라는 명령을 넣는다.
            s.push({poped[0] - 1, 1, poped[3], poped[2], poped[4]});

            // 스택에 [n번째 a b c] 라는 명령을 넣는다.
            s.push({poped[0], 0, poped[2], poped[3], poped[4]});

            // 스택에 [n-1개 a c b] 라는 명령을 넣는다.
            s.push({poped[0] - 1, 1, poped[2], poped[4], poped[3]});
         }
      }
   }
}

int main() {
   hanoi(4, 'A','B','C');
   return 0;
}