# Лабораторная работа 2.

*Я удаляла символы "~" в фрагментах из командной строки, потому что иначе часть текста зачеркивались там, где это не нужно.*

## Задание 1
- ser17@WIN-GCHLLJVFKQQ:~$ cp -r ~/lab1/* ~/project-1/labs/lab2/lab1-sd/  
С помощью этой команды я скопировала лабораторную 1 по структурам данных в папку lab1-sd (которая в папке lab2).

- Файл gitignore нужен, чтобы при создании, например, коммита, гит игнорировал определенные файлы. Эту и более подаробную информацию про gitignore я прочитала [тут](https://git-scm.com/docs/gitignore) и [тут](https://purpleschool.ru/knowledge-base/git/basics/gitignore?ysclid=mnest9p0jf492046379).

- ser17@WIN-GCHLLJVFKQQ:/project-1$ git add labs/lab2/lab1-sd/  
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

Я добавила файл .gitignore и сделала коммит. Во всех файлах, кроме build и a.out, сохранились изменения.

## Задание 2
- Защита веток - это определенные настройки репозитория, которые позволяют избежать случайного удаления или изменения веток. Читала я [тут](https://docs.github.com/ru/repositories/configuring-branches-and-merges-in-your-repository/managing-protected-branches/managing-a-branch-protection-rule) и [тут](https://techhaps.com/ru/p/how-to-set-up-and-maintain-github-branch-protection-rules-8204740).

- Для защиты ветки на GitHub я зашла в настройки репозитория, в раздел Branches и добавила настройку: для ветки master поставила галочку на "Require a pull request before merging". Но проблема в том, что гит хаб не позволяет это сделать в приватном репозитории. Я временно сделала репозиторий публичным в настройках. Теперь проблем нет и настройка применилась.




