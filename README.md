# cm-h-sasm

ASM 문법에서 아이디어를 얻어 만든 매우 간단한 스크립트 인터프리터.

## 목차

- [문법](#문법)
- [런타임](#런타임)

----

# 문법

ASM과 같이 Instruction이 가장 앞에 오며 한 줄에 한 명령을 적을 수 있습니다.
이 때 모든 인자는 문자열로 다룹니다.

> 주석처럼 쓰인 명령이 있으나 주석은 지원하지 않습니다.

## ADD [arg1] [arg2] ...

ADD 명령은 인자들은 모두 더해 메모리에 저장합니다.

```
ADD 1 2 3
PRINT_I // 6
```

## MINUS [arg1] [arg2] [arg3] ...

MINUS 명령은 첫 번째 인자에서 나머지 인자를 모두 뺀 다음 메모리에 저장합니다.

```
MINUS 10 1 2
PRINT_I // 7
```

## PRINT_I

PRINT_I 명령은 최근에 계산한 결과를 메모리에서 출력합니다.

```
ADD 1 1
PRINT_I // 2
```

## SET [key] [value]

SET 명령은 내부 KEY-VALUE 스토리지에 임시로 데이터를 저장합니다.
단, `=` 문자는 지원하지 않습니다.

```
// 정상적으로 작동하는 예시
SET TEST 13
READ TEST // 13

// 정상적으로 작동하지 않는 예시
SET TEST TEST\=13
READ TEST // TEST\
```

## UNSET [key]

UNSET 명령은 내부 KEY-VALUE 스토리지에서 저장된 키 값을 빈 값으로 지정합니다.
빈 값은 `(null)`로 출력됩니다.

```
SET TEST 1
UNSET TEST
READ TEST // (null)
```

## READ [key]

READ 명령은 내부 KEY-VALUE 스토리지에서 특정 값을 읽어옵니다.
없거나 빈 값은 `(null)`로 출력됩니다.

```
SET TEST 2
READ TEST // 2
```

## PRINT [messages]

PRINT 명령은 모든 인자를 그대로 출력합니다.

```
PRINT hello world // hello world
```

# 런타임

런타임은 프로젝트를 CMake로 빌드한 후에 첫 번째 인자로 파일명을 주면 해당 파일을 해석하게 됩니다.
만약 첫 번째 인자가 비어 있는 경우 같은 디렉터리의 index.s 파일이 대신 사용됩니다.

```
./cmhcpu index.s
```
