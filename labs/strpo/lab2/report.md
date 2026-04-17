# Лабораторная работа 2.

## Задание 1
```
ser17@WIN-GCHLLJVFKQQ:~$ cp -r ~/lab1/* ~/project-1/labs/lab2/lab1-sd/  
```
С помощью этой команды я скопировала лабораторную 1 по структурам данных в папку lab1-sd (которая в папке lab2).

- Файл gitignore нужен, чтобы при создании, например, коммита, гит игнорировал определенные файлы. Эту и более подаробную информацию про gitignore я прочитала [тут](https://git-scm.com/docs/gitignore) и [тут](https://purpleschool.ru/knowledge-base/git/basics/gitignore?ysclid=mnest9p0jf492046379).

```
ser17@WIN-GCHLLJVFKQQ:/project-1$ git add labs/lab2/lab1-sd/  
ser17@WIN-GCHLLJVFKQQ:/project-1$ git add labs/lab2/report.md  
ser17@WIN-GCHLLJVFKQQ:/project-1$ git status  
On branch master  
Your branch is up to date with 'origin/master'.  
Changes to be committed:  
  (use "git restore --staged <file>..." to unstage)  
        new file:   labs/lab2/lab1-sd/.gitignore  
        new file:   labs/lab2/lab1-sd/Makefile  
        new file:   labs/lab2/lab1-sd/input.txt  
        new file:   labs/lab2/lab1-sd/lab1  
        new file:   labs/lab2/lab1-sd/rect.hpp  
        new file:   labs/lab2/lab1-sd/src/barrel.cpp  
        new file:   labs/lab2/lab1-sd/src/barrel.hpp  
        new file:   labs/lab2/lab1-sd/src/main.cpp  
        new file:   labs/lab2/lab1-sd/src/matrix.cpp  
        new file:   labs/lab2/lab1-sd/src/matrix.hpp  
        new file:   labs/lab2/lab1-sd/src/my_string.cpp  
        new file:   labs/lab2/lab1-sd/src/my_string.hpp  
        new file:   labs/lab2/lab1-sd/src/rect.cpp  
        new file:   labs/lab2/lab1-sd/src/rect.hpp  
        new file:   labs/lab2/lab1-sd/src/text_wrapper.cpp  
        new file:   labs/lab2/lab1-sd/src/text_wrapper.hpp  
        new file:   labs/lab2/lab1-sd/tests/test_bounding_rect.cpp  
        new file:   labs/lab2/lab1-sd/tests/test_rect_basic_methods.cpp  
        new file:   labs/lab2/lab1-sd/tests/test_rect_operations.cpp  
        new file:   labs/lab2/lab1-sd/tests/test_rect_properties.cpp  
        new file:   labs/lab2/report.md  
ser17@WIN-GCHLLJVFKQQ:/project-1$ git commit -m "Коммит для лаб2. Задание 1."  
```

Я добавила файл .gitignore и сделала коммит. Во всех файлах, кроме build и a.out, сохранились изменения.

## Задание 2
- Защита веток - это определенные настройки репозитория, которые позволяют избежать случайного удаления или изменения веток. Читала я [тут](https://docs.github.com/ru/repositories/configuring-branches-and-merges-in-your-repository/managing-protected-branches/managing-a-branch-protection-rule) и [тут](https://techhaps.com/ru/p/how-to-set-up-and-maintain-github-branch-protection-rules-8204740).

- Для защиты ветки на GitHub я зашла в настройки репозитория, в раздел Branches и добавила настройку: для ветки master поставила галочку на "Require a pull request before merging". Но проблема в том, что гит хаб не позволяет это сделать в приватном репозитории. Я временно сделала репозиторий публичным в настройках. Теперь проблем нет и настройка применилась.

Изменения отправились, тк я забыла отключить обход правил для администратора. Так что я добавила еще галочку на "Do not allow bypassing the above settings". 

```
ser17@WIN-GCHLLJVFKQQ:/project-1$ git commit -m "Еще одна проверка работы защиты веток"  
[master e8ae942] Еще одна проверка работы защиты веток  
 1 file changed, 1 insertion(+), 1 deletion(-)  
ser17@WIN-GCHLLJVFKQQ:/project-1$ git push  
Enumerating objects: 9, done.  
Counting objects: 100% (9/9), done.  
Delta compression using up to 18 threads  
Compressing objects: 100% (4/4), done.  
Writing objects: 100% (5/5), 696 bytes | 696.00 KiB/s, done.  
Total 5 (delta 1), reused 0 (delta 0), pack-reused 0  
remote: Resolving deltas: 100% (1/1), completed with 1 local object.  
remote: error: GH006: Protected branch update failed for refs/heads/master.  
remote:  
remote: - Changes must be made through a pull request.  
To github.com:wikiped1ya/project-lab1.git  
 ! [remote rejected] master -> master (protected branch hook declined)  
error: failed to push some refs to 'github.com:wikiped1ya/project-lab1.git'  
```

Теперь защита веток работает правильно и мне не удалось сделать git push. 

*Запись для тестовой ветки*

- Изменения сохранились и получилось сделать push из ветки pr-test.  
```
ser17@WIN-GCHLLJVFKQQ:/project-1$ git commit -m "Изменения в тестовой ветке"  
[pr-test 5a193b9] Изменения в тестовой ветке  
 1 file changed, 27 insertions(+)  
ser17@WIN-GCHLLJVFKQQ:/project-1$ git push origin pr-test  
Enumerating objects: 14, done.  
Counting objects: 100% (14/14), done.  
Delta compression using up to 18 threads  
Compressing objects: 100% (8/8), done.  
Writing objects: 100% (10/10), 1.68 KiB | 1.68 MiB/s, done.  
Total 10 (delta 2), reused 0 (delta 0), pack-reused 0  
remote: Resolving deltas: 100% (2/2), completed with 1 local object.  
remote:  
remote: Create a pull request for 'pr-test' on GitHub by visiting:  
remote:      https://github.com/wikiped1ya/project-lab1/pull/new/pr-test  
remote:  
To github.com:wikiped1ya/project-lab1.git  
 * [new branch]      pr-test -> pr-test  
```

## Задание 3
- Через GitHub я сделала pull request, ветки получилось слить.  
```
ser17@WIN-GCHLLJVFKQQ:/project-1$ git pull  
remote: Enumerating objects: 1, done.  
remote: Counting objects: 100% (1/1), done.  
remote: Total 1 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)  
Unpacking objects: 100% (1/1), 881 bytes | 881.00 KiB/s, done.  
From github.com:wikiped1ya/project-lab1  
   a5b8b91..6f66b8e  master     -> origin/master  
Updating e8ae942..6f66b8e  
Fast-forward  
 labs/lab2/report.md | 43 +++++++++++++++++++++++++++++++++++++++++++  
 1 file changed, 43 insertions(+)  
ser17@WIN-GCHLLJVFKQQ:/project-1$ git branch  
* master  
  pr-test  
```







