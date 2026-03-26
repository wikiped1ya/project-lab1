# Отчет по выполнению работы

## Задание 1
- ser17@WIN-GCHLLJVFKQQ:~/project-1$ git version  
git version 2.43.0

- ser17@WIN-GCHLLJVFKQQ:~$ git config --list  
user.email=vshalnuh@gmail.com  
user.name=wikiped1ya

- ser17@WIN-GCHLLJVFKQQ:~/project-1$ git --help  
These are common Git commands used in various situations:  
start a working area (see also: git help tutorial)  
   clone     Clone a repository into a new directory  
   init      Create an empty Git repository or reinitialize an existing one  
work on the current change (see also: git help everyday)  
   add       Add file contents to the index  
   mv        Move or rename a file, a directory, or a symlink  
   restore   Restore working tree files  
   rm        Remove files from the working tree and from the index  
examine the history and state (see also: git help revisions)  
   bisect    Use binary search to find the commit that introduced a bug  
   diff      Show changes between commits, commit and working tree, etc  
   grep      Print lines matching a pattern  
   log       Show commit logs  
   show      Show various types of objects  
   status    Show the working tree status  
grow, mark and tweak your common history  
   branch    List, create, or delete branches  
   commit    Record changes to the repository  
   merge     Join two or more development histories together  
   rebase    Reapply commits on top of another base tip  
   reset     Reset current HEAD to the specified state  
   switch    Switch branches  
   tag       Create, list, delete or verify a tag object signed with GPG  
collaborate (see also: git help workflows)  
   fetch     Download objects and refs from another repository  
   pull      Fetch from and integrate with another repository or a local branch  
   push      Update remote refs along with associated objects  

- Команда git --help выводит на консоль основные команды git. Нампример, init, создающий репозиторий, commit, делающий коммит, и прочие.  

## Задание 2
- Директория и файлы созданы с помощью команд init, mkdir, vim. 

- Основные синтаксические элементы языка Markdown:  
Заголовки обозначаются символом решетки(чем больше решеток, тем ниже уровень заголовка). Параграфы разделяются пропущенными строками. Текст можно выделять *курсивом*, **жирным шрифтом**, ~~зачеркнутым~~ при помощи одной, двух звездочек и тильды соответсвенно. Списки можно нумеровать цифрами, маркировать тире. Так же можно оставлять ссылки в тексте: [Отсюда](https://gist.github.com/Jekins/2bf2d0638163f1294637) была взята вся эта информация, из поста на гит. 

- ser17@WIN-GCHLLJVFKQQ:~/project-1$ git add README.md reports/lab1.md  
ser17@WIN-GCHLLJVFKQQ:~/project-1$ git commit -m "Начальный коммит"  
[master (root-commit) c35051b] Начальный коммит  
 2 files changed, 57 insertions(+)  
 create mode 100644 README.md  
 create mode 100644 reports/lab1.md  

- Сначала файлы переводятся в режим staget(то есть подготовлены к коммиту) при помощи комманды add, а затем создается сам коммит к текстовым сообщением "Начальный коммит" с помощью команды commit -m.

## Задание 3
- ser17@WIN-GCHLLJVFKQQ:~/project-1$ git add reports/lab1.md  
ser17@WIN-GCHLLJVFKQQ:~/project-1$ git status  
On branch master  
Changes to be committed:  
  (use "git restore --staged <file>..." to unstage)  
        modified:   reports/lab1.md  

ser17@WIN-GCHLLJVFKQQ:~/project-1$ git commit -m "Тот же коммит коммит"  
[master 6958af4] Тот же коммит коммит  
 1 file changed, 9 insertions(+)  
ser17@WIN-GCHLLJVFKQQ:~/project-1$ git status  
On branch master  
nothing to commit, working tree clean  

- После первого коммита(начального) git status показал, что изменений нет, так как тогда файл был только создан. Сейчас git status вывел информацию об изменениях после первого коммита.

- Команда git diff вывела конкретные строчки, которые были добавлены/удалены.

- На этапе 3.3 git status показывает, что изменений нет, а git diff вывело то же, что и прежде

- ser17@WIN-GCHLLJVFKQQ:~/project-1$ git status  
On branch master  
Changes to be committed:  
  (use "git restore --staged <file>..." to unstage)  
        modified:   reports/lab1.md  

- После изменения файла и добавления их в индекс git status показывает, что изменения есть и они ждут коммита.

- Файл reports/lab1.md был в индексе, а README.md нет. Поэтому когда я создаю коммит, сохраняется только первый

- ser17@WIN-GCHLLJVFKQQ:~/project-1$ git status  
On branch master  
Changes to be committed:  
  (use "git restore --staged <file>..." to unstage)  
        modified:   reports/lab1.md  
Changes not staged for commit:  
  (use "git add/rm <file>..." to update what will be committed)  
  (use "git restore <file>..." to discard changes in working directory)  
        deleted:    reports/lab1.md  

- ser17@WIN-GCHLLJVFKQQ:~/project-1$ git status  
On branch master  
Changes to be committed:  
  (use "git restore --staged <file>..." to unstage)  
        modified:   reports/lab1.md

- После удаления файла команда git status сообщает об этом (deleted:    reports/lab1.md). Но в выводе видно, что файл в двух состояниях: готов к коммиту и удален. Это конфликтная ситуация, которую нужно решить. В моем случае я просто вернула файл и сделала коммит. После отката изменений файл возвращается таким же, каким был. git status так же сообщает об этом.

## Задание 5
- ser17@WIN-GCHLLJVFKQQ:~/project-1$ git branch  
* master

- ser17@WIN-GCHLLJVFKQQ:~/project-1$ git checkout -b lab1-1  
Switched to a new branch 'lab1-1'

- Первая команда вывела текущую ветку - master, а вторая создала новую - lab1-1 - с помощью -b (branch) и сразу же перевелючилась на нее.

- ser17@WIN-GCHLLJVFKQQ:~/project-1$ git branch  
  lab1-1  
* master

- При переключении обратно на ветку master изменения в файле reports/lab1.md не отображаются. 

- ser17@WIN-GCHLLJVFKQQ:~/project-1$ git checkout lab1-1  
M       README.md  
Already on 'lab1-1'

- Гит перенес незакоммиченные изменения. Это произошло, потому что в ветке lab1-1 не было изменений в файле README.md, которые конфликтовали бы с этими. В противном случае гит запретил бы переключение между ветками. 

## Задание 6
- После слияния веток командой git merge lab1-1 все изменения в reports/lab1.md стали отображаться и в ветке master.

- ser17@WIN-GCHLLJVFKQQ:~/project-1$ git merge lab1-1  
Auto-merging README.md  
CONFLICT (content): Merge conflict in README.md  
Auto-merging reports/lab1.md  
CONFLICT (content): Merge conflict in reports/lab1.md  
Automatic merge failed; fix conflicts and then commit the result.

- При попытке слияния веток с разными изменениями в одних и тех же файлах в каждом из них остаются и те, и те изменения. Изменения из ветки lab1-1 были обозначены символами "=" и подписью, из какой они ветки. Во всех местах такого конфликта в файлах я убрала ту версию изменений, которая осталась от ветки lab1-1. 

- ser17@WIN-GCHLLJVFKQQ:~/project-1$ git branch -d lab1-1  
Deleted branch lab1-1 (was 08650c9).  
ser17@WIN-GCHLLJVFKQQ:~/project-1$ git branch  
* master

- Ветка lab1-1 была удалена с помощью команды git branch -d.

## Задание 7
- Я создала ключ SSH, создала приватный репозиторий project-lab1 в GitHub. 

- Все данные успешно перенеслись в гит хаб.  












