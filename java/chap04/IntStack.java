//package chap04;
//
//public class IntStack {
//    private int[] stk; // 스택용 배열
//    private int capacity; // 스택 용량
//    private int ptr;    // 스택포인트
//
//    // 실행 시 예외: 스택이 비어있음
//    public class EmptyStackException extends RuntimeException {
//        public EmptyStackException() {}
//    }
//
//    // 실행 시 예외: 스택이 가득 참
//    public class OverflowIntStackException extends RuntimeException {
//        public OverflowIntStackException() {}
//    }
//
//    // 생성자
//    public IntStack(int maxlen) {
//        ptr = 0;
//        capacity = maxlen;
//        try {
//            stk = new int[capacity];
//        } catch (OutOfMemoryError e) {
//            capacity = 0;
//        }
//    }
//
//    // 스택에 x를 푸시
//    public int push(int x) throws OverflowIntStackException {
//        if (ptr >= capacity)
//            throw new OverflowIntStackException();
//        return stk[ptr++] = x;
//    }
//
//    // 스택에서 데이터를 팝
//    public int pop() throws EmptyStackException {
//        if (ptr <= 0)
//            throw new EmptyStackException();
//        return stk[--ptr];
//    }
//
//    // 맨 위 데이터를 peek
//    public int peek() throws EmptyStackException {
//        if (ptr <= 0) // 스택이 비어 있음
//            throw new EmptyStackException();
//        return stk[ptr - 1];    // 데이터를 빼는게 아니므로 ptr의 수에는 변화가 없음
//    }
//
//    // 스택을 비움
//    public void clear() {
//        ptr = 0;
//    }
//
//    // x를 찾아 인덱스 반환(없으면 -1)
//    public int indexOf(int x) {
//        for (int i = ptr - 1; i >= 0; i--) // 꼭대기 쪽부터 선형 검색
//            if (skt[i] == x)
//                return i;
//        return -1;
//    }
//
//    // 스택 용량 반환
//    public int getCapacity() {
//        return capacity;
//    }
//
//    // 스택에 쌓여 있는 데이터 개수 반환
//    public int size() {
//        return ptr;
//    }
//
//    // 스택이 비어 있는가
//    public boolean isEmpty() {
//        return ptr <= 0;
//    }
//
//    // 스택이 가득 찾는가
//    public boolean isFull() {
//        return ptr >= capacity;
//    }
//}
