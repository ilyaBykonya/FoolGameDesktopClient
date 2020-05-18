# FoolGameDesktopClientd
ПК-клиент игры для Windows 10 (возможно, запустится на восьмёрке).
Разделён на 3 части:
  ApplicationGUI, InstanceGUI и ApplicationEthernetController (не очень удачные названия, потом поправлю).

  InstanceGUI - отвечает за показ игры пользователю, а также собирает информацию
  о его действиях (нажатиях) во время игры и передаёт её классу ApplicationEthernetController

  ApplicationEthernetController - отвечает за связь с сервером и создание игрового окна.

  ApplicationGUI - отвечает за настройки, операции с кошельком, выбор типа игры.
  Короче - меню.
