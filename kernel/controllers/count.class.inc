<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of count
 *
 * @author Alex
 */
class count {
   
    public static function count_txt(){
        // Объявляем некоторые константы
        define('COOKIE_NAME', '__count_date');
        define('SPLITTER'   , ' ');
        define('STAT_FILE'  , 'stat.txt');
        define('TODAY_TIME' , time());
        define('TODAY_DATE' , date('Y-m-d') );


        // Получение куки
        $userTime = isset($_COOKIE[ COOKIE_NAME ]) ? (int) $_COOKIE[ COOKIE_NAME ] : null;

        // Установка куки
        setcookie(COOKIE_NAME, TODAY_TIME, TODAY_TIME + 60 * 60 * 24);

        // Проверка на хост (хостом пусть будет браузер без куки)
        if ( $userTime )
            $isNewHost = date('Y-m-d', $userTime) !== TODAY_DATE;
        else 
            $isNewHost = true;

        // Хитом будем называть просто показ страницы
        $isHit = true;

        // Обнуляем суммарные значения счтёчика
        $totalHosts = (int) $isNewHost;
        $totalHits  = (int) $isHit;

        $todayHosts = (int) $isNewHost;
        $todayHits  = (int) $isHit;

        // Открываем файл статистики для чтения и записи
        if ( $fp = fopen(STAT_FILE, 'a+b') )
        {
            // Блокируем файл, чтобы не дать другим процессам переписать файл до его обработки
            if ( flock($fp, LOCK_EX) )
            {
                // Файл успешно блокирован, выполняем его обработку

                // Переводим указатель на начало файла
                fseek($fp, 0, SEEK_SET);

                // Подготавливаем переменные для подсчёта хитов и хостов
                $totalHostsTemp = 0;
                $todayHostsTemp = 0;

                $totalHitsTemp  = 0;
                $todayHitsTemp  = 0;

                $todayTemp = null;
                $time = 0;

                // Будем думать, что в файле первая строка содержит нужные данные
                $line = fgets($fp);

                // Пускай в первой строке содержатся: хосты, хиты, хосты за сегодня, 
                // хиты за сегодня, дата записи
                if ( $line ) @list($totalHostsTemp, $totalHitsTemp, $todayHostsTemp, 
        $todayHitsTemp, $todayTemp ,$time) = explode(SPLITTER, $line);

                // Проверка даты
                if ( $todayTemp !== TODAY_DATE )
                {
                    // Дата в файле ститистики устарела, обнуляем сегодняшие хосты и хиты
                    $todayHostsTemp = 0;
                    $todayHitsTemp  = 0;
                }

                // Прибавляем данные
                $totalHosts += $totalHostsTemp;
                $todayHosts += $todayHostsTemp;

                $totalHits  += $totalHitsTemp;
                $todayHits  += $todayHitsTemp;

                // Переводим указатель на начало файла
                fseek($fp, 0, SEEK_SET);

                // Урезаем файл до нулевой длины
                ftruncate($fp, 0);

                // Записываем данные - сначало хосты, хиты, хосты за сегодня, 
                // хиты за сегодня, дата
                fputs($fp, join(SPLITTER, 
                    array($totalHosts, $totalHits, $todayHosts, $todayHits, TODAY_DATE, $time )));

                // Снимаем блокировку, но можно и не снимать, если верить мануалу
                flock($fp, LOCK_UN);
            }

            // Обработка файла завершена, закрываем файловый указатель
            fclose($fp);
        }
    }
    public static function get_statistic(){
       // define('SPLITTER'   , ' ');
       // define('STAT_FILE'  , 'stat.txt');

        // Переменные статистики
        $totalHosts = 0;
        $totalHits  = 0;

        $todayHosts = 0;
        $todayHits  = 0;

        if ( file_exists(STAT_FILE) && ($fp = fopen(STAT_FILE, 'rb')) ){
            // Файл статистики существует и доступен для чтения

            // Считываем первую строку
            $line = fgets($fp);
            fclose($fp);

            // Пускай в первой строке содержатся: хосты, хиты, 
            // хосты за сегодня, хиты за сегодня, дата записи
            if ( $line ) @list($data['totalHosts'], $data['totalHits'], $data['todayHosts'], $data['todayHits'],$data['date'],$data['time']) = explode(SPLITTER, $line);
        }
        return $data;
    }
    public static function put_stat_time($time){
        // Открываем файл статистики для чтения и записи
        if ( $fp = fopen(STAT_FILE, 'a+b') )
        {
            // Блокируем файл, чтобы не дать другим процессам переписать файл до его обработки
            if ( flock($fp, LOCK_EX) )
            {
                // Файл успешно блокирован, выполняем его обработку

                // Переводим указатель на начало файла
                fseek($fp, 0, SEEK_SET);

                // Подготавливаем переменные для подсчёта хитов и хостов
                $totalHostsTemp = 0;
                $todayHostsTemp = 0;

                $totalHitsTemp  = 0;
                $todayHitsTemp  = 0;

                $todayTemp = null;

                // Будем думать, что в файле первая строка содержит нужные данные
                $line = fgets($fp);

                // Пускай в первой строке содержатся: хосты, хиты, хосты за сегодня, 
                // хиты за сегодня, дата записи
                if ( $line ) @list($totalHosts, $totalHits, $todayHosts, 
                                        $todayHits, $today) = preg_split(SPLITTER, $line);

                // Переводим указатель на начало файла
                fseek($fp, 0, SEEK_SET);

                // Урезаем файл до нулевой длины
                ftruncate($fp, 0);

                // Записываем данные - сначало хосты, хиты, хосты за сегодня, 
                // хиты за сегодня, дата
                fputs($fp, join(SPLITTER, 
                    array($totalHosts, $totalHits, $todayHosts, $todayHits, $today ,$time)));

                // Снимаем блокировку, но можно и не снимать, если верить мануалу
                flock($fp, LOCK_UN);
            }

            // Обработка файла завершена, закрываем файловый указатель
            fclose($fp);
        }
    }
}

?>
