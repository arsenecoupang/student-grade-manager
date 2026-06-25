# 학생 성적 관리 시스템

## 기능

- 학생 추가 / 삭제
- 성적 수정
- 전체 목록 보기
- 이름으로 검색
- 통계 보기 (과목별 평균, 등급 분포)
- 파일 저장 / 불러오기

## 빌드

```
gcc src/main.c src/student.c -o student_grade_manager
```

## 파일 구조

```
src/
  main.c        - 메인 메뉴 루프
  student.c     - 기능 구현
  student.h     - 구조체 및 함수 선언
```
