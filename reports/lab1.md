# Отчет по выполнению работы

## Задание 1
    ser17@WIN-GCHLLJVFKQQ:~/project-1$ git version  
    git version 2.43.0


    ser17@WIN-GCHLLJVFKQQ:~$ git config --list  
    user.email=vshalnuh@gmail.com  
    user.name=wikiped1ya


    ser17@WIN-GCHLLJVFKQQ:~/project-1$ git --help  
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

```
ser17@WIN-GCHLLJVFKQQ:/project-1$ git add README.md reports/lab1.md  
ser17@WIN-GCHLLJVFKQQ:/project-1$ git commit -m "Начальный коммит"  
 [master (root-commit) c35051b] Начальный коммит  
 2 files changed, 57 insertions(+)  
 create mode 100644 README.md  
 create mode 100644 reports/lab1.md  
```

- Сначала файлы переводятся в режим staget(то есть подготовлены к коммиту) при помощи комманды add, а затем создается сам коммит к текстовым сообщением "Начальный коммит" с помощью команды commit -m.

## Задание 3
    ser17@WIN-GCHLLJVFKQQ:/project-1$ git add reports/lab1.md  
    ser17@WIN-GCHLLJVFKQQ:/project-1$ git status  
    On branch master  
    Changes to be committed:  
      (use "git restore --staged <file>..." to unstage)  
            modified:   reports/lab1.md  


    ser17@WIN-GCHLLJVFKQQ:/project-1$ git commit -m "Тот же коммит коммит"  
    [master 6958af4] Тот же коммит коммит  
     1 file changed, 9 insertions(+)  
    ser17@WIN-GCHLLJVFKQQ:/project-1$ git status  
    On branch master  
    nothing to commit, working tree clean  

- После первого коммита(начального) git status показал, что изменений нет, так как тогда файл был только создан. Сейчас git status вывел информацию об изменениях после первого коммита.

- Команда git diff вывела конкретные строчки, которые были добавлены/удалены.

- На этапе 3.3 git status показывает, что изменений нет, а git diff вывело то же, что и прежде

```
ser17@WIN-GCHLLJVFKQQ:~/project-1$ git status  
On branch master  
Changes to be committed:  
  (use "git restore --staged <file>..." to unstage)  
        modified:   reports/lab1.md  
```

- После изменения файла и добавления их в индекс git status показывает, что изменения есть и они ждут коммита.

- Файл reports/lab1.md был в индексе, а README.md нет. Поэтому когда я создаю коммит, сохраняется только первый

```
ser17@WIN-GCHLLJVFKQQ:~/project-1$ git status  
On branch master  
Changes to be committed:  
  (use "git restore --staged <file>..." to unstage)  
        modified:   reports/lab1.md  
Changes not staged for commit:  
  (use "git add/rm <file>..." to update what will be committed)  
  (use "git restore <file>..." to discard changes in working directory)  
        deleted:    reports/lab1.md  
```

```
ser17@WIN-GCHLLJVFKQQ:~/project-1$ git status  
On branch master  
Changes to be committed:  
  (use "git restore --staged <file>..." to unstage)  
        modified:   reports/lab1.md
```

- После удаления файла команда git status сообщает об этом (deleted:    reports/lab1.md). Но в выводе видно, что файл в двух состояниях: готов к коммиту и удален. Это конфликтная ситуация, которую нужно решить. В моем случае я просто вернула файл и сделала коммит. После отката изменений файл возвращается таким же, каким был. git status так же сообщает об этом.

## Задание 5
    ser17@WIN-GCHLLJVFKQQ:~/project-1$ git branch  
      master


    ser17@WIN-GCHLLJVFKQQ:~/project-1$ git checkout -b lab1-1  
    Switched to a new branch 'lab1-1'

- Первая команда вывела текущую ветку - master, а вторая создала новую - lab1-1 - с помощью -b (branch) и сразу же перевелючилась на нее.

```
ser17@WIN-GCHLLJVFKQQ:~/project-1$ git branch  
 *lab1-1  
  master
```

- При переключении обратно на ветку master изменения в файле reports/lab1.md не отображаются. 

```
ser17@WIN-GCHLLJVFKQQ:~/project-1$ git checkout lab1-1  
M       README.md  
Already on 'lab1-1'
```

- Гит перенес незакоммиченные изменения. Это произошло, потому что в ветке lab1-1 не было изменений в файле README.md, которые конфликтовали бы с этими. В противном случае гит запретил бы переключение между ветками. 

## Задание 6
- После слияния веток командой git merge lab1-1 все изменения в reports/lab1.md стали отображаться и в ветке master.

```
ser17@WIN-GCHLLJVFKQQ:~/project-1$ git merge lab1-1  
Auto-merging README.md  
CONFLICT (content): Merge conflict in README.md  
Auto-merging reports/lab1.md  
CONFLICT (content): Merge conflict in reports/lab1.md  
Automatic merge failed; fix conflicts and then commit the result.
```

- При попытке слияния веток с разными изменениями в одних и тех же файлах в каждом из них остаются и те, и те изменения. Изменения из ветки lab1-1 были обозначены символами "=" и подписью, из какой они ветки. Во всех местах такого конфликта в файлах я убрала ту версию изменений, которая осталась от ветки lab1-1. 

```
ser17@WIN-GCHLLJVFKQQ:/project-1$ git branch -d lab1-1  
Deleted branch lab1-1 (was 08650c9).  
ser17@WIN-GCHLLJVFKQQ:/project-1$ git branch  
  master
```

- Ветка lab1-1 была удалена с помощью команды git branch -d.

## Задание 7
- Я создала ключ SSH, создала приватный репозиторий project-lab1 в GitHub. 

- Все данные успешно перенеслись в гит хаб.  

```
ser17@WIN-GCHLLJVFKQQ:~/project-1$ git log --oneline  
f524282 (HEAD -> master) Обновление отчета. Задание 7.  
c39e923 (origin/master) Обновление отчета. Задание 7.  
09d18c2 Обновление отчета. Снова задание 6  
14b0b76 Обновление файлов. Еще одно в задании 6.  
ec57b7f Обновление файлов. Последнее в задании 6.  
08650c9 Обновление файлов. Задание 6.  
dfd9eae Обновление README.md. Задание 6.  
1b55067 Обновление README.md. Задание 6.  
bbb5407 Обновление отчета. Снова задание 5.  
49feb10 Обновление отчета. Задании 5.  
2cbc1d5 Обновление отчета. Все еще задание 4.  
05fdd6b Обновлен отчет. Задание 4.  
6958af4 Тот же коммит коммит  
c35051b Начальный коммит  

ser17@WIN-GCHLLJVFKQQ:~/project-1$ git push  
Enumerating objects: 9, done.  
Counting objects: 100% (9/9), done.  
Delta compression using up to 18 threads  
Compressing objects: 100% (4/4), done.  
Writing objects: 100% (5/5), 985 bytes | 985.00 KiB/s, done.  
Total 5 (delta 2), reused 0 (delta 0), pack-reused 0  
remote: Resolving deltas: 100% (2/2), completed with 2 local objects.  
To github.com:wikiped1ya/project-lab1.git  
   c39e923..f524282  master -> master  
```

## Задание 8
    ser17@WIN-GCHLLJVFKQQ:~/project-test$ git clone git@github.com:wikiped1ya/project-lab1.git  
    Cloning into 'project-lab1'...  
    remote: Enumerating objects: 67, done.  
    remote: Counting objects: 100% (67/67), done.  
    remote: Compressing objects: 100% (33/33), done.  
    remote: Total 67 (delta 19), reused 67 (delta 19), pack-reused 0 (from 0)  
    Receiving objects: 100% (67/67), 10.00 KiB | 1.67 MiB/s, done.  
    Resolving deltas: 100% (19/19), done.  

- При помощи этой команды репозиторий скопировался в новую директорию. Содержимое файлов полностью совпадает.

```
ser17@WIN-GCHLLJVFKQQ:~/project-1$ git fetch  
remote: Enumerating objects: 7, done.  
remote: Counting objects: 100% (7/7), done.  
remote: Compressing objects: 100% (2/2), done.  
remote: Total 4 (delta 1), reused 4 (delta 1), pack-reused 0 (from 0)  
Unpacking objects: 100% (4/4), 783 bytes | 391.00 KiB/s, done.  
From github.com:wikiped1ya/project-lab1  
   724d3dc..db8ad71  master     -> origin/master  
```

- Вывод означает, что нужно передать 7 объектов. Из них только два были новыми. 4 объекта передано, дальше написана информация о них. 

- После git pull данные из project-test перенеслись сюда. 

- Сводка последних изменений:

```
commit db8ad7118a1b09e6b72abab3b638bb6c9eb21eae (HEAD -> master, origin/master)
Author: wikiped1ya <vshalnuh@gmail.com>
Date:   Thu Mar 26 18:12:49 2026 +0300

    Последний коммит. Задание 8.
    
commit 724d3dcc77df7c503b3dbe9d8e5f77a8d41aa33a
Author: wikiped1ya <vshalnuh@gmail.com>
Date:   Thu Mar 26 17:56:28 2026 +0300
    
    Правки еще. Задание 7.
    
commit afc62d1765cd8d67279d03e4fe7036d70885e76e
Author: wikiped1ya <vshalnuh@gmail.com>
Date:   Thu Mar 26 17:51:53 2026 +0300
    
    Правки. Задание 7.
    
commit f524282b726333ddfb2644856639c3d9b25b278a
Author: wikiped1ya <vshalnuh@gmail.com>
Date:   Thu Mar 26 17:47:06 2026 +0300
    
    Обновление отчета. Задание 7.
    
commit c39e92316927337bf74160c5035e0adca6617a06
Author: wikiped1ya <vshalnuh@gmail.com>
Date:   Thu Mar 26 17:33:17 2026 +0300
    
    Обновление отчета. Задание 7.
    
commit 09d18c2f064e21e70c2d4d33cee1f684041df643
Author: wikiped1ya <vshalnuh@gmail.com>
Date:   Thu Mar 26 16:32:35 2026 +0300
    
    Обновление отчета. Снова задание 6
    
commit 14b0b76a3bfaffb16c1c9e4f313dad4f9caed1bd
Author: wikiped1ya <vshalnuh@gmail.com>
Date:   Thu Mar 26 16:27:08 2026 +0300
    
    Обновление файлов. Еще одно в задании 6.
    
commit ec57b7f9f7775564ff887fcb0cdb1f1f18c65c92
Merge: dfd9eae 08650c9
Author: wikiped1ya <vshalnuh@gmail.com>
Date:   Thu Mar 26 16:22:38 2026 +0300
    
    Обновление файлов. Последнее в задании 6.
    
commit 08650c941cd89660caf24f0dc661ac7ac286b847
Author: wikiped1ya <vshalnuh@gmail.com>
Date:   Thu Mar 26 16:16:37 2026 +0300
    
    Обновление файлов. Задание 6.
    
commit dfd9eae6424aa18aac0059e72e80a63fe8f55374
Author: wikiped1ya <vshalnuh@gmail.com>
Date:   Thu Mar 26 15:46:24 2026 +0300
    
    Обновление README.md. Задание 6.
    
commit 1b55067c5c7f4721ecf65e879ecccf298d69274a
Author: wikiped1ya <vshalnuh@gmail.com>
Date:   Thu Mar 26 15:45:48 2026 +0300
    
    Обновление README.md. Задание 6.
    
commit bbb540765d3e03e1c9686b853d910605bee97ba6
Author: wikiped1ya <vshalnuh@gmail.com>
Date:   Thu Mar 26 15:37:13 2026 +0300
    
    Обновление отчета. Снова задание 5.
    
commit 49feb10e0717d148f9d19907a4673e9b4c390c37
Author: wikiped1ya <vshalnuh@gmail.com>
Date:   Thu Mar 26 15:29:05 2026 +0300
    
    Обновление отчета. Задании 5.
    
commit 2cbc1d552f95b89503830a9a2b45d2aecb62640d
Author: wikiped1ya <vshalnuh@gmail.com>
Date:   Thu Mar 26 15:10:31 2026 +0300
    
    Обновление отчета. Все еще задание 4.
   
commit 05fdd6b7f74df6367aa83aab72832379edbdebac
Author: wikiped1ya <vshalnuh@gmail.com>
Date:   Thu Mar 26 14:36:54 2026 +0300
    
    Обновлен отчет. Задание 4.
    
commit 6958af42b214d66cf7636c0e5d0d7e857713e914
Author: wikiped1ya <vshalnuh@gmail.com>
Date:   Wed Mar 25 22:14:41 2026 +0300
    
    Тот же коммит коммит
    
commit c35051b03eb87850fb68f7c8dd5632299b54c65a
Author: wikiped1ya <vshalnuh@gmail.com>
Date:   Wed Mar 25 21:55:30 2026 +0300
    
    Начальный коммит
```


