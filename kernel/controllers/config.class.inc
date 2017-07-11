<?php if ( ! defined('BASE')) exit('Нету прямого доступа к данному скрипту');

/**
 * Класс который отвечает за загрузку конфигураций 
 * из корфигарционных файлов из папки config
 * и помещает их в статический массив для возможности 
 * их использования в любом месте кода...
 *
 * @author Alex
 */
class config {
    
    public static $config = NULL;
    
    function __construct() {        
       if(self::$config==NULL):
            require_once APP.'config/database.inc';
            require_once APP.'config/routs.inc';           
            self::$config = $config;
            
            if(!is_file(INSTALL."install.php")):
                $route = db::GetAll("SELECT r.url,r.route,p.url AS page FROM routes r
                                     JOIN pages p ON p.id = r.p_id");
                self::$config['route'] = array();
                for($x=0;$x<sizeof($route);$x++):
                     self::$config['route'][LANGDIR.'/'.$route[$x]['url']] = $route[$x]['page'].'/'.$route[$x]['route'];
                endfor;  

                $redirect = db::GetAll("SELECT url,redirect FROM redirects");
                self::$config['redirect'] = array();
                for($y=0;$y<sizeof($redirect);$y++):
                    self::$config['redirect'][$redirect[$y]['url']] = $redirect[$y]['redirect']; 
                endfor;
            endif;
        endif;       
    }
}

?>
