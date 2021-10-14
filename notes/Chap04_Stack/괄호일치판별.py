# 괄호 일치 판별 함수
# 리트코드 20번
def isValid(self, s: str) -> bool:
    stack = []
    table = {
        ')': '(',
        '}': '{',
        ']': '['
    }

    # 스택 이용 예외 처리 및 일치 여부 판별
    for i in s:
        if i not in table:
            stack.append(i)
        elif not stack or table[i] != stack.pop():
            return False
    # stack 원소 없으면 괄호 일치
    return len(stack) == 0

