# FoolGameDesktopClientd
ПК-клиент игры для Windows 10 (возможно, запустится на восьмёрке).
Разделён на две части:
  GUI и ApplicationEthernetController (не очень удачное название, потом поправлю). 
  
  GUI - отвечает за показ игры пользователю, а также собирает информацию о его действиях (нажатиях)
        и передаёт её классу  ApplicationEthernetController
    
  ApplicationEthernetController - отвечает за связь с сервером и создание игрового окна.
