# booking-rooms-application
## Домашняя работа по предмету прикладное программирование, семестровый проект по курсу Qt/QML

Приложение, позволяющее пользователю искать, просматривать и бронировать доступные комнаты в отелях. Также предусмотрена возможность использования сервиса администраторами для изменения и добавления данных о комнатах и отелях.

Проект состоит из 2 частей: серверная и клиентская.

### Серверная часть: 
HTTPServer с sqlite3 базой данных на борту. Позволяет проводить авторизацию, получать данные из базы, а также добавлять их в базу.
### Клиентская часть: 
QML приложение-клиент для взаимодействия с сервером посредством отправки запросов и отображения данных пользователю, с возможностью изменять или добавлять данные в базу.
### Список фич:
- Возможность регистрации и авторизации, разбиение пользователей на группы по правам на админов и юзеров.
- Просмотр списка доступных отелей, выбор комнат в них, бронь выбранных доступных комнат.
- Для админов доступно добавление отелей, комнат и т.д. в базу данных на сервере.
- Создание сессии после авторизации, просмотр всех забронированных комнат для текущего пользователя.
### Требования к серверной части:
- python 3.6
- BaseHttpServer
- Sqlite3
### Требования к клиентской части:
- QT 5.14.2
- QT Quick

## Инструкции по сборке
### Сервер
Запустить скрипт в папке Server:```python3 main.py```
### Клиент
Запустить проект Client в среде разработки
Либо собрать через терминал: 
```qmake Client.pro && make && make clean```
