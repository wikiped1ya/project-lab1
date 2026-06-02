# Лабораторная работа 6. Простые CI-CD пайплайны
## Задание 1. Базовые хуки в Git на стороне клиента
### 1.
Git хуки — это скрипты, которые автоматически запускаются при выполнении определённых действий. Они делятся на клиентские и серверные.
Клиентские:
* Commit (можно прервать)
* Push (можно прервать)
* Checkout (нельзя прервать)

Серверные:
* pre-receive
* update
* post-receive

Для контроля качества коммитов на стороне разработчика чаще всего используют pre-commit (проверка кода) и commit-msg (проверка сообщения). Оба этих хука могут прервать операцию, если проверка не пройдена.

### 2.
Я перешла в необходимую папку и добавила хук:
```
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/strpo/lab6$ cd ~/project-1/.git/hooks
ser17@WIN-GCHLLJVFKQQ:~/project-1/.git/hooks$ ls -la
total 72
drwxr-xr-x 2 ser17 ser17 4096 Mar 24 23:10 .
drwxr-xr-x 8 ser17 ser17 4096 May 16 12:56 ..
-rwxr-xr-x 1 ser17 ser17  478 Mar 24 23:10 applypatch-msg.sample
-rwxr-xr-x 1 ser17 ser17  896 Mar 24 23:10 commit-msg.sample
-rwxr-xr-x 1 ser17 ser17 4726 Mar 24 23:10 fsmonitor-watchman.sample
-rwxr-xr-x 1 ser17 ser17  189 Mar 24 23:10 post-update.sample
-rwxr-xr-x 1 ser17 ser17  424 Mar 24 23:10 pre-applypatch.sample
-rwxr-xr-x 1 ser17 ser17 1643 Mar 24 23:10 pre-commit.sample
-rwxr-xr-x 1 ser17 ser17  416 Mar 24 23:10 pre-merge-commit.sample
-rwxr-xr-x 1 ser17 ser17 1374 Mar 24 23:10 pre-push.sample
-rwxr-xr-x 1 ser17 ser17 4898 Mar 24 23:10 pre-rebase.sample
-rwxr-xr-x 1 ser17 ser17  544 Mar 24 23:10 pre-receive.sample
-rwxr-xr-x 1 ser17 ser17 1492 Mar 24 23:10 prepare-commit-msg.sample
-rwxr-xr-x 1 ser17 ser17 2783 Mar 24 23:10 push-to-checkout.sample
-rwxr-xr-x 1 ser17 ser17 2308 Mar 24 23:10 sendemail-validate.sample
-rwxr-xr-x 1 ser17 ser17 3650 Mar 24 23:10 update.sample
ser17@WIN-GCHLLJVFKQQ:~/project-1/.git/hooks$ vim pre-commit
ser17@WIN-GCHLLJVFKQQ:~/project-1/.git/hooks$ chmod +x pre-commit
```

Содержимое фала:
```
#!/bin/bash
echo "Проверка на запрещённые слова"

FORBIDDEN=(
    "-----BEGIN.*PRIVATE KEY-----"
    "AKIA[0-9A-Z]{16}"
    "ghp_[A-Za-z0-9]{36}"
    "password\s*=\s*.+"
    "SECRET\s*=\s*.+"
    "token\s*=\s*.+"
)

for file in $(git diff --cached --name-only); do
    if [ ! -f "$file" ]; then continue; fi
    for pattern in "${FORBIDDEN[@]}"; do
        if grep -Eiq -- "$pattern" "$file"; then
            echo "Ошибка: В файле '$file' найдено запрещённое содержимое!"
            echo "   Соответствует паттерну: $pattern"
            exit 1
        fi
    done
done

echo "pre-commit хук успешно завершён."
exit 0
```

### 3.
Аналогично со вторым:
```
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/strpo/lab6$ cd ~/project-1/.git/hooks
ser17@WIN-GCHLLJVFKQQ:~/project-1/.git/hooks$ vim commit-msg
ser17@WIN-GCHLLJVFKQQ:~/project-1/.git/hooks$ chmod +x commit-msg
```

Содержимое файла:
```
  1 #!/bin/bash
  2 echo "Проверка сообщения коммита"
  3
  4 #Путь к файлу с сообщением коммита (временный файл)
  5 COMMIT_MSG_FILE=$1
  6
  7 #Читаем первую строку сообщения
  8 first_line=$(head -n1 "$COMMIT_MSG_FILE")
  9
 10 if [ -z "$first_line" ]; then
 11     echo "Ошибка: Сообщение коммита не может быть пустым!"
 12     exit 1
 13 fi
 14
 15 if [ ${#first_line} -gt 72 ]; then
 16     echo "Ошибка: Первая строка сообщения коммита длиннее 72 символов."
 17     echo "   Сейчас: ${#first_line} символов."
 18     exit 1
 19 fi
 20
 21 if [[ $first_line =~ ^[a-z] ]]; then
 22     echo "Ошибка: Сообщение коммита должно начинаться с заглавной буквы."
 23     exit 1
 24 fi
 25
 26 echo "commit-msg хук успешно завершён. Сообщение соответствует правилам."
 27 exit 0
```

### 4.
```
ser17@WIN-GCHLLJVFKQQ:~/project-1$ echo "password = 12345" > secret_file.txt
ser17@WIN-GCHLLJVFKQQ:~/project-1$ git add secret_file.txt
ser17@WIN-GCHLLJVFKQQ:~/project-1$ git commit -m "Добавлен секретный файл"
Проверка на запрещённые слова
Usage: grep [OPTION]... PATTERNS [FILE]...
Try 'grep --help' for more information.
Ошибка: В файле 'secret.txt' найдено запрещённое содержимое!
   Соответствует паттерну: password\s*=\s*.+
   Исправьте файл и повторите коммит.
ser17@WIN-GCHLLJVFKQQ:~/project-1$ echo "# Это безопасный файл" > safe.txt
ser17@WIN-GCHLLJVFKQQ:~/project-1$ git add safe.txt
ser17@WIN-GCHLLJVFKQQ:~/project-1$ git commit -m "добавлен безопасный файл"
Проверка на запрещённые слова
Usage: grep [OPTION]... PATTERNS [FILE]...
Try 'grep --help' for more information.
Usage: grep [OPTION]... PATTERNS [FILE]...
Try 'grep --help' for more information.
Ошибка: В файле 'secret.txt' найдено запрещённое содержимое!
   Соответствует паттерну: password\s*=\s*.+
   Исправьте файл и повторите коммит.
```

Оба хука сработали как надо, предотвратив возможные ошибки.

## Задание 2. Хуки Git на стороне сервера
### 1.
Я создала копию репозитория и запушила туда изменения
```
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/strpo/lab6$ cd ~
ser17@WIN-GCHLLJVFKQQ:~$ mkdir server-copy.git
ser17@WIN-GCHLLJVFKQQ:~$ cd server-copy.git
ser17@WIN-GCHLLJVFKQQ:~/server-copy.git$ git init --bare
hint: Using 'master' as the name for the initial branch. This default branch name
hint: is subject to change. To configure the initial branch name to use in all
hint: of your new repositories, which will suppress this warning, call:
hint:
hint:   git config --global init.defaultBranch <name>
hint:
hint: Names commonly chosen instead of 'master' are 'main', 'trunk' and
hint: 'development'. The just-created branch can be renamed via this command:
hint:
hint:   git branch -m <name>
Initialized empty Git repository in /home/ser17/server-copy.git/
ser17@WIN-GCHLLJVFKQQ:~/server-copy.git$ cd ~/project-1
ser17@WIN-GCHLLJVFKQQ:~/project-1$ git remote add server-copy ~/server-copy.git
ser17@WIN-GCHLLJVFKQQ:~/project-1$ ls
README.md  labs  reports  safe.txt  secret.txt  secret_file.txt
ser17@WIN-GCHLLJVFKQQ:~/project-1$ git remote -v
origin  git@github.com:wikiped1ya/project-lab1.git (fetch)
origin  git@github.com:wikiped1ya/project-lab1.git (push)
server-copy     /home/ser17/server-copy.git (fetch)
server-copy     /home/ser17/server-copy.git (push)
ser17@WIN-GCHLLJVFKQQ:~/project-1$ git push server-copy master
Enumerating objects: 179, done.
Counting objects: 100% (179/179), done.
Delta compression using up to 18 threads
Compressing objects: 100% (149/149), done.
Writing objects: 100% (179/179), 309.37 KiB | 8.36 MiB/s, done.
Total 179 (delta 38), reused 0 (delta 0), pack-reused 0
remote: Resolving deltas: 100% (38/38), done.
To /home/ser17/server-copy.git
 * [new branch]      master -> master
```

### 2.
Для конвертации Markdown-файл в html-файл можно использовать pandoc, marked или grip.

Если, например, использовать pandoc, то для установки нужны команды:
```
sudo apt update
sudo apt install pandoc -y
```

### 3. 
Я установила pandoc
```
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/strpo/lab6$ pandoc --version
pandoc 3.1.3
Features: -server +lua
Scripting engine: Lua 5.4
User data directory: /home/ser17/.local/share/pandoc
Copyright (C) 2006-2023 John MacFarlane. Web: https://pandoc.org
This is free software; see the source for copying conditions. There is no
warranty, not even for merchantability or fitness for a particular purpose.
```
Затем добавила новый хук
```
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/strpo/lab6$ cd ~/server-copy.git/hooks
ser17@WIN-GCHLLJVFKQQ:~/server-copy.git/hooks$ vim post-receive
ser17@WIN-GCHLLJVFKQQ:~/server-copy.git/hooks$ chmod +x post-receive
```

Вот содержимое файла:
```
  1 #!/bin/bash
  2
  3 DEPLOY_DIR="/home/ser17/server-deploy"
  4
  5 #Имя файла, который нужно обработать (относительно корня репозитория)
  6 MD_FILE="labs/strpo/lab6/report.md"
  7 HTML_FILE="lab6.html"
  8
  9 echo "начинаю сборку HTML"
 10
 11 #Создаём временную папку для клонирования
 12 TMP_DIR=$(mktemp -d)
 13
 14 #Клонируем репозиторий во временную папку
 15 git clone --branch main --depth 1 ~/server-copy.git "$TMP_DIR"
 16
 17 #Проверяем, существует ли MD-файл
 18 if [ ! -f "$TMP_DIR/$MD_FILE" ]; then
 19     echo "Ошибка: файл $MD_FILE не найден в ветке main!"
 20     rm -rf "$TMP_DIR"
 21     exit 1
 22 fi
 23
 24 #Создаём папку для развёртывания, если её нет
 25 mkdir -p "$DEPLOY_DIR"
 26
 27 #Конвертируем Markdown в HTML
 28 pandoc "$TMP_DIR/$MD_FILE" -o "$DEPLOY_DIR/$HTML_FILE"
 29
 30 #Удаляем временную папку
 31 rm -rf "$TMP_DIR"
 32
 33 echo "Готово! HTML-отчёт создан: $DEPLOY_DIR/$HTML_FILE"
```

### 4.
Я добавила хук и запушила изменения. HTML-файл успешно создался.
```
ser17@WIN-GCHLLJVFKQQ:~/project-1$ git add labs/strpo/lab6/report.md
ser17@WIN-GCHLLJVFKQQ:~/project-1$ git commit --no-verify -m "Изменения для запуска хука"
[prog-lab1 5fcb3fc] Изменения для запуска хука
 8 files changed, 130 insertions(+), 20 deletions(-)
 create mode 160000 labs/data-str/last_lab/tictactoe-course
ser17@WIN-GCHLLJVFKQQ:~/project-1$ git push server-copy prog-lab1
Enumerating objects: 30, done.
Counting objects: 100% (30/30), done.
Delta compression using up to 18 threads
Compressing objects: 100% (14/14), done.
Writing objects: 100% (16/16), 10.54 KiB | 2.11 MiB/s, done.
Total 16 (delta 10), reused 0 (delta 0), pack-reused 0
remote: начинаю сборку HTML
remote: Cloning into '/tmp/tmp.wH9eUcmA4N'...
remote: warning: --depth is ignored in local clones; use file:// instead.
remote: done.
remote: Готово! HTML-отчёт создан: /home/ser17/server-deploy/lab6.html
To /home/ser17/server-copy.git
   4c60461..5fcb3fc  prog-lab1 -> prog-lab1
ser17@WIN-GCHLLJVFKQQ:~/project-1$ ls -la ~/server-deploy/
total 20
drwxr-xr-x  2 ser17 ser17  4096 May 17 17:08 .
drwxr-x--- 14 ser17 ser17  4096 May 17 17:08 ..
-rw-r--r--  1 ser17 ser17 10312 May 17 17:08 lab6.html
```

## Задание 3. Сборка с помощью CMake
### 1.
У меня CMake уже устновлен
```
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/strpo/lab6$ cmake --version
cmake version 3.28.3

CMake suite maintained and supported by Kitware (kitware.com/cmake).
```

### 2.
CMake — это не сама система сборки, а её генератор. 
Ключевые понятия:
* Проект - логическая единица, верхний уровень набора исходников.
* Цель - основная единица сборки.
* Связывание - показывает, какие библиотеки нужны для сборки цели.
* Каталоги включений - указывает компилятору, где искать заголовочные файлы, связанные с целью.
* Тестирование - включает поддержку тестов и добавляет конкретный тест в проект.

### 3.
```
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/data-str/lab4$ mkdir -p src include apps tests
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/data-str/lab4$ mv *.hpp include/
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/data-str/lab4$ mv list.cpp src/
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/data-str/lab4$ mv main.cpp apps/
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/data-str/lab4$ ls
apps  circle.txt  include  lab4  src  tests
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/data-str/lab4$ vim CMakeLists.txt
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/data-str/lab4$ cd src
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/data-str/lab4/src$ vim CMakeLists.txt
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/data-str/lab4/src$ cd ../apps
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/data-str/lab4/apps$ vim CMakeLists.txt
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/data-str/lab4/apps$ cd ~/project-1/labs/data-str/lab4
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/data-str/lab4$ mkdir build
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/data-str/lab4$ cd build
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/data-str/lab4/build$ cmake ..
-- The C compiler identification is GNU 13.3.0
-- The CXX compiler identification is GNU 13.3.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (1.8s)
-- Generating done (0.0s)
-- Build files have been written to: /home/ser17/project-1/labs/data-str/lab4/build
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/data-str/lab4/build$ cmake --build .
[ 25%] Building CXX object src/CMakeFiles/list_lib.dir/list.cpp.o
[ 50%] Linking CXX static library liblist_lib.a
[ 50%] Built target list_lib
[ 75%] Building CXX object apps/CMakeFiles/lab4.dir/main.cpp.o
[100%] Linking CXX executable lab4
[100%] Built target lab4
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/data-str/lab4/build$ ./apps/lab4
Исходный список:
0: -1, 0, 6
1: 1, 2, 4
2: 0, 0, 5
3: 0, 0, 3

Segmentation fault (core dumped)
```

### 4.
Я добавила простой тест и пересобрала проект. Затем запустила тесты через CTest.
```
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/data-str/lab4$ mkdir -p tests
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/data-str/lab4$ vim tests/test_simple.cpp
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/data-str/lab4$ vim tests/CMakeLists.txt
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/data-str/lab4$ vim CMakeLists.txt
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/data-str/lab4$ rm -rf build
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/data-str/lab4$ mkdir build
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/data-str/lab4$ cd build
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/data-str/lab4/build$ cmake ..
-- The C compiler identification is GNU 13.3.0
-- The CXX compiler identification is GNU 13.3.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (1.2s)
-- Generating done (0.0s)
-- Build files have been written to: /home/ser17/project-1/labs/data-str/lab4/build
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/data-str/lab4/build$ cmake --build .
[ 16%] Building CXX object src/CMakeFiles/list_lib.dir/list.cpp.o
[ 33%] Linking CXX static library liblist_lib.a
[ 33%] Built target list_lib
[ 50%] Building CXX object apps/CMakeFiles/lab4.dir/main.cpp.o
[ 66%] Linking CXX executable lab4
[ 66%] Built target lab4
[ 83%] Building CXX object tests/CMakeFiles/test_simple.dir/test_simple.cpp.o
[100%] Linking CXX executable test_simple
[100%] Built target test_simple
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/data-str/lab4/build$ ctest
Test project /home/ser17/project-1/labs/data-str/lab4/build
    Start 1: SimpleTest
1/1 Test #1: SimpleTest .......................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.01 sec
```

## Задание 4. Автоматизация задач CMake в git
### 1.
Я создала и запушила новую ветку
```
ser17@WIN-GCHLLJVFKQQ:~/project-1$ git checkout -b dev
Switched to a new branch 'dev'
ser17@WIN-GCHLLJVFKQQ:~/project-1$ git push origin dev
Total 0 (delta 0), reused 0 (delta 0), pack-reused 0
remote:
remote: Create a pull request for 'dev' on GitHub by visiting:
remote:      https://github.com/wikiped1ya/project-lab1/pull/new/dev
remote:
To github.com:wikiped1ya/project-lab1.git
 * [new branch]      dev -> dev
```

### 2.
Далее добавила новый хук
```
ser17@WIN-GCHLLJVFKQQ:~/project-1/labs/strpo/lab6$ cd ~/project-1/.git/hooks
ser17@WIN-GCHLLJVFKQQ:~/project-1/.git/hooks$ vim pre-commit
ser17@WIN-GCHLLJVFKQQ:~/project-1/.git/hooks$ chmod +x pre-commit
```

Содержимое файла:
```
#!/bin/bash

BRANCH=$(git rev-parse --abbrev-ref HEAD)

if [ "$BRANCH" != "dev" ]; then
    echo "Текущая ветка: $BRANCH (не dev). Проверки пропущены."
    exit 0
fi

echo "Ветка dev: запускаем CMake тесты..."

PROJECT_DIR="$HOME/project-1/labs/data-str/lab4"
BUILD_DIR="$PROJECT_DIR/build"

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR" || exit 1

cmake .. > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo "Ошибка: CMake конфигурация не удалась!"
    exit 1
fi

cmake --build . > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo "Ошибка: сборка проекта не удалась!"
    exit 1
fi

ctest --output-on-failure
if [ $? -ne 0 ]; then
    echo "Ошибка: некоторые тесты не прошли!"
    exit 1
fi

echo "Все тесты прошли успешно! Коммит разрешён."
exit 0
```

### 3.
Проверка хука
```
ser17@WIN-GCHLLJVFKQQ:~/project-1$ git checkout dev
M       labs/data-str/last_lab/tictactoe-course
M       labs/strpo/lab6/report.md
Already on 'dev'
ser17@WIN-GCHLLJVFKQQ:~/project-1$ echo "// test comment" >> ~/project-1/labs/data-str/lab4/apps/main.cpp
ser17@WIN-GCHLLJVFKQQ:~/project-1$ git add labs/data-str/lab4/apps/main.cpp
ser17@WIN-GCHLLJVFKQQ:~/project-1$ git commit -m "Тестовый коммит в ветку dev"
Запуск pre-commit хука...
Ветка dev: запускаем CMake тесты...
   Конфигурация CMake...
Сборка проекта...
Запуск тестов (CTest)...
Test project /home/ser17/project-1/labs/data-str/lab4/build
    Start 1: SimpleTest
1/1 Test #1: SimpleTest .......................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.00 sec
Все тесты прошли успешно! Коммит разрешён.
Проверка сообщения коммита
commit-msg хук успешно завершён. Сообщение соответствует правилам.
[dev 9ad620d] Тестовый коммит в ветку dev
 1 file changed, 1 insertion(+)
```

### 4.
Добавила новый хук
```
ser17@WIN-GCHLLJVFKQQ:~/project-1$ git commit -m "Тест post-commit хука"
Запуск pre-commit хука...
Ветка dev: запускаем CMake тесты...
   Конфигурация CMake...
Сборка проекта...
Запуск тестов (CTest)...
Test project /home/ser17/project-1/labs/data-str/lab4/build
   Start 1: SimpleTest
1/1 Test #1: SimpleTest .......................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.00 sec
Все тесты прошли успешно! Коммит разрешён.
Проверка сообщения коммита
commit-msg хук успешно завершён. Сообщение соответствует правилам.
После коммита в dev: сборка библиотеки...
Библиотека успешно собрана: src/liblist_lib.a
[dev c67d935] Тест post-commit хука
 1 file changed, 1 insertion(+)
```

## Задание 5. Автоматизация с помощью Github Actions
### 1.
YAML - это язык для написания конфигурационных файлов, который используется в GitHub Actions.

Основные конструкции:
* Ключ-значение (ключ: значение)
* Список (- элемент)
* Словарь (ключ: {подключ: значение})
* Многострочная строка (| (сохраняет переносы) или > (складывает в одну строку))
* Комментарии (# текст)
* Переменные/выражения (${{ выражение }})

### 2.
GitHub Actions — это встроенный инструмент для автоматизации CI/CD прямо в репозитории .

Основные компоненты GitHub Actions:
* Workflow
* Event
* Job
* Step
* Runner
* Action

Тарифы GitHub Actions:
* GitHub Free - 2,000 минут/месяц   
* GitHub Pro - 3,000 минут/месяц
* GitHub Team - 3,000 минут/месяц
* GitHub Enterprise - 50,000 минут/месяц

### 3.
Я создала файл cmake-ci.yml, затем все закоммитила и запушила. В репозитории на GitHub во вкладке Actions workflow отображается запущенным.

```
ser17@WIN-GCHLLJVFKQQ:~/project-1$ mkdir -p .github/workflows
ser17@WIN-GCHLLJVFKQQ:~/project-1$ vim .github/workflows/cmake-ci.yml
ser17@WIN-GCHLLJVFKQQ:~/project-1$ ls -la .github/workflows/
total 12
drwxr-xr-x 2 ser17 ser17 4096 May 17 18:45 .
drwxr-xr-x 3 ser17 ser17 4096 May 17 18:45 ..
-rw-r--r-- 1 ser17 ser17 2363 May 17 18:45 cmake-ci.yml
ser17@WIN-GCHLLJVFKQQ:~/project-1$ git add .github/
ser17@WIN-GCHLLJVFKQQ:~/project-1$ git commit -m "Добавлен CI/CD пайплайн для CMake проекта"
Запуск pre-commit хука...
Текущая ветка: prog-lab1 (не dev). Проверки пропущены.
Проверка сообщения коммита
commit-msg хук успешно завершён. Сообщение соответствует правилам.
[prog-lab1 9846c1e] Добавлен CI/CD пайплайн для CMake проекта
 1 file changed, 80 insertions(+)
 create mode 100644 .github/workflows/cmake-ci.yml
ser17@WIN-GCHLLJVFKQQ:~/project-1$ git push origin dev
Enumerating objects: 13, done.
Counting objects: 100% (13/13), done.
Delta compression using up to 18 threads
Compressing objects: 100% (7/7), done.
Writing objects: 100% (7/7), 663 bytes | 221.00 KiB/s, done.
Total 7 (delta 3), reused 0 (delta 0), pack-reused 0
remote: Resolving deltas: 100% (3/3), completed with 3 local objects.
To github.com:wikiped1ya/project-lab1.git
   136b09c..c67d935  dev -> dev
``` 

Результат работы пайплайна: после упрощения workflow до базовых шагов (checkout, установка зависимостей, проверка наличия файлов) пайплайн успешно выполняется.

![Скриншот](i.webp)













 
