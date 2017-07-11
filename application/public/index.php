<?php
session_start();
	



/*
 * Подключение файла констант...
 */
require_once '../config/constants.inc';
require_once '../config/langueges.inc';
echo INSTALL;

if(is_file(INSTALL."install.php")):
    require_once INSTALL."install.php";
    exit();
endif;

require_once CORE.'controllers/functions.inc';

$lang = setLanguege($langarray);
define('LANGDIR',rtrim($lang,'/'));

$cache = new cache();

$config = new config();

$route = new route();

$param = $route->routes($lang);
define('LANG',$param['lang']);

$cache->cache_path = APP.'temp/cache'; //устанавливает папку где будут хранится файлы кеширования


/*
 * Установка обработчика ошибок...
 */

ini_set( 'display_errors', 1 );
error_reporting( -1 );
set_error_handler( array( 'Errors', 'captureNormal' ) );
set_exception_handler( array( 'Errors', 'captureException' ) );
register_shutdown_function( array( 'Errors', 'captureShutdown' ) );


/*
 * Начало кеширования
 * есть возможность кешировать отдельные блоки
 * для этого нужно третьим параметром передавать TURE 
 * $cache->start('ALLPAGES',60*60*24,TRUE) );
 * $cache->page['ALLPAGES'] -- нужно указывать нужный блок вместо ALLPAGES
 */ 

if($cache->start('ALLPAGES',1) ):

/*
 * Дальше можно выводить любой другой контент
 */
    
makeLayout($param);


endif;


/*
 * Обезательно нжуно завершать кеширование для формирования файла 
 * а иначе файл не будет перезаписыватся...
 */
if(CACHE)
    $cache->end_cache('ALLPAGES');

unset($cache,$config,$route);
?>
