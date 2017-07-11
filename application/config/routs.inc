<?php if ( ! defined('BASE')) exit('Нету прямого доступа к данному скрипту');

/*
 * Настройки для маршрутизации
 * 
 */

$config['route_def'][LANGDIR.'/admin/(\w*)']                     = 'admin/$1';
$config['route_def'][LANGDIR.'/admin/(\w*)/(\w*)']               = 'admin/$1/$2';
$config['route_def'][LANGDIR.'/admin/(\w*)/(\w*)/(\w*)']         = 'admin/$1/$2/$3';
$config['route_def'][LANGDIR.'/admin/(\w*)/(\w*)/(\w*)/(\w*)']         = 'admin/$1/$2/$3/$4';
$config['route_def'][LANGDIR.'/admin/(\w*)/(\w*)/(\w*)/(\w*)/(\w*)']         = 'admin/$1/$2/$3/$4/$5';
$config['route_def'][LANGDIR.'/admin/(\w*)/(\w*)/(\w*)/(\w*)/(\w*)/(\w*)']         = 'admin/$1/$2/$3/$4/$5/$6';
$config['route_def'][LANGDIR.'/admin/(\w*)/(\w*)/(\w*)/(\w*)/(\w*)/(\w*)/(\w*)']         = 'admin/$1/$2/$3/$4/$5/$6/$7';


$config['route_def'][LANGDIR.'/group/(\w*)']                    = 'main/group/$1';
$config['route_def'][LANGDIR.'/item/(\w*)']                    = 'main/item/$1';
$config['route_def'][LANGDIR.'/loguot']                    = 'main/loguot';
$config['route_def'][LANGDIR.'/(\w*)|(\-*)']                    = '$1';
$config['route_def'][LANGDIR.'/(\w*)/[%_0-9A-Za-zА-Яа-яЁё]*']                    = '$1/$2';
$config['route_def'][LANGDIR.'/(\w*)/(\w*)/(\w*)']                    = '$1/$2/$3';


?>
