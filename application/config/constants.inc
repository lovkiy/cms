<?php
/*
 * Установка базовой директории...
 */
define('BASE',realpath('../../'));

/*
 *Установка базовой директории для приложения 
 */

define('APP', BASE."/application/");

/*
 * Установка базового пути к ядру
 */

define('CORE', BASE."/kernel/");

/*
 * Установка разширения шаблонов и макетов
 */

define('EXT', '.tpl');

/*
 * Установка базового пути к модулям
 */

define('MODULES',APP.'modules/');

/*
 * Включение/выключение отображения нотисов и варнингсов
 */

define('DEBBUG',FALSE);

/*
 * Название сайта берем из названия хоста
 */

define('SITENAME',$_SERVER['SERVER_NAME']);

/*
 *Базовый урл который нужен для установки постоянных 
 * адрессов ссылок и закгрузки CSS и JS скриптов...
 * ато падла работать не хочет без этого ппц....((((( 
 */

define('BASEURL','http://'.SITENAME.'/');

/*
 * Язык по умолчанию
 */
define('LANGUEGE','ru');

/*
 *Включение выключение кеширования 
 */
define('CACHE',FALSE);

/*
 * Путь к папке с  файлами для инсталяции
 */

define('INSTALL', BASE.'/install/');
/*
 * Путь к папке загрузок
 */
define('UPLOAD',APP.'public/uploads/');

?>
