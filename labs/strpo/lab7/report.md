# Лабораторная работа 7.

## Задание 1. Создание виртуальной машины.
1. Для работы я буду использовать Ubuntu. Он у меня уже установлен
```
PS C:\WINDOWS\system32> wsl --list --verbose
  NAME      STATE           VERSION
* Ubuntu    Running         2
```

2. WSL - это полноценная виртуальная машина, а я использую именно ее. Она создает изолированную среду с собственным ядром Linux.
```
PS C:\WINDOWS\system32> wsl --version
Версия WSL: 2.6.3.0
Версия ядра: 6.6.87.2-1
Версия WSLg: 1.0.71
Версия MSRDC: 1.2.6353
Версия Direct3D: 1.611.1-81528511
Версия DXCore: 10.0.26100.1-240331-1435.ge-release
Версия Windows: 10.0.26200.8246
```

3. Когда кто то получает доступ к твоей ВМ, он получает так же возможность выполнять команды внутри твоего Linux. В случае если это sudo / root, то человек может вообще все: устанавливать программы, менять настройки, читать любые файлы, выключать систему. Чтобы минимизировать угрозы, я попробую использовать SSH-ключи вместо паролей, ограничить права доступа, после работы удалить напарника и возможно еще некоторые меры предосторожности.

4. Поскольку у меня уже есть WSL, его я и буду использовать как вирутальную машину. WSL предоставляет готовую среду Linux, полностью отвечающую требованиям лабораторной работы.

## Задание 2. Настройка удаленного доступа.
1. В Windows 10 и 11 SSH-клиент уже встроен.
```
PS C:\WINDOWS\system32> ssh -V
OpenSSH_for_Windows_9.5p2, LibreSSL 3.8.2
```

2. Для настройки службы OpenSSH я сделала следующие шаги:
* Вошла в wsl в PowerShell
* Установила SSH-сервер ( на этом этапе возникли некоторые трудности в паролем, которые пришлось исправлять)
```
ser17@WIN-GCHLLJVFKQQ:/mnt/c/WINDOWS/system32$ sudo apt update
[sudo] password for ser17:
Hit:1 http://archive.ubuntu.com/ubuntu noble InRelease

*тут процесс установки*

65 packages can be upgraded. Run 'apt list --upgradable' to see them.
ser17@WIN-GCHLLJVFKQQ:/mnt/c/WINDOWS/system32$ sudo apt install openssh-server -y
Reading package lists... Done

*тут тоже*

Processing triggers for libc-bin (2.39-0ubuntu8.7) ...
```
* Отредактировала конфиг SSH-сервера:
```
Port 22 #Порт, где ssh слушает подключения
PermitRootLogin no #Запрещает вход под пользователем root
PubkeyAuthentication yes #Разерашет вход по ssh-ключам
PasswordAuthentication yes #Разрешает вход по паролю
KbdInteractiveAuthentication yes #Тоже разрешает вход по паролю, но через вспомогательные модули
```
* Сгенерировала ключи хоста
```
sudo ssh-keygen -A
```
* Запустила SSH-сервер
```
ser17@WIN-GCHLLJVFKQQ:/mnt/c/WINDOWS/system32$ sudo service ssh start
ser17@WIN-GCHLLJVFKQQ:/mnt/c/WINDOWS/system32$ sudo service ssh status
● ssh.service - OpenBSD Secure Shell server
     Loaded: loaded (/usr/lib/systemd/system/ssh.service; disabled; preset: enabled)
     Active: active (running) since Wed 2026-04-29 18:24:03 MSK; 6s ago
TriggeredBy: ● ssh.socket
       Docs: man:sshd(8)
             man:sshd_config(5)
    Process: 1277 ExecStartPre=/usr/sbin/sshd -t (code=exited, status=0/SUCCESS)
   Main PID: 1279 (sshd)
      Tasks: 1 (limit: 9206)
     Memory: 3.6M (peak: 4.0M)
        CPU: 17ms
     CGroup: /system.slice/ssh.service
             └─1279 "sshd: /usr/sbin/sshd -D [listener] 0 of 10-100 startups"

Apr 29 18:24:03 WIN-GCHLLJVFKQQ systemd[1]: Starting ssh.service - OpenBSD Secure Shell server...
Apr 29 18:24:03 WIN-GCHLLJVFKQQ sshd[1279]: Server listening on 0.0.0.0 port 22.
Apr 29 18:24:03 WIN-GCHLLJVFKQQ sshd[1279]: Server listening on :: port 22.
Apr 29 18:24:03 WIN-GCHLLJVFKQQ systemd[1]: Started ssh.service - OpenBSD Secure Shell server.
```
* Чтобы не стартовать каждый раз вручную, добавила автозапуск
```
ser17@WIN-GCHLLJVFKQQ:/mnt/c/WINDOWS/system32$ sudo systemctl enable ssh
Synchronizing state of ssh.service with SysV service script with /usr/lib/systemd/systemd-sysv-install.
Executing: /usr/lib/systemd/systemd-sysv-install enable ssh
Created symlink /etc/systemd/system/sshd.service → /usr/lib/systemd/system/ssh.service.
Created symlink /etc/systemd/system/multi-user.target.wants/ssh.service → /usr/lib/systemd/system/ssh.service.
```
* Проверила подключение из Windows к wsl
```
PS C:\WINDOWS\system32> ssh localhost -p 2222
The authenticity of host '[localhost]:2222 ([127.0.0.1]:2222)' can't be established.
ED25519 key fingerprint is SHA256:hj0GpmFmr7JzufpCMCxdgnt9WwgMtcoI/SgQT4yRs3s.
This key is not known by any other names.
```

3. Порт TCP — это числовой идентификатор (от 0 до 65535), который помогает компьютеру понять, какой программе предназначены приходящие данные.
*Основная роль порта:* Определить, какой программе (службе) на компьютере предназначены входящие данные.

Пробрасывание портов - это механизм, который перенаправляет входящий трафик с одного порта на другой адрес и/или порт. 

Это позволяет подключаться к WSL через SSH, указывая порт 2222 на локальном компьютере.

Основная часть информации [отсюда](https://www.osp.ru/winitpro/2005/06/380029) и [отсюда](https://www.dotcom-monitor.com/learn/glossary/tcp-port/)

4. Еще в прошлом пункте я создала правило проброса портов
```
PS C:\WINDOWS\system32> netsh interface portproxy add v4tov4 listenport=2222 listenaddress=0.0.0.0 connectport=22 connectaddress=localhost
```

Открыла порт в брандмауэре
```
PS C:\WINDOWS\system32> New-NetFirewallRule -DisplayName "SSH-WSL" -Direction Inbound -Protocol TCP -LocalPort 2222 -Action Allow


Name                          : {cbdaabbe-91e6-4114-b7cc-f52599a1999c}
DisplayName                   : SSH-WSL
Description                   :
DisplayGroup                  :
Group                         :
Enabled                       : True
Profile                       : Any
Platform                      : {}
Direction                     : Inbound
Action                        : Allow
EdgeTraversalPolicy           : Block
LooseSourceMapping            : False
LocalOnlyMapping              : False
Owner                         :
PrimaryStatus                 : OK
Status                        : Правило было успешно проанализировано из хранилища. (65536)
EnforcementStatus             : NotApplicable
PolicyStoreSource             : PersistentStore
PolicyStoreSourceType         : Local
RemoteDynamicKeywordAddresses : {}
PolicyAppId                   :
PackageFamilyName             :
```

Вход по паролю:
```
PS C:\WINDOWS\system32> ssh -p 2222 ser17@localhost
(ser17@localhost) Password:
Welcome to Ubuntu 24.04.3 LTS (GNU/Linux 6.6.87.2-microsoft-standard-WSL2 x86_64)

 * Documentation:  https://help.ubuntu.com
 * Management:     https://landscape.canonical.com
 * Support:        https://ubuntu.com/pro

 System information as of Wed Apr 29 18:53:52 MSK 2026

  System load:  0.06                Processes:             35
  Usage of /:   0.2% of 1006.85GB   Users logged in:       2
  Memory usage: 5%                  IPv4 address for eth0: 172.29.245.237
  Swap usage:   0%

 * Strictly confined Kubernetes makes edge and IoT secure. Learn how MicroK8s
   just raised the bar for easy, resilient and secure K8s cluster deployment.

   https://ubuntu.com/engage/secure-kubernetes-at-the-edge
```

5. SSH использует асимметричное шифрование: создаётся пара ключей — приватный и публичный. Приватный ключ хранится на клиентской машине и никогда не передаётся по сети. Публичный ключ размещается на сервере в файле. 
При подключении сервер отправляет клиенту случайное число, клиент подписывает его приватным ключом, а сервер проверяет подпись с помощью публичного ключа. Если подпись верна — доступ разрешается без ввода пароля.

6. Я создала ключи
```
PS C:\WINDOWS\system32> ssh-keygen -t ed25519 -C "ser17-wsl-key"
Generating public/private ed25519 key pair.
Enter file in which to save the key (/home/ser17/.ssh/id_ed25519):
/home/ser17/.ssh/id_ed25519 already exists.
Overwrite (y/n)? y
Enter passphrase (empty for no passphrase):
Enter same passphrase again:
Your identification has been saved in /home/ser17/.ssh/id_ed25519
Your public key has been saved in /home/ser17/.ssh/id_ed25519.pub
The key fingerprint is:
SHA256:LtOoKWi0pkeafeUdY298KMfrvuXjKXHiOWEcMiOcCaE ser17-wsl-key
The key's randomart image is:
+--[ED25519 256]--+
|    ..           |
|   ..            |
|  E  o o         |
|      = + .      |
|       .S= .     |
| ..   .++ * .    |
|.*.  o+ooO B.    |
|+++ .o.oo %oo.   |
|=. oo    *=B+.   |
+----[SHA256]-----+
```

Скопировала публичный ключ в wsl
```
PS C:\WINDOWS\system32> type $env:USERPROFILE\.ssh\id_ed25519.pub | ssh -p 2222 ser17@localhost "mkdir -p ~/.ssh && cat >> ~/.ssh/authorized_keys"
(ser17@localhost) Password:
```

Проверка подключения без пароля:
```
PS C:\WINDOWS\system32> ssh -p 2222 ser17@localhost
Welcome to Ubuntu 24.04.3 LTS (GNU/Linux 6.6.87.2-microsoft-standard-WSL2 x86_64)

 * Documentation:  https://help.ubuntu.com
 * Management:     https://landscape.canonical.com
 * Support:        https://ubuntu.com/pro

 System information as of Wed Apr 29 19:20:15 MSK 2026

  System load:  0.0                 Processes:             36
  Usage of /:   0.2% of 1006.85GB   Users logged in:       2
  Memory usage: 5%                  IPv4 address for eth0: 172.29.245.237
  Swap usage:   0%

 * Strictly confined Kubernetes makes edge and IoT secure. Learn how MicroK8s
   just raised the bar for easy, resilient and secure K8s cluster deployment.

   https://ubuntu.com/engage/secure-kubernetes-at-the-edge
Last login: Wed Apr 29 19:18:10 2026 from 127.0.0.1
```

7. В файле /etc/ssh/sshd_config я изменила строки:
```
...
PasswordAuthentication no
...
KbdInteractiveAuthentication no
...
ChallengeResponseAuthentication no
...
```

Перезапустила сервер:
```
ser17@WIN-GCHLLJVFKQQ:~$ sudo service ssh restart
ser17@WIN-GCHLLJVFKQQ:~$ sudo service ssh status
● ssh.service - OpenBSD Secure Shell server
     Loaded: loaded (/usr/lib/systemd/system/ssh.service; enabled; preset: enabled)
     Active: active (running) since Wed 2026-04-29 19:27:30 MSK; 4s ago
TriggeredBy: ● ssh.socket
       Docs: man:sshd(8)
             man:sshd_config(5)
    Process: 1718 ExecStartPre=/usr/sbin/sshd -t (code=exited, status=0/SUCCESS)
   Main PID: 1719 (sshd)
      Tasks: 1 (limit: 9206)
     Memory: 1.2M (peak: 1.6M)
        CPU: 19ms
     CGroup: /system.slice/ssh.service
             └─1719 "sshd: /usr/sbin/sshd -D [listener] 0 of 10-100 startups"

Apr 29 19:27:30 WIN-GCHLLJVFKQQ systemd[1]: Starting ssh.service - OpenBSD Secure Shell server...
Apr 29 19:27:30 WIN-GCHLLJVFKQQ sshd[1719]: Server listening on 0.0.0.0 port 22.
Apr 29 19:27:30 WIN-GCHLLJVFKQQ sshd[1719]: Server listening on :: port 22.
Apr 29 19:27:30 WIN-GCHLLJVFKQQ systemd[1]: Started ssh.service - OpenBSD Secure Shell server.
```

Пробую подключиться с помощью пароля
```
PS C:\WINDOWS\system32> ssh -p 2222 -o PreferredAuthentications=password ser17@localhost
ser17@localhost: Permission denied (publickey).
```

## Задание 3. Настройка сессии для другого пользователя.






























