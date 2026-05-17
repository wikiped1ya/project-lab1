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
✏️  Исправьте файл и повторите коммит.
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
✏️  Исправьте файл и повторите коммит.
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

























