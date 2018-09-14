# Clean Room
## Abstract

Чистая комната - разновидность занятий, которая в целом похожа на лабораторные условия. Они нацелены на обретение практических навыков в безопасной среде (без давления и профессиональной оценки) и нацелены в первую очередь на овладение навыком написания тестов с целью его дальнейшего применения.

На первой стадии "чистая комната" подразумевает под собой участие в процессе приближенном к реальным боевым условиям (вероятно, даже работа над кодом одного из существующих продуктов), но в безопасной обстановке.

Продолжительность выполнения этого задания в сумме должна быть порядка 4-х часов работы, так чтобы ее можно было разделить на несколько сессии.

Тут группа работает уже в большей степени самостоятельно, куратор вмешивается гораздо реже, лишь в случае, когда встречаются грубые нарушения базовых принципов.

На каждой сессии ученики работают парами друг с другом, меняя состав пары в процессе сессии.

Каждое занятие начинается с небольшой планерки и постановки целей на сегодня.

Первое занятие посвящено планированию и перед группой стоит две задачи - обсудить и внести правки в спецификацию и составить список тестов для реализации.

В конце каждой сессии куратор формулирует список решенных и оставшихся для решения задач и дает обратную связь участникам по процессу.

## Specification

**Implement chat application, that communicates via TCP sockets.**
 * It receives user nickname through commandline arguments on start
 * It runs only for two clients
 * On start it checks if port 4444 is bound
    * if it is - connects to other client
    * if not - binds a port and waits for inbound connection
        * message "No one is here..." is displayed in UI
 * After establishing connection - handshake is performed:
    * client writes message with it's nickname and ':HELLO!' string to socket ("metizik:HELLO!")
    * server responses with it's nickname and ':HELLO!' magic ("user:HELLO!")
        * if server receives malformated message - it drops connection with this client
        * if client receives malformated message - it drops connection and exits
            * Error message is shown
    * Listening socket must be closed
        (i) More than one client is not allowed to connect

 * It must send messages via created connection, until it is dropped
    * Application outputs "me: " prefix for user input
    * User inputs message through console interface and presses ENTER
    * Text message is sent to socket
 * It must receive messages via created connection, until it is dropped
    * Message received through socket
    * Line with message and '@friend_name: ' prefix is displayed ("metizik: Hello!")
 * End of message is determined by '\0' byte
 * When connection is dropped by one of users
    * "You are alone now" message is displayed to user
    * Application exits

  (i) Client starts dialog

 OPTIONAL requirements:
* If user enters '!exit!' message, application must close connection and exit
* If user runs app with 'me' nickname - error with text "Username me is reserved and can not be used"  is displayed and application exits
