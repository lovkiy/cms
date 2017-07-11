<?php if ( ! defined('BASE')) exit('Нету прямого доступа к данному скрипту');

/**
 * Класс который отвечает за кеширование
 * он может как целиком кешировать все страницы
 * или же есть возможность кеширования отдельных 
 * блоков и их дальнейшего паринга
 * Для этого нужно третьим параметром передавать TURE 
 * $cache->start('ALLPAGES',60*60*24,TRUE) );
 * $cache->page['ALLPAGES'] -- нужно указывать нужный блок вместо ALLPAGES
 *
 * @author Alex
 */
class Cache {
   
    public $page = array();
    public $cachce_path = 'cache';
 
    private static $doc;
    private $time = array();
    private $_time_kick;
 
    function start($param,$time=0,$type=false) {
        
        if(!CACHE)
            return TRUE;
        
        if(empty($param)) {
            exit('Для кэширования нужно обязательно указывать параметр идентификации');
        }
 
        $this->time[$param] = $time;

        $file_name = md5($_SERVER['HTTP_HOST'].$_SERVER['REQUEST_URI'].$param);

        if(! is_dir(APP.'temp/cache/'.substr($file_name,0,1).'/') )
        mkdir(APP.'temp/cache/'.substr($file_name,0,1).'/');

        self::$doc = APP.'temp/cache/'.substr($file_name,0,1).'/'.$file_name.".txt";


        if(! file_exists(self::$doc)){
            ob_start();
            return true;
        }

        $file = $this->_get_file();
        
        
        if($time != 0) {           
            if($this->_check_time($file)) {                 
                ob_start();
                return true;
            }
        }
       
        if($type) {
            $this->page[$param] = $file;
        }else{            
            echo str_replace($this->_time_kick."\r\n",'',$file);          
        }
        return false;
    }
 
    function end_cache($param) {
        
        $file = $this->_get_file();
        
        if($this->_check_time($file)){
            $buffer = ob_get_contents();
            ob_end_clean();
            $this->_write_file($buffer,$param);
            echo $buffer; 
        }        
    }
 
    private function _check_time($str) {
        $time ='';
        preg_match_all('/<!--time([0-9]+)time-->/',$str,$time);
        $this->_time_kick = $time[0][0];        
        if( (int) $time[1][0] > (int) microtime('get_as_float')) {            
            return false;
        }else{           
            return true;
        }
    }
 
    private function _write_file($buffer,$param) {

        $ch = fopen(self::$doc,'w+');

        if($this->time[$param] == 0 ) {
            $dc = fwrite($ch,$buffer);
        }else{
            $current = (int) microtime('get_as_float');
            $time_to = $current + (int)$this->time[$param];
            $point = '<!--time'. $time_to .'time-->'."\r\n";
            $dc = fwrite($ch,$buffer.$point);
        }

            if(! $dc) {
                exit("Файл кэша не может быть записан.");
            }
        fclose($ch);
    }
 
    private function _get_file() {

        $ch =  fopen(self::$doc,'r');
        $str = fread($ch,filesize(self::$doc));
        fclose($ch);
        return $str;
    }
}

?>
